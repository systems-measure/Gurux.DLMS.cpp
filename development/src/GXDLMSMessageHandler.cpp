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

#include "../include/GXDLMSMessageHandler.h"
#include "../include/GXDLMSClient.h"
#include <sstream>

//Constructor.
CGXDLMSMessageHandler::CGXDLMSMessageHandler() : CGXDLMSObject(DLMS_OBJECT_TYPE_MESSAGE_HANDLER)
{
}

//LN Constructor.
CGXDLMSMessageHandler::CGXDLMSMessageHandler(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_MESSAGE_HANDLER, ln)
{

}

std::vector<std::pair<CGXDateTime, CGXDateTime> >& CGXDLMSMessageHandler::GetListeningWindow()
{
    return m_ListeningWindow;
}

std::vector<std::string>& CGXDLMSMessageHandler::GetAllowedSenders()
{
    return m_AllowedSenders;
}

std::vector<std::pair<std::string, std::pair<int, CGXDLMSScriptAction> > >& CGXDLMSMessageHandler::GetSendersAndActions()
{
    return m_SendersAndActions;
}

// Returns amount of attributes.
int CGXDLMSMessageHandler::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSMessageHandler::GetMethodCount()
{
    return 0;
}

int CGXDLMSMessageHandler::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    //ListeningWindow
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    //AllowedSenders
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    //SendersAndActions
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSMessageHandler::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSMessageHandler::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
