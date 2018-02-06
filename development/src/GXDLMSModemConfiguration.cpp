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
#include "../include/GXDLMSModemConfiguration.h"
#include "../include/GXDLMSConverter.h"
#include <sstream>

void CGXDLMSModemConfiguration::Init()
{
    m_CommunicationSpeed = DLMS_BAUD_RATE_9600;
    m_ModemProfile.push_back("OK");
    m_ModemProfile.push_back("CONNECT");
    m_ModemProfile.push_back("RING");
    m_ModemProfile.push_back("NO CARRIER");
    m_ModemProfile.push_back("ERROR");
    m_ModemProfile.push_back("CONNECT 1200");
    m_ModemProfile.push_back("NO DIAL TONE");
    m_ModemProfile.push_back("BUSY");
    m_ModemProfile.push_back("NO ANSWER");
    m_ModemProfile.push_back("CONNECT 600");
    m_ModemProfile.push_back("CONNECT 2400");
    m_ModemProfile.push_back("CONNECT 4800");
    m_ModemProfile.push_back("CONNECT 9600");
    m_ModemProfile.push_back("CONNECT 14 400");
    m_ModemProfile.push_back("CONNECT 28 800");
    m_ModemProfile.push_back("CONNECT 33 600");
    m_ModemProfile.push_back("CONNECT 56 000");
}

// Constructor.
CGXDLMSModemConfiguration::CGXDLMSModemConfiguration() : CGXDLMSObject(DLMS_OBJECT_TYPE_MODEM_CONFIGURATION, "0.0.2.0.0.255")
{
    Init();
}

/**
 Constructor.
 @param ln Logical Name of the object.
*/
CGXDLMSModemConfiguration::CGXDLMSModemConfiguration(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_MODEM_CONFIGURATION, ln)
{
    Init();
}

DLMS_BAUD_RATE CGXDLMSModemConfiguration::GetCommunicationSpeed()
{
    return m_CommunicationSpeed;
}
void CGXDLMSModemConfiguration::SetCommunicationSpeed(DLMS_BAUD_RATE value)
{
    m_CommunicationSpeed = value;
}

std::vector<CGXDLMSModemInitialisation>& CGXDLMSModemConfiguration::GetInitialisationStrings()
{
    return m_InitialisationStrings;
}
void CGXDLMSModemConfiguration::SetInitialisationStrings(std::vector<CGXDLMSModemInitialisation>& value)
{
    m_InitialisationStrings = value;
}

std::vector< std::string > CGXDLMSModemConfiguration::GetModemProfile()
{
    return m_ModemProfile;
}

void CGXDLMSModemConfiguration::SetModemProfile(std::vector< std::string >& value)
{
    m_ModemProfile = value;
}

// Returns amount of attributes.
int CGXDLMSModemConfiguration::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSModemConfiguration::GetMethodCount()
{
    return 0;
}

int CGXDLMSModemConfiguration::GetDataType(signed char index, DLMS_DATA_TYPE& type)
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
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSModemConfiguration::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
int CGXDLMSModemConfiguration::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
       return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 4)
    {
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}
