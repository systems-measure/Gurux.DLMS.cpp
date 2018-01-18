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

#include "../include/GXDLMSRegisterMonitor.h"
#include "../include/GXDLMSClient.h"

/**
 Constructor.
*/
CGXDLMSRegisterMonitor::CGXDLMSRegisterMonitor() : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER_MONITOR)
{
}

/**
 Constructor.

 @param ln Logical Name of the object.
*/
CGXDLMSRegisterMonitor::CGXDLMSRegisterMonitor(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_REGISTER_MONITOR, ln)
{
}


CGXDLMSRegisterMonitor::~CGXDLMSRegisterMonitor()
{
    for (std::vector<CGXDLMSActionSet*>::iterator it = m_Actions.begin(); it != m_Actions.end(); ++it)
    {
        delete *it;
    }
    m_Actions.clear();
    m_Thresholds.clear();
}

std::vector<CGXDLMSVariant> CGXDLMSRegisterMonitor::GetThresholds()
{
    return m_Thresholds;
}
void CGXDLMSRegisterMonitor::SetThresholds(std::vector<CGXDLMSVariant> value)
{
    m_Thresholds = value;
}

CGXDLMSMonitoredValue& CGXDLMSRegisterMonitor::GetMonitoredValue()
{
    return m_MonitoredValue;
}
void CGXDLMSRegisterMonitor::SetMonitoredValue(CGXDLMSMonitoredValue& value)
{
    m_MonitoredValue = value;
}

std::vector<CGXDLMSActionSet*>& CGXDLMSRegisterMonitor::GetActions()
{
    return m_Actions;
}

// Returns amount of attributes.
int CGXDLMSRegisterMonitor::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSRegisterMonitor::GetMethodCount()
{
    return 0;
}

int CGXDLMSRegisterMonitor::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Returns value of given attribute.
 */
int CGXDLMSRegisterMonitor::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
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
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 3)
    {
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

/*
 * Set value of given attribute.
 */
int CGXDLMSRegisterMonitor::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    if (e.GetIndex() == 2)
    {
        
    }
    if (e.GetIndex() == 3)
    {
      
    }
    if (e.GetIndex() == 4)
    {
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}
