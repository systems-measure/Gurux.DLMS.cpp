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

CArtVariant::CArtVariant() {
	byteArr = NULL;
	size = 0;
	position = 0;
	capacity = 0;
}

CArtVariant::CArtVariant(unsigned char*& buff, unsigned short& size_buff) {
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

void CArtVariant::Set(unsigned char* buff, unsigned short size_buff) {
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

bool CArtVariant::Reserve(unsigned short new_size) {
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

bool CArtVariant::SetPosition(unsigned short pos) {
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

unsigned char CArtVariant::ChangeType(unsigned short src_size, DLMS_DATA_TYPE type, CArtVariant& new_value) {
	int8_t type_size = spodesSizeof(type);
	switch (type_size) {
	case -2: {
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	case -1: {
			new_value.Reserve(src_size + 2);
			new_value.SetUInt8(type);
			new_value.SetObjectCount(src_size);
			new_value.Set(GetCurPtr(), src_size);
			return DLMS_ERROR_CODE_OK;
	}
	case 0: {
		return DLMS_ERROR_CODE_UNMATCH_TYPE;
	}
	default: {
		new_value.Reserve(type_size + 1);
		new_value.SetUInt8(type);
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
	//case 8: {
	//	ret = GetUInt64(value);
	//	return ret;
	//}
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
//
//unsigned char CArtVariant::GetUInt64(unsigned long long* value) {
//	if (position + 8 > size)
//	{
//		return DLMS_ERROR_CODE_OUTOFMEMORY;
//	}
//	*value = (unsigned long long)byteArr[position] << 56 |
//			 (unsigned long long) byteArr[position + 1] << 48 |
//			 (unsigned long long) byteArr[position + 2] << 40 |
//			 (unsigned long long) byteArr[position + 3] << 32 |
//			 (unsigned long long) byteArr[position + 4] << 24 |
//			 (unsigned long long) byteArr[position + 5] << 16 |
//			 (unsigned long long) byteArr[position + 6] << 8 |
//			 (unsigned long long) byteArr[position + 7];
//	return 0;
//}
//
//unsigned char CArtVariant::GetReal(unsigned char size, double& value) {
//	unsigned char ret = DLMS_ERROR_CODE_INVALID_PARAMETER;
//	switch (size) {
//	case 4: {
//		float tmp;
//		ret = GetFloat(&tmp);
//		value = tmp;
//		return ret;
//	}
//	case 8: {
//		return GetDouble(&value);
//	}
//	}
//	return ret;
//}
//
//unsigned char CArtVariant::GetFloat(float* value) {
//	if (position + 4 > size)
//	{
//		return DLMS_ERROR_CODE_OUTOFMEMORY;
//	}
//	typedef union
//	{
//		float value;
//		char b[sizeof(float)];
//	} HELPER;
//	HELPER tmp;
//	tmp.b[3] = byteArr[position];
//	tmp.b[2] = byteArr[position + 1];
//	tmp.b[1] = byteArr[position + 2];
//	tmp.b[0] = byteArr[position + 3];
//	*value = tmp.value;
//	position += 4;
//	return 0;
//}
//
//unsigned char CArtVariant::GetDouble(double* value) {
//	if (position + 8 > size)
//	{
//		return DLMS_ERROR_CODE_OUTOFMEMORY;
//	}
//	typedef union
//	{
//		double value;
//		char b[sizeof(double)];
//	} HELPER;
//	HELPER tmp;
//	tmp.b[7] = byteArr[position];
//	tmp.b[6] = byteArr[position + 1];
//	tmp.b[5] = byteArr[position + 2];
//	tmp.b[4] = byteArr[position + 3];
//	tmp.b[3] = byteArr[position + 4];
//	tmp.b[2] = byteArr[position + 5];
//	tmp.b[1] = byteArr[position + 6];
//	tmp.b[0] = byteArr[position + 7];
//	*value = tmp.value;
//	position += 8;
//	return 0;
//}

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
//
//void CArtVariant::SetUInt64(unsigned long long item)
//{
//	if (size + 8 > capacity) {
//		//capacity = size + 8;
//		//byteArr = (unsigned char*)realloc(byteArr, capacity);
//		Reserve(size + 8);
//	}
//	byteArr[size]	  = (item >> 56) & 0xFF;
//	byteArr[size + 1] = (item >> 48) & 0xFF;
//	byteArr[size + 2] = (item >> 40) & 0xFF;
//	byteArr[size + 3] = (item >> 32) & 0xFF;
//	byteArr[size + 4] = (item >> 24) & 0xFF;
//	byteArr[size + 5] = (item >> 16) & 0xFF;
//	byteArr[size + 6] = (item >> 8) & 0xFF;
//	byteArr[size + 7] = item & 0xFF;
//	size += 8;
//}

void CArtVariant::SetUInt8(unsigned short index, unsigned char item) {
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

void CArtVariant::SetUInt16(unsigned short index, unsigned short item) {
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

void CArtVariant::SetUInt32(unsigned short index, unsigned long item) {
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
//
//void CArtVariant::SetUInt64(unsigned short index, unsigned long long item) {
//	if (index + 8 > capacity) {
//		//capacity = index + 8;
//		//byteArr = (unsigned char*)realloc(byteArr, capacity);
//		Reserve(index + 8);
//	}
//	byteArr[index] = (item >> 56) & 0xFF;
//	byteArr[index + 1] = (item >> 48) & 0xFF;
//	byteArr[index + 2] = (item >> 40) & 0xFF;
//	byteArr[index + 3] = (item >> 32) & 0xFF;
//	byteArr[index + 4] = (item >> 24) & 0xFF;
//	byteArr[index + 5] = (item >> 16) & 0xFF;
//	byteArr[index + 6] = (item >> 8) & 0xFF;
//	byteArr[index + 7] = item & 0xFF;
//	if (size < index + 8) {
//		Zero(size, index - size);
//		size = capacity;
//	}
//}
//
//void CArtVariant::SetFloat(float item) {
//	typedef union
//	{
//		float value;
//		char b[sizeof(float)];
//	} HELPER;
//
//	HELPER tmp;
//	tmp.value = item;
//	if (size + 4 > capacity)
//	{
//		//capacity = size + 4;
//		//byteArr = (unsigned char*)realloc(byteArr, capacity);
//		Reserve(size + 4);
//	}
//	byteArr[size] = tmp.b[3];
//	byteArr[size + 1] = tmp.b[2];
//	byteArr[size + 2] = tmp.b[1];
//	byteArr[size + 3] = tmp.b[0];
//	size += 4;
//}
//
//void CArtVariant::SetDouble(double item) {
//	typedef union
//	{
//		double value;
//		char b[sizeof(double)];
//	} HELPER;
//
//	HELPER tmp;
//	tmp.value = item;
//	if (size + 8 > capacity)
//	{
//		//capacity = size + 8;
//		//byteArr = (unsigned char*)realloc(byteArr, capacity);
//		Reserve(size + 8);
//	}
//	byteArr[size]	  = tmp.b[7];
//	byteArr[size + 1] = tmp.b[6];
//	byteArr[size + 2] = tmp.b[5];
//	byteArr[size + 3] = tmp.b[4];
//	byteArr[size + 4] = tmp.b[3];
//	byteArr[size + 5] = tmp.b[2];
//	byteArr[size + 6] = tmp.b[1];
//	byteArr[size + 7] = tmp.b[0];
//	size += 8;
//}

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

unsigned char CArtVariant::GetObjectCount(unsigned short& count)
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

void CArtVariant::SetObjectCount(unsigned short count)
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