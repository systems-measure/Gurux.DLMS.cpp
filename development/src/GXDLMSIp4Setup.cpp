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

#include "../include/GXDLMSIp4Setup.h"

#if defined(_WIN32) || defined(_WIN64)//Windows includes
#include "pcap.h"
#elif !defined(__ICCARM__)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#endif


//Constructor.
CGXDLMSIp4Setup::CGXDLMSIp4Setup() : CGXDLMSObject(DLMS_OBJECT_TYPE_IP4_SETUP)
{
    
}

//LN Constructor.
CGXDLMSIp4Setup::CGXDLMSIp4Setup(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_IP4_SETUP, ln)
{
   
}

// Returns amount of attributes.
unsigned char CGXDLMSIp4Setup::GetAttributeCount()
{
    return 10;
}

// Returns amount of methods.
unsigned char CGXDLMSIp4Setup::GetMethodCount()
{
    return 3;
}

const DLMS_DATA_TYPE IP4_TypeArr[] = { DLMS_DATA_TYPE_NONE, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_OCTET_STRING, DLMS_DATA_TYPE_UINT32, DLMS_DATA_TYPE_ARRAY, DLMS_DATA_TYPE_ARRAY,
                                       DLMS_DATA_TYPE_UINT32, DLMS_DATA_TYPE_UINT32, DLMS_DATA_TYPE_BOOLEAN, DLMS_DATA_TYPE_UINT32, DLMS_DATA_TYPE_UINT32 };

int CGXDLMSIp4Setup::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
	if (index >= 1 && index <= 10) {
		type = IP4_TypeArr[index];
		return DLMS_ERROR_CODE_OK;
	}
	return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

DLMS_DATA_TYPE CGXDLMSIp4Setup::GetDataType(signed char index) {
	if (index >= 1 && index <= 10) {
		return IP4_TypeArr[index];
	}
	return DLMS_DATA_TYPE_NONE;
}