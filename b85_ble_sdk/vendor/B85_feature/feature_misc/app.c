/********************************************************************************************************
 * @file	app.c
 *
 * @brief	This is the source file for BLE SDK
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
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "app_config.h"
#include "app.h"
#include "app_buffer.h"
#include "app_att.h"

#include "application/keyboard/keyboard.h"
#include "application/usbstd/usbkeycode.h"

#if (FEATURE_TEST_MODE == TEST_MISC_FUNC)




#define TEST_L2CAP_CONN_PARAM_UPDATE                    1
#define TEST_CSA2										2


#define MISC_FUNC_TEST_MODE								TEST_CSA2






int	master_smp_pending = 0; 		// SMP: security & encryption;
int	master_sdp_pending = 0;			// SDP: service discovery

int	master_pairing_enable = 0;
int master_unpair_enable = 0;
int master_disconnect_connhandle;   //mark the master connection which is in un_pair disconnection flow
int master_auto_connect = 0;
int user_manual_pairing;






const u8	tbl_advData[] = {
	 0x09, 0x09, 'B','8','5','_','M','i','s','c',
	 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
	 0x03, 0x19, 0x80, 0x01, 					// 384, Generic Remote Control, Generic category
	 0x05, 0x02, 0x12, 0x18, 0x0F, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
};

const u8	tbl_scanRsp [] = {
	0x09, 0x09, 'B','8','5','_','M','i','s','c',
};



/**
 * @brief      BLE Adv report event handler
 * @param[in]  p         Pointer point to event parameter buffer.
 * @return
 */
int app_le_adv_report_event_handle(u8 *p)
{
	event_adv_report_t *pa = (event_adv_report_t *)p;
	s8 rssi = pa->data[pa->len];


	/*********************** Master Create connection demo: Key press or ADV pair packet triggers pair  ********************/
	if(master_smp_pending || master_sdp_pending){ 	 //if previous connection SMP & SDP not finish, can not create a new connection
		return 1;
	}
	if (master_disconnect_connhandle){ //one master connection is in un_pair disconnection flow, do not create a new one
		return 1;
	}

	int master_auto_connect = 0;
	int user_manual_pairing = 0;

	//manual pairing methods 1: key press triggers
	user_manual_pairing = master_pairing_enable && (rssi > -66);  //button trigger pairing(RSSI threshold, short distance)

	#if (BLE_MASTER_SMP_ENABLE)
		master_auto_connect = blc_smp_searchBondingSlaveDevice_by_PeerMacAddress(pa->adr_type, pa->mac);
	#else

	#endif


	if(master_auto_connect || user_manual_pairing){


		/* send create connection command to Controller, trigger it switch to initiating state. After this command, Controller
		 * will scan all the ADV packets it received but not report to host, to find the specified device(mac_adr_type & mac_adr),
		 * then send a "CONN_REQ" packet, enter to connection state and send a connection complete event
		 * (HCI_SUB_EVT_LE_CONNECTION_COMPLETE) to Host*/
		blc_ll_createConnection( SCAN_INTERVAL_100MS, SCAN_WINDOW_100MS, INITIATE_FP_ADV_SPECIFY,  \
								 pa->adr_type, pa->mac, OWN_ADDRESS_PUBLIC, \
								 CONN_INTERVAL_31P25MS, CONN_INTERVAL_31P25MS, 0, CONN_TIMEOUT_2S, \
								 0, 0xFFFF);
	}
	/*********************** Master Create connection demo code end  *******************************************************/


	return 0;
}


/**
 * @brief      BLE Connection complete event handler
 * @param[in]  p         Pointer point to event parameter buffer.
 * @return
 */
int app_le_connection_complete_event_handle(u8 *p)
{
	event_connection_complete_t *pCon = (event_connection_complete_t *)p;

	if(pCon->status == BLE_SUCCESS){

		dev_char_info_t cur_conn_device;
		memset(&cur_conn_device, 0, sizeof(dev_char_info_t));

		//save current connect address type and address and conn_handle
		cur_conn_device.conn_handle = pCon->handle;
		cur_conn_device.peer_adrType = pCon->peer_adr_type;
		memcpy(cur_conn_device.peer_addr, pCon->mac, 6);


		dev_char_info_insert( &cur_conn_device );


		if( pCon->handle & BLM_CONN_HANDLE ) // master connection handle, process SMP and SDP
		{
			#if (BLE_MASTER_SMP_ENABLE)
				master_smp_pending = pCon->handle; // this connection need SMP
			#else

			#endif
		}
	}

	return 0;
}



/**
 * @brief      BLE Disonnection event handler
 * @param[in]  p         Pointer point to event parameter buffer.
 * @return
 */
int 	app_disconnect_event_handle(u8 *p)
{
	event_disconnection_t	*pCon = (event_disconnection_t *)p;

	//terminate reason
	if(pCon->reason == HCI_ERR_CONN_TIMEOUT){  	//connection timeout

	}
	else if(pCon->reason == HCI_ERR_REMOTE_USER_TERM_CONN){  	//peer device send terminate command on link layer

	}
	//master host disconnect( blm_ll_disconnect(current_connHandle, HCI_ERR_REMOTE_USER_TERM_CONN) )
	else if(pCon->reason == HCI_ERR_CONN_TERM_BY_LOCAL_HOST){

	}
	else{

	}



	//if previous connection SMP & SDP not finished, clear flag
#if (BLE_MASTER_SMP_ENABLE)
	if(master_smp_pending == pCon->connHandle){
		master_smp_pending = 0;
	}
#endif

	if(master_disconnect_connhandle == pCon->connHandle){  //un_pair disconnection flow finish, clear flag
		master_disconnect_connhandle = 0;
	}

	dev_char_info_delete_by_connhandle(pCon->connHandle);




	return 0;
}



//////////////////////////////////////////////////////////
// event call back
//////////////////////////////////////////////////////////
/**
 * @brief      BLE controller event handler call-back.
 * @param[in]  h       event type
 * @param[in]  p       Pointer point to event parameter buffer.
 * @param[in]  n       the length of event parameter.
 * @return
 */
int app_controller_event_callback (u32 h, u8 *p, int n)
{
	if (h &HCI_FLAG_EVENT_BT_STD)		//Controller HCI event
	{
		u8 evtCode = h & 0xff;

		//------------ disconnect -------------------------------------
		if(evtCode == HCI_EVT_DISCONNECTION_COMPLETE)  //connection terminate
		{
			app_disconnect_event_handle(p);
		}
		else if(evtCode == HCI_EVT_LE_META)  //LE Event
		{
			u8 subEvt_code = p[0];

			//------hci le event: le connection complete event---------------------------------
			if (subEvt_code == HCI_SUB_EVT_LE_CONNECTION_COMPLETE)	// connection complete
			{
				app_le_connection_complete_event_handle(p);
			}
			//--------hci le event: le adv report event ----------------------------------------
			else if (subEvt_code == HCI_SUB_EVT_LE_ADVERTISING_REPORT)	// ADV packet
			{
				//after controller is set to scan state, it will report all the adv packet it received by this event

				app_le_adv_report_event_handle(p);
			}
			//------hci le event: le connection update complete event-------------------------------
			else if (subEvt_code == HCI_SUB_EVT_LE_CONNECTION_UPDATE_COMPLETE)	// connection update
			{

			}
		}
	}


	return 0;

}




/**
 * @brief      BLE host event handler call-back.
 * @param[in]  h       event type
 * @param[in]  para    Pointer point to event parameter buffer.
 * @param[in]  n       the length of event parameter.
 * @return
 */
int app_host_event_callback (u32 h, u8 *para, int n)
{
	u8 event = h & 0xFF;

	switch(event)
	{
		case GAP_EVT_SMP_PAIRING_BEAGIN:
		{
		}
		break;

		case GAP_EVT_SMP_PAIRING_SUCCESS:
		{
		}
		break;

		case GAP_EVT_SMP_PAIRING_FAIL:
		{
		#if (BLE_MASTER_SMP_ENABLE)
			gap_smp_pairingFailEvt_t *p = (gap_smp_pairingFailEvt_t *)para;

			if( p->connHandle & BLM_CONN_HANDLE){  //master connection
				if(master_smp_pending == p->connHandle){
					master_smp_pending = 0;
				}
			}
		#endif
		}
		break;

		case GAP_EVT_SMP_CONN_ENCRYPTION_DONE:
		{

		}
		break;

		case GAP_EVT_SMP_SECURITY_PROCESS_DONE:
		{
		#if (BLE_MASTER_SMP_ENABLE)
			gap_smp_connEncDoneEvt_t* p = (gap_smp_connEncDoneEvt_t*)para;

			if( p->connHandle & BLM_CONN_HANDLE){  //master connection

				if(master_smp_pending == p->connHandle){
					master_smp_pending = 0;
				}

			}
		#endif
		}
		break;
		case GAP_EVT_ATT_EXCHANGE_MTU:
		{

		}
		break;

		case GAP_EVT_GATT_HANDLE_VLAUE_CONFIRM:
		{

		}
		break;

		default:
		break;
	}

	return 0;
}



/**
 * @brief      BLE GATT data handler call-back.
 * @param[in]  connHandle     connection handle.
 * @param[in]  pkt             Pointer point to data packet buffer.
 * @return
 */
int app_gatt_data_handler (u16 connHandle, u8 *pkt)
{

	if( connHandle & BLM_CONN_HANDLE)   //GATT data for Master
	{
			//so any ATT data before service discovery will be dropped
			dev_char_info_t* dev_info = dev_char_info_search_by_connhandle (connHandle);
			if(dev_info)
			{
				//-------	user process ------------------------------------------------
				rf_packet_att_t *pAtt = (rf_packet_att_t*)pkt;
				//u16 attHandle = pAtt->handle0 | pAtt->handle1<<8;

				if(pAtt->opcode == ATT_OP_HANDLE_VALUE_NOTI)  //slave handle notify
				{

				}
				else if (pAtt->opcode == ATT_OP_HANDLE_VALUE_IND)
				{

				}
			}

	}
	else{   //GATT data for Slave


	}


	return 0;
}


















///////////////////////////////////////////

/**
 * @brief		user initialization when MCU power on or wake_up from deepSleep mode
 * @param[in]	none
 * @return      none
 */
void user_init_normal(void)
{
	/* random number generator must be initiated here( in the beginning of user_init_nromal).
	 * When deepSleep retention wakeUp, no need initialize again */
	random_generator_init();

//////////////////////////// BLE stack Initialization  Begin //////////////////////////////////

	/* for 512K Flash, flash_sector_mac_address equals to 0x76000
	 * for 1M   Flash, flash_sector_mac_address equals to 0xFF000 */
	u8  mac_public[6];
	u8  mac_random_static[6];
	blc_initMacAddress(flash_sector_mac_address, mac_public, mac_random_static);


	// Fifo initialization function should be called before  blc_ll_initAclConnection_module()
	/* all ACL connection share same RX FIFO */
	if(blc_ll_initAclConnRxFifo(app_acl_rxfifo, ACL_RX_FIFO_SIZE, ACL_RX_FIFO_NUM) != BLE_SUCCESS)	{  	while(1); 	}
	/* ACL Master TX FIFO */
	if(blc_ll_initAclConnMasterTxFifo(app_acl_mstTxfifo, ACL_MASTER_TX_FIFO_SIZE, ACL_MASTER_TX_FIFO_NUM, MASTER_MAX_NUM) != BLE_SUCCESS) { while(1); }
	/* ACL Slave TX FIFO */
	if(blc_ll_initAclConnSlaveTxFifo(app_acl_slvTxfifo, ACL_SLAVE_TX_FIFO_SIZE, ACL_SLAVE_TX_FIFO_NUM, SLAVE_MAX_NUM) != BLE_SUCCESS)	{ while(1); }



	//////////// Controller Initialization  Begin /////////////////////////
	blc_ll_initBasicMCU();

	blc_ll_initStandby_module(mac_public);						   //mandatory

    blc_ll_initLegacyAdvertising_module(); 	//adv module: 		 mandatory for BLE slave,

    blc_ll_initLegacyScanning_module(); 	//scan module: 		 mandatory for BLE master

	blc_ll_initInitiating_module();			//initiate module: 	 mandatory for BLE master

	blc_ll_initAclConnection_module();
	blc_ll_initAclMasterRole_module();
	blc_ll_initAclSlaveRole_module();



	blc_ll_setMaxConnectionNumber( MASTER_MAX_NUM, SLAVE_MAX_NUM);

	blc_ll_setAclMasterConnectionInterval(CONN_INTERVAL_31P25MS);

	#if (MISC_FUNC_TEST_MODE == TEST_CSA2)
		blc_ll_initChannelSelectionAlgorithm_2_feature();
	#endif

	#if (MCU_CORE_TYPE == MCU_CORE_825x)
		rf_set_power_level_index (RF_POWER_P3p01dBm);
	#else
		rf_set_power_level_index (RF_POWER_P3p50dBm);
	#endif

	//////////// Controller Initialization  End /////////////////////////



	//////////// HCI Initialization  Begin /////////////////////////
	blc_hci_registerControllerDataHandler (blc_l2cap_pktHandler);

	blc_hci_registerControllerEventHandler(app_controller_event_callback); //controller hci event to host all processed in this func

	//bluetooth event
	blc_hci_setEventMask_cmd (HCI_EVT_MASK_DISCONNECTION_COMPLETE);

	//bluetooth low energy(LE) event
	blc_hci_le_setEventMask_cmd(		HCI_LE_EVT_MASK_CONNECTION_COMPLETE  \
									|	HCI_LE_EVT_MASK_ADVERTISING_REPORT \
									|   HCI_LE_EVT_MASK_CONNECTION_UPDATE_COMPLETE);

	//////////// HCI Initialization  End /////////////////////////


	//////////// Host Initialization  Begin /////////////////////////
	/* Host Initialization */
	/* GAP initialization must be done before any other host feature initialization !!! */
	blc_gap_init();

	/* L2CAP Initialization */
	blc_l2cap_initAclConnMasterMtuBuffer(mtu_m_rx_fifo, MTU_M_BUFF_SIZE_MAX, 			0,					 0);
	blc_l2cap_initAclConnSlaveMtuBuffer(mtu_s_rx_fifo, MTU_S_BUFF_SIZE_MAX, mtu_s_tx_fifo, MTU_S_BUFF_SIZE_MAX);

	/* GATT Initialization */
	my_gatt_init();
	blc_gatt_register_data_handler(app_gatt_data_handler);

	/* SMP Initialization */
	#if (BLE_SLAVE_SMP_ENABLE)  //Slave SMP Enable
		blc_smp_setSecurityLevel_slave(Unauthenticated_Pairing_with_Encryption);  //LE_Security_Mode_1_Level_2
	#else
		blc_smp_setSecurityLevel_slave(No_Security);
	#endif

	#if (BLE_MASTER_SMP_ENABLE) //Master SMP Enable
		blc_smp_setSecurityLevel_master(Unauthenticated_Pairing_with_Encryption);  //LE_Security_Mode_1_Level_2
	#else
		blc_smp_setSecurityLevel_master(No_Security);
	#endif

	blc_smp_smpParamInit();


	//host(GAP/SMP/GATT/ATT) event process: register host event callback and set event mask
	blc_gap_registerHostEventHandler( app_host_event_callback );
	blc_gap_setEventMask( GAP_EVT_MASK_SMP_PAIRING_BEAGIN 			|  \
						  GAP_EVT_MASK_SMP_PAIRING_SUCCESS   		|  \
						  GAP_EVT_MASK_SMP_PAIRING_FAIL				|  \
						  GAP_EVT_MASK_SMP_SECURITY_PROCESS_DONE);
	//////////// Host Initialization  End /////////////////////////

//////////////////////////// BLE stack Initialization  End //////////////////////////////////



//////////////////////////// User Configuration for BLE application ////////////////////////////
	blc_ll_setAdvData( (u8 *)tbl_advData, sizeof(tbl_advData) );
	blc_ll_setScanRspData( (u8 *)tbl_scanRsp, sizeof(tbl_scanRsp));
	blc_ll_setAdvParam(ADV_INTERVAL_30MS, ADV_INTERVAL_30MS, ADV_TYPE_CONNECTABLE_UNDIRECTED, OWN_ADDRESS_PUBLIC, 0, NULL, BLT_ENABLE_ADV_ALL, ADV_FP_NONE);
	blc_ll_setAdvEnable(1);  //ADV enable

	blc_ll_setScanParameter(SCAN_TYPE_PASSIVE, SCAN_INTERVAL_100MS, SCAN_INTERVAL_100MS, OWN_ADDRESS_PUBLIC, SCAN_FP_ALLOW_ADV_ANY);
	blc_ll_setScanEnable (BLC_SCAN_ENABLE, DUP_FILTER_DISABLE);
}




/**
 * @brief		user initialization when MCU wake_up from deepSleep_retention mode
 * @param[in]	none
 * @return      none
 */
void user_init_deepRetn(void)
{

}



#if (UI_KEYBOARD_ENABLE)

extern kb_data_t kb_event;
_attribute_data_retention_	int 	key_not_released;


#define CONSUMER_KEY   	   			1
#define KEYBOARD_KEY   	   			2
#define PAIR_UNPAIR_KEY   	   		3

_attribute_data_retention_	u8 		key_type;

/**
 * @brief   Check changed key value.
 * @param   none.
 * @return  none.
 */
void key_change_proc(void)
{

	u8 key0 = kb_event.keycode[0];
//	u8 key_buf[8] = {0,0,0,0,0,0,0,0};

	key_not_released = 1;
	if (kb_event.cnt == 2)   //two key press
	{

	}
	else if(kb_event.cnt == 1)
	{
		if(key0 >= CR_VOL_UP )  //volume up/down
		{

		}
		else{
			key_type = PAIR_UNPAIR_KEY;

			if(key0 == BTN_PAIR)   //Manual pair triggered by Key Press
			{
				master_pairing_enable = 1;
			}
			else if(key0 == BTN_UNPAIR) //Manual un_pair triggered by Key Press
			{

			}

		}

	}
	else   //kb_event.cnt == 0,  key release
	{
		key_not_released = 0;
		if(key_type == CONSUMER_KEY)
		{

		}
		else if(key_type == KEYBOARD_KEY)
		{

		}
		else if(key_type == PAIR_UNPAIR_KEY){
			if(master_pairing_enable){
				master_pairing_enable = 0;
			}
		}
	}


}



_attribute_data_retention_		static u32 keyScanTick = 0;

/**
 * @brief      keyboard task handler
 * @param[in]  e    - event type
 * @param[in]  p    - Pointer point to event parameter.
 * @param[in]  n    - the length of event parameter.
 * @return     none.
 */
void proc_keyboard (u8 e, u8 *p, int n)
{
	if(clock_time_exceed(keyScanTick, 10 * 1000)){  //keyScan interval: 10mS
		keyScanTick = clock_time();
	}
	else{
		return;
	}

	kb_event.keycode[0] = 0;
	int det_key = kb_scan_key (0, 1);

	if (det_key){
		key_change_proc();
	}

}




#endif   //end of UI_KEYBOARD_ENABLE













/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////

/**
 * @brief     BLE main loop
 * @param[in]  none.
 * @return     none.
 */
int main_idle_loop (void)
{

	////////////////////////////////////// BLE entry /////////////////////////////////
	blc_sdk_main_loop();


	////////////////////////////////////// UI entry /////////////////////////////////
	#if (UI_KEYBOARD_ENABLE)
		proc_keyboard (0,0, 0);
	#endif

#if (MISC_FUNC_TEST_MODE == TEST_L2CAP_CONN_PARAM_UPDATE)

#elif (MISC_FUNC_TEST_MODE == TEST_CSA2)

#else

#endif


	return 0; //must return 0 due to SDP flow
}



void main_loop (void)
{
	main_idle_loop ();
}

#endif



