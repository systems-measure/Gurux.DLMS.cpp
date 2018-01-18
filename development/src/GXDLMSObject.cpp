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
	get_data_type = nullptr;
	constr_idx = 0xFF;
	//m_Attributes = nullptr;
	//m_MethodAttributes = nullptr;
}

CGXDLMSObject::~CGXDLMSObject(void)
{
	//if (m_Attributes != nullptr) {
	//	delete m_Attributes;
	//	m_Attributes = nullptr;
	//}
	//if (m_MethodAttributes != nullptr) {
	//	delete m_MethodAttributes;
	//	m_MethodAttributes = nullptr;
	//}
}

void CGXDLMSObject::SetDataTypeFunc(TypeAttrCallback callback) {
	get_data_type = callback;
}

bool CGXDLMSObject::GetDataValidity() {
	return m_DataValidity;
}

void CGXDLMSObject::SetDataValidity(bool validity) {
	m_DataValidity = validity;
}

void CGXDLMSObject::SetConstructedIdx(uint8_t* idx) {
	constr_idx = *idx;
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

int CGXDLMSObject::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 0)
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
	//if (index == 1) {
	//	type = DLMS_DATA_TYPE_OCTET_STRING;
	//}
	//else {
		if (get_data_type != nullptr && constr_idx != 0xFF) {
			type = (DLMS_DATA_TYPE)get_data_type(constr_idx);
		}
		/*if (m_Attributes != nullptr ) {
			for (unsigned char i = 0; i < m_Attributes->GetCountCollection(); ++i) {
				if (index == (m_Attributes->GetCollection())[i].GetIndex()) {
					type = (m_Attributes->GetCollection())[i].GetDataType();
					return DLMS_ERROR_CODE_OK;
				}
			}
		}
		else {
			type = DLMS_DATA_TYPE_NONE;
		}*/
	//}
    return DLMS_ERROR_CODE_OK;
}

DLMS_DATA_TYPE CGXDLMSObject::GetDataType(signed char index) {
	if (get_data_type != nullptr && constr_idx != 0xFF) {
		return (DLMS_DATA_TYPE)get_data_type(constr_idx);
	}
}

//int CGXDLMSObject::SetDataType(signed char index, DLMS_DATA_TYPE type)
//{
//	if (index == 1 && type != DLMS_DATA_TYPE_OCTET_STRING) {
//		return DLMS_ERROR_CODE_INVALID_PARAMETER;
//	}
//	else {
//		if (m_Attributes == nullptr) {
//			m_Attributes = new CGXAttributeCollection(this->GetAttributeCount());
//		}
//		for (unsigned char i = 0; i < m_Attributes->GetCountCollection(); ++i) {
//			if (index == (m_Attributes->GetCollection())[i].GetIndex()) {
//				(m_Attributes->GetCollection())[i].SetDataType(type);
//				return DLMS_ERROR_CODE_OK;
//			}
//		}
//		(m_Attributes->GetCollection())[m_Attributes->GetCountCollection()].SetIndex(index);
//		(m_Attributes->GetCollection())[m_Attributes->GetCountCollection()].SetDataType(type);
//		m_Attributes->IncreaseCountCollection();
//		return DLMS_ERROR_CODE_OK;
//	}
//}

//DLMS_ACCESS_MODE CGXDLMSObject::GetAccess(signed char index)
//{
//	//LN is read only.
//	if (index == 1)
//	{
//		return DLMS_ACCESS_MODE_READ;
//	}
//	else {
//		if (m_Attributes != nullptr) {
//			for (unsigned char i = 0; i < m_Attributes->GetCountCollection(); ++i) {
//				if (index == (m_Attributes->GetCollection())[i].GetIndex()) {
//					return (m_Attributes->GetCollection())[i].GetAccess();
//				}
//			}
//		}
//	}
//	return DLMS_ACCESS_MODE_READ;
//}
//
//// Set attribute access.
//int CGXDLMSObject::SetAccess(signed char index, DLMS_ACCESS_MODE access)
//{
//	if (index == 1 && access != DLMS_ACCESS_MODE_READ) {
//		return DLMS_ERROR_CODE_INVALID_PARAMETER;
//	}
//	else {
//		if (m_Attributes == nullptr) {
//			m_Attributes = new CGXAttributeCollection(this->GetAttributeCount());
//		}
//		for (unsigned char i = 0; i < m_Attributes->GetCountCollection(); ++i) {
//			if (index == (m_Attributes->GetCollection())[i].GetIndex()) {
//				(m_Attributes->GetCollection())[i].SetAccess(access);
//				return DLMS_ERROR_CODE_OK;
//			}
//		}
//		(m_Attributes->GetCollection())[m_Attributes->GetCountCollection()].SetIndex(index);
//		(m_Attributes->GetCollection())[m_Attributes->GetCountCollection()].SetAccess(access);
//		m_Attributes->IncreaseCountCollection();
//		return DLMS_ERROR_CODE_OK;
//	}
//}
//
//DLMS_METHOD_ACCESS_MODE CGXDLMSObject::GetMethodAccess(signed char index)
//{
//	if (m_MethodAttributes != nullptr) {
//		for (unsigned char i = 0; i < m_MethodAttributes->GetCountCollection(); ++i) {
//			if (index == (m_MethodAttributes->GetCollection())[i].GetIndex()) {
//				return (m_MethodAttributes->GetCollection())[i].GetMethodAccess();
//			}
//		}
//	}
//	return DLMS_METHOD_ACCESS_MODE_NONE;
//}
//
//int CGXDLMSObject::SetMethodAccess(signed char index, DLMS_METHOD_ACCESS_MODE access)
//{
//	/*if (m_MethodAttributes == nullptr) {
//		m_MethodAttributes = new CGXAttributeCollection(this->GetMethodCount());
//	}
//	for (unsigned char i = 0; i < m_MethodAttributes->GetCountCollection(); ++i) {
//		if (index == (m_MethodAttributes->GetCollection())[i].GetIndex()) {
//			(m_MethodAttributes->GetCollection())[i].SetMethodAccess(access);
//			return DLMS_ERROR_CODE_OK;
//		}
//	}
//	(m_MethodAttributes->GetCollection())[m_MethodAttributes->GetCountCollection()].SetIndex(index);
//	(m_MethodAttributes->GetCollection())[m_MethodAttributes->GetCountCollection()].SetMethodAccess(access);
//	m_MethodAttributes->IncreaseCountCollection();*/
//	return DLMS_ERROR_CODE_OK;
//}

//int CGXDLMSObject::GetUIDataType(signed char index, DLMS_DATA_TYPE& type)
//{
//	/*if (index == 0)
//	{
//		return DLMS_ERROR_CODE_INVALID_PARAMETER;
//	}
//	if (index == 1) {
//		type = DLMS_DATA_TYPE_OCTET_STRING;
//	}
//	else {
//		if (m_Attributes != nullptr) {
//			for (unsigned char i = 0; i < m_Attributes->GetCountCollection(); ++i) {
//				if (index == (m_Attributes->GetCollection())[i].GetIndex()) {
//					type = (m_Attributes->GetCollection())[i].GetUIDataType();
//					return DLMS_ERROR_CODE_OK;
//				}
//			}
//		}
//		else {
//			type = DLMS_DATA_TYPE_NONE;
//		}
//	}*/
//	return DLMS_ERROR_CODE_OK;
//}
//
//int CGXDLMSObject::SetUIDataType(signed char index, DLMS_DATA_TYPE type)
//{
//	//if (index == 1 && type != DLMS_DATA_TYPE_OCTET_STRING) {
//	//	return DLMS_ERROR_CODE_INVALID_PARAMETER;
//	//}
//	//else {
//	//	if (m_Attributes == nullptr) {
//	//		m_Attributes = new CGXAttributeCollection(this->GetAttributeCount());
//	//	}
//	//	for (unsigned char i = 0; i < m_Attributes->GetCountCollection(); ++i) {
//	//		if (index == (m_Attributes->GetCollection())[i].GetIndex()) {
//	//			(m_Attributes->GetCollection())[i].SetUIDataType(type);
//	//			return DLMS_ERROR_CODE_OK;
//	//		}
//	//	}
//	//	(m_Attributes->GetCollection())[m_Attributes->GetCountCollection()].SetIndex(index);
//	//	(m_Attributes->GetCollection())[m_Attributes->GetCountCollection()].SetUIDataType(type);
//	//	m_Attributes->IncreaseCountCollection();
//	//	return DLMS_ERROR_CODE_OK;
//	//}
//}

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

//CGXAttributeCollection* CGXDLMSObject::GetAttributes()
//{
//    return m_Attributes;
//}
//
//CGXAttributeCollection* CGXDLMSObject::GetMethodAttributes()
//{
//    return m_MethodAttributes;
//}

void CGXDLMSObject::SetAttributeCount(unsigned char count) {
	/*if (m_Attributes != nullptr) {
		delete[] m_Attributes;
	}
	m_Attributes = new CGXAttributeCollection(count);*/
}

void CGXDLMSObject::SetMethodCount(unsigned char count) {
	/*if (m_MethodAttributes != nullptr) {
		delete[] m_MethodAttributes;
	}
	m_MethodAttributes = new CGXAttributeCollection(count);*/
}

//bool CGXDLMSObject::IsRead(int index)
//{
//	return 0;
//}
//
//bool CGXDLMSObject::CanRead(int index)
//{
//    return GetAccess(index) != DLMS_ACCESS_MODE_NONE;
//}