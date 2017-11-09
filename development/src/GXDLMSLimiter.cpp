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

#include "../include/GXDLMSLimiter.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSActionSet.h"
#include "SPODES.h"
#include <sstream>

//Constructor.
CGXDLMSLimiter::CGXDLMSLimiter() : CGXDLMSObject(DLMS_OBJECT_TYPE_LIMITER)
{
    m_MinOverThresholdDuration = 0;
    m_MinUnderThresholdDuration = 0;
    m_EmergencyProfileActive = false;
    m_MonitoredAttributeIndex = 0;
}

//SN Constructor.
CGXDLMSLimiter::CGXDLMSLimiter(unsigned short sn) : CGXDLMSObject(DLMS_OBJECT_TYPE_LIMITER, sn)
{
    m_MinOverThresholdDuration = 0;
    m_MinUnderThresholdDuration = 0;
    m_EmergencyProfileActive = false;
    m_MonitoredAttributeIndex = 0;
}

//LN Constructor.
CGXDLMSLimiter::CGXDLMSLimiter(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_LIMITER, ln)
{
    m_MinOverThresholdDuration = 0;
    m_MinUnderThresholdDuration = 0;
    m_EmergencyProfileActive = false;
    m_MonitoredAttributeIndex = 0;
}

/**
Defines an attribute of an object to be monitored.
*/
CArtVariant CGXDLMSLimiter::GetMonitoredValue()
{
    return m_MonitoredValue;
}
void CGXDLMSLimiter::SetMonitoredValue(CArtVariant& value)
{
    m_MonitoredValue = value;
}

/**
 Provides the active threshold value to which the attribute monitored is compared.
*/
CArtVariant& CGXDLMSLimiter::GetThresholdActive()
{
    return m_ThresholdActive;
}
void CGXDLMSLimiter::SetThresholdActive(CArtVariant& value)
{
    m_ThresholdActive = value;
}

/**
 Provides the threshold value to which the attribute monitored
 is compared when in normal operation.
*/
CArtVariant& CGXDLMSLimiter::GetThresholdNormal()
{
    return m_ThresholdNormal;
}
void CGXDLMSLimiter::SetThresholdNormal(CArtVariant& value)
{
    m_ThresholdNormal = value;
}

/**
 Provides the threshold value to which the attribute monitored
 is compared when an emergency profile is active.
*/
CArtVariant& CGXDLMSLimiter::GetThresholdEmergency()
{
    return m_ThresholdEmergency;
}
void CGXDLMSLimiter::SetThresholdEmergency(CArtVariant& value)
{
    m_ThresholdEmergency = value;
}

/**
 Defines minimal over threshold duration in seconds required
 to execute the over threshold action.
*/
unsigned long CGXDLMSLimiter::GetMinOverThresholdDuration()
{
    return m_MinOverThresholdDuration;
}
void CGXDLMSLimiter::SetMinOverThresholdDuration(unsigned long value)
{
    m_MinOverThresholdDuration = value;
}

/**
 Defines minimal under threshold duration in seconds required to
 execute the under threshold action.
*/
unsigned long CGXDLMSLimiter::GetMinUnderThresholdDuration()
{
    return m_MinUnderThresholdDuration;
}
void CGXDLMSLimiter::SetMinUnderThresholdDuration(unsigned long value)
{
    m_MinUnderThresholdDuration = value;
}
CGXDLMSEmergencyProfile& CGXDLMSLimiter::GetEmergencyProfile()
{
    return m_EmergencyProfile;
}
void CGXDLMSLimiter::SetEmergencyProfile(CGXDLMSEmergencyProfile value)
{
    m_EmergencyProfile = value;
}

std::vector<unsigned short>& CGXDLMSLimiter::GetEmergencyProfileGroupIDs()
{
    return m_EmergencyProfileGroupIDs;
}
void CGXDLMSLimiter::SetEmergencyProfileGroupIDs(std::vector<unsigned short>& value)
{
    m_EmergencyProfileGroupIDs = value;
}

/**
 Is Emergency Profile active.
*/
bool CGXDLMSLimiter::GetEmergencyProfileActive()
{
    return m_EmergencyProfileActive;
}
void CGXDLMSLimiter::SetEmergencyProfileActive(bool value)
{
    m_EmergencyProfileActive = value;
}

/**
 Defines the scripts to be executed when the monitored value
 crosses the threshold for minimal duration time.
*/
CGXDLMSActionItem& CGXDLMSLimiter::GetActionOverThreshold()
{
    return m_ActionOverThreshold;
}
void CGXDLMSLimiter::SetActionOverThreshold(CGXDLMSActionItem value)
{
    m_ActionOverThreshold = value;
}

/**
 Defines the scripts to be executed when the monitored value
 crosses the threshold for minimal duration time.
*/
CGXDLMSActionItem& CGXDLMSLimiter::GetActionUnderThreshold()
{
    return m_ActionUnderThreshold;
}
void CGXDLMSLimiter::SetActionUnderThreshold(CGXDLMSActionItem value)
{
    m_ActionUnderThreshold = value;
}

// Returns amount of attributes.
int CGXDLMSLimiter::GetAttributeCount()
{
    return 11;
}

// Returns amount of methods.
int CGXDLMSLimiter::GetMethodCount()
{
    return 2;
}

void CGXDLMSLimiter::GetValues(std::vector<std::string>& values)
{
   /* values.clear();
    std::string ln;
    GetLogicalName(ln);
    values.push_back(ln);
    if (m_MonitoredValue != NULL)
    {
        values.push_back(m_MonitoredValue->GetName());
    }
    else
    {
        values.push_back("");
    }
    values.push_back(m_ThresholdActive.ToString());
    values.push_back(m_ThresholdNormal.ToString());
    values.push_back(m_ThresholdEmergency.ToString());
    values.push_back(CGXDLMSVariant(m_MinOverThresholdDuration).ToString());
    values.push_back(CGXDLMSVariant(m_MinUnderThresholdDuration).ToString());
    values.push_back(m_EmergencyProfile.ToString());
    std::stringstream sb;
    sb << '[';
    bool empty = true;
    for (std::vector<int>::iterator it = m_EmergencyProfileGroupIDs.begin(); it != m_EmergencyProfileGroupIDs.end(); ++it)
    {
        if (!empty)
        {
            sb << ", ";
        }
        empty = false;
        std::string str = CGXDLMSVariant(*it).ToString();
        sb.write(str.c_str(), str.size());
    }
    sb << ']';
    values.push_back(sb.str());
    values.push_back(CGXDLMSVariant(m_EmergencyProfileActive).ToString());

    sb.str(std::string());
    sb << m_ActionOverThreshold.ToString().c_str();
    sb << ", ";
    sb << m_ActionUnderThreshold.ToString().c_str();
    values.push_back(sb.str());*/
}

void CGXDLMSLimiter::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //MonitoredValue
    if (CanRead(2))
    {
        attributes.push_back(2);
    }

    //ThresholdActive
    if (CanRead(3))
    {
        attributes.push_back(3);
    }

    //ThresholdNormal
    if (CanRead(4))
    {
        attributes.push_back(4);
    }

    //ThresholdEmergency
    if (CanRead(5))
    {
        attributes.push_back(5);
    }

    //MinOverThresholdDuration
    if (CanRead(6))
    {
        attributes.push_back(6);
    }

    //MinUnderThresholdDuration
    if (CanRead(7))
    {
        attributes.push_back(7);
    }

    //EmergencyProfile
    if (CanRead(8))
    {
        attributes.push_back(8);
    }
    //EmergencyProfileGroup
    if (CanRead(9))
    {
        attributes.push_back(9);
    }

    //EmergencyProfileActive
    if (CanRead(10))
    {
        attributes.push_back(10);
    }
    //Actions
    if (CanRead(11))
    {
        attributes.push_back(11);
    }
}

int CGXDLMSLimiter::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 3)
    {
		type = (DLMS_DATA_TYPE)*(m_MonitoredValue.byteArr + (m_MonitoredValue.size - 1));
    }
    else if (index == 4)
    {
		type = (DLMS_DATA_TYPE)*(m_MonitoredValue.byteArr + (m_MonitoredValue.size - 1));
    }
    else if (index == 5)
    {
		type = (DLMS_DATA_TYPE)*(m_MonitoredValue.byteArr + (m_MonitoredValue.size - 1));
    }
    else if (index == 6)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 7)
    {
        type = DLMS_DATA_TYPE_UINT32;
    }
    else if (index == 8)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else if (index == 9)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 10)
    {
        type = DLMS_DATA_TYPE_BOOLEAN;
    }
    else if (index == 11)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns value of given attribute.
int CGXDLMSLimiter::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
	CGXByteBuffer data;
//	e.SetByteArray(true);
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
    else if (e.GetIndex() == 2)
    {
       data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(3);
		if (m_MonitoredValue.byteArr != nullptr) {
			data.Set(m_MonitoredValue.byteArr, m_MonitoredValue.size - 2);
		}
		else {
			data.SetUInt8(DLMS_DATA_TYPE_INT16);
			data.SetUInt16(0);
			data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
			data.SetUInt8(0x06);
			data.Zero(data.GetSize(), 6);
		}
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_MonitoredAttributeIndex);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 3)
    {
		CArtVariant tmp_val(m_ThresholdActive);
        e.SetValue(tmp_val);
        return DLMS_ERROR_CODE_OK;
    }
    else if (e.GetIndex() == 4)
    {
		CArtVariant tmp_val(m_ThresholdNormal);
		e.SetValue(tmp_val);
    }
    else if (e.GetIndex() == 5)
    {
		CArtVariant tmp_val(m_ThresholdEmergency);
		e.SetValue(tmp_val);
    }
    else if (e.GetIndex() == 6)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(m_MinOverThresholdDuration);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 7)
    {
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(m_MinUnderThresholdDuration);
		e.SetValue(data);
    }
    else if (e.GetIndex() == 8)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
		data.SetUInt8(3);
        data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_EmergencyProfile.GetID());
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(12);
		GXHelpers::SetDateTime(data, m_EmergencyProfile.GetActivationTime());
		data.SetUInt8(DLMS_DATA_TYPE_UINT32);
		data.SetUInt32(m_EmergencyProfile.GetDuration());
		e.SetValue(data);
    }
    else if (e.GetIndex() == 9)
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        GXHelpers::SetObjectCount((unsigned long)m_EmergencyProfileGroupIDs.size(), data);
        for (std::vector<unsigned short>::iterator it = m_EmergencyProfileGroupIDs.begin(); it != m_EmergencyProfileGroupIDs.end(); ++it)
        {
			data.SetUInt8(DLMS_DATA_TYPE_UINT16);
			data.SetUInt16(*it);
        }
        e.SetValue(data);
    }
    else if (e.GetIndex() == 10)
    {
		data.SetUInt8(DLMS_DATA_TYPE_BOOLEAN);
		data.SetUInt8(m_EmergencyProfileActive);
        e.SetValue(data);
    }
    else if (e.GetIndex() == 11)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(2);
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(2);
        CArtVariant ln;
        GXHelpers::SetLogicalName(m_ActionOverThreshold.GetLogicalName().c_str(), ln);
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(6);
		data.Set(ln.byteArr, 6);
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_ActionOverThreshold.GetScriptSelector());
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(2);
        GXHelpers::SetLogicalName(m_ActionUnderThreshold.GetLogicalName().c_str(), ln);
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		data.SetUInt8(6);
		data.Set(ln.byteArr, 6);
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_ActionUnderThreshold.GetScriptSelector());
        e.SetValue(data);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Set value of given attribute.
int CGXDLMSLimiter::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
		m_MonitoredValue.Clear();
		m_MonitoredValue.Reserve(13);
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 3) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		m_MonitoredValue.Set(e.GetCAValue().GetCurPtr(), 11);
		e.GetCAValue().GetVar(v_info);
		unsigned short val;
		e.GetCAValue().GetUInt16(&val);
		e.GetCAValue().GetVar(v_info);
		std::string ln;
		GXHelpers::GetLogicalName(m_MonitoredValue.GetCurPtr(), ln);
		e.GetCAValue().IncreasePosition(v_info.size);
		char data_type = GetTypeAttr(ln.c_str(), (char)val);
		m_MonitoredValue.SetUInt8(DLMS_DATA_TYPE_UINT8);
		m_MonitoredValue.SetUInt8(data_type);
		e.GetCAValue().GetVar(v_info);
		m_MonitoredAttributeIndex = *(e.GetCAValue().GetCurPtr());
    }
    else if (e.GetIndex() == 3)
    {
        m_ThresholdActive = e.GetCAValue();
    }
    else if (e.GetIndex() == 4)
    {
        m_ThresholdNormal = e.GetCAValue();
    }
    else if (e.GetIndex() == 5)
    {
        m_ThresholdEmergency = e.GetCAValue();
    }
    else if (e.GetIndex() == 6)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_MinOverThresholdDuration = (long)val;
    }
    else if (e.GetIndex() == 7)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_MinUnderThresholdDuration = (long)val;
    }
    else if (e.GetIndex() == 8)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 3) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		e.GetCAValue().GetVar(v_info);
		unsigned long long val;
		unsigned char ret;
		if ((ret = e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_EmergencyProfile.SetID((unsigned short)val);
		e.GetCAValue().GetVar(v_info);
		if ((ret = GXHelpers::GetDateTime(e.GetCAValue(), m_EmergencyProfile.GetActivationTime())) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
		e.GetCAValue().GetVar(v_info);
		if ((e.GetCAValue().GetUInt(v_info.size, &val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
        m_EmergencyProfile.SetDuration((unsigned long)val);
    }
    else if (e.GetIndex() == 9)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
        m_EmergencyProfileGroupIDs.clear();
		unsigned short val;
		unsigned char ret;
        for (unsigned short i = 0; i < v_info.size; ++i)
        {
			e.GetCAValue().GetVar(v_info);
			if (v_info.vt != DLMS_DATA_TYPE_UINT16) {
				return DLMS_ERROR_CODE_INVALID_PARAMETER;
			}
			if ((ret = e.GetCAValue().GetUInt16(&val)) != DLMS_ERROR_CODE_OK) {
				return ret;
			}
            m_EmergencyProfileGroupIDs.push_back(val);
        }
    }
    else if (e.GetIndex() == 10)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
        m_EmergencyProfileActive = *(e.GetCAValue().GetCurPtr());
    }
    else if (e.GetIndex() == 11)
    {
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 2) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		e.GetCAValue().GetVar(v_info);
		if (v_info.vt != DLMS_DATA_TYPE_STRUCTURE || v_info.size != 2) {
			return DLMS_ERROR_CODE_INVALID_PARAMETER;
		}
		e.GetCAValue().GetVar(v_info);
		std::string ln;
		unsigned short val;
		unsigned char ret;
		GXHelpers::GetLogicalName(e.GetCAValue().GetCurPtr(), ln);
		m_ActionOverThreshold.SetLogicalName(ln);
		e.GetCAValue().IncreasePosition(v_info.size);
		e.GetCAValue().GetVar(v_info);
		if ((ret = e.GetCAValue().GetUInt16(&val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
		m_ActionOverThreshold.SetScriptSelector(val);

		e.GetCAValue().GetVar(v_info);
		GXHelpers::GetLogicalName(e.GetCAValue().GetCurPtr(), ln);
		m_ActionUnderThreshold.SetLogicalName(ln);
		e.GetCAValue().IncreasePosition(v_info.size);
		e.GetCAValue().GetVar(v_info);
		if ((ret = e.GetCAValue().GetUInt16(&val)) != DLMS_ERROR_CODE_OK) {
			return ret;
		}
		m_ActionUnderThreshold.SetScriptSelector(val);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
