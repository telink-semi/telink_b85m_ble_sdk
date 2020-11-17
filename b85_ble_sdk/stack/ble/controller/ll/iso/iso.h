/********************************************************************************************************
 * @file	iso.h
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
#ifndef ISO_H_
#define ISO_H_


#if (LL_FEATURE_ENABLE_ISO)



/******************************* Macro & Enumeration & Structure Definition for Stack Begin, user can not use!!!!  *****/

////////////////////////////// ISO TX Data Buffer Init ////////////////////////////////////////////

typedef struct{
//	u64		ft_cisEventCnt;		/* 39-bit cisEventCounter: FT_E = E + FT -1, cisPayloadNumber  [E*BN, (E+1)*BN-1] */
//	u32		ft_cisSubEvtNum;	/* FT_U = NSE C floor (NSE  BN)  (BN C 1 C cisPayloadNumber mod BN) */
	u64 	payloadNumber;
	u64		eventCnt;
}iso_tx_pdu_para_t;

typedef	struct {
//	u64		ft_cisEventCnt;		/* 39-bit cisEventCounter: FT_E = E + FT -1, cisPayloadNumber  [E*BN, (E+1)*BN-1] */
	u64 	payloadNumber;
	u64		eventCnt;

//	u32		ft_cisSubEvtNum;	/* FT_U = NSE C floor (NSE  BN)  (BN C 1 C cisPayloadNumber mod BN) */

	u16		offset;
	u16 	RFU;
	rf_packet_ll_data_t isoTxPdu;
}iso_tx_pdu_t;

typedef	struct {
	u16		fifo_size;
	u8		fifo_num;
	u8		iso_num;
	iso_tx_pdu_t* iso_tx_pdu;
}iso_tx_pdu_fifo_t;


#define		ISO_PDU_TXFIFO_INIT(name,fifo_size,fifo_num,iso_num)		u8 name##_b[DATA_LENGTH_ALLIGN4((ISO_PDU_SIZE_ALLIGN16(fifo_size) + sizeof(iso_tx_pdu_t) - sizeof(rf_packet_ll_data_t)))*fifo_num*iso_num]={0}; iso_tx_pdu_fifo_t name = {ISO_PDU_SIZE_ALLIGN16(fifo_size),fifo_num,iso_num, (iso_tx_pdu_t*)name##_b}


iso_tx_pdu_fifo_t	bltIsoPduTxfifo;
u8					bltIsoPduTxfifo_b[];


iso_tx_pdu_fifo_t	bltIsoBisPduTxfifo;
u8 					bltIsoBisPduTxfifo_b[];

////////////////////////////// ISO CIS RX Data Buffer Init ////////////////////////////////////////////
typedef	struct {
	u64 	curRcvdPldNum;	//The cisPayloadNum corresponding to the received CIS Data PDU.
	u64		rcvdPldCisEventCnt;
	u32		rcvdPldCisAnchorTick;	//Calculate the corresponding CIS reference anchor value according to the received peer CisPayloadNum.
	u32     rxFlushedFlg;	//Passed it's Flush Point
	rf_packet_ll_data_t isoRxPdu;
}iso_rx_pdu_t;

typedef	struct {
	u32		fifo_size;
	u16		fifo_num;
	u8		wptr;
	u8		rptr;
	iso_rx_pdu_t* iso_rx_pdu;
}iso_rx_pdu_fifo_t;

#define		ISO_PDU_RXFIFO_INIT(name,fifo_size,fifo_num)		u8 name##_b[DATA_LENGTH_ALLIGN4((ISO_PDU_SIZE_ALLIGN16(fifo_size) + sizeof(iso_rx_pdu_t) - sizeof(rf_packet_ll_data_t)))*fifo_num]={0}; iso_rx_pdu_fifo_t name = {ISO_PDU_SIZE_ALLIGN16(fifo_size),fifo_num, 0, 0, (iso_rx_pdu_t*)name##_b}

iso_rx_pdu_fifo_t	bltIsoPduRxfifo;
u8					bltIsoPduRxfifo_b[];


////////////////////////////// ISO BIS RX Data Buffer Init ////////////////////////////////////////////
typedef	struct {
	u64 	bisPayloadCnt;	//bisPayloadcounter
	u32		rcvdPldbisAnchorTick;	//Calculate the corresponding CIS reference anchor value according to the received peer CisPayloadNum.
	rf_packet_ll_data_t isoRxPdu;
}iso_bis_rx_pdu_t;

typedef	struct {
	u32		fifo_size;
	u16		fifo_num;
	u8		wptr;
	u8		rptr;
	iso_bis_rx_pdu_t* bis_rx_pdu;
}iso_bis_rx_pdu_fifo_t;

#define		BIS_PDU_RXFIFO_INIT(name,fifo_size,fifo_num)		u8 name##_b[ISO_BIS_RX_PDU_SIZE_ALLIGN16(fifo_size) *fifo_num]={0}; iso_rx_pdu_fifo_t name = {ISO_BIS_RX_PDU_SIZE_ALLIGN16(fifo_size),fifo_num, 0, 0, (iso_rx_pdu_t*)name##_b}

iso_bis_rx_pdu_fifo_t	bltIsoBisPduRxfifo;
u8					    bltIsoBisPduRxfifo_b[];





////////////////////////////// ISO RX event Init ////////////////////////////////////////////
u8 					bltIsoRxEvt_b[];
my_fifo_t 			bltIsoRxEvt;

typedef	struct {
	u64					 	curRcvdPldNum;      //The cisPayloadNum corresponding to the received CIS Data PDU.
	rf_packet_ll_data_t* 	pCurrIsoRxPdu;      //ISO RX PDU buffer address
	u32	    				idealPldAnchorTick; //Calculate the corresponding CIS reference anchor value according to the received peer CisPayloadNum.
	u16	    				handle;          //Current CIS connection handle
	u8						payloadLen;		//The length indicates the size of the CIS Payload and MIC, if included.
	u8						rsvd;               //align
}iso_rx_evt_t;


/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/






/******************************* Macro & Enumeration variables for User Begin ******************************************/



/******************************* Macro & Enumeration variables for User End ********************************************/







/******************************* Stack Interface Begin, user can not use!!! ********************************************/
ble_sts_t  blc_hci_le_read_iso_tx_sync_cmd(u16 iso_connHandle, u8 *pData);


/******************************* Stack Interface End *******************************************************************/






/******************************* User Interface  Begin *****************************************************************/



/******************************* User Interface  End  ******************************************************************/


#endif


#endif /* ISO_H_ */
