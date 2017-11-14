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
   
}

//LN Constructor.
CGXDLMSIecHdlcSetup::CGXDLMSIecHdlcSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_IEC_HDLC_SETUP, ln)
{
   
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

// Set value of given attribute.
int CGXDLMSIecHdlcSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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