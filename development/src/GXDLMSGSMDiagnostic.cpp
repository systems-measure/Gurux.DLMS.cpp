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
#include "../include/GXDLMSGSMDiagnostic.h"

//Constructor.
CGXDLMSGSMDiagnostic::CGXDLMSGSMDiagnostic() : CGXDLMSObject(DLMS_OBJECT_TYPE_GPRS_SETUP)
{
}

//LN Constructor.
CGXDLMSGSMDiagnostic::CGXDLMSGSMDiagnostic(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_GPRS_SETUP, ln)
{
}

// Returns amount of attributes.
int CGXDLMSGSMDiagnostic::GetAttributeCount()
{
    return 8;
}

// Returns amount of methods.
int CGXDLMSGSMDiagnostic::GetMethodCount()
{
    return 0;
}

void CGXDLMSGSMDiagnostic::GetValues(std::vector<std::string>& values)
{

}

void CGXDLMSGSMDiagnostic::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }
}

int CGXDLMSGSMDiagnostic::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_DATETIME;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSGSMDiagnostic::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
	CGXByteBuffer data;
//	e.SetByteArray(true);
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
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSGSMDiagnostic::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

