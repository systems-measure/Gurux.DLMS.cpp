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

#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSDisconnectControl.h"
#include "../include/GXDLMSConverter.h"

//Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl() : CGXDLMSObject(DLMS_OBJECT_TYPE_DISCONNECT_CONTROL)
{
}

//SN Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(unsigned short sn) : CGXDLMSObject(DLMS_OBJECT_TYPE_DISCONNECT_CONTROL, sn)
{

}

//LN Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_DISCONNECT_CONTROL, ln)
{

}

/**
 Output state of COSEM Disconnect Control object.
*/
bool CGXDLMSDisconnectControl::GetOutputState()
{
    return m_OutputState;
}
void CGXDLMSDisconnectControl::SetOutputState(bool value)
{
    m_OutputState = value;
}

/**
 Control state of COSEM Disconnect Control object.
*/
DLMS_CONTROL_STATE CGXDLMSDisconnectControl::GetControlState()
{
    return m_ControlState;
}
void CGXDLMSDisconnectControl::SetControlState(DLMS_CONTROL_STATE value)
{
    m_ControlState = value;
}

/**
Control mode of COSEM Disconnect Control object.
*/
DLMS_CONTROL_MODE CGXDLMSDisconnectControl::GetControlMode()
{
    return m_ControlMode;
}
void CGXDLMSDisconnectControl::SetControlMode(DLMS_CONTROL_MODE value)
{
    m_ControlMode = value;
}

// Returns amount of attributes.
int CGXDLMSDisconnectControl::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSDisconnectControl::GetMethodCount()
{
    return 2;
}

void CGXDLMSDisconnectControl::GetValues(std::vector<std::string>& values)
{
   /* values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(CGXDLMSVariant(m_OutputState).ToString());
    values.push_back(CGXDLMSConverter::ToString(m_ControlState));
    values.push_back(CGXDLMSConverter::ToString(m_ControlMode));*/
}

void CGXDLMSDisconnectControl::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //OutputState
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //ControlState
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //ControlMode
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
}

int CGXDLMSDisconnectControl::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSDisconnectControl::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    if (e.GetIndex() == 2)
    {
		data.SetUInt8(DLMS_DATA_TYPE_BOOLEAN);
		data.SetUInt8(m_OutputState);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(m_ControlState);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(m_ControlMode);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSDisconnectControl::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.size == 1) {
			m_OutputState = *(e.GetCAValue().GetCurPtr());
			return DLMS_ERROR_CODE_OK;
		}
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
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
        m_ControlState = (DLMS_CONTROL_STATE)val;
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
		m_ControlMode = (DLMS_CONTROL_MODE)val;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}