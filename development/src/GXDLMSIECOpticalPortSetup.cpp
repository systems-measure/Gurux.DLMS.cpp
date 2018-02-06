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

#include "../include/GXDLMSIECOpticalPortSetup.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSConverter.h"

void CGXDLMSIECOpticalPortSetup::Init()
{
    m_DefaultMode = DLMS_OPTICAL_PROTOCOL_MODE_DEFAULT;
    m_DefaultBaudrate = DLMS_BAUD_RATE_300;
    m_ProposedBaudrate = DLMS_BAUD_RATE_9600;
}

//Constructor.
CGXDLMSIECOpticalPortSetup::CGXDLMSIECOpticalPortSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, "0.0.20.0.0.255")
{
    Init();
}

//LN Constructor.
CGXDLMSIECOpticalPortSetup::CGXDLMSIECOpticalPortSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP, ln)
{
    Init();
}

DLMS_OPTICAL_PROTOCOL_MODE CGXDLMSIECOpticalPortSetup::GetDefaultMode()
{
    return m_DefaultMode;
}
void CGXDLMSIECOpticalPortSetup::SetDefaultMode(DLMS_OPTICAL_PROTOCOL_MODE value)
{
    m_DefaultMode = value;
}

DLMS_BAUD_RATE CGXDLMSIECOpticalPortSetup::GetDefaultBaudrate()
{
    return m_DefaultBaudrate;
}
void CGXDLMSIECOpticalPortSetup::SetDefaultBaudrate(DLMS_BAUD_RATE value)
{
    m_DefaultBaudrate = value;
}

DLMS_BAUD_RATE CGXDLMSIECOpticalPortSetup::GetProposedBaudrate()
{
    return m_ProposedBaudrate;
}
void CGXDLMSIECOpticalPortSetup::SetProposedBaudrate(DLMS_BAUD_RATE value)
{
    m_ProposedBaudrate = value;
}

DLMS_LOCAL_PORT_RESPONSE_TIME CGXDLMSIECOpticalPortSetup::GetResponseTime()
{
    return m_ResponseTime;
}
void CGXDLMSIECOpticalPortSetup::SetResponseTime(DLMS_LOCAL_PORT_RESPONSE_TIME value)
{
    m_ResponseTime = value;
}

std::string CGXDLMSIECOpticalPortSetup::GetDeviceAddress()
{
    return m_DeviceAddress;
}
void CGXDLMSIECOpticalPortSetup::SetDeviceAddress(std::string value)
{
    m_DeviceAddress = value;
}

std::string CGXDLMSIECOpticalPortSetup::GetPassword1()
{
    return m_Password1;
}
void CGXDLMSIECOpticalPortSetup::SetPassword1(std::string value)
{
    m_Password1 = value;
}

std::string CGXDLMSIECOpticalPortSetup::GetPassword2()
{
    return m_Password2;
}
void CGXDLMSIECOpticalPortSetup::SetPassword2(std::string value)
{
    m_Password2 = value;
}

std::string CGXDLMSIECOpticalPortSetup::GetPassword5()
{
    return m_Password5;
}
void CGXDLMSIECOpticalPortSetup::SetPassword5(std::string value)
{
    m_Password5 = value;
}

// Returns amount of attributes.
int CGXDLMSIECOpticalPortSetup::GetAttributeCount()
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSIECOpticalPortSetup::GetMethodCount()
{
    return 0;
}

int CGXDLMSIECOpticalPortSetup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSIECOpticalPortSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        int ret;
		CGXByteBuffer data;
        if ((ret = GetLogicalName(this, data)) != 0)
        {
            return ret;
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 5)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 6)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 7)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 8)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 9)
    {
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSIECOpticalPortSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 3)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 4)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 5)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 6)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 7)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 8)
    {
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 9)
    {
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}