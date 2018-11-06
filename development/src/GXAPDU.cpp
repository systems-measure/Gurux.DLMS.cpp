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

#include "../include/GXAPDU.h"

/**
* Code application context name.
*
* @param settings
*            DLMS settings.
* @param data
*            Byte buffer where data is saved.
*/

const uint8_t gApplCntxtName_str[4] = { (BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME), // Application context name tag
                                         0x09,                                                                         // Len
                                         BER_TYPE_OBJECT_IDENTIFIER,                                                   // Tag
                                         0x07 };                                                                       // Len

void GenerateApplicationContextName(
	CGXDLMSSettings& settings,
	CGXByteBuffer& data)
{
	data.Set(gApplCntxtName_str, sizeof(gApplCntxtName_str));
	data.Set(LOGICAL_NAME_OBJECT_ID, sizeof(LOGICAL_NAME_OBJECT_ID));
}

/**
 * Parse User Information from PDU.
 */
int ParseUserInformation(
    CGXDLMSSettings& settings,
    CGXByteBuffer& data)
{
    int ret;
    unsigned short pduSize;
    unsigned char ch, len, tag;
    if ((ret = data.GetUInt8(&len)) != 0)
    {
        return ret;
    }
    if (data.GetSize() - data.GetPosition() < len)
    {
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    // Encoding the choice for user information
    if ((ret = data.GetUInt8(&tag)) != 0)
    {
        return ret;
    }
    if (tag != 0x4)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = data.GetUInt8(&len)) != 0)
    {
        return ret;
    }
    // Tag for xDLMS-Initate.response
    if ((ret = data.GetUInt8(&tag)) != 0)
    {
        return ret;
    }
	if (tag == DLMS_COMMAND_INITIATE_REQUEST)
    {
        // Optional usage field of the negotiated quality of service
        // component
        if ((ret = data.GetUInt8(&tag)) != 0)
        {
            return ret;
        }
        // CtoS.
        if (tag != 0)
        {
            if ((ret = data.GetUInt8(&len)) != 0)
            {
                return ret;
            }
            CGXByteBuffer tmp;
            tmp.Set(&data, data.GetPosition());
            settings.SetCtoSChallenge(tmp);
        }
        // Optional usage field of the negotiated quality of service
        // component
        if ((ret = data.GetUInt8(&tag)) != 0)
        {
            return ret;
        }
        // Skip if used.
        if (tag != 0)
        {
            if ((ret = data.GetUInt8(&len)) != 0)
            {
                return ret;
            }
            data.SetPosition(data.GetPosition() + len);
        }
        // Optional usage field of the proposed quality of service component
        if ((ret = data.GetUInt8(&tag)) != 0)
        {
            return ret;
        }
        // Skip if used.
        if (tag != 0)
        {
            if ((ret = data.GetUInt8(&tag)) != 0)
            {
                return ret;
			}
		}
	}
	else
	{
		return DLMS_ERROR_CODE_INVALID_TAG;
	}
	if ((ret = data.GetUInt8(&ch)) != 0)
	{
		return ret;
	}
	settings.SetDLMSVersion(ch);
	if (ch < 6)
	{
		//Invalid DLMS version number.
		return DLMS_ERROR_CODE_INVALID_VERSION_NUMBER;
	}

	// Tag for conformance block
	if ((ret = data.GetUInt8(&tag)) != 0)
	{
		return ret;
	}
    if (tag != 0x5F)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    // Old Way...
    if ((ret = data.GetUInt8(data.GetPosition(), &tag)) != 0)
    {
        return ret;
    }
    if (tag == 0x1F)
    {
        data.SetPosition(data.GetPosition() + 1);
    }
    if ((ret = data.GetUInt8(&len)) != 0)
    {
        return ret;
    }
    // The number of unused bits in the bit string.
    if ((ret = data.GetUInt8(&tag)) != 0)
    {
        return ret;
    }
    unsigned long v;
    unsigned char tmp[3];
    CGXByteBuffer bb(4);
    data.Get(tmp, 3);
    bb.SetUInt8(0);
    bb.Set(tmp, 3);
	bb.GetUInt32(&v);
	settings.SetNegotiatedConformance((DLMS_CONFORMANCE)(v & settings.GetProposedConformance()));
	if (settings.GetNegotiatedConformance() == 0) {
		return DLMS_ERROR_CODE_INVALID_PARAMETER;
	}
	if ((ret = data.GetUInt16(&pduSize)) != 0)
	{
		return ret;
	}
	//If client asks too high PDU.
	if (pduSize > settings.GetMaxServerPDUSize())
	{
		pduSize = settings.GetMaxServerPDUSize();
	}
	if ((ret = settings.SetMaxReceivePDUSize(pduSize)) != 0) {
		return ret;
	}
	return 0;
}

/**
 * Parse application context name.
 *
 * @param settings
 *            DLMS settings.
 * @param buff
 *            Received data.
 */
int ParseApplicationContextName(
    CGXDLMSSettings& settings,
    CGXByteBuffer& buff)
{
    int ret;
    unsigned char len, ch;
    // Get length.
    if ((ret = buff.GetUInt8(&len)) != 0)
    {
        return ret;
    }
    if (buff.GetSize() - buff.GetPosition() < len)
    {
        //Encoding failed. Not enough data.
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    if ((ret = buff.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x6)
    {
        //Encoding failed. Not an Object ID.
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    // Object ID length.
	if ((ret = buff.GetUInt8(&len)) != 0)
	{
		return ret;
	}

	if (buff.Compare((unsigned char*)LOGICAL_NAME_OBJECT_ID, sizeof(LOGICAL_NAME_OBJECT_ID)))
	{
		return 0;
	}
	// If ciphering is used.
	if (!buff.Compare((unsigned char*)LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING, sizeof(LOGICAL_NAME_OBJECT_ID_WITH_CIPHERING)))
	{
		return DLMS_ERROR_CODE_FALSE;
	}
	else
	{
		return 0;
	}
	return 0;
}

int ValidateAare(
	CGXDLMSSettings& settings,
	CGXByteBuffer& buff)
{
	int ret;
	unsigned char tag;
	if ((ret = buff.GetUInt8(&tag)) != 0)
	{
		return ret;
	}
	if (tag != (BER_TYPE_APPLICATION
		| BER_TYPE_CONSTRUCTED
		| PDU_TYPE_PROTOCOL_VERSION))
	{
		return DLMS_ERROR_CODE_INVALID_TAG;
	}
	return 0;
}

int UpdatePassword(
    CGXDLMSSettings& settings,
    CGXByteBuffer& buff)
{
    CGXByteBuffer tmp;
    int ret;
    unsigned char ch, len;
    if ((ret = buff.GetUInt8(&len)) != 0)
    {
        return ret;
    }

    // Get authentication information.
    if ((ret = buff.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    if (ch != 0x80)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    if ((ret = buff.GetUInt8(&len)) != 0)
    {
        return ret;
    }
    tmp.Set(&buff, buff.GetPosition(), len);
    if (settings.GetAuthentication() == DLMS_AUTHENTICATION_LOW)
    {
        settings.SetPassword(tmp);
    }
    else
    {
		if (len <= 8) {
			return DLMS_ERROR_CODE_INVALID_TAG;
		}
        settings.SetCtoSChallenge(tmp);
    }
    return 0;
}


const uint8_t valOfObjID[7] = { 0x07, 0x60, 0x85, 0x74, 0x05, 0x08, 0x02 };
int UpdateAuthentication(
    CGXDLMSSettings& settings,
    CGXByteBuffer& buff)
{
    int ret;
	uint8_t val[7];
    unsigned char ch;
    if ((ret = buff.Get(val, sizeof(val))) != 0)
    {
        return ret;
    }

	if (memcmp(valOfObjID, val, sizeof(val))) {
		return DLMS_ERROR_CODE_INVALID_TAG;
	}

    if ((ret = buff.GetUInt8(&ch)) != 0)
    {
        return ret;
    }
    if (ch > 5)
    {
        return DLMS_ERROR_CODE_INVALID_TAG;
    }
    settings.SetAuthentication((DLMS_AUTHENTICATION)ch);
	CGXByteBuffer null_psw;
	null_psw.SetUInt8('\0');
	if (settings.GetAuthentication() == DLMS_AUTHENTICATION_LOW) {
		settings.SetPassword(null_psw);
	}
	else {
		if (settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH) {
			settings.SetCtoSChallenge(null_psw);
		}
	}
    return 0;
}

const uint8_t gUserInfo_str_err[] = { DLMS_COMMAND_CONFIRMED_SERVICE_ERROR,
									  DLMS_CONFIRMED_SERVICE_ERROR_INITIATE_ERROR,
									  DLMS_SERVICE_ERROR_INITIATE,
									  DLMS_INITIATE_DLMS_VERSION_TOO_LOW };
const uint8_t gUserInfo_str[] = { DLMS_COMMAND_INITIATE_RESPONSE, // Tag for xDLMS-Initiate response
                                  0x00,                           // Usage field for the response allowed component(not used)
                                  0x06,                           // DLMS Version Number
                                  0x5F,
                                  0x1F,
                                  0x04,                           // length of the conformance block
                                  0x00};                          // encoding the number of unused bits in the bit string

void GetUserInformation(
    CGXDLMSSettings& settings,
    CGXByteBuffer& data)
{
    data.Clear();
	if (settings.GetDLMSVersion() < 6) {	
		data.Set(gUserInfo_str_err, sizeof(gUserInfo_str_err));
	}
	else {
		data.Set(gUserInfo_str, sizeof(gUserInfo_str));
		settings.GetNegotiatedConformance(data);
		data.SetUInt16(settings.GetMaxPduSize());
		data.SetUInt16(0x0007);
	}
}

const DLMS_ERROR_CODE diagnostic_res[3][4] = {
	{ DLMS_ERROR_CODE_OK, DLMS_ERROR_CODE_NO_REASON_GIVEN,                              DLMS_ERROR_CODE_APPLICATION_CONTEXT_NAME_NOT_SUPPORTED, DLMS_ERROR_CODE_OK },
    { DLMS_ERROR_CODE_OK, DLMS_ERROR_CODE_AUTHENTICATION_MECHANISM_NAME_NOT_RECOGNISED, DLMS_ERROR_CODE_AUTHENTICATION_MECHANISM_NAME_REQUIRED, DLMS_ERROR_CODE_AUTHENTICATION_FAILURE },
    { DLMS_ERROR_CODE_OK, DLMS_ERROR_CODE_OK,                                           DLMS_ERROR_CODE_INVALID_VERSION_NUMBER,                 DLMS_ERROR_CODE_OK }
};

int CGXAPDU::ParsePDU(
    CGXDLMSSettings& settings,
    CGXByteBuffer& buff,
    DLMS_SOURCE_DIAGNOSTIC& diagnostic)
{
    CGXByteBuffer tmp;
    unsigned char tag, len;
    int ret;
	settings.SetAuthentication(DLMS_AUTHENTICATION_NONE);
    diagnostic = DLMS_SOURCE_DIAGNOSTIC_NONE;
    // Get AARE tag and length
    if ((ret = ValidateAare(settings, buff)) != 0)
    {
        return ret;
    }
    if ((ret = buff.GetUInt8(&len)) != 0)
    {
        return ret;
    }
    if (len > buff.GetSize() - buff.GetPosition())
    {
        //Encoding failed. Not enough data.
        return DLMS_ERROR_CODE_OUTOFMEMORY;
    }
    DLMS_ASSOCIATION_RESULT resultComponent = DLMS_ASSOCIATION_RESULT_ACCEPTED;
    while (buff.GetPosition() < buff.GetSize())
    {
        if ((ret = buff.GetUInt8(&tag)) != 0)
        {
            return ret;
        }
        switch (tag)
        {
            //0xA1
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME:
        {
            if ((ret = ParseApplicationContextName(settings, buff)) != 0)
            {
                //return DLMS_ERROR_CODE_REJECTED_PERMAMENT;
				buff.SetPosition(buff.GetSize());
				diagnostic = DLMS_SOURCE_DIAGNOSTIC_NOT_SUPPORTED;
            }
        }
        break;
            // 0xA6 Client system title.
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLING_AP_TITLE:
            if ((ret = buff.GetUInt8(&len)) != 0)
            {
                return ret;
            }
            if ((ret = buff.GetUInt8(&tag)) != 0)
            {
                return ret;
            }
            if ((ret = buff.GetUInt8(&len)) != 0)
            {
                return ret;
            }
            tmp.Clear();
            tmp.Set(&buff, buff.GetPosition(), len);
            settings.SetSourceSystemTitle(tmp);
            break;
            //  0x8A or 0x88
        case BER_TYPE_CONTEXT | PDU_TYPE_SENDER_ACSE_REQUIREMENTS:
        case BER_TYPE_CONTEXT | PDU_TYPE_CALLING_AP_INVOCATION_ID:
            // Get sender ACSE-requirements field component.
            if ((ret = buff.GetUInt8(&len)) != 0)
            {
                return ret;
            }
            if (len != 2)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            if ((ret = buff.GetUInt8(&tag)) != 0)
            {
                return ret;
            }
            if (tag != BER_TYPE_OBJECT_DESCRIPTOR)
            {
                return DLMS_ERROR_CODE_INVALID_TAG;
            }
            //Get only value because client app is sending system title with LOW authentication.
            if ((ret = buff.GetUInt8(&tag)) != 0)
            {
                return ret;
            }
			if (tag != 0x80) {
				buff.SetPosition(buff.GetSize());
				diagnostic  = DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
			}
            break;
            //  0x8B or 0x89
        case BER_TYPE_CONTEXT | PDU_TYPE_MECHANISM_NAME:
        case BER_TYPE_CONTEXT | PDU_TYPE_CALLING_AE_INVOCATION_ID:
            if ((ret = UpdateAuthentication(settings, buff)) != 0)
            {
                return ret;
            }
            break;
            // 0xAC
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_CALLING_AUTHENTICATION_VALUE:
            if ((ret = UpdatePassword(settings, buff)) != 0)
            {
				buff.SetPosition(buff.GetSize());
				diagnostic = DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_FAILURE;
            }
            break;
            // 0xBE
        case BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_USER_INFORMATION:
            if (resultComponent != DLMS_ASSOCIATION_RESULT_ACCEPTED
                && diagnostic != DLMS_SOURCE_DIAGNOSTIC_NONE)
            {
                return DLMS_ERROR_CODE_REJECTED_PERMAMENT;
            }
            if ((ret = ParseUserInformation(settings, buff)) != 0)
            {
				buff.SetPosition(buff.GetSize());
                diagnostic = DLMS_SOURCE_DIAGNOSTIC_NO_REASON_GIVEN;
				if (ret == DLMS_ERROR_CODE_INVALID_VERSION_NUMBER) {
					return ret;
				}
            }
            break;
		case BER_TYPE_CONTEXT| PDU_TYPE_PROTOCOL_VERSION:
		{
			if ((ret = buff.GetUInt8(&len)) != 0) {
				return ret;
			}
			if ((ret = buff.GetUInt8(&len)) != 0) {
				return ret;
			}
			unsigned char ver;
			unsigned char cur_ver = 0x01 << (settings.GetDLMSVersion() - 1);

			if ((ret = buff.GetUInt8(&ver)) != 0) {
				return ret;
			}
			if ((cur_ver & (ver >> len)) == 0) {
				buff.SetPosition(buff.GetSize());
				diagnostic = DLMS_SOURCE_DIAGNOSTIC_ASCE_NO_COMMON_VERSION;
			}
			break;
		}
        default:
            // Unknown tags.
            if (buff.GetPosition() < buff.GetSize())
            {
                if ((ret = buff.GetUInt8(&len)) != 0)
                {
                    return ret;
                }
                buff.SetPosition(buff.GetPosition() + len);
            }
            break;
        }
    }

	if (diagnostic < DLMS_SOURCE_DIAGNOSTIC_ASCE_NO_COMMON_VERSION) {
		return diagnostic_res[diagnostic / 10][diagnostic % 10];
	}
    return 0;
}

/**
 * Server generates AARE message.
 */

const uint8_t gAARERes_str[24] = { BER_TYPE_APPLICATION | BER_TYPE_CONSTRUCTED | PDU_TYPE_APPLICATION_CONTEXT_NAME, // Set AARE tag and length 0x61
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,          // Length and application context name are updated later
	                             BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | BER_TYPE_INTEGER,                      // Result 0xA2
	                             0x03,                                                                            // len
	                             BER_TYPE_INTEGER,                                                                // Tag
	                             0x01,                                                                            // Len
	                             0x00,                                                                            // ResultValue is updated later
	                             0xA3,                                                                            // 0xA3 SourceDiagnostic
	                             0x05,                                                                            // len
	                             0x00,                                                                            // Tag is updated later
	                             0x03,                                                                            // len
	                             0x02,                                                                            // Tag
	                             0x01                                                                             // len
};

const uint8_t gAARESysTitle_str[12] = { 0x88,              // Add server ACSE-requirenents field component.
                                        0x02,              // Len
                                        0x07,              // value
                                        0x80,			   //
                                        0x89,              // Tag
                                        0x07,              // Len
                                        0x60,              // value
                                        0x85,			   //
                                        0x74,			   //
                                        0x05,			   //
                                        0x08,			   //
                                        0x02
};

void CGXAPDU::GenerateAARE(
    CGXDLMSSettings& settings,
    CGXByteBuffer& data,
    DLMS_ASSOCIATION_RESULT result,
    DLMS_SOURCE_DIAGNOSTIC diagnostic)
{
    unsigned long offset = data.GetSize();
	data.Capacity(offset + sizeof(gAARERes_str) + sizeof(gAARESysTitle_str) + 2);
	// Result 0xA2
	data.Set(gAARERes_str, sizeof(gAARERes_str));
	data.SetSize(offset + 2);
	GenerateApplicationContextName(settings, data);
	data.SetUInt8(offset + 17, result);
	data.SetUInt8(offset + 20, 0xA1 + diagnostic / 20);
	data.SetSize(offset + 24);
	data.SetUInt8(diagnostic % 20);

	// SystemTitle
	if (result != DLMS_ASSOCIATION_RESULT_PERMANENT_REJECTED
		&& diagnostic == DLMS_SOURCE_DIAGNOSTIC_AUTHENTICATION_REQUIRED)
	{
		data.Set(gAARESysTitle_str, sizeof(gAARESysTitle_str));
		data.SetSize(offset + 37);
		data.SetUInt8(settings.GetAuthentication());
		// Add tag.
		data.SetUInt8(0xAA);
		GXHelpers::SetObjectCount(2 + settings.GetStoCChallenge().GetSize(), data); // Len
		data.SetUInt8(BER_TYPE_CONTEXT);
		GXHelpers::SetObjectCount(settings.GetStoCChallenge().GetSize(), data);
		data.Set(settings.GetStoCChallenge().GetData(), settings.GetStoCChallenge().GetSize());
	}

    // Add User Information
    // Tag 0xBE
    data.SetUInt8(BER_TYPE_CONTEXT | BER_TYPE_CONSTRUCTED | PDU_TYPE_USER_INFORMATION);
    CGXByteBuffer tmp;
	GetUserInformation(settings, tmp);
    GXHelpers::SetObjectCount(2 + tmp.GetSize(), data);
    // Coding the choice for user-information (Octet STRING, universal)
    data.SetUInt8(BER_TYPE_OCTET_STRING);
    // Length
    GXHelpers::SetObjectCount(tmp.GetSize(), data);
    data.Set(&tmp);
    data.SetUInt8(offset + 1, (unsigned char)(data.GetSize() - offset - 2));
}