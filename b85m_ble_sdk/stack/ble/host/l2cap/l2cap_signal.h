/********************************************************************************************************
 * @file	l2cap_signal.h
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
#ifndef L2CAP_COC_H_
#define L2CAP_COC_H_




typedef int blc_l2cap_server_cb(u16 connHandle, u8 *p, u8*arg);
typedef int blc_l2cap_rx_cb(void *arg);

/******************************* Macro & Enumeration & Structure Definition for Stack Begin, user can not use!!!!  *****/
#define MAX_NUM_SUPPORT_L2CAP_CHNL					16
#define SLAVE_MAX_NUM_L2CAP_SERVICE					4
#define MAX_NUM_CHANNEL_ENDPOINT_PER_SERVICE		5


#define L2CAP_LE_CID_START		0X0040
#define L2CAP_LE_CID_END		0X007F

#define L2CAP_COC_MIN_MTU		(64)
#define L2CAP_COC_MIN_MPS		(64)


typedef enum{
	CHNL_UNUSED	= 0,
	CHNL_ALLCOATED,
	CHNL_CONN_PENDING,
	CHNL_CONN_ESTABLISH,
}l2cap_chnl_state_t;

typedef struct{

	l2cap_chnl_state_t state;
	u8 scid;
	u8 dcid;
	u8 rsvd;

	void * arg; //l2cap_chnl_t

	//todo align 4
	u8 sdu[1];//sud buff point
}l2cap_endpoint_t;

typedef struct{

	u8  valid;
	u8  rsvd1;
	u16 rsvd2;

	u16 psm;
	u16 my_mtu;		//minimum 64

	u16 my_mps; 		//minimum 64
	u16 my_credit;

	blc_l2cap_server_cb *cb;
	void *cb_arg;
}l2cap_service_t;

typedef struct{
	l2cap_chnl_state_t st; // 0: idle 1: connect pending 2: establish
	u8  identifier;
	u8  num_ed;  // channel endpoint in this channel
	u8 	rsvd;

	u16 connHandle;
	u16 peer_mtu;		// peer device mtu
	u16 peer_mps;
	u16 peer_credits;

	u16 psm;
	u16 my_mtu;		//minimum 64
	u16 my_mps; 		//minimum 64
	u16 my_credit;

	blc_l2cap_server_cb *cb;
	void *cb_arg;

	l2cap_endpoint_t *ed[MAX_NUM_CHANNEL_ENDPOINT_PER_SERVICE]; //channel endpoint

}l2cap_chnl_t;

typedef struct
{
	u8 id;
	u16 mtu;
	u16 mps;
	u16 dcid[MAX_NUM_CHANNEL_ENDPOINT_PER_SERVICE];

}l2cap_reconfigure_t;




#define L2CAP_CHANL_LENGTH		(sizeof(l2cap_chnl_t))

typedef struct
{
	u8 maxNum_ed; //maximum endpoint support
	u8 useNum_ed; // used already enpoint
	u16 maxMTU_ed;;

	u8 maxNum_chnl;
	u8 useNum_chnl;

}l2cap_channel_endpoint_mng_t;
/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/


/******************************* Macro & Enumeration variables & Structure for User Begin ******************************/

/******************************* Macro & Enumeration variables & Structure for User End ********************************/





/******************************* Stack Interface Begin, user can not use!!! ********************************************/
u8 * blt_signal_l2capCmdHandler(u16 connHandle, u8 * p);
u8 blt_l2cap_GetSignal_id(void);
l2cap_service_t *bls_l2cap_coc_FindService(u16 psm);
l2cap_chnl_t* blt_l2cap_chnl_allcoate(u16 connHandle);
l2cap_chnl_t* blc_l2cap_FindChannel_by_psm(u16 connHandle, u16 psm);
l2cap_endpoint_t *blt_l2cap_endpoint_allocate(void);
ble_sts_t blt_l2cap_RemoveEndpoint(l2cap_endpoint_t *endpoint);
ble_sts_t blt_l2cap_RemoveChannel(l2cap_chnl_t * chnl);
l2cap_endpoint_t *blt_l2cap_FindEndPoint_by_dcid(u16 connHandle, u16 dcid);
l2cap_endpoint_t *blt_l2cap_FindEndPoint_by_scid(u16 connHandle, u16 scid);
/******************************* Stack Interface End *******************************************************************/




/******************************* User Interface  Begin *****************************************************************/
// allocate endpoint buffer
void blc_l2cap_coc_InitChnlEndpointParameter(u8 *pEndpointBuff, u16 buff_size, u8 num_max_ed);

/*
 * user should register this service firstly to allocate resource,when receive l2cap_conn_req, device
 * can response this request according this registered service
 */
ble_sts_t blc_l2cap_coc_RegisterService(u16 psm, u16 mtu, blc_l2cap_server_cb *cb, void* cb_arg);


ble_sts_t blc_l2cap_CreditBasedReconfigureReq(u16 connHandle,u16 mtu,u16 mps, u8 num, u16 *endpoint);

ble_sts_t blc_l2cap_CreditBasedConnectionReq(u16 connHandle,u16 psm, u16 mtu, blc_l2cap_server_cb *cb, void* cb_arg,u8 chnl_num);
/******************************* User Interface  End  ******************************************************************/




#endif /* L2CAP_COC_H_ */
