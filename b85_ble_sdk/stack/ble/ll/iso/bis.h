/********************************************************************************************************
 * @file	bis.h
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
#ifndef BIS_H_
#define BIS_H_

#if (LL_FEATURE_ENABLE_CONNECTIONLESS_ISO)

#include "stack/ble/ble.h"
#include "stack/ble/hci/hci_cmd.h" // if removed here,it'll will cause a compiler err.
#include "stack/ble/ble_format.h"
#include "iso_stack.h"



/******************************* Macro & Enumeration & Structure Definition for Stack Begin, user can not use!!!!  *****/
extern ll_big_mng_t		big_mng;
extern ll_big_para_t		*gloabl_pBig;
extern ll_big_para_t		*blt_pBig;
extern ll_big_para_t		*latest_pBigPara; // last used BIG parameter pointer
extern ll_bis_t		*global_pBis ;



/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/






/******************************* Macro & Enumeration variables for User Begin ******************************************/
//BIG parameters
typedef struct
{
  	u8  	big_handle;			/* Used to identify the BIG */
	u8		adv_handle;			/* Used to identify the periodic advertising train */
	u8		num_bis;			/* Total number of BISes in the BIG */
  	u8  	sdu_intvl[3];		/* The interval, in microseconds, of periodic SDUs */
  	u16		max_sdu;			/* Maximum size of an SDU, in octets */
  	u16		max_trans_lat; 		/* Maximum time, in milliseconds, for transmitting an SDU */
  	u8  	rtn; 				/* The maximum number of times that every BIS Data PDU should be retransmitted */
  	u8		phy;				/* The transmitter PHY of packets */
	packing_type_t		packing;//type same as u8
	framing_t	    	framing;//type same as u8
	u8		enc;				/* Encryption flag */
	u8      broadcast_code[16]; /* The code used to derive the session key that is used to encrypt and decrypt BIS payloads */
} ll_createBigParams_t;

//BIG parameters test
typedef struct
{
  	u8  	big_handle;			/* Used to identify the BIG */
	u8		adv_handle;			/* Used to identify the periodic advertising train */
	u8		num_bis;			/* Total number of BISes in the BIG */
  	u8  	sdu_intvl[3];		/* The interval, in microseconds, of periodic SDUs */
  	u16     iso_intvl;			/* The time between consecutive BIG anchor points */
  	u8		nse;				/* The total number of subevents in each interval of each BIS in the BIG */
  	u16		max_sdu;			/* Maximum size of an SDU, in octets */
  	u16		max_pdu; 			/* Maximum size, in octets, of payload */
  	u8		phy;				/* The transmitter PHY of packets */
	packing_type_t		packing;//type same as u8
	framing_t	    	framing;//type same as u8
	u8		bn;					/* The number of new payloads in each interval for each BIS */
	u8		irc;				/* The number of times the scheduled payload(s) are transmitted in a given event*/
	u8		pto;				/* Offset used for pre-transmissions */
	u8		enc;				/* Encryption flag */
	u8      broadcast_code[16]; /* The code used to derive the session key that is used to encrypt and decrypt BIS payloads */
} ll_createBigParamsTest_t;

//BIG create sync parameters
typedef struct
{
  	u8  	big_handle;			/* Used to identify the BIG */
	u16		sync_handle;		/* Identifier of the periodic advertising train */
	u8		enc;				/* Encryption flag */
	u8      broadcast_code[16]; /* The code used to derive the session key that is used to encrypt and decrypt BIS payloads */
	u8		mse;				/* The Controller can schedule reception of any number of subevents up to NSE */
  	u16		big_sync_timeout;	/* Synchronization timeout for the BIG */
  	u16		max_trans_lat; 		/* Maximum time, in milliseconds, for transmitting an SDU */
  	u8  	num_bis; 			/* Total number of BISes to synchronize */
  	u8*     bis;				/* List of indices of BISes */
} ll_bigCreateSyncParams_t;



/******************************* Macro & Enumeration variables for User End ********************************************/







/******************************* Stack Interface Begin, user can not use!!! ********************************************/
ble_sts_t 	blc_hci_le_createBigParams(hci_le_createBigParams_t* pCmdParam);
ble_sts_t 	blc_hci_le_createBigParamsTest(hci_le_createBigParamsTest_t* pCmdParam);
ble_sts_t 	blc_hci_le_terminateBig(hci_le_terminateBigParams_t* pCmdParam);
ble_sts_t 	blc_hci_le_bigCreateSync(hci_le_bigCreateSyncParams_t* pCmdParam);
ble_sts_t 	blc_hci_le_bigTerminateSync(u8 bigHandle, u8* pRetParam);

u32 blt_ll_bis_getAccessCode(u32 seedAccessCode, u8 bisSeq);
u32 blt_ll_bis_getSeedAccessAddr(void);


/******************************* Stack Interface End *******************************************************************/






/******************************* User Interface  Begin *****************************************************************/
ble_sts_t 	blc_ll_createBigParams(ll_createBigParams_t setCigParams);
ble_sts_t 	blc_ll_createBigParamsTest(ll_createBigParamsTest_t setCigParamsTst);
ble_sts_t 	blc_ll_terminateBig(u8 bigHandle, u8 reason);
ble_sts_t 	blc_ll_bigCreateSync(ll_bigCreateSyncParams_t setBigCreateSyncParams);
ble_sts_t 	blc_ll_bigTerminateSync(u8 bigHandle);


/******************************* User Interface  End  ******************************************************************/




#endif

#endif /* BIS_H_ */
