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
    m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
    GXHelpers::SetLogicalName("0.7.25.9.0.255", m_LN);
    m_Service = DLMS_SERVICE_TYPE_TCP;
    m_Message = DLMS_MESSAGE_TYPE_COSEM_APDU;
}

//SN Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup(unsigned short sn) : CGXDLMSObject(DLMS_OBJECT_TYPE_PUSH_SETUP, sn)
{
    m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
    GXHelpers::SetLogicalName("0.7.25.9.0.255", m_LN);
}

//LN Constructor.
CGXDLMSPushSetup::CGXDLMSPushSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_PUSH_SETUP, ln)
{
    m_RandomisationStartInterval = m_NumberOfRetries = m_RepetitionDelay = 0;
    GXHelpers::SetLogicalName(ln, m_LN);
}

DLMS_SERVICE_TYPE CGXDLMSPushSetup::GetService()
{
    return m_Service;
}
void CGXDLMSPushSetup::SetService(DLMS_SERVICE_TYPE value)
{
    m_Service = value;
}

std::string& CGXDLMSPushSetup::GetDestination()
{
    return m_Destination;
}
void CGXDLMSPushSetup::SetDestination(std::string& value)
{
    m_Destination = value;
}

DLMS_MESSAGE_TYPE CGXDLMSPushSetup::GetMessage()
{
    return m_Message;
}
void CGXDLMSPushSetup::SetMessage(DLMS_MESSAGE_TYPE value)
{
    m_Message = value;
}
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
    /*values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);

    std::stringstream sb;
    sb << '[';
    bool empty = true;
    for (std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >::iterator it = m_PushObjectList.begin(); it != m_PushObjectList.end(); ++it)
    {
        if (!empty)
        {
            sb << ", ";
        }
        empty = false;
        std::string str;
        it->first->GetLogicalName(str);
        sb.write(str.c_str(), str.size());
    }
    sb << ']';
    values.push_back(sb.str());

    sb.str(std::string());
    sb << GetService();
    sb << " ";
    sb << GetDestination().c_str();
    sb << " ";
    sb << GetMessage();
    values.push_back(sb.str());

    sb.str(std::string());
    sb << '[';
    empty = true;
    for (std::vector<std::pair<CGXDateTime, CGXDateTime> >::iterator it = m_CommunicationWindow.begin(); it != m_CommunicationWindow.end(); ++it)
    {
        if (!empty)
        {
            sb << ", ";
        }
        empty = false;
        std::string str = it->first.ToString();
        sb.write(str.c_str(), str.size());
        sb << " ";
        str = it->second.ToString();
        sb.write(str.c_str(), str.size());
    }
    sb << ']';
    values.push_back(sb.str());

    values.push_back(CGXDLMSVariant(m_RandomisationStartInterval).ToString());
    values.push_back(CGXDLMSVariant(m_NumberOfRetries).ToString());
    values.push_back(CGXDLMSVariant(m_RepetitionDelay).ToString());*/
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

int CGXDLMSPushSetup::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
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
//	e.SetByteArray(true);
    int ret;
    if (e.GetIndex() == 1)
    {
//		e.SetByteArray(true);
        if ((ret = GetLogicalName(this, data)) != 0)
        {
            return ret;
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_PushObjectList.size(), data);
        for (std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject> >::iterator it = m_PushObjectList.begin(); it != m_PushObjectList.end(); ++it)
        {
			data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
			data.SetUInt8(4);
			data.SetUInt8(DLMS_DATA_TYPE_UINT16);
			data.SetUInt16(it->first->GetObjectType());
            if ((ret = GetLogicalName(it->first, data)) != 0)
            {
                return ret;
            }
			data.SetUInt8(DLMS_DATA_TYPE_INT8);
			data.SetUInt8((it->second).GetAttributeIndex());
			data.SetUInt8(DLMS_DATA_TYPE_UINT16);
			data.SetUInt16((it->second).GetDataIndex());
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(3);
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(GetService());
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(GetDestination().length());
		data.AddString(GetDestination().c_str());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(GetMessage());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_CommunicationWindow.size(), data);
        for (std::vector<std::pair< CGXDateTime, CGXDateTime> >::iterator it = m_CommunicationWindow.begin(); it != m_CommunicationWindow.end(); ++it)
        {
            data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
            data.SetUInt8(2);
			data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
			data.SetUInt8(12);
			GXHelpers::SetDateTime(data, it->first);
			data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
			data.SetUInt8(12);
			GXHelpers::SetDateTime(data, it->second);
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 5)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_RandomisationStartInterval);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 6)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_NumberOfRetries);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 7)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_RepetitionDelay);
		e.SetValue(data);
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
        //std::string ln;
        //m_PushObjectList.clear();
        //if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        //{
        //    for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
        //    {
        //        //DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)it->Arr[0].ToInteger();
        //        //GXHelpers::GetLogicalName(it->Arr[1].byteArr, ln);
        //        //CGXDLMSObject* obj = settings.GetObjects()->FindByLN(type, ln);
        //        ///*if (obj == NULL)
        //        //{
        //        //    obj = CGXDLMSObjectFactory::CreateObject(type);
        //        //    CGXDLMSObject::SetLogicalName(obj, it->Arr[1]);
        //        //}*/
        //        //CGXDLMSCaptureObject co(it->Arr[2].ToInteger(), it->Arr[3].ToInteger());
        //        //m_PushObjectList.push_back(std::pair<CGXDLMSObject*, CGXDLMSCaptureObject>(obj, co));
        //    }
        //}
    }
    else if (e.GetIndex() == 3)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 3) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		e.GetCAValue().GetVar(v_info);
		SetService((DLMS_SERVICE_TYPE)(*e.GetCAValue().GetCurPtr()));
		e.GetCAValue().IncreasePosition(v_info.size);
		e.GetCAValue().GetVar(v_info);
		std::string str;
		str.append(reinterpret_cast<char const*>(e.GetCAValue().GetCurPtr()), v_info.size);
		SetDestination(str);
		e.GetCAValue().IncreasePosition(v_info.size);
		e.GetCAValue().GetVar(v_info);
		SetMessage((DLMS_MESSAGE_TYPE)(*e.GetCAValue().GetCurPtr()));
    }
    else if (e.GetIndex() == 4)
    {
        /*m_CommunicationWindow.clear();
        if (e.GetValue().vt == DLMS_DATA_TYPE_ARRAY)
        {
            int ret;
            for (std::vector<CGXDLMSVariant>::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                CGXDLMSVariant tmp;
                if ((ret = CGXDLMSClient::ChangeType(it->Arr[0], DLMS_DATA_TYPE_DATETIME, tmp)) != 0)
                {
                    return ret;
                }
                CGXDateTime start = tmp.dateTime;
                if ((ret = CGXDLMSClient::ChangeType(it->Arr[1], DLMS_DATA_TYPE_DATETIME, tmp)) != 0)
                {
                    return ret;
                }
                CGXDateTime end = tmp.dateTime;
                m_CommunicationWindow.push_back(std::pair<CGXDateTime, CGXDateTime>(start, end));
            }
        }*/
    }
    else if (e.GetIndex() == 5)
    {
        //m_RandomisationStartInterval = e.GetValue().ToInteger();
    }
    else if (e.GetIndex() == 6)
    {
       // m_NumberOfRetries = e.GetValue().ToInteger();
    }
    else if (e.GetIndex() == 7)
    {
       // m_RepetitionDelay = e.GetValue().ToInteger();
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
