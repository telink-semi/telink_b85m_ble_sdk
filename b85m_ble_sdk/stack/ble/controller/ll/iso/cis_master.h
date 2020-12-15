/********************************************************************************************************
 * @file	cis_master.h
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
#ifndef CIS_MASTER_H_
#define CIS_MASTER_H_

#if (LL_FEATURE_ENABLE_CONNECTED_ISOCHRONOUS_STREAM_MASTER)
//ISO interval shall be a multiple of 1.25mS in the range of 5ms to 4S

#define 		CIG_FIFONUM 									16  //16*5 = 80mS

//	CIG parameters
_attribute_aligned_(4)
typedef struct
{
// 0x00	 //
	u8		cig_index;
  	u8  	cigId;					/* Used to identify the CIG */
  	u8		cig_test_cmd;           // 1 for "LE Set CIG Parameters Test command", FT/Iso_interval/NSE[i]/Max_PDU[i]/BN[i] set by Host
  									// 0 for "LE Set CIG Parameters command", FT/Iso_interval/NSE[i]/Max_PDU[i]/BN[i] set by Controller
  	u8		cig_valid;				// mark if used now, should set and clear in CIG set and remove


  	u8		cis_alloc_count;		// CIS allocate count
  	u8		cis_estab_cnt;			// CIS establish count
  	u8		cis_alloc_msk;			// mark which CIS allocate for current CIG, support 8 CIS max with "u8"
  	u8		cis_estab_msk;			// mark which CIS established			  , support 8 CIS max with "u8"

  	u8		first_cis_flag;   // 0: first CIS
	u8		sca;		/* Slaves_Clock_Accuracy */   //type same as u8
	u8		cis_packing;			// 'cis' but not 'cig'
	u8	    cig_framed;

	u8      cis_total_se_num;   //The cumulative number of cis arrangement mapping tables from the beginning of the idx0 to the last valid se (se may belong to different cis)
	u8      cis_se_en_num;
	u8      cis_arrgmt_next_idx;//Starting idx of cis arrangement mappings
	u8      cis_se_skip;		//If the part of the mapping table that is initially checked is invalid, it will skip to find the next valid CIS.




// 0x10	 //
	u8		ft_m2s; 					/* The flush timeout in multiples of ISO_Interval for each payload sent from the master to slave */
	u8		ft_s2m; 					/* The flush timeout in multiples of ISO_Interval for each payload sent from the slave to master */
	u8		u8_rsvd1;
	u8		u8_rsvd2;

	u16		iso_interval;
  	u16 	max_trans_lat_m2s;		/* Maximum time, in milliseconds, for an SDU to be transported from the master Controller to slave Controller */
  	u16 	max_trans_lat_s2m;		/* Maximum time, in milliseconds, for an SDU to be transported from the slave Controller to master Controller */

  	u16		bSlot_duration_cig;		// u8 is enough
  	u16		sSlot_duration_cig;		// u8 is enough
  	u16		bSlot_interval_cig;      // u16 can handle max 4S




// 0x20	 //
	u32     cis_arrgmt_map_msk; //Which idx are valid in the cis arrangement mapping table
  	u32		cig_sync_delay;	  // unit: uS ? //TODO
	u32		sdu_int_m2s;			/* The interval, in microseconds, of periodic SDUs */
	u32		sdu_int_s2m;			/* The interval, in microseconds, of periodic SDUs */


// 0x30	 //
  	u32		bSlot_first_anchor;		// u8 is enough
	u32 	bSlot_mark_cig;
	u32 	slot_tick_cig;


	u8		u8_rsvd22;
	u8		u8_rsvd33;
	u8		cigTsk_wptr;
	u8		cigTsk_rptr;

	//Attention: if not 4B aligned, task scheduler will collapse. SO variable must 4B aligned above !!!
	sch_task_t	cigTsk_fifo[CIG_FIFONUM];


// 0x40	 //
  	u32		cis_sync_delay[LL_CIS_IN_CIG_NUM_MAX];  //TODO: maybe not need
	u8		cis_alloc_tbl[LL_CIS_IN_CIG_NUM_MAX];	//mark which CIS used for CIG, it's ordered
	u8		cis_order_tbl[LL_CIS_IN_CIG_NUM_MAX];
	u8		cis_arrgmt_map[LL_SE_IN_CIG_NUM_MAX]; //mark cis arrangement (according to the cis_idx)
} ll_cig_para_t;

extern ll_cig_para_t		*global_pCigPara;
extern ll_cig_para_t		*latest_pCigPara;


extern ll_cig_para_t		*blt_pCig;
extern int					blt_cig_sel;


#define CIG_PARAM_LENGTH				(sizeof(ll_cig_para_t))   //sizeof(ll_cig_para_t) =  ,  must 4 byte aligned



extern u32	ctx_start_tick;


/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/





/******************************* Stack Interface Begin, user can not use!!! ********************************************/


int 		blt_ll_searchExistingCigId(u8 cur_cigId);
int			blt_ll_AllocateNewCigId(u8 cur_cigId);
int	 		blt_ll_searchAvailableCig(u8 cur_cigId);


int 		blt_ctx_start (void);
int 		blt_ctx_post (void);
int			blt_cig_start(void);


int 		blt_ll_cis_master_cis_establish(st_llms_conn_t *pConn, ll_cis_conn_t * cur_pCisConn, ble_sts_t status);

bool		blt_ll_sendCisReq(st_llms_conn_t *pConn, u8 acl_conn_idx);
bool		blt_ll_sendCisInd(st_llms_conn_t *pConn, u8 acl_conn_idx);
bool		blt_ll_rejectCisRsp(st_llms_conn_t *pConn, u8 acl_conn_idx);


int 		blt_ll_cis_master_mainloop(void);
ble_sts_t 	blt_ll_cis_master_control_pdu_process(st_llms_conn_t* pConn, u16 acl_connHandle, u8 opcode, u8 *pLlCtrlPkt);
int 		blt_ll_cis_master_terminate_check(void);



int 		blt_ll_find_next_cis_subevent (int start_idx);
/******************************* Stack Interface End *******************************************************************/





















/******************************* Macro & Enumeration variables for User Begin ******************************************/

#define 		CIG_ID_0		              					0
#define 		CIG_ID_1		              					1
#define 		CIG_ID_2		              					2
#define 		CIG_ID_3		              					3
#define 		CIG_ID_INVALID		              				0xFF







// CIS parameters Test
typedef struct
{
	u8  	cis_id;			/* Used to identify a CIS */
	u8		nse; 			/* Maximum number of subevents in each CIS event */
	u16		max_sdu_m2s;	/* Maximum size, in octets, of the payload from the masters Host */
	u16		max_sdu_s2m;	/* Maximum size, in octets, of the payload from the slaves Host */
	u16		max_pdu_m2s;	/* Maximum size, in octets, of the payload from master Link Layer to slave Link Layer*/
	u16		max_pdu_s2m;	/* Maximum size, in octets, of the payload from master Link Layer to master Link Layer*/
  	u8  	phy_m2s;		/* The transmitter PHY of packets from the master */
  	u8		phy_s2m;		/* The transmitter PHY of packets from the slave */
  	u8  	bn_m2s;			/* BN > 0: The burst number for master to slave transmission */
  	u8		bn_s2m;			/* BN > 0: The burst number for slave to master transmission */
}ll_CisParamsTest_t;

// CIG parameters Test
typedef struct
{
	u8		cig_id;             		/* Used to identify the CIG */
	u8		sdu_int_m2s[3];				/* The interval, in microseconds, of periodic SDUs */
  	u8		sdu_int_s2m[3];				/* The interval, in microseconds, of periodic SDUs */
	u8		ft_m2s; 					/* The flush timeout in multiples of ISO_Interval for each payload sent from the master to slave */
	u8		ft_s2m; 					/* The flush timeout in multiples of ISO_Interval for each payload sent from the slave to master */
	u16 	iso_intvl;					/* Time between consecutive CIS anchor points */
	slv_clk_accuracy_t	sca;			/* Slaves_Clock_Accuracy */   //type same as u8
	packing_type_t	packing;			//type same as u8
	framing_t		framing;			//type same as u8
  	u8		cis_count;					/* Total number of CISes in the CIG being added or modified */
  	ll_CisParamsTest_t*	pCisParamTst;	/* CIS parameters test */
}ll_CigParamsTest_t;


// CIS create CIS parameters
typedef struct
{
	u16		cis_handle;                    /* List of connection handles of CISes */
	u16		acl_handle;                    /* List of connection handles of ACLs */
} ll_CreateCisParams_t;


typedef struct
{
	u8	cigId;
	u8	cisId;
	u8  phyM2S;
	u8	phyS2M;

	u32 maxSduM2S :12;
	u32 rfu0 	  :3;
	u32 framed    :1;
	u32 maxSduS2M :12;
	u32 rfu1      :4;

	u8 sduIntvlM2S[3]; //SDU_Interval_M_To_S(20 bits) + RFU(4 bits)
	u8 sduIntvlS2M[3]; //SDU_Interval_S_To_M(20 bits) + RFU(4 bits)

	u16 maxPduM2S;
	u16 maxPduS2M;
	u8	nse;
	u8	subIntvl[3];

	u8 	bnM2S:4;
	u8 	bnS2M:4;
	u8 	ftM2S;
	u8 	ftS2M;
	u16	isoIntvl;

	u8	cisOffsetMin[3];
	u8	cisOffsetMax[3];
	u16	connEventCnt; //similar to instant
}ll_cisReqParams_t;



/******************************* Macro & Enumeration variables for User End ********************************************/


























/**
 * @brief      for user to initialize CIS master module.
 * @param	   none
 * @return     none
 */
void 		blc_ll_initCisMaster_module(void);






/**
 * @brief
 * @param	   none
 * @return     none
 */
void 		blc_ll_initCisMasterParameters( u8 *pCigPara, int cig_num);




ble_sts_t 	blc_hci_le_setCigParams	   (hci_le_setCigParam_cmdParam_t* pCmdParam, 		hci_le_setCigParam_retParam_t* pRetParam);



ble_sts_t 	blc_hci_le_setCigParamsTest(hci_le_setCigParamTest_cmdParam_t* pCmdParam, 	hci_le_setCigParam_retParam_t* pRetParam);


ble_sts_t 	blc_hci_le_removeCig(u8 cigId, u8* pRetParamm);


ble_sts_t 	blc_hci_le_createCis(hci_le_CreateCisParams_t* pCisPara);



#endif


#endif /* CIS_MASTER_H_ */
