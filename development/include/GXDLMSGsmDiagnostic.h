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

#ifndef GXDLMSGSMDIAGNOSTIC_H
#define GXDLMSGSMDIAGNOSTIC_H

#include "GXDLMSObject.h"
#include "GXDLMSQualityOfService.h"

enum GX_STATUS
{
	DLMS_STATUS_NOT_REG		= 0,
	DLMS_STATUS_REGISTERED	= 1,
	DLMS_STATUS_SEARCHING	= 2,
	DLMS_STATUS_REG_DENY	= 3,
	DLMS_STATUS_UNKNOWN		= 4,
	DLMS_STATUS_REG_ROAMING	= 5
};
enum GX_CS_ATTACHMENT
{
	DLMS_CS_ATTACHMENT_INACTIVE			= 0,
	DLMS_CS_ATTACHMENT_INCOMING_CALL	= 1,
	DLMS_CS_ATTACHMENT_ACTIVE			= 2,
};
enum GX_PS_STATUS
{
	DLMS_PS_STATUS_INACTIVE	= 0,
	DLMS_PS_STATUS_GPRS		= 1,
	DLMS_PS_STATUS_EDGE		= 2,
	DLMS_PS_STATUS_UMTS		= 3,
	DLMS_PS_STATUS_HSDPA	= 4,
};
class CGXDLMSGsmDiagnostic : public CGXDLMSObject
{
private:
	std::string			m_operator;
	GX_STATUS			m_status;
	GX_CS_ATTACHMENT	m_cs_attachment;
	GX_PS_STATUS		m_ps_status;

	void Init(void);
public:
    //Constructor.
    CGXDLMSGsmDiagnostic();

    //SN Constructor.
    CGXDLMSGsmDiagnostic(unsigned short sn);

    //LN Constructor.
    CGXDLMSGsmDiagnostic(std::string ln);

    std::string			GetOperator();
	GX_STATUS			GetStatus();
	GX_CS_ATTACHMENT	GetCsAttachment();
	GX_PS_STATUS		GetPsStatus();
    

    CGXDLMSQualityOfService& GetDefaultQualityOfService();

    CGXDLMSQualityOfService& GetRequestedQualityOfService();

    // Returns amount of attributes.
    int GetAttributeCount();

    // Returns amount of methods.
    int GetMethodCount();

    //Get attribute values of object.
    void GetValues(std::vector<std::string>& values);

    void GetAttributeIndexToRead(std::vector<int>& attributes);

    int GetDataType(int index, DLMS_DATA_TYPE& type);

    // Returns value of given attribute.
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    // Set value of given attribute.
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};

#endif //GXDLMSGSMDIAGNOSTIC_H