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
#include <sstream>

CGXDLMSObjectCollection::CGXDLMSObjectCollection() {
	constructed_obj = nullptr;
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
				DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln.c_str());
				constructed_obj = CGXDLMSObjectFactory::CreateObject(o_type);
				if (constructed_obj != NULL) {
					GXHelpers::SetLogicalName(ln.c_str(), constructed_obj->m_LN);
					if (init_callback != nullptr) {
						init_callback(constructed_obj);
						return constructed_obj;
					}
				}
			}
		}
	}
	return NULL;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindByLN(DLMS_OBJECT_TYPE type, CGXByteBuffer& ln)
{
    if (ln.GetSize() != 6)
    {
        return NULL;
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
				DLMS_OBJECT_TYPE o_type = (DLMS_OBJECT_TYPE)type_callback(ln.c_str());
				constructed_obj = CGXDLMSObjectFactory::CreateObject(o_type);
				if (constructed_obj != NULL) {
					memcpy(constructed_obj->m_LN, *it, 6);
					if (init_callback != nullptr) {
						init_callback(constructed_obj);
						return constructed_obj;
					}
				}
			}
		}
	}
	return NULL;
}

CGXDLMSObject* CGXDLMSObjectCollection::FindBySN(unsigned short sn)
{
   /* for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
    {
        if ((*it)->GetShortName() == sn)
        {
            return *it;
        }
    }*/
    return NULL;
}

//void CGXDLMSObjectCollection::GetObjects(DLMS_OBJECT_TYPE type, CGXDLMSObjectCollection& items)
//{
//    for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
//    {
//        if ((*it)->GetObjectType() == type)
//        {
//            items.push_back(*it);
//        }
//    }
//}

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

void CGXDLMSObjectCollection::clear() {
	std::vector<unsigned char*>::clear();
	dlms_only_obj.clear();
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
    for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
    {
        delete (*it);
    }
	for (std::vector<CGXDLMSObject*>::iterator it = dlms_only_obj.begin(); it != dlms_only_obj.end(); ++it) {
		delete (*it);
	}
    std::vector<unsigned char*>::clear();
	dlms_only_obj.clear();
}

void CGXDLMSObjectCollection::FreeConstructedObj() {
	if (constructed_obj != nullptr) {
		delete constructed_obj;
		constructed_obj = nullptr;
	}
}

std::string CGXDLMSObjectCollection::ToString()
{
    std::stringstream sb;
	CGXDLMSObject* tmp_obj = NULL;
	CGXByteBuffer ln;
    sb << '[';
    bool empty = true;
    for (CGXDLMSObjectCollection::iterator it = begin(); it != end(); ++it)
    {
        if (!empty)
        {
            sb << ", ";
        }
        empty = false;
		ln.Clear();
		ln.Set(*it, 6);
		tmp_obj = FindByLN(DLMS_OBJECT_TYPE_ALL, ln);
        std::string str = tmp_obj->GetName().ToString();
        sb.write(str.c_str(), str.size());
		tmp_obj = NULL;
		FreeConstructedObj();
    }
	for (std::vector<CGXDLMSObject*>::iterator it = dlms_only_obj.begin(); it != dlms_only_obj.end(); ++it)
	{
		if (!empty)
		{
			sb << ", ";
		}
		empty = false;
		std::string str = (*it)->GetName().ToString();
		sb.write(str.c_str(), str.size());
	}
    sb << ']';
    return sb.str();
}
