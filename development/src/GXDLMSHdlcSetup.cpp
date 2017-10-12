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

#include "../include/GXDLMSHdlcSetup.h"
#include "../include/GXDLMSConverter.h"

//Constructor.
CGXDLMSIecHdlcSetup::CGXDLMSIecHdlcSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_HDLC_SETUP)
{
    m_CommunicationSpeed = DLMS_BAUD_RATE_9600;
    m_WindowSizeTransmit = m_WindowSizeReceive = 1;
    m_MaximumInfoLengthTransmit = m_MaximumInfoLengthReceive = 128;
}

//SN Constructor.
CGXDLMSIecHdlcSetup::CGXDLMSIecHdlcSetup(unsigned short sn) : CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_HDLC_SETUP, sn)
{
    m_CommunicationSpeed = DLMS_BAUD_RATE_9600;
    m_WindowSizeTransmit = m_WindowSizeReceive = 1;
    m_MaximumInfoLengthTransmit = m_MaximumInfoLengthReceive = 128;
}

//LN Constructor.
CGXDLMSIecHdlcSetup::CGXDLMSIecHdlcSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_HDLC_SETUP, ln)
{
    m_CommunicationSpeed = DLMS_BAUD_RATE_9600;
    m_WindowSizeTransmit = m_WindowSizeReceive = 1;
    m_MaximumInfoLengthTransmit = m_MaximumInfoLengthReceive = 128;
}

DLMS_BAUD_RATE CGXDLMSIecHdlcSetup::GetCommunicationSpeed()
{
    return m_CommunicationSpeed;
}
void CGXDLMSIecHdlcSetup::SetCommunicationSpeed(DLMS_BAUD_RATE value)
{
    m_CommunicationSpeed = value;
}

unsigned char CGXDLMSIecHdlcSetup::GetWindowSizeTransmit()
{
    return m_WindowSizeTransmit;
}
void CGXDLMSIecHdlcSetup::SetWindowSizeTransmit(unsigned char value)
{
    m_WindowSizeTransmit = value;
}

unsigned char CGXDLMSIecHdlcSetup::GetWindowSizeReceive()
{
    return m_WindowSizeReceive;
}
void CGXDLMSIecHdlcSetup::SetWindowSizeReceive(unsigned char value)
{
    m_WindowSizeReceive = value;
}

unsigned short CGXDLMSIecHdlcSetup::GetMaximumInfoLengthTransmit()
{
    return m_MaximumInfoLengthTransmit;
}
void CGXDLMSIecHdlcSetup::SetMaximumInfoLengthTransmit(unsigned short value)
{
    m_MaximumInfoLengthTransmit = value;
}

unsigned short CGXDLMSIecHdlcSetup::GetMaximumInfoLengthReceive()
{
    return m_MaximumInfoLengthReceive;
}
void CGXDLMSIecHdlcSetup::SetMaximumInfoLengthReceive(unsigned short value)
{
    m_MaximumInfoLengthReceive = value;
}

unsigned short CGXDLMSIecHdlcSetup::GetInterCharachterTimeout()
{
    return m_InterCharachterTimeout;
}
void CGXDLMSIecHdlcSetup::SetInterCharachterTimeout(unsigned short value)
{
    m_InterCharachterTimeout = value;
}

unsigned short CGXDLMSIecHdlcSetup::GetInactivityTimeout()
{
    return m_InactivityTimeout;
}
void CGXDLMSIecHdlcSetup::SetInactivityTimeout(unsigned short value)
{
    m_InactivityTimeout = value;
}

unsigned short CGXDLMSIecHdlcSetup::GetDeviceAddress()
{
    return m_DeviceAddress;
}
void CGXDLMSIecHdlcSetup::SetDeviceAddress(unsigned short value)
{
    m_DeviceAddress = value;
}

// Returns amount of attributes.
int CGXDLMSIecHdlcSetup::GetAttributeCount()
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSIecHdlcSetup::GetMethodCount()
{
    return 0;
}

void CGXDLMSIecHdlcSetup::GetValues(std::vector<std::string>& values)
{
    /*values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(CGXDLMSConverter::ToString(m_CommunicationSpeed));
    values.push_back(CGXDLMSVariant(m_WindowSizeTransmit).ToString());
    values.push_back(CGXDLMSVariant(m_WindowSizeReceive).ToString());
    values.push_back(CGXDLMSVariant(m_MaximumInfoLengthTransmit).ToString());
    values.push_back(CGXDLMSVariant(m_MaximumInfoLengthReceive).ToString());
    values.push_back(CGXDLMSVariant(m_InterCharachterTimeout).ToString());
    values.push_back(CGXDLMSVariant(m_InactivityTimeout).ToString());
    values.push_back(CGXDLMSVariant(m_DeviceAddress).ToString());*/
}

void CGXDLMSIecHdlcSetup::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //CommunicationSpeed
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //WindowSizeTransmit
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //WindowSizeReceive
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //MaximumInfoLengthTransmit
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    //MaximumInfoLengthReceive
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    //InterCharachterTimeout
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    //InactivityTimeout
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }
    //DeviceAddress
    if (!IsRead(9))
    {
        attributes.push_back(9);
    }
}

int CGXDLMSIecHdlcSetup::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
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
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSIecHdlcSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
	e.SetByteArray(true);
	CGXByteBuffer data;
    if (e.GetIndex() == 1)
    {
        int ret;
		if ((ret = GetLogicalName(this, data)) != 0)
        {
            return ret;
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 2)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(m_CommunicationSpeed);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 3)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_WindowSizeTransmit);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 4)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_WindowSizeReceive);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 5)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_MaximumInfoLengthTransmit);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 6)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_MaximumInfoLengthReceive);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 7)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_InterCharachterTimeout);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 8)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_InactivityTimeout);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 9)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_DeviceAddress);
        e.SetValue(data);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSIecHdlcSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_CommunicationSpeed = (DLMS_BAUD_RATE)val;
    }
    else if (e.GetIndex() == 3)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_WindowSizeTransmit = (unsigned char)val;
    }
    else if (e.GetIndex() == 4)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_WindowSizeReceive = (unsigned char)val;
    }
    else if (e.GetIndex() == 5)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_MaximumInfoLengthTransmit = (unsigned short)val;
    }
    else if (e.GetIndex() == 6)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_MaximumInfoLengthReceive = (unsigned short)val;
    }
    else if (e.GetIndex() == 7)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_InterCharachterTimeout = (unsigned short)val;
    }
    else if (e.GetIndex() == 8)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_InactivityTimeout = (unsigned short)val;
    }
    else if (e.GetIndex() == 9)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_DeviceAddress = (unsigned short)val;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}