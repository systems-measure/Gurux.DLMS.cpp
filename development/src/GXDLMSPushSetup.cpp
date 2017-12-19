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

#include "../include/GXDLMSPushSetup.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSObjectFactory.h"
#include <sstream>

//Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_PUSH_SETUP)
{
   /* m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
    GXHelpers::SetLogicalName("0.7.25.9.0.255", m_LN);
    m_Service = DLMS_SERVICE_TYPE_TCP;
    m_Message = DLMS_MESSAGE_TYPE_COSEM_APDU;*/
}

//LN Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_PUSH_SETUP, ln)
{
    /*m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;*/
    GXHelpers::SetLogicalName(ln, m_LN);
}

//DLMS_SERVICE_TYPE CGXDLMSPushSetup::GetService()
//{
//    return m_Service;
//}
//void CGXDLMSPushSetup::SetService(DLMS_SERVICE_TYPE value)
//{
//    m_Service = value;
//}
//
//std::string& CGXDLMSPushSetup::GetDestination()
//{
//    return m_Destination;
//}
//void CGXDLMSPushSetup::SetDestination(std::string& value)
//{
//    m_Destination = value;
//}
//
//DLMS_MESSAGE_TYPE CGXDLMSPushSetup::GetMessage()
//{
//    return m_Message;
//}
//void CGXDLMSPushSetup::SetMessage(DLMS_MESSAGE_TYPE value)
//{
//    m_Message = value;
//}
// Returns amount of attributes.
int CGXDLMSPushSetup::GetAttributeCount()
{
    return 7;
}

// Returns amount of methods.
int CGXDLMSPushSetup::GetMethodCount()
{
    return 1;
}

void CGXDLMSPushSetup::GetValues(std::vector<std::string>& values)
{
   
}

void CGXDLMSPushSetup::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //PushObjectList
    if (CanRead(2))
    {
        attributes.push_back(2);
    }

    //SendDestinationAndMethod
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //CommunicationWindow
    if (CanRead(4))
    {
        attributes.push_back(4);
    }
    //RandomisationStartInterval
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //NumberOfRetries
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
    //RepetitionDelay
    if (CanRead(7))
    {
        attributes.push_back(7);
    }
}

int CGXDLMSPushSetup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 5)
    {
        type = DLMS_DATA_TYPE_UINT16;
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT8;
    }
    else if (index == 7)
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
int CGXDLMSPushSetup::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    CGXByteBuffer data;
    int ret;
    if (e.GetIndex() == 1)
    {
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
        
        e.SetValue(data);
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSPushSetup::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
