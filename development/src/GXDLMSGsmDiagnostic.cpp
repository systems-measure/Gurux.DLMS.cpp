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
#include "../include/GXDLMSGsmDiagnostic.h"

//Constructor.
CGXDLMSGsmDiagnostic::CGXDLMSGsmDiagnostic() : CGXDLMSObject(DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC)
{
	Init();
}

//SN Constructor.
CGXDLMSGsmDiagnostic::CGXDLMSGsmDiagnostic(unsigned short sn) : CGXDLMSObject(DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC, sn)
{
	Init();
}

//LN Constructor.
CGXDLMSGsmDiagnostic::CGXDLMSGsmDiagnostic(std::string ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC, ln)
{
	Init();
}

void CGXDLMSGsmDiagnostic::Init()
{
	m_operator.clear();
	m_status = DLMS_STATUS_NOT_REG;
	m_cs_attachment = DLMS_CS_ATTACHMENT_INACTIVE;
	m_ps_status = DLMS_PS_STATUS_INACTIVE;
}

std::string	CGXDLMSGsmDiagnostic::GetOperator()
{
	return m_operator;
}

GX_STATUS CGXDLMSGsmDiagnostic::GetStatus()
{
	return m_status;
}
GX_CS_ATTACHMENT CGXDLMSGsmDiagnostic::GetCsAttachment()
{
	return m_cs_attachment;
}
GX_PS_STATUS CGXDLMSGsmDiagnostic::GetPsStatus()
{
	return m_ps_status;
}



// Returns amount of attributes.
int CGXDLMSGsmDiagnostic::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSGsmDiagnostic::GetMethodCount()
{
    return 0;
}

void CGXDLMSGsmDiagnostic::GetValues(std::vector<std::string>& values)
{
    values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    values.push_back(m_operator);
    values.push_back(CGXDLMSVariant(m_status).ToString());
	values.push_back(CGXDLMSVariant(m_cs_attachment).ToString());
	values.push_back(CGXDLMSVariant(m_ps_status).ToString());
 
}

void CGXDLMSGsmDiagnostic::GetAttributeIndexToRead(std::vector<int>& attributes)
{
	//LN is static and read only once.
	if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
	{
		attributes.push_back(1);
	}
	if (!IsRead(2))
	{
		attributes.push_back(2);
	}
	if (!IsRead(3))
	{
		attributes.push_back(3);
	}
	if (!IsRead(4))
	{
		attributes.push_back(4);
	}
	if (!IsRead(5))
	{
		attributes.push_back(5);
	}
	if (!IsRead(6))
	{
		attributes.push_back(6);
	}
	if (!IsRead(7))
	{
		attributes.push_back(7);
	}
	if (!IsRead(8))
	{
		attributes.push_back(8);
	}
}

int CGXDLMSGsmDiagnostic::GetDataType(int index, DLMS_DATA_TYPE& type)
{
	if (index == 1)
	{
		type = DLMS_DATA_TYPE_OCTET_STRING;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 2)
	{
		type = DLMS_DATA_TYPE_STRING;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 3)
	{
		type = DLMS_DATA_TYPE_ENUM;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 4)
	{
		type = DLMS_DATA_TYPE_ENUM;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 5)
	{
		type = DLMS_DATA_TYPE_ENUM;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 6)
	{
		type = DLMS_DATA_TYPE_STRUCTURE;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 7)
	{
		type = DLMS_DATA_TYPE_ARRAY;
		return DLMS_ERROR_CODE_OK;
	}
	if (index == 8)
	{
		type = DLMS_DATA_TYPE_DATETIME;
		return DLMS_ERROR_CODE_OK;
	}
	return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Returns value of given attribute.
int CGXDLMSGsmDiagnostic::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        int ret;
        CGXDLMSVariant tmp;
        if ((ret = GetLogicalName(this, tmp)) != 0)
        {
            return ret;
        }
        e.SetValue(tmp);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
        CGXByteBuffer bb;
        bb.AddString(m_operator);
        e.SetValue(bb);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {
		e.SetValue(m_status);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
		e.SetValue(m_cs_attachment);
        return DLMS_ERROR_CODE_OK;
    }
	if (e.GetIndex() == 5)
	{
		e.SetValue(m_ps_status);
		return DLMS_ERROR_CODE_OK;
	}
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

// Set value of given attribute.
int CGXDLMSGsmDiagnostic::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetValue());
    }
    else if (e.GetIndex() == 2)
    {
        if (e.GetValue().vt == DLMS_DATA_TYPE_STRING)
        {
			m_operator = e.GetValue().ToString();
        }
        else
        {
			m_operator.clear();
			m_operator.append(e.GetValue().byteArr, e.GetValue().byteArr + e.GetValue().GetSize());
        }
    }
    else if (e.GetIndex() == 3)
    {
		m_status = (GX_STATUS)e.GetValue().uiVal;
    }
    else if (e.GetIndex() == 4)
    {
		m_cs_attachment = (GX_CS_ATTACHMENT)e.GetValue().uiVal;
    }
	else if (e.GetIndex() == 5)
	{
		m_ps_status = (GX_PS_STATUS)e.GetValue().uiVal;
	}
    /// 4.6.8 GSM diagnostic (class_id: 47, version: 0) [Attribute 6 cell_info](https://gyazo.com/f79705a612552818286a12c28109f6aa)
    else if (e.GetIndex() == 6)
    {
        // -- Check type
        if ( (e.GetValue().vt != DLMS_DATA_TYPE_STRUCTURE) ||
             (e.GetValue().Arr.size() != 4) )
            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        // -- cell_ID
        if(e.GetValue().Arr[0].vt != DLMS_DATA_TYPE_UINT16) return DLMS_ERROR_CODE_INVALID_PARAMETER;
        m_cell_info.cell_ID = e.GetValue().Arr[0].uiVal;
        // -- location_ID
        if(e.GetValue().Arr[1].vt != DLMS_DATA_TYPE_UINT16) return DLMS_ERROR_CODE_INVALID_PARAMETER;
        m_cell_info.location_ID = e.GetValue().Arr[1].uiVal;
        // -- signal_quality
        if(e.GetValue().Arr[2].vt != DLMS_DATA_TYPE_UINT8) return DLMS_ERROR_CODE_INVALID_PARAMETER;
        m_cell_info.signal_quality = e.GetValue().Arr[2].bVal;
        // -- ber
        if(e.GetValue().Arr[3].vt != DLMS_DATA_TYPE_UINT8) return DLMS_ERROR_CODE_INVALID_PARAMETER;
        m_cell_info.ber = e.GetValue().Arr[3].bVal;
    }
    else if (e.GetIndex() <= 8) return DLMS_ERROR_CODE_NOT_IMPLEMENTED;
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

