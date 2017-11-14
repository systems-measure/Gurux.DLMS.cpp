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

CGXDLMSObject::CGXDLMSObject(unsigned short class_id, unsigned char version, CGXByteBuffer& ln)
{
    Initialize(class_id, version, &ln);
}

CGXDLMSObject::CGXDLMSObject(DLMS_OBJECT_TYPE type)
{
    Initialize(type, 0, NULL);
}

int CGXDLMSObject::GetLogicalName(CGXDLMSObject * target, CGXByteBuffer& value)
{
	value.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
	value.SetUInt8(6);
    value.Set(target->m_LN, 6);
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSObject::SetLogicalName(CGXDLMSObject * target, CArtVariant& value)
{
	VarInfo v_info;
	value.GetVar(v_info);
    if (v_info.vt != DLMS_DATA_TYPE_OCTET_STRING || v_info.size != 6)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    memcpy(target->m_LN, value.byteArr, 6);
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSObject::Initialize(unsigned short class_id, unsigned char version, CGXByteBuffer* ln)
{
    m_DataValidity = false;
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
	m_Attributes = nullptr;
	m_MethodAttributes = nullptr;
}

CGXDLMSObject::~CGXDLMSObject(void)
{
	if (m_Attributes != nullptr) {
		delete m_Attributes;
		m_Attributes = nullptr;
	}
	if (m_MethodAttributes != nullptr) {
		delete m_MethodAttributes;
		m_MethodAttributes = nullptr;
	}
}

bool CGXDLMSObject::GetDataValidity() {
	return m_DataValidity;
}

void CGXDLMSObject::SetDataValidity(bool validity) {
	m_DataValidity = validity;
}

std::string CGXDLMSObject::GetName()
{
	std::string ln;
    GXHelpers::GetLogicalName(m_LN, ln);
    return ln;
}

int CGXDLMSObject::SetName(CGXDLMSVariant& value)
{
    if (value.vt == DLMS_DATA_TYPE_STRING)
    {
        GXHelpers::SetLogicalName(value.strVal.c_str(), m_LN);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_OBJECT_TYPE CGXDLMSObject::GetObjectType()
{
    return m_ObjectType;
}

int CGXDLMSObject::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
    if (index == 0)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
	if (index == 1) {
		type = DLMS_DATA_TYPE_OCTET_STRING;
	}
	else {
		if (m_Attributes != nullptr ) {
			if (index <= m_Attributes->GetSize()) {
				type = (m_Attributes->GetCollection())[index - 1].GetDataType();
			}
			else {
				return DLMS_ERROR_CODE_INVALID_PARAMETER;
			}
		}
		else {
			type = DLMS_DATA_TYPE_NONE;
		}
	}
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSObject::SetDataType(unsigned char index, DLMS_DATA_TYPE type)
{
	if (index == 1 && type != DLMS_DATA_TYPE_OCTET_STRING) {
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	else {
		if (m_Attributes == nullptr) {
			m_Attributes = new CGXAttributeCollection(this->GetAttributeCount());
		}
		if (index <= m_Attributes->GetSize()) {
			(m_Attributes->GetCollection())[index - 1].SetDataType(type);
			return DLMS_ERROR_CODE_OK;
		}
	}
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_ACCESS_MODE CGXDLMSObject::GetAccess(unsigned char index)
{
	//LN is read only.
	if (index == 1)
	{
		return DLMS_ACCESS_MODE_READ;
	}
	else {
		if (m_Attributes != nullptr) {
			if (index <= m_Attributes->GetSize()) {
				return (m_Attributes->GetCollection())[index - 1].GetAccess();
			}
			else {
				return DLMS_ACCESS_MODE_NONE;
			}
		}
	}
	return DLMS_ACCESS_MODE_READ;
}

// Set attribute access.
void CGXDLMSObject::SetAccess(unsigned char index, DLMS_ACCESS_MODE access)
{
	if (index == 1 && access != DLMS_ACCESS_MODE_READ) {
	}
	else {
		if (m_Attributes == nullptr) {
			m_Attributes = new CGXAttributeCollection(this->GetAttributeCount());
		}
		if (index <= m_Attributes->GetSize()) {
			(m_Attributes->GetCollection())[index - 1].SetAccess(access);
		}
	}
}

DLMS_METHOD_ACCESS_MODE CGXDLMSObject::GetMethodAccess(unsigned char index)
{
	if (m_MethodAttributes != nullptr) {
		if (index <= m_MethodAttributes->GetSize()) {
			return (m_MethodAttributes->GetCollection())[index - 1].GetMethodAccess();
		}
		else {
			return DLMS_METHOD_ACCESS_MODE_NONE;
		}
	}
	return DLMS_METHOD_ACCESS_MODE_NONE;
}

void CGXDLMSObject::SetMethodAccess(unsigned char index, DLMS_METHOD_ACCESS_MODE access)
{
	if (m_MethodAttributes == nullptr) {
		m_MethodAttributes = new CGXAttributeCollection(this->GetMethodCount());
	}
	if (index <= m_MethodAttributes->GetSize()) {
		(m_MethodAttributes->GetCollection())[index - 1].SetMethodAccess(access);
	}
}

int CGXDLMSObject::GetUIDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
	if (index == 0)
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if (index == 1) {
		type = DLMS_DATA_TYPE_OCTET_STRING;
	}
	else {
		if (m_Attributes != nullptr) {
			if (index <= m_Attributes->GetSize()) {
				type = (m_Attributes->GetCollection())[index - 1].GetUIDataType();
			}
			else {
				return DLMS_ERROR_CODE_INVALID_PARAMETER;
			}
		}
		else {
			type = DLMS_DATA_TYPE_NONE;
		}
	}
	return DLMS_ERROR_CODE_OK;
}

void CGXDLMSObject::SetUIDataType(unsigned char index, DLMS_DATA_TYPE type)
{
	if (index == 1 && type != DLMS_DATA_TYPE_OCTET_STRING) {
	}
	else {
		if (m_Attributes == nullptr) {
			m_Attributes = new CGXAttributeCollection(this->GetAttributeCount());
		}
		if (index <= m_Attributes->GetSize()) {
			(m_Attributes->GetCollection())[index - 1].SetUIDataType(type);
		}
	}
}

void CGXDLMSObject::GetLogicalName(std::string& ln)
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

CGXAttributeCollection* CGXDLMSObject::GetAttributes()
{
    return m_Attributes;
}

CGXAttributeCollection* CGXDLMSObject::GetMethodAttributes()
{
    return m_MethodAttributes;
}

void CGXDLMSObject::SetAttributeCount(unsigned char count) {
	if (m_Attributes != nullptr) {
		delete[] m_Attributes;
	}
	m_Attributes = new CGXAttributeCollection(count);
}

void CGXDLMSObject::SetMethodCount(unsigned char count) {
	if (m_MethodAttributes != nullptr) {
		delete[] m_MethodAttributes;
	}
	m_MethodAttributes = new CGXAttributeCollection(count);
}

bool CGXDLMSObject::IsRead(int index)
{
	return 0;
}

bool CGXDLMSObject::CanRead(int index)
{
    return GetAccess(index) != DLMS_ACCESS_MODE_NONE;
}