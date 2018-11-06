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

#ifndef GXDLMSVARIANT_H
#define GXDLMSVARIANT_H

#include "GXDate.h"
#include "GXTime.h"
#include "GXDateTime.h"
#include "GXBytebuffer.h"

#define __tagVARIANT
#define __VARIANT_NAME_1
#define __VARIANT_NAME_2
#define __VARIANT_NAME_3

class CArtVariant;

struct VarInfo {
	DLMS_DATA_TYPE vt;
	unsigned short size;
};

struct cVariant {
	unsigned char *byteArr;
	unsigned short position;
	unsigned short size;
	unsigned short capacity;
};

class CArtVariant: public cVariant
{
public:
	CArtVariant();
	~CArtVariant();
	CArtVariant(const CArtVariant& value);
	CArtVariant(unsigned char*& buff, unsigned short& size_buff);

	//Move
	CArtVariant& operator=(CArtVariant& value);
	CArtVariant& operator=(CGXByteBuffer& value);

	void Set(unsigned char* buff, unsigned short size);
	unsigned char* GetCurPtr();

	bool Reserve(unsigned short new_size);

	bool IncreasePosition(unsigned short diff);
	bool DecreasePosition(unsigned short diff);
	bool SetPosition(unsigned short pos);

	unsigned char GetUInt(unsigned char size, unsigned long long* value);
	unsigned char GetUInt8(unsigned char* value);
	unsigned char GetUInt16(unsigned short* value);
	unsigned char GetUInt32(unsigned long* value);
	//unsigned char GetUInt64(unsigned long long* value);

	//unsigned char GetReal(unsigned char size, double& value);
	//unsigned char GetFloat(float* value);
	//unsigned char GetDouble(double* value);

	void SetUInt8(unsigned char item);
	void SetUInt16(unsigned short item);
	void SetUInt32(unsigned long item);
	//void SetUInt64(unsigned long long item);

	void SetUInt8(unsigned short index, unsigned char item);
	void SetUInt16(unsigned short index,unsigned short item);
	void SetUInt32(unsigned short index,unsigned long item);
	//void SetUInt64(unsigned short index,unsigned long long item);

	//void SetFloat(float item);
	//void SetDouble(double item);

	unsigned char Zero(unsigned short index, unsigned short count);

	void GetVar(VarInfo& v_info);
	unsigned char ChangeType(unsigned short src_size, DLMS_DATA_TYPE type, CArtVariant& new_value);

	unsigned char GetObjectCount(unsigned short& count);
	void SetObjectCount(unsigned short count);

	void Clear();

};
//
//class CGXDLMSVariant;
//
//struct dlmsVARIANT
//{
//    union
//    {
//        struct __tagVARIANT
//        {
//            DLMS_DATA_TYPE vt;
//            union
//            {
//                unsigned char bVal;
//                char cVal;
//                short iVal;
//                long lVal;
//                long long llVal;
//                float fltVal;
//                double dblVal;
//                bool boolVal;
//                unsigned short uiVal;
//                unsigned long ulVal;
//                unsigned long long ullVal;
//                unsigned char *byteArr;
//            } 	__VARIANT_NAME_3;
//        } 	__VARIANT_NAME_2;
//    } 	__VARIANT_NAME_1;
//    CGXDateTime dateTime;
//    //Size of byte array.
//    unsigned short size;
//    std::string strVal;
//    std::basic_string<wchar_t> strUtfVal;
//    std::vector<CGXDLMSVariant> Arr;
//};

#endif //GXDLMSVARIANT_H
