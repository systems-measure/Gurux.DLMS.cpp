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

#ifndef GXBYTEBUFFER_H
#define GXBYTEBUFFER_H

#include "errorcodes.h"
#include "enums.h"

const unsigned char VECTOR_CAPACITY = 24;
class CGXByteBuffer
{
    unsigned char* m_Data;
    unsigned short m_Capacity;
    unsigned short m_Size;
    unsigned short m_Position;
public:
    //Constructor.
    CGXByteBuffer();

    //Constructor.
    CGXByteBuffer(unsigned short capacity);

    //Copy constructor.
    CGXByteBuffer(const CGXByteBuffer& value);

    //Destructor.
    ~CGXByteBuffer();

    //Returns buffer size.
    unsigned short GetSize();

    //Set buffer size.
    void SetSize(unsigned short value);

    //Returns position of the buffer.
    unsigned short GetPosition();

    //Returns position of the buffer.
    void SetPosition(unsigned short value);

    //Allocate new size for the array in bytes.
    void Capacity(unsigned short capacity);

    //Get buffer capacity.
    unsigned short Capacity();

	void Reserve(unsigned short capacity);

    //Fill buffer it with zeros.
    void Zero(unsigned short index, unsigned short count);

    //Push new data to the byteArray.
    void SetUInt8(unsigned char item);

    void SetUInt8(unsigned short index, unsigned char item);

    void SetUInt16(unsigned short item);

	void SetUInt16(unsigned short index, unsigned short item);

    void SetUInt32(unsigned long item);

    void SetUInt32(unsigned short index, unsigned long item);

   // void SetUInt64(unsigned long long item);

    void SetInt8(signed char item);

    void SetInt16(short item);

    void SetInt32(long item);

    //void SetInt64(long long item);

    //void SetFloat(float value);

    //void SetDouble(double value);

    void Set(const void* pSource, unsigned short count);

    void Set(unsigned short index, const void* pSource, unsigned short count);

    void Set(CGXByteBuffer* data, unsigned short index = 0, unsigned short count = -1);

    void Clear(bool free = true);

    int GetUInt8(unsigned char* value);

    int GetUInt8(unsigned short index, unsigned char* value);

    int GetUInt16(unsigned short* value);

    int GetUInt32(unsigned long* value);

    //int GetInt16(short* value);

    //int GetInt32(long* value);

    //int GetInt64(long long* value);

    //int GetUInt64(unsigned long long* value);

    //int GetFloat(float* value);

    //int GetDouble( double* value);

    int Get(unsigned char* value, unsigned short count);

    unsigned char*& GetData();

    /**
     * Compares, whether two given arrays are similar starting from current
     * position.
     *
     * @param arr
     *            Array to compare.
     * @return True, if arrays are similar. False, if the arrays differ.
     */
    bool Compare(unsigned char* buff, unsigned long length);

    //int GetUInt16(unsigned long index, unsigned short* value);
    //int GetUInt32(unsigned long index, unsigned long* value);
    //int GetUInt64(unsigned long index, unsigned long long* value);
    //int GetUInt128(unsigned long index, unsigned char* value);

    //Move data insize byte array.
    int Move(unsigned short srcPos, unsigned short destPos, unsigned short count);

    ////Little Endian methods.
    //int GetUInt32LE(unsigned long* value);
    //int GetUInt32LE(unsigned long index, unsigned long* value);
    //void SetUInt32ByIndexLE(unsigned long index, unsigned long item);

    CGXByteBuffer& operator=(CGXByteBuffer& value);
};

#endif //GXBYTEBUFFER_H
