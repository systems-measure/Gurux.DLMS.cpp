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
#include "../include/GXDLMSConverter.h"
#include "../include/GXDLMSDemandRegister.h"

bool CGXDLMSDemandRegister::IsRead(int index)
{
   	return true;
}

/**
 Constructor.
*/
CGXDLMSDemandRegister::CGXDLMSDemandRegister() : CGXDLMSObject(DLMS_OBJECT_TYPE_DEMAND_REGISTER)
{
   
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSDemandRegister::CGXDLMSDemandRegister(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_DEMAND_REGISTER, ln)
{
    
}

/*
 * Reset e.GetValue().
 */
void CGXDLMSDemandRegister::Reset()
{

}

/*
 * Next period.
 */
void CGXDLMSDemandRegister::NextPeriod()
{

}

void CGXDLMSDemandRegister::GetValues(std::vector<std::string>& values)
{
    
}

void CGXDLMSDemandRegister::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //ScalerUnit
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //CurrentAvarageValue
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //LastAvarageValue
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //Status
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //CaptureTime
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
    //StartTimeCurrent
    if (CanRead(7))
    {
        attributes.push_back(7);
    }
    //Period
    if (CanRead(8))
    {
        attributes.push_back(8);
    }
    //NumberOfPeriods
    if (CanRead(9))
    {
        attributes.push_back(9);
    }
}

// Returns amount of attributes.
int CGXDLMSDemandRegister::GetAttributeCount()
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSDemandRegister::GetMethodCount()
{
    return 2;
}

int CGXDLMSDemandRegister::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        Reset();
        return DLMS_ERROR_CODE_OK;
    }
    e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSDemandRegister::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
		
    }
    if (index == 3)
    {
		
    }
    if (index == 4)
    {
        
    }
    if (index == 5)
    {
		
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        type = DLMS_DATA_TYPE_UINT16;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSDemandRegister::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
		
    }
    if (e.GetIndex() == 3)
    {
		
    }
    if (e.GetIndex() == 4)
    {
		
    }
    if (e.GetIndex() == 5)
    {
		
    }
    if (e.GetIndex() == 6)
    {
		
    }
    if (e.GetIndex() == 7)
    {
		
    }
    if (e.GetIndex() == 8)
    {
		
    }
    if (e.GetIndex() == 9)
    {
		
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSDemandRegister::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
    else if (e.GetIndex() == 4 )
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
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
