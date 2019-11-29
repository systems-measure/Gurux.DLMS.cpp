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
#ifndef GXDLMSLNPARAMETERS_H
#define GXDLMSLNPARAMETERS_H

#include "GXBytebuffer.h"
#include "GXDLMSSettings.h"

/**
 * LN Parameters
 */
class CGXDLMSLNParameters
{
private:

    /**
     * DLMS settings.
     */
    CGXDLMSSettings *m_Settings;
    /**
     * Data.
     */
    CGXByteBuffer* m_Data;

	  /**
	  * DLMS command.
	  */
	  DLMS_COMMAND m_Command;
    /**
     * Reply status.
     */
    unsigned char m_Status;
    /**
     * Are there more data to send or more data to receive.
     */
    bool m_MultipleBlocks;
    /**
     * Is this last block in send.
     */
    bool m_LastBlock;
    /**
     * Block index.
     */
    unsigned long m_BlockIndex;
	/**
	* Request type.
	*/
	unsigned char m_RequestType;

public:
    /**
     * Constructor.
     *
     * @param settings
     *            DLMS settings.
     * @param command
     *            Command.
     * @param commandType
     *            DLMS_COMMAND type.
     * @param attributeDescriptor
     *            Attribute descriptor.
     * @param data
     *            Data.
     */
    CGXDLMSLNParameters(CGXDLMSSettings* settings,
                        DLMS_COMMAND command,
		                unsigned char commandType,
                        CGXByteBuffer* data,
		                unsigned char status);

    /**
     * @return DLMS settings.
     */
    CGXDLMSSettings* GetSettings();

    /**
     * @return DLMS command.
     */
    DLMS_COMMAND GetCommand();

    /**
     * @return Request type.
     */
	unsigned char GetRequestType();

    /**
     * @param value
     *            the requestType to set
     */
    void SetRequestType(unsigned char value);

    /**
     * @return the data
     */
    CGXByteBuffer* GetData();

    /**
     * @return Status.
     */
	unsigned char GetStatus();

    /**
     * @param value
     *            Status to set
     */
    void SetStatus(unsigned char value);

    /**
     * @return the multipleBlocks
     */
    bool IsMultipleBlocks();

    /**
     * @param value
     *            the multipleBlocks to set
     */
    void SetMultipleBlocks(bool value);

    /**
     * @return the lastBlock
     */
    bool IsLastBlock();

    /**
     * @param value
     *            Block index.
     */
    void SetLastBlock(bool value);

    /**
     * @return Block index.
     */
    unsigned long GetBlockIndex();

    /**
     * @param value
     *            the blockIndex to set
     */
    void SetBlockIndex(unsigned long value);
};

#endif //GXDLMSLNPARAMETERS_H
