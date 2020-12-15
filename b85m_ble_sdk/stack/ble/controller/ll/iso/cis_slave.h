/********************************************************************************************************
 * @file	cis_slave.h
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
#ifndef CIS_SLAVE_H_
#define CIS_SLAVE_H_

#if (LL_FEATURE_ENABLE_CONNECTED_ISOCHRONOUS_STREAM_SLAVE)


/******************************* Macro & Enumeration & Structure Definition for Stack Begin, user can not use!!!!  *****/
#define		CIS_REQ_ACCEPT_TIMEOUT		4000000 //TODO: 4s timeout unit:us



/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/












/******************************* Macro & Enumeration variables for User Begin ******************************************/
#define 		CIS_SLAVE_FIFONUM 								16  //16*5mS(minimum) = 80mS



//#define			CRX_EARLY_SET_TICK
#define			CRX_EARLY_SET_SSLOT_NUM_MAX	   						7

//#define			CRX_HALF_MARGIN_TICK
#define			CRX_HALF_MARGIN_SSLOT_NUM_MAX		   				3




#define SCHE_MODE_SUCCESSIVE									0
#define SCHE_MODE_SEPARATED										1

_attribute_aligned_(4)
typedef struct {
	u8		acl_slave_idx;
	u8		sche_mode;
	u8		crx_early_set_sSlot_num;
	u8		crx_half_margin_sSlot_num;

	s8		ciss_sSlotOft;  //CIS slave sSlot_offset
	u8		get_rx_timestamp;
	u8		u8_rsvd1;
	u8		u8_rsvd2;

	u16		ciss_isoIntvl;           //unit: 1.25mS
	u16 	ciss_bSlotInterval;
	u16 	ciss_sSlotInterval;		 //65536*20uS = 1.3S, slave interval can not exceed this value
  	u16		ciss_sSlotDuration;		// u8 is enough
  	u16		idle_interval_us;
  	u16		cisOffset_us;


    u32		cisOffset_tick;		/* CIS_Offset shall be set to the time, in microseconds */
	u32		cis_expect_time;
	u32		cis_anchor_point;
//	u32		cis_arrive_time;
//	u32		cissTick_1st_rx;
	u32 	cis_tolerance_time;

	u32		conn_duration;

	u32		cissTick_rx;
	s32		sSlot_mark_ciss;
	u32		bSlot_mark_ciss;

	u8		u8_rsvd22;
	u8		u8_rsvd33;
	u8		schTsk_wptr;
	u8		schTsk_rptr;


	//Attention: if not 4B aligned, task scheduler will collapse. SO variable must 4B aligned above !!!
	sch_task_t	schTsk_fifo[CIS_SLAVE_FIFONUM];

}ll_cis_slv_t;

#define CIS_SLAVE_PARAM_LENGTH				(sizeof(ll_cis_slv_t))   //sizeof(ll_cis_slv_t) =  ,  must 4 byte aligned


extern ll_cis_slv_t *blt_pCisSlave;
/******************************* Macro & Enumeration variables for User End ********************************************/







/******************************* Stack Interface Begin, user can not use!!! ********************************************/
ble_sts_t   blt_llCisReqParamsChk(st_llms_conn_t* pc, rf_packet_ll_cis_req_t* pLlCisReq);

int 		blt_ll_cis_slave_terminate_check(void);

int 		blt_ll_cis_slave_cis_establish(st_llms_conn_t *pConn, ll_cis_conn_t * cur_pCisConn, ll_cis_slv_t * cur_pCisSlv, ble_sts_t status);

bool		blt_ll_sendCisRsp(st_llms_conn_t *pConn, u8 acl_conn_idx);
bool		blt_ll_rejectCisReq(st_llms_conn_t *pConn, u8 acl_conn_idx);

int 		blt_ll_cis_slave_mainloop(void);
ble_sts_t 	blt_ll_cis_slave_control_pdu_process(st_llms_conn_t* pConn, u16 acl_connHandle, u8 opcode, u8 *pLlCtrlPkt);




int 		blt_crx_start (void);
int 		blt_crx_post (void);
/******************************* Stack Interface End *******************************************************************/






/******************************* User Interface  Begin *****************************************************************/







/**
 * @brief      for user to initialize CIS slave module.
 * @param	   none
 * @return     none
 */
void 		blc_ll_initCisSlave_module(void);



/**
 * @brief
 * @param
 * @param
 * @return     ble_sts_t
 */
ble_sts_t 	blc_ll_initCisSlaveParameters( u8 *pCisSlavePara, int cis_slave_num);






ble_sts_t 	blc_hci_le_acceptCisReq(u16 cisHandle);
ble_sts_t 	blc_hci_le_rejectCisReq(u16 cisHandle, u8 reason, u8* pRetParam);


/******************************* User Interface  End  ******************************************************************/



#endif


#endif /* CIS_MASTER_H_ */
