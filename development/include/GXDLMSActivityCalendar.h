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

#ifndef GXDLMSACTIVITYCALENDAR_H
#define GXDLMSACTIVITYCALENDAR_H

#include "GXDLMSObject.h"

class CGXDLMSActivityCalendar : public CGXDLMSObject
{
public:
    //Constructor.
    CGXDLMSActivityCalendar();

    //LN Constructor.
    CGXDLMSActivityCalendar(const char* ln);

    //Destructor.
    ~CGXDLMSActivityCalendar();

    // Returns amount of attributes.
	unsigned char GetAttributeCount();

    // Returns amount of methods.
	unsigned char GetMethodCount();

    int GetDataType(signed char index, DLMS_DATA_TYPE& type);
	DLMS_DATA_TYPE GetDataType(signed char index) override;

};
#endif //GXDLMSACTIVITYCALENDAR_H