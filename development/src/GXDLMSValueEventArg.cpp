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

#include "../include/GXDLMSValueEventArg.h"
#include "../include/GXDLMSSettings.h"
#include "../include/GXDLMSServer.h"

CGXDLMSObject* CGXDLMSValueEventArg::GetTarget()
{
    return m_Target;
}

void CGXDLMSValueEventArg::SetTarget(CGXDLMSObject* value)
{
    m_Target = value;
}

unsigned char* CGXDLMSValueEventArg::GetTargetName() 
{
	return event_param;
}

void CGXDLMSValueEventArg::SetTargetName() {
	if (m_Target != nullptr) {
		m_Target->GetLogicalName(event_param);
		m_Target = nullptr;
	}
}

unsigned char& CGXDLMSValueEventArg::GetIndex()
{
    return event_param[6];
}

void CGXDLMSValueEventArg::SetIndex(unsigned char value)
{
	event_param[6] = value;
}

CArtVariant& CGXDLMSValueEventArg::GetCAValue()
{
	return c_Value;
}

void CGXDLMSValueEventArg::SetValue(CArtVariant& value) 
{
	c_Value = value;
}

void CGXDLMSValueEventArg::SetValue(CGXByteBuffer& value) {
	c_Value = value;
}

unsigned char& CGXDLMSValueEventArg::GetSelector()
{
    return event_param[7];
}

void CGXDLMSValueEventArg::SetSelector(unsigned char& value)
{
	event_param[7] = value;
}

CArtVariant& CGXDLMSValueEventArg::GetParameters()
{
    return m_Parameters;
}

void CGXDLMSValueEventArg::SetParameters(CArtVariant& value)
{
    m_Parameters = value;
}

void CGXDLMSValueEventArg::Init(
    CGXDLMSServer* server,
    CGXDLMSObject* target,
	unsigned char * target_name,
    int index,
    int selector)
{
    m_Server = server;
    m_Settings = &server->GetSettings();
    SetTarget(target);
	if (target_name != nullptr) {
		memcpy(event_param, target_name, 6);
	}
	event_param[6] = index;
	event_param[7] = selector;
	event_param[8] = DLMS_ERROR_CODE_OK;
	event_param[9] = 0;
	row_param[0] = 0;
	row_param[1] = 0;
	row_param[2] = 0;
	m_Parameters.Reserve(0);
	c_Value.Reserve(0);
}

CGXDLMSValueEventArg::CGXDLMSValueEventArg(
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index)
{
    Init(server, target, nullptr, index, 0);
}

CGXDLMSValueEventArg::CGXDLMSValueEventArg(
    CGXDLMSServer* server,
    CGXDLMSObject* target,
    int index,
    int selector,
	CArtVariant& parameters)
{
    Init(server, target, nullptr, index, selector);
    m_Parameters = parameters;
}

CGXDLMSValueEventArg::CGXDLMSValueEventArg(
    CGXDLMSObject* target,
    int index)
{
    Init(nullptr, target, nullptr, index, 0);
}

CGXDLMSValueEventArg::CGXDLMSValueEventArg(
    CGXDLMSObject* target,
    int index,
    int selector,
	CArtVariant& parameters)
{
    Init(nullptr, target, nullptr, index, selector);
    m_Parameters = parameters;
}

CGXDLMSValueEventArg::CGXDLMSValueEventArg(
	CGXDLMSServer* server,
	unsigned char* target_name,
	int index,
	int selector,
	CArtVariant& parameters)
{
	Init(server, nullptr, target_name, index, selector);
	m_Parameters = parameters;
}

CGXDLMSValueEventArg::~CGXDLMSValueEventArg() 
{
	/*c_Value.Clear();
	m_Parameters.Clear();*/
}

DLMS_ERROR_CODE CGXDLMSValueEventArg::GetError()
{
    return (DLMS_ERROR_CODE)event_param[8];
}

void CGXDLMSValueEventArg::SetError(DLMS_ERROR_CODE value)
{
	event_param[8] = value;
}

bool CGXDLMSValueEventArg::GetSkipMaxPduSize()
{
    return (event_param[9] != 0);
}

void CGXDLMSValueEventArg::SetSkipMaxPduSize(bool value)
{
	event_param[9] = value;
}

unsigned short CGXDLMSValueEventArg::GetRowToPdu()
{
    return row_param[0];
}

void CGXDLMSValueEventArg::SetRowToPdu(unsigned short value) {
	row_param[0] = value;
}

unsigned short& CGXDLMSValueEventArg::GetRowEndIndex() {
    return row_param[2];
}

void CGXDLMSValueEventArg::SetRowEndIndex(unsigned int value) {
	row_param[2] = value;
}

unsigned int CGXDLMSValueEventArg::GetRowBeginIndex() {
    return row_param[1];
}

void CGXDLMSValueEventArg::SetRowBeginIndex(unsigned int value) {
	row_param[1] = value;
}

CGXDLMSSettings* CGXDLMSValueEventArg::GetSettings()
{
	return  m_Settings;
}

CGXDLMSServer* CGXDLMSValueEventArg::GetServer()
{
    return m_Server;
}