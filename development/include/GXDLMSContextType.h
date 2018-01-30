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

#ifndef GXDLMSCONTEXTTYPE_H
#define GXDLMSCONTEXTTYPE_H

//#include <string>
#include "GXBytebuffer.h"

class CGXDLMSContextType
{
private:
	unsigned short m_MaxReceivePduSize;
	unsigned short m_MaxSendPduSize;
	unsigned char m_DlmsVersionNumber;
	char m_QualityOfService;
    DLMS_CONFORMANCE m_Conformance;
    CGXByteBuffer m_CypheringInfo;

public:

    /**
    * Server will tell what functionality is available for the client.
    * @return Available functionality.
    */
    DLMS_CONFORMANCE GetConformance();

    /**
    * Server will tell what functionality is available for the client.
    *
    * @param value
    *            Available functionality.
    */
    void SetConformance(DLMS_CONFORMANCE value);

	unsigned short GetMaxPduSize();
    void SetMaxReceivePduSize(unsigned short value);

	unsigned short GetMaxSendPduSize();
    void SetMaxSendPduSize(unsigned short value);

	unsigned char GetDlmsVersionNumber();
    void SetDlmsVersionNumber(unsigned char value);

	char GetQualityOfService();
    void SetQualityOfService(char value);

    CGXByteBuffer& GetCypheringInfo();
    void SetCypheringInfo(CGXByteBuffer& value);

    //std::string ToString();
};
#endif //GXDLMSCONTEXTTYPE_H