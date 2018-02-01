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

#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSServer.h"

CGXDLMSProfileGeneric::~CGXDLMSProfileGeneric()
{
   
}

void CGXDLMSProfileGeneric::Init()
{
    
}

int CGXDLMSProfileGeneric::GetSelectedColumns(
    int selector,
    CGXDLMSVariant& parameters,
    std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >& columns)
{
    
    return 0;
}
int CGXDLMSProfileGeneric::GetColumns(CGXByteBuffer& data)
{
    
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSProfileGeneric::GetData(
    CGXDLMSSettings& settings,
    CGXDLMSValueEventArg& e,
    std::vector< std::vector<CGXDLMSVariant> >& table,
    std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >& columns,
    CGXByteBuffer& data)
{
    
    return DLMS_ERROR_CODE_OK;
}

/*
* Add new capture object (column) to the profile generic.
*/
int CGXDLMSProfileGeneric::AddCaptureObject(CGXDLMSObject* pObj, int attributeIndex, int dataIndex)
{
    
    return DLMS_ERROR_CODE_OK;
}

/**
     * Get selected columns.
     *
     * @param cols
     *            selected columns.
     * @return Selected columns.
     */
int CGXDLMSProfileGeneric::GetSelectedColumns(
    std::vector<CGXDLMSVariant>& cols,
    std::vector<std::pair<CGXDLMSObject*, CGXDLMSCaptureObject*> >& columns)
{
   
    return 0;
}

int CGXDLMSProfileGeneric::GetProfileGenericData(
    CGXDLMSSettings& settings, CGXDLMSValueEventArg& e, CGXByteBuffer& reply)
{
    
	return 0;
}

/**
 Constructor.
*/
CGXDLMSProfileGeneric::CGXDLMSProfileGeneric() : CGXDLMSObject(DLMS_OBJECT_TYPE_PROFILE_GENERIC)
{
    Init();
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSProfileGeneric::CGXDLMSProfileGeneric(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_PROFILE_GENERIC, ln)
{
    Init();
}

/*
* Copies the values of the objects to capture into the buffer by reading
* capture objects.
*/
int CGXDLMSProfileGeneric::Capture(CGXDLMSServer* server)
{
    
    return 0;
}

int CGXDLMSProfileGeneric::Reset(std::vector<CGXByteBuffer>& reply)
{
    
	return 0;
}

int CGXDLMSProfileGeneric::Capture(std::vector<CGXByteBuffer>& reply)
{
    
	return 0;
}

//Returns amount of attributes.
int CGXDLMSProfileGeneric::GetAttributeCount()
{
    return 8;
}

//Returns amount of methods.
int CGXDLMSProfileGeneric::GetMethodCount()
{
    return 2;
}

int CGXDLMSProfileGeneric::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSProfileGeneric::GetDataType(signed char index) {
	if (index == 1)
	{
		return  DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 2)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 3)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 4)
	{
		return DLMS_DATA_TYPE_UINT32;
	}
	if (index == 5)
	{
		return DLMS_DATA_TYPE_ENUM;
	}
	if (index == 6)
	{
		return DLMS_DATA_TYPE_ARRAY;
	}
	if (index == 7)
	{
		return DLMS_DATA_TYPE_UINT32;
	}
	if (index == 8)
	{
		return DLMS_DATA_TYPE_UINT32;
	}
	return DLMS_DATA_TYPE_NONE;
}


int CGXDLMSProfileGeneric::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
   
    return 0;
}

/*
* Returns value of given attribute.
*/
int CGXDLMSProfileGeneric::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
		data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
		data.SetUInt8(0);
		e.SetValue(data);
       
    }
    else if (e.GetIndex() == 3)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
		data.SetUInt8(0);
		e.SetValue(data);
       
    }
    else if (e.GetIndex() == 4)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(0);
		e.SetValue(data);
      
    }
    else if (e.GetIndex() == 5)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(DLMS_SORT_METHOD_FIFO);
		e.SetValue(data);
       
    }
    else if (e.GetIndex() == 6)
    {
		data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
		data.SetUInt8(4);
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(0);
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(6);
		data.Zero(data.GetSize(), 6);
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(0);
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(0);
		e.SetValue(data);
        
    }
    else if (e.GetIndex() == 7)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(0);
		e.SetValue(data);
       
    }
    else if (e.GetIndex() == 8)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(1);
		e.SetValue(data);
     
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSProfileGeneric::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
