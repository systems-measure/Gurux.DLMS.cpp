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

#ifndef GXDLMS_H
#define GXDLMS_H

#include "GXDLMSLimits.h"
#include "GXDLMSObject.h"
#include "GXDLMSObjectCollection.h"
#include "GXBytebuffer.h"
#include "GXDLMSSettings.h"
#include "GXDLMSVariant.h"
#include "GXCipher.h"
#include "GXReplyData.h"
#include "GXDLMSLNParameters.h"

class CGXDLMS
{
private:

    static unsigned short CountFCS16(CGXByteBuffer& buff, int index, int count);

    /////////////////////////////////////////////////////////////////////////////
    // Get adress as GXDLMSVariant.
    /////////////////////////////////////////////////////////////////////////////
    static int GetAddress(long value, unsigned long& address, int& size);

    /////////////////////////////////////////////////////////////////////////////
    // Get address as an byte array.
    /////////////////////////////////////////////////////////////////////////////
    static int GetAddressBytes(unsigned long value, CGXByteBuffer& bytes);

    /////////////////////////////////////////////////////////////////////////////
    // Check LLC bytes.
    /////////////////////////////////////////////////////////////////////////////
    // server : Is server.
    // data : Received data.
    /////////////////////////////////////////////////////////////////////////////
    static void GetLLCBytes(CGXByteBuffer& data);

    /////////////////////////////////////////////////////////////////////////////
    // Get value from data.
    /////////////////////////////////////////////////////////////////////////////
    // settings : DLMS settings.
    // reply : Received data.
    /////////////////////////////////////////////////////////////////////////////
    static int GetValueFromData(
        CGXDLMSSettings& settings,
        CGXReplyData& reply);

    /////////////////////////////////////////////////////////////////////////////
    // Get data from HDLC or wrapper frame.
    /////////////////////////////////////////////////////////////////////////////
    // reply : Received data that includes HDLC frame.
    // info : Reply data.
    /////////////////////////////////////////////////////////////////////////////
    static void GetDataFromFrame(
        CGXByteBuffer& reply,
        CGXReplyData& info);
public:

    /**
    * Handle General block transfer message.
    *
    * @param settings
    *            DLMS settings.
    * @param data
    *            received data.
    */
    static int HandleGbt(CGXDLMSSettings& settings, CGXReplyData& data);

	  static long GetLongInvokeIDPriority(CGXDLMSSettings& settings);

    /**
    * Get next logical name PDU.
    *
    * @param p
    *            LN parameters.
    * @param reply
    *            Generated message.
    */
    static void GetLNPdu(
        CGXDLMSLNParameters& p,
        CGXByteBuffer& reply);

    /**
    * Get HDLC frame for data.
    *
    * @param settings
    *            DLMS settings.
    * @param frame
    *            Frame ID. If zero new is generated.
    * @param data
    *            Data to add.
    * @return HDLC frame.
    */
    static int GetHdlcFrame(
        CGXDLMSSettings& settings,
        unsigned char frame,
        CGXByteBuffer* data,
        CGXByteBuffer& reply,
        bool remove_sent_bytes = true);

    static int GetHdlcData(
        CGXDLMSSettings& settings,
        CGXByteBuffer& reply,
        CGXReplyData& data,
        unsigned char& frame);

    /**
     * Get HDLC address from byte array.
     *
     * @param buff
     *            byte array.
     * @return HDLC address.
     */
    static int GetHDLCAddress(
        CGXByteBuffer& buff,
        unsigned long& address,
        unsigned char& addrSize);

    /**
     * Check that client and server address match.
     *
     * @param server
     *            Is server.
     * @param settings
     *            DLMS settings.
     * @param reply
     *            Received data.
     * @param index
     *            Position.
     * @return True, if client and server address match.
     */
    static int CheckHdlcAddress(
        CGXDLMSSettings& settings,
        CGXByteBuffer& reply);

    /////////////////////////////////////////////////////////////////////////////
    // Get PDU from the packet.
    /////////////////////////////////////////////////////////////////////////////
    // settings : DLMS settings.
    // data : received data.
    // cipher : Cipher interface.
    /////////////////////////////////////////////////////////////////////////////
    static int GetPdu(
        CGXDLMSSettings& settings,
        CGXReplyData& data);

    /////////////////////////////////////////////////////////////////////////////
    //
    /////////////////////////////////////////////////////////////////////////////
    static int GetData(
        CGXDLMSSettings& settings,
        CGXByteBuffer& reply,
        CGXReplyData& data);
};
#endif //GXDLMS_H
