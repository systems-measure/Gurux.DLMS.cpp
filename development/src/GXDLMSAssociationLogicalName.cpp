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
#include "../include/GXDLMSObjectFactory.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSServer.h"

void CGXDLMSAssociationLogicalName::Init()
{
    m_AssociationStatus = DLMS_DLMS_ASSOCIATION_STATUS_NON_ASSOCIATED;
    m_LlsSecret.AddString("111");
    m_HlsSecret.AddString("12345");
}

void CGXDLMSAssociationLogicalName::UpdateAccessRights(CGXDLMSObject* pObj, CGXDLMSVariant data)
{
    /*for (std::vector<CGXDLMSVariant >::iterator it = data.Arr[0].Arr.begin(); it != data.Arr[0].Arr.end(); ++it)
    {
        int id = it->Arr[0].ToInteger();
        DLMS_ACCESS_MODE mode = (DLMS_ACCESS_MODE)it->Arr[1].ToInteger();
        pObj->SetAccess(id, mode);
    }
    for (std::vector<CGXDLMSVariant >::iterator it = data.Arr[1].Arr.begin(); it != data.Arr[1].Arr.end(); ++it)
    {
        int id = it->Arr[0].ToInteger();
        DLMS_METHOD_ACCESS_MODE mode = (DLMS_METHOD_ACCESS_MODE)it->Arr[1].ToInteger();
        pObj->SetMethodAccess(id, mode);
    }*/
}

int CGXDLMSAssociationLogicalName::GetAccessRights(CGXDLMSObject* pItem, CGXDLMSServer* server, CGXByteBuffer& data)
{
    int8_t cnt = (int8_t)pItem->GetAttributeCount();
    data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
    data.SetUInt8(2);
    data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    GXHelpers::SetObjectCount(cnt, data);
    CGXDLMSValueEventArg e(server, pItem, 0);
	int8_t index, access;
    for (int8_t pos = 0; pos != cnt; ++pos)
    {
        e.SetIndex(pos + 1);
        index = pos + 1;
        if (server != NULL)
        {
            access = server->GetAttributeAccess(&e);
        }
        else
        {
            access = DLMS_ACCESS_MODE_READ_WRITE;
        }
        //attribute_access_item
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(3);
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(index);
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(access);
		data.SetUInt8(DLMS_DATA_TYPE_NONE);
    }
    cnt = pItem->GetMethodCount();
    data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
    GXHelpers::SetObjectCount(cnt, data);
    for (int8_t pos = 0; pos != cnt; ++pos)
    {
        e.SetIndex(pos + 1);
        index = pos + 1;
        if (server != NULL)
        {
            access = server->GetMethodAccess(&e);
        }
        else
        {
            access = DLMS_METHOD_ACCESS_MODE_ACCESS;
        }
        //attribute_access_item
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(2);
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(index);
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8(access);
    }
    return DLMS_ERROR_CODE_OK;
}

// Returns LN Association View.
int CGXDLMSAssociationLogicalName::GetObjects(
    CGXDLMSSettings& settings,
    CGXDLMSValueEventArg& e,
    CGXByteBuffer& data)
{
    int ret;
    //Add count only for first time.
    if (settings.GetIndex() == 0)
    {
		m_pos = 0;
		settings.SetCount((unsigned short)m_ObjectList.size() + m_ObjectList.sizeRequiredObj());
		if(e.GetTarget()->GetName().compare("0.0.40.0.2.255") == 0){
			settings.SetCount(settings.GetCount() - 1);
		}
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        //Add count
        GXHelpers::SetObjectCount((unsigned long)settings.GetCount(), data);
    }
	CGXDLMSObject* tmp_obj = nullptr;
	CGXByteBuffer ln;
	if (m_pos < m_ObjectList.size()) {
		CGXDLMSObjectCollection::iterator it = m_ObjectList.begin();
		it += m_pos;
		for (it; it != m_ObjectList.end(); ++it)
		{
			ln.Clear();
			ln.Set(*it, 6);
			tmp_obj = m_ObjectList.FindByLN(DLMS_OBJECT_TYPE_ALL, ln);
			if (tmp_obj != NULL) {
				++m_pos;
				if (m_pos <= settings.GetCount())
				{
					data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
					data.SetUInt8(4);//Count
					data.SetUInt8(DLMS_DATA_TYPE_UINT16);
					data.SetUInt16(tmp_obj->GetObjectType());//ClassID
					data.SetUInt8(DLMS_DATA_TYPE_UINT8);
					data.SetUInt8(tmp_obj->GetVersion());//Version
					data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
					data.SetUInt8(0x06);
					data.Set(tmp_obj->m_LN, 6);//LN
											   //Access rights.
					if ((ret = GetAccessRights(tmp_obj, e.GetServer(), data)) != 0)
					{
						tmp_obj = nullptr;
						m_ObjectList.FreeConstructedObj();
						return ret;
					};
					if (settings.IsServer())
					{
						settings.SetIndex(settings.GetIndex() + 1);
						//If PDU is full.
						if (!e.GetSkipMaxPduSize() && data.GetSize() >= settings.GetMaxPduSize())
						{
							m_ObjectList.FreeConstructedObj();
							tmp_obj = nullptr;
							break;
						}
					}
				}
			}
			m_ObjectList.FreeConstructedObj();
			tmp_obj = nullptr;

		}
	}
	if (data.GetSize() < settings.GetMaxPduSize() || e.GetSkipMaxPduSize())
	{
		std::vector<CGXDLMSObject*> tmp_dlms_obj = m_ObjectList.GetDlmsObj();
		std::vector<CGXDLMSObject*>::iterator it = tmp_dlms_obj.begin();
		if (settings.GetCount() == m_ObjectList.size() + m_ObjectList.sizeRequiredObj() - 1) {
			++it;
		}
		it += m_pos - m_ObjectList.size();
		for (; it != tmp_dlms_obj.end(); ++it) {
			++m_pos;
			if (m_pos <= settings.GetCount())
			{
				data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
				data.SetUInt8(4);//Count
				data.SetUInt8(DLMS_DATA_TYPE_UINT16);
				data.SetUInt16((*it)->GetObjectType());//ClassID
				data.SetUInt8(DLMS_DATA_TYPE_UINT8);
				data.SetUInt8((*it)->GetVersion());//Version
				data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
				data.SetUInt8(0x06);
				data.Set((*it)->m_LN, 6);//LN
				//Access rights.
				if ((ret = GetAccessRights((*it), e.GetServer(), data)) != 0)
				{
					return ret;
				};
				if (settings.IsServer())
				{
					settings.SetIndex(settings.GetIndex() + 1);
					//If PDU is full.
					if (!e.GetSkipMaxPduSize() && data.GetSize() >= settings.GetMaxPduSize())
					{
						break;
					}
				}
			}
		}
	}
	return DLMS_ERROR_CODE_OK;
}

/**
 Constructor.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName() : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, "0.0.40.0.0.255")
{
    Init();
}

/**
 Constructor.
 @param ln Logical Name of the object.
*/
CGXDLMSAssociationLogicalName::CGXDLMSAssociationLogicalName(const char* ln) : CGXDLMSObject(DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME, ln)
{
    Init();
}

CGXDLMSObjectCollection& CGXDLMSAssociationLogicalName::GetObjectList()
{
    return m_ObjectList;
}

unsigned char CGXDLMSAssociationLogicalName::GetClientSAP()
{
    return m_ClientSAP;
}
void CGXDLMSAssociationLogicalName::SetClientSAP(unsigned char value)
{
    m_ClientSAP = value;
}

unsigned short CGXDLMSAssociationLogicalName::GetServerSAP()
{
    return m_ServerSAP;
}

void CGXDLMSAssociationLogicalName::SetServerSAP(unsigned short value)
{
    m_ServerSAP = value;
}

CGXApplicationContextName CGXDLMSAssociationLogicalName::GetApplicationContextName()
{
    return m_ApplicationContextName;
}

CGXDLMSContextType CGXDLMSAssociationLogicalName::GetXDLMSContextInfo()
{
    return m_XDLMSContextInfo;
}

CGXAuthenticationMechanismName CGXDLMSAssociationLogicalName::GetAuthenticationMechanismMame()
{
    return m_AuthenticationMechanismName;
}

CGXByteBuffer& CGXDLMSAssociationLogicalName::GetSecret()
{
    return m_LlsSecret;
}
void CGXDLMSAssociationLogicalName::SetSecret(CGXByteBuffer& value)
{
    m_LlsSecret = value;
}

DLMS_DLMS_ASSOCIATION_STATUS CGXDLMSAssociationLogicalName::GetAssociationStatus()
{
    return m_AssociationStatus;
}

void CGXDLMSAssociationLogicalName::SetAssociationStatus(DLMS_DLMS_ASSOCIATION_STATUS value)
{
    m_AssociationStatus = value;
}

std::string CGXDLMSAssociationLogicalName::GetSecuritySetupReference()
{
    return m_SecuritySetupReference;
}
void CGXDLMSAssociationLogicalName::SetSecuritySetupReference(std::string value)
{
    m_SecuritySetupReference = value;
}

// Returns amount of attributes.
int CGXDLMSAssociationLogicalName::GetAttributeCount()
{
    //Security Setup Reference is from version 1.
    if (GetVersion() > 0)
        return 9;
    return 8;
}

// Returns amount of methods.
int CGXDLMSAssociationLogicalName::GetMethodCount()
{
    return 4;
}

void CGXDLMSAssociationLogicalName::GetValues(std::vector<std::string>& values)
{
    //values.clear();
    //std::string ln;
    //GetLogicalName(ln);
    //values.push_back(ln);
    //values.push_back(m_ObjectList.ToString());
    //std::string str = CGXDLMSVariant(m_ClientSAP).ToString();
    //str += "/";
    //str += CGXDLMSVariant(m_ServerSAP).ToString();
    //values.push_back(str);
    //values.push_back(m_ApplicationContextName.ToString());
    //values.push_back(m_XDLMSContextInfo.ToString());
    //values.push_back(m_AuthenticationMechanismName.ToString());
    //values.push_back(m_LlsSecret.ToHexString());
    //values.push_back(CGXDLMSVariant(m_AssociationStatus).ToString());
    ////Security Setup Reference is from version 1.
    //if (GetVersion() > 0)
    //{
    //    values.push_back(m_SecuritySetupReference);
    //}
}

void CGXDLMSAssociationLogicalName::GetAttributeIndexToRead(std::vector<int>& attributes)
{
    //LN is static and read only once.
    if (CGXDLMSObject::IsLogicalNameEmpty(m_LN))
    {
        attributes.push_back(1);
    }
    //ObjectList is static and read only once.
    if (!IsRead(2))
    {
        attributes.push_back(2);
    }
    //associated_partners_id is static and read only once.
    if (!IsRead(3))
    {
        attributes.push_back(3);
    }
    //Application Context Name is static and read only once.
    if (!IsRead(4))
    {
        attributes.push_back(4);
    }
    //xDLMS Context Info
    if (!IsRead(5))
    {
        attributes.push_back(5);
    }
    // Authentication Mechanism Name
    if (!IsRead(6))
    {
        attributes.push_back(6);
    }
    // Secret
    if (!IsRead(7))
    {
        attributes.push_back(7);
    }
    // Association Status
    if (!IsRead(8))
    {
        attributes.push_back(8);
    }
    //Security Setup Reference is from version 1.
    if (GetVersion() > 0 && !IsRead(9))
    {
        attributes.push_back(9);
    }
}

int CGXDLMSAssociationLogicalName::GetDataType(unsigned char index, DLMS_DATA_TYPE& type)
{
    if (index == 1)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 2)
    {
        type = DLMS_DATA_TYPE_ARRAY;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 3)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 4)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 5)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 6)
    {
        type = DLMS_DATA_TYPE_STRUCTURE;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 7)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 8)
    {
        type = DLMS_DATA_TYPE_ENUM;
        return DLMS_ERROR_CODE_OK;
    }
    if (index == 9)
    {
        type = DLMS_DATA_TYPE_OCTET_STRING;
        return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSAssociationLogicalName::Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    // Check reply_to_HLS_authentication
    if (e.GetIndex() == 1)
    {
		VarInfo v_info;
		e.GetParameters().GetVar(v_info);
		e.SetByteArray(true);
        int ret;
        unsigned long ic = 0;
        CGXByteBuffer* readSecret;
        if (settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH_GMAC)
        {
            unsigned char ch;
            readSecret = &settings.GetSourceSystemTitle();
            CGXByteBuffer bb;
            bb.Set(e.GetParameters().GetCurPtr(), v_info.size);
            if ((ret = bb.GetUInt8(&ch)) != 0)
            {
                return ret;
            }
            if ((ret = bb.GetUInt32(&ic)) != 0)
            {
                return ret;
            }
        }
        else
        {
            readSecret = &m_HlsSecret;
        }
        CGXByteBuffer serverChallenge;
		if ((ret = CGXSecure::Secure(settings, settings.GetCipher(), ic,
            settings.GetStoCChallenge(), *readSecret, serverChallenge)) != 0)
        {
            return ret;
        }
        if (serverChallenge.Compare(e.GetParameters().GetCurPtr(), v_info.size))
        {
            if (settings.GetAuthentication() == DLMS_AUTHENTICATION_HIGH_GMAC)
            {
                readSecret = &settings.GetCipher()->GetSystemTitle();
                ic = settings.GetCipher()->GetFrameCounter();
            }
            else
            {
                readSecret = &m_HlsSecret;
            }
            if ((ret = CGXSecure::Secure(settings, settings.GetCipher(), ic,
                settings.GetCtoSChallenge(), *readSecret, serverChallenge)) != 0)
            {
                return ret;
            }
			if (serverChallenge.GetSize() + 2 > serverChallenge.Capacity()) {
				serverChallenge.Capacity(serverChallenge.GetSize() + 2);
			}
			serverChallenge.SetSize(serverChallenge.GetSize() + 2);
			serverChallenge.Move(0, 2, serverChallenge.GetSize() - 2);
			serverChallenge.SetUInt8(0, DLMS_DATA_TYPE_OCTET_STRING);
			serverChallenge.SetUInt8(1, serverChallenge.GetSize() - 2);
            e.SetValue(serverChallenge);
            settings.SetConnected(true);
        }
        else
        {
            settings.SetConnected(false);       
			e.SetError(DLMS_ERROR_CODE_OTHER_REASON);
        }
    }
    else
    {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
    }
    return 0;
}

int CGXDLMSAssociationLogicalName::GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    int ret;
	CGXByteBuffer data;
	e.SetByteArray(true);
    if (e.GetIndex() == 1)
    {
		if ((ret = GetLogicalName(this, data)) != 0)
        {
            return ret;
        }
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 2)
    {
        ret = GetObjects(settings, e, data);
        e.SetValue(data);
        return ret;
    }
    if (e.GetIndex() == 3)
    {
        data.SetUInt8(DLMS_DATA_TYPE_ARRAY);
        //Add count
        data.SetUInt8(2);
        data.SetUInt8(DLMS_DATA_TYPE_UINT8);
        data.SetUInt8(m_ClientSAP);
        data.SetUInt8(DLMS_DATA_TYPE_UINT16);
        data.SetUInt16(m_ServerSAP);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 4)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        data.SetUInt8(0x7);
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetJointIsoCtt());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetCountry());
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_ApplicationContextName.GetCountryName());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetIdentifiedOrganization());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetDlmsUA());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetApplicationContext());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_ApplicationContextName.GetContextId());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 5)
    {
        CGXByteBuffer info = m_XDLMSContextInfo.GetCypheringInfo();
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        data.SetUInt8(6);
		data.SetUInt8(DLMS_DATA_TYPE_BIT_STRING);
		uint32_t tmp = m_XDLMSContextInfo.GetConformance();
		GXHelpers::SetObjectCount(24, data);
		data.SetUInt8((tmp >> 16) & 0xFF);
		data.SetUInt8((tmp >> 8) & 0xFF);
		data.SetUInt8(tmp & 0xFF);
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt8(m_XDLMSContextInfo.GetMaxPduSize());
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt8(m_XDLMSContextInfo.GetMaxSendPduSize());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_XDLMSContextInfo.GetDlmsVersionNumber());
		data.SetUInt8(DLMS_DATA_TYPE_INT8);
		data.SetUInt8(m_XDLMSContextInfo.GetQualityOfService());
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		GXHelpers::SetObjectCount(info.GetSize(), data);
		data.Set(info.GetData(),info.GetSize());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 6)
    {
        data.SetUInt8(DLMS_DATA_TYPE_STRUCTURE);
        //Add count
        data.SetUInt8(0x7);
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetJointIsoCtt());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetCountry());
		data.SetUInt8(DLMS_DATA_TYPE_UINT16);
		data.SetUInt16(m_AuthenticationMechanismName.GetCountryName());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetIdentifiedOrganization());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetDlmsUA());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetAuthenticationMechanismName());
		data.SetUInt8(DLMS_DATA_TYPE_UINT8);
		data.SetUInt8(m_AuthenticationMechanismName.GetMechanismId());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 7)
    {
		data.SetUInt8(DLMS_DATA_TYPE_OCTET_STRING);
		GXHelpers::SetObjectCount(m_LlsSecret.GetSize(), data);
		data.Set(m_LlsSecret.GetData(), m_LlsSecret.GetSize());
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 8)
    {
		data.SetUInt8(DLMS_DATA_TYPE_ENUM);
		data.SetUInt8((unsigned char)m_AssociationStatus);
        e.SetValue(data);
        return DLMS_ERROR_CODE_OK;
    }
    if (e.GetIndex() == 9)
    {
        unsigned char tmp[6];
		GXHelpers::SetLogicalName(m_SecuritySetupReference.c_str(), tmp);
		data.Set(tmp, 6);
        e.SetValue(data);
		return DLMS_ERROR_CODE_OK;
    }
    return DLMS_ERROR_CODE_INVALID_PARAMETER;
}

int CGXDLMSAssociationLogicalName::SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
{
    if (e.GetIndex() == 1)
    {
        return SetLogicalName(this, e.GetCAValue());
    }
    else if (e.GetIndex() == 2)
    {
        /*m_ObjectList.clear();
        if (e.GetValue().vt != DLMS_DATA_TYPE_NONE)
        {
            for (std::vector<CGXDLMSVariant >::iterator it = e.GetValue().Arr.begin(); it != e.GetValue().Arr.end(); ++it)
            {
                DLMS_OBJECT_TYPE type = (DLMS_OBJECT_TYPE)(*it).Arr[0].ToInteger();
                int version = (*it).Arr[1].ToInteger();
                std::string ln;
                GXHelpers::GetLogicalName((*it).Arr[2].byteArr, ln);
                CGXDLMSObject* pObj = settings.GetObjects()->FindByLN(type, ln);
                if (pObj == NULL)
                {
                    pObj = CGXDLMSObjectFactory::CreateObject(type, ln);
                    if (pObj != NULL)
                    {
                        pObj->SetVersion(version);
                    }
                }
                if (pObj != NULL)
                {
                    UpdateAccessRights(pObj, (*it).Arr[3]);
                    m_ObjectList.push_back(pObj);
                }
            }
        }*/
    }
    else if (e.GetIndex() == 3)
    {
        /*m_ClientSAP = e.GetValue().Arr[0].ToInteger();
        m_ServerSAP = e.GetValue().Arr[1].ToInteger();*/
    }
    else if (e.GetIndex() == 4)
    {
        ////Value of the object identifier encoded in BER
        //if (e.GetValue().vt == DLMS_DATA_TYPE_OCTET_STRING)
        //{
        //    CGXByteBuffer tmp;
        //    tmp.Set(e.GetValue().byteArr, e.GetValue().GetSize());
        //    int ret;
        //    unsigned char val;
        //    if ((ret = tmp.GetUInt8(0, &val)) != 0)
        //    {
        //        return ret;
        //    }
        //    if (val == 0x60)
        //    {
        //        m_ApplicationContextName.SetJointIsoCtt(0);
        //        m_ApplicationContextName.SetCountry(0);
        //        m_ApplicationContextName.SetCountryName(0);
        //        tmp.SetPosition(3);
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetIdentifiedOrganization(val);
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetDlmsUA(val);
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetApplicationContext(val);
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetContextId(val);
        //    }
        //    else
        //    {
        //        //Get Tag and Len.
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 2)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 7)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x11)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetJointIsoCtt(val);
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x11)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetCountry(val);
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x12)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetCountryName(val);
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x11)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetIdentifiedOrganization(val);
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x11)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetDlmsUA(val);
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x11)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetApplicationContext(val);
        //        //Get tag
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val != 0x11)
        //        {
        //            return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //        }
        //        if ((ret = tmp.GetUInt8(&val)) != 0)
        //        {
        //            return ret;
        //        }
        //        m_ApplicationContextName.SetContextId(val);
        //    }
        //}
        //else
        //{
        //    m_ApplicationContextName.SetJointIsoCtt(e.GetValue().Arr[0].ToInteger());
        //    m_ApplicationContextName.SetCountry(e.GetValue().Arr[1].ToInteger());
        //    m_ApplicationContextName.SetCountryName(e.GetValue().Arr[2].ToInteger());
        //    m_ApplicationContextName.SetIdentifiedOrganization(e.GetValue().Arr[3].ToInteger());
        //    m_ApplicationContextName.SetDlmsUA(e.GetValue().Arr[4].ToInteger());
        //    m_ApplicationContextName.SetApplicationContext(e.GetValue().Arr[5].ToInteger());
        //    m_ApplicationContextName.SetContextId(e.GetValue().Arr[6].ToInteger());
        //}
    }
    else if (e.GetIndex() == 5)
    {
        /*if (e.GetValue().vt == DLMS_DATA_TYPE_STRUCTURE)
        {
            m_XDLMSContextInfo.SetConformance((DLMS_CONFORMANCE)e.GetValue().Arr[0].ToInteger());
            m_XDLMSContextInfo.SetMaxReceivePduSize(e.GetValue().Arr[1].ToInteger());
            m_XDLMSContextInfo.SetMaxSendPduSize(e.GetValue().Arr[2].ToInteger());
            m_XDLMSContextInfo.SetDlmsVersionNumber(e.GetValue().Arr[3].ToInteger());
            m_XDLMSContextInfo.SetQualityOfService(e.GetValue().Arr[4].ToInteger());
            CGXByteBuffer tmp;
            tmp.Set(e.GetValue().Arr[5].byteArr, e.GetValue().Arr[5].GetSize());
            m_XDLMSContextInfo.SetCypheringInfo(tmp);
        }*/
    }
    else if (e.GetIndex() == 6)
    {
        //if (e.GetValue().vt != DLMS_DATA_TYPE_NONE)
        //{
        //    unsigned char val;
        //    int ret;
        //    //Value of the object identifier encoded in BER
        //    if (e.GetValue().vt == DLMS_DATA_TYPE_OCTET_STRING)
        //    {
        //        CGXByteBuffer tmp;
        //        tmp.Set(e.GetValue().byteArr, e.GetValue().GetSize());
        //        if ((ret = tmp.GetUInt8(0, &val)) != 0)
        //        {
        //            return ret;
        //        }
        //        if (val == 0x60)
        //        {
        //            m_AuthenticationMechanismName.SetJointIsoCtt(0);
        //            m_AuthenticationMechanismName.SetCountry(0);
        //            m_AuthenticationMechanismName.SetCountryName(0);
        //            tmp.SetPosition(3);
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetIdentifiedOrganization(val);
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetDlmsUA(val);
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetAuthenticationMechanismName(val);
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetMechanismId((DLMS_AUTHENTICATION)val);
        //        }
        //        else
        //        {
        //            //Get Tag and Len.
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 2)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 7)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x11)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetJointIsoCtt(val);
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x11)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetCountry(val);
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x12)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            unsigned short tmp2;
        //            if ((ret = tmp.GetUInt16(&tmp2)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetCountryName(tmp2);
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x11)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetIdentifiedOrganization(val);
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x11)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetDlmsUA(val);
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x11)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetAuthenticationMechanismName(val);
        //            //Get tag
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            if (val != 0x11)
        //            {
        //                return DLMS_ERROR_CODE_INVALID_PARAMETER;
        //            }
        //            if ((ret = tmp.GetUInt8(&val)) != 0)
        //            {
        //                return ret;
        //            }
        //            m_AuthenticationMechanismName.SetMechanismId((DLMS_AUTHENTICATION)val);
        //        }
        //    }
        //    else
        //    {
        //        m_AuthenticationMechanismName.SetJointIsoCtt(e.GetValue().Arr[0].ToInteger());
        //        m_AuthenticationMechanismName.SetCountry(e.GetValue().Arr[1].ToInteger());
        //        m_AuthenticationMechanismName.SetCountryName(e.GetValue().Arr[2].ToInteger());
        //        m_AuthenticationMechanismName.SetIdentifiedOrganization(e.GetValue().Arr[3].ToInteger());
        //        m_AuthenticationMechanismName.SetDlmsUA(e.GetValue().Arr[4].ToInteger());
        //        m_AuthenticationMechanismName.SetAuthenticationMechanismName(e.GetValue().Arr[5].ToInteger());
        //        m_AuthenticationMechanismName.SetMechanismId((DLMS_AUTHENTICATION)e.GetValue().Arr[6].ToInteger());
        //    }
        //}
    }
    else if (e.GetIndex() == 7)
    {
        m_LlsSecret.Clear();
		VarInfo v_info;
		e.GetCAValue().GetVar(v_info);
        m_LlsSecret.Set(e.GetCAValue().GetCurPtr(), v_info.size);
    }
    else if (e.GetIndex() == 8)
    {
       // m_AssociationStatus = (DLMS_DLMS_ASSOCIATION_STATUS)e.GetValue().ToInteger();
    }
    else if (e.GetIndex() == 9)
    {
       // GXHelpers::GetLogicalName(e.GetValue().byteArr, m_SecuritySetupReference);
    }
    else
    {
        return DLMS_ERROR_CODE_INVALID_PARAMETER;
    }
    return DLMS_ERROR_CODE_OK;
}
