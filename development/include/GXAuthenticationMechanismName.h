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

#ifndef GXAUTHENTICATIONMECHANISMNAME_H
#define GXAUTHENTICATIONMECHANISMNAME_H

#include "enums.h"
//#include <string>

class CGXAuthenticationMechanismName
{
private:
    unsigned char m_JointIsoCtt;
	unsigned char m_Country;
	unsigned short m_CountryName;
    unsigned char m_IdentifiedOrganization;
    unsigned char m_DlmsUA;
    unsigned char m_AuthenticationMechanismName;
    DLMS_AUTHENTICATION m_MechanismId;

public:
    /*
     * Constructor.
     */
    CGXAuthenticationMechanismName();

	unsigned char GetJointIsoCtt();
    void SetJointIsoCtt(unsigned char value);

	unsigned char GetCountry();
    void SetCountry(unsigned char value);

	unsigned short GetCountryName();
    void SetCountryName(unsigned short value);

	unsigned char GetIdentifiedOrganization();
    void SetIdentifiedOrganization(unsigned char value);

	unsigned char GetDlmsUA();
    void SetDlmsUA(unsigned char value);

	unsigned char GetAuthenticationMechanismName();
    void SetAuthenticationMechanismName(unsigned char value);

    DLMS_AUTHENTICATION GetMechanismId();
    void SetMechanismId(DLMS_AUTHENTICATION value);

    //std::string ToString();
};
#endif //GXAUTHENTICATIONMECHANISMNAME_H