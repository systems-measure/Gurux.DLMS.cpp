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
#include "../include/GXDLMSGPRSSetup.h"
#include "Helper\Helper.h"

typedef void(*newObj)(CGXDLMSObject*& constracted);

void CreateData(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSData();
}

void CreateRegister(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSRegister();
}

void CreateDemandRegister(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSDemandRegister();
}

void CreateProfile(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSProfileGeneric();
}

void CreateClock(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSClock();
}

void CreateScriptTable(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSScriptTable();
}

void CreateSpecDayTable(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSSpecialDaysTable();
}

void CreateALN(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSAssociationLogicalName();
}

void CreateActivityCalendar(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSActivityCalendar();
}

void CreateHdlcSetup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSIecHdlcSetup();
}

void CreatePushSetup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSPushSetup();
}

void CreateGPRSSetup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSGPRSSetup();
}

void CreateDisconectControl(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSDisconnectControl();
}

void CreateLimiter(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSLimiter();
}

const tabFunc<newObj> create_func[] = {
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_DATA,								  CreateData },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_REGISTER,						  CreateRegister },
	{ DLMS_OBJECT_TYPE_EXTENDED_REGISTER,							NULL },
	{ DLMS_OBJECT_TYPE_DEMAND_REGISTER,				CreateDemandRegister },
	{ DLMS_OBJECT_TYPE_REGISTER_ACTIVATION,							NULL },
	{ DLMS_OBJECT_TYPE_PROFILE_GENERIC,					   CreateProfile },
	{ DLMS_OBJECT_TYPE_CLOCK,								 CreateClock },
	{ DLMS_OBJECT_TYPE_SCRIPT_TABLE,				   CreateScriptTable },
	{ DLMS_OBJECT_TYPE_SCHEDULE,									NULL },
	{ DLMS_OBJECT_TYPE_SPECIAL_DAYS_TABLE,			  CreateSpecDayTable },
	{ DLMS_OBJECT_TYPE_ASSOCIATION_SHORT_NAME,						NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_ASSOCIATION_LOGICAL_NAME,			   CreateALN },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_SAP_ASSIGNMENT,								NULL },
	{ DLMS_OBJECT_TYPE_IMAGE_TRANSFER,								NULL },
	{ DLMS_OBJECT_TYPE_IEC_LOCAL_PORT_SETUP,						NULL },
	{ DLMS_OBJECT_TYPE_ACTIVITY_CALENDAR,		  CreateActivityCalendar },
	{ DLMS_OBJECT_TYPE_REGISTER_MONITOR,							NULL },
	{ DLMS_OBJECT_TYPE_ACTION_SCHEDULE,								NULL },
	{ DLMS_OBJECT_TYPE_IEC_HDLC_SETUP,					 CreateHdlcSetup },
	{ DLMS_OBJECT_TYPE_IEC_TWISTED_PAIR_SETUP,						NULL },
	{ DLMS_OBJECT_TYPE_MBUS_SLAVE_PORT_SETUP,						NULL },
	{ DLMS_OBJECT_TYPE_UTILITY_TABLES,								NULL },
	{ DLMS_OBJECT_TYPE_MODEM_CONFIGURATION,							NULL },
	{ DLMS_OBJECT_TYPE_AUTO_ANSWER,									NULL },
	{ DLMS_OBJECT_TYPE_AUTO_CONNECT,								NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_PUSH_SETUP,						 CreatePushSetup },
	{ DLMS_OBJECT_TYPE_TCP_UDP_SETUP,								NULL },
	{ DLMS_OBJECT_TYPE_IP4_SETUP,									NULL },
	{ DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP,							NULL },
	{ DLMS_OBJECT_TYPE_PPP_SETUP,									NULL },
	{ DLMS_OBJECT_TYPE_GPRS_SETUP,						 CreateGPRSSetup },
	{ DLMS_OBJECT_TYPE_SMTP_SETUP,									NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_MESSAGE_HANDLER,								NULL },
	{ DLMS_OBJECT_TYPE_REGISTER_TABLE,								NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_STATUS_MAPPING,								NULL },
	{ DLMS_OBJECT_TYPE_DLMS_SECURITY_SETUP,							NULL },
	{ DLMS_OBJECT_TYPE_PARAMETER_MONITOR,							NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_NONE,										NULL },
	{ DLMS_OBJECT_TYPE_DISCONNECT_CONTROL,		  CreateDisconectControl },
	{ DLMS_OBJECT_TYPE_LIMITER,							   CreateLimiter }
};

void CGXDLMSObjectCollection::CreateObject(DLMS_OBJECT_TYPE type)
{
	/*switch (type)
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
	}*/
	if (create_func[type].execute_func != NULL) {
		create_func[type].execute_func(constructed_obj);
	}
	else {
		constructed_obj = nullptr;
	}
}

CGXDLMSObjectCollection::CGXDLMSObjectCollection() {
	constructed_obj = nullptr;
	idx_constructed_obj = new uint8_t;
    *idx_constructed_obj = 0;
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
