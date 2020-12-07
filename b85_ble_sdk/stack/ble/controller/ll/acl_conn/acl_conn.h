/********************************************************************************************************
 * @file	acl_conn.h
 *
 * @brief	This is the header file for BLE SDK
 *
 * @author	BLE GROUP
 * @date	2020.06
 *
 * @par     Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd. ("TELINK")
 *          All rights reserved.
 *          
 *          Redistribution and use in source and binary forms, with or without
 *          modification, are permitted provided that the following conditions are met:
 *          
 *              1. Redistributions of source code must retain the above copyright
 *              notice, this list of conditions and the following disclaimer.
 *          
 *              2. Unless for usage inside a TELINK integrated circuit, redistributions 
 *              in binary form must reproduce the above copyright notice, this list of 
 *              conditions and the following disclaimer in the documentation and/or other
 *              materials provided with the distribution.
 *          
 *              3. Neither the name of TELINK, nor the names of its contributors may be 
 *              used to endorse or promote products derived from this software without 
 *              specific prior written permission.
 *          
 *              4. This software, with or without modification, must only be used with a
 *              TELINK integrated circuit. All other usages are subject to written permission
 *              from TELINK and different commercial license may apply.
 *
 *              5. Licensee shall be solely responsible for any claim to the extent arising out of or 
 *              relating to such deletion(s), modification(s) or alteration(s).
 *         
 *          THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *          ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *          WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *          DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER BE LIABLE FOR ANY
 *          DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *          (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *          LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *          ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *          (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *          SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *         
 *******************************************************************************************************/
#ifndef LLMS_CONN_H_
#define LLMS_CONN_H_



/**
 * @brief
 */
#define			BLM_CONN_HANDLE									BIT(7)
#define			BLS_CONN_HANDLE									BIT(6)
#define 		BLT_ACL_CONN_MASTER_HANDLE						BLM_CONN_HANDLE
#define 		BLT_ACL_CONN_SLAVE_HANDLE						BLS_CONN_HANDLE
#define			BLT_ACL_CONN_HANDLE								(BLT_ACL_CONN_MASTER_HANDLE | BLT_ACL_CONN_SLAVE_HANDLE)



#define			CONN_IDX_MASK									15



#define			MAX_OCTETS_DATA_LEN_27							27
#define			MAX_OCTETS_DATA_LEN_EXTENSION					251

/**
 * @brief      This function is used to get the current number of ACL connections.
 * @param[in]  none.
 * @return     The number of currently connected ACLs.
 */
int 		blc_ll_getCurrentConnectionNumber(void);   //master + slave connection number


/**
 * @brief      This function is used to obtain the number of ACL connections of the Master role.
 * @param[in]  none.
 * @return     The number of currently connected master ACLs.
 */
int 		blc_ll_getCurrentMasterRoleNumber(void);   //master role number


/**
 * @brief      This function is used to obtain the number of ACL connections of the Slave role.
 * @param[in]  none.
 * @return     The number of currently connected slave ACLs.
 */
int 		blc_ll_getCurrentSlaveRoleNumber(void);    //slave  role number


/**
 * @brief      This function is used to configure the number of master and slave connections that the protocol stack can support.
 * @param[in]  max_master_num - Number of master ACL connections supported.
 * @param[in]  max_slave_num - Number of slave ACL connections supported.
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_ll_setMaxConnectionNumber(int max_master_num, int max_slave_num);


/**
 * @brief      This function is used to obtain the currently available TX FIFO numbers according to the ACL handle.
 * @param[in]  connHandle - ACL connection handle.
 * @return     available TX FIFO numbers
 */
u8  		blc_ll_getTxFifoNumber (u16 connHandle);


/**
 * @brief      This function is used to disconnect the device with the specified ACL connection handle and specify the reason for the disconnection.
 * @param[in]  connHandle - ACL connection handle.
 * @param[in]  reason - Reason for disconnection..
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_ll_disconnect (u16 connHandle, u8 reason);



/**
 * @brief      This function is used to obtain the connection establishment time point corresponding to the current ACL connection handle.
 * @param[in]  connHandle - ACL connection handle.
 * @param[in]  reason - Reason for disconnection..
 * @return     The connection establishment time point corresponding to the current ACL connection handle: Based on 16M system clock ticks.
 */
u32 		blc_ll_getConnectionStartTick(u16 connHandle);

ble_sts_t 	blc_ll_readRemoteVersion(u16 connHandle);


/**
 * @brief      for user to initialize ACL connection module, this is must if user want use ACL master role or ACL slave role.
 * @param	   none
 * @return     none
 */
void		blc_ll_initAclConnection_module(void);



/**
 * @brief      for user to initialize LinkLayer ACL connection RX FIFO.
 * 			   all connection will share the FIFO.
 * @param[in]  pRxbuf - RX FIFO buffer address.
 * @param[in]  fifo_size - RX FIFO size
 * @param[in]  fifo_number - RX FIFO number, can only be 4, 8, 16 or 32
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_ll_initAclConnRxFifo(u8 *pRxbuf, int fifo_size, int fifo_number);



/**
 * @brief      for user to initialize master LinkLayer ACL connection TX FIFO.
 * @param[in]  pRxbuf - TX FIFO buffer address.
 * @param[in]  fifo_size - TX FIFO size
 * @param[in]  fifo_number - TX FIFO number, can only be 4, 8, 16 or 32
 * @param[in]  conn_number - Number of supported master ACL connections
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_ll_initAclConnMasterTxFifo(u8 *pTxbuf, int fifo_size, int fifo_number, int conn_number);


/**
 * @brief      for user to initialize slave LinkLayer ACL connection TX FIFO.
 * @param[in]  pRxbuf - TX FIFO buffer address.
 * @param[in]  fifo_size - TX FIFO size
 * @param[in]  fifo_number - TX FIFO number, can only be 4, 8, 16 or 32
 * @param[in]  conn_number - Number of supported slave ACL connections
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_ll_initAclConnSlaveTxFifo(u8 *pTxbuf, int fifo_size, int fifo_number, int conn_number);


/**
 * @brief      check ACL whether is in establish state.
 * @param[in]  connHandle - ACL connection handle.
 * @return     status, 0:  connection not established(disconnection or connection complete but not established)
 * 					   1:  connection established state
 */
bool  		blc_ll_isAclConnEstablished(u16 connHandle);


/**
 * @brief      send data length extend request.
 * @param[in]  connHandle - ACL connection handle.
 * @param[in]  maxTxOct  - the length to request
 * @return     status, 0x00 :  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_ll_sendDateLengthExtendReq (u16 connHandle,  u16 maxTxOct);


/**
 * @brief      set ACL data length for Master and Slave.
 * @param[in]  maxRxOct - ACL max RX Oct.
 * @param[in]  maxTxOct_master - ACL master max TX Oct
 * @param[in]  maxTxOct_slave - ACL slave max TX Oct
 * @return     status, 0x00 :  succeed
 * 					   other: failed
 */
ble_sts_t	blc_ll_setAclConnMaxOctetsNumber(u8 maxRxOct, u8 maxTxOct_master, u8 maxTxOct_slave);



#endif /* LLMS_CONN_H_ */
