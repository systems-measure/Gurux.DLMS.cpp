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
//#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSClock.h"
//#include "../include/GXDLMSConverter.h"

void CGXDLMSClock::Init()
{
    //m_Deviation = m_ClockBase = DLMS_CLOCK_BASE_NONE;
    //m_Enabled = false;
    //m_TimeZone = 0;
    //m_Status = DLMS_CLOCK_STATUS_OK;
}

/**
 Constructor.
*/
CGXDLMSClock::CGXDLMSClock() : CGXDLMSObject(DLMS_OBJECT_TYPE_CLOCK, "0.0.1.0.0.255")
{
    Init();
}

/**
Constructor.
@param ln Logical Name of the object.
*/
CGXDLMSClock::CGXDLMSClock(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_CLOCK, ln)
{
    Init();
}

/**
 Time of COSEM Clock object.
*/
//CGXDateTime& CGXDLMSClock::GetTime()
//{
//    return m_Time;
//}
//void CGXDLMSClock::SetTime(CGXDateTime& value)
//{
//    m_Time = value;
//}
//
///**
// TimeZone of COSEM Clock object.
//*/
//short CGXDLMSClock::GetTimeZone()
//{
//    return m_TimeZone;
//}
//void CGXDLMSClock::SetTimeZone(short value)
//{
//    m_TimeZone = value;
//}
//
///**
// Status of COSEM Clock object.
//*/
//DLMS_CLOCK_STATUS CGXDLMSClock::GetStatus()
//{
//    return m_Status;
//}
//void CGXDLMSClock::SetStatus(DLMS_CLOCK_STATUS value)
//{
//    m_Status = value;
//}
//
//CGXDateTime& CGXDLMSClock::GetBegin()
//{
//    return m_Begin;
//}
//
//void CGXDLMSClock::SetBegin(CGXDateTime& value)
//{
//    m_Begin = value;
//}
//
//CGXDateTime& CGXDLMSClock::GetEnd()
//{
//    return m_End;
//}
//void CGXDLMSClock::SetEnd(CGXDateTime& value)
//{
//    m_End = value;
//}
//
//char CGXDLMSClock::GetDeviation()
//{
//    return m_Deviation;
//}
//void CGXDLMSClock::SetDeviation(char value)
//{
//    m_Deviation = value;
//}
//
//bool CGXDLMSClock::GetEnabled()
//{
//    return m_Enabled;
//}
//void CGXDLMSClock::SetEnabled(bool value)
//{
//    m_Enabled = value;
//}
//
///**
// Clock base of COSEM Clock object.
//*/
//DLMS_CLOCK_BASE CGXDLMSClock::GetClockBase()
//{
//    return m_ClockBase;
//}
//void CGXDLMSClock::SetClockBase(DLMS_CLOCK_BASE value)
//{
//    m_ClockBase = value;
//}

// Returns amount of attributes.
int CGXDLMSClock::GetAttributeCount()
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSClock::GetMethodCount()
{
    return 6;
}

int CGXDLMSClock::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_INT16;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_INT8;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_ENUM;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

DLMS_DATA_TYPE CGXDLMSClock::GetDataType(signed char index) {
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
		return DLMS_DATA_TYPE_INT16;
	}
	if (index == 4)
	{
		return DLMS_DATA_TYPE_UINT8;
	}
	if (index == 5)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 6)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 7)
	{
		return DLMS_DATA_TYPE_INT8;
	}
	if (index == 8)
	{
		return DLMS_DATA_TYPE_BOOLEAN;
	}
	if (index == 9)
	{
		return DLMS_DATA_TYPE_ENUM;
	}
	return DLMS_DATA_TYPE_NONE;
}
/*
 * Returns value of given attribute.
 */
int CGXDLMSClock::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
		CGXByteBuffer data;
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
       
        return 0;
    }
    if (e.GetIndex() == 3)
    {
       
        return 0;
    }
    if (e.GetIndex() == 4)
    {
        
        return 0;
    }
    if (e.GetIndex() == 5)
    {
       
        return 0;
    }
    if (e.GetIndex() == 6)
    {
      
        return 0;
    }
    if (e.GetIndex() == 7)
    {
       
        return 0;
    }
    if (e.GetIndex() == 8)
    {
     
        return 0;
    }
    if (e.GetIndex() == 9)
    {
       
        return 0;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSClock::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
