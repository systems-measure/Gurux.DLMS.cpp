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
#include "GXDLMSLNParameters.h"
#include "GXDLMSAssociationLogicalName.h"

class CGXDLMSServer
{
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
	void GetRequestNormal(CGXByteBuffer& data, CGXDLMSLNParameters& p);

	/**
    * Handle get request next data block command.
    *
    * @param data
    *            Received data.
    */
	void CheckGetRequestLongTransaction(CGXByteBuffer& data, CGXDLMSLNParameters& p);

	void GetRequestNextDataBlock(CGXByteBuffer& data, CGXDLMSLNParameters& p);

    /**
     * Handle get request with list command.
     *
     * @param data
     *            Received data.
     */
	void GetRequestWithList(CGXByteBuffer& data, CGXDLMSLNParameters& p);

	void GetRequestError(CGXDLMSLNParameters& p);

	void GetSetRequestBlockIndex(CGXByteBuffer& data,
		CGXDLMSLNParameters& p);

	void HandleSetRequestNormalAndFirstDataBlock(
		CGXByteBuffer& data,
		CGXDLMSLNParameters& p);

  void HandleSetRequestWithDataBlock(
      CGXByteBuffer& data,
      CGXDLMSLNParameters& p);


	void HanleMethodRequestNormal(
		CGXByteBuffer& data,
		CGXDLMSLNParameters& p);

    /**
    * Reset settings when connection is made or close.
    *
    * @param connected
    *            Is co3nnected.
    */
  void Reset(bool connected);

	void ClearLastLTInfo(CGXDLMSLNParameters& p);

    /**
    * Handle received command.
    */
    int HandleCommand(
        DLMS_COMMAND& cmd,
        CGXByteBuffer& data);

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
	* Handle Action request.
	*
	* @return Reply to the client.
	*/
	int HandleMethodRequest(
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
protected:

	/**
	* Try to take single configurator session, if fail p will carry status TEMPORARY_FAILURE
	* If current interface is optoport then single configurator session taked garranty 
	*/
	virtual void CheckTakeConfiguratorSession(CGXDLMSLNParameters& p, CGXDLMSValueEventArg* arg) = 0;

	/**
	* Reply data.
	*/
	CGXByteBuffer m_ReplyData;

    bool m_LinkEstablished;
	/**
	* Received data.
	*/
	CGXByteBuffer m_RxTxData;

    /**
     * Server Settings.
     */
    CGXDLMSSettings m_Settings;

	/**
	* Server Current ALN.
	*/
	CGXDLMSAssociationLogicalName *m_CurrentALN;
   
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

	/**
	* Action is occurred.
	*
	* @param args
	*            Handled action requests.
	*/
	virtual void PreAction(
		CGXDLMSValueEventArg* arg) = 0;

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
	* Return current long transaction processing or not
	*/
	bool IsLongTransaction();

	/**
	* Return event argument of request with target object pointer, attribute index and selective access flag
	*/
	CGXDLMSValueEventArg* GetObjectInfoFromRequest(CGXByteBuffer& data, CGXDLMSLNParameters& p);

	/**
	* Take parameters from request, if it presents
	*/
	void GetParametersFromRequest(CGXByteBuffer& data, CGXDLMSLNParameters& p, CGXDLMSValueEventArg* arg);

	/**
	* Take value from request (for set request), if it presents 
	*/
	void GetValueFromRequest(CGXByteBuffer& data, CGXDLMSValueEventArg* arg);

	/**
	* Verificate value type (for set request). 
	* If value type is octet string, but object attribute type is not octet string, try to cast value to wanted type 
	*/
	bool CheckValueType(CGXDLMSLNParameters& p, CGXDLMSValueEventArg* arg);

	/**
	* Free event argument, long transaction of server and constructed object by current association LN
	* @param arg 
	            Value event argument
	* @param long_trns_clear
				Need clear long transaction
	*/
	void BeforeReturn(CGXDLMSValueEventArg* arg, bool long_trns_clear);

public:
	/**
	* @return Get settings.
	*/
	CGXDLMSSettings& GetSettings();

	CGXDLMSAssociationLogicalName* GetCurrentALN();

	/**
     * Constructor.
     *
     * @param logicalNameReferencing
     *            Is logical name referencing used.
     * @param type
     *            Interface type.
     */
    CGXDLMSServer();

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
    void SetMaxReceivePDUSize( unsigned short value);

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
    int HandleRequest();

};
#endif //GXDLMSSERVER_H
