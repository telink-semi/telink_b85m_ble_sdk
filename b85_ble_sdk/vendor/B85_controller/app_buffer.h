/********************************************************************************************************
 * @file	app_buffer.h
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
#ifndef APP_BUFFER_H_
#define APP_BUFFER_H_

#include "tl_common.h"

#include "app_config.h"



/********************* USB_DEBUG_LOG FIFO allocation, Begin *******************************/

#if (APP_DUMP_EN)
	extern my_fifo_t print_fifo;
	extern	u8 	print_fifo_b[];
#endif

/******************** USB_DEBUG_LOG FIFO allocation, End ***********************************/




/********************* ACL connection LinkLayer TX & RX data FIFO allocation, Begin *******************************/

//CONN Rx fifo size
#define ACL_RX_MAX_DLE				(251)
//slave tx fifo size
#define ACL_SLAVE_TX_MAX_DLE		(251)
//master tx fifo size
#define ACL_MASTER_TX_MAX_DLE		(251)

#define ACL_RX_FIFO_SIZE		 	ACL_DLE_RX_FIFO_SIZE(ACL_RX_MAX_DLE)
#define ACL_RX_FIFO_NUM				8

#define ACL_SLAVE_TX_FIFO_SIZE		ACL_DLE_TX_FIFO_SIZE(ACL_SLAVE_TX_MAX_DLE)
#define ACL_SLAVE_TX_FIFO_NUM		8 //Different process for different MCU: kite&vulture 8 and eagle 9.

#define ACL_MASTER_TX_FIFO_SIZE		ACL_DLE_TX_FIFO_SIZE(ACL_MASTER_TX_MAX_DLE)
#define ACL_MASTER_TX_FIFO_NUM		8 //Different process for different MCU: kite&vulture 8 and eagle 9.

extern	u8	app_acl_rxfifo[];
extern	u8	app_acl_mstTxfifo[];
extern	u8	app_acl_slvTxfifo[];

/******************** ACL connection LinkLayer TX & RX data FIFO allocation, End ***********************************/




/***************************** HCI TX & RX data FIFO allocation, Begin *********************************************/
#define HCI_MAX_TX_SIZE				max2(ACL_SLAVE_TX_MAX_DLE, ACL_MASTER_TX_MAX_DLE) //support common tx max

#define HCI_TX_FIFO_SIZE			HCI_FIFO_SIZE(HCI_MAX_TX_SIZE)
#define HCI_TX_FIFO_NUM				8

#define HCI_RX_FIFO_SIZE			HCI_FIFO_SIZE(ACL_RX_MAX_DLE)
#define HCI_RX_FIFO_NUM				4

#define HCI_RX_ACL_FIFO_SIZE		HCI_FIFO_SIZE(ACL_RX_MAX_DLE)
#define HCI_RX_ACL_FIFO_NUM			8

#if (HCI_NEW_FIFO_FEATURE_ENABLE)
extern	u8	app_hci_rxfifo[];
extern	u8	app_hci_txfifo[];
extern	u8	app_hci_rxAclfifo[];
#else
extern  u8  hci_rxfifo_b[];
extern  u8  hci_txfifo_b[];
#endif

//HCI UART variables
#define UART_DATA_LEN    			HCI_TX_FIFO_SIZE

typedef struct{
    unsigned int  len;
    unsigned char data[UART_DATA_LEN];
}uart_data_t;

/****************************** HCI TX & RX data FIFO allocation, End *********************************************/




#endif /* APP_BUFFER_H_ */
