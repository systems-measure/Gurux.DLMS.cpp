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

#ifndef GXDLMSOBJECT_H
#define GXDLMSOBJECT_H

#include "GXHelpers.h"
#include "GXDateTime.h"
#include "GXDLMSValueEventArg.h"

typedef uint8_t(*TypeAttrCallback)(uint16_t construct_idx);

class CGXDLMSObjectCollection;

class CGXDLMSObject 
{
    friend class CGXDLMSObjectCollection;

    void Initialize(unsigned short class_id, unsigned char version, CGXByteBuffer* pLogicalName);
    DLMS_OBJECT_TYPE m_ObjectType;
    unsigned char m_Version;
	TypeAttrCallback get_data_type;
protected:
	unsigned char m_LN[6];
	unsigned short constr_idx;
public:

    CGXDLMSObject(void);
    CGXDLMSObject(DLMS_OBJECT_TYPE type);

    //LN Constructor.
    CGXDLMSObject(DLMS_OBJECT_TYPE type, const char* ln);
	CGXDLMSObject(unsigned short class_id, unsigned char version, const char* ln);

    virtual ~CGXDLMSObject(void);

	void SetDataTypeFunc(TypeAttrCallback callback);

	void SetConstructedIdx(uint16_t* idx);

    //Get Object's Logical or Short Name as a std::string.
    std::string GetName();

    //Get Object's Interface class type.
    DLMS_OBJECT_TYPE GetObjectType();

    //Get Object's Logical Name.
    void GetLogicalName(char* ln);
	void GetLogicalName(unsigned char* c_ln);
    void GetLogicalName(signed char* c_ln) { GetLogicalName((unsigned char*)c_ln); }

	static int GetLogicalName(CGXDLMSObject * target, CGXByteBuffer& value);

    void SetVersion(unsigned char value);
    unsigned char GetVersion();

    virtual int GetDataType(signed char index, DLMS_DATA_TYPE& type);

	virtual DLMS_DATA_TYPE GetDataType(signed char index);

    // Returns amount of attributes.
    virtual unsigned char GetAttributeCount()
    {
        assert(0);
        return 1;
    }

	// Returns amount of methods.
    virtual unsigned char GetMethodCount()
    {
        assert(0);
        return 0;
    }
};

#endif //GXDLMSOBJECT_H