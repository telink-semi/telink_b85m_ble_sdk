/********************************************************************************************************
 * @file	cis.h
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
#ifndef CIS_H_
#define CIS_H_


#include "algorithm/aes_ccm/aes_ccm.h"

/******************************* Macro & Enumeration & Structure Definition for Stack Begin, user can not use!!!!  *****/

//this macro can used by application layer
#define			BLT_CIS_HANDLE									BIT(5)  //CIS connection handle, BIT(5), 0x0020
#define			BLT_CIS_CONN_HANDLE								BLT_CIS_HANDLE

#define			BLT_CIS_IDX_MSK									0x0F  //15 most, though standard 31 max, 15 is enough in our SDK

#define 		CIS_ID_INVALID		              				0xFF


#define			CIS_FLOW_IDLE									0
#define			CIS_FLOW_SLAVE_REQ_HOST							BIT(0)
#define			CIS_FLOW_SLAVE_SEND_CIS_RSP						BIT(1)
#define			CIS_FLOW_SLAVE_REJECT_CIS_REQ					BIT(2)
#define			CIS_FLOW_SLAVE_WAIT_CIS_IND						BIT(3)



#define			CIS_FLOW_MASTER_START_NEW_CIS					BIT(0)
#define			CIS_FLOW_MASTER_SEND_CIS_REQ					BIT(1)
#define			CIS_FLOW_MASTER_SEND_CIS_IND					BIT(2)
#define			CIS_FLOW_MASTER_REJECT_CIS_RSP					BIT(3)


#define			CIS_FLOW_CIS_SYNC								BIT(5)
#define			CIS_FLOW_CIS_SYNC_SUCCESS						BIT(6)
#define			CIS_FLOW_CIS_SYNC_FAIL							BIT(7)




#define 		CIS_ROLE_MASTER              					1
#define 		CIS_ROLE_SLAVE               					0



#define 		TLK_T_MSS						 				480//300		//unit: uS  //TODO:test CIS Data, temporary modification 2020/06/13
#define 		TLK_TX_TRIG_OFFSET								60//50 //TODO: CSA#2 for subEvt requires more time, 50us may not be enough
#define 		TLK_TX_STL_OFFSET								120
#define 		TLK_TX_SEND_OFFSET								(TLK_TX_TRIG_OFFSET + TLK_TX_STL_OFFSET)
#define 		TLK_TM_DELAY									50



//CIS parameters
_attribute_aligned_(4)
typedef struct
{

// 0x00	 //
  	u8  	cis_connHandle;		/* Used to identify a CIS */
  	u8     	cis_masCigIndex_slvCigId;  /* for CIS master: Which CIG_ID the CIS belongs to; for slave: peer cig_id*/
  	u8		cisId;				//cisId is allocated by Host, 0x00 ~ 0xEF
  	u8		cis_occupied;		//indicate whether this CIS is used now, should clear when: 1.CIG remove; 2. ACL_conn terminate; 3.

  	u8		established;		//CIS is occupied and established, should allocate slot
  	u8		cis_tim_en;			// CIS slave timing enable, should allocate slot
  	u8		nse;
  	u8		link_acl_handle;	//link ACL_conn_hancle, associated ACL connection handle, for CIS master: 0x80/0x81...; for CIS slave 0x40,0x41....
  								//u8 is enough, due to our special design
  								//reason for not use link_acl_conn_idx: 0 has confusing meanings, one for master 0x80, one for data clear
  								//TODO, when CIS destroy, clear it. so acl_handle is used to judge whether a ACL connection is  associated
  	u8		cur_se_index;	//TODO: no need, use cisSubEventCnt
 	u8      cis_framed;		/* Framed indicates whether the CIS carries framed or unframed data */
 	u8		cis_receive_packet;
 	u8		cis_receive_new_packet;

 	u8		conn_successive_miss;
	u8 		conn_peer_terminate;
	u8 		conn_local_terminate;
	u8		cis_terminate_reason;


// 0x10	 //
	u8		conn_chn_hop;
	u8      ll_enc_busy;
	u8		connState;			 // 0/Conn_Complete/Conn_Establish
	u8		disconn_evt;

	u8		cisSubEventCnt;		//Internal sub-event accumulation, the first subeventcnt is 1, subevent <=nse.Need to be cleared before each CIG event is triggered
	u8      cisCurrPduAcked;    //CIS Data was ACKed in current subEvent
	u8      cis_cie;            //Close Isoc Event
	u8		cisConnChn;

	//CIS TX && RX buffer ctrl
	u8		isoPduTxFifoWptr;
	u8		isoPduTxFifoRptr;
	u8      cisPduNewData;
	u8      closeIsoEvent; 		/* 1 means close current CIS event */
						/// current RX pdu pointer ///
	void* 	pISOrxPdu;	//Rx irq handler will init it's value

	//for CIS flowctrl
	u8		local_sn;
	u8		local_nesn;
	u8      peer_lastSN;
	u8      cisPduCrcErr;

	volatile u64 curSendPldNum;  //When CIS is first established, it is initialized to 0, and it is used locally to record the currently sent CisPayloadNum. Every time a CIS Data PDU is sent or FT is incremented
	volatile u64 curRcvdPldNum;	 //When CIS is established, it is initialized to 0. It is used locally to record the currently received CisPayloadNum. Every time a CIS Data PDU is received or the FT is incremented
	                         /// L && F is used to determine the peer_CisPayloadNum corresponding to the received peer CIS data PDU ///
	u64     lastAckedPldNum; //L be the last PDU that you have acknowledged
	u64		lastPassFtPldNum;//F be the last PDU that has passed its flush point

	u8		cis_rx_num;
	u8		markLastPduType; //In the TX interrupt, mark whether the sent CIS data is a NULL packet
	bool	rdyToSentNullPkt;//Whether the data currently selected to be sent is a NULL packet: 1 NULL PDU, 0 Data PDU
	u8		cisRole; 		 //1:master CIS role; 0:Slave CIS role


// 0x20	 //
	// CSA#2 for subevent channel index
	u8		se_remapIdxOfLstUsedChn;
	u8		se_d;     //u8 d = max2(1, max2(min2(3, chnUsedNum -5), min2(11, (chnUsedNum-10)>>1)));
	u16     se_chnId; //equal to: (cisAccessAddr>>16) ^ (cisAccessAddr&0xffff);

	u8		se_idxOfLastUsedChn;
	u8		se_subEventIdx;
	u8		curCisPhy;
	u8		u8_rsvd5;

 	u8  	phy_m2s;		/* The transmitter PHY of packets from the master */
  	u8		phy_s2m;		/* The transmitter PHY of packets from the slave */
  	u8		bn_m2s;
  	u8		bn_s2m;

  	u8		rtn_m2s; 		/* only for CIS master: Maximum number of times every CIS Data PDU should be retransmitted from the master to slave */
  	u8  	rtn_s2m; 		/* only for CIS master: Maximum number of times every CIS Data PDU should be retransmitted from the slave to master */
    u8		ft_m2s; 			/* The flush timeout in multiples of ISO_Interval for each payload sent from the master to slave */
	u8		ft_s2m; 			/* The flush timeout in multiples of ISO_Interval for each payload sent from the slave to master */



// 0x30	 //
	u16		se_lastUsedprn;
	u16 	se_prnSubEvent_lu;
	u16 	se_prnSubEvent_se;
	u16		cisBeginConnEventCnt; //similar to instant


  	u16		max_sdu_m2s;	/* Maximum size, in octets, of the payload from the master  Host */
	u16		max_sdu_s2m;	/* Maximum size, in octets, of the payload from the slave  Host */
	u16		max_pdu_m2s;
	u16		max_pdu_s2m;


// 0x40	 //
	u32 	MPTM_T_IFS_MPTS;	//unit: uS
	u32     se_length_us;		/* SE_Length is the maximum length of a subevent, SE_Length = MPTM + T_IFS + MPTS + T_MSS */
//	u32		MPTm_tick;			/* MPTM and MPTS shall equal the time taken by the master and slave respectively to transmit a packet containing a CIS PDU with a payload of Max_PDU octets */
//	u32		MPTs_tick;      	/* MPTM and MPTS shall equal the time taken by the master and slave respectively to transmit a packet containing a CIS PDU with a payload of Max_PDU octets */


	u32 	sub_intvl_us;		/* Sub_Interval is the time between start of two consecutive subevents of a CIS*/
	u32 	sub_intvl_tick;
	u32     se_length_tick;

	u32     iso_intvl_tick;		/* Time between consecutive CIS anchor points */;


  	u32		sdu_int_m2s_tick;	/* The interval, in microseconds, of periodic SDUs */
  	u32		sdu_int_s2m_tick;	/* The interval, in microseconds, of periodic SDUs */
	u32		own_cisOffsetMin_us;
	u32		own_cisOffsetMax_us;
	u32		peer_cisOffsetMin_us;
	u32		peer_cisOffsetMax_us;
//	u32		cisOffsetMin_tick;	/* CIS_Offset_Min shall be set to the proposed minimum time, in microseconds, between the ACL anchor point of
//	                               the connection event with the connection event counter equal to connEventCount and the first CIS anchor point */
//	u32		cisOffsetMax_tick;

	u32		cig_sync_delay;
	u32		cis_sync_delay;

  	u32		cisAccessAddr;		/* AA shall be set to the Access Address of the CIS */

//  u32		cigSyncDly_tick;	/* Timing parameters (CIS_Sync_Delay and CIG_Sync_Delay)  from Master LL for sync ISO data at the application layer */
// 	u32		cisSyncDly_tick;	/* Timing parameters (CIS_Sync_Delay and CIG_Sync_Delay)  from Master LL for sync ISO data at the application layer */


	u32		cis_tick;
	u32		conn_access_code;
	u32		cis_timeout;



	u64		cisEventCnt;		/* TODO: u64? Both the master and slave shall have a 39-bit counter cisEventCounter */
	u64		cisPayloadNum;  	/* TODO: u64? Each CIS shall have a 39-bit cisPayloadNumber associated with it */

	// ISO link quality record (Ref Core5.2 | Vol 4,Part E, Page2741)
	u32		tx_unAckedPktsCntr;
	u32		tx_flushedPktsCntr;
	u32		tx_lastSubEvtPktsCntr;
	u32		retransmittedPktsCntr;
	u32		crcErrPktsCntr;
	u32		rxUnrcvedPktsCntr;
	u32		duplicatePktsCntr;

	// encryption concerned
	leCryptCtrl_t cisCryptCtrl; //for CIS encryption/decryption

} ll_cis_conn_t;
extern ll_cis_conn_t		*global_pCisConn;

extern ll_cis_conn_t		*blt_pCisConn;
extern int					blt_cis_sel;

extern rf_packet_ll_data_t  gCisNullPdu;
extern rf_packet_ll_data_t* pCurrCisPdu;

#define CIS_CONN_PARAM_LENGTH				(sizeof(ll_cis_conn_t))   //sizeof(ll_cis_conn_t) =  ,  must 4 byte aligned




#define CIG_SLOT_BUILD_MSK				BIT(7)
#define CIS_SLOT_BUILD_MSK				BIT(6)

#define SLOT_BUILD_IDX_MSK				0x0F

_attribute_aligned_(4)
typedef struct
{
    u8		maxNum_cig;
    u8		curNum_cig;
    u8 		maxNum_cisConn;
    u8		latest_cigId;

    u8 		maxNum_cisMaster;
    u8		curNum_cisMaster;
    u8 		maxNum_cisSlave;
    u8		curNum_cisSlave;

  	u8		cis_pending_cnt;
  	u8		cis_pending_msk;		   // mark which CIS is request by Host, pending now, CIS establish event is not generated
  	u8		ciss_1st_se;		//first sub_event for cis_salve
  	u8		cis_conn_sync; //not use


  	u32		cis_1st_anchor_evtCnt;

}ll_cis_mng_t;
extern ll_cis_mng_t		bltCisMng;



/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/






/******************************* Macro & Enumeration variables for User Begin ******************************************/


/******************************* Macro & Enumeration variables for User End ********************************************/







/******************************* Stack Interface Begin, user can not use!!! ********************************************/
void 	    blt_cis_pushRxEvtInfoToFifo(ll_cis_conn_t *pCisConn, rf_packet_ll_data_t* pIsoRxRawPkt);

int 		blt_ms_iso_procCisConnectionEvent(u16 cisHandle, ll_cis_conn_t *pCisConn);


int 	 	blt_cis_connect_common   (ll_cis_conn_t *pCisConn);
int 	 	blt_ll_cis_start_common_1   (ll_cis_conn_t *pCisConn);
u8* 		blt_ll_cis_prepare_data_common (ll_cis_conn_t *pCisConn);
int 	 	blt_ll_cis_start_common_2   (ll_cis_conn_t *pCisConn);
void 		blt_ll_cis_flush_timeout_jump (ll_cis_conn_t *pCisConn, u16 jumpCisEvtNum);
void 		blt_ll_cis_flush_timeout_common (ll_cis_conn_t *pCisConn);
ble_sts_t	blt_ll_cis_post_common   (ll_cis_conn_t *pCisConn);

ble_sts_t 	blt_cisgrp_post_common (void);

int 		irq_cis_rx(void);

//bool 		blt_ll_cis_pushTxfifo(u16 cis_connHandle, rf_cis_data_hdr_t cisPduHdr, u8* pIsoDataLoad, iso_cis_tx_pdu_para_t cisSeqNoInfo);
//bool 		blt_ll_cis_encryptPdu(u16 cis_connHandle, iso_tx_pdu_t *pdu);
/******************************* Stack Interface End *******************************************************************/






/******************************* User Interface  Begin *****************************************************************/
ble_sts_t 	blc_ll_initCisConnectionParameters( u8 *pCisConnPara, u32 master_cis_num, u32 slave_cis_num);


/******************************* User Interface  End  ******************************************************************/





#endif /* CIS_H_ */
