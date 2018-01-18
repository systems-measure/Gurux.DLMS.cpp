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

#include "GXAttributeCollection.h"
#include "GXDLMSVariant.h"
#include "IGXDLMSBase.h"
#include "GXHelpers.h"
#include "GXDateTime.h"

typedef uint8_t(*TypeAttrCallback)(uint8_t construct_idx);

class CGXDLMSObjectCollection;

class CGXDLMSObject : public IGXDLMSBase
{
    friend class CGXDLMSClient;
    friend class CGXDLMSObjectCollection;
    friend class CGXDLMSObjectFactory;
    friend class CGXDLMSAssociationLogicalName;
    friend class CGXDLMSAssociationShortName;

    void Initialize(unsigned short class_id, unsigned char version, CGXByteBuffer* pLogicalName);
    DLMS_OBJECT_TYPE m_ObjectType;
    unsigned char m_Version;
	TypeAttrCallback get_data_type;
protected:
   	bool m_DataValidity;
    unsigned char m_LN[6];
	unsigned char constr_idx;

    static int GetLogicalName(CGXDLMSObject * target, CGXByteBuffer& value);
    static int SetLogicalName(CGXDLMSObject * target, CArtVariant& value);
	
	void SetAttributeCount(unsigned char count);
	void SetMethodCount(unsigned char count);
public:

    static bool IsLogicalNameEmpty(unsigned char* pLN)
    {
        const unsigned char EmptyLN[] = { 0, 0, 0, 0, 0, 0 };
        return memcmp(pLN, EmptyLN, 6) == 0;
    }

    CGXDLMSObject(void);
    CGXDLMSObject(DLMS_OBJECT_TYPE type);

    //LN Constructor.
    CGXDLMSObject(DLMS_OBJECT_TYPE type, const char* ln);
    CGXDLMSObject(unsigned short class_id, unsigned char version, CGXByteBuffer& ln);

    virtual ~CGXDLMSObject(void);

	void SetDataTypeFunc(TypeAttrCallback callback);

	//Get Object's Data validity
	bool GetDataValidity();

	void SetDataValidity(bool validity);

	void SetConstructedIdx(uint8_t* idx);

    //Get Object's Logical or Short Name as a std::string.
    std::string GetName();

    int SetName(CGXDLMSVariant& value);

    //Get Object's Interface class type.
    DLMS_OBJECT_TYPE GetObjectType();

    //Get Object's Logical Name.
    void GetLogicalName(char* ln);

	void GetLogicalName(unsigned char* c_ln);

    void SetVersion(unsigned char value);
    unsigned char GetVersion();

    virtual int GetDataType(signed char index, DLMS_DATA_TYPE& type);

	virtual DLMS_DATA_TYPE GetDataType(signed char index);

    // Returns amount of attributes.
    virtual int GetAttributeCount()
    {
        assert(0);
        return 1;
    }

	// Returns amount of methods.
    virtual int GetMethodCount()
    {
        assert(0);
        return 0;
    }
	
    // Returns value of given attribute.
    virtual int GetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
    {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }

    // Set value of given attribute.
    virtual int SetValue(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
    {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }

    // Set value of given attribute.
    virtual int Invoke(CGXDLMSSettings& settings, CGXDLMSValueEventArg& e)
    {
        e.SetError(DLMS_ERROR_CODE_READ_WRITE_DENIED);
        return DLMS_ERROR_CODE_OK;
    }
};

class CGXDLMSCustomObject : public CGXDLMSObject
{
public:
    CGXDLMSCustomObject(DLMS_OBJECT_TYPE type) : CGXDLMSObject(type)
    {
    }
};

#endif //GXDLMSOBJECT_H