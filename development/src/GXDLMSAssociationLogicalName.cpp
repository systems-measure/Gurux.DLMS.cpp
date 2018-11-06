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
#include "prj_defines.h"

#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSServer.h"
#include "../include/GXSecure.h"

#include "converter_mpro\converter_mpro.h"
#include "memory\memory_srv.h"

/**
 Constructor.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName() : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, 1, "0.0.40.0.0.255")
{
	m_AssociationStatus = DLMS_DLMS_ASSOCIATION_STATUS_NON_ASSOCIATED;
}

/**
 Constructor.
 @param ln Logical Name of the object.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, 1, ln)
{
	m_AssociationStatus = DLMS_DLMS_ASSOCIATION_STATUS_NON_ASSOCIATED;
}

CGXDLMSObjectCollection& CGXDLMSAssociationLogicalName::GetObjectList()
{
    return m_ObjectList;
}

bool CGXDLMSAssociationLogicalName::CompareSecret(CGXByteBuffer& lls) {
	uint8_t	LLSSecret_read[64];
	mem::rd_ext_mem(LLSSecret_read, GetAddr(LLSSecret), sizeof(LLSSecret_read));
	bool equal = lls.Compare(LLSSecret_read, strlen((const char*)LLSSecret_read));
	lls.SetPosition(0);
	return equal;
}

DLMS_DLMS_ASSOCIATION_STATUS CGXDLMSAssociationLogicalName::GetAssociationStatus()
{
    return m_AssociationStatus;
}

void CGXDLMSAssociationLogicalName::SetAssociationStatus(DLMS_DLMS_ASSOCIATION_STATUS value)
{
    m_AssociationStatus = value;
}

unsigned char CGXDLMSAssociationLogicalName::GetMPos() {
	return m_pos;
}

void CGXDLMSAssociationLogicalName::SetMPos(unsigned char pos) {
	m_pos = pos;
}

// Returns amount of attributes.
int CGXDLMSAssociationLogicalName::GetAttributeCount()
{
    //Security Setup Reference is from version 1.
    if (GetVersion() > 0)
        return 9;
    return 8;
}

// Returns amount of methods.
int CGXDLMSAssociationLogicalName::GetMethodCount()
{
    return 4;
}

const DLMS_DATA_TYPE ALN_TypeArr[] = { DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_ARRAY, DLMS_DATA_TYPE_STRUCTURE, DLMS_DATA_TYPE_STRUCTURE,
                                   DLMS_DATA_TYPE_STRUCTURE, DLMS_DATA_TYPE_STRUCTURE, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_ENUM, DLMS_DATA_TYPE_OCTET_STRING };

int CGXDLMSAssociationLogicalName::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
	if (index >= 1 && index <= 9) {
		type = ALN_TypeArr[index];
		return DLMS_ERROR_CODE_OK;
	}
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSAssociationLogicalName::GetDataType(signed char index) {
	if (index >= 1 && index <= 9) {
		return ALN_TypeArr[index];
	}
	return DLMS_DATA_TYPE_NONE;
}
