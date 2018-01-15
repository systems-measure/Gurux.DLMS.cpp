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

#include "../include/GXDLMSPppSetup.h"
#include "../include/GXDLMSClient.h"
#include <sstream>

//Constructor.
CGXDLMSPppSetup::CGXDLMSPppSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_PPP_SETUP)
{
    m_Authentication = PPP_AUTHENTICATION_TYPE_NONE;
}

//LN Constructor.
CGXDLMSPppSetup::CGXDLMSPppSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_PPP_SETUP, ln)
{
    m_Authentication = PPP_AUTHENTICATION_TYPE_NONE;
}

PPP_AUTHENTICATION_TYPE CGXDLMSPppSetup::GetAuthentication()
{
    return m_Authentication;
}
void CGXDLMSPppSetup::SetAuthentication(PPP_AUTHENTICATION_TYPE value)
{
    m_Authentication = value;
}

/**
PPP authentication procedure user name.
*/
CGXByteBuffer CGXDLMSPppSetup::GetUserName()
{
    return m_UserName;
}

void CGXDLMSPppSetup::SetUserName(CGXByteBuffer value)
{
    m_UserName = value;
}

/**
 PPP authentication procedure password.
*/

CGXByteBuffer& CGXDLMSPppSetup::GetPassword()
{
    return m_Password;
}

void CGXDLMSPppSetup::SetPassword(CGXByteBuffer value)
{
    m_Password = value;
}

std::string CGXDLMSPppSetup::GetPHYReference()
{
    return m_PHYReference;
}
void CGXDLMSPppSetup::SetPHYReference(std::string value)
{
    m_PHYReference = value;
}

std::vector<CGXDLMSPppSetupLcpOption>& CGXDLMSPppSetup::GetLCPOptions()
{
    return m_LCPOptions;
}


std::vector<CGXDLMSPppSetupIPCPOption>& CGXDLMSPppSetup::GetIPCPOptions()
{
    return m_IPCPOptions;
}

// Returns amount of attributes.
int CGXDLMSPppSetup::GetAttributeCount()
{
    return 5;
}

// Returns amount of methods.
int CGXDLMSPppSetup::GetMethodCount()
{
    return 0;
}

int CGXDLMSPppSetup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
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
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSPppSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else if (e.GetIndex() == 5)
    {
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSPppSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
