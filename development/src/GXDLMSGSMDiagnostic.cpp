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

#include "../include/GXDLMSGSMDiagnostic.h"

//Constructor.
CGXDLMSGSMDiagnostic::CGXDLMSGSMDiagnostic() : CGXDLMSObject(DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC)
{
}

//LN Constructor.
CGXDLMSGSMDiagnostic::CGXDLMSGSMDiagnostic(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC, ln)
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

const DLMS_DATA_TYPE GSM_TypeArr[] = { DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_STRING, DLMS_DATA_TYPE_ENUM, DLMS_DATA_TYPE_ENUM,
                                       DLMS_DATA_TYPE_ENUM, DLMS_DATA_TYPE_STRUCTURE, DLMS_DATA_TYPE_ARRAY, DLMS_DATA_TYPE_DATETIME };

int CGXDLMSGSMDiagnostic::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
	if (index >= 1 && index <= 8) {
		type = GSM_TypeArr[index];
		return DLMS_ERROR_CODE_OK;
	}
	return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSGSMDiagnostic::GetDataType(signed char index) {
	if (index >= 1 && index <= 8) {
		return GSM_TypeArr[index];
	}
	return DLMS_DATA_TYPE_NONE;
}