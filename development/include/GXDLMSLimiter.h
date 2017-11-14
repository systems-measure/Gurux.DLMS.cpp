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

#ifndef GXDLMSLIMITER_H
#define GXDLMSLIMITER_H

#include "GXDLMSObject.h"
#include "GXDLMSEmergencyProfile.h"
#include "GXDLMSActionItem.h"

class CGXDLMSLimiter : public CGXDLMSObject
{
	// format monitored_value: uint16 iclass, octet_str[6] ln, uint8 attr data type 
	CArtVariant m_MonitoredValue;
    CArtVariant m_ThresholdActive;
	CArtVariant m_ThresholdNormal;
	CArtVariant m_ThresholdEmergency;
    unsigned long m_MinOverThresholdDuration;
	unsigned long m_MinUnderThresholdDuration;
    CGXDLMSEmergencyProfile m_EmergencyProfile;
    std::vector<unsigned short> m_EmergencyProfileGroupIDs;
    bool m_EmergencyProfileActive;
	unsigned char m_MonitoredAttributeIndex;
    CGXDLMSActionItem m_ActionOverThreshold;
    CGXDLMSActionItem m_ActionUnderThreshold;
public:
    //Constructor.
    CGXDLMSLimiter();

    //LN Constructor.
    CGXDLMSLimiter(const char* ln);


    /**
     Defines an attribute of an object to be monitored.
    */
	CArtVariant GetMonitoredValue();
    void SetMonitoredValue(CArtVariant& value);

    /**
     Provides the active threshold value to which the attribute monitored is compared.
    */
	CArtVariant& GetThresholdActive();
    void SetThresholdActive(CArtVariant& value);

    /**
     Provides the threshold value to which the attribute monitored
     is compared when in normal operation.
    */
	CArtVariant& GetThresholdNormal();
    void SetThresholdNormal(CArtVariant& value);

    /**
     Provides the threshold value to which the attribute monitored
     is compared when an emergency profile is active.
    */
	CArtVariant& GetThresholdEmergency();
    void SetThresholdEmergency(CArtVariant& value);

    /**
     Defines minimal over threshold duration in seconds required
     to execute the over threshold action.
    */
	unsigned long GetMinOverThresholdDuration();
    void SetMinOverThresholdDuration(unsigned long value);

    /**
     Defines minimal under threshold duration in seconds required to
     execute the under threshold action.
    */
	unsigned long GetMinUnderThresholdDuration();
    void SetMinUnderThresholdDuration(unsigned long value);

    CGXDLMSEmergencyProfile& GetEmergencyProfile();
    void SetEmergencyProfile(CGXDLMSEmergencyProfile value);

    std::vector<unsigned short>& GetEmergencyProfileGroupIDs();
    void SetEmergencyProfileGroupIDs(std::vector<unsigned short>& value);

    /**
     Is Emergency Profile active.
    */
    bool GetEmergencyProfileActive();
    void SetEmergencyProfileActive(bool value);

    /**
     Defines the scripts to be executed when the monitored value
     crosses the threshold for minimal duration time.
    */
    CGXDLMSActionItem& GetActionOverThreshold();
    void SetActionOverThreshold(CGXDLMSActionItem value);

    /**
     Defines the scripts to be executed when the monitored value
     crosses the threshold for minimal duration time.
    */
    CGXDLMSActionItem& GetActionUnderThreshold();
    void SetActionUnderThreshold(CGXDLMSActionItem value);

    // Returns amount of attributes.
    int GetAttributeCount();

    // Returns amount of methods.
    int GetMethodCount();

    //Get attribute values of object.
    void GetValues(std::vector<std::string>& values);

    void GetAttributeIndexToRead(std::vector<int>& attributes);

    int GetDataType(unsigned char index, DLMS_DATA_TYPE& type);

    // Returns value of given attribute.
    int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);

    // Set value of given attribute.
    int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e);
};
#endif //GXDLMSLIMITER_H