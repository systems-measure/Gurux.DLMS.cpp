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

#ifndef GXDLMSIECHDLCSETUP_H
#define GXDLMSIECHDLCSETUP_H

#include "GXDLMSObject.h"

class CGXDLMSIecHdlcSetup : public CGXDLMSObject
{
	/*unsigned short m_InactivityTimeout;
	unsigned short m_DeviceAddress;
	unsigned short m_MaximumInfoLengthTransmit;
	unsigned short m_InterCharachterTimeout;
	unsigned short m_MaximumInfoLengthReceive;
	unsigned char m_WindowSizeTransmit;
	unsigned char m_WindowSizeReceive;
    DLMS_BAUD_RATE m_CommunicationSpeed;	*/

public:
    //Constructor.
    CGXDLMSIecHdlcSetup();

    //SN Constructor.
    CGXDLMSIecHdlcSetup(unsigned short sn);

    //LN Constructor.
    CGXDLMSIecHdlcSetup(const char* ln);

    /*DLMS_BAUD_RATE GetCommunicationSpeed();

    void SetCommunicationSpeed(DLMS_BAUD_RATE value);

	unsigned char GetWindowSizeTransmit();
    void SetWindowSizeTransmit(unsigned char value);

	unsigned char GetWindowSizeReceive();
    void SetWindowSizeReceive(unsigned char value);
	unsigned short GetMaximumInfoLengthTransmit();
    void SetMaximumInfoLengthTransmit(unsigned short value);
	unsigned short GetMaximumInfoLengthReceive();
    void SetMaximumInfoLengthReceive(unsigned short value);

	unsigned short GetInterCharachterTimeout();
    void SetInterCharachterTimeout(unsigned short value);


	unsigned short GetInactivityTimeout();
    void SetInactivityTimeout(unsigned short value);

	unsigned short GetDeviceAddress();
    void SetDeviceAddress(unsigned short value);*/

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
#endif //GXDLMSIECHDLCSETUP_H