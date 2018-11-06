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

#include "../include/GXReplyData.h"

CGXReplyData::CGXReplyData(
    DLMS_DATA_REQUEST_TYPES more,
    DLMS_COMMAND cmd,
    CGXByteBuffer& buff,
    bool complete)
{
    Clear();
    m_MoreData = more;
    m_Command = cmd;
    m_Data = buff;
    m_Complete = complete;
    m_ControlField = 0xFF;
}

CGXReplyData::CGXReplyData()
{
    Clear();
}

CArtVariant& CGXReplyData::GetValue()
{
    return m_DataValue;
}

void CGXReplyData::SetValue(CArtVariant& value)
{
    m_DataValue = value;
}

unsigned short CGXReplyData::GetReadPosition()
{
    return m_ReadPosition;
}

void CGXReplyData::SetReadPosition(unsigned short value)
{
    m_ReadPosition = value;
}

unsigned short CGXReplyData::GetPacketLength()
{
    return m_PacketLength;
}

void CGXReplyData::SetPacketLength(unsigned short value)
{
    m_PacketLength = value;
}

void CGXReplyData::SetCommand(DLMS_COMMAND value)
{
    m_Command = value;
}

void CGXReplyData::SetData(CGXByteBuffer& value)
{
    m_Data = value;
}

void CGXReplyData::SetComplete(bool value)
{
    m_Complete = value;
}

void CGXReplyData::Clear()
{
    m_MoreData = DLMS_DATA_REQUEST_TYPES_NONE;
    m_Command = DLMS_COMMAND_NONE;
    m_Data.Clear();
    m_Complete = false;
    m_DataValue.Clear();
    m_ReadPosition = 0;
    m_PacketLength = 0;
    m_Gbt = false;
}

bool CGXReplyData::IsMoreData()
{
    return m_MoreData != DLMS_DATA_REQUEST_TYPES_NONE;
}

DLMS_DATA_REQUEST_TYPES CGXReplyData::GetMoreData()
{
    return m_MoreData;
}

void CGXReplyData::SetMoreData(DLMS_DATA_REQUEST_TYPES value)
{
    m_MoreData = value;
}

DLMS_COMMAND& CGXReplyData::GetCommand()
{
    return m_Command;
}

CGXByteBuffer& CGXReplyData::GetData()
{
    return m_Data;
}

bool CGXReplyData::IsComplete()
{
    return m_Complete;
}

bool CGXReplyData::GetGbt()
{
    return m_Gbt;
}

void CGXReplyData::SetGbt(bool value)
{
    m_Gbt = value;
}

unsigned char CGXReplyData::GetControlField(void)
{
    return m_ControlField;
}
        
void CGXReplyData::SetControlField(unsigned char ctl)
{
    m_ControlField = ctl;
}