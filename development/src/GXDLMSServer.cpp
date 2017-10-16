//
// --------------------------------------------------------------------------
//  Gurux Ltd
//
//
//
// Filename:        $HeadURL$
//
// Version:         $Revision$,
//                  $Date$
//                  $Author$
//
// Copyright (c) Gurux Ltd
//
//---------------------------------------------------------------------------
//
//  DESCRIPTION
//
// This file is a part of Gurux Device Framework.
//
// Gurux Device Framework is Open Source software; you can redistribute it
// and/or modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General Public License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#include "../include/GXDLMSServer.h"
#include "../include/GXDLMS.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSAssociationShortName.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXAPDU.h"
#include "../include/GXSecure.h"
#include "../include/GXDLMSValueEventCollection.h"
#include "profile_cap_objects.h"
#include "Helper\Helper.h"


CGXDLMSServer::CGXDLMSServer(bool logicalNameReferencing,
    DLMS_INTERFACE_TYPE type) : m_Transaction(NULL), m_Settings(true),    
    m_LinkEstablished(false)
{
    m_Settings.SetUseLogicalNameReferencing(logicalNameReferencing);
    m_Settings.SetInterfaceType(type);
	m_CurrentALN = new CGXDLMSAssociationLogicalName("0.0.40.0.0.255");
	m_CurrentALN->SetDataValidity(true);
    if (GetUseLogicalNameReferencing())
    {
        SetConformance((DLMS_CONFORMANCE)(DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_ACTION |
            DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_SET_OR_WRITE |
            DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_GET_OR_READ |
            DLMS_CONFORMANCE_SET | DLMS_CONFORMANCE_SELECTIVE_ACCESS |
            DLMS_CONFORMANCE_ACTION | DLMS_CONFORMANCE_MULTIPLE_REFERENCES |
            DLMS_CONFORMANCE_GET | DLMS_CONFORMANCE_GENERAL_PROTECTION));
    }
    Reset();
}

CGXDLMSServer::~CGXDLMSServer()
{
	delete m_CurrentALN;
}

CGXDLMSObjectCollection*& CGXDLMSServer::GetItems()
{
    return m_Settings.GetObjects();
}

void CGXDLMSServer::SetCipher(CGXCipher* value)
{
    m_Settings.SetCipher(value);
}

CGXDLMSSettings& CGXDLMSServer::GetSettings()
{
    return m_Settings;
}

CGXByteBuffer& CGXDLMSServer::GetCtoSChallenge()
{
    return m_Settings.GetCtoSChallenge();
}

CGXByteBuffer& CGXDLMSServer::GetStoCChallenge()
{
    return m_Settings.GetStoCChallenge();
}

DLMS_INTERFACE_TYPE CGXDLMSServer::GetInterfaceType()
{
    return m_Settings.GetInterfaceType();
}

void CGXDLMSServer::SetStoCChallenge(CGXByteBuffer& value)
{
    m_Settings.SetUseCustomChallenge(value.GetSize() != 0);
    m_Settings.SetStoCChallenge(value);
}

void CGXDLMSServer::SetStartingPacketIndex(int value)
{
    m_Settings.SetBlockIndex(value);
}

int CGXDLMSServer::GetInvokeID()
{
    return m_Settings.GetInvokeID();
}

CGXDLMSLimits& CGXDLMSServer::GetLimits()
{
    return m_Settings.GetLimits();
}

unsigned short CGXDLMSServer::GetMaxReceivePDUSize()
{
    return m_Settings.GetMaxServerPDUSize();
}

void CGXDLMSServer::SetMaxReceivePDUSize(unsigned short value)
{
    m_Settings.SetMaxServerPDUSize(value);
}

bool CGXDLMSServer::GetUseLogicalNameReferencing()
{
    return m_Settings.GetUseLogicalNameReferencing();
}

/**
 * @param value
 *            Is Logical Name referencing used.
 */
void CGXDLMSServer::SetUseLogicalNameReferencing(bool value)
{
    m_Settings.SetUseLogicalNameReferencing(value);
}

bool CGXDLMSServer::IsLongTransaction() {
	if (m_Transaction == NULL) {
		return false;
	}
	return true;
}

int CGXDLMSServer::Initialize()
{
    m_Initialized = true;

	m_Settings.GetLimits().SetWindowSizeRX(1);
	m_Settings.GetLimits().SetWindowSizeTX(1);
	m_Settings.GetLimits().SetMaxInfoRX(256);
	m_Settings.GetLimits().SetMaxInfoTX(256);

    std::string ln;
	CGXByteBuffer c_ln;
	CGXDLMSObject* tmp_obj = nullptr;
    for (CGXDLMSObjectCollection::iterator it = GetItems()->begin(); it != GetItems()->end(); ++it)
    {
		c_ln.Clear();
		c_ln.Set(*it, 6);
		tmp_obj = GetItems()->FindByLN(DLMS_OBJECT_TYPE_ALL, c_ln);
		if (tmp_obj != NULL) {
			tmp_obj->GetLogicalName(ln);
			if (ln.size() == 0)
			{
				//Invalid Logical Name.
				tmp_obj = nullptr;
				GetItems()->FreeConstructedObj();
				return DLMS_ERROR_CODE_INVALID_LOGICAL_NAME;
			}
			tmp_obj = nullptr;
			GetItems()->FreeConstructedObj();
		}
	}
	std::vector<CGXDLMSObject*> tmp_dlms_obj = GetItems()->GetDlmsObj();
	for (std::vector<CGXDLMSObject*>::iterator it = tmp_dlms_obj.begin(); it != tmp_dlms_obj.end(); ++it) {
		(*it)->GetLogicalName(ln);
		if (ln.size() == 0)
		{
			//Invalid Logical Name.
			return DLMS_ERROR_CODE_INVALID_LOGICAL_NAME;
		}
	}    
    return 0;
}


int CGXDLMSServer::UpdateShortNames()
{
    return UpdateShortNames(true);
}

int CGXDLMSServer::UpdateShortNames(bool force)
{
    return 0;
}

void CGXDLMSServer::Reset(bool connected)
{
    if (m_Transaction != NULL)
    {
        delete m_Transaction;
        m_Transaction = NULL;
    }
    m_Settings.SetCount(0);
    m_Settings.SetIndex(0);
    m_Settings.SetConnected(false);
    m_ReceivedData.Clear();
    m_ReplyData.Clear();
    if (!connected)
    {        
        m_Info.Clear();
        m_Settings.SetServerAddress(0);
        m_Settings.SetClientAddress(0);
        m_LinkEstablished = false;
    }

    m_Settings.SetAuthentication(DLMS_AUTHENTICATION_NONE);
    if (m_Settings.GetCipher() != NULL)
    {
        if (!connected)
        {
            m_Settings.GetCipher()->Reset();
        }
        else
        {
            m_Settings.GetCipher()->SetSecurity(DLMS_SECURITY_NONE);
        }
    }
}

void CGXDLMSServer::Reset()
{    
    Reset(false);
}

/**
    * Parse AARQ request that client send and returns AARE request.
    *
    * @return Reply to the client.
    */
int CGXDLMSServer::HandleAarqRequest(
    CGXByteBuffer& data,
    CGXDLMSConnectionEventArgs& connectionInfo)
{
    int ret;
    DLMS_ASSOCIATION_RESULT result = DLMS_ASSOCIATION_RESULT_ACCEPTED;
    m_Settings.GetCtoSChallenge().Clear();
    m_Settings.GetStoCChallenge().Clear();
    DLMS_SOURCE_DIAGNOSTIC diagnostic;
    if (m_Settings.GetInterfaceType() == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        Reset(true);
    }
    ret = CGXAPDU::ParsePDU(m_Settings, m_Settings.GetCipher(), data, diagnostic);
	if (ret == DLMS_ERROR_CODE_INVALID_TAG || ret == DLMS_ERROR_CODE_OUTOFMEMORY || ret == DLMS_ERROR_CODE_INVALID_PARAMETER)
	{
		diagnostic = DLMS_SOURCE_DIAGNOSTIC_NOT_SUPPORTED;
	}
    if (diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE)
    {
        result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;        
        InvalidConnection(connectionInfo);
    }
    else
    {
        diagnostic = ValidateAuthentication(m_Settings.GetAuthentication(), m_Settings.GetPassword());
        if (diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE)
        {
            result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
            InvalidConnection(connectionInfo);
        }
        else if (m_Settings.GetAuthentication() > DLMS_AUTHENTICATION_LOW)
        {
            // If High authentication is used.
            CGXByteBuffer challenge;
            if ((ret = CGXSecure::GenerateChallenge(m_Settings.GetAuthentication(), challenge)) != 0)
            {
                return ret;
            }
            m_Settings.SetStoCChallenge(challenge);
            result = DLMS_ASSOCIATION_RESULT_ACCEPTED;
            diagnostic = DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED;
        }
        else
        {
            Connected(connectionInfo);
            m_Settings.SetConnected(true);
        }
    }
    if (m_Settings.GetInterfaceType() == DLMS_INTERFACE_TYPE_HDLC)
    {
        m_ReplyData.Set(LLC_REPLY_BYTES, 3);
    }
    // Generate AARE packet.
    return CGXAPDU::GenerateAARE(m_Settings, m_ReplyData, result, diagnostic, m_Settings.GetCipher());
}

/**
 * Parse SNRM Request. If server do not accept client empty byte array is
 * returned.
 *
 * @return Returns returned UA packet.
 */
unsigned char ParseSNRM(CGXByteBuffer& data, CGXDLMSLimits& lms) {
	if (data.GetSize() == 0) {
		if (lms.GetMaxInfoTX() > lms.DEFAULT_MAX_INFO_TX) {
			lms.DefaultInfoTX();
		}
		if (lms.GetMaxInfoRX() > lms.DEFAULT_MAX_INFO_RX) {
			lms.DefaultInfoRX();
		}
		if (lms.GetWindowSizeTX() > lms.DEFAULT_WINDOWS_SIZE_TX) {
			lms.DefaultWindowSizeTX();
		}
		if (lms.GetWindowSizeRX() > lms.DEFAULT_WINDOWS_SIZE_RX) {
			lms.DefaultWindowSizeRX();
		}
		return 0;
	}
	else {
		unsigned char ch, id, len;
		unsigned short ui;
		unsigned long ul;
		unsigned char ret;
		unsigned char fl[4];
		memset(fl, 0, 4);
		if ((ret = data.GetUInt8(&ch)) != 0)
		{
			return ret;
		}
		if ((ret = data.GetUInt8(&ch)) != 0)
		{
			return ret;
		}
		if ((ret = data.GetUInt8(&ch)) != 0)
		{
			return ret;
		}
		unsigned int value;
		while (data.GetPosition() < data.GetSize())
		{
			if ((ret = data.GetUInt8(&id)) != 0)
			{
				return ret;
			}
			if ((ret = data.GetUInt8(&len)) != 0)
			{
				return ret;
			}
			switch (len)
			{
			case 1:
				if ((ret = data.GetUInt8(&ch)) != 0)
				{
					return ret;
				}
				value = ch;
				break;
			case 2:
				if ((ret = data.GetUInt16(&ui)) != 0)
				{
					return ret;
				}
				value = ui;
				break;
			case 4:
				if ((ret = data.GetUInt32(&ul)) != 0)
				{
					return ret;
				}
				value = ul;
				break;
			default:
				return DLMS_ERROR_CODE_INVALID_PARAMETER;
			}
			switch (id)
			{
			case HDLC_INFO_MAX_INFO_TX:
				if (value < lms.GetMaxInfoRX()) {
					lms.SetMaxInfoRX(value);
				}
				break;
			case HDLC_INFO_MAX_INFO_RX:
				if (value < lms.GetMaxInfoTX()) {
					lms.SetMaxInfoTX(value);
				}
				break;
			case HDLC_INFO_WINDOW_SIZE_TX:
				if (value < lms.GetWindowSizeRX()) {
					lms.SetWindowSizeRX(value);
				}
				break;
			case HDLC_INFO_WINDOW_SIZE_RX:
				if (value < lms.GetWindowSizeRX()) {
					lms.SetWindowSizeTX(value);
				}
				break;
			default:
				ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
				break;
			}
			fl[id - 5] = 1;
		}
		for (unsigned char i = 0; i < 4; ++i) {
			if (fl[i] != 1) {
				switch (i + 5)
				{
				case HDLC_INFO_MAX_INFO_TX:
					if (lms.DEFAULT_MAX_INFO_RX < lms.GetMaxInfoRX()) {
						lms.DefaultInfoRX();
					}
					break;
				case HDLC_INFO_MAX_INFO_RX:
					if (lms.DEFAULT_MAX_INFO_TX < lms.GetMaxInfoTX()) {
						lms.DefaultInfoTX();
					}
					break;
				case HDLC_INFO_WINDOW_SIZE_TX:
					if (lms.DEFAULT_WINDOWS_SIZE_RX < lms.GetWindowSizeRX()) {
						lms.DefaultWindowSizeRX();
					}
					break;
				case HDLC_INFO_WINDOW_SIZE_RX:
					if (lms.DEFAULT_WINDOWS_SIZE_TX < lms.GetWindowSizeRX()) {
						lms.DefaultWindowSizeTX();
					}
					break;
				}
			}
		}
		return ret;
	}
}

int CGXDLMSServer::HandleSnrmRequest(CGXByteBuffer& data, CGXDLMSSettings& settings, CGXByteBuffer& reply)
{
	m_Settings.GetLimits().SetWindowSizeRX(1);
	m_Settings.GetLimits().SetWindowSizeTX(1);
	m_Settings.GetLimits().SetMaxInfoRX(256);
	m_Settings.GetLimits().SetMaxInfoTX(256);
    Reset(true);
	m_LinkEstablished = false;
	unsigned char ret = ParseSNRM(data, GetLimits());
	if (ret != 0) {
		return ret;
	}
    reply.SetUInt8(0x81); // FromatID
    reply.SetUInt8(0x80); // GroupID
    reply.SetUInt8(0x14); // Length
    reply.SetUInt8(HDLC_INFO_MAX_INFO_TX);
    reply.SetUInt8(2);
	reply.SetUInt16(GetLimits().GetMaxInfoTX());

    reply.SetUInt8(HDLC_INFO_MAX_INFO_RX);
    reply.SetUInt8(2);
	reply.SetUInt16(GetLimits().GetMaxInfoRX());

    reply.SetUInt8(HDLC_INFO_WINDOW_SIZE_TX);
    reply.SetUInt8(4);
	reply.SetUInt32(GetLimits().GetWindowSizeTX());

    reply.SetUInt8(HDLC_INFO_WINDOW_SIZE_RX);
	reply.SetUInt8(4);
	reply.SetUInt32(GetLimits().GetWindowSizeRX());

    return 0;
}

/**
 * Generates disconnect request.
 *
 * @return Disconnect request.
 */
int GenerateDisconnectRequest(CGXDLMSSettings& settings, CGXByteBuffer& reply)
{
    if (settings.GetInterfaceType() == DLMS_INTERFACE_TYPE_WRAPPER)
    {
        reply.SetUInt8(0x63);
        reply.SetUInt8(0x0);
    }
    else
    {
        reply.SetUInt8(0x81); // FromatID
        reply.SetUInt8(0x80); // GroupID
		reply.SetUInt8(0x14); // Length

		reply.SetUInt8(HDLC_INFO_MAX_INFO_TX);
		reply.SetUInt8(2);
		reply.SetUInt16(settings.GetLimits().GetMaxInfoTX());

		reply.SetUInt8(HDLC_INFO_MAX_INFO_RX);
		reply.SetUInt8(2);
		reply.SetUInt16(settings.GetLimits().GetMaxInfoRX());

		reply.SetUInt8(HDLC_INFO_WINDOW_SIZE_TX);
		reply.SetUInt8(4);
		reply.SetUInt32(settings.GetLimits().GetWindowSizeTX());

		reply.SetUInt8(HDLC_INFO_WINDOW_SIZE_RX);
		reply.SetUInt8(4);
		reply.SetUInt32(settings.GetLimits().GetWindowSizeRX());
    }
    return 0;
}

int ReportError(CGXDLMSSettings& settings, DLMS_COMMAND command, DLMS_ERROR_CODE error, CGXByteBuffer& reply)
{
    int ret;
    DLMS_COMMAND cmd;
    CGXByteBuffer data;
    switch (command)
    {
    case DLMS_COMMAND_READ_REQUEST:
        cmd = DLMS_COMMAND_READ_RESPONSE;
        break;
    case DLMS_COMMAND_WRITE_REQUEST:
        cmd = DLMS_COMMAND_WRITE_RESPONSE;
        break;
    case DLMS_COMMAND_GET_REQUEST:
        cmd = DLMS_COMMAND_GET_RESPONSE;
        break;
    case DLMS_COMMAND_SET_REQUEST:
        cmd = DLMS_COMMAND_SET_RESPONSE;
        break;
    case DLMS_COMMAND_METHOD_REQUEST:
        cmd = DLMS_COMMAND_METHOD_RESPONSE;
        break;
    default:
        // Return HW error and close connection.
        cmd = DLMS_COMMAND_NONE;
        break;
    }

    if (settings.GetUseLogicalNameReferencing())
    {
        CGXDLMSLNParameters p(&settings, cmd, 1,
            NULL, NULL, error);
        ret = CGXDLMS::GetLNPdu(p, data);
    }
    if (ret == 0)
    {
        if (settings.GetInterfaceType() == DLMS_INTERFACE_TYPE_WRAPPER)
        {
            ret = CGXDLMS::GetWrapperFrame(settings, data, reply);
        }
        else
        {
            ret = CGXDLMS::GetHdlcFrame(settings, 0, &data, reply);
        }
    }
    return ret;
}

int CGXDLMSServer::HandleSetRequest(
    CGXByteBuffer& data,
    short type,
    CGXDLMSLNParameters& p)
{
    CArtVariant value;
    int ret;
    unsigned char index, ch;
    unsigned short tmp;
	m_CurrentALN->GetObjectList().FreeConstructedObj();
	if ((ret = data.GetUInt16(&tmp)) != 0)
    {
        return ret;
    }
    DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)tmp;
    CGXByteBuffer ln;
    ln.Set(&data, data.GetPosition(), 6);
    // Attribute index.
    if ((ret = data.GetUInt8(&index)) != 0)
    {
        return ret;
    }
	 // Get Access Selection.
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    if (type == 2)
    {
        unsigned long size, blockNumber;
        if ((ret = data.GetUInt8(&ch)) != 0)
        {
            return ret;
        }
        p.SetMultipleBlocks(ch == 0);
        ret = data.GetUInt32(&blockNumber);
        if (ret != 0)
        {
            return ret;
        }
        if (blockNumber != m_Settings.GetBlockIndex())
        {
            p.SetStatus(DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);
            return 0;
        }
        m_Settings.IncreaseBlockIndex();
        ret = GXHelpers::GetObjectCount(data, size);
        if (ret != 0)
        {
            return ret;
        }
        unsigned long realSize = data.GetSize() - data.GetPosition();
        if (size != realSize)
        {
            p.SetStatus(DLMS_ERROR_CODE_BLOCK_UNAVAILABLE);
            return 0;
        }
    }
    if (!p.IsMultipleBlocks())
    {
        m_Settings.ResetBlockIndex();
        ret = GXHelpers::GetDataCA(data, value);
        if (ret != 0)
        {
            return ret;
        }
    }
	CGXDLMSObject* obj = m_CurrentALN->GetObjectList().FindByLN(ci, ln);
    if (obj == NULL)
    {
        std::string name;
        GXHelpers::GetLogicalName(ln, name);
        obj = FindObject(ci, 0, name);
    }
    // If target is unknown.
    if (obj == NULL)
    {
        // Device reports a undefined object.
        p.SetStatus(DLMS_ERROR_CODE_UNAVAILABLE_OBJECT);
    }
    else
    {
        CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, index);
        CGXDLMSValueEventCollection list;
        DLMS_ACCESS_MODE am = GetAttributeAccess(e);
        // If write is denied.
        if (am != DLMS_ACCESS_MODE_WRITE && am != DLMS_ACCESS_MODE_READ_WRITE)
        {
            //Read Write denied.
            p.SetStatus(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        }
        else
        {
			if (p.IsMultipleBlocks()) {
				e->SetValue(value);
				list.push_back(e);
				m_Transaction = new CGXDLMSLongTransaction(list, DLMS_COMMAND_GET_REQUEST, data);
			}
			else {
				VarInfo v_info;
				value.GetVar(v_info);
				if (v_info.vt != DLMS_DATA_TYPE_NONE) {
					if (v_info.vt == DLMS_DATA_TYPE_OCTET_STRING)
					{
						DLMS_DATA_TYPE dt;
						ret = obj->GetDataType(index, dt);
						if (ret != 0)
						{
							p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
							obj = nullptr;
							m_CurrentALN->GetObjectList().FreeConstructedObj();
							return ret;
						}
						if (dt != DLMS_DATA_TYPE_NONE && dt != DLMS_DATA_TYPE_OCTET_STRING)
						{
							CArtVariant tmp;
							if ((ret = value.ChangeType(v_info.size, dt, tmp)) != 0)
							{
								value.Clear();
								tmp.Clear();
								p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
								obj = nullptr;
								m_CurrentALN->GetObjectList().FreeConstructedObj();
								return ret;
							}
							value = tmp;
						}
					}
					value.position = 0;
					e->SetValue(value);
					list.push_back(e);
					if (p.IsMultipleBlocks())
					{
						m_Transaction = new CGXDLMSLongTransaction(list, DLMS_COMMAND_GET_REQUEST, data);
					}
					PreWrite(list);
					if (e->GetError() != 0)
					{
						p.SetStatus(e->GetError());
					}
					else if (!e->GetHandled() && !p.IsMultipleBlocks() && e->GetTarget()->GetDataValidity())
					{
						obj->SetValue(m_Settings, *e);
						PostWrite(list);
					}
				}
				else {
					p.SetStatus(DLMS_ERROR_CODE_READ_WRITE_DENIED);
				}
			}
		}
    }
	if(m_Transaction == nullptr){
		obj = nullptr;
		m_CurrentALN->GetObjectList().FreeConstructedObj();
	}
    return ret;
}

int CGXDLMSServer::HanleSetRequestWithDataBlock(CGXByteBuffer& data, CGXDLMSLNParameters& p)
{
    int ret;
    unsigned long blockNumber, size;
    unsigned char ch;
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    p.SetMultipleBlocks(ch == 0);
    if ((ret = data.GetUInt32(&blockNumber)) != 0)
    {
        return ret;
    }
	if (blockNumber != m_Settings.GetBlockIndex() && !p.IsLastBlock())
	{
		p.SetStatus(DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);
	}
    else
    {
        m_Settings.IncreaseBlockIndex();
        if ((ret = GXHelpers::GetObjectCount(data, size)) != 0)
        {
            return ret;
        }
        unsigned long realSize = data.GetSize() - data.GetPosition();
        if (size != realSize)
        {
            p.SetStatus(DLMS_ERROR_CODE_BLOCK_UNAVAILABLE);
        }
        m_Transaction->GetData().Set(&data, data.GetPosition());
        // If all data is received.
        if (!p.IsMultipleBlocks())
        {
            CArtVariant value;
            if ((ret != GXHelpers::GetDataCA(m_Transaction->GetData(), value)) != 0)
            {
                return ret;
            }
            CGXDLMSValueEventArg * target = *m_Transaction->GetTargets().begin();
			VarInfo v_info;
			value.GetVar(v_info);
            if (v_info.vt == DLMS_DATA_TYPE_OCTET_STRING)
            {
                DLMS_DATA_TYPE dt;
                ret = target->GetTarget()->GetDataType(target->GetIndex(), dt);
                if (dt != DLMS_DATA_TYPE_NONE && dt != DLMS_DATA_TYPE_OCTET_STRING)
                {
					CArtVariant bb;
                    if ((ret = value.ChangeType(v_info.size, dt, bb)) != 0)
                    {
                        return ret;
                    }
					value = bb;
                }
            }
			value.position = 0;
            target->SetValue(value);
            PreWrite(m_Transaction->GetTargets());
			p.SetStatus(target->GetError());
            if (!target->GetHandled() && !p.IsMultipleBlocks() && target->GetTarget()->GetDataValidity())
            {
                target->GetTarget()->SetValue(m_Settings, *target);
                PostWrite(m_Transaction->GetTargets());
            }
            if (m_Transaction != NULL)
            {
				m_CurrentALN->GetObjectList().FreeConstructedObj();
                delete m_Transaction;
                m_Transaction = NULL;
            }
            m_Settings.ResetBlockIndex();
        }
    }
    p.SetMultipleBlocks(true);
    return 0;
}

/**
    * Generate confirmed service error.
    *
    * @param service
    *            Confirmed service error.
    * @param type
    *            Service error.
    * @param code
    *            code
    * @return
    */
void GenerateConfirmedServiceError(
    DLMS_CONFIRMED_SERVICE_ERROR service,
    DLMS_SERVICE_ERROR type,
    unsigned char code, CGXByteBuffer& data)
{    
    data.Set(LLC_REPLY_BYTES, 3);         
    data.SetUInt8(DLMS_COMMAND_CONFIRMED_SERVICE_ERROR);
    data.SetUInt8(service);
    data.SetUInt8(type);
    data.SetUInt8(code);
}

int CGXDLMSServer::HandleSetRequest(CGXByteBuffer& data)
{
	unsigned char ch, type;
	int ret;
	// Return error if connection is not established.
	if (!m_Settings.IsConnected())
	{
		GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
			DLMS_SERVICE_ERROR_SERVICE, DLMS_SERVICE_UNSUPPORTED,
			m_ReplyData);
		return 0;
	}
	// Get type.
	if ((ret = data.GetUInt8(&type)) != 0)
	{
		return ret;
	}
	// Get invoke ID and priority.
	if ((ret = data.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_SET_RESPONSE, type, NULL, NULL, 0);
	if (type > 5) {
		type = DLMS_SET_COMMAND_TYPE_NORMAL;
		p.SetRequestType(type);
		p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
	}
	else{
		if (type == DLMS_SET_COMMAND_TYPE_NORMAL || type == DLMS_SET_COMMAND_TYPE_FIRST_DATABLOCK)
		{
			ret = HandleSetRequest(data, type, p);
		}
		else {
			if (type == DLMS_SET_COMMAND_TYPE_WITH_DATABLOCK)
			{
				// Set Request With Data Block
				ret = HanleSetRequestWithDataBlock(data, p);
			}
			else
			{
				m_Settings.ResetBlockIndex();
				p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
			}
		}
	}
	return CGXDLMS::GetLNPdu(p, m_ReplyData);
}

unsigned short CGXDLMSServer::GetRowsToPdu(CGXDLMSProfileGeneric* pg)
{
	std::vector<DLMS_DATA_TYPE> dt;
	std::string ln = pg->GetName();
	pType type = (pType)GetTypeProfile(ln);
	if (type != PROFILE_TYPE_UNKOWN) {
		GetProfileCaptureObjectsTypes(dt, type);
	}
	int rowsize = 0;
    // Count how many rows we can fit to one PDU.
    for (std::vector<DLMS_DATA_TYPE>::iterator it = dt.begin();
        it != dt.end(); ++it)
    {
        if ((*it) == DLMS_DATA_TYPE_NONE)
        {
            rowsize += 2;
        }
        else if (((*it) == DLMS_DATA_TYPE_STRUCTURE))
        {
            rowsize += 2;
        }
        else
        {
            rowsize += GXHelpers::GetDataTypeSize((*it));
        }
    }
    if (rowsize != 0)
    {
        return m_Settings.GetMaxPduSize() / rowsize;
    }
    return 0;
}

int CGXDLMSServer::GetRequestNormal(CGXByteBuffer& data)
{
    CGXByteBuffer bb;
    DLMS_ERROR_CODE status = DLMS_ERROR_CODE_OK;
    m_Settings.SetCount(0);
    m_Settings.SetIndex(0);
    m_Settings.ResetBlockIndex();
    CGXDLMSValueEventCollection arr;
    unsigned char attributeIndex;
    int ret;
    CGXByteBuffer ln; 
	m_CurrentALN->GetObjectList().FreeConstructedObj();
    // CI
    unsigned short tmp;
    if ((ret = data.GetUInt16(&tmp)) != 0)
    {
        return ret;
    }
    DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)tmp;    
    ln.Set(&data, data.GetPosition(), 6);    
    // Attribute Id
    if ((ret = data.GetUInt8(&attributeIndex)) != 0)
    {
        status = (DLMS_ERROR_CODE)ret;
    }
	else {
		CGXDLMSObject* obj = m_CurrentALN->GetObjectList().FindByLN(ci, ln);
		if (obj == NULL)
		{
			std::string name;
			GXHelpers::GetLogicalName(ln, name);
			obj = FindObject(ci, 0, name);
		}
		if (obj == NULL)
		{
			// "Access Error : Device reports a undefined object."
			status = DLMS_ERROR_CODE_UNDEFINED_OBJECT;
		}
		else
		{
			// Access selection
			unsigned char selection, selector = 0;
			if ((ret = data.GetUInt8(&selection)) != 0)
			{
				obj = nullptr;
				m_CurrentALN->GetObjectList().FreeConstructedObj();
				return ret;
			}
			CArtVariant parameters;
			if (selection != 0)
			{
				if ((ret = data.GetUInt8(&selector)) != 0)
				{
					obj = nullptr;
					m_CurrentALN->GetObjectList().FreeConstructedObj();
					return ret;
				}
				if ((ret = GXHelpers::GetDataCA(data, parameters)) != 0)
				{
					obj = nullptr;
					m_CurrentALN->GetObjectList().FreeConstructedObj();
					return ret;
				}
			}
			CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, attributeIndex, selector, parameters);
			arr.push_back(e);
			if (GetAttributeAccess(e) != DLMS_ACCESS_MODE_READ && GetAttributeAccess(e) != DLMS_ACCESS_MODE_READ_WRITE)
			{
				// Read Write denied.
				status = DLMS_ERROR_CODE_READ_WRITE_DENIED;
			}
			else
			{
				if (obj->GetObjectType() == DLMS_OBJECT_TYPE_PROFILE_GENERIC && attributeIndex == 2)
				{
					e->SetRowToPdu(GetRowsToPdu((CGXDLMSProfileGeneric*)obj));
				}
				if (e->GetIndex() != 1) {
					PreRead(arr);
				}
				if (!e->GetHandled())
				{
					m_Settings.SetCount(e->GetRowEndIndex() - e->GetRowBeginIndex());                                                           
					if (obj->GetDataValidity() || e->GetIndex() == 1) {
						if (ci != DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME) {
							ret = obj->GetValue(m_Settings, *e);
						}
						else {
							ret = m_CurrentALN->GetValue(m_Settings, *e);
						}
						if (ret != 0) {
							status = DLMS_ERROR_CODE_HARDWARE_FAULT;
						}
					}
					PostRead(arr);
				}
				if (status == 0)
				{
					status = e->GetError();
				}
				if (e->GetCAValue().byteArr != nullptr && e->GetCAValue().size != 0) {
					CArtVariant& value = e->GetCAValue();
					// If byte array is added do not add type.
					bb.Set(value.byteArr, value.size);
					value.Clear();
				}
				//else {
				//	CGXDLMSVariant& value = e->GetValue();
				//	if (e->IsByteArray() && value.vt == DLMS_DATA_TYPE_OCTET_STRING)
				//	{
				//		// If byte array is added do not add type.
				//		bb.Set(value.byteArr, value.GetSize());
				//	}
				//	else if ((ret = CGXDLMS::AppendData(obj, attributeIndex, bb, value)) != 0)
				//	{
				//		status = DLMS_ERROR_CODE_HARDWARE_FAULT;
				//	}
				//}	
			}
		}
	}       
    
    CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_GET_RESPONSE, 1, NULL, &bb, status);

    ret = CGXDLMS::GetLNPdu(p, m_ReplyData);
    if (m_Settings.GetCount() != m_Settings.GetIndex()
        || bb.GetSize() != bb.GetPosition())
    {
        if (m_Transaction != NULL)
        {
            delete m_Transaction;
            m_Transaction = NULL;
        }
        m_Transaction = new CGXDLMSLongTransaction(arr, DLMS_COMMAND_GET_REQUEST, bb);
    }
	else {
		if (m_Transaction != NULL) {
			delete m_Transaction;
			m_Transaction = NULL;
		}
		m_CurrentALN->GetObjectList().FreeConstructedObj();
	}
    return ret;
}

int CGXDLMSServer::GetRequestNextDataBlock(CGXByteBuffer& data)
{
    CGXByteBuffer bb;
    int ret;
    unsigned long index;
    // Get block index.
    if ((ret = data.GetUInt32(&index)) != 0)
    {
        return ret;
    }
    if (index != m_Settings.GetBlockIndex())
    {
        CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_GET_RESPONSE, 2,
            NULL, &bb,
            DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);
        return CGXDLMS::GetLNPdu(p, m_ReplyData);
    }
    else
    {
        m_Settings.IncreaseBlockIndex();
        CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_GET_RESPONSE, 2, NULL, &bb, DLMS_ERROR_CODE_OK);
        // If m_Transaction is not in progress.
        if (m_Transaction == NULL)
        {
            p.SetStatus(DLMS_ERROR_CODE_NO_LONG_GET_OR_READ_IN_PROGRESS);
        }
        else
        {
            bb.Set(&m_Transaction->GetData());
            unsigned char moreData = m_Settings.GetIndex() != m_Settings.GetCount();
            if (moreData)
            {
                // If there is multiple blocks on the buffer.
                // This might happen when Max PDU size is very small.
                if (bb.GetSize() < m_Settings.GetMaxPduSize())
                {
					CArtVariant value1;
                    for (std::vector<CGXDLMSValueEventArg*>::iterator arg = m_Transaction->GetTargets().begin();
                        arg != m_Transaction->GetTargets().end(); ++arg)
                    {
                        PreRead(m_Transaction->GetTargets());
                        if (!(*arg)->GetHandled())
                        {
							if ((*arg)->GetTarget()->GetDataValidity()) {
								if ((*arg)->GetTarget()->GetObjectType() != DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME) {
									ret = (*arg)->GetTarget()->GetValue(m_Settings, *(*arg));
								}
								else
								{
									ret = m_CurrentALN->GetValue(m_Settings, *(*arg));
								}
								if (ret != 0) {
									return ret;
								}
							}
                            std::vector<CGXDLMSValueEventArg*> arr;
                            arr.push_back(*arg);
                            PostRead(arr);
                        }

						if ((*arg)->GetCAValue().byteArr != nullptr && (*arg)->GetCAValue().size != 0) {
							value1 = (*arg)->GetCAValue();
							// If byte array is added do not add type.
							bb.Set(value1.byteArr, value1.size);
							value1.Clear();
						}
						else {

						}
						//else {
						//	value = (*arg)->GetValue();
						//	if ((*arg)->IsByteArray() && value.vt == DLMS_DATA_TYPE_OCTET_STRING)
						//	{
						//		// If byte array is added do not add type.
						//		bb.Set(value.byteArr, value.GetSize());
						//	}
						//	else if ((ret = CGXDLMS::AppendData((*arg)->GetTarget(), (*arg)->GetIndex(), bb, value)) != 0)
						//	{
						//		return DLMS_ERROR_CODE_HARDWARE_FAULT;
						//	}
						//}
                    }
                }
            }
            p.SetMultipleBlocks(true);
            ret = CGXDLMS::GetLNPdu(p, m_ReplyData);
            moreData = m_Settings.GetIndex() != m_Settings.GetCount();
            if (moreData || bb.GetSize() - bb.GetPosition() != 0)
            {
                m_Transaction->SetData(bb);
            }
            else
            {
				m_CurrentALN->GetObjectList().FreeConstructedObj();
                delete m_Transaction;
                m_Transaction = NULL;
                m_Settings.ResetBlockIndex();
            }
        }
    }
    return ret;
}

int CGXDLMSServer::GetRequestWithList(CGXByteBuffer& data)
{
    CGXDLMSValueEventCollection list;
    CGXByteBuffer bb;
    int ret;
    unsigned char attributeIndex;
    unsigned short id;
    unsigned long pos, cnt;
    if ((ret = GXHelpers::GetObjectCount(data, cnt)) != 0)
    {
        return ret;
    }
    GXHelpers::SetObjectCount(cnt, bb);
	m_CurrentALN->GetObjectList().FreeConstructedObj();
    for (pos = 0; pos != cnt; ++pos)
    {
        if ((ret = data.GetUInt16(&id)) != 0)
        {
            return ret;
        }
        DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)id;
        CGXByteBuffer ln;
        ln.Set(&data, data.GetPosition(), 6);
        if ((ret = data.GetUInt8(&attributeIndex)) != 0)
        {
            return ret;
        }
		CGXDLMSObject* obj = m_CurrentALN->GetObjectList().FindByLN(ci, ln);
        if (obj == NULL)
        {
            std::string name;
            GXHelpers::GetLogicalName(ln, name);
            obj = FindObject(ci, 0, name);
        }
        if (obj == NULL)
        {
            // Access Error : Device reports a undefined object.
            CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, attributeIndex);
            e->SetError(DLMS_ERROR_CODE_UNDEFINED_OBJECT);
            list.push_back(e);
        }
        else
        {
            // AccessSelection
            unsigned char selection, selector = 0;
            CArtVariant parameters;
            if ((ret = data.GetUInt8(&selection)) != 0)
            {
				obj = nullptr;
				m_CurrentALN->GetObjectList().FreeConstructedObj();
                return ret;
            }
            if (selection != 0)
            {
                if ((ret = data.GetUInt8(&selector)) != 0)
                {
					obj = nullptr;
					m_CurrentALN->GetObjectList().FreeConstructedObj();
                    return ret;
                }
                if ((ret = GXHelpers::GetDataCA(data, parameters)) != 0)
                {
					obj = nullptr;
					m_CurrentALN->GetObjectList().FreeConstructedObj();
                    return ret;
                }
            }
            CGXDLMSValueEventArg *arg = new CGXDLMSValueEventArg(this, obj, attributeIndex, selector, parameters);
            list.push_back(arg);
            if (GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ && GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ_WRITE)
            {
                // Read Write denied.
                arg->SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
            }
        }
		PreRead(list);
		std::vector<CGXDLMSValueEventArg*>::iterator it = list.begin();
		if (!(*it)->GetHandled())
		{
			ret = (*it)->GetTarget()->GetValue(m_Settings, *(*it));
		}
		bb.SetUInt8((*it)->GetError());

		if ((*it)->GetCAValue().byteArr != nullptr && (*it)->GetCAValue().size != 0) {
			CArtVariant value = (*it)->GetCAValue();
			// If byte array is added do not add type.
			bb.Set(value.byteArr, value.size);
			value.Clear();
		}
		else {
			obj = nullptr;
			m_CurrentALN->GetObjectList().FreeConstructedObj();
			return DLMS_ERROR_CODE_HARDWARE_FAULT;
		}

		//CGXDLMSVariant& value = (*it)->GetValue();
		//if ((*it)->IsByteArray() && value.vt == DLMS_DATA_TYPE_OCTET_STRING)
		//{
		//	// If byte array is added do not add type.
		//	bb.Set(value.byteArr, value.GetSize());
		//}
		//else if ((ret = CGXDLMS::AppendData((*it)->GetTarget(), (*it)->GetIndex(), bb, value)) != 0)
		//{
		//	obj = nullptr;
		//	m_CurrentALN->GetObjectList().FreeConstructedObj();
		//	return DLMS_ERROR_CODE_HARDWARE_FAULT;
		//}
		if (m_Settings.GetIndex() != m_Settings.GetCount())
		{
			if (m_Transaction != NULL)
			{
				delete m_Transaction;
				m_Transaction = NULL;
			}
			CGXByteBuffer empty;
			m_Transaction = new CGXDLMSLongTransaction(list, DLMS_COMMAND_GET_REQUEST, empty);
		}
		list.clear();
		obj = NULL;
		m_CurrentALN->GetObjectList().FreeConstructedObj();
    }
    CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_GET_RESPONSE, 3, NULL, &bb, 0xFF);
    return CGXDLMS::GetLNPdu(p, m_ReplyData);
}

int CGXDLMSServer::HandleGetRequest(
    CGXByteBuffer& data)
{       
    // Return error if connection is not established.
    if (!m_Settings.IsConnected())
    {
        GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
            DLMS_SERVICE_ERROR_SERVICE, DLMS_SERVICE_UNSUPPORTED,
            m_ReplyData);
        return 0;
    }
    int ret;
    unsigned char ch;
    // Get type.
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    DLMS_GET_COMMAND_TYPE type = (DLMS_GET_COMMAND_TYPE)ch;
    // Get invoke ID and priority.
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    // GetRequest normal
    if (type == DLMS_GET_COMMAND_TYPE_NORMAL)
    {
        ret = GetRequestNormal(data);       
    }
    else if (type == DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK)
    {
        // Get request for next data block
        ret = GetRequestNextDataBlock(data);
    }
    else if (type == DLMS_GET_COMMAND_TYPE_WITH_LIST)
    {
        // Get request with a list.
        ret = GetRequestWithList(data);
    }
    else
    {
        CGXByteBuffer bb;
        m_Settings.ResetBlockIndex();
        // Access Error : Device reports a hardware fault.
        bb.SetUInt8(DLMS_ERROR_CODE_HARDWARE_FAULT);
        CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_GET_RESPONSE,
			DLMS_GET_COMMAND_TYPE_NORMAL, NULL, &bb, DLMS_ERROR_CODE_INVALID_RESPONSE);
        ret = CGXDLMS::GetLNPdu(p, m_ReplyData);
    }
    return ret;
}

int CGXDLMSServer::HandleCommand(
    CGXDLMSConnectionEventArgs& connectionInfo,
    DLMS_COMMAND cmd,
    CGXByteBuffer& data,
    CGXByteBuffer& reply)
{
    int ret = 0;
    unsigned char frame = 0;    
    switch (cmd)
    {
    case DLMS_COMMAND_SET_REQUEST:
        ret = HandleSetRequest(data);
        break;
    case DLMS_COMMAND_WRITE_REQUEST:
		if (!m_Settings.IsConnected() || m_Settings.GetUseLogicalNameReferencing())
		{
			GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_WRITE,
				DLMS_SERVICE_ERROR_SERVICE,
				DLMS_SERVICE_UNSUPPORTED, m_ReplyData);
		}
        break;
    case DLMS_COMMAND_GET_REQUEST:
        if (data.GetSize() != 0)
        {            
            ret = HandleGetRequest(data);            
        }
        break;
    case DLMS_COMMAND_READ_REQUEST:
		if (!m_Settings.IsConnected() || m_Settings.GetUseLogicalNameReferencing())
		{
			GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_READ,
				DLMS_SERVICE_ERROR_SERVICE,
				DLMS_SERVICE_UNSUPPORTED, m_ReplyData);
		}
        break;
    case DLMS_COMMAND_METHOD_REQUEST:
        ret = HandleMethodRequest(data, connectionInfo);
        break;
    case DLMS_COMMAND_SNRM:        
        ret = HandleSnrmRequest(data, m_Settings, m_ReplyData);
        if(ret == 0) {
            frame = DLMS_COMMAND_UA;
            m_LinkEstablished = true;
            
        } else {
            frame = DLMS_COMMAND_DM;
        }        
        break;
    case DLMS_COMMAND_AARQ:
        if(m_LinkEstablished) {
            ret = HandleAarqRequest(data, connectionInfo);            
        } else {
            ret = DLMS_ERROR_CODE_REJECTED;
        }
        break;
    case DLMS_COMMAND_DISCONNECT_REQUEST:
    case DLMS_COMMAND_DISC:        
        if(m_LinkEstablished) {
            ret = GenerateDisconnectRequest(m_Settings, m_ReplyData);
            m_Settings.SetConnected(false);
            Disconnected(connectionInfo);
            frame = DLMS_COMMAND_UA;
            Reset(true);
            m_LinkEstablished = false;
        
        } else {
            frame = DLMS_COMMAND_DM;
        }
        break;
    case DLMS_COMMAND_NONE:
        //Get next frame.
        break;        
        
    default:  
        if((cmd & 0x0F) == HDLC_FRAME_TYPE_S_FRAME) { // RR      
            ret = HandleReadyRead(cmd, frame);
            
        } else {
            frame = DLMS_COMMAND_REJECTED;
        }
        break;
    }

    if (ret == 0)
    {
        if (m_Settings.GetInterfaceType() == DLMS_INTERFACE_TYPE_WRAPPER)
        {
            ret = CGXDLMS::GetWrapperFrame(m_Settings, m_ReplyData, reply);
        }
        else
        {
            ret = CGXDLMS::GetHdlcFrame(m_Settings, frame, &m_ReplyData, reply);
        }
    }
    return ret;
}

/**
 * Handle action request.
 *
 * @param reply
 *            Received data from the client.
 * @return Reply.
 */
int CGXDLMSServer::HandleMethodRequest(
    CGXByteBuffer& data,
    CGXDLMSConnectionEventArgs& connectionInfo)
{
    CGXByteBuffer bb;
    DLMS_ERROR_CODE error = DLMS_ERROR_CODE_OK;
    CArtVariant parameters;
    int ret;
    unsigned char ch, id;
    unsigned short tmp;
	m_CurrentALN->GetObjectList().FreeConstructedObj();
    // Get type.
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    // Get invoke ID and priority.
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    // CI
    if ((ret = data.GetUInt16(&tmp)) != 0)
    {
        return ret;
    }
    DLMS_OBJECT_TYPE ci = (DLMS_OBJECT_TYPE)tmp;
    CGXByteBuffer ln;
    ln.Set(&data, data.GetPosition(), 6);
    // Attribute
    if ((ret = data.GetUInt8(&id)) != 0)
    {
        return ret;
    }
    // Get parameters.
    if ((ret = data.GetUInt8(&ch)) != 0)
    {
        return ret;
    }

    if (ch != 0)
    {
        if ((ret = GXHelpers::GetDataCA(data, parameters)) != 0)
        {
            return ret;
        }
    }
    CGXDLMSObject* obj = m_CurrentALN->GetObjectList().FindByLN(ci, ln);
    if (obj == NULL)
    {
        std::string name;
        GXHelpers::GetLogicalName(ln, name);
        obj = FindObject(ci, 0, name);
    }
    if (obj == NULL)
    {
        error = DLMS_ERROR_CODE_UNDEFINED_OBJECT;
    }
    else
    {
        CGXDLMSValueEventArg* e = new CGXDLMSValueEventArg(this, obj, id, 0, parameters);
        CGXDLMSValueEventCollection arr;
        arr.push_back(e);
        if (GetMethodAccess(e) == DLMS_METHOD_ACCESS_MODE_NONE)
        {
            error = DLMS_ERROR_CODE_READ_WRITE_DENIED;
        }
        else
        {
            PreAction(arr);
            if (!e->GetHandled())
            {
				if (obj->GetDataValidity()) {
					if ((ret = obj->Invoke(m_Settings, *e)) != 0)
					{
						obj = nullptr;
						m_CurrentALN->GetObjectList().FreeConstructedObj();
						return ret;
					}
				}
                PostAction(arr);
            }
			if (e->GetError() != DLMS_ERROR_CODE_OK) {
				// Add parameters error code.
				error = e->GetError();
				bb.SetUInt8(0);
			}
			else {
				if (e->GetCAValue().byteArr != nullptr && e->GetCAValue().size != 0) {
					CArtVariant& value = e->GetCAValue();
					// Add return parameters
					bb.SetUInt8(1);
					//Add parameters error code.
					bb.SetUInt8(0);
					bb.Set(value.byteArr, value.size);
					value.Clear();
				}
				else {
					error = e->GetError();
					bb.SetUInt8(0);
					//CGXDLMSVariant& actionReply = e->GetValue();
					//// Set default action reply if not given.
					//if (actionReply.vt != DLMS_DATA_TYPE_NONE)
					//{
					//	// Add return parameters
					//	bb.SetUInt8(1);
					//	//Add parameters error code.
					//	bb.SetUInt8(0);
					//	if (e->IsByteArray())
					//	{
					//		bb.Set(actionReply.byteArr, actionReply.size);
					//	}
					//	else
					//	{
					//		GXHelpers::SetData(bb, actionReply.vt, actionReply);
					//	}
					//}
					//else {
					//	// Add parameters error code.
					//	error = e->GetError();
					//	bb.SetUInt8(0);
					//}
				}
			}
        }
    }
    CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_METHOD_RESPONSE, 1, NULL, &bb, error);
    ret = CGXDLMS::GetLNPdu(p, m_ReplyData);
    // If High level authentication fails.
    if (!m_Settings.IsConnected() && obj->GetObjectType() == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME && id == 1)
    {
        InvalidConnection(connectionInfo);
    } else if(m_Settings.IsConnected() && obj->GetObjectType() == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME && id == 1) {
        Connected(connectionInfo);
    }
	m_CurrentALN->GetObjectList().FreeConstructedObj();
    return ret;
}

int CGXDLMSServer::HandleReadyRead(unsigned char cmd,                                   
                                   unsigned char &frame)
{       
    if((cmd == DLMS_COMMAND_RR) && !m_Settings.IsConnected()) {
        frame = DLMS_COMMAND_RR;
        return 0;
    }
    
    if(!m_Settings.IsConnected()) {
        frame = DLMS_COMMAND_REJECTED;
        return 0;
    }
            
    unsigned char clientNR = (cmd & 0xE0) >> 5;
    unsigned char srvNS = (m_Settings.GetSenderFrame() & 0x0E) >> 1;
    srvNS = (srvNS >= 7)?0:(srvNS + 1);
    if(clientNR == srvNS) {
		if (IsLongTransaction() || m_ReplyData.GetSize() != 0) {
			frame = m_Settings.GetNextSend(0);
		}
		else {
			frame = (m_Settings.GetSenderFrame() & 0xF0) | 0x01;
		}
    } else {
        frame = DLMS_COMMAND_REJECTED;
    }
     
    return 0;
}

bool CGXDLMSServer::CheckCtlField(unsigned char ctl,
                                  CGXByteBuffer &reply)
{   
    if((ctl & 0x01) == HDLC_FRAME_TYPE_I_FRAME) { // I-frame

        unsigned char clientNS = (ctl & 0x0E) >> 1;
        unsigned char srvNR = (m_Settings.GetSenderFrame() & 0xE0) >> 5;
        if(clientNS != srvNR) {
            unsigned char frame = DLMS_COMMAND_RR;
            frame |= ((srvNR << 5) & 0xE0);
            CGXDLMS::GetHdlcFrame(m_Settings, frame, NULL, reply);
            return false;
        }

    } else if((ctl & 0x0F) == HDLC_FRAME_TYPE_S_FRAME) {    // RR                
        if(ctl == DLMS_COMMAND_RR) {
            return true;
        }
        
        unsigned char clientNR = (ctl & 0xE0) >> 5;
        unsigned char srvNS = (m_Settings.GetSenderFrame() & 0x0E) >> 1;
        srvNS = (srvNS >= 7)?0:(srvNS + 1);
        if(clientNR != srvNS) {
            CGXDLMS::GetHdlcFrame(m_Settings, DLMS_COMMAND_REJECTED, NULL, reply);
            return false;
        }
    }
    
    return true;
}

int CGXDLMSServer::HandleRequest(
    CGXByteBuffer& reply)
{   
	CGXDLMSConnectionEventArgs connectionInfo;
    int ret;        
    reply.Clear();
    if (m_ReceivedData.GetData() == NULL || m_ReceivedData.GetSize() == 0)
    {
        return 0;
    }
    if (!m_Initialized)
    {
        //Server not Initialized.
        return DLMS_ERROR_CODE_NOT_INITIALIZED;
    }
    bool first = m_Settings.GetServerAddress() == 0
        && m_Settings.GetClientAddress() == 0;
    if ((ret = CGXDLMS::GetData(m_Settings, m_ReceivedData, m_Info)) != 0)
    {
        //If all data is not received yet.
        if (ret == DLMS_ERROR_CODE_FALSE)
        {
            ret = 0;
        }
		else {
			m_ReceivedData.Clear();
			m_Info.Clear();
		}
        return ret;
    }
    // If all data is not received yet.
    if (!m_Info.IsComplete())
    {
        return 0;
    }
    m_ReceivedData.Clear();

    if (first)
    {
        // Check is data send to this server.
        if (!IsTarget(m_Settings.GetServerAddress(), m_Settings.GetClientAddress()))
        {
            m_Info.Clear();
            return 0;
        }
    }    
    
    // If client want next frame.
    if ((m_Info.GetMoreData() & DLMS_DATA_REQUEST_TYPES_FRAME) == DLMS_DATA_REQUEST_TYPES_FRAME)
    {
        return CGXDLMS::GetHdlcFrame(m_Settings, m_Settings.GetReceiverReady(), &m_ReplyData, reply);
    }
    // Update command if m_Transaction and next frame is asked.
    if (m_Info.GetCommand() == DLMS_COMMAND_NONE)
    {
        if (m_Transaction != NULL)
        {
            m_Info.SetCommand(m_Transaction->GetCommand());
        }
    }
    
    // 
    if(!CheckCtlField(m_Info.GetControlField(), reply)) {
        m_Info.Clear();
        return 0;
    }
        
    ret = HandleCommand(connectionInfo, m_Info.GetCommand(), m_Info.GetData(), reply);
    m_Info.Clear();
    return ret;
}

/**
* Server will tell what functionality is available for the client.
* @return Available functionality.
*/
DLMS_CONFORMANCE CGXDLMSServer::GetConformance()
{
    return m_Settings.GetProposedConformance();
}

/**
* Server will tell what functionality is available for the client.
*
* @param value
*            Available functionality.
*/
void CGXDLMSServer::SetConformance(DLMS_CONFORMANCE value)
{
    m_Settings.SetProposedConformance(value);
}