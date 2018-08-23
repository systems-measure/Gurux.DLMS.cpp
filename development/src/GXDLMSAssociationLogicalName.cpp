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
#include "prj_defines.h"

#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSServer.h"
#include "../include/GXSecure.h"

#include "converter_mpro\converter_mpro.h"
#include "memory\memory_srv.h"

void SecureHLS_Psw(CGXDLMSSettings& settings, CGXByteBuffer& secured) {
	CGXByteBuffer hls_psw;
    uint8_t	HLSSecret_read[64];
    mem::rd_ext_mem(HLSSecret_read, GetAddr(HLSSecret), sizeof(HLSSecret_read));
	hls_psw.Set(HLSSecret_read, strlen((const char*)HLSSecret_read));
	CGXSecure::Secure(settings, hls_psw, HLSSecret_read, secured);
	if (secured.GetSize() != 0) {
		if (secured.Capacity() < secured.GetSize() + 2) {
			secured.Capacity(secured.GetSize() + 2);
		}
		secured.SetSize(secured.GetSize() + 2);
		secured.Move(0, 2, secured.GetSize() - 2);
		secured.SetUInt8(0, DLMS_DATA_TYPE_OCTET_STRING);
		secured.SetUInt8(1, secured.GetSize() - 2);
	}
}

void CGXDLMSAssociationLogicalName::Init()
{
    m_AssociationStatus = DLMS_DLMS_ASSOCIATION_STATUS_NON_ASSOCIATED;
}

void CGXDLMSAssociationLogicalName::GetAccessRights(CGXDLMSObject* pItem, CGXDLMSServer* server, CGXByteBuffer& data)
{
    int8_t cnt = (int8_t)pItem->GetAttributeCount();
    data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
    data.SetUInt8(2);
    data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    GXHelpers::SetObjectCount(cnt, data);
    CGXDLMSValueEventArg e(server, pItem, 0);
	int8_t index, access;
    for (int8_t pos = 0; pos != cnt; ++pos)
    {
        e.SetIndex(pos + 1);
        index = pos + 1;
        if (server != NULL)
        {
            access = server->GetAttributeAccess(&e);
        }
        else
        {
            access = DLMS_ACCESS_MODE_READ_WRITE;
        }
        //attribute_access_item
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(3);
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(index);
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(access);
		data.SetUInt8(DLMS_DATA_TYPE_NONE);
    }
    cnt = pItem->GetMethodCount();
    data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    GXHelpers::SetObjectCount(cnt, data);
    for (int8_t pos = 0; pos != cnt; ++pos)
    {
        e.SetIndex(pos + 1);
        index = pos + 1;
        if (server != NULL)
        {
            access = server->GetMethodAccess(&e);
        }
        else
        {
            access = DLMS_METHOD_ACCESS_MODE_ACCESS;
        }
        //attribute_access_item
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(2);
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(index);
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(access);
    }
}

// Returns LN Association View.
int CGXDLMSAssociationLogicalName::GetObjects(
    CGXDLMSSettings& settings,
    CGXDLMSValueEventArg& e,
    CGXByteBuffer& data)
{
    //Add count only for first time.
	e.SetTargetName();
    if (settings.GetIndex() == 0)
    {
		m_pos = 0;
		settings.SetCount((unsigned short)m_ObjectList.size() + 1);
		const unsigned char reader_ln[] = { 0x00, 0x00, 0x28, 0x00, 0x02, 0xFF };
		if(memcmp(e.GetTargetName(), reader_ln,6) == 0 && settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH){
			settings.SetCount(settings.GetCount() - 1);
			m_pos = 1;
		}
		data.Reserve(settings.GetMaxPduSize() + 10);
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers::SetObjectCount((unsigned long)settings.GetCount(), data);
    }
	m_ObjectList.FreeConstructedObj();
	CGXDLMSObject* tmp_obj = nullptr;
	if (m_pos < m_ObjectList.size()) {
		data.Reserve(settings.GetMaxPduSize() + 10);
		for (uint8_t i = m_pos; i < m_ObjectList.size(); ++i)
		{
			++m_pos;
			tmp_obj = m_ObjectList.MakeByPosition(i);
			if (tmp_obj != nullptr && m_pos < settings.GetCount()) {
				data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
				data.SetUInt8(4);//Count
				data.SetUInt8(DLMS_DATA_TYPE_UINT16);
				data.SetUInt16(tmp_obj->GetObjectType());//ClassID
				data.SetUInt8(DLMS_DATA_TYPE_UINT8);
				data.SetUInt8(tmp_obj->GetVersion());//Version
				data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
				data.SetUInt8(0x06);
				data.Set(tmp_obj->m_LN, 6);//LN
				//Access rights.
				GetAccessRights(tmp_obj, e.GetServer(), data);
				settings.SetIndex(settings.GetIndex() + 1);
				//If PDU is full.
				if (!e.GetSkipMaxPduSize() && data.GetSize() >= settings.GetMaxPduSize())
				{
					m_ObjectList.FreeConstructedObj();
					tmp_obj = nullptr;
					return DLMS_ERROR_CODE_OK;
				}
			}
			m_ObjectList.FreeConstructedObj();
			tmp_obj = nullptr;
		}
	}
	if (data.GetSize() < settings.GetMaxPduSize() || e.GetSkipMaxPduSize())
	{
		if (settings.GetIndex() < settings.GetCount())
		{
			data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
			data.SetUInt8(4);//Count
			data.SetUInt8(DLMS_DATA_TYPE_UINT16);
			data.SetUInt16(m_ObjectList.GetCurALN()->GetObjectType());//ClassID
			data.SetUInt8(DLMS_DATA_TYPE_UINT8);
			data.SetUInt8(m_ObjectList.GetCurALN()->GetVersion());//Version
			data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
			data.SetUInt8(0x06);
			data.Set(m_ObjectList.GetCurALN()->m_LN, 6);//LN
			//Access rights.
			GetAccessRights(m_ObjectList.GetCurALN(), e.GetServer(), data);
			settings.SetIndex(settings.GetCount());
			e.SetHandled(true);
			++m_pos;
		}
	}
	return DLMS_ERROR_CODE_OK;
}

/**
 Constructor.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName() : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, "0.0.40.0.0.255")
{
    Init();
}

/**
 Constructor.
 @param ln Logical Name of the object.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, ln)
{
    Init();
}

CGXDLMSObjectCollection& CGXDLMSAssociationLogicalName::GetObjectList()
{
    return m_ObjectList;
}

unsigned char CGXDLMSAssociationLogicalName::GetClientSAP()
{
    return m_ClientSAP;
}
void CGXDLMSAssociationLogicalName::SetClientSAP(unsigned char value)
{
    m_ClientSAP = value;
}

unsigned short CGXDLMSAssociationLogicalName::GetServerSAP()
{
    return m_ServerSAP;
}

void CGXDLMSAssociationLogicalName::SetServerSAP(unsigned short value)
{
    m_ServerSAP = value;
}

CGXApplicationContextName CGXDLMSAssociationLogicalName::GetApplicationContextName()
{
    return m_ApplicationContextName;
}

CGXDLMSContextType CGXDLMSAssociationLogicalName::GetXDLMSContextInfo()
{
    return m_XDLMSContextInfo;
}

CGXAuthenticationMechanismName CGXDLMSAssociationLogicalName::GetAuthenticationMechanismMame()
{
    return m_AuthenticationMechanismName;
}

void CGXDLMSAssociationLogicalName::GetSecret(CGXByteBuffer& lls)
{
    uint8_t	LLSSecret_read[64];
    mem::rd_ext_mem(LLSSecret_read, GetAddr(LLSSecret), sizeof(LLSSecret_read));
	uint8_t size_str = strlen((const char*)LLSSecret_read);
	lls.Set(LLSSecret_read, size_str);
}
void CGXDLMSAssociationLogicalName::SetSecret(CGXByteBuffer& value)
{
	value.SetUInt8('\0');
    mem::wr_ext_mem(GetAddr(LLSSecret), value.GetData(), value.GetSize());
}

DLMS_DLMS_ASSOCIATION_STATUS CGXDLMSAssociationLogicalName::GetAssociationStatus()
{
    return m_AssociationStatus;
}

void CGXDLMSAssociationLogicalName::SetAssociationStatus(DLMS_DLMS_ASSOCIATION_STATUS value)
{
    m_AssociationStatus = value;
}

std::string CGXDLMSAssociationLogicalName::GetSecuritySetupReference()
{
    return m_SecuritySetupReference;
}
void CGXDLMSAssociationLogicalName::SetSecuritySetupReference(std::string value)
{
    m_SecuritySetupReference = value;
}

// Returns amount of attributes.
int CGXDLMSAssociationLogicalName::GetAttributeCount()
{
    //Security Setup Reference is from version 1.
    if (GetVersion() > 0)
        return 9;
    return 8;
}

// Returns amount of methods.
int CGXDLMSAssociationLogicalName::GetMethodCount()
{
    return 4;
}

int CGXDLMSAssociationLogicalName::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSAssociationLogicalName::GetDataType(signed char index) {
	if (index == 1)
	{
		return  DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 2)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 3)
	{
		return DLMS_DATA_TYPE_STRUCTURE;
	}
	if (index == 4)
	{
		return DLMS_DATA_TYPE_STRUCTURE;
	}
	if (index == 5)
	{
		return DLMS_DATA_TYPE_STRUCTURE;
	}
	if (index == 6)
	{
		return DLMS_DATA_TYPE_STRUCTURE;
	}
	if (index == 7)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 8)
	{
		return DLMS_DATA_TYPE_ENUM;
	}
	if (index == 9)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	return DLMS_DATA_TYPE_NONE;
}

int CGXDLMSAssociationLogicalName::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    uint8_t	HLSSecret_read[64];
    mem::rd_ext_mem(HLSSecret_read, GetAddr(HLSSecret), sizeof(HLSSecret_read));
    // Check reply_to_HLS_authentication
    if (e.GetIndex() == 1)
    {
		VarInfo v_info;
		e.GetParameters().GetVar(v_info);
		int ret;
        CGXByteBuffer serverChallenge;
		if ((ret = CGXSecure::Secure(settings, settings.GetStoCChallenge(), HLSSecret_read, serverChallenge)) != 0)
        {
            return ret;
        }
        if (serverChallenge.Compare(e.GetParameters().GetCurPtr(), v_info.size))
        {
            if ((ret = CGXSecure::Secure(settings, settings.GetCtoSChallenge(), HLSSecret_read, serverChallenge)) != 0)
            {
                return ret;
            }
			if (serverChallenge.GetSize() + 2 > serverChallenge.Capacity()) {
				serverChallenge.Capacity(serverChallenge.GetSize() + 2);
			}
			serverChallenge.SetSize(serverChallenge.GetSize() + 2);
			serverChallenge.Move(0, 2, serverChallenge.GetSize() - 2);
			serverChallenge.SetUInt8(0, DLMS_DATA_TYPE_OCTET_STRING);
			serverChallenge.SetUInt8(1, serverChallenge.GetSize() - 2);
            e.SetValue(serverChallenge);
            settings.SetConnected(true);
        }
        else
        {
            settings.SetConnected(false);
			e.SetError(DLMS_ERROR_CODE_OTHER_REASON);
        }
		return 0;
    }
	if (e.GetIndex() == 2) {
		CGXByteBuffer decrypted;
		VarInfo v_info;
		e.GetParameters().GetVar(v_info);
		if (v_info.size > 16) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		CGXSecure::UnSecure(settings, e.GetParameters().GetCurPtr(), v_info.size, decrypted);
		decrypted.SetUInt8('\0');
		if (strcmp((const char*)HLSSecret_read, (const char*)decrypted.GetData()) != 0) {
			CGXCipher::SetRoundKeysState(false);
			mem::wr_ext_mem(GetAddr(HLSSecret), decrypted.GetData(), strlen((const char*)decrypted.GetData()) + 1);
		}
		e.GetServer()->Configurated();
		e.GetServer()->FixateCorrectDataEvent(14);
		return 0;
	}
    else
    {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    }
    return 0;
}

void CGXDLMSAssociationLogicalName::GetContextInfo(CGXByteBuffer& data) {
	CGXByteBuffer info = m_XDLMSContextInfo.GetCypheringInfo();
	data.Reserve(16 + info.GetSize());
	data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
	data.SetUInt8(6);
	data.SetUInt8(DLMS_DATA_TYPE_BIT_STRING);
	uint32_t tmp = m_XDLMSContextInfo.GetConformance();
	GXHelpers::SetObjectCount(24, data);
	data.SetUInt8((tmp >> 16) & 0xFF);
	data.SetUInt8((tmp >> 8) & 0xFF);
	data.SetUInt8(tmp & 0xFF);
	data.SetUInt8(DLMS_DATA_TYPE_UINT16);
	data.SetUInt8(m_XDLMSContextInfo.GetMaxPduSize());
	data.SetUInt8(DLMS_DATA_TYPE_UINT16);
	data.SetUInt8(m_XDLMSContextInfo.GetMaxSendPduSize());
	data.SetUInt8(DLMS_DATA_TYPE_UINT8);
	data.SetUInt8(m_XDLMSContextInfo.GetDlmsVersionNumber());
	data.SetUInt8(DLMS_DATA_TYPE_INT8);
	data.SetUInt8(m_XDLMSContextInfo.GetQualityOfService());
	data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
	GXHelpers::SetObjectCount(info.GetSize(), data);
	data.Set(info.GetData(), info.GetSize());
}

int CGXDLMSAssociationLogicalName::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret;
	CGXByteBuffer data;
	if (e.GetIndex() == 1)
    {
		data.Reserve(6);
		if ((ret = GetLogicalName(e.GetTarget(), data)) != 0)
        {
            return ret;
        }
        e.SetValue(data);
		e.SetHandled(true);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
        ret = GetObjects(settings, e, data);
		e.SetValue(data);
        return ret;
    }
    if (e.GetIndex() == 3)
    {
		data.Reserve(7);
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        //Add count
        data.SetUInt8(2);
        data.SetUInt8(DLMS_DATA_TYPE_UINT8);
        data.SetUInt8(m_ClientSAP);
        data.SetUInt8(DLMS_DATA_TYPE_UINT16);
        data.SetUInt16(m_ServerSAP);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {

		data.Reserve(17);
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        data.SetUInt8(0x7);
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetJointIsoCtt());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetCountry());
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_ApplicationContextName.GetCountryName());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetIdentifiedOrganization());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetDlmsUA());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetApplicationContext());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetContextId());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 5)
    {
		GetContextInfo(data);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 6)
    {
		data.Reserve(17);
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        data.SetUInt8(0x7);
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetJointIsoCtt());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetCountry());
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_AuthenticationMechanismName.GetCountryName());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetIdentifiedOrganization());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetDlmsUA());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetAuthenticationMechanismName());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetMechanismId());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 7)
	{
		data.Reserve(66);
		uint8_t size_str = 0;
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		if (e.GetTarget()->GetName().compare("0.0.40.0.0.255") == 0) {
			if (settings.GetAuthentication() == DLMS_AUTHENTICATION_LOW) {
                uint8_t	LLSSecret_read[64];
                mem::rd_ext_mem(LLSSecret_read, GetAddr(LLSSecret), sizeof(LLSSecret_read));
				size_str = strlen((const char*)LLSSecret_read);
				GXHelpers::SetObjectCount(size_str, data);
				data.Set(LLSSecret_read, size_str);
			}
			else {
				if (settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH) {
					SecureHLS_Psw(settings, data);
					if (data.GetSize() == 0) {
						return DLMS_ERROR_CODE_HARDWARE_FAULT;
					}
				}
			}
		}
		else {
			if (e.GetTarget()->GetName().compare("0.0.40.0.2.255") == 0) {
                uint8_t	LLSSecret_read[64];
                mem::rd_ext_mem(LLSSecret_read, GetAddr(LLSSecret), sizeof(LLSSecret_read));
				size_str = strlen((const char*)LLSSecret_read);
				GXHelpers::SetObjectCount(size_str, data);
				data.Set(LLSSecret_read, size_str);
			}
			else {
				SecureHLS_Psw(settings, data);
				if (data.GetSize() == 0) {
					return DLMS_ERROR_CODE_HARDWARE_FAULT;
				}
			}
		}
		e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 8)
    {
		data.Reserve(2);
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8((unsigned char)m_AssociationStatus);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 9)
    {
		data.Reserve(8);
        unsigned char tmp[6];
		GXHelpers::SetLogicalName(m_SecuritySetupReference.c_str(), tmp);
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(6);
		data.Set(tmp, 6);
        e.SetValue(data);
		return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSAssociationLogicalName::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
    }
    else if (e.GetIndex() == 3)
    {
    }
    else if (e.GetIndex() == 4)
    {
    }
    else if (e.GetIndex() == 5)
    {
    }
    else if (e.GetIndex() == 6)
    {
    }
    else if (e.GetIndex() == 7)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		e.GetCAValue().SetUInt8('\0');
        mem::wr_ext_mem(GetAddr(LLSSecret), e.GetCAValue().GetCurPtr(), v_info.size + 1);
		e.GetServer()->Configurated();
		e.GetServer()->FixateCorrectDataEvent(13);
    }
    else if (e.GetIndex() == 8)
    {
    }
    else if (e.GetIndex() == 9)
    {
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
