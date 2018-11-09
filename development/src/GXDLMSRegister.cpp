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

#include "../include/GXDLMSRegister.h"

//LN Constructor.
CGXDLMSRegister::CGXDLMSRegister(DLMS_OBJECT_TYPE type, const char* ln) : CGXDLMSObject(type, ln)
{
}

//Constructor.
CGXDLMSRegister::CGXDLMSRegister(void) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER)
{
}

//LN Constructor.
CGXDLMSRegister::CGXDLMSRegister(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER, ln)
{
}

//LN Constructor.
CGXDLMSRegister::CGXDLMSRegister(const char* ln, double scaler, unsigned char unit, CArtVariant value) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER, ln)
{
}

// Returns amount of attributes.
unsigned char CGXDLMSRegister::GetAttributeCount()
{
    return 3;
}

// Returns amount of methods.
unsigned char CGXDLMSRegister::GetMethodCount()
{
    return 1;
}

const DLMS_DATA_TYPE Rg_TypeArr[] = { DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_STRUCTURE};

int CGXDLMSRegister::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
	if (index >= 1 && index <= 3) {
		type = Rg_TypeArr[index];
		if (type == DLMS_DATA_TYPE_NONE) {
			return CGXDLMSObject::GetDataType(index, type);
		}
		return DLMS_ERROR_CODE_OK;
	}
	return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSRegister::GetDataType(signed char index) {
	if (index >= 1 && index <= 3) {
		DLMS_DATA_TYPE type = Rg_TypeArr[index];
		if (type == DLMS_DATA_TYPE_NONE) {
			return CGXDLMSObject::GetDataType(index);
		}
		return type;
	}
	return DLMS_DATA_TYPE_NONE;
}