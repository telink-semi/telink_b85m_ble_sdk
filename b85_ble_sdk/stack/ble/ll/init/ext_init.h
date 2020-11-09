/********************************************************************************************************
 * @file	ext_init.h
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
#ifndef EXT_INIT_H_
#define EXT_INIT_H_



/**
 * @brief      for user to initialize extended initiating module
 * 			   notice that only one module can be selected between legacy initiating module and extended initiating module
 * @param	   none
 * @return     none
 */
void 		blc_ll_initExtInitiating_module(void);





/**
 * @brief      This function is used to create an ACL connection to a connectable advertiser.
 * @param[in]  pCmdParam - point to a buffer for extended scan parameters.
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t 	blc_hci_le_extended_createConnection( hci_le_ext_createConn_cmdParam_t * pCmdParam);




/**
 * @brief      This function is used to create an ACL connection to a connectable advertiser.
 *             init_phys can be only 1M PHY or 2M PHY or Coded PHY, but can not be two or three of them
 * @param[in]  init_filterPolicy
 * @param[in]  ownAdr_type
 * @param[in]  peerAddr_type
 * @param[in]  *peerAddr
 * @param[in]  init_phys
 * @param[in]  scan_interval
 * @param[in]  scan_window
 * @param[in]  conn_min
 * @param[in]  conn_max
 * @param[in]  conn_latency
 * @param[in]  timeout
 * @param[in]  ce_min
 * @param[in]  ce_max
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t 	blc_ll_extended_createConnection_1_phy( init_fp_t  init_filterPolicy, own_addr_type_t  ownAdr_type, u8	peerAddr_type, u8 *peerAddr,
													init_phy_t init_phys, 		  u16 scan_interval,  			u16 scan_window,
													u16 conn_min, u16 conn_max,u16 conn_latency, u16 timeout,u16 ce_min, u16 ce_max );






#endif /* EXT_INIT_H_ */
