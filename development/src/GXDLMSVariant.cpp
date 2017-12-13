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
#include "../include/errorcodes.h"
#include "../include/GXHelpers.h"

#include "Helper\Helper.h"


CArtVariant::CArtVariant() {
	byteArr = NULL;
	size = 0;
	position = 0;
	capacity = 0;
}

CArtVariant::CArtVariant(unsigned char*& buff, unsigned long& size_buff) {
	byteArr = buff;
	size = size_buff;
	capacity = size_buff;
	position = 0;
	buff = nullptr;
	size_buff = 0;
}

CArtVariant::CArtVariant(const CArtVariant& value) {
		size = value.size;
		capacity = size;
		byteArr = (unsigned char*)malloc(size);
		memcpy(byteArr, value.byteArr, size);
		position = 0;
}

CArtVariant& CArtVariant::operator=(CArtVariant& value) {
	if (this != &value) {
		if (byteArr != NULL) {
			free(byteArr);
		}
		byteArr = value.byteArr;
		size = value.size;
		position = value.position;
		capacity = value.capacity;
		value.byteArr = nullptr;
		value.size = 0;
		value.position = 0;
		value.capacity = 0;
	}
	return *this;
}

CArtVariant& CArtVariant::operator=(CGXByteBuffer& value) {
	if (this->byteArr != value.GetData()) {
		if (byteArr != NULL) {
			free(byteArr);
		}
		byteArr = value.GetData();
		size = value.GetSize();
		position = value.GetPosition();
		capacity = value.Capacity();
		value.GetData() = nullptr;
		value.Capacity(0);
	}
	else {
		value.GetData() = nullptr;
		value.Capacity(0);
	}
	return *this;
}

void CArtVariant::Set(unsigned char* buff, unsigned long size_buff) {
	if (size + size_buff > capacity) {
		unsigned char* tmp_ptr = (unsigned char*)malloc(size + size_buff);
		if (tmp_ptr != NULL) {
			memcpy(tmp_ptr, byteArr, size);
			free(byteArr);
			byteArr = tmp_ptr;
			tmp_ptr = NULL;
			capacity = size + size_buff;
			memcpy(byteArr + size, buff, size_buff);
			size += size_buff;
		}
	}
	else{
		memcpy(byteArr + size, buff, size_buff);
		size += size_buff;
	}
}

unsigned char*  CArtVariant::GetCurPtr() {
	return (byteArr + position);
}

bool CArtVariant::Reserve(unsigned long new_size) {
	if (new_size > capacity) {
		unsigned char* tmp_ptr = (unsigned char*)malloc(new_size);
		if (tmp_ptr != NULL) {
			memcpy(tmp_ptr, byteArr, size);
			free(byteArr);
			byteArr = tmp_ptr;
			tmp_ptr = NULL;
			capacity = new_size;
		}
		return true;
	}
	else {
		if (new_size < size) {
			unsigned char* tmp_ptr = (unsigned char*)malloc(new_size);
			if (tmp_ptr != NULL) {
				memcpy(tmp_ptr, byteArr, new_size);
				free(byteArr);
				byteArr = tmp_ptr;
				tmp_ptr = NULL;
				capacity = new_size;
				size = new_size;
			}
			return true;
		}
		else {
			if (byteArr != NULL) {
				free(byteArr);
			}
			byteArr = NULL;
			size = 0;
			capacity = 0;
			position = 0;
		}
	}
	return false;
}

bool  CArtVariant::IncreasePosition(unsigned short diff) {
	if (position + diff <= size) {
		position += diff;
		return true;
	}
	return false;
}

bool CArtVariant::DecreasePosition(unsigned short diff) {
	if ((long long)position - diff < 0) {
		return false;
	}
	position -= diff;
	return true;
}

bool CArtVariant::SetPosition(unsigned long pos) {
	if (pos <= size) {
		position = pos;
		return true;
	}
	return false;
}

void CArtVariant::GetVar(VarInfo& v_info) {
	if (byteArr != NULL && position + 1 < size) {
		v_info.vt = (DLMS_DATA_TYPE)*(byteArr + position);
		++position;
		int8_t type_size = spodesSizeof(v_info.vt);
		switch (type_size) {
		case -1: {
			GetObjectCount(v_info.size);
			break;
		}
		case -2: {
			v_info.size = 0;
			break;
		}
		default: {
			v_info.size = type_size;
			break;
		}
		}
	}
	else {
		v_info.vt = DLMS_DATA_TYPE_NONE;
		v_info.size = 0;
	}
}

unsigned char CArtVariant::ChangeType(unsigned long src_size, DLMS_DATA_TYPE type, CArtVariant& new_value) {
	int8_t type_size = spodesSizeof(type);
	switch (type_size) {
	case -2: {
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	case -1: {
			Reserve(src_size + 2);
			SetUInt8(type);
			SetObjectCount(src_size);
			new_value.Set(GetCurPtr(), src_size);
			return DLMS_ERROR_CODE_OK;
	}
	case 0: {
		return DLMS_ERROR_CODE_UNMATCH_TYPE;
	}
	default: {
		Reserve(type_size + 1);
		SetUInt8(type);
		new_value.Set(GetCurPtr(), type_size);
		return DLMS_ERROR_CODE_OK;
	}
	}
}

unsigned char CArtVariant::GetUInt(unsigned char size, unsigned long long* value) {
	unsigned char ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
	switch (size) {
	case 1: {
		unsigned char tmp;
		ret = GetUInt8(&tmp);
		*value = tmp;
		return ret;
	}
	case 2: {
		unsigned short tmp;
		ret = GetUInt16(&tmp);
		*value = tmp;
		return ret;
	}
	case 4: {
		unsigned long tmp;
		ret = GetUInt32(&tmp);
		*value = tmp;
		return ret;
	}
	case 8: {
		ret = GetUInt64(value);
		return ret;
	}
	}
	return ret;
}

unsigned char CArtVariant::GetUInt8(unsigned char* value) {
	if (position >= size)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = byteArr[position];
	++position;
	return 0;
}

unsigned char CArtVariant::GetUInt16(unsigned short* value) {
	if (position + 2 > size)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = (unsigned short)(byteArr[position] & 0xFF) << 8 | 
			 (unsigned short)byteArr[position + 1] & 0xFF;
	position += 2;
	return 0;
}

unsigned char CArtVariant::GetUInt32(unsigned long* value) {
	if (position + 4 > size)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = (unsigned long)byteArr[position] << 24 |
			 (unsigned long)byteArr[position + 1] << 16 |
			 (unsigned long)byteArr[position + 2] << 8 |
			 (unsigned long)byteArr[position + 3];
	position += 4;
	return 0;
}

unsigned char CArtVariant::GetUInt64(unsigned long long* value) {
	if (position + 8 > size)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	*value = (unsigned long long)byteArr[position] << 56 |
			 (unsigned long long) byteArr[position + 1] << 48 |
			 (unsigned long long) byteArr[position + 2] << 40 |
			 (unsigned long long) byteArr[position + 3] << 32 |
			 (unsigned long long) byteArr[position + 4] << 24 |
			 (unsigned long long) byteArr[position + 5] << 16 |
			 (unsigned long long) byteArr[position + 6] << 8 |
			 (unsigned long long) byteArr[position + 7];
	return 0;
}

unsigned char CArtVariant::GetReal(unsigned char size, double& value) {
	unsigned char ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
	switch (size) {
	case 4: {
		float tmp;
		ret = GetFloat(&tmp);
		value = tmp;
		return ret;
	}
	case 8: {
		return GetDouble(&value);
	}
	}
	return ret;
}

unsigned char CArtVariant::GetFloat(float* value) {
	if (position + 4 > size)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	typedef union
	{
		float value;
		char b[sizeof(float)];
	} HELPER;
	HELPER tmp;
	tmp.b[3] = byteArr[position];
	tmp.b[2] = byteArr[position + 1];
	tmp.b[1] = byteArr[position + 2];
	tmp.b[0] = byteArr[position + 3];
	*value = tmp.value;
	position += 4;
	return 0;
}

unsigned char CArtVariant::GetDouble(double* value) {
	if (position + 8 > size)
	{
		return DLMS_ERROR_CODE_OUTOFMEMORY;
	}
	typedef union
	{
		double value;
		char b[sizeof(double)];
	} HELPER;
	HELPER tmp;
	tmp.b[7] = byteArr[position];
	tmp.b[6] = byteArr[position + 1];
	tmp.b[5] = byteArr[position + 2];
	tmp.b[4] = byteArr[position + 3];
	tmp.b[3] = byteArr[position + 4];
	tmp.b[2] = byteArr[position + 5];
	tmp.b[1] = byteArr[position + 6];
	tmp.b[0] = byteArr[position + 7];
	*value = tmp.value;
	position += 8;
	return 0;
}

void CArtVariant::SetUInt8(unsigned char item)
{
	if (size == capacity) {
		//++capacity;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);	
		Reserve(size + 1);
	}
	byteArr[size] = item;
	++size;
}

void CArtVariant::SetUInt16(unsigned short item)
{
	if (size + 2 > capacity) {
		//capacity = size + 2;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(size + 2);
	}
	byteArr[size] = (item >> 8) & 0xFF;
	byteArr[size + 1] = item & 0xFF;
	size += 2;
}

void CArtVariant::SetUInt32( unsigned long item)
{
	if (size + 4 > capacity) {
		//capacity = size + 4;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);	
		Reserve(size + 4);
	}
	byteArr[size] = (item >> 24) & 0xFF;
	byteArr[size + 1] = (item >> 16) & 0xFF;
	byteArr[size + 2] = (item >> 8) & 0xFF;
	byteArr[size + 3] = item & 0xFF;
	size += 4;
}

void CArtVariant::SetUInt64(unsigned long long item)
{
	if (size + 8 > capacity) {
		//capacity = size + 8;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(size + 8);
	}
	byteArr[size]	  = (item >> 56) & 0xFF;
	byteArr[size + 1] = (item >> 48) & 0xFF;
	byteArr[size + 2] = (item >> 40) & 0xFF;
	byteArr[size + 3] = (item >> 32) & 0xFF;
	byteArr[size + 4] = (item >> 24) & 0xFF;
	byteArr[size + 5] = (item >> 16) & 0xFF;
	byteArr[size + 6] = (item >> 8) & 0xFF;
	byteArr[size + 7] = item & 0xFF;
	size += 8;
}

void CArtVariant::SetUInt8(unsigned long index, unsigned char item) {
	if (index + 1 > capacity) {
		//capacity = index + 1;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(index + 1);
	}
	byteArr[index] = item;
	if (size < index + 1) {
		Zero(size, index - size);
		size = capacity;
	}
}

void CArtVariant::SetUInt16(unsigned long index, unsigned short item) {
	if (index + 2 > capacity) {
		//capacity = index + 2;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(index + 2);
	}
	byteArr[index] = (item >> 8) & 0xFF;
	byteArr[index + 1] = item & 0xFF;
	if (size < index + 2) {
		Zero(size, index - size);
		size = capacity;
	}
}

void CArtVariant::SetUInt32(unsigned long index, unsigned long item) {
	if (index + 4 > capacity) {
		//capacity = index + 4;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(index + 4);
	}
	byteArr[index] = (item >> 24) & 0xFF;
	byteArr[index + 1] = (item >> 16) & 0xFF;
	byteArr[index + 2] = (item >> 8) & 0xFF;
	byteArr[index + 3] = item & 0xFF;
	if (size < index + 4) {
		Zero(size, index - size);
		size = capacity;
	}
}

void CArtVariant::SetUInt64(unsigned long index, unsigned long long item) {
	if (index + 8 > capacity) {
		//capacity = index + 8;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(index + 8);
	}
	byteArr[index] = (item >> 56) & 0xFF;
	byteArr[index + 1] = (item >> 48) & 0xFF;
	byteArr[index + 2] = (item >> 40) & 0xFF;
	byteArr[index + 3] = (item >> 32) & 0xFF;
	byteArr[index + 4] = (item >> 24) & 0xFF;
	byteArr[index + 5] = (item >> 16) & 0xFF;
	byteArr[index + 6] = (item >> 8) & 0xFF;
	byteArr[index + 7] = item & 0xFF;
	if (size < index + 8) {
		Zero(size, index - size);
		size = capacity;
	}
}

void CArtVariant::SetFloat(float item) {
	typedef union
	{
		float value;
		char b[sizeof(float)];
	} HELPER;

	HELPER tmp;
	tmp.value = item;
	if (size + 4 > capacity)
	{
		//capacity = size + 4;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(size + 4);
	}
	byteArr[size] = tmp.b[3];
	byteArr[size + 1] = tmp.b[2];
	byteArr[size + 2] = tmp.b[1];
	byteArr[size + 3] = tmp.b[0];
	size += 4;
}

void CArtVariant::SetDouble(double item) {
	typedef union
	{
		double value;
		char b[sizeof(double)];
	} HELPER;

	HELPER tmp;
	tmp.value = item;
	if (size + 8 > capacity)
	{
		//capacity = size + 8;
		//byteArr = (unsigned char*)realloc(byteArr, capacity);
		Reserve(size + 8);
	}
	byteArr[size]	  = tmp.b[7];
	byteArr[size + 1] = tmp.b[6];
	byteArr[size + 2] = tmp.b[5];
	byteArr[size + 3] = tmp.b[4];
	byteArr[size + 4] = tmp.b[3];
	byteArr[size + 5] = tmp.b[2];
	byteArr[size + 6] = tmp.b[1];
	byteArr[size + 7] = tmp.b[0];
	size += 8;
}

unsigned char CArtVariant::Zero(unsigned short index, unsigned short count) {
	if (index + count > capacity) {
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	memset(byteArr + index, 0, count);
	if (index + count > size) {
		size = index + count;
	}
		return DLMS_ERROR_CODE_OK;
}

unsigned char CArtVariant::GetObjectCount(unsigned long& count)
{
	int ret;
	unsigned char cnt;
	if ((ret = GetUInt8(&cnt)) != 0)
	{
		return ret;
	}
	switch (cnt) {
	case 0x81: {
		if ((ret = GetUInt8(&cnt)) != 0)
		{
			return ret;
		}
		count = cnt;
		return DLMS_ERROR_CODE_OK;
	}
	case 0x82: {
		unsigned short tmp;
		if ((ret = GetUInt16(&tmp)) != 0)
		{
			return ret;
		}
		count = tmp;
		return DLMS_ERROR_CODE_OK;
	}
	case 0x84: {
		unsigned long tmp;
		if ((ret = GetUInt32(&tmp)) != 0)
		{
			return ret;
		}
		count = tmp;
		return DLMS_ERROR_CODE_OK;
	}
	default: {
		count = cnt;
		return DLMS_ERROR_CODE_OK;
	}
	}	
}

void CArtVariant::SetObjectCount(unsigned long count)
{
	if (count < 0x80)
	{
		SetUInt8((unsigned char)count);
	}
	else if (count < 0x100)
	{
		SetUInt8(0x81);
		SetUInt8((unsigned char)count);
	}
	else if (count < 0x10000)
	{
		SetUInt8(0x82);
		SetUInt16((unsigned short)count);
	}
	else
	{
		SetUInt8(0x84);
		SetUInt32(count);
	}
}

void CArtVariant::Clear() {
	if (byteArr != NULL) {
		free(byteArr);
		byteArr = NULL;
	}
	size = 0;
	position = 0;
	capacity = 0;
}

CArtVariant::~CArtVariant() {
	Clear();
}






int CGXDLMSVariant::Convert(CGXDLMSVariant* item, DLMS_DATA_TYPE type)
{
    if (item->vt == type)
    {
        return DLMS_ERROR_CODE_OK;
    }
    CGXDLMSVariant tmp(item);
    if (type == DLMS_DATA_TYPE_STRING)
    {
        item->Clear();
        if (tmp.vt == DLMS_DATA_TYPE_ARRAY || tmp.vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            std::string str = "{";
            for (std::vector<CGXDLMSVariant>::iterator it = tmp.Arr.begin(); it != tmp.Arr.end(); ++it)
            {
                str += it->ToString();
                if (it != tmp.Arr.end())
                {
                    str += ", ";
                }
            }
            str += "}";
            item->strVal = str;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_BOOLEAN)
        {
            if (tmp.boolVal == 0)
            {
                item->strVal = "False";
            }
            else
            {
                item->strVal = "True";
            }
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        char buff[250];
        if (tmp.vt == DLMS_DATA_TYPE_INT32)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%ld", tmp.lVal);
#else
            sprintf(buff, "%ld", tmp.lVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_UINT32)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%lu", tmp.ulVal);
#else
            sprintf(buff, "%lu", tmp.ulVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_INT8)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%d", tmp.cVal);
#else
            sprintf(buff, "%d", tmp.cVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_INT16)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%d", tmp.iVal);
#else
            sprintf(buff, "%d", tmp.iVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_UINT8)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%d", tmp.bVal);
#else
            sprintf(buff, "%d", tmp.bVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_UINT16)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%d", tmp.uiVal);
#else
            sprintf(buff, "%d", tmp.uiVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_INT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%lld", tmp.llVal);
#else
            sprintf(buff, "%I64d", tmp.llVal);
#endif

#else
            sprintf(buff, "%lld", tmp.llVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_UINT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%llu", tmp.ullVal);
#else
            sprintf(buff, "%I64u", tmp.llVal);
#endif
#else
            sprintf(buff, "%llu", tmp.ullVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_ENUM)
        {
#if _MSC_VER > 1000
            sprintf_s(buff, 250, "%d", tmp.bVal);
#else
            sprintf(buff, "%d", tmp.bVal);
#endif
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_FLOAT32)
        {
            snprintf(buff, 250, "%f", tmp.fltVal);
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_FLOAT64)
        {
            snprintf(buff, 250, "%lf", tmp.dblVal);
            item->strVal = buff;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_BIT_STRING)
        {
            //TODO:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
        }
        if (tmp.vt == DLMS_DATA_TYPE_DATETIME)
        {
            item->strVal = tmp.dateTime.ToString();
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (tmp.vt == DLMS_DATA_TYPE_OCTET_STRING)
        {
            unsigned char ch;
            char buff[4];
            for (int pos = 0; pos != tmp.size; ++pos)
            {
                if (pos != 0)
                {
                    item->strVal.append(".");
                }
                ch = tmp.byteArr[pos];
#if _MSC_VER > 1000
                sprintf_s(buff, 4, "%d", ch);
#else
                sprintf(buff, "%d", ch);
#endif
                item->strVal.append(buff);
            }
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
    }
    if (item->vt == DLMS_DATA_TYPE_STRING)
    {
        item->Clear();
        if (type == DLMS_DATA_TYPE_BOOLEAN)
        {
            item->boolVal = tmp.strVal.compare("False") == 0 ? 0 : 1;
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT32)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%ld", &item->lVal);
#else
            sscanf(tmp.strVal.c_str(), "%ld", &item->lVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT32)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%lu", &item->ulVal);
#else
            sscanf(tmp.strVal.c_str(), "%lu", &item->ulVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT8)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%c", &item->cVal, 1);
#else
            sscanf(tmp.strVal.c_str(), "%c", &item->cVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT16)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%hd", &item->iVal);
#else
            sscanf(tmp.strVal.c_str(), "%hd", &item->iVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT8)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%hhu", &item->bVal);
#else
            int value;
            sscanf(tmp.strVal.c_str(), "%d", &value);
            item->bVal = value & 0xFF;
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT16)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%hu", &item->uiVal);
#else
            int value;
            sscanf(tmp.strVal.c_str(), "%d", &value);
            item->uiVal = value & 0xFFFF;
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_INT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%lld", &item->llVal);
#else
            sscanf(tmp.strVal.c_str(), "%I64d", &item->llVal);
#endif
#else
            sscanf(tmp.strVal.c_str(), "%lld", &item->llVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_UINT64)
        {
#if defined(_WIN32) || defined(_WIN64)//Windows
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%llu", &item->ullVal);
#else
            sscanf(tmp.strVal.c_str(), "%I64u", &item->ullVal);
#endif
#else
            sscanf(tmp.strVal.c_str(), "%llu", &item->ullVal);
#endif

#if _MSC_VER > 1000
#else
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_ENUM)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%hhu", &item->bVal);
#else
            int value;
            sscanf(tmp.strVal.c_str(), "%d", &value);
            item->bVal = value & 0xFF;
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_FLOAT32)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%f", &item->fltVal);
#else
            sscanf(tmp.strVal.c_str(), "%f", &item->fltVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_FLOAT64)
        {
#if _MSC_VER > 1000
            sscanf_s(tmp.strVal.c_str(), "%lf", &item->dblVal);
#else
            sscanf(tmp.strVal.c_str(), "%lf", &item->dblVal);
#endif
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        if (type == DLMS_DATA_TYPE_OCTET_STRING)
        {
            CGXByteBuffer tmp2;
            GXHelpers::HexToBytes(tmp.strVal, tmp2);
            item->Add(tmp2.GetData(), tmp2.GetSize());
            item->vt = type;
            return DLMS_ERROR_CODE_OK;
        }
        return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
    }
    int fromSize = tmp.GetSize();
    int toSize = GetSize(type);
    //If we try to change bigger valut to smaller check that value is not too big.
    //Example Int16 to Int8.
    if (fromSize > toSize)
    {
        unsigned char* pValue = &tmp.bVal;
        for (int pos = toSize; pos != fromSize; ++pos)
        {
            if (pValue[pos] != 0)
            {
                return DLMS_ERROR_CODE_INVALID_PARAMETER;
            }
        }
    }
    item->Clear();
    if (fromSize > toSize)
    {
        memcpy(&item->bVal, &tmp.bVal, toSize);
    }
    else
    {
        memset(&item->bVal, 0, toSize);
        memcpy(&item->bVal, &tmp.bVal, fromSize);
    }
    item->vt = type;
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSVariant::Clear()
{
    Arr.clear();
    strVal.clear();
    if (vt == DLMS_DATA_TYPE_OCTET_STRING && byteArr != NULL)
    {
        if (size == 0)
        {
            assert(size != 0);
        }
        std::free(byteArr);
        byteArr = NULL;
        size = 0;
    }
    vt = DLMS_DATA_TYPE_NONE;
    this->byteArr = NULL;
    size = 0;
}

CGXDLMSVariant::CGXDLMSVariant()
{
    size = 0;
    byteArr = NULL;
    Clear();
}

CGXDLMSVariant::~CGXDLMSVariant()
{
    Clear();
}
CGXDLMSVariant::CGXDLMSVariant(CGXDLMSVariant* value)
{
    byteArr = NULL;
    vt = value->vt;
    if (vt == DLMS_DATA_TYPE_NONE)
    {
        return;
    }
    else if (vt == DLMS_DATA_TYPE_STRING ||
        vt == DLMS_DATA_TYPE_BIT_STRING)
    {
        this->strVal.append(value->strVal);
    }
    else if (vt == DLMS_DATA_TYPE_DATETIME ||
        vt == DLMS_DATA_TYPE_DATE ||
        vt == DLMS_DATA_TYPE_TIME)
    {
        this->dateTime = value->dateTime;
    }
    else if (vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        size = value->size;
        if (size != 0)
        {
            byteArr = (unsigned char*)malloc(size);
            memcpy(byteArr, value->byteArr, size);
        }
    }
    else if (vt == DLMS_DATA_TYPE_ARRAY || vt == DLMS_DATA_TYPE_STRUCTURE)
    {
        for (std::vector<CGXDLMSVariant>::iterator it = value->Arr.begin(); it != value->Arr.end(); ++it)
        {
            Arr.push_back(*it);
        }
    }
    else
    {
        int size = value->GetSize();
        if (size > 0)
        {
            memcpy(&bVal, &value->bVal, size);
        }
        else
        {
            assert(0);
        }
    }
}

CGXDLMSVariant::CGXDLMSVariant(float value)
{
    vt = DLMS_DATA_TYPE_FLOAT32;
    fltVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(double value)
{
    vt = DLMS_DATA_TYPE_FLOAT64;
    dblVal = value;
}


CGXDLMSVariant::CGXDLMSVariant(unsigned long long value)
{
    vt = DLMS_DATA_TYPE_UINT64;
    ullVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(long long value)
{
    vt = DLMS_DATA_TYPE_INT64;
    llVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(bool value)
{
    vt = DLMS_DATA_TYPE_BOOLEAN;
    boolVal = value;
}


CGXDLMSVariant::CGXDLMSVariant(char value)
{
    vt = DLMS_DATA_TYPE_INT8;
    cVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(short value)
{
    vt = DLMS_DATA_TYPE_INT16;
    iVal = value;
}


CGXDLMSVariant::CGXDLMSVariant(int value)
{
    vt = DLMS_DATA_TYPE_INT32;
    lVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(long value)
{
    vt = DLMS_DATA_TYPE_INT32;
    lVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(struct tm value)
{
    vt = DLMS_DATA_TYPE_DATETIME;
    dateTime.SetValue(value);
}

CGXDLMSVariant::CGXDLMSVariant(CGXByteBuffer& value)
{
    vt = DLMS_DATA_TYPE_OCTET_STRING;
    size = (unsigned short)value.GetSize();
    if (size != 0)
    {
        byteArr = (unsigned char*)malloc(size);
        memcpy(byteArr, value.GetData(), size);
    }
    else
    {
        byteArr = NULL;
    }
}

CGXDLMSVariant::CGXDLMSVariant(CGXDate& value)
{
    vt = DLMS_DATA_TYPE_DATE;
    dateTime = value;
}

CGXDLMSVariant::CGXDLMSVariant(CGXTime& value)
{
    vt = DLMS_DATA_TYPE_TIME;
    dateTime = value;
}

CGXDLMSVariant::CGXDLMSVariant(CGXDateTime& value)
{
    vt = DLMS_DATA_TYPE_DATETIME;
    dateTime = value;
}

CGXDLMSVariant::CGXDLMSVariant(unsigned char value)
{
    vt = DLMS_DATA_TYPE_UINT8;
    bVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(unsigned short value)
{
    vt = DLMS_DATA_TYPE_UINT16;
    uiVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(unsigned long value)
{
    vt = DLMS_DATA_TYPE_UINT32;
    ulVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(std::string value)
{
    vt = DLMS_DATA_TYPE_STRING;
    strVal = value;
}

CGXDLMSVariant::CGXDLMSVariant(unsigned char* value, int count)
{
    vt = DLMS_DATA_TYPE_OCTET_STRING;
    size = count;
    if (size != 0)
    {
        byteArr = (unsigned char*)malloc(size);
        memcpy(byteArr, value, size);
    }
    else
    {
        byteArr = NULL;
    }
}

CGXDLMSVariant::CGXDLMSVariant(const CGXDLMSVariant& value)
{
    //If Octect String, copy byte buffer.
    if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        vt = value.vt;
        size = value.size;
        if (size != 0)
        {
            byteArr = (unsigned char*)malloc(size);
            memcpy(byteArr, value.byteArr, size);
        }
        else
        {
            byteArr = NULL;
        }
    }
    else
    {
        *((dlmsVARIANT*)this) = value;
    }
}

CGXDLMSVariant& CGXDLMSVariant::operator=(const CGXDLMSVariant& value)
{
    Clear();
    //If Octect String, copy byte buffer.
    if (value.vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        vt = value.vt;
        size = value.size;
        if (size != 0)
        {
            byteArr = (unsigned char*)malloc(size);
            memcpy(byteArr, value.byteArr, size);
        }
    }
    else
    {
        *((dlmsVARIANT*)this) = value;
    }
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(CGXByteBuffer& value)
{
    Clear();
    vt = DLMS_DATA_TYPE_OCTET_STRING;
    size = (unsigned short)value.GetSize();
    if (size != 0)
    {
        byteArr = (unsigned char*)malloc(size);
        memcpy(byteArr, value.GetData(), size);
    }
    return *this;
}

CGXDLMSVariant::CGXDLMSVariant(const char* value)
{
    vt = DLMS_DATA_TYPE_STRING;
    strVal.append(value);
}

CGXDLMSVariant::CGXDLMSVariant(unsigned char* pValue, int count, DLMS_DATA_TYPE type)
{
    assert(count > -1);
    byteArr = NULL;
    size = count;
    if (size != 0)
    {
        byteArr = (unsigned char*)malloc(count);
        memcpy(byteArr, pValue, count);
    }
    vt = type;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(std::string value)
{
    Clear();
    vt = DLMS_DATA_TYPE_STRING;
    strVal.append(value);
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(const char* value)
{
    Clear();
    vt = DLMS_DATA_TYPE_STRING;
    strVal.append(value);
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(float value)
{
    Clear();
    vt = DLMS_DATA_TYPE_FLOAT32;
    fltVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(double value)
{
    Clear();
    vt = DLMS_DATA_TYPE_FLOAT64;
    dblVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(unsigned long long value)
{
    Clear();
    vt = DLMS_DATA_TYPE_UINT64;
    ullVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(long long value)
{
    Clear();
    vt = DLMS_DATA_TYPE_INT64;
    llVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(const bool value)
{
    Clear();
    vt = DLMS_DATA_TYPE_BOOLEAN;
    boolVal = value;
    return *this;
}


CGXDLMSVariant& CGXDLMSVariant::operator=(char value)
{
    Clear();
    vt = DLMS_DATA_TYPE_INT8;
    cVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(short value)
{
    Clear();
    vt = DLMS_DATA_TYPE_INT16;
    iVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(int value)
{
    Clear();
    vt = DLMS_DATA_TYPE_INT32;
    lVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(long value)
{
    Clear();
    vt = DLMS_DATA_TYPE_INT32;
    lVal = value;
    return *this;
}


CGXDLMSVariant& CGXDLMSVariant::operator=(unsigned char value)
{
    Clear();
    vt = DLMS_DATA_TYPE_UINT8;
    bVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(unsigned short value)
{
    Clear();
    vt = DLMS_DATA_TYPE_UINT16;
    uiVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(unsigned long value)
{
    Clear();
    vt = DLMS_DATA_TYPE_UINT32;
    ulVal = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(struct tm value)
{
    Clear();
    vt = DLMS_DATA_TYPE_DATETIME;
    dateTime.SetValue(value);
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(CGXDate& value)
{
    Clear();
    vt = DLMS_DATA_TYPE_DATE;
    dateTime = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(CGXTime& value)
{
    Clear();
    vt = DLMS_DATA_TYPE_TIME;
    dateTime = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(CGXDateTime& value)
{
    Clear();
    vt = DLMS_DATA_TYPE_DATETIME;
    dateTime = value;
    return *this;
}

CGXDLMSVariant& CGXDLMSVariant::operator=(unsigned int value)
{
    Clear();
    vt = DLMS_DATA_TYPE_UINT32;
    ulVal = value;
    return *this;
}

void CGXDLMSVariant::Add(const unsigned char* pValue, int count)
{
    vt = DLMS_DATA_TYPE_OCTET_STRING;
    if (count != 0)
    {
        byteArr = (unsigned char*)realloc(byteArr, size + count);
        memcpy(byteArr + size, pValue, count);
        size += count;
    }
}

void CGXDLMSVariant::Add(const char* pValue, int count)
{
    vt = DLMS_DATA_TYPE_OCTET_STRING;
    if (count != 0)
    {
        byteArr = (unsigned char*)realloc(byteArr, size + count);
        memcpy(byteArr + size, pValue, count);
        size += count;
    }
}

void CGXDLMSVariant::Add(std::string value)
{
    vt = DLMS_DATA_TYPE_OCTET_STRING;
    if (value.size() != 0)
    {
        byteArr = (unsigned char*)realloc(byteArr, size + value.size());
        memcpy(byteArr + size, value.c_str(), value.size());
        size += (unsigned short)value.size();
    }
}

bool CGXDLMSVariant::Equals(CGXDLMSVariant& item)
{
    if (vt != item.vt)
    {
        return false;
    }
    int size = GetSize();
    if (size == -1 || size != item.GetSize())
    {
        return false;
    }
    if (size != 0)
    {
        return memcmp(&this->bVal, &item.bVal, size) == 0;
    }
    return true;
}

int CGXDLMSVariant::ChangeType(DLMS_DATA_TYPE newType)
{
    if (newType == vt)
    {
        return DLMS_ERROR_CODE_OK;
    }

    if (newType == DLMS_DATA_TYPE_NONE)
    {
        Clear();
        return DLMS_ERROR_CODE_OK;
    }
    if (vt == DLMS_DATA_TYPE_ARRAY && newType == DLMS_DATA_TYPE_OCTET_STRING)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (vt == DLMS_DATA_TYPE_STRING)
    {
        return Convert(this, newType);
    }
    switch (newType)
    {
    case DLMS_DATA_TYPE_STRING:
    case DLMS_DATA_TYPE_BOOLEAN:
    case DLMS_DATA_TYPE_INT32:
    case DLMS_DATA_TYPE_UINT32:
    case DLMS_DATA_TYPE_INT8:
    case DLMS_DATA_TYPE_INT16:
    case DLMS_DATA_TYPE_UINT8:
    case DLMS_DATA_TYPE_UINT16:
    case DLMS_DATA_TYPE_INT64:
    case DLMS_DATA_TYPE_UINT64:
    case DLMS_DATA_TYPE_ENUM:
    case DLMS_DATA_TYPE_FLOAT32:
    case DLMS_DATA_TYPE_FLOAT64:
        return Convert(this, newType);
        break;
    default:
        //Handled later.
        break;
    }
    CGXDLMSVariant tmp(this);
    switch (vt)
    {
    case DLMS_DATA_TYPE_BOOLEAN:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    case DLMS_DATA_TYPE_BIT_STRING:
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    case DLMS_DATA_TYPE_INT32:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT32:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_OCTET_STRING:
        switch (newType)
        {
        case DLMS_DATA_TYPE_DATETIME:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        case DLMS_DATA_TYPE_DATE:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        case DLMS_DATA_TYPE_TIME:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        switch (newType)
        {
        case DLMS_DATA_TYPE_INT32:
            break;
        case DLMS_DATA_TYPE_UINT32:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_INT8:
            break;
        case DLMS_DATA_TYPE_INT16:
            break;
        case DLMS_DATA_TYPE_UINT8:
            break;
        case DLMS_DATA_TYPE_UINT16:
            break;
        case DLMS_DATA_TYPE_INT64:
            break;
        case DLMS_DATA_TYPE_UINT64:
            break;
        case DLMS_DATA_TYPE_ENUM:
            break;
        case DLMS_DATA_TYPE_FLOAT32:
            break;
        case DLMS_DATA_TYPE_FLOAT64:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_INT8:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_INT16:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT8:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT16:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_INT64:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_UINT64:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_ENUM:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_FLOAT32:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_FLOAT64:
        switch (newType)
        {
        case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
            return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_DATETIME:
        switch (newType)
        {
        case DLMS_DATA_TYPE_OCTET_STRING:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_DATE:
            break;
        case DLMS_DATA_TYPE_TIME:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_DATE:
        switch (newType)
        {
        case DLMS_DATA_TYPE_OCTET_STRING:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_DATETIME:
            break;
        case DLMS_DATA_TYPE_DATE:
            break;
        case DLMS_DATA_TYPE_TIME:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_TIME:
        switch (newType)
        {
        case DLMS_DATA_TYPE_OCTET_STRING:
            break;
        case DLMS_DATA_TYPE_STRING:
            break;
        case DLMS_DATA_TYPE_DATETIME:
            break;
        case DLMS_DATA_TYPE_DATE:
            break;
        case DLMS_DATA_TYPE_TIME:
            break;
        default:
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
        break;
    case DLMS_DATA_TYPE_ARRAY:
    case DLMS_DATA_TYPE_STRUCTURE:
    case DLMS_DATA_TYPE_COMPACT_ARRAY:
    default:
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

//Get size in bytes.
int CGXDLMSVariant::GetSize()
{
    if (this->vt == DLMS_DATA_TYPE_STRING ||
        this->vt == DLMS_DATA_TYPE_BIT_STRING)
    {
        return (int)strVal.size();
    }
    if (this->vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        return size;
    }
    return GetSize(this->vt);
}

//Get size in bytes.
int CGXDLMSVariant::GetSize(DLMS_DATA_TYPE vt)
{
    int nSize = -1;
    switch (vt)
    {
    case DLMS_DATA_TYPE_NONE:
        nSize = 0;
        break;
    case DLMS_DATA_TYPE_BOOLEAN:
    case DLMS_DATA_TYPE_INT8:
    case DLMS_DATA_TYPE_UINT8:
    case DLMS_DATA_TYPE_ENUM:
        nSize = 1;
        break;
    case DLMS_DATA_TYPE_INT16:
    case DLMS_DATA_TYPE_UINT16:
        nSize = 2;
        break;
    case DLMS_DATA_TYPE_INT32:
    case DLMS_DATA_TYPE_UINT32:
    case DLMS_DATA_TYPE_FLOAT32:
        nSize = 4;
        break;
    case DLMS_DATA_TYPE_INT64:
    case DLMS_DATA_TYPE_UINT64:
    case DLMS_DATA_TYPE_FLOAT64:
        nSize = 8;
        break;
    case DLMS_DATA_TYPE_BIT_STRING:
        break;
    case DLMS_DATA_TYPE_OCTET_STRING:
        break;
    case DLMS_DATA_TYPE_STRING:
    case DLMS_DATA_TYPE_STRING_UTF8:
        nSize = -1;
        break;
    case DLMS_DATA_TYPE_BINARY_CODED_DESIMAL:
        break;
    case DLMS_DATA_TYPE_DATETIME:
        nSize = 12;
        break;
    case DLMS_DATA_TYPE_DATE:
        break;
    case DLMS_DATA_TYPE_TIME:
        break;
    case DLMS_DATA_TYPE_ARRAY:
        break;
    case DLMS_DATA_TYPE_STRUCTURE:
        break;
    case DLMS_DATA_TYPE_COMPACT_ARRAY:
        break;
    }
    return nSize;
}

std::string CGXDLMSVariant::ToString()
{
    CGXDLMSVariant tmp(this);
    tmp.ChangeType(DLMS_DATA_TYPE_STRING);
    if (tmp.strVal.length() == 0)
    {
        return "";
    }
    return tmp.strVal.c_str();
}

int CGXDLMSVariant::ToInteger()
{
    if (vt == DLMS_DATA_TYPE_NONE)
    {
        return 0;
    }

    if (vt == DLMS_DATA_TYPE_BOOLEAN)
    {
        return boolVal ? 1 : 0;
    }
    if (vt == DLMS_DATA_TYPE_INT32)
    {
        return lVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT32)
    {
        return ulVal;
    }
    if (vt == DLMS_DATA_TYPE_BINARY_CODED_DESIMAL)
    {
        assert(0);
    }
    if (vt == DLMS_DATA_TYPE_STRING_UTF8)
    {
        //TODO:
        assert(0);
    }
    if (vt == DLMS_DATA_TYPE_INT8)
    {
        return cVal;
    }

    if (vt == DLMS_DATA_TYPE_INT16)
    {
        return iVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT8)
    {
        return bVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT16)
    {
        return uiVal;
    }
    if (vt == DLMS_DATA_TYPE_INT64)
    {
        //TODO:
        assert(0);
    }
    if (vt == DLMS_DATA_TYPE_UINT64)
    {
        //TODO:
        assert(0);
    }
    if (vt == DLMS_DATA_TYPE_ENUM)
    {
        return bVal;
    }
    if (vt == DLMS_DATA_TYPE_FLOAT32)
    {
        return (int)fltVal;
    }
    if (vt == DLMS_DATA_TYPE_FLOAT64)
    {
        return (int)dblVal;
    }
    if (vt == DLMS_DATA_TYPE_STRING)
    {
        int val = 0;
#if _MSC_VER > 1000
        if (sscanf_s(strVal.c_str(), "%d", &val) == -1)
#else
        if (sscanf(strVal.c_str(), "%d", &val) == -1)
#endif
        {
            assert(0);
        }
        return val;
    }
    assert(0);
    return 0;
}

double CGXDLMSVariant::ToDouble()
{
    if (vt == DLMS_DATA_TYPE_NONE)
    {
        return 0;
    }

    if (vt == DLMS_DATA_TYPE_BOOLEAN)
    {
        return boolVal ? 1 : 0;
    }
    if (vt == DLMS_DATA_TYPE_INT32)
    {
        return lVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT32)
    {
        return ulVal;
    }
    if (vt == DLMS_DATA_TYPE_BINARY_CODED_DESIMAL)
    {
        assert(0);
    }
    if (vt == DLMS_DATA_TYPE_STRING_UTF8)
    {
        assert(0);
    }
    if (vt == DLMS_DATA_TYPE_INT8)
    {
        return cVal;
    }

    if (vt == DLMS_DATA_TYPE_INT16)
    {
        return iVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT8)
    {
        return bVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT16)
    {
        return uiVal;
    }
    if (vt == DLMS_DATA_TYPE_INT64)
    {
        return (double)llVal;
    }
    if (vt == DLMS_DATA_TYPE_UINT64)
    {
        return (double)ullVal;
    }
    if (vt == DLMS_DATA_TYPE_ENUM)
    {
        return bVal;
    }
    if (vt == DLMS_DATA_TYPE_FLOAT32)
    {
        return fltVal;
    }
    if (vt == DLMS_DATA_TYPE_FLOAT64)
    {
        return dblVal;
    }
    assert(0);
    return 0;
}

/**
* Add new object to the byte buffer.
*
* @param value
*            Value to add.
*/
int CGXDLMSVariant::GetBytes(CGXByteBuffer& value)
{
    if (vt == DLMS_DATA_TYPE_OCTET_STRING)
    {
        value.Set(byteArr, size);
    }
    else if (vt == DLMS_DATA_TYPE_UINT8)
    {
        value.SetUInt8(cVal);
    }
    else if (vt == DLMS_DATA_TYPE_UINT16)
    {
        value.SetUInt16(uiVal);
    }
    else if (vt == DLMS_DATA_TYPE_UINT32)
    {
        value.SetUInt32(ulVal);
    }
    else if (vt == DLMS_DATA_TYPE_UINT64)
    {
        value.SetUInt64(ullVal);
    }
    else if (vt == DLMS_DATA_TYPE_INT8)
    {
        value.SetInt8(bVal);
    }
    else if (vt == DLMS_DATA_TYPE_INT16)
    {
        value.SetInt16(iVal);
    }
    else if (vt == DLMS_DATA_TYPE_INT32)
    {
        value.SetInt32(lVal);
    }
    else if (vt == DLMS_DATA_TYPE_INT64)
    {
        value.SetInt64(llVal);
    }
    else if (vt == DLMS_DATA_TYPE_STRING)
    {
        value.AddString(strVal.c_str());
    }
    else if (vt == DLMS_DATA_TYPE_FLOAT32)
    {
        value.SetFloat(fltVal);
    }
    else if (vt == DLMS_DATA_TYPE_FLOAT64)
    {
        value.SetDouble(dblVal);
    }
    else
    {
        //Invalid object type.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return 0;
}
