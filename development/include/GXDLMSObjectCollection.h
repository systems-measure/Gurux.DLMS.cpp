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

#ifndef GXDLMSOBJECTCOLLECTION_H
#define GXDLMSOBJECTCOLLECTION_H



#include <vector>
#include "GXDLMSObject.h"

typedef void(*InitObjField)(CGXDLMSObject* constr_obj, uint8_t* idx_cnstrd);

typedef unsigned char(*TypeObj)(const char* obis, uint8_t* idx_cnstrd);

class CGXDLMSObjectCollection : public std::vector<unsigned char*>
{
private:
	CGXDLMSObject* constructed_obj;

	uint8_t* idx_constructed_obj;

	std::vector<CGXDLMSObject*> dlms_only_obj;

	InitObjField init_callback;

	TypeObj type_callback;

	void CreateObject(DLMS_OBJECT_TYPE type);
public:
	CGXDLMSObjectCollection();

    ~CGXDLMSObjectCollection();

    CGXDLMSObject* FindByLN(DLMS_OBJECT_TYPE type, std::string& ln);

	unsigned char* FindByLN(const char* ln);

    CGXDLMSObject* FindByLN(DLMS_OBJECT_TYPE type, CGXByteBuffer& ln);

    CGXDLMSObject* FindBySN(unsigned short sn);

	std::vector<CGXDLMSObject*>& GetDlmsObj();

    void push_back(unsigned char* item);

	void push_back(CGXDLMSObject* item);

	int sizeRequiredObj();

	void clear();

	InitObjField GetInitCallback();

	void SetInitCallback(InitObjField init);

	TypeObj GetTypeObjCallback();

	void SetTypeObjCallback(TypeObj type);

    void Free();

	void FreeConstructedObj();

    std::string ToString();
};

#endif //GXDLMSOBJECTCOLLECTION_H
