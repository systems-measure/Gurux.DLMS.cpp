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

#include "GXDLMSObject.h"

typedef void(*InitObjField)(CGXDLMSObject* constr_obj, uint16_t* idx_cnstrd);

typedef unsigned char(*TypeObj)(const char* obis, uint16_t* idx_cnstrd);

class CGXDLMSObjectCollection
{
private:
	CGXDLMSObject* constructed_obj;

	uint16_t* idx_constructed_obj;

	uint8_t** objects_ln;

	uint16_t size_collection;

	uint16_t num_obj_in_collection;

	CGXDLMSObject* m_currentALN;

	InitObjField init_callback;

	TypeObj type_callback;

	void CreateObject(DLMS_OBJECT_TYPE type);
public:

	CGXDLMSObjectCollection();

	CGXDLMSObjectCollection(uint16_t size);

    ~CGXDLMSObjectCollection();

	CGXDLMSObject* MakeByPosition(uint16_t pos);

    CGXDLMSObject* FindByLN(uint8_t* ln);

	unsigned char* FindByLN(const char* ln);

    CGXDLMSObject* FindByLN(CGXByteBuffer& ln);

	CGXDLMSObject* GetCurALN();

	uint8_t** GetObjectsCollection();

	bool empty();

	uint8_t size();

	void Init(uint8_t new_size);

  void push_back(unsigned char* item);

	void push_back_aln(CGXDLMSObject* item);

	void clear();

	void insert(uint16_t start_pos, uint8_t** src, uint16_t count);

	InitObjField GetInitCallback();

	void SetInitCallback(InitObjField init);

	TypeObj GetTypeObjCallback();

	void SetTypeObjCallback(TypeObj type);

	void FreeConstructedObj();

};

#endif //GXDLMSOBJECTCOLLECTION_H
