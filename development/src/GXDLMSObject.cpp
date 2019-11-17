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

#include "../include/GXDLMSObject.h"
#include "../include/GXHelpers.h"


//LN Constructor.
CGXDLMSObject::CGXDLMSObject(DLMS_OBJECT_TYPE type, const char* ln)
{
    Initialize(type, 0, NULL);
    GXHelpers::SetLogicalName(ln, m_LN);
}

CGXDLMSObject::CGXDLMSObject()
{
    Initialize(DLMS_OBJECT_TYPE_NONE, 0, NULL);
}

CGXDLMSObject::CGXDLMSObject(unsigned short class_id, unsigned char version, const char* ln) {
	Initialize(class_id, version, NULL);
	GXHelpers::SetLogicalName(ln, m_LN);
}

CGXDLMSObject::CGXDLMSObject(DLMS_OBJECT_TYPE type)
{
    Initialize(type, 0, NULL);
}

int CGXDLMSObject::GetLogicalName(CGXDLMSObject * target, CGXByteBuffer& value)
{
	if (target != nullptr) {
		value.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		value.SetUInt8(6);
		value.Set(target->m_LN, 6);
		return DLMS_ERROR_CODE_OK;
	}
	return DLMS_ERROR_CODE_HARDWARE_FAULT;
}


void CGXDLMSObject::Initialize(unsigned short class_id, unsigned char version, CGXByteBuffer* ln)
{
    m_ObjectType = (DLMS_OBJECT_TYPE)class_id;
    m_Version = version;
    if (ln == NULL)
    {
        memset(m_LN, 0, 6);
    }
    else
    {
        int cnt = ln->GetSize();
        if (cnt == 6)
        {
            ln->Get(m_LN, 6);
        }
        else
        {
            assert(false);
        }
    }
	get_data_type = nullptr;
	constr_idx = 0xFFFF;
}

CGXDLMSObject::~CGXDLMSObject(void)
{
	
}

void CGXDLMSObject::SetDataTypeFunc(TypeAttrCallback callback) {
	get_data_type = callback;
}

void CGXDLMSObject::SetConstructedIdx(uint16_t* idx) {
	constr_idx = *idx;
}

std::string CGXDLMSObject::GetName()
{
	std::string ln;
    GXHelpers::GetLogicalName(m_LN, ln);
    return ln;
}

DLMS_OBJECT_TYPE CGXDLMSObject::GetObjectType()
{
    return m_ObjectType;
}

int CGXDLMSObject::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
	if (index == 0)
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if (get_data_type != nullptr && constr_idx != 0xFFFF) {
		type = (DLMS_DATA_TYPE)get_data_type(constr_idx);
	}
	return DLMS_ERROR_CODE_OK;
}

DLMS_DATA_TYPE CGXDLMSObject::GetDataType(signed char index) {
	if (get_data_type != nullptr && constr_idx != 0xFFFF) {
		return (DLMS_DATA_TYPE)get_data_type(constr_idx);
	}
    return DLMS_DATA_TYPE_NONE;
}

void CGXDLMSObject::GetLogicalName(char* ln)
{
    GXHelpers::GetLogicalName(m_LN, ln);
}

void CGXDLMSObject::GetLogicalName(unsigned char* c_ln) {
	memcpy(c_ln, m_LN, 6);
}

void CGXDLMSObject::SetVersion(unsigned char value)
{
    m_Version = value;
}

unsigned char CGXDLMSObject::GetVersion()
{
    return m_Version;
}
