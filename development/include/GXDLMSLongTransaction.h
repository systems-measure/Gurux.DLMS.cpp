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

#ifndef GXDLMSLONGTRANSACTION_H
#define GXDLMSLONGTRANSACTION_H

#include <vector>
#include "enums.h"
#include "GXBytebuffer.h"
#include "GXDLMSValueEventArg.h"
#include "GXDLMSValueEventCollection.h"

class CGXDLMSLongTransaction
{
private:
    /**
    * Executed command.
    */
    DLMS_COMMAND m_Command;

	uint8_t m_Command_type;

    /**
     * Targets.
     */
    CGXDLMSValueEventCollection m_Targets;

    /**
     * Extra data from PDU.
     */
    CGXByteBuffer m_Data;

public:

    /**
     * Constructor.
     *
     * @param targets
     * @param command
     * @param data
     */
	CGXDLMSLongTransaction()
	{
		m_Targets.clear();
		m_Command = DLMS_COMMAND_NONE;
		m_Command_type = 0;
		m_Data.Clear();
	}

	void ClearEventTo(CGXDLMSValueEventCollection::iterator endEvent) {
		for (CGXDLMSValueEventCollection::iterator it = m_Targets.begin(); it != endEvent; ++it) {
			delete *it;
		}
		m_Targets.erase(m_Targets.begin(), endEvent);
	}

    void SetLongTransactionList(CGXDLMSValueEventCollection& targets,
                           DLMS_COMMAND command, uint8_t com_type, CGXByteBuffer& data)
    {
        m_Targets.insert(m_Targets.end(), targets.begin(), targets.end());
        targets.clear();
        m_Command = command;
		m_Command_type = com_type;
        m_Data.Set(&data, data.GetPosition());
    }

	void SetLongTransactionEvent(CGXDLMSValueEventArg* event,
		DLMS_COMMAND command, uint8_t com_type, CGXByteBuffer& data)
	{
		m_Targets.push_back(event);
		m_Command = command;
		m_Command_type = com_type;
		m_Data.Set(&data, data.GetPosition());
	}

	void SetLongTransactionEvent(CGXDLMSValueEventArg* event,
		DLMS_COMMAND command, uint8_t com_type)
	{
		m_Targets.push_back(event);
		m_Command = command;
		m_Command_type = com_type;
	}

    /**
     * @return Executed command.
     */
    DLMS_COMMAND GetCommand()
    {
        return m_Command;
    }

	void SetCommand(DLMS_COMMAND command) {
		m_Command = command;
	}

	uint8_t GetCommandType()
	{
		return m_Command_type;
	}

	void SetCommandType(uint8_t command_type) {
		m_Command_type = command_type;
	}

    /**
     * @return Targets.
     */
    std::vector<CGXDLMSValueEventArg*>& GetTargets()
    {
        return m_Targets;
    }

    /**
     * @return data.
     */
    CGXByteBuffer& GetData()
    {
        return m_Data;
    }

    /**
     * @param value
     *            New data.
     */
    void SetData(CGXByteBuffer& value)
    {
        m_Data.Clear();
        m_Data.Set(&value, value.GetPosition());
    }

	void SetLongTransactionEvent(CGXDLMSValueEventArg* event) {
		m_Targets.push_back(event);
	}

	void Clear() {
		for (std::vector<CGXDLMSValueEventArg*>::iterator it = m_Targets.begin(); it != m_Targets.end(); ++it)
		{
			delete *it;
		}
		m_Targets.clear();
		m_Data.Clear();
		m_Command_type = 0;
		m_Command = DLMS_COMMAND_NONE;
	}
};
#endif //GXDLMSLONGTRANSACTION_H
