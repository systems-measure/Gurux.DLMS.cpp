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
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSConverter.h"
#include "../include/GXDLMSDemandRegister.h"

bool CGXDLMSDemandRegister::IsRead(int index)
{
    if (index == 4)
    {
        return m_Unit != 0;
    }
    return CGXDLMSObject::IsRead(index);
}

/**
 Constructor.
*/
CGXDLMSDemandRegister::CGXDLMSDemandRegister() : CGXDLMSObject(DLMS_OBJECT_TYPE_DEMAND_REGISTER)
{
    m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSDemandRegister::CGXDLMSDemandRegister(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_DEMAND_REGISTER, ln)
{
    m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
}

/**
 Constructor.

 @param ln Logical Name of the object.
 @param sn Short Name of the object.
*/
CGXDLMSDemandRegister::CGXDLMSDemandRegister(int sn) : CGXDLMSObject(DLMS_OBJECT_TYPE_DEMAND_REGISTER, sn)
{
    m_Period = m_NumberOfPeriods = m_Unit = m_Scaler = 0;
}

/**
 Current avarage value of COSEM Data object.
*/
CArtVariant CGXDLMSDemandRegister::GetCurrentAvarageValue()
{
    return m_CurrentAvarageValue;
}
void CGXDLMSDemandRegister::SetCurrentAvarageValue(CArtVariant value)
{
    m_CurrentAvarageValue = value;
}

/**
 Last avarage value of COSEM Data object.
*/
CArtVariant CGXDLMSDemandRegister::GetLastAvarageValue()
{
    return m_LastAvarageValue;
}
void CGXDLMSDemandRegister::SetLastAvarageValue(CArtVariant value)
{
    m_LastAvarageValue = value;
}

/**
 Scaler of COSEM Register object.
*/
double CGXDLMSDemandRegister::GetScaler()
{
    return pow((float)10, m_Scaler);
}

void CGXDLMSDemandRegister::SetScaler(double value)
{
    m_Scaler = (signed char)log10(value);
}

// Unit of COSEM Register object.
unsigned char CGXDLMSDemandRegister::GetUnit()
{
    return m_Unit;
}

void CGXDLMSDemandRegister::SetUnit(unsigned char value)
{
    m_Unit = value;
}

/**
 Scaler of COSEM Register object.
*/
CArtVariant CGXDLMSDemandRegister::GetStatus()
{
    return m_Status;
}
void CGXDLMSDemandRegister::SetStatus(CArtVariant value)
{
    m_Status = value;
}

/**
 Capture time of COSEM Register object.
*/
CGXDateTime CGXDLMSDemandRegister::GetCaptureTime()
{
    return m_CaptureTime;
}
void CGXDLMSDemandRegister::SetCaptureTime(CGXDateTime value)
{
    m_CaptureTime = value;
}

/**
 Current start time of COSEM Register object.
*/
CGXDateTime CGXDLMSDemandRegister::GetStartTimeCurrent()
{
    return m_StartTimeCurrent;
}
void CGXDLMSDemandRegister::SetStartTimeCurrent(CGXDateTime value)
{
    m_StartTimeCurrent = value;
}

unsigned long CGXDLMSDemandRegister::GetPeriod()
{
    return m_Period;
}

void CGXDLMSDemandRegister::SetPeriod(unsigned long value)
{
    m_Period = value;
}

unsigned short CGXDLMSDemandRegister::GetNumberOfPeriods()
{
    return m_NumberOfPeriods;
}

void CGXDLMSDemandRegister::SetNumberOfPeriods(unsigned short value)
{
    m_NumberOfPeriods = value;
}

/*
 * Reset e.GetValue().
 */
void CGXDLMSDemandRegister::Reset()
{

}

/*
 * Next period.
 */
void CGXDLMSDemandRegister::NextPeriod()
{

}

void CGXDLMSDemandRegister::GetValues(std::vector<std::string>& values)
{
    //values.clear();
    //std::string ln;
    //GetLogicalName(ln);
    //values.push_back(ln);
    //values.push_back(m_CurrentAvarageValue.ToString());
    //values.push_back(m_LastAvarageValue.ToString());
    //std::string str = "Scaler: ";
    ////if there is no fractal part.
    //double s = GetScaler();
    //if (s - (long)s == 0)
    //{
    //    str += CGXDLMSVariant((long)s).ToString();
    //}
    //else
    //{
    //    str += CGXDLMSVariant(s).ToString();
    //}
    //str += " Unit: ";
    //str += CGXDLMSConverter::GetUnitAsString(m_Unit);
    //values.push_back(str);
    //values.push_back(m_Status.ToString());
    //values.push_back(m_CaptureTime.ToString());
    //values.push_back(m_StartTimeCurrent.ToString());
    //values.push_back(CGXDLMSVariant(m_Period).ToString());
    //values.push_back(CGXDLMSVariant(m_NumberOfPeriods).ToString());
}

void CGXDLMSDemandRegister::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //ScalerUnit
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //CurrentAvarageValue
    if (CanRead(2))
    {
        attributes.push_back(2);
    }
    //LastAvarageValue
    if (CanRead(3))
    {
        attributes.push_back(3);
    }
    //Status
    if (CanRead(5))
    {
        attributes.push_back(5);
    }
    //CaptureTime
    if (CanRead(6))
    {
        attributes.push_back(6);
    }
    //StartTimeCurrent
    if (CanRead(7))
    {
        attributes.push_back(7);
    }
    //Period
    if (CanRead(8))
    {
        attributes.push_back(8);
    }
    //NumberOfPeriods
    if (CanRead(9))
    {
        attributes.push_back(9);
    }
}

// Returns amount of attributes.
int CGXDLMSDemandRegister::GetAttributeCount()
{
    return 9;
}

// Returns amount of methods.
int CGXDLMSDemandRegister::GetMethodCount()
{
    return 2;
}

int CGXDLMSDemandRegister::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        Reset();
        return DLMS_ERROR_CODE_OK;
    }
    e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSDemandRegister::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
		VarInfo v_info;
		m_CurrentAvarageValue.GetVar(v_info);
		m_CurrentAvarageValue.SetPosition(0);
        type = v_info.vt;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
		VarInfo v_info;
		m_LastAvarageValue.GetVar(v_info);
		m_LastAvarageValue.SetPosition(0);
		type = v_info.vt;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
		VarInfo v_info;
		m_Status.GetVar(v_info);
		m_Status.SetPosition(0);
		type = v_info.vt;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_UINT32;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        type = DLMS_DATA_TYPE_UINT16;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSDemandRegister::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
	e.SetByteArray(true);
	CGXByteBuffer data;
    if (e.GetIndex() == 1)
    {
        int ret;
		if ((ret = GetLogicalName(this, data)) != 0)
        {
            return ret;
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
		CArtVariant tmp_val(m_CurrentAvarageValue);
        e.SetValue(tmp_val);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {
		CArtVariant tmp_val(m_LastAvarageValue);
		e.SetValue(tmp_val);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
		data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
		data.SetUInt8(2);
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(m_Scaler);
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(m_Unit);
		e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 5)
    {
		CArtVariant tmp_val(m_Status);
		e.SetValue(tmp_val);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 6)
    {
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(12);
		GXHelpers::SetDateTime(data, m_CaptureTime);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 7)
    {
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(12);
		GXHelpers::SetDateTime(data, m_StartTimeCurrent);
		e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 8)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(m_Period);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 9)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_NumberOfPeriods);
		e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSDemandRegister::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
        if (m_Scaler != 0)
        {
			VarInfo v_info;
			e.GetCAValue().GetVar(v_info);
			unsigned char ret;
			unsigned long long val;
			double res;
			if (v_info.vt == DLMS_DATA_TYPE_UINT8 || v_info.vt == DLMS_DATA_TYPE_UINT16 || v_info.vt == DLMS_DATA_TYPE_UINT32 || v_info.vt == DLMS_DATA_TYPE_UINT64 ||
				v_info.vt == DLMS_DATA_TYPE_INT8  || v_info.vt == DLMS_DATA_TYPE_INT16  || v_info.vt == DLMS_DATA_TYPE_INT32  || v_info.vt == DLMS_DATA_TYPE_INT64) {
				if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
					return ret;
				}
				res = (double)val*GetScaler();
			}
			else {
				if (v_info.vt == DLMS_DATA_TYPE_FLOAT32 || v_info.vt == DLMS_DATA_TYPE_FLOAT64) {
					if ((ret = e.GetCAValue().GetReal(v_info.size, res)) != DLMS_ERROR_CODE_OK) {
						return ret;
					}
					res *= GetScaler();
				}
			} 
			CArtVariant tmp_val;
			tmp_val.Reserve(9);
			tmp_val.SetUInt8(DLMS_DATA_TYPE_FLOAT64);
			tmp_val.SetDouble(res);
            SetCurrentAvarageValue(tmp_val);
        }
        else
        {
            SetCurrentAvarageValue(e.GetCAValue());
        }
    }
    else if (e.GetIndex() == 3)
    {
        if (m_Scaler != 0)
        {
			VarInfo v_info;
			e.GetCAValue().GetVar(v_info);
			unsigned char ret;
			unsigned long long val;
			double res;
			if (v_info.vt == DLMS_DATA_TYPE_UINT8 || v_info.vt == DLMS_DATA_TYPE_UINT16 || v_info.vt == DLMS_DATA_TYPE_UINT32 || v_info.vt == DLMS_DATA_TYPE_UINT64 ||
				v_info.vt == DLMS_DATA_TYPE_INT8 || v_info.vt == DLMS_DATA_TYPE_INT16 || v_info.vt == DLMS_DATA_TYPE_INT32 || v_info.vt == DLMS_DATA_TYPE_INT64) {
				if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
					return ret;
				}
				res = (double)val*m_Scaler;
			}
			else {
				if (v_info.vt == DLMS_DATA_TYPE_FLOAT32 || v_info.vt == DLMS_DATA_TYPE_FLOAT64) {
					if ((ret = e.GetCAValue().GetReal(v_info.size, res)) != DLMS_ERROR_CODE_OK) {
						return ret;
					}
					res *= m_Scaler;
				}
			}
			CArtVariant tmp_val;
			tmp_val.Reserve(9);
			tmp_val.SetUInt8(DLMS_DATA_TYPE_FLOAT64);
			tmp_val.SetDouble(res);
			SetLastAvarageValue(tmp_val);
        }
        else
        {
            SetLastAvarageValue(e.GetCAValue());
        }
    }
    else if (e.GetIndex() == 4 )
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 2) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
			e.GetCAValue().GetVar(v_info);
			m_Scaler = *(e.GetCAValue().GetCurPtr());
			e.GetCAValue().IncreasePosition(v_info.size);
			e.GetCAValue().GetVar(v_info);
			m_Unit = *(e.GetCAValue().GetCurPtr());
    }
    else if (e.GetIndex() == 5)
    {
        SetStatus(e.GetCAValue());
    }
    else if (e.GetIndex() == 6)
    {
		unsigned char ret;
		if ((ret = GXHelpers::GetDateTime(e.GetCAValue(), m_CaptureTime)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
    }
    else if (e.GetIndex() == 7)
    {
		unsigned char ret;
		if ((ret = GXHelpers::GetDateTime(e.GetCAValue(), m_StartTimeCurrent)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
    }
    else if (e.GetIndex() == 8)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
		SetPeriod((unsigned long)val);
    }
    else if (e.GetIndex() == 9)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        SetNumberOfPeriods((unsigned short)val);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
