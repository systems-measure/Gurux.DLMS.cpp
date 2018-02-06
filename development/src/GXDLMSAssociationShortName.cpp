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

#include "../include/GXDLMSVariant.h"
#include "../include/GXDLMSClient.h"
#include "../include/GXDLMSAssociationShortName.h"
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSServer.h"

int CGXDLMSAssociationShortName::GetAccessRights(CGXDLMSObject* pObj, CGXDLMSServer* server, CGXByteBuffer& data)
{
    return DLMS_ERROR_CODE_OK;
}

void CGXDLMSAssociationShortName::UpdateAccessRights(CGXDLMSVariant& buff)
{

}

//Constructor.
CGXDLMSAssociationShortName::CGXDLMSAssociationShortName() : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME)
{
    GXHelpers::SetLogicalName("0.0.40.0.0.255", m_LN);
    m_LlsSecret.AddString("Gurux");
    m_HlsSecret.AddString("Gurux");
}

CGXDLMSObjectCollection& CGXDLMSAssociationShortName::GetObjectList()
{
    return m_ObjectList;
}

CGXByteBuffer& CGXDLMSAssociationShortName::GetSecret()
{
    return m_LlsSecret;
}
void CGXDLMSAssociationShortName::SetSecret(CGXByteBuffer& value)
{
    m_LlsSecret = value;
}

// Returns amount of attributes.
int CGXDLMSAssociationShortName::GetAttributeCount()
{
    return 4;
}

// Returns amount of methods.
int CGXDLMSAssociationShortName::GetMethodCount()
{
    return 8;
}

int CGXDLMSAssociationShortName::GetDataType(signed char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 3)
    {
        type = DLMS_DATA_TYPE_ARRAY;
    }
    else if (index == 4)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns SN Association View.
int CGXDLMSAssociationShortName::GetObjects(
    CGXDLMSSettings& settings,
    CGXDLMSValueEventArg& e,
    CGXByteBuffer& data)
{
   
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSAssociationShortName::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
   
    return 0;
}

int CGXDLMSAssociationShortName::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
  
    return DLMS_ERROR_CODE_OK;
}

int CGXDLMSAssociationShortName::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
   
    return DLMS_ERROR_CODE_OK;
}
