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
#include "../include/GXDLMSActivityCalendar.h"

CGXDLMSActivityCalendar::CGXDLMSActivityCalendar() : CGXDLMSObject(DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR, "0.0.13.0.0.255")
{
}

CGXDLMSActivityCalendar::CGXDLMSActivityCalendar(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR, ln)
{

}

CGXDLMSActivityCalendar::~CGXDLMSActivityCalendar()
{
    
}

// Returns amount of attributes.
int CGXDLMSActivityCalendar::GetAttributeCount()
{
    return 10;
}

// Returns amount of methods.
int CGXDLMSActivityCalendar::GetMethodCount()
{
    return 1;
}

int CGXDLMSActivityCalendar::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;

    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 10)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSActivityCalendar::GetDataType(signed char index) {
	if (index == 1)
	{
		return  DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 2)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 3)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 4)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 5)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 6)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 7)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 8)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 9)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 10)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	return DLMS_DATA_TYPE_NONE;
}

// Returns value of given attribute.
int CGXDLMSActivityCalendar::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    CGXByteBuffer data;
    if (e.GetIndex() == 1)
    {
        int ret;
        if ((ret = GetLogicalName(this, data)) != 0)
        {
            return ret;
        }
		e.SetHandled(true);
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
    if (e.GetIndex() == 10)
    {
       
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSActivityCalendar::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else if (e.GetIndex() == 10)
    {
       
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
