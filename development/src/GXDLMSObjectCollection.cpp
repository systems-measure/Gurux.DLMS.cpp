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

#include "../include/GXDLMSObjectCollection.h"
#include "../include/GXDLMSAssociationLogicalName.h"
#include "../include/GXDLMSClock.h"
#include "../include/GXDLMSData.h"
#include "../include/GXDLMSRegister.h"
#include "../include/GXDLMSDemandRegister.h"
#include "../include/GXDLMSProfileGeneric.h"
#include "../include/GXDLMSActivityCalendar.h"
#include "../include/GXDLMSHdlcSetup.h"
#include "../include/GXDLMSSpecialDaysTable.h"
#include "../include/GXDLMSLimiter.h"
#include "../include/GXDLMSScriptTable.h"
#include "../include/GXDLMSPushSetup.h"
#include "../include/GXDLMSDisconnectControl.h"
#include <sstream>

void CGXDLMSObjectCollection::CreateObject(DLMS_OBJECT_TYPE type)
{
	switch (type)
	{
	case DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR:
		constructed_obj =  new CGXDLMSActivityCalendar();
		break;
	case DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME:
		constructed_obj = new CGXDLMSAssociationLogicalName();
		break;
	case DLMS_OBJECT_TYPE_CLOCK:
		constructed_obj = new CGXDLMSClock();
		break;
	case DLMS_OBJECT_TYPE_DATA:
		constructed_obj = new CGXDLMSData();
		break;
	case DLMS_OBJECT_TYPE_DEMAND_REGISTER:
		constructed_obj = new CGXDLMSDemandRegister();
		break;
	case DLMS_OBJECT_TYPE_IEC_HDLC_SETUP:
		constructed_obj = new CGXDLMSIecHdlcSetup();
		break;
	case DLMS_OBJECT_TYPE_DISCONNECT_CONTROL:
		constructed_obj = new CGXDLMSDisconnectControl();
		break;
	case DLMS_OBJECT_TYPE_LIMITER:
		constructed_obj = new CGXDLMSLimiter();
		break;
	case DLMS_OBJECT_TYPE_PROFILE_GENERIC:
		constructed_obj = new CGXDLMSProfileGeneric();
		break;
	case DLMS_OBJECT_TYPE_REGISTER:
		constructed_obj = new CGXDLMSRegister();
		break;
	case DLMS_OBJECT_TYPE_SCRIPT_TABLE:
		constructed_obj = new CGXDLMSScriptTable();
		break;
	case DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE:
		constructed_obj = new CGXDLMSSpecialDaysTable();
		break;
	case DLMS_OBJECT_TYPE_PUSH_SETUP:
		constructed_obj = new CGXDLMSPushSetup();
		break;
	default:
		constructed_obj = nullptr;
		break;
	}
}

CGXDLMSObjectCollection::CGXDLMSObjectCollection() {
	constructed_obj = nullptr;
	idx_constructed_obj = new uint8_t(0);
	init_callback = nullptr;
	type_callback = nullptr;
}

CGXDLMSObjectCollection::~CGXDLMSObjectCollection()
{
	if (constructed_obj != nullptr) {
		delete constructed_obj;
		constructed_obj = nullptr;
	}
	if (init_callback != nullptr) {
		init_callback = nullptr;
	}
	delete idx_constructed_obj;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(DLMS_OBJECT_TYPE type, std::string& ln)
{
    const char* pLn = ln.c_str();
    std::string ln2;
	for (std::vector<CGXDLMSObject*>::iterator it = dlms_only_obj.begin(); it != dlms_only_obj.end(); ++it) {
		if ((type == DLMS_OBJECT_TYPE_ALL || (*it)->GetObjectType() == type))
        {
            (*it)->GetLogicalName(ln2);
            if (strcmp(ln2.c_str(), pLn) == 0)
            {
                return *it;
            }
        }
    }
	for (CGXDLMSObjectCollection::iterator it = this->begin(); it != end(); ++it)
	{
		GXHelpers::GetLogicalName(*it, ln2);
		if (strcmp(ln2.c_str(), pLn) == 0)
		{
			if (type_callback != nullptr) {
				DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln.c_str(), idx_constructed_obj);
				CreateObject(o_type);
				if (constructed_obj != nullptr) {
					GXHelpers::SetLogicalName(ln.c_str(), constructed_obj->m_LN);
					if (init_callback != nullptr) {
						init_callback(constructed_obj, idx_constructed_obj);
						return constructed_obj;
					}
				}
			}
		}
	}
	return nullptr;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(DLMS_OBJECT_TYPE type, CGXByteBuffer& ln)
{
    if (ln.GetSize() != 6)
    {
        return nullptr;
    }
    for (std::vector<CGXDLMSObject*>::iterator it = dlms_only_obj.begin(); it != dlms_only_obj.end(); ++it)
    {
        if (type == DLMS_OBJECT_TYPE_ALL || (*it)->GetObjectType() == type)
        {
            if (memcmp(ln.GetData(), (*it)->m_LN, 6) == 0)
            {
                return *it;
            }
        }
	}
	for (CGXDLMSObjectCollection::iterator it = this->begin(); it != end(); ++it)
	{
		if (memcmp(ln.GetData(), (*it), 6) == 0)
		{
			std::string ln;
			GXHelpers::GetLogicalName(*it, ln);
			if (type_callback != nullptr) {
				DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln.c_str(), idx_constructed_obj);
				CreateObject(o_type);
				if (constructed_obj != nullptr) {
					memcpy(constructed_obj->m_LN, *it, 6);
					if (init_callback != nullptr) {
						init_callback(constructed_obj, idx_constructed_obj);
						return constructed_obj;
					}
				}
			}
		}
	}
	return nullptr;
}

unsigned char* CGXDLMSObjectCollection::FindByLN(const char* ln) {
	std::string ln2;
	for (CGXDLMSObjectCollection::iterator it = this->begin(); it != end(); ++it)
	{
		GXHelpers::GetLogicalName(*it, ln2);
		if (strcmp(ln2.c_str(), ln) == 0)
		{
			return *it;
		}
	}
	return nullptr;
}

unsigned char* CGXDLMSObjectCollection::FindByLN(CGXByteBuffer& ln) {
	if (ln.GetSize() != 6)
	{
		return nullptr;
	}
	for (std::vector<CGXDLMSObject*>::iterator it = dlms_only_obj.begin(); it != dlms_only_obj.end(); ++it)
	{
		if (memcmp(ln.GetData(), (*it)->m_LN, 6) == 0)
		{
			return (*it)->m_LN;
		}
	}
	for (CGXDLMSObjectCollection::iterator it = this->begin(); it != end(); ++it)
	{
		if (memcmp(ln.GetData(), (*it), 6) == 0)
		{
			return (*it);
		}
	}
	return nullptr;
}

std::vector<CGXDLMSObject*>& CGXDLMSObjectCollection::GetDlmsObj() {
	return dlms_only_obj;
}

void CGXDLMSObjectCollection::push_back(unsigned char* item)
{
    std::vector<unsigned char*>::push_back(item);
}

void CGXDLMSObjectCollection::push_back(CGXDLMSObject* item) {
	dlms_only_obj.push_back(item);
}

int CGXDLMSObjectCollection::sizeRequiredObj() {
	return dlms_only_obj.size();
}

std::vector<CGXDLMSObject*>::iterator CGXDLMSObjectCollection::insert(std::vector<CGXDLMSObject*>::const_iterator where,
	std::vector<CGXDLMSObject*>::const_iterator first, std::vector<CGXDLMSObject*>::const_iterator last) {
	return dlms_only_obj.insert(where, first, last);
}

std::vector<unsigned char*>::iterator CGXDLMSObjectCollection::insert(std::vector<unsigned char*>::const_iterator where,
	std::vector<unsigned char*>::const_iterator first, std::vector<unsigned char*>::const_iterator last) {
	return std::vector<unsigned char*>::insert(where, first, last);
}

void CGXDLMSObjectCollection::clear() {
	//Free();
	std::vector<unsigned char*>::clear();
	dlms_only_obj.clear();
	*idx_constructed_obj = 0;
	FreeConstructedObj();
}

InitObjField CGXDLMSObjectCollection::GetInitCallback() {
	return init_callback;
}

void CGXDLMSObjectCollection::SetInitCallback(InitObjField init) {
	init_callback = init;
}

TypeObj CGXDLMSObjectCollection::GetTypeObjCallback() {
	return type_callback;
}

void CGXDLMSObjectCollection::SetTypeObjCallback(TypeObj type) {
	type_callback = type;
}

void CGXDLMSObjectCollection::Free()
{
	if (this->size() != 0) {
		for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
		{
			delete (*it);
		}
	}
	if (dlms_only_obj.size() != 0) {
		for (std::vector<CGXDLMSObject*>::iterator it = dlms_only_obj.begin(); it != dlms_only_obj.end(); ++it) {
			delete (*it);
		}
	}
	std::vector<unsigned char*>::clear();
	dlms_only_obj.clear();
	*idx_constructed_obj = 0;
	FreeConstructedObj();
}

void CGXDLMSObjectCollection::FreeConstructedObj() {
	if (constructed_obj != nullptr) {
		delete constructed_obj;
		constructed_obj = nullptr;
	}
}
