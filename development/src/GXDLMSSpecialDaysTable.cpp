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
#include "../include/GXDLMSSpecialDaysTable.h"
#include <sstream>

//Constructor.
CGXDLMSSpecialDaysTable::CGXDLMSSpecialDaysTable() : CGXDLMSObject(DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE)
{
}

//LN Constructor.
CGXDLMSSpecialDaysTable::CGXDLMSSpecialDaysTable(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE, ln)
{

}

CGXDLMSSpecialDaysTable::~CGXDLMSSpecialDaysTable()
{
    
}

// Returns amount of attributes.
int CGXDLMSSpecialDaysTable::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSSpecialDaysTable::GetMethodCount()
{
    return 2;
}

void CGXDLMSSpecialDaysTable::GetValues(std::vector<std::string>& values)
{
    
}

void CGXDLMSSpecialDaysTable::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //Entries
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
}

int CGXDLMSSpecialDaysTable::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    //Entries
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSSpecialDaysTable::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
        
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSSpecialDaysTable::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else if (e.GetIndex() == 2)
    {
        
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
