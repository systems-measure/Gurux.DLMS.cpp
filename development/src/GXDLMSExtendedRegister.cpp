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
#include "../include/GXDLMSExtendedRegister.h"

//Constructor.
CGXDLMSExtendedRegister::CGXDLMSExtendedRegister(void) : CGXDLMSRegister(DLMS_OBJECT_TYPE_EXTENDED_REGISTER, "0.0.0.0.0.0")
{
}

//LN Constructor.
CGXDLMSExtendedRegister::CGXDLMSExtendedRegister(const char* ln) : CGXDLMSRegister(DLMS_OBJECT_TYPE_EXTENDED_REGISTER, ln)
{
}

/**
 Status of COSEM Extended Register object.
*/
CGXDLMSVariant CGXDLMSExtendedRegister::GetStatus()
{
    return m_Status;
}
void CGXDLMSExtendedRegister::SetStatus(CGXDLMSVariant value)
{
    m_Status = value;
}

/**
 Capture time of COSEM Extended Register object.
*/
CGXDateTime& CGXDLMSExtendedRegister::GetCaptureTime()
{
    return m_CaptureTime;
}

void CGXDLMSExtendedRegister::SetCaptureTime(CGXDateTime value)
{
    m_CaptureTime = value;
}

// Returns amount of attributes.
int CGXDLMSExtendedRegister::GetAttributeCount()
{
    return 5;
}

// Returns amount of methods.
int CGXDLMSExtendedRegister::GetMethodCount()
{
    return 1;
}

int CGXDLMSExtendedRegister::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index < 4)
    {
        return CGXDLMSRegister::GetDataType(index, type);
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSExtendedRegister::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSExtendedRegister::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() < 4)
    {
        return CGXDLMSRegister::SetValue(settings, e);
    }
    else if (e.GetIndex() == 4)
    {
       
    }
    else if (e.GetIndex() == 5)
    {
        
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

