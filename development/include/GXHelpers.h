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

#ifndef GXHELPERS_H
#define GXHELPERS_H

#include "errorcodes.h"
#include "GXDLMSVariant.h"
#include "GXDataInfo.h"

const char num_codes[10] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', };

class GXHelpers
{
    /*
    * Convert char hex value to byte value.
    * @param c Character to convert hex.
    * @return Byte value of hex char value.
    */
    static unsigned char GetValue(char c);
public:

	static void GetDataCA(CGXByteBuffer& data, CArtVariant& value);

	static void SetDateTime(CArtVariant& buff, unsigned char index, CGXDateTime& value);

	static unsigned char GetDateTime(CArtVariant& buff, CGXDateTime& value);

	static void GetNum(unsigned char& num, char* ln, unsigned char& size) {
		if (num >= 100) {
			*(ln + size) = (num_codes[num / 100]);
			++size;
		}
		if (num >= 10) {
			*(ln + size) = (num_codes[(num / 10) % 10]);
			++size;
		}
		*(ln + size) = (num_codes[num % 10]);
		++size;
	}

	static void GetNum16(unsigned short& num, char* ln, unsigned char& size) {
		if (num >= 10000) {
			*(ln + size) = (num_codes[num / 10000]);
			++size;
		}
		if (num >= 1000) {
			*(ln + size) = (num_codes[(num / 1000) % 10]);
			++size;
		}
		if (num >= 100) {
			*(ln + size) = (num_codes[(num / 100) % 10]);
			++size;
		}
		if (num >= 10) {
			*(ln + size) = (num_codes[(num / 10) % 10]);
			++size;
		}
		*(ln + size) = (num_codes[num % 10]);
		++size;
	}

    static void GetLogicalName(unsigned char* buff, std::string& ln)
    {
        
		ln.clear();
        //If Script Action target is not set it is null
        if (buff == NULL)
        {
            ln.append("0.0.0.0.0.0");
        }
		else
		{
			unsigned char dataSize = 0;
			char tmp[23];
			GetNum(buff[0], tmp, dataSize);
			tmp[dataSize] = '.';
			++dataSize;
			GetNum(buff[1], tmp, dataSize);
			tmp[dataSize] = '.';
			++dataSize;
			GetNum(buff[2], tmp, dataSize);
			tmp[dataSize] = '.';
			++dataSize;
			GetNum(buff[3], tmp, dataSize);
			tmp[dataSize] = '.';
			++dataSize;
			GetNum(buff[4], tmp, dataSize);
			tmp[dataSize] = '.';
			++dataSize;
			GetNum(buff[5], tmp, dataSize);
			ln.append(tmp, dataSize);
		}
    }

	static void GetLogicalName(unsigned char* buff, char* ln)
	{
		//If Script Action target is not set it is null
		if (buff != NULL)
		{
			unsigned char dataSize = 0;
			GetNum(buff[0], ln, dataSize);
			ln[dataSize] = '.';
			++dataSize;
			GetNum(buff[1], ln, dataSize);
			ln[dataSize] = '.';
			++dataSize;
			GetNum(buff[2], ln, dataSize);
			ln[dataSize] = '.';
			++dataSize;
			GetNum(buff[3], ln, dataSize);
			ln[dataSize] = '.';
			++dataSize;
			GetNum(buff[4], ln, dataSize);
			ln[dataSize] = '.';
			++dataSize;
			GetNum(buff[5], ln, dataSize);
			ln[dataSize] = '\0';
		}
		else {
			memset(ln, 0, 24);
		}
	}

    static void GetLogicalName(CGXByteBuffer& buff, std::string& ln)
    {
        unsigned char tmp[6];
        buff.Get(tmp, 6);
        GetLogicalName(tmp, ln);
    }

#define TRACEUL(text, ul) printf("%s %x%x%x%x\r\n", text, (unsigned char) (ul >> 24) & 0xFF, (unsigned char)(ul >> 16) & 0xFF, (unsigned char) (ul >> 8) & 0xFF, (unsigned char) ul & 0xFF)

#define TRACE1(var) printf(var)
#define TRACE(var, fmt) printf(var, fmt)

    /////////////////////////////////////////////////////////////////////////////
    //Set logical name from std::string.
    /////////////////////////////////////////////////////////////////////////////
    static int SetLogicalName(const char* name, CArtVariant& value);

    /////////////////////////////////////////////////////////////////////////////
    //Set logical name from std::string.
    /////////////////////////////////////////////////////////////////////////////
    static int SetLogicalName(const char* name, unsigned char ln[6]);

    /////////////////////////////////////////////////////////////////////////////
    // Get object count. If first byte is 0x80 or higger it will tell bytes count.
    // data ; received data.
    // Returns Object count.
    /////////////////////////////////////////////////////////////////////////////
    static int GetObjectCount(CGXByteBuffer& data, unsigned long& count);

    /**
        * Return how many bytes object count takes.
        *
        * @param count
        *            Value
        * @return Value size in bytes.
        */
    static unsigned char GetObjectCountSizeInBytes(unsigned long count);

    /////////////////////////////////////////////////////////////////////////////
    // Set item count.
    /////////////////////////////////////////////////////////////////////////////
    // count : Item count.
    // buff : Byte buffer.
    /////////////////////////////////////////////////////////////////////////////
    static void SetObjectCount(unsigned long count, CGXByteBuffer& buff);
    
    static void LNToBytes(std::string ln, CGXByteBuffer& buffer);

};

template<typename T, typename attr_t = int8_t>
struct tabFunc {
    attr_t attr_index;
    T execute_func;
};

int8_t spodesSizeof(DLMS_DATA_TYPE type);
#endif //GXHELPERS_H
