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

#include "../include/GXDLMSContextType.h"
#include "../include/GXDLMSVariant.h"
#include "../include/GXHelpers.h"

DLMS_CONFORMANCE CGXDLMSContextType::GetConformance()
{
    return m_Conformance;
}
void CGXDLMSContextType::SetConformance(DLMS_CONFORMANCE value)
{
    m_Conformance = value;
}

unsigned short CGXDLMSContextType::GetMaxPduSize()
{
    return m_MaxReceivePduSize;
}
void CGXDLMSContextType::SetMaxReceivePduSize(unsigned short value)
{
    m_MaxReceivePduSize = value;
}

unsigned short CGXDLMSContextType::GetMaxSendPduSize()
{
    return m_MaxSendPduSize;
}
void CGXDLMSContextType::SetMaxSendPduSize(unsigned short value)
{
    m_MaxSendPduSize = value;
}

unsigned char CGXDLMSContextType::GetDlmsVersionNumber()
{
    return m_DlmsVersionNumber;
}
void CGXDLMSContextType::SetDlmsVersionNumber(unsigned char value)
{
    m_DlmsVersionNumber = value;
}
char CGXDLMSContextType::GetQualityOfService()
{
    return m_QualityOfService;
}
void CGXDLMSContextType::SetQualityOfService(char value)
{
    m_QualityOfService = value;
}

CGXByteBuffer& CGXDLMSContextType::GetCypheringInfo()
{
    return m_CypheringInfo;
}

void CGXDLMSContextType::SetCypheringInfo(CGXByteBuffer& value)
{
    m_CypheringInfo = value;
}
