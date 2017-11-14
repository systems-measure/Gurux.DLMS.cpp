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

//LN Constructor.
CGXDLMSDisconnectControl::CGXDLMSDisconnectControl(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_DISCONNECT_CONTROL, ln)
{

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

int CGXDLMSDisconnectControl::GetDataType(signed char index, DLMS_DATA_TYPE& type)
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
		
    }
    else if (e.GetIndex() == 3)
    {
		
    }
    else if (e.GetIndex() == 4)
    {
		
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}