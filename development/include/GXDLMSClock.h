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

#ifndef GXDLMSCLOCK_H
#define GXDLMSCLOCK_H

#include "GXDLMSObject.h"

class CGXDLMSClock : public CGXDLMSObject
{

public:
    /**
     Constructor.
    */
    CGXDLMSClock();

    /**
     Constructor.
     @param ln Logical Name of the object.
    */
    CGXDLMSClock(const char* ln);

    // Returns amount of attributes.
    int GetAttributeCount();

    // Returns amount of methods.
    int GetMethodCount();

    int GetDataType(signed char index, DLMS_DATA_TYPE& type);
	DLMS_DATA_TYPE GetDataType(signed char index) override;

};
#endif //GXDLMSCLOCK_H
