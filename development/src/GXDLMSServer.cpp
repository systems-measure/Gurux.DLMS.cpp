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
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXAPDU.h"
#include "../include/GXSecure.h"
#include "../include/GXDLMSValueEventCollection.h"

CGXDLMSServer::CGXDLMSServer() :  m_Settings(), m_LinkEstablished(false)
{
   	m_CurrentALN = new CGXDLMSAssociationLogicalName("0.0.40.0.0.255");
	m_Transaction = new CGXDLMSLongTransaction();
	m_Settings.SetProposedConformance((DLMS_CONFORMANCE)(DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_ACTION |
            DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_SET_OR_WRITE |
            DLMS_CONFORMANCE_BLOCK_TRANSFER_WITH_GET_OR_READ |
            DLMS_CONFORMANCE_SET | DLMS_CONFORMANCE_SELECTIVE_ACCESS |
            DLMS_CONFORMANCE_ACTION | DLMS_CONFORMANCE_MULTIPLE_REFERENCES |
            DLMS_CONFORMANCE_GET | DLMS_CONFORMANCE_GENERAL_PROTECTION));
    Reset();
}

CGXDLMSServer::~CGXDLMSServer()
{
	if (m_CurrentALN != nullptr)
		delete m_CurrentALN;
	if (m_Transaction != nullptr)
		delete m_Transaction;
}

CGXDLMSObjectCollection*& CGXDLMSServer::GetItems()
{
    return m_Settings.GetObjects();
}

CGXDLMSSettings& CGXDLMSServer::GetSettings()
{
    return m_Settings;
}

CGXDLMSAssociationLogicalName* CGXDLMSServer::GetCurrentALN() {
	return m_CurrentALN;
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

bool CGXDLMSServer::IsLongTransaction() {
	return (m_Transaction->GetCommand() != DLMS_COMMAND_NONE);
}

int CGXDLMSServer::Initialize() {
	m_Settings.GetLimits().SetWindowSizeRX(1);
	m_Settings.GetLimits().SetWindowSizeTX(1);
	m_Settings.GetLimits().SetMaxInfoRX(300);
	m_Settings.GetLimits().SetMaxInfoTX(300);

	uint8_t ln[6];
  const uint8_t empty[sizeof(ln)] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	CGXDLMSObject* tmp_obj = nullptr;
	for (uint16_t i = 0; i < GetItems()->size(); ++i) {
    memset(ln, 0x00, sizeof(ln));
		tmp_obj = GetItems()->MakeByPosition(i);
		if (tmp_obj != nullptr) {
			tmp_obj->GetLogicalName(ln);
			if (memcmp(ln, empty, sizeof(ln)) == 0) {
				//Invalid Logical Name.
				tmp_obj = nullptr;
				GetItems()->FreeConstructedObj();
				return DLMS_ERROR_CODE_INVALID_LOGICAL_NAME;
			}
			tmp_obj = nullptr;
			GetItems()->FreeConstructedObj();
		}
	}
  memset(ln, 0x00, sizeof(ln));
  m_CurrentALN->GetLogicalName(ln);
	if(memcmp(ln, empty, sizeof(ln)) == 0) {
			//Invalid Logical Name.
			return DLMS_ERROR_CODE_INVALID_LOGICAL_NAME;
		}
    return 0;
}

void CGXDLMSServer::Reset(bool connected)
{
	m_Transaction->Clear();
	m_Settings.SetCount(0);
	m_Settings.SetIndex(0);
	if (m_Settings.IsConnected()) {
		Disconnected();
		m_Settings.SetConnected(false);
	}
	m_RxTxData.Clear(false);
	m_ReplyData.Clear();
	if (!connected)
	{
		m_Info.Clear();
		m_Settings.SetServerAddress(0);
		m_Settings.SetClientAddress(0);
		m_Settings.ResetFrameSequence();
		m_LinkEstablished = false;
	}

	m_Settings.SetAuthentication(DLMS_AUTHENTICATION_NONE);
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
int CGXDLMSServer::HandleAarqRequest(CGXByteBuffer& data)
{
	int ret;
	DLMS_ASSOCIATION_RESULT result = DLMS_ASSOCIATION_RESULT_ACCEPTED;
	m_Settings.GetCtoSChallenge().Clear();
	m_Settings.GetStoCChallenge().Clear();
	DLMS_SOURCE_DIAGNOSTIC diagnostic;
	Reset(true);
	ret = CGXAPDU::ParsePDU(m_Settings, data, diagnostic);
	if (ret == DLMS_ERROR_CODE_INVALID_TAG || ret == DLMS_ERROR_CODE_OUTOFMEMORY || ret == DLMS_ERROR_CODE_INVALID_PARAMETER)
	{
		diagnostic = DLMS_SOURCE_DIAGNOSTIC_NOT_SUPPORTED;
	}
	if (diagnostic == DLMS_SOURCE_DIAGNOSTIC_NONE)
	{
		diagnostic = ValidateAuthentication(m_Settings.GetAuthentication(), m_Settings.GetPassword());
		if (diagnostic == DLMS_SOURCE_DIAGNOSTIC_NONE)
		{
			if (m_Settings.GetAuthentication() > DLMS_AUTHENTICATION_LOW)
			{
				// If High authentication is used.
				CGXByteBuffer challenge;
				if ((ret = CGXSecure::GenerateChallenge(challenge)) != 0)
				{
					return ret;
				}
				m_Settings.SetStoCChallenge(challenge);
				result = DLMS_ASSOCIATION_RESULT_ACCEPTED;
				diagnostic = DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED;
			}
			else
			{
				Connected();
				m_Settings.SetConnected(true);
			}
		}
	}
	if (diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE && diagnostic != DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED)
	{
		result = DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED;
		InvalidConnection();
	}
	m_ReplyData.Set(LLC_REPLY_BYTES, 3);
	// Generate AARE packet.
	CGXAPDU::GenerateAARE(m_Settings, m_ReplyData, result, diagnostic);
	return 0;
}

/**
 * Parse SNRM Request. If server do not accept client empty byte array is
 * returned.
 *
 * @return Returns returned UA packet.
 */
typedef void(*setLimitsInfo)(uint32_t val, CGXDLMSLimits& lms);

void SetMaxLimitInfoRX(uint32_t value, CGXDLMSLimits& lms) {
	if (value < lms.GetMaxInfoRX())
		lms.SetMaxInfoRX(value);
}

void SetMaxLimitInfoTX(uint32_t value, CGXDLMSLimits& lms) {
	if (value < lms.GetMaxInfoTX())
		lms.SetMaxInfoTX(value);
}

void SetLimitWindowSizeRX(uint32_t value, CGXDLMSLimits& lms) {
	if (value < lms.GetWindowSizeRX())
		lms.SetWindowSizeRX(value);
}

void SetLimitWindowSizeTX(uint32_t value, CGXDLMSLimits& lms) {
	if (value < lms.GetWindowSizeTX())
		lms.SetWindowSizeTX(value);
}

const tabFunc<setLimitsInfo> snrm_set_limits_func[] = {
	{ HDLC_INFO_MAX_INFO_TX,       SetMaxLimitInfoRX },
    { HDLC_INFO_MAX_INFO_RX,       SetMaxLimitInfoTX },
    { HDLC_INFO_WINDOW_SIZE_TX, SetLimitWindowSizeRX },
    { HDLC_INFO_WINDOW_SIZE_RX, SetLimitWindowSizeTX }
};

unsigned char ParseSNRM(CGXByteBuffer& data, CGXDLMSLimits& lms) {
	if (data.GetSize() == 0) {
		lms.SetDefaultLimits();
		return 0;
	}
	else {
		unsigned char ch, id, len, ret;
		unsigned int value = 0;
		unsigned char fl = 0x0F;
		if ((ret = data.GetUInt16((unsigned short*)&value)) != 0)
		{
			return ret;
		}
		if ((ret = data.GetUInt8(&ch)) != 0)
		{
			return ret;
		}
		if (value != 0x8180 || ch != data.GetSize() - data.GetPosition()) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
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
				ret = data.GetUInt8((unsigned char*)&value);
				break;
			case 2:
				ret = data.GetUInt16((unsigned short*)&value);
				break;
			case 4:
				ret = data.GetUInt32((unsigned long*)&value);
				break;
			default:
				return DLMS_ERROR_CODE_INVALID_PARAMETER;
			}
			if (ret != 0)
			{
				return ret;
			}
			if (id >= HDLC_INFO_MAX_INFO_TX && id <= HDLC_INFO_WINDOW_SIZE_RX) {
				snrm_set_limits_func[id - HDLC_INFO_MAX_INFO_TX].execute_func(value, lms);
				fl &= ~(0x01 << (id - HDLC_INFO_MAX_INFO_TX));
			}
			else {
				return DLMS_ERROR_CODE_INVALID_PARAMETER;
			}

		}
		id = HDLC_INFO_MAX_INFO_TX;
		while (fl != 0x00) {
			if (fl & 0x01) {
				snrm_set_limits_func[id - HDLC_INFO_MAX_INFO_TX].execute_func(lms.defLimits[id - HDLC_INFO_MAX_INFO_TX], lms);
			}
			++id;
			fl = (fl >> 1) & 0x0F;
		}
		return 0;
	}
}

const uint8_t snrm_res_tmpl[] = { 0x81, 0x80, 0x14,                                       // FromatID, GroupID, Length
                                  HDLC_INFO_MAX_INFO_TX, 0x02, 0x00, 0x00,
                                  HDLC_INFO_MAX_INFO_RX, 0x02, 0x00, 0x00,
                                  HDLC_INFO_WINDOW_SIZE_TX, 0x04, 0x00, 0x00, 0x00, 0x00,
                                  HDLC_INFO_WINDOW_SIZE_RX, 0x04, 0x00, 0x00, 0x00, 0x00
};

int CGXDLMSServer::HandleSnrmRequest(CGXByteBuffer& data)
{
	m_Settings.GetLimits().SetWindowSizeRX(1);
	m_Settings.GetLimits().SetWindowSizeTX(1);
	m_Settings.GetLimits().SetMaxInfoRX(300);
	m_Settings.GetLimits().SetMaxInfoTX(300);
    Reset(true);
	m_LinkEstablished = false;
	unsigned char ret = ParseSNRM(data, GetLimits());
	if (ret != 0) {
		return ret;
	}
	m_ReplyData.Set(snrm_res_tmpl, sizeof(snrm_res_tmpl));
	m_ReplyData.SetUInt16(5, GetLimits().GetMaxInfoTX());
	m_ReplyData.SetUInt16(9, GetLimits().GetMaxInfoRX());
	m_ReplyData.SetUInt32(13,GetLimits().GetWindowSizeTX());
	m_ReplyData.SetUInt32(19,GetLimits().GetWindowSizeRX());
    return 0;
}

CGXDLMSValueEventArg* CGXDLMSServer::GetObjectInfoFromRequest(CGXByteBuffer& data, CGXDLMSLNParameters& p) {
	p.SetStatus(DLMS_ERROR_CODE_OK);
	m_CurrentALN->GetObjectList().FreeConstructedObj();
	CGXDLMSValueEventArg* e = nullptr;
	uint16_t obj_type = 0;
	uint8_t ln[6];
	uint8_t index = 0;
	unsigned char selector = 0;
	if (data.GetUInt16(&obj_type) != 0) {
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return e;
	}
	if (data.Get(ln, sizeof(ln)) != 0) {
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return e;
	}
	// Attribute Id
	if (data.GetUInt8(&index) != 0)
	{
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return e;
	}
	// Access selection
	if (data.GetUInt8(&selector) != 0)
	{
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return e;
	}
	CGXDLMSObject* obj = m_CurrentALN->GetObjectList().FindByLN(ln);
	e = new CGXDLMSValueEventArg(obj, index);
	e->SetSelector(selector);
	if (obj == nullptr)
	{
		// "Access Error : Device reports a undefined object."
		e->SetError(DLMS_ERROR_CODE_UNDEFINED_OBJECT);
		return e;
	}
	if ((DLMS_OBJECT_TYPE)obj_type != obj->GetObjectType()) {
		m_CurrentALN->GetObjectList().FreeConstructedObj();
		e->SetError(DLMS_ERROR_CODE_INCONSISTENT_OBJECT);
	}
	return e;
}

void CGXDLMSServer::BeforeReturn(CGXDLMSValueEventArg* arg, bool long_trns_clear) {
	if (long_trns_clear ) {
		m_Transaction->Clear();
	}
	if (arg != nullptr) {
		delete arg;
	}
	m_CurrentALN->GetObjectList().FreeConstructedObj();
}

unsigned char FindEndOfValue(CGXByteBuffer& data) {
	unsigned char ch;
	if (data.GetUInt8(&ch) != 0) {
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	int8_t size_val = spodesSizeof((DLMS_DATA_TYPE)ch);
	if (size_val == -2) {
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if (size_val != -1 && (data.GetPosition() + size_val <= data.GetSize())) {
		data.SetPosition(data.GetPosition() + size_val);
		return DLMS_ERROR_CODE_OK;
	}
	else {
		unsigned long size_arr = 0;
		if (GXHelpers::GetObjectCount(data, size_arr) != 0) {
			return DLMS_ERROR_CODE_OUTOFMEMORY;
		}
		if (ch != DLMS_DATA_TYPE_ARRAY && ch != DLMS_DATA_TYPE_STRUCTURE
			&& (data.GetPosition() + size_arr <= data.GetSize())) {
			data.SetPosition(data.GetPosition() + size_arr);
			return DLMS_ERROR_CODE_OK;
		}
		while (size_arr--) {
			ch = FindEndOfValue(data);
			if (ch != DLMS_ERROR_CODE_OK) {
				return ch;
			}
		}
		return DLMS_ERROR_CODE_OK;
	}
}

void CGXDLMSServer::GetParametersFromRequest(CGXByteBuffer& data, CGXDLMSLNParameters& p, CGXDLMSValueEventArg* arg) {
	if (arg->GetSelector()) {
		if (p.GetCommand() != DLMS_COMMAND_METHOD_RESPONSE) {
			unsigned char selector = 0;
			if (data.GetUInt8(&selector) != 0) {
				p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
				return;
			}
			arg->SetSelector(selector);
		}
		unsigned short start_pos = data.GetPosition();
		CArtVariant parameters;
		if (FindEndOfValue(data) != 0) {
			p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
			return;
		}
		parameters.Set(data.GetData() + start_pos, data.GetPosition() - start_pos);
		arg->SetParameters(parameters);
	}
}

void CGXDLMSServer::GetValueFromRequest(CGXByteBuffer& data, CGXDLMSValueEventArg* arg) {
	CArtVariant value;
	GXHelpers::GetDataCA(data, value);
	arg->SetValue(value);
}

bool CGXDLMSServer::CheckValueType(CGXDLMSLNParameters& p, CGXDLMSValueEventArg* arg) {
	VarInfo v_info;
	arg->GetCAValue().GetVar(v_info);
	if (v_info.vt == DLMS_DATA_TYPE_NONE) {
		p.SetStatus(DLMS_ERROR_CODE_READ_WRITE_DENIED);
		return false;
	}
	if (v_info.vt == DLMS_DATA_TYPE_OCTET_STRING) {
		DLMS_DATA_TYPE dt;
		if (arg->GetTarget()->GetDataType(arg->GetIndex(), dt) != 0) {
			p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
			return false;
		}
		if (dt != DLMS_DATA_TYPE_NONE && dt != DLMS_DATA_TYPE_OCTET_STRING)	{
			CArtVariant tmp;
			if (arg->GetCAValue().ChangeType(v_info.size, dt, tmp) != 0) {
				p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
				return false;
			}
			arg->GetCAValue() = tmp;
		}
	}
	arg->GetCAValue().position = 0;
	return true;
}

void CGXDLMSServer::GetSetRequestBlockIndex(CGXByteBuffer& data, CGXDLMSLNParameters& p) {
	unsigned char ch = 0;
	unsigned long size, blockNumber;
	if (data.GetUInt8(&ch) != 0) {
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return;
	}
	p.SetMultipleBlocks(ch == 0);
	p.SetLastBlock(ch == 1);
	if (data.GetUInt32(&blockNumber) != 0) {
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return;
	}
	if (blockNumber != m_Settings.GetBlockIndex()) {
		p.SetStatus(DLMS_ERROR_CODE_DATA_BLOCK_NUMBER_INVALID);
		return;
	}
	m_Settings.IncreaseBlockIndex();
	p.SetStatus(GXHelpers::GetObjectCount(data, size));
	if ((p.GetStatus() == DLMS_ERROR_CODE_OK) &&
		(size != data.GetSize() - data.GetPosition())) {

		p.SetStatus(DLMS_ERROR_CODE_BLOCK_UNAVAILABLE);
		return;
	}
	if (p.IsLastBlock())
		p.SetRequestType(DLMS_SET_RESPONSE_TYPE_LAST_DATA_BLOCK);
	else
		p.SetRequestType(DLMS_SET_RESPONSE_TYPE_DATA_BLOCK);
}

void CGXDLMSServer::HandleSetRequestNormalAndFirstDataBlock( CGXByteBuffer& data, CGXDLMSLNParameters& p) {

	ClearLastLTInfo(p);

	CGXDLMSValueEventArg* arg = GetObjectInfoFromRequest(data, p);
	if (arg != nullptr && arg->GetError() != DLMS_ERROR_CODE_OK) {
		p.SetStatus(arg->GetError());
	}
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	GetParametersFromRequest(data, p, arg);
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	if (p.GetRequestType() == 2) {
		GetSetRequestBlockIndex(data, p);
	}
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	if (GetAttributeAccess(arg) != DLMS_ACCESS_MODE_WRITE && GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ_WRITE) {
		p.SetStatus(DLMS_ERROR_CODE_READ_WRITE_DENIED);
		BeforeReturn(arg, false);
		return;
	}
	if (p.IsMultipleBlocks()) {
		m_Transaction->SetLongTransactionEvent(arg, DLMS_COMMAND_SET_REQUEST, DLMS_SET_COMMAND_TYPE_WITH_DATABLOCK, data);
		arg = nullptr;
		return;
	}
	GetValueFromRequest(data, arg);
	if (CheckValueType(p, arg)) {
		PreWrite(arg);
		p.SetStatus(arg->GetError());
	}
	BeforeReturn(arg, false);
}

void CGXDLMSServer::HandleSetRequestWithDataBlock(CGXByteBuffer& data, CGXDLMSLNParameters& p){
	GetSetRequestBlockIndex(data, p);
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(nullptr, true);
		return;
	}
	if (!p.IsLastBlock()) {
		m_Info.SetMoreData( (DLMS_DATA_REQUEST_TYPES)(m_Info.GetMoreData() | DLMS_DATA_REQUEST_TYPES_BLOCK));
	}
	else {
		m_Info.SetMoreData( (DLMS_DATA_REQUEST_TYPES)(m_Info.GetMoreData() & ~DLMS_DATA_REQUEST_TYPES_BLOCK));
	}
	m_Transaction->GetData().Set(&data, data.GetPosition());
	if (!p.IsMultipleBlocks()) {
		CGXDLMSValueEventArg* arg = *m_Transaction->GetTargets().begin();
		GetValueFromRequest(m_Transaction->GetData(), arg);
		if (CheckValueType(p, arg)) {
			PreWrite(arg);
			p.SetStatus(arg->GetError());
			p.SetMultipleBlocks(true);
			BeforeReturn(nullptr, true);
			return;
		}
	}
	return;
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
int GenerateConfirmedServiceError(
    DLMS_CONFIRMED_SERVICE_ERROR service,
    DLMS_SERVICE_ERROR type,
    unsigned char Code, CGXByteBuffer& data)
{    
    data.Set(LLC_REPLY_BYTES, 3);         
    data.SetUInt8(DLMS_COMMAND_CONFIRMED_SERVICE_ERROR);
    data.SetUInt8(service);
    data.SetUInt8(type);
    data.SetUInt8(Code);
	return 0;
}

int CGXDLMSServer::HandleSetRequest(CGXByteBuffer& data)
{
	unsigned char ch, type;
	// Return error if connection is not established.
	if (!m_Settings.IsConnected())
	{
		return GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
			DLMS_SERVICE_ERROR_SERVICE, DLMS_SERVICE_UNSUPPORTED, m_ReplyData);
	}
	// Get type.
	if (data.GetUInt8(&type))
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	// Get invoke ID and priority.
	if (data.GetUInt8(&ch))
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_SET_RESPONSE, DLMS_SET_COMMAND_TYPE_NORMAL, nullptr, 0);
	if (type > 3) {
		m_Settings.ResetBlockIndex();
		p.SetStatus(DLMS_ERROR_CODE_NOT_IMPLEMENTED);
	}
	else{
		p.SetRequestType(type);
		if (type == DLMS_SET_COMMAND_TYPE_NORMAL || type == DLMS_SET_COMMAND_TYPE_FIRST_DATABLOCK)
		{
			HandleSetRequestNormalAndFirstDataBlock(data, p);
		}
		else {
			if (type == DLMS_SET_COMMAND_TYPE_WITH_DATABLOCK)
			{
				// Set Request With Data Block
				HandleSetRequestWithDataBlock(data, p);
			}
		}
	}
	CGXDLMS::GetLNPdu(p, m_ReplyData);
	return DLMS_ERROR_CODE_OK;
}

void CGXDLMSServer::ClearLastLTInfo(CGXDLMSLNParameters& p) {
	if (m_Transaction->GetCommand() != DLMS_COMMAND_NONE) {
		m_Settings.SetCount(0);
		m_Settings.SetIndex(0);
		m_Settings.ResetBlockIndex();

		m_Transaction->Clear();

		p.SetBlockIndex(m_Settings.GetBlockIndex());
	}
}

void CGXDLMSServer::CheckGetRequestLongTransaction(CGXByteBuffer& data, CGXDLMSLNParameters& p) {
	unsigned long index;
	if (data.GetUInt32(&index) != 0)
	{
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return;
	}
	if (index != m_Settings.GetBlockIndex())
	{
		p.SetStatus(DLMS_ERROR_CODE_READ_ABORTED);
		return;
	}
	m_Settings.IncreaseBlockIndex();
	p.SetBlockIndex(m_Settings.GetBlockIndex());
	// If m_Transaction is not in progress.
	if (m_Transaction->GetCommand() == DLMS_COMMAND_NONE)
	{
		p.SetStatus(DLMS_ERROR_CODE_NO_LONG_GET_OR_READ_IN_PROGRESS);
		return;
	}
}

void ProcessGetRequestWithList(CGXDLMSValueEventArg* arg, CGXDLMSLNParameters& p) {
	if (arg->GetError() != DLMS_ERROR_CODE_OK) {
		p.GetData()->SetUInt8(arg->GetError());
		arg->SetHandled(true);
	}
	else {
		if (arg->GetCAValue().byteArr != NULL && arg->GetCAValue().size != 0) {
			p.GetData()->SetUInt8(DLMS_ERROR_CODE_OK);
			p.GetData()->Set(arg->GetCAValue().byteArr, arg->GetCAValue().size);
			arg->GetCAValue().Clear();
		}
		else {
			p.GetData()->SetUInt8(DLMS_ERROR_CODE_HARDWARE_FAULT);
			arg->SetHandled(true);
		}
	}
}

void ProcessGetRequest(CGXDLMSValueEventArg* arg, CGXDLMSLNParameters& p) {
	if (arg->GetError() != DLMS_ERROR_CODE_OK) {
		p.SetStatus(arg->GetError());
		arg->SetHandled(true);
	}
	else {
		if (arg->GetCAValue().byteArr != NULL && arg->GetCAValue().size != 0) {
			p.GetData()->Set(arg->GetCAValue().byteArr, arg->GetCAValue().size);
			arg->GetCAValue().Clear();
		}
		else {
			p.SetStatus(DLMS_ERROR_CODE_HARDWARE_FAULT);
			arg->SetHandled(true);
		}
	}
}

void CGXDLMSServer::GetRequestNormal(CGXByteBuffer& data, CGXDLMSLNParameters& p) {

	ClearLastLTInfo(p);

	CGXDLMSValueEventArg* arg = GetObjectInfoFromRequest(data, p);
	if (arg != nullptr && arg->GetError() != DLMS_ERROR_CODE_OK) {
		p.SetStatus(arg->GetError());
	}
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	GetParametersFromRequest(data, p, arg);
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	if (GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ && GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ_WRITE)
	{
		p.SetStatus(DLMS_ERROR_CODE_READ_WRITE_DENIED);
		BeforeReturn(arg, false);
		return;
	}
	PreRead(arg);
	if (m_Settings.GetCount() == 0) {
		m_Settings.SetCount(arg->GetRowEndIndex());
	}
	p.SetStatus(arg->GetError());
	if (arg->GetCAValue().byteArr != NULL && arg->GetCAValue().size != 0) {
		// If byte array is added do not add type.
		p.GetData()->Set(arg->GetCAValue().byteArr, arg->GetCAValue().size);
		arg->GetCAValue().Clear();
	}
	if (arg->GetHandled()) {
		m_Settings.SetCount(0);
		m_Settings.SetIndex(0);
		m_Transaction->SetCommand(DLMS_COMMAND_GET_REQUEST);
		BeforeReturn(arg, false);
	}
	else {
		m_Transaction->SetLongTransactionEvent(arg, DLMS_COMMAND_GET_REQUEST, DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK);
	}
}	

void CGXDLMSServer::GetRequestNextDataBlock(CGXByteBuffer& data, CGXDLMSLNParameters& p) {
	CheckGetRequestLongTransaction(data, p);
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(nullptr, true);
		return;
	}
	p.GetData()->Set(&m_Transaction->GetData());
	bool moreData = ((m_Settings.GetIndex() != m_Settings.GetCount()) || (m_Transaction->GetTargets().size() != 0));
	if (moreData)
	{
		if (p.GetData()->GetSize() < m_Settings.GetMaxPduSize())
		{
			std::vector<CGXDLMSValueEventArg*>::iterator arg = m_Transaction->GetTargets().begin();
			while (arg != m_Transaction->GetTargets().end() && p.GetData()->GetSize() < m_Settings.GetMaxPduSize())	{

				if ((*arg)->GetError() == DLMS_ERROR_CODE_OK) {
					if ((*arg)->GetTarget() == nullptr) {
						(*arg)->SetTarget(m_CurrentALN->GetObjectList().FindByLN((uint8_t*)(*arg)->GetTargetName()));
					}
                    bool first_request_arg = !m_Settings.GetIndex();
					PreRead(*arg);

					(*arg)->SetTargetName();
					m_CurrentALN->GetObjectList().FreeConstructedObj();
                    (*arg)->SetTarget(nullptr);
					if (first_request_arg && (m_Transaction->GetCommandType() == DLMS_GET_COMMAND_TYPE_WITH_LIST)) {
						ProcessGetRequestWithList((*arg), p);
					} else {
						ProcessGetRequest((*arg), p);
					}
				}
				else {
					if (m_Transaction->GetCommandType() == DLMS_GET_COMMAND_TYPE_WITH_LIST)
						p.GetData()->SetUInt8((*arg)->GetError());
					else
						p.SetStatus((*arg)->GetError());

					(*arg)->SetHandled(true);
				}
				if ((*arg)->GetHandled()) {
					m_Settings.SetCount(0);
					m_Settings.SetIndex(0);
					++arg;
				}
			}
			for (CGXDLMSValueEventCollection::iterator beg = m_Transaction->GetTargets().begin(); beg != arg; ++beg) {
				delete *beg;
			}
			m_Transaction->GetTargets().erase(m_Transaction->GetTargets().begin(), arg);
		}
	}
	p.SetMultipleBlocks(true);
}

void CGXDLMSServer::GetRequestWithList(CGXByteBuffer& data, CGXDLMSLNParameters& p) {
	unsigned long cnt;

	ClearLastLTInfo(p);

	m_Transaction->SetCommand(DLMS_COMMAND_GET_REQUEST);
	m_Transaction->SetCommandType(DLMS_GET_COMMAND_TYPE_WITH_LIST);

	if (GXHelpers::GetObjectCount(data, cnt) != 0)
	{
		p.SetStatus(DLMS_ERROR_CODE_OUTOFMEMORY);
		return;
	}
	GXHelpers::SetObjectCount(cnt, *p.GetData());
	while (cnt--) {
		CGXDLMSValueEventArg* arg = GetObjectInfoFromRequest(data, p);
		if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
			BeforeReturn(arg, true);
			return;
		}
		GetParametersFromRequest(data, p, arg);
		if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
			BeforeReturn(arg, true);
			return;
		}
		if (GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ && GetAttributeAccess(arg) != DLMS_ACCESS_MODE_READ_WRITE)
		{
			arg->SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
		}
		m_Transaction->SetLongTransactionEvent(arg);
		arg->SetTargetName();
	}
	m_CurrentALN->GetObjectList().FreeConstructedObj();
	CGXDLMSValueEventCollection::iterator t_arg = m_Transaction->GetTargets().begin();
	while (t_arg != m_Transaction->GetTargets().end() && p.GetData()->GetSize() < m_Settings.GetMaxPduSize()) {
		CGXDLMSValueEventArg* arg = *t_arg;
		if (arg->GetError() != DLMS_ERROR_CODE_OK) {
			p.GetData()->SetUInt8(arg->GetError());
			arg->SetHandled(true);
		}
		else {
			arg->SetTarget(m_CurrentALN->GetObjectList().FindByLN((uint8_t*)arg->GetTargetName()));
			PreRead(arg);
			ProcessGetRequestWithList(arg, p);

			m_CurrentALN->GetObjectList().FreeConstructedObj();
            arg->SetTarget(nullptr);
		}
		if (arg->GetHandled()) {
			m_Settings.SetCount(0);
			m_Settings.SetIndex(0);
			++t_arg;
		}
	}
	m_Transaction->ClearEventTo(t_arg);
}

int CGXDLMSServer::HandleGetRequest(
    CGXByteBuffer& data)
{       
    // Return error if connection is not established.
    if (!m_Settings.IsConnected())
    {
        return GenerateConfirmedServiceError(DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
            DLMS_SERVICE_ERROR_SERVICE, DLMS_SERVICE_UNSUPPORTED, m_ReplyData);
    }
    unsigned char ch, type;
    // Get type.
    if (data.GetUInt8(&type) != 0)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    // Get invoke ID and priority.
    if (data.GetUInt8(&ch) != 0)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
	CGXByteBuffer bb;
	CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_GET_RESPONSE, type, &bb, DLMS_ERROR_CODE_OK);
    // GetRequest normal
    if (type == DLMS_GET_COMMAND_TYPE_NORMAL)
    {
       GetRequestNormal(data, p);       
    }
    else if (type == DLMS_GET_COMMAND_TYPE_NEXT_DATA_BLOCK)
    {
        // Get request for next data block
        GetRequestNextDataBlock(data, p);
    }
    else if (type == DLMS_GET_COMMAND_TYPE_WITH_LIST)
    {
        // Get request with a list.
        GetRequestWithList(data, p);
    }
    else
    {
		GetRequestError(p);
	}
	CGXDLMS::GetLNPdu(p, m_ReplyData);
	if (m_Settings.GetCount() != m_Settings.GetIndex()
		|| bb.GetSize() != bb.GetPosition()) {

		if (m_Transaction->GetCommand() != DLMS_COMMAND_NONE)
			m_Transaction->SetData(bb);
	}
	else {
		m_Settings.SetCount(0);
		m_Settings.SetIndex(0);
		m_Settings.ResetBlockIndex();
		m_Transaction->Clear();
	}
	return DLMS_ERROR_CODE_OK;
}

void CGXDLMSServer::HanleMethodRequestNormal( CGXByteBuffer& data,	CGXDLMSLNParameters& p) {
	CGXDLMSValueEventArg* arg = GetObjectInfoFromRequest(data, p);
	if (arg != nullptr && arg->GetError() != DLMS_ERROR_CODE_OK) {
		p.SetStatus(arg->GetError());
	}
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	GetParametersFromRequest(data, p, arg);
	if (p.GetStatus() != DLMS_ERROR_CODE_OK) {
		BeforeReturn(arg, false);
		return;
	}
	if (GetMethodAccess(arg) == DLMS_METHOD_ACCESS_MODE_NONE)
	{
		p.SetStatus(DLMS_ERROR_CODE_READ_WRITE_DENIED);
		BeforeReturn(arg, false);
		return;
	}
	CheckTakeConfiguratorSession(p, arg);
	if (p.GetStatus() == DLMS_ERROR_CODE_OK) {
		PreAction(arg);
		if (arg->GetError() != DLMS_ERROR_CODE_OK) {
			// Add parameters error code.
			p.SetStatus(arg->GetError());
			p.GetData()->SetUInt8(0);
		}
		else {
			if (arg->GetCAValue().byteArr != NULL && arg->GetCAValue().size != 0) {
				// Add return parameters
				p.GetData()->SetUInt8(1);
				//Add parameters error code.
				p.GetData()->SetUInt8(0);
				p.GetData()->Set(arg->GetCAValue().byteArr, arg->GetCAValue().size);
				arg->GetCAValue().Clear();
			}
			else {
				p.SetStatus(arg->GetError());
				p.GetData()->SetUInt8(0);
			}
		}
	}
	if (arg->GetTarget()->GetObjectType() == DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME && arg->GetIndex() == 1)
	{
		if (!m_Settings.IsConnected())
			InvalidConnection();
		else
			Connected();
	}
	BeforeReturn(arg, false);
}

int CGXDLMSServer::HandleMethodRequest(CGXByteBuffer& data) {
	unsigned char ch, type;
	// Get type.
	if (data.GetUInt8(&type) != 0)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	// Get invoke ID and priority.
	if (data.GetUInt8(&ch) != 0)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	CGXByteBuffer bb;
	CGXDLMSLNParameters p(&m_Settings, DLMS_COMMAND_METHOD_RESPONSE, type, &bb, DLMS_ERROR_CODE_OK);
	// GetRequest normal
	if (type == DLMS_ACTION_COMMAND_TYPE_NORMAL)
		HanleMethodRequestNormal(data, p);
	else
		p.SetStatus(DLMS_ERROR_CODE_NOT_IMPLEMENTED);

	CGXDLMS::GetLNPdu(p, m_ReplyData);
	return DLMS_ERROR_CODE_OK;
}

void CGXDLMSServer::GetRequestError(CGXDLMSLNParameters& p) {
	m_Settings.ResetBlockIndex();
	p.SetRequestType(DLMS_GET_COMMAND_TYPE_NORMAL);
	p.SetStatus(DLMS_ERROR_CODE_NOT_IMPLEMENTED);
	p.GetData()->Clear();
}

int CGXDLMSServer::HandleCommand(
    DLMS_COMMAND& cmd,
    CGXByteBuffer& data)
{
#if defined(MEMLOG)
	vMemLog_ReportHeap("--> GXDLMSServer::HandleCommand()\n");
#endif
	int ret = 0;
	unsigned char frame = 0;
	if (cmd == DLMS_COMMAND_WRITE_REQUEST || cmd == DLMS_COMMAND_READ_REQUEST) {
		GenerateConfirmedServiceError((DLMS_CONFIRMED_SERVICE_ERROR)cmd,
			DLMS_SERVICE_ERROR_SERVICE,
			DLMS_SERVICE_UNSUPPORTED, m_ReplyData);
	}
	else {
		switch (cmd)
		{
		case DLMS_COMMAND_GET_REQUEST:
			if (data.GetSize() != 0)
			{
				ret = HandleGetRequest(data);
			}
			break;
		case DLMS_COMMAND_SET_REQUEST:
			ret = HandleSetRequest(data);
			break;
		case DLMS_COMMAND_METHOD_REQUEST:
			ret = HandleMethodRequest(data);
			break;
		case DLMS_COMMAND_SNRM:
			ret = HandleSnrmRequest(data);
			if (ret == 0) {
				frame = DLMS_COMMAND_UA;
				m_LinkEstablished = true;
				ResetPushState();
			}
			else {
				frame = DLMS_COMMAND_DM;
			}
			break;
		case DLMS_COMMAND_AARQ:
			if (m_LinkEstablished) {
				ret = HandleAarqRequest(data);
			}
			else {
				ret = DLMS_ERROR_CODE_REJECTED;
			}
			break;
		case DLMS_COMMAND_DISCONNECT_REQUEST:
		case DLMS_COMMAND_DISC:
			if (m_LinkEstablished) {
				m_Settings.SetConnected(false);
				Disconnected();
				frame = DLMS_COMMAND_UA;
				Reset(true);
				m_LinkEstablished = false;

			}
			else {
				frame = DLMS_COMMAND_DM;
			}
			break;
		case DLMS_COMMAND_NONE:
			//Get next frame.
			break;

		default:
			if ((cmd & 0x0F) == HDLC_FRAME_TYPE_S_FRAME) { // RR
				ret = HandleReadyRead(cmd, frame);
			}
			else {
				frame = DLMS_COMMAND_REJECTED;
			}
			break;
		}
	}

    if (ret == 0)
	{
		ret = CGXDLMS::GetHdlcFrame(m_Settings, frame, &m_ReplyData, m_RxTxData);
	}
    #if defined(MEMLOG)
    vMemLog_ReportLeaks();    
    #endif
    return ret;
}

int CGXDLMSServer::HandleReadyRead(DLMS_COMMAND& cmd, unsigned char& frame) {

	if (IsLongTransaction() || m_ReplyData.GetSize() != 0) {
		frame = m_Settings.GetNextSend(0);
	}
	else {
		frame = (m_Settings.GetSenderFrame() & 0xF0) | 0x01;
	}
	return 0;
}

bool CGXDLMSServer::CheckCtlField(unsigned char ctl,
	CGXByteBuffer &reply)
{
	if ((ctl & 0x0F) == HDLC_FRAME_TYPE_U_FRAME) {
		return true;
	}
	unsigned char clientNR = (ctl & 0xE0) >> 5;
	unsigned char srvNS = (m_Settings.GetSenderFrame() & 0x0E) >> 1;
	srvNS = (srvNS >= 7) ? 0 : (srvNS + 1);
	if (clientNR != srvNS) {
		CGXDLMS::GetHdlcFrame(m_Settings, DLMS_COMMAND_REJECTED, nullptr, reply);
		return false;
	}
	if ((ctl & 0x01) == HDLC_FRAME_TYPE_I_FRAME) { // I-frame

		unsigned char clientNS = (ctl & 0x0E) >> 1;
		unsigned char srvNR = (m_Settings.GetSenderFrame() & 0xE0) >> 5;
		if (clientNS != srvNR) {
			unsigned char frame = DLMS_COMMAND_RR;
			frame |= ((srvNR << 5) & 0xE0);
			CGXDLMS::GetHdlcFrame(m_Settings, frame, nullptr, reply);
			return false;
		}

	}
	return true;
}

int CGXDLMSServer::HandleRequest()
{
	int ret;
	if (m_RxTxData.GetSize() == 0)
		return 0;


	if ((ret = CGXDLMS::GetData(m_Settings, m_RxTxData, m_Info)) != 0)
	{
		//If all data is not received yet.
		if (ret == DLMS_ERROR_CODE_FALSE)
			ret = 0;
		else {
			if (m_Info.GetControlField() != 0x13)
				m_Info.Clear();

			CheckPushNeeded(m_Info);
			m_RxTxData.Clear(false);
		}
		return ret;
	}
	// If all data is not received yet.
	if (!m_Info.IsComplete())
		return 0;

	m_RxTxData.Clear(false);

	// Check is data send to this server.
	if (!IsTarget(m_Settings.GetServerAddress(), m_Settings.GetClientAddress()))
	{
		if (m_Info.GetCommand() != DLMS_COMMAND_SNRM || !CheckCallingAfterPush() || ((m_Info.GetControlField() & 0x10) == 0))
		{
			m_Info.Clear();
			return 0;
		}
	}

	// If client want next frame.
	if ((m_Info.GetMoreData() & DLMS_DATA_REQUEST_TYPES_FRAME) == DLMS_DATA_REQUEST_TYPES_FRAME)
	{
		return CGXDLMS::GetHdlcFrame(m_Settings, m_Settings.GetReceiverReady(), &m_ReplyData, m_RxTxData);
	}
	// Update command if m_Transaction and next frame is asked.
	if (m_Info.GetCommand() == DLMS_COMMAND_NONE)
	{
		if (m_Transaction->GetCommand() != DLMS_COMMAND_NONE)
		{
			m_Info.SetCommand(m_Transaction->GetCommand());
		}
	}

	if (!CheckCtlField(m_Info.GetControlField(), m_RxTxData)) {
		m_Info.Clear();
		return 0;
	}
	ret = HandleCommand(m_Info.GetCommand(), m_Info.GetData());
	CheckPushNeeded(m_Info);
	m_Info.Clear();
	return ret;
}
