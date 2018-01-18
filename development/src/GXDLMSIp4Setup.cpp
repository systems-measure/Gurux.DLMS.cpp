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

#include "../include/GXDLMSIp4Setup.h"
#include "../include/GXDLMSClient.h"
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)//Windows includes
#include "pcap.h"
#elif !defined(__ICCARM__)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif


//Constructor.
CGXDLMSIp4Setup::CGXDLMSIp4Setup() : CGXDLMSObject(DLMS_OBJECT_TYPE_IP4_SETUP)
{
    m_IPAddress.empty();
    m_SubnetMask = 0;
    m_GatewayIPAddress = 0;
    m_UseDHCP = false;
    m_PrimaryDNSAddress = 0;
    m_SecondaryDNSAddress = 0;
}

//LN Constructor.
CGXDLMSIp4Setup::CGXDLMSIp4Setup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_IP4_SETUP, ln)
{
    m_IPAddress.empty();
    m_SubnetMask = 0;
    m_GatewayIPAddress = 0;
    m_UseDHCP = false;
    m_PrimaryDNSAddress = 0;
    m_SecondaryDNSAddress = 0;
}

std::string& CGXDLMSIp4Setup::GetDataLinkLayerReference()
{
    return m_DataLinkLayerReference;
}
void CGXDLMSIp4Setup::SetDataLinkLayerReference(std::string value)
{
    m_DataLinkLayerReference = value;
}

std::string& CGXDLMSIp4Setup::GetIPAddress()
{
    return m_IPAddress;
}

void CGXDLMSIp4Setup::SetIPAddress(std::string& value)
{
    m_IPAddress = value;
}

std::vector<unsigned long>& CGXDLMSIp4Setup::GetMulticastIPAddress()
{
    return m_MulticastIPAddress;
}

std::vector<CGXDLMSIp4SetupIpOption>& CGXDLMSIp4Setup::GetIPOptions()
{
    return m_IPOptions;
}
void CGXDLMSIp4Setup::SetIPOptions(std::vector<CGXDLMSIp4SetupIpOption>& value)
{
    m_IPOptions.clear();
    for (std::vector<CGXDLMSIp4SetupIpOption>::iterator it = value.begin(); it != value.end(); ++it)
    {
        m_IPOptions.push_back(*it);
    }
}

unsigned long CGXDLMSIp4Setup::GetSubnetMask()
{
    return m_SubnetMask;
}

void CGXDLMSIp4Setup::SetSubnetMask(unsigned long value)
{
    m_SubnetMask = value;
}

unsigned long CGXDLMSIp4Setup::GetGatewayIPAddress()
{
    return m_GatewayIPAddress;
}
void CGXDLMSIp4Setup::SetGatewayIPAddress(unsigned long value)
{
    m_GatewayIPAddress = value;
}

bool CGXDLMSIp4Setup::GetUseDHCP()
{
    return m_UseDHCP;
}
void CGXDLMSIp4Setup::SetUseDHCP(bool value)
{
    m_UseDHCP = value;
}

unsigned long CGXDLMSIp4Setup::GetPrimaryDNSAddress()
{
    return m_PrimaryDNSAddress;
}
void CGXDLMSIp4Setup::SetPrimaryDNSAddress(unsigned long value)
{
    m_PrimaryDNSAddress = value;
}

unsigned long CGXDLMSIp4Setup::GetSecondaryDNSAddress()
{
    return m_SecondaryDNSAddress;
}

void CGXDLMSIp4Setup::SetSecondaryDNSAddress(unsigned long value)
{
    m_SecondaryDNSAddress = value;
}

// Returns amount of attributes.
int CGXDLMSIp4Setup::GetAttributeCount()
{
    return 10;
}

// Returns amount of methods.
int CGXDLMSIp4Setup::GetMethodCount()
{
    return 3;
}

int CGXDLMSIp4Setup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
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
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 10)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSIp4Setup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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

// Set value of given attribute.
int CGXDLMSIp4Setup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
