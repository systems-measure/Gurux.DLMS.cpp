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
#include "../include/GXDLMSTcpUdpSetup.h"


void CGXDLMSTcpUdpSetup::Init()
{
 /*   m_Port = 4059;
    m_IPReference = "127.0.0.1";
    m_MaximumSimultaneousConnections = 1;
    SetInactivityTimeout(180);
    SetMaximumSegmentSize(576);*/
}

/**
 Constructor.
*/
CGXDLMSTcpUdpSetup::CGXDLMSTcpUdpSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_TCP_UDP_SETUP, "0.0.25.0.0.255")
{
    Init();
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSTcpUdpSetup::CGXDLMSTcpUdpSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_TCP_UDP_SETUP, ln)
{
    Init();
}

//int CGXDLMSTcpUdpSetup::GetPort()
//{
//    return m_Port;
//}
//
//void CGXDLMSTcpUdpSetup::SetPort(int value)
//{
//    m_Port = value;
//}
//
//std::string CGXDLMSTcpUdpSetup::GetIPReference()
//{
//    return m_IPReference;
//}
//void CGXDLMSTcpUdpSetup::SetIPReference(std::string value)
//{
//    m_IPReference = value;
//}
//
//int CGXDLMSTcpUdpSetup::GetMaximumSegmentSize()
//{
//    return m_MaximumSegmentSize;
//}
//void CGXDLMSTcpUdpSetup::SetMaximumSegmentSize(int value)
//{
//    m_MaximumSegmentSize = value;
//}
//
//int CGXDLMSTcpUdpSetup::GetMaximumSimultaneousConnections()
//{
//    return m_MaximumSimultaneousConnections;
//}
//void CGXDLMSTcpUdpSetup::SetMaximumSimultaneousConnections(int value)
//{
//    m_MaximumSimultaneousConnections = value;
//}
//
//int CGXDLMSTcpUdpSetup::GetInactivityTimeout()
//{
//    return m_InactivityTimeout;
//}
//void CGXDLMSTcpUdpSetup::SetInactivityTimeout(int value)
//{
//    m_InactivityTimeout = value;
//}

// Returns amount of attributes.
int CGXDLMSTcpUdpSetup::GetAttributeCount()
{
    return 6;
}

// Returns amount of methods.
int CGXDLMSTcpUdpSetup::GetMethodCount()
{
    return 0;
}

int CGXDLMSTcpUdpSetup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

DLMS_DATA_TYPE CGXDLMSTcpUdpSetup::GetDataType(signed char index) {
	if (index == 1)
	{
		return  DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 2)
	{
		return DLMS_DATA_TYPE_UINT16;
	}
	if (index == 3)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 4)
	{
		return DLMS_DATA_TYPE_UINT16;
	}
	if (index == 5)
	{
		return DLMS_DATA_TYPE_UINT8;
	}
	if (index == 6)
	{
		return DLMS_DATA_TYPE_UINT16;
	}
	return DLMS_DATA_TYPE_NONE;
}

// Returns value of given attribute.
int CGXDLMSTcpUdpSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSTcpUdpSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}