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

#include "../include/GXApplicationContextName.h"
#include "../include/GXDLMSVariant.h"

std::string CGXApplicationContextName::GetLogicalName()
{
    return m_LogicalName;
}

void CGXApplicationContextName::SetLogicalName(std::string value)
{
    m_LogicalName = value;
}

unsigned char CGXApplicationContextName::GetJointIsoCtt()
{
    return m_JointIsoCtt;
}
void CGXApplicationContextName::SetJointIsoCtt(unsigned char value)
{
    m_JointIsoCtt = value;
}

unsigned char CGXApplicationContextName::GetCountry()
{
    return m_Country;
}
void CGXApplicationContextName::SetCountry(unsigned char value)
{
    m_Country = value;
}

unsigned short CGXApplicationContextName::GetCountryName()
{
    return m_CountryName;
}
void CGXApplicationContextName::SetCountryName(unsigned short value)
{
    m_CountryName = value;
}

unsigned char CGXApplicationContextName::GetIdentifiedOrganization()
{
    return m_IdentifiedOrganization;
}
void CGXApplicationContextName::SetIdentifiedOrganization(unsigned char value)
{
    m_IdentifiedOrganization = value;
}

unsigned char CGXApplicationContextName::GetDlmsUA()
{
    return m_DlmsUA;
}
void CGXApplicationContextName::SetDlmsUA(unsigned char value)
{
    m_DlmsUA = value;
}

unsigned char CGXApplicationContextName::GetApplicationContext()
{
    return m_ApplicationContext;
}
void CGXApplicationContextName::SetApplicationContext(unsigned char value)
{
    m_ApplicationContext = value;
}

unsigned char CGXApplicationContextName::GetContextId()
{
    return m_ContextId;
}
void CGXApplicationContextName::SetContextId(unsigned char value)
{
    m_ContextId = value;
}
