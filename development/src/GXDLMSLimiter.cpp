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

#include "../include/GXDLMSLimiter.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSActionSet.h"
#include "SPODES.h"
#include <sstream>

//Constructor.
CGXDLMSLimiter::CGXDLMSLimiter() : CGXDLMSObject(DLMS_OBJECT_TYPE_LIMITER)
{

}

//LN Constructor.
CGXDLMSLimiter::CGXDLMSLimiter(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_LIMITER, ln)
{
   
}

// Returns amount of attributes.
int CGXDLMSLimiter::GetAttributeCount()
{
    return 11;
}

// Returns amount of methods.
int CGXDLMSLimiter::GetMethodCount()
{
    return 2;
}

int CGXDLMSLimiter::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 3)
    {
		return CGXDLMSObject::GetDataType(index, type);
    }
    else if (index == 4)
    {
		return CGXDLMSObject::GetDataType(index, type);
    }
    else if (index == 5)
    {
		return CGXDLMSObject::GetDataType(index, type);
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
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 10)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 11)
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
int CGXDLMSLimiter::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else if (e.GetIndex() == 11)
    {
        
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSLimiter::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else if (e.GetIndex() == 11)
    {
		
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
