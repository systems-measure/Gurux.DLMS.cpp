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
#ifndef CGXDLMSATTRIBUTE_H
#define CGXDLMSATTRIBUTE_H

#include "enums.h"

class CGXDLMSAttribute
{
	signed char				m_index;
    DLMS_ACCESS_MODE		m_Access;
    DLMS_DATA_TYPE			m_Type;
    DLMS_METHOD_ACCESS_MODE	m_MethodAccess;

    void Initialize(signed char index, DLMS_DATA_TYPE Type, DLMS_ACCESS_MODE Access)
    {
		m_index = index;
        m_Access = Access;
        m_Type = Type;
        m_MethodAccess = DLMS_METHOD_ACCESS_MODE_NONE;
    }

public:
    //Constructor.
    CGXDLMSAttribute(signed char index = 0, DLMS_DATA_TYPE Type = DLMS_DATA_TYPE_NONE, DLMS_ACCESS_MODE Access = DLMS_ACCESS_MODE_READ)
    {
        Initialize(index, Type, Access);
    }

	signed char& GetIndex() {
		return m_index;
	}

	void SetIndex(signed char index) {
		m_index = index;
	}

    /// <summary>
    /// Attribute data type.
    /// </summary>
    DLMS_DATA_TYPE& GetDataType()
    {
        return m_Type;
    }

    void SetDataType(DLMS_DATA_TYPE type)
    {
        m_Type = type;
    }

    /// <summary>
    /// Data type that user want's to see.
    /// </summary>
    DLMS_DATA_TYPE& GetUIDataType()
    {
        return m_Type;
    }

    void SetUIDataType(DLMS_DATA_TYPE type)
    {
  
    }

    DLMS_ACCESS_MODE& GetAccess()
    {
        return m_Access;
    }
    void SetAccess(DLMS_ACCESS_MODE value)
    {
        m_Access = value;
    }

    DLMS_METHOD_ACCESS_MODE& GetMethodAccess()
    {
        return m_MethodAccess;
    }

    void SetMethodAccess(DLMS_METHOD_ACCESS_MODE value)
    {
        m_MethodAccess = value;
    }

};

#endif //CGXDLMSATTRIBUTE_H