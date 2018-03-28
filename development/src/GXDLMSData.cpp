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

#include "../include/GXDLMSData.h"

//Constructor.
CGXDLMSData::CGXDLMSData() : CGXDLMSObject(DLMS_OBJECT_TYPE_DATA)
{
}

//LN Constructor.
CGXDLMSData::CGXDLMSData(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_DATA, ln)
{

}

//LN Constructor.
CGXDLMSData::CGXDLMSData(const char* ln, CArtVariant value) : CGXDLMSObject(DLMS_OBJECT_TYPE_DATA, ln)
{
   // m_Value = value;
}

// Get value of COSEM Data object.
//CArtVariant CGXDLMSData::GetValue()
//{
//    return m_Value;
//}
//
//// Set value of COSEM Data object.
//void CGXDLMSData::SetValue(CArtVariant& value)
//{
//    m_Value = value;
//}

// Returns amount of attributes.
int CGXDLMSData::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSData::GetMethodCount()
{
    return 0;
}

int CGXDLMSData::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        return CGXDLMSObject::GetDataType(index, type);
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSData::GetDataType(signed char index)
{
	if (index == 1)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 2)
	{
		return CGXDLMSObject::GetDataType(index);
	}
	return DLMS_DATA_TYPE_NONE;
}

// Returns value of given attribute.
int CGXDLMSData::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
		//CArtVariant tmp_value(m_Value);
  //      e.SetValue(tmp_value);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSData::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
        //SetValue(e.GetCAValue());
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}