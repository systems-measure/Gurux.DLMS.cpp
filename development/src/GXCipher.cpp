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

#include "../include/GXCipher.h"
#include "../include/chipperingenums.h"
#include "../include/GXHelpers.h"

#define ZERO_KEY 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

const unsigned char init_row[16] = { ZERO_KEY };

unsigned char CGXCipher::round_keys[176] = { ZERO_KEY };
unsigned char CGXCipher::round_keys_not_init = 1;


CGXCipher::CGXCipher()
{

}

CGXCipher::~CGXCipher()
{

}

/**
     * Encrypt data using AES.
     *
     * @param data
     *            Encrypted data.
     * @param offset
     *            Data offset.
     * @param secret
     *            Secret.
     */
void CGXCipher::Aes1Encrypt(unsigned char * data)
{
	unsigned char buf1, buf2, i, round = 0;
	unsigned char *key = round_keys;
	for (; round < 10; ++round)
	{
		for (i = 0; i < 16; ++i)
		{
			data[i] = S_BOX[(data[i] ^ key[i]) & 0xFF];
		}
		// shift rows
		buf1 = data[1];
		data[1] = data[5];
		data[5] = data[9];
		data[9] = data[13];
		data[13] = buf1;

		buf1 = data[2];
		buf2 = data[6];
		data[2] = data[10];
		data[6] = data[14];
		data[10] = buf1;
		data[14] = buf2;

		buf1 = data[15];
		data[15] = data[11];
		data[11] = data[7];
		data[7] = data[3];
		data[3] = buf1;

		if (round < 9)
		{
			for (i = 0; i < 16; i += 4)
			{
				buf1 = (data[i] ^ data[i + 1] ^ data[i + 2] ^ data[i + 3]);
				buf2 = data[i];

				data[i] = (data[i] ^ GF_Multiply_Fast[data[i] ^ data[i + 1]] ^ buf1);

				data[i + 1] = (data[i + 1] ^ GF_Multiply_Fast[data[i + 1] ^ data[i + 2]] ^ buf1);

				data[i + 2] = (data[i + 2] ^ GF_Multiply_Fast[data[i + 2] ^ data[i + 3]] ^ buf1);

				data[i + 3] = (data[i + 3] ^ GF_Multiply_Fast[data[i + 3] ^ buf2] ^ buf1);
			}
		}
		key += 16;
	}

	for (i = 0; i < 16; ++i)
	{
		data[i] = (data[i] ^ key[i]);
	}
}

int CGXCipher::KeyExpand() {
	if (memcmp(round_keys, init_row, 16) == 0) {
		return DLMS_ERROR_CODE_HARDWARE_FAULT;
	}
	for (uint8_t round = 16; round < 176; round += 16) {
		round_keys[round] = (S_BOX[round_keys[round - 4 + 1]] ^ round_keys[round - 16] ^ R_CON[(round / 16) - 1]);
		round_keys[round + 1] = (S_BOX[round_keys[round - 4 + 2]] ^ round_keys[round - 16 + 1]);
		round_keys[round + 2] = (S_BOX[round_keys[round - 4 + 3]] ^ round_keys[round - 16 + 2]);
		round_keys[round + 3] = (S_BOX[round_keys[round - 4]] ^ round_keys[round - 16 + 3]);
		for (uint8_t i = 4; i < 16; ++i)
		{
			round_keys[round + i] = (round_keys[round - 16 + i] ^ round_keys[round + i - 4]);
		}
	}
	return DLMS_ERROR_CODE_OK;
}

void CGXCipher::SetKeyToExtKey(const unsigned char* key, unsigned char size) {
	memset(round_keys, 0, 16);
	memcpy(round_keys, key, size > 16 ? 16 : size);
	round_keys_not_init = 0;
}

bool CGXCipher::RoundKeysIsInit() {
	return round_keys_not_init ? false : true;
}

void CGXCipher::SetRoundKeysState(bool state) {
	round_keys_not_init = state ? 0 : 1;
}


void CGXCipher::Aes1Decrypt(	unsigned char * data)
{
	unsigned char buf1, buf2, buf3, buf4, i = 0;
	signed char round = 9;
	unsigned char *key = round_keys + 160;
	for (; i < 16; ++i)
	{
		data[i] = (data[i] ^ key[i]) & 0xFF;
	}
	for (; round >= 0; --round)
	{
		// shift rigth rows
		buf1 = data[13];
		data[13] = data[9];
		data[9] = data[5];
		data[5] = data[1];
		data[1] = buf1;

		buf1 = data[10];
		buf2 = data[14];
		data[14] = data[6];
		data[10] = data[2];
		data[6] = buf2;
		data[2] = buf1;

		buf1 = data[3];
		data[3] = data[7];
		data[7] = data[11];
		data[11] = data[15];
		data[15] = buf1;

		key -= 16;
		for (i = 0; i < 16; ++i)
		{
			data[i] = InvS_BOX[(data[i]) & 0xFF] ^ key[i];
		}

		if (round != 0)
		{
			//inv mix columns
			for (i = 0; i < 16; i += 4)
			{
				buf1 = (data[i] ^ data[i + 1] ^ data[i + 2] ^ data[i + 3]);
				buf2 = data[i];
				buf3 = data[i + 1];
				buf4 = GF_Multiply_Fast[GF_Multiply_Fast[GF_Multiply_Fast[buf1]]];

				data[i] = (data[i] ^ buf1 ^ buf4
					^ GF_Multiply_Fast[GF_Multiply_Fast[data[i] ^ data[i + 2]]]
					^ GF_Multiply_Fast[data[i] ^ data[i + 1]]);

				data[i + 1] = (data[i + 1] ^ buf1 ^ buf4
					^ GF_Multiply_Fast[GF_Multiply_Fast[data[i + 1] ^ data[i + 3]]]
					^ GF_Multiply_Fast[data[i + 1] ^ data[i + 2]]);

				data[i + 2] = (data[i + 2] ^ buf1 ^ buf4
					^ GF_Multiply_Fast[GF_Multiply_Fast[buf2 ^ data[i + 2]]]
					^ GF_Multiply_Fast[data[i + 2] ^ data[i + 3]]);

				data[i + 3] = (data[i + 3] ^ buf1 ^ buf4
					^ GF_Multiply_Fast[GF_Multiply_Fast[buf3 ^ data[i + 3]]]
					^ GF_Multiply_Fast[buf2 ^ data[i + 3 ]]);
			}
		}
	}
}

