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

#include "../include/GXSecure.h"
#include <stdlib.h> //rand

int CGXSecure::GenerateChallenge(DLMS_AUTHENTICATION authentication, CGXByteBuffer& challenge)
{
    // Random challenge is 8 to 64 bytes.
    // Texas Instruments accepts only 16 byte long challenge.
    // For this reason challenge size is 16 bytes at the moment.
    int len = 16;
    //int len = rand() % 58 + 8;
    unsigned char val;
    for (int pos = 0; pos != len; ++pos)
    {
        val = rand();
        challenge.SetUInt8(val);
    }
    return 0;
}

/**
    * Chipher text.
    *
    * @param auth
    *            Authentication level.
    * @param data
    *            Text to chipher.
    * @param secret
    *            Secret.
    * @return Chiphered text.
    */
int CGXSecure::Secure(
    CGXDLMSSettings& settings,
    CGXByteBuffer& data,
	const unsigned char* secret,
    CGXByteBuffer& reply)
{
    int ret = 0, pos;
    reply.Clear();
    if (settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH)
    {
        int len = data.GetSize();
        if (len % 16 != 0)
        {
            len += (16 - (data.GetSize() % 16));
        }
		if (!CGXCipher::RoundKeysIsInit()) {
			CGXCipher::SetKeyToExtKey(secret, strlen((const char*)secret));
			if ((ret = CGXCipher::KeyExpand()) != DLMS_ERROR_CODE_OK) {
				return ret;
			}
		}
        reply.Set(&data);
        reply.Zero(reply.GetSize(), len - reply.GetSize());
        for (pos = 0; pos < len / 16; ++pos)
        {
            CGXCipher::Aes1Encrypt(reply.GetData() + pos * 16);
        }
        return 0;
    }
    return ret;
}

void CGXSecure::UnSecure(
	CGXDLMSSettings& settings,
	unsigned char* data,
	unsigned char size_data,
	CGXByteBuffer& reply) {
	int pos;
	reply.Clear();
	if (settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH)
	{
		if (size_data % 16 != 0)
		{
			size_data += (16 - (size_data % 16));
		}
		reply.Set(data, size_data);
		reply.Zero(reply.GetSize(), size_data - reply.GetSize());
		for (pos = 0; pos < size_data / 16; ++pos)
		{
			CGXCipher::Aes1Decrypt(reply.GetData() + pos * 16);
		}
	}
}