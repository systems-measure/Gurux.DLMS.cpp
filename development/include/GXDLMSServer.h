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

#ifndef GXDLMSSERVER_H
#define GXDLMSSERVER_H

#include <vector>
#include "GXDLMSLongTransaction.h"
#include "GXReplyData.h"
#include "GXDLMSSettings.h"
#include "GXDLMSLNParameters.h"

class CGXDLMSProfileGeneric;
class CGXDLMSServer
{
    friend class CGXDLMSProfileGeneric;
    friend class CGXDLMSValueEventArg;
    friend class CGXDLMSAssociationLogicalName;
    friend class CGXDLMSAssociationShortName;
private:
    CGXReplyData m_Info;

    /**
     * Long get or read transaction information.
     */
    CGXDLMSLongTransaction* m_Transaction;
	/**
    * Parse SNRM Request. If server do not accept client empty byte array is
    * returned.
    *
    * @return Returns returned UA packet.
    */
    int HandleSnrmRequest(CGXByteBuffer& data);

    /**
    * Handle get request normal command.
    *
    * @param data
    *            Received data.
    */
    int GetRequestNormal(CGXByteBuffer& data);

    /**
    * Handle get request next data block command.
    *
    * @param data
    *            Received data.
    */
    int GetRequestNextDataBlock(CGXByteBuffer& data);

    /**
     * Handle get request with list command.
     *
     * @param data
     *            Received data.
     */
    int GetRequestWithList(CGXByteBuffer& data);

	int GetRequestError();

    int HandleSetRequest(
        CGXByteBuffer& data,
        unsigned char& type,
        CGXDLMSLNParameters& p);

    int HanleSetRequestWithDataBlock(
        CGXByteBuffer& data,
        CGXDLMSLNParameters& p);


    /**
    * Reset settings when connection is made or close.
    *
    * @param connected
    *            Is co3nnected.
    */
    void Reset(bool connected);

    /**
    * Handle received command.
    */
    int HandleCommand(
        DLMS_COMMAND& cmd,
        CGXByteBuffer& data,
        CGXByteBuffer& reply);

    /**
    * Parse AARQ request that client send and returns AARE request.
    *
    * @return Reply to the client.
    */
    int HandleAarqRequest(
        CGXByteBuffer& data);

    /**
     * Handle Set request.
     *
     * @return Reply to the client.
     */
    int HandleSetRequest(
        CGXByteBuffer& data);

    /**
    * Handle Get request.
    *
    * @return Reply to the client.
    */
    int HandleGetRequest(
        CGXByteBuffer& data);
  
    /**
    * Handle RR request.
    *
    * @param 
    *            
    * @return 
    */
    int HandleReadyRead(DLMS_COMMAND& cmd,
                        unsigned char &frame);           
    
    /**
    *  Checks Control field of frame
    *
    * @param ctl 
    *           Control field value
    *
    * @param reply
    *           Buffer for response in case of error.
    *        
    * @return true - control field ok, false - bad control field 
    */
    bool CheckCtlField(unsigned char ctl,
                       CGXByteBuffer &reply);
    
	bool m_Initialized;
protected:
  
	/**
	* Handle action request.
	*
	* @param reply
	*            Received data from the client.
	* @return Reply.
	*/
	virtual int HandleMethodRequest(
		CGXByteBuffer& data);

	CGXDLMSValueEventArg * getCGXDLMSValueEventArg(
		CGXDLMSServer* server,
		CGXDLMSObject* target,
		int index,
		int selector,
		CArtVariant& parameters);
	/**
	* Reply data.
	*/
	CGXByteBuffer m_ReplyData;

   bool m_LinkEstablished;
	/**
	* Received data.
	*/
	CGXByteBuffer m_ReceivedData;

    /**
     * Server Settings.
     */
    CGXDLMSSettings m_Settings;

	/**
	* Server Current ALN.
	*/
	CGXDLMSAssociationLogicalName *m_CurrentALN;

    /**
     * @param value
     *            Cipher interface that is used to cipher PDU.
     */
    void SetCipher(CGXCipher* value);

   

    /**
        * Check is data sent to this server.
        *
        * @param serverAddress
        *            Server address.
        * @param clientAddress
        *            Client address.
        * @return True, if data is sent to this server.
        */
    virtual bool IsTarget(
        unsigned long int serverAddress,
        unsigned long clientAddress) = 0;

    /**
     * Check whether the authentication and password are correct.
     *
     * @param authentication
     *            Authentication level.
     * @param password
     *            Password.
     * @return Source diagnostic.
     */
    virtual DLMS_SOURCE_DIAGNOSTIC ValidateAuthentication(
        DLMS_AUTHENTICATION authentication,
        CGXByteBuffer& password) = 0;


    /**
     * Read selected item(s).
     *
     * @param args
     *            Handled read requests.
     */
    virtual void PreRead(
        CGXDLMSValueEventArg* arg) = 0;

    /**
     * Write selected item(s).
     *
     * @param args
     *            Handled write requests.
     */
    virtual void PreWrite(
        CGXDLMSValueEventArg* arg) = 0;

	/*
	If write data or actions with data were successful, then counter of configuarations 
	and date of last configurations should update by this 
	*/
	virtual void Configurated() = 0;

	/**
	* Fixing events associated with changes in a data
	* based value. Usually this is not used.
	*
	* @param value
	*            type event
	*/
	virtual void FixateCorrectDataEvent(unsigned char event) = 0;

	/*
	Check than push message exists and need send it by HDLC protocol
	return true if invokes server's interface is Rs485 and push message exists
	*/
	virtual void CheckPushNeeded(CGXReplyData& info) = 0;

	/*
	Check special CALLING device phisical address in SNRM request if push message sended
	*/
	virtual bool CheckCallingAfterPush() = 0;

	/*
	Reset push state if recived SNRM request with valid server address before 
	recive special CALLING device phisical address in SNRM request
	*/
	virtual void ResetPushState() = 0;

    /**
     * Accepted connection is made for the server. All initialization is done
     * here.
     */
    virtual void Connected() = 0;

    /**
     * Client has try to made invalid connection. Password is incorrect.
     *
     * @param connectionInfo
     *            Connection information.
     */
    virtual void InvalidConnection() = 0;

    /**
     * Server has close the connection. All clean up is made here.
     */
    virtual void Disconnected() = 0;

    /**
    * Get attribute access mode.
    *
    * @param arg
    *            Value event argument.
    * @return Access mode.
    * @throws Exception
    *             Server handler occurred exceptions.
    */
    virtual DLMS_ACCESS_MODE GetAttributeAccess(CGXDLMSValueEventArg* arg) = 0;

    /**
    * Get method access mode.
    *
    * @param arg
    *            Value event argument.
    * @return Method access mode.
    * @throws Exception
    *             Server handler occurred exceptions.
    */
    virtual DLMS_METHOD_ACCESS_MODE GetMethodAccess(CGXDLMSValueEventArg* arg) = 0;

    /**
     * Action is occurred.
     *
     * @param args
     *            Handled action requests.
     */
    virtual void PreAction(
        CGXDLMSValueEventArg* arg) = 0;

	bool IsLongTransaction();

public:
	/**
	* @return Get settings.
	*/
	CGXDLMSSettings& GetSettings();
    /**
     * @return Client to Server challenge.
     */
    CGXByteBuffer& GetCtoSChallenge();

    /**
     * @return Server to Client challenge.
     */
    CGXByteBuffer& GetStoCChallenge();

    /**
     * @return Interface type.
     */
    DLMS_INTERFACE_TYPE GetInterfaceType();

    /**
     * Server to Client custom challenge. This is for debugging purposes. Reset
     * custom challenge settings StoCChallenge to NULL.
     *
     * @param value
     *            Server to Client challenge.
     */
    void SetStoCChallenge(
        CGXByteBuffer& value);

    /**
     * Set starting packet index. Default is One based, but some meters use Zero
     * based value. Usually this is not used.
     *
     * @param value
     *            Zero based starting index.
     */
    void SetStartingPacketIndex(int value);

    /**
     * @return Invoke ID.
     */
    int GetInvokeID();

    /**
     * Constructor.
     *
     * @param logicalNameReferencing
     *            Is logical name referencing used.
     * @param type
     *            Interface type.
     */
    CGXDLMSServer( DLMS_INTERFACE_TYPE type);

    /**
    * Destructor.
    */
    ~CGXDLMSServer();

    /**
     * @return List of objects that meter supports.
     */
    CGXDLMSObjectCollection*& GetItems();

    /**
     * @return Information from the connection size that server can handle.
     */
    CGXDLMSLimits& GetLimits();

    /**
     * Retrieves the maximum size of received PDU. PDU size tells maximum size
     * of PDU packet. Value can be from 0 to 0xFFFF. By default the value is
     * 0xFFFF.
     *
     * @return Maximum size of received PDU.
     */
    unsigned short GetMaxReceivePDUSize();

    /**
     * @param value
     *            Maximum size of received PDU.
     */
    void SetMaxReceivePDUSize(
        unsigned short value);



	 /**
     * Initialize server. This must call after server objects are set.
     */
    int Initialize();

    /**
     * Reset after connection is closed.
     */
    void Reset();

    ///**
    // * Handles client request.
    // *
    // * @param data
    // *            Received data from the client.
    // * @return Response to the request. Response is NULL if request packet is
    // *         not complete.
    // */
    int HandleRequest(CGXByteBuffer& reply);


    /**
    * Server will tell what functionality is available for the client.
    * @return Available functionality.
    */
    DLMS_CONFORMANCE GetConformance();

    /**
    * Server will tell what functionality is available for the client.
    *
    * @param value
    *            Available functionality.
    */
    void SetConformance(DLMS_CONFORMANCE value);
};
#endif //GXDLMSSERVER_H
