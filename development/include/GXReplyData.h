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

#ifndef GXREPLYDATA_H
#define GXREPLYDATA_H

#include "GXBytebuffer.h"
#include "GXDLMSVariant.h"

class CGXReplyData
{
private:
    /**
     * Is more data available.
     */
    DLMS_DATA_REQUEST_TYPES m_MoreData;
    /**
     * Received command.
     */
    DLMS_COMMAND m_Command;

	/**
	* Control filed value
	*/
	unsigned char m_ControlField;

	/**
	* Is received message General Block Transfer message.
	*/
	bool m_Gbt;

	/**
	* Is frame complete.
	*/
	bool m_Complete;
	
	/**
	* Packet Length.
	*/
	unsigned short m_PacketLength;

	/**
	* Last read position. This is used in peek to solve how far data is read.
	*/
	unsigned short m_ReadPosition;

    /**
     * Received data.
     */
    CGXByteBuffer m_Data;
    /**
     * Read value.
     */
    CArtVariant m_DataValue;
    
   
public:
    /**
     * Constructor.
     *
     * @param more
     *            Is more data available.
     * @param cmd
     *            Received command.
     * @param buff
     *            Received data.
     * @param forComplete
     *            Is frame complete.
     */
    CGXReplyData(
        DLMS_DATA_REQUEST_TYPES more,
        DLMS_COMMAND cmd,
        CGXByteBuffer& buff,
        bool complete);

    /**
     * Constructor.
     */
    CGXReplyData();

    CArtVariant& GetValue();


    void SetValue(CArtVariant& value);

	unsigned short GetReadPosition();

    void SetReadPosition(unsigned short value);

	unsigned short GetPacketLength();

    void SetPacketLength(unsigned short value);

    void SetCommand(DLMS_COMMAND value);

    void SetData(CGXByteBuffer& value);

    void SetComplete(bool value);

    /**
     * Reset data values to default.
     */
    void Clear();

    /**
     * @return Is more data available.
     */
    bool IsMoreData();

    /**
     * Is more data available.
     *
     * @return Return None if more data is not available or Frame or Block type.
     */
    DLMS_DATA_REQUEST_TYPES GetMoreData();

    void SetMoreData(DLMS_DATA_REQUEST_TYPES value);


    /**
     * Get received command.
     *
     * @return Received command.
     */
    DLMS_COMMAND& GetCommand();

    /**
     * Get received data.
     *
     * @return Received data.
     */
    CGXByteBuffer& GetData();

    /**
     * Is frame complete.
     *
     * @return Returns true if frame is complete or false if bytes is missing.
     */
    bool IsComplete();

    /**
     * @return Is received message General Block Transfer message.
     */
    bool GetGbt();

    /**
     * @param Is
     *            received message General Block Transfer message.
     */
    void SetGbt(bool value);

    /**
     * @return Control field value.
     */
    unsigned char GetControlField(void);
    
    /**
     * @param New control field value.
     */
    void SetControlField(unsigned char ctl);
};

#endif //GXREPLYDATA_H