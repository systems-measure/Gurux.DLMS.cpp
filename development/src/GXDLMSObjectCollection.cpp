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
#include "../include/GXDLMSGSMDiagnostic.h"
#include "../include/GXDLMSIp4Setup.h"
#include "../include/GXDLMSTcpUdpSetup.h"
#include "../include/GXDLMSMacAddressSetup.h"
#include "../include/GXDLMSImageTransfer.h"

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

void CreateImageTransfer(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSImageTransfer();
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

void CreateTcpUdpSetup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSTcpUdpSetup();
}

void CreateIp4Setup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSIp4Setup();
}

void CreateMacAddressSetup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSMacAddressSetup();
}

void CreateGPRSSetup(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSGPRSSetup();
}

void CreateGSMDiagnostic(CGXDLMSObject*& constracted) {
	constracted = new CGXDLMSGSMDiagnostic();
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
	{ DLMS_OBJECT_TYPE_IMAGE_TRANSFER,				 CreateImageTransfer },
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
	{ DLMS_OBJECT_TYPE_TCP_UDP_SETUP,				   CreateTcpUdpSetup },
	{ DLMS_OBJECT_TYPE_IP4_SETUP,						  CreateIp4Setup },
	{ DLMS_OBJECT_TYPE_MAC_ADDRESS_SETUP,		   CreateMacAddressSetup },
	{ DLMS_OBJECT_TYPE_PPP_SETUP,									NULL },
	{ DLMS_OBJECT_TYPE_GPRS_SETUP,						 CreateGPRSSetup },
	{ DLMS_OBJECT_TYPE_SMTP_SETUP,									NULL },
	{ DLMS_OBJECT_TYPE_GSM_DIAGNOSTIC,				 CreateGSMDiagnostic },
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
	if (create_func[type].execute_func != NULL) {
		create_func[type].execute_func(constructed_obj);
	}
	else {
		constructed_obj = nullptr;
	}
}

CGXDLMSObjectCollection::CGXDLMSObjectCollection() {
	constructed_obj = nullptr;
	m_currentALN = nullptr;
	idx_constructed_obj = new uint8_t;
	*idx_constructed_obj = 0;
	init_callback = nullptr;
	type_callback = nullptr;
	size_collection = 0;
	num_obj_in_collection = 0;
	objects_ln = nullptr;
}

CGXDLMSObjectCollection::CGXDLMSObjectCollection(uint8_t size) {
	constructed_obj = nullptr;
	m_currentALN = nullptr;
	idx_constructed_obj = new uint8_t;
    *idx_constructed_obj = 0;
	init_callback = nullptr;
	type_callback = nullptr;
	size_collection = size;
	num_obj_in_collection = 0;
	objects_ln = new uint8_t*[size];
	for (uint8_t i = 0; i < size; ++i) {
		objects_ln[i] = nullptr;
	}
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
	m_currentALN = nullptr;
	if (idx_constructed_obj != nullptr) {
		delete idx_constructed_obj;
	}
	if (objects_ln != nullptr) {
		for (uint8_t i = 0; i < size_collection; ++i) {
			if (objects_ln[i] != nullptr) {
				delete[] objects_ln[i];
				objects_ln[i] = nullptr;
			}
		}
		delete[] objects_ln;
		objects_ln = nullptr;
	}
}

CGXDLMSObject* CGXDLMSObjectCollection::MakeByPosition(uint8_t pos) {
	if (type_callback != nullptr) {
		char ln[24];
		GXHelpers::GetLogicalName(objects_ln[pos], ln);
		DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln, idx_constructed_obj);
		CreateObject(o_type);
		if (constructed_obj != nullptr) {
			memcpy(constructed_obj->m_LN, objects_ln[pos], 6);
			if (init_callback != nullptr) {
				init_callback(constructed_obj, idx_constructed_obj);
				return constructed_obj;
			}
		}
	}
	return nullptr;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(uint8_t* ln)
{
	if (ln == nullptr) {
		return nullptr;
	}
	if (memcmp(ln, m_currentALN->m_LN, 6) == 0) {
		return m_currentALN;
	}
	for (uint8_t i = 0; i < num_obj_in_collection; ++i) {
		if (memcmp(ln, objects_ln[i], 6) == 0)
		{
			char ln_str[24];
			GXHelpers::GetLogicalName(objects_ln[i], ln_str);
			if (type_callback != nullptr) {
				DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln_str, idx_constructed_obj);
				CreateObject(o_type);
				if (constructed_obj != nullptr) {
					memcpy(constructed_obj->m_LN, objects_ln[i], 6);
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

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(CGXByteBuffer& ln)
{
    if (ln.GetSize() != 6)
    {
        return nullptr;
    }
	if (memcmp(ln.GetData(), m_currentALN->m_LN, 6) == 0) {
		return m_currentALN;
	}
	for (uint8_t i = 0; i < num_obj_in_collection; ++i) {
		if (memcmp(ln.GetData(), objects_ln[i], 6) == 0)
		{
			char ln[24];
			GXHelpers::GetLogicalName(objects_ln[i], ln);
			if (type_callback != nullptr) {
				DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln, idx_constructed_obj);
				CreateObject(o_type);
				if (constructed_obj != nullptr) {
					memcpy(constructed_obj->m_LN, objects_ln[i], 6);
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
	char ln2[24];
	for (uint8_t i = 0; i < num_obj_in_collection; ++i) {
		memset(ln2, 0, 24);
		GXHelpers::GetLogicalName(objects_ln[i], ln2);
		if (strcmp(ln2, ln) == 0)
		{
			return objects_ln[i];
		}
	}
	return nullptr;
}

uint8_t** CGXDLMSObjectCollection::GetObjectsCollection() {
	return objects_ln;
}

CGXDLMSObject* CGXDLMSObjectCollection::GetCurALN() {
	return m_currentALN;
}

void CGXDLMSObjectCollection::Init(uint8_t new_size) {
	if (objects_ln == nullptr) {
		size_collection = new_size;
		objects_ln = new uint8_t*[new_size];
		for (uint8_t i = 0; i < new_size; ++i) {
			objects_ln[i] = nullptr;
		}
	}
}

uint8_t CGXDLMSObjectCollection::size() {
	return num_obj_in_collection;
}

bool CGXDLMSObjectCollection::empty() {
	return num_obj_in_collection == 0 ? true : false;
}

void CGXDLMSObjectCollection::push_back(unsigned char* item)
{
	if (num_obj_in_collection < size_collection) {
		objects_ln[num_obj_in_collection] = item;
		++num_obj_in_collection;
	}
}

void CGXDLMSObjectCollection::push_back_aln(CGXDLMSObject* item) {
	m_currentALN = item;
}

void CGXDLMSObjectCollection::insert(uint8_t start_pos, uint8_t** src, uint8_t count) {
	if (start_pos + count <= size_collection) {
		memcpy(objects_ln + start_pos, src, count*sizeof(uint8_t*));
		num_obj_in_collection += count;
	}
	else {
		if (start_pos < size_collection) {
			memcpy(objects_ln + start_pos, src, (size_collection - start_pos) * sizeof(uint8_t*));
			num_obj_in_collection += count;
		}
	}
}

void CGXDLMSObjectCollection::clear() {
	for (uint8_t i = 0; i < num_obj_in_collection; ++i) {
		objects_ln[i] = nullptr;
	}
	num_obj_in_collection = 0;
	m_currentALN = nullptr;
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

void CGXDLMSObjectCollection::FreeConstructedObj() {
	if (constructed_obj != nullptr) {
		delete constructed_obj;
		constructed_obj = nullptr;
	}
}
