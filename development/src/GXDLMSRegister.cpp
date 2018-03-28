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
#include "../include/GXDLMSRegister.h"
//
//void CGXDLMSRegister::Init()
//{
//    m_Unit = 0;
//    m_Scaler = 0;
//}

//LN Constructor.
CGXDLMSRegister::CGXDLMSRegister(DLMS_OBJECT_TYPE type, const char* ln) : CGXDLMSObject(type, ln)
{
    //Init();
}

//Constructor.
CGXDLMSRegister::CGXDLMSRegister(void) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER)
{
    //Init();
}

//LN Constructor.
CGXDLMSRegister::CGXDLMSRegister(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER, ln)
{
    //Init();
}

//LN Constructor.
CGXDLMSRegister::CGXDLMSRegister(const char* ln, double scaler, unsigned char unit, CArtVariant value) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER, ln)
{
    //m_Value = value;
   // Init();
}

/// <summary>
/// Get value of COSEM Data object.
/// </summary>
//CArtVariant CGXDLMSRegister::GetValue()
//{
//    return m_Value;
//}
//
///// <summary>
///// Set value of COSEM Data object.
///// </summary>
//void CGXDLMSRegister::SetValue(CArtVariant& value)
//{
//    m_Value = value;
//}

// Scaler of COSEM Register object.
//double CGXDLMSRegister::GetScaler()
//{
//    return pow((float)10, m_Scaler);
//}
//
//void CGXDLMSRegister::SetScaler(double value)
//{
//    m_Scaler = (signed char)log10(value);
//}

// Unit of COSEM Register object.
//unsigned char CGXDLMSRegister::GetUnit()
//{
//    return m_Unit;
//}
//
//void CGXDLMSRegister::SetUnit(unsigned char value)
//{
//    m_Unit = value;
//}

/*
 * Reset value.
 */
//void CGXDLMSRegister::Reset()
//{
//    m_Value.Clear();
//}

// Returns amount of attributes.
int CGXDLMSRegister::GetAttributeCount()
{
    return 3;
}

// Returns amount of methods.
int CGXDLMSRegister::GetMethodCount()
{
    return 1;
}

int CGXDLMSRegister::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        //Reset();
        return DLMS_ERROR_CODE_OK;
    }
    e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSRegister::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        return CGXDLMSObject::GetDataType(index, type);
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSRegister::GetDataType(signed char index) {
	if (index == 1)
	{
		return DLMS_DATA_TYPE_OCTET_STRING;
	}
	if (index == 2)
	{
		return CGXDLMSObject::GetDataType(index);
	}
	if (index == 3)
	{
		return DLMS_DATA_TYPE_STRUCTURE;
	}
	return DLMS_DATA_TYPE_NONE;
}

int CGXDLMSRegister::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
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
		/*CArtVariant tmp_val(m_Value);
        e.SetValue(tmp_val);*/
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {    
		//data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
		//data.SetUInt8(2);
		//data.SetUInt8(DLMS_DATA_TYPE_INT8);
		//data.SetUInt8(m_Scaler);
		//data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		//data.SetUInt8(m_Unit);
		//e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSRegister::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
        /*if (m_Scaler != 0)
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
            SetValue(tmp_val);
        }
        else
        {
            SetValue(e.GetCAValue());
        }*/
    }
    else if (e.GetIndex() == 3 )
    {
		/*VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 2) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		e.GetCAValue().GetVar(v_info);
		m_Scaler = *(e.GetCAValue().GetCurPtr());
		e.GetCAValue().IncreasePosition(v_info.size);
		e.GetCAValue().GetVar(v_info);
		m_Unit = *(e.GetCAValue().GetCurPtr());*/
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
