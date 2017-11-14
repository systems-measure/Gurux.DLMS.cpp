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
#include "../include/GXDLMSActivityCalendar.h"
#include <sstream>

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

void CGXDLMSActivityCalendar::GetValues(std::vector<std::string>& values)
{
   
}

void CGXDLMSActivityCalendar::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //CalendarNameActive
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //SeasonProfileActive
    if (CanRead(3))
    {
        attributes.push_back(3);
    }

    //WeekProfileTableActive
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //DayProfileTableActive
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //CalendarNamePassive
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
    //SeasonProfilePassive
    if (CanRead(7))
    {
        attributes.push_back(7);
    }
    //WeekProfileTablePassive
    if (CanRead(8))
    {
        attributes.push_back(8);
    }
    //DayProfileTablePassive
    if (CanRead(9))
    {
        attributes.push_back(9);
    }
    //Time.
    if (CanRead(10))
    {
        attributes.push_back(10);
    }
}

int CGXDLMSActivityCalendar::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
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
