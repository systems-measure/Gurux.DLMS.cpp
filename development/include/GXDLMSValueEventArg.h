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
// and/or modify it under the terms of the GNU General License
// as published by the Free Software Foundation; version 2 of the License.
// Gurux Device Framework is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General License for more details.
//
// More information of Gurux products: http://www.gurux.org
//
// This code is licensed under the GNU General License v2.
// Full text may be retrieved at http://www.gnu.org/licenses/gpl-2.0.txt
//---------------------------------------------------------------------------

#ifndef GXDLMSVALUEEVENTARGS_H
#define GXDLMSVALUEEVENTARGS_H

#include "enums.h"
#include "errorcodes.h"
#include "GXDLMSVariant.h"

class CGXDLMSObject;

class CGXDLMSValueEventArg
{
private:

	CArtVariant c_Value;

	CArtVariant m_Parameters;

	signed char event_param[10];//0-5 target_name, 6-m_Index, 7-m_Selector, 8-m_Error, 9- m_Handled

	unsigned short m_RowEndIndex;//0-m_RowToPdu, 1-m_RowBeginIndex , 2-m_RowEndIndex
    
    /**
    * DLMS server.
    */
    void* m_Server;
	/**
	* Target DLMS object
	*/
	CGXDLMSObject* m_Target;

    void Init(
        CGXDLMSObject* target,
		unsigned char * target_name,
		signed char index,
		unsigned char selector);

public:
	/**
	* DLMS server.
	*/
	void* GetServer();

	void SetServer(void* serv_instance);

	CArtVariant& GetCAValue();
    /**
    * @return Target DLMS object.
    */
    CGXDLMSObject* GetTarget();

    void SetTarget(CGXDLMSObject* value);


	signed char* GetTargetName();

	/*
	Set target name and delete target object
	*/
	void SetTargetName();
    /**
    * @return Attribute index of queried object.
    */
    signed char GetIndex();

    void SetIndex(signed char value);

	/**
	* @param value
	*            CArtVariant value.
	*/
	void SetValue(CArtVariant& value);

	void SetValue(CGXByteBuffer& value);

    /**
    * @return Optional selector.
    */
	unsigned char GetSelector();

    /**
    * @param value
    *           Selector.
    */
    void SetSelector(unsigned char value);

    /**
    * @return Optional parameters.
    */
    CArtVariant& GetParameters();

    /**
    * @param value
    *           Parameters.
    */
    void SetParameters(CArtVariant& value);


    /**
    * Constructor.
    *
    * @param target
    *            Event target.
    * @param index
    *            Event index.
    */
    CGXDLMSValueEventArg(
        CGXDLMSObject* target,
		signed char index);

    /**
    * Constructor.
    *
    * @param target
    *            Event target.
    * @param index
    *            Event index.
    * @param selector
    *            Optional read event selector.
    * @param parameters
    *            Optional parameters.
    */
    CGXDLMSValueEventArg(
        CGXDLMSObject* target,
		signed char index,
		unsigned char selector,
        CArtVariant& parameters);

	~CGXDLMSValueEventArg();
    /**
    * @return Occurred error.
    */
    DLMS_ERROR_CODE GetError();

    /**
     * @param error
     *            Occurred error.
     */
    void SetError(DLMS_ERROR_CODE value);

	/**
	* @return State of handling object attribute.
	*/
	bool GetHandled();

	/**
	* @param value
	*           setting state of handling object attribute.
	*/
	void SetHandled(bool value);

    /**
    * @return Rows end index.
    */
    unsigned short& GetRowEndIndex();

};
#endif //GXDLMSVALUEEVENTARGS_H
