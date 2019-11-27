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

#include "../include/GXDate.h"
#include "../include/GXTime.h"
#include "../include/GXHelpers.h"

unsigned char GXHelpers::GetDateTime(CArtVariant& buff, CGXDateTime& value)
{
	struct tm tm = { 0 };
	unsigned short year;
	unsigned short deviation;
	int ret, ms, status;
	unsigned char ch;
	VarInfo v_info;
	buff.GetVar(v_info);
	// If there is not enough data available.
	if ((v_info.vt != DLMS_DATA_TYPE_OCTET_STRING && v_info.vt != DLMS_DATA_TYPE_DATETIME) || v_info.size != 12)
	{
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	// Get year.
	if ((ret = buff.GetUInt16(&year)) != 0)
	{
		return ret;
	}
	tm.tm_year = year;
	// Get month
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	tm.tm_mon = ch;
	// Get day
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	tm.tm_mday = ch;
	// Skip week day
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	tm.tm_wday = ch;
	// Get time.
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	tm.tm_hour = ch;
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	tm.tm_min = ch;
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	tm.tm_sec = ch;
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	ms = ch;
	if (ms != 0xFF)
	{
		ms *= 10;
	}
	else
	{
		ms = 0;
	}
	if ((ret = buff.GetUInt16(&deviation)) != 0)
	{
		return ret;
	}
	if ((ret = buff.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	status = ch;
	value.SetStatus((DLMS_CLOCK_STATUS)status);
	DATETIME_SKIPS skip = DATETIME_SKIPS_NONE;
	if (year < 1 || year == 0xFFFF)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_YEAR);
		tm.tm_year = 0;
	}
	else
	{
		tm.tm_year -= 1900;
	}
	if (tm.tm_wday < 0 || tm.tm_wday > 7)
	{
		tm.tm_wday = 0;
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_DAYOFWEEK);
	}
	value.SetDaylightSavingsBegin(tm.tm_mon == 0xFE);
	value.SetDaylightSavingsEnd(tm.tm_mon == 0xFD);
	if (tm.tm_mon < 1 || tm.tm_mon > 12)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_MONTH);
		tm.tm_mon = 0;
	}
	else
	{
		tm.tm_mon -= 1;
	}
	if (tm.tm_mday == -1 || tm.tm_mday == 0 || tm.tm_mday > 31)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_DAY);
		tm.tm_mday = 1;
	}
	else if (tm.tm_mday < 0)
	{
		tm.tm_mday = CGXDateTime::DaysInMonth(year, tm.tm_mon + 1) + tm.tm_mday + 3;
	}
	if (tm.tm_hour < 0 || tm.tm_hour > 24)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_HOUR);
		tm.tm_hour = 0;
	}
	if (tm.tm_min < 0 || tm.tm_min > 60)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_MINUTE);
		tm.tm_min = 0;
	}
	if (tm.tm_sec < 0 || tm.tm_sec > 60)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_SECOND);
		tm.tm_sec = 0;
	}
	// If ms is Zero it's skipped.
	if (ms < 1 || ms > 1000)
	{
		skip = (DATETIME_SKIPS)(skip | DATETIME_SKIPS_MS);
		ms = 0;
	}
	tm.tm_isdst = (status & DLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE) != 0;
	value.SetValue(tm);
	value.SetDeviation(deviation);
	value.SetSkip(skip);
	return 0;
}

int GXHelpers::GetObjectCount(CGXByteBuffer& data, unsigned long& count)
{
    int ret;
    unsigned char cnt;
    if ((ret = data.GetUInt8(&cnt)) != 0)
    {
        return ret;
    }
    if (cnt > 0x80)
    {
        if (cnt == 0x81)
        {
            if ((ret = data.GetUInt8(&cnt)) != 0)
            {
                return ret;
            }
            count = cnt;
            return DLMS_ERROR_CODE_OK;
        }
        else if (cnt == 0x82)
        {
            unsigned short tmp;
            if ((ret = data.GetUInt16(&tmp)) != 0)
            {
                return ret;
            }
            count = tmp;
            return DLMS_ERROR_CODE_OK;
        }
        else if (cnt == 0x84)
        {
            unsigned long tmp;
            if ((ret = data.GetUInt32(&tmp)) != 0)
            {
                return ret;
            }
            count = tmp;
            return DLMS_ERROR_CODE_OK;
        }
        else
        {
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        }
    }
    count = cnt;
    return DLMS_ERROR_CODE_OK;
}

unsigned char GXHelpers::GetObjectCountSizeInBytes(unsigned long count)
{
    if (count < 0x80)
    {
        return 1;
    }
    else if (count < 0x100)
    {
        return 2;
    }
    else if (count < 0x10000)
    {
        return 3;
    }
    else
    {
        return 5;
    }
}

void GXHelpers::SetObjectCount(unsigned long count, CGXByteBuffer& buff)
{
    if (count < 0x80)
    {
        buff.SetUInt8((unsigned char)count);
    }
    else if (count < 0x100)
    {
        buff.SetUInt8(0x81);
        buff.SetUInt8((unsigned char)count);
    }
    else if (count < 0x10000)
    {
        buff.SetUInt8(0x82);
        buff.SetUInt16((unsigned short)count);
    }
    else
    {
        buff.SetUInt8(0x84);
        buff.SetUInt32(count);
    }
}

void GXHelpers::GetDataCA(CGXByteBuffer& data, CArtVariant& value) {
	if (data.GetPosition() < data.GetSize())
	{
		value.Set(data.GetData() + data.GetPosition(), data.GetSize() - data.GetPosition());
	}
}

void GXHelpers::SetDateTime(CArtVariant& buff, unsigned char index, CGXDateTime& value) {
	//Add year.
	unsigned short year = 0xFFFF;
	struct tm dt = value.GetValue();
	DATETIME_SKIPS skip = value.GetSkip();
	if (dt.tm_year != -1 && (skip & DATETIME_SKIPS_YEAR) == 0)
	{
		year = 1900 + dt.tm_year;
	}
	buff.SetUInt16(index, year);
	index += 2;
	//Add month
	if (value.GetDaylightSavingsBegin())
	{
		buff.SetUInt8(index, 0xFE);
	}
	else if (value.GetDaylightSavingsEnd())
	{
		buff.SetUInt8(index, 0xFD);
	}
	else if (dt.tm_mon != -1 && (skip & DATETIME_SKIPS_MONTH) == 0)
	{
		buff.SetUInt8(index, dt.tm_mon + 1);
	}
	else
	{
		buff.SetUInt8(index, 0xFF);
	}
	index += 1;
	//Add day
	if (dt.tm_mday != -1 && (skip & DATETIME_SKIPS_DAY) == 0)
	{
		buff.SetUInt8(index, dt.tm_mday);
	}
	else
	{
		buff.SetUInt8(index, 0xFF);
	}
	index += 1;
	//Add week day
	if ((skip & DATETIME_SKIPS_DAYOFWEEK) != 0)
	{
		buff.SetUInt8(index, 0xFF);
	}
	else
	{
		int val = dt.tm_wday + 1;
		//If Sunday.
		if (val == 1)
		{
			val = 8;
		}
		buff.SetUInt8(index, val - 1);
	}
	index += 1;
	//Add Hours
	if (dt.tm_hour != -1 && (skip & DATETIME_SKIPS_HOUR) == 0)
	{
		buff.SetUInt8(index, dt.tm_hour);
	}
	else
	{
		buff.SetUInt8(index, 0xFF);
	}
	index += 1;
	//Add Minutes
	if (dt.tm_min != -1 && (skip & DATETIME_SKIPS_MINUTE) == 0)
	{
		buff.SetUInt8(index, dt.tm_min);
	}
	else
	{
		buff.SetUInt8(index, 0xFF);
	}
	index += 1;
	//Add seconds.
	if (dt.tm_sec != -1 && (skip & DATETIME_SKIPS_SECOND) == 0)
	{
		buff.SetUInt8(index, dt.tm_sec);
	}
	else
	{
		buff.SetUInt8(index, 0xFF);
	}
	index += 1;
	//Add ms.
	if ((skip & DATETIME_SKIPS_MS) != 0)
	{
		// Hundredths of second is not used.
		buff.SetUInt8(index, 0xFF);
	}
	else
	{
		buff.SetUInt8(index, 0);
	}
	index += 1;
	// devitation not used.
	if ((skip & DATETIME_SKIPS_DEVITATION) != 0)
	{
		buff.SetUInt16(index, 0x8000);
	}
	else
	{
		// Add devitation.
		buff.SetUInt16(index, value.GetDeviation());
	}
	index += 2;
	// Add clock_status
	if (dt.tm_isdst)
	{
		buff.SetUInt8(index, value.GetStatus() | DLMS_CLOCK_STATUS_DAYLIGHT_SAVE_ACTIVE);
	}
	else
	{
		buff.SetUInt8(index, value.GetStatus());
	}
}

int GXHelpers::SetLogicalName(const char* name, CArtVariant& value)
{
	value.Clear();
	value.Reserve(6);
    return SetLogicalName(name, value.byteArr);
}

DLMS_ERROR_CODE GXHelpers::SetLogicalName(const char* name, unsigned char ln[6]){
	uint8_t i = 0;
	uint8_t char_val = 0;
  uint16_t val = 0;
	while (i < 6 && *name != '\0') {
		while (*name != '.' && *name != '\0') {
      char_val = (uint8_t)(*name - '0');
      if (char_val > 9)
        return DLMS_ERROR_CODE_INVALID_PARAMETER;

      val *= 10;
      val += char_val;
      if(val > 0xFF)
        return DLMS_ERROR_CODE_INVALID_PARAMETER;

      ++name;
		}
    ln[i] = (uint8_t)val;
    val = 0;
		++name;
		++i;
	}
  return i == 6 ? DLMS_ERROR_CODE_OK : DLMS_ERROR_CODE_INVALID_PARAMETER;
}

const int8_t typesSize[] = { 0, -1, -1, 1, -1,  4, 4, -2, -2, -1,   // DLMS_DATA_TYPE_NONE - DLMS_DATA_TYPE_OCTET_STRING
                            -1, -2, -1, 1, -2,  1, 2,  1,  2, -1,   // DLMS_DATA_TYPE_STRING - DLMS_DATA_TYPE_COMPACT_ARRAY
                             8,  8,  1, 4,  8, 12, 5,  4         }; //DLMS_DATA_TYPE_INT64 - DLMS_DATA_TYPE_TIME

int8_t spodesSizeof(DLMS_DATA_TYPE type) {
	if (type >= DLMS_DATA_TYPE_NONE && type <= DLMS_DATA_TYPE_TIME)
		return typesSize[type];
	return -2;
}