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

#include "../include/GXDLMSMacAddressSetup.h"

/**
 Constructor.
*/
CGXDLMSMacAddressSetup::CGXDLMSMacAddressSetup() : CGXDLMSObject(DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP, "0.0.25.2.0.255")
{
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSMacAddressSetup::CGXDLMSMacAddressSetup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP, ln)
{
}

// Returns amount of attributes.
int CGXDLMSMacAddressSetup::GetAttributeCount()
{
    return 2;
}

// Returns amount of methods.
int CGXDLMSMacAddressSetup::GetMethodCount()
{
    return 0;
}

const DLMS_DATA_TYPE MAC_TypeArr[] = { DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_OCTET_STRING };

int CGXDLMSMacAddressSetup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
	if (index >= 1 && index <= 2) {
		type = MAC_TypeArr[index];
		return DLMS_ERROR_CODE_OK;
	}
	return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSMacAddressSetup::GetDataType(signed char index) {
	if (index >= 1 && index <= 2) {
		return MAC_TypeArr[index];
	}
	return DLMS_DATA_TYPE_NONE;
}
