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

#include "../include/GXDLMSMBusMasterPortSetup.h"
#include "../include/GXDLMSConverter.h"

//Constructor.
CGXDLMSMBusMasterPortSetup::CGXDLMSMBusMasterPortSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_MBUS_MASTER_PORT_SETUP)
{
    m_CommSpeed = DLMS_BAUD_RATE_2400;
}

//LN Constructor.
CGXDLMSMBusMasterPortSetup::CGXDLMSMBusMasterPortSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_MBUS_MASTER_PORT_SETUP, ln)
{
    m_CommSpeed = DLMS_BAUD_RATE_2400;
}

/**
The communication speed supported by the port.
*/
DLMS_BAUD_RATE CGXDLMSMBusMasterPortSetup::GetCommSpeed()
{
    return m_CommSpeed;
}

void CGXDLMSMBusMasterPortSetup::SetCommSpeed(DLMS_BAUD_RATE value)
{
    m_CommSpeed = value;
}

// Returns amount of attributes.
int CGXDLMSMBusMasterPortSetup::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSMBusMasterPortSetup::GetMethodCount()
{
    return 0;
}

int CGXDLMSMBusMasterPortSetup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSMBusMasterPortSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMBusMasterPortSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}