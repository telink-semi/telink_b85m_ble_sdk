/********************************************************************************************************
 * @file     bqb_ll.h
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     Sep. 18, 2018
 *
 * @par      Copyright (c) Telink Semiconductor (Shanghai) Co., Ltd.
 *           All rights reserved.
 *
 *			 The information contained herein is confidential and proprietary property of Telink
 * 		     Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *			 of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *			 Co., Ltd. and the licensee in separate contract or the terms described here-in.
 *           This heading MUST NOT be removed from this file.
 *
 * 			 Licensees are granted free, non-transferable use of the information in this
 *			 file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#ifndef BQB_LL_H_
#define BQB_LL_H_




// <<LL.TS.p17.pdf>> Page 836
#define			BQB_DFT_SDU_Interval_M_To_S						20000
#define			BQB_DFT_SDU_Interval_S_To_M						20000
#define			BQB_DFT_ISO_Interval							ISO_INTERVAL_20MS
#define			BQB_DFT_CIS_Count								1
#define			BQB_DFT_Slaves_Clock_Accuracy					0
#define			BQB_DFT_Packing									PACK_SEQUENTIAL
#define			BQB_DFT_Framing									UNFRAMED
#define			BQB_DFT_NSE										3
#define			BQB_DFT_Max_SDU_M_To_S
#define			BQB_DFT_Max_SDU_S_To_M
/* Note 1: Set to the maximum SDU size as defined by the bandwidth requirements specified in [17] Section 2.1
   for unframed PDUs and Section 2.2 for framed PDUs, or MAX SDU Length defined in IXIT, whichever is smaller. */
#define			BQB_DFT_Max_PDU_M_To_S							251
#define			BQB_DFT_Max_PDU_M_To_S							251
#define			BQB_DFT_PHY_M_To_S								PHY_PREFER_1M
#define			BQB_DFT_PHY_S_To_M								PHY_PREFER_1M
#define			BQB_DFT_FT_M_To_S								1
#define			BQB_DFT_FT_S_To_M								1
#define			BQB_DFT_BN_M_To_S								1
#define			BQB_DFT_BN_S_To_M								1
#define			BQB_DFT_Transport_Latency_M_To_S					//40mS
#define			BQB_DFT_Transport_Latency_S_To_M					//40mS
#define			BQB_DFT_RTN_M_To_S								3
#define			BQB_DFT_RTN_S_To_M								3






typedef enum {


	TP_STATUS_ACL_CONN_PKT_MAX = 0,
	TP_STATUS_CIS_CONN_PKT_MAX,










	TP_STATUS_CONN_UNKNOWN_RSP,

	TP_STATUS_CONNECTION_DATA_SEND,


	TP_STATUS_ADV_PKT_MAX		,
	TP_STATUS_CONN_ESTABLISH	,
	TP_STATUS_CONN_TERMINATE				,

	TP_STATUS_CONN_PARA_REQ					,
	TP_STATUS_CONN_PARA_UPDATE				,

	TP_STATUS_CONNECTION_TIMEOUT			,
	TP_STATUS_CONNE_RCVD_L2CAP_DATA			,

	TP_STATUS_CONN_MAP_REQ					,
	TP_STATUS_CONN_MAP_UPDATE				,
	TP_STATUS_CONN_DATA_LENGTH_EXCHANGE		,

	TP_STATUS_CONN_BRX_MISS_END				,

	TP_STATUS_L2CAP_DATA_IN_IRQ_RX			,

	TP_STATUS_TERMINATE_IN_IRQ_RX			,
	TP_STATUS_BRX_START						,
	TP_STATUS_RECV_CERT_DATA				,
	TP_STATUS_PUSH_DATA_CRC_ERR				,
	TP_STATUS_PUSH_DATA_SN_ERR				,
	TP_STATUS_CONN_IN_IRQ_RX				,
	TP_STATUS_BRX_POST						,
	TP_STATUS_BRX_TX						,


	TP_STATUS_SCAN_HIT_MAX					,
	TP_STATUS_SCAN_RCVD_RSP					,
	TP_STATUS_SCAN_REQ_SENT					,
	TP_STATUS_CONN_HIT_MAX					,

	TP_STATUS_CONN_RCVD_DAT					,
	TP_STATUS_CONN_REQ_SENT					,
	TP_STATUS_TIMEOUT						,
	TP_STATUS_CONNECTION_LOST				,
	TP_STATUS_CONN_PKT_MISSING				,
	TP_STATUS_CONNECTION_RETX_MAX			,

	 TP_STATUS_RCVD_NO_EMPTY_PKT			,
	 TP_STATUS_CHN_MAP_FULL_USED			,


	TP_STATUS_CONN_PHY_UPDATE       		,

	TP_STATUS_CONNECTION_FEATURE_REQ		,

	TP_STATUS_CONN_BTX_MIDDLE				,








	TP_STATUS_HCI_EVT_DISCONNECT = 0x80,
	TP_STATUS_HCI_EVT_CONNECTION_COMPLETE,
	TP_EVT_NUM_OF_COMPLETE_PACKETS,
	TP_STATUS_HCI_EVT_LE_ADV_REPORT,
	TP_STATUS_HCI_EVT_LE_CONNECTION_UPDATE_COMPLETE,
	TP_STATUS_HCI_EVT_LE_READ_REMOTE_USED_FEATURES_COMPLET,
	TP_STATUS_HCI_EVT_LE_LONG_TERM_KEY_REQUESTED,
	TP_STATUS_HCI_EVT_LE_REMOTE_CONNECTION_PARAM_REQUEST,
	TP_STATUS_HCI_EVT_LE_DATA_LENGTH_CHANGE,
	TP_STATUS_HCI_EVT_LE_READ_LOCAL_P256_KEY_COMPLETE,
	TP_STATUS_HCI_EVT_LE_GENERATE_DHKEY_COMPLETE,
	TP_STATUS_HCI_EVT_LE_ENHANCED_CONNECTION_COMPLETE,
	//...
	TP_STATUS_HCI_EVT_LE_PHY_UPDATE_COMPLETE,

	TP_STATUS_HCI_EVT_LE_EXTENDED_ADVERTISING_REPORT,
	TP_STATUS_HCI_EVT_LE_ADVERTISING_SET_TERMINATED ,

	TP_STATUS_HCI_EVT_LE_CIS_ESTABLISHED,
	TP_STATUS_HCI_EVT_LE_CIS_REQUESTED,
	TP_STATUS_HCI_EVT_LE_CREATE_BIG_COMPLETE,
	TP_STATUS_HCI_EVT_LE_BIG_SYNC_ESTABLILSHED,
	TP_STATUS_HCI_EVT_LE_BIG_SYNC_LOST,
	TP_EVT_UNKNOWN_PACKETS,
	TP_HCI_EVT_RET_CHECK,



	TP_STATUS_INIT = 0x8000,
} tp_status_t;


















typedef int (*callback_testcase_t)(int, void*);






typedef struct {

	u16	 	testAclConnEvent_cnt;
	u16 	testAclConnEvent_numMax;

	u16 	testCisConnEvent_cnt;
	u16 	testCisConnEvent_numMax;

	bool    testAclConnPktMaxEnFlg;
	bool    testCisConnPktMaxEnFlg;



} st_bqb_ll_t;

extern st_bqb_ll_t		bltBQB;

extern u64				bqbIrqEvt_mask;






void tp_set_acl_conn_event_max(u16 m);
void tp_set_cis_conn_event_max(u16 m);










void test_case_function_register (char * testcase, callback_testcase_t func);
int  exe_lower_tester_command (u8 *cmd);


void blc_bqb_ll_main_loop(void);















void 	tp_set_adv_pkt_max (u16 m);
void 	tp_enable_advData_inrease(u8 en, s8 step);

void 	tp_AdvAddress_companyId_exchange(void);
void 	tp_AdvAddress_companyAssignId_exchange(void);
void 	tp_AdvAddress_companyId_companyAssignId_mismatch(void);
//void 	tp_ScanRspAddress_companyId_exchange(void);
//void 		tp_ScanRspAddress_companyAssignId_exchange(void);
//void tp_ScanRspAddress_companyId_companyAssignId_mismatch(void);


void 	tp_enable_adv_scanRsp_Bad_CRC (u8 advBadCrc, u8 scanRspBadCrc );

void 	tp_set_conn_pkt_max (u32 m);

void	tp_flip_access_address (int n);
void	tp_set_test_data (u8 type, u8 len, u8 d, int pkts);
void	tp_set_manual_timeout (u32 timeout);
void 	tp_disable_more_data(u8 disable);
void 	tp_enbale_print_rcvd_data_connect(u8 en);
void 	tp_enbale_rcvd_l2cap_data_callback(u8 en);
void 	tp_disable_data_len_exchange(u8 en);
void 	tp_set_brx_missing_time(u32 time_ms);
void 	tp_set_brx_missing_delay_intervals(int interval_num);
void 	tp_enable_conn_pkt_Bad_CRC (u8 connBadCrc );



void 	tp_set_adv_pkt_max (u16 m);
void 	tp_disable_more_data(u8 disable);
void 	tp_set_conn_pkt_max(u32 m);
void 	tp_phy_req_col(u8 en);
void 	tp_phy_req_skip(u8 en);
void 	tp_phy_req_nochange(u8 en);
void 	tp_phy_no_common(u8 en);
void 	tp_set_test_data (u8 type, u8 len, u8 d, int pkts);
void 	tp_enbale_rcvd_l2cap_data_callback(u8 en);




void 	tp_set_test_pkt(u8 num);
void 	tp_SetPhyUpdate_Same(u8 en);
void 	tp_set_PhyUpdate_InsInPast(u8 en);
void 	tp_set_PhyReq_TO(u8 en);
void 	tp_set_DiffProc_ChnMap(u8 en);
void 	tp_set_DiffProc_ConUp(u8 en);
void 	tp_setRecv_no(u8 num);
void 	tp_set_PhyInd_TO(u8 en);
void 	tp_set_NoPhyReqChan(u8 en);
void 	tp_set_NoPhyRspChan(u8 en);





#endif /* LL_BQB_H_ */
