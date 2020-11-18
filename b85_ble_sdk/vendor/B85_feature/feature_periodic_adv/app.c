/********************************************************************************************************
 * @file     app.c
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     May. 22, 2019
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

#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "application/usbstd/usbkeycode.h"
#include "application/keyboard/keyboard.h"

#include "app_buffer.h"
#include "app_att.h"
#include "app_ui.h"
#include "app_config.h"

#if (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)


int	master_smp_pending = 0; 		// SMP: security & encryption;
int	master_sdp_pending = 0;			// SDP: service discovery

dev_char_info_t cur_master_conn_device;


const u8	tbl_advData[] = {
	 0x09, 0x09, 'T','L','K','_','M','4','S','3',
	 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
	 0x03, 0x19, 0x80, 0x01, 					// 384, Generic Remote Control, Generic category
	 0x05, 0x02, 0x12, 0x18, 0x0F, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
};

const u8	tbl_scanRsp [] = {
	 0x09, 0x09, 'T','L','K','_','M','4','S','3',
};





int app_controller_event_callback (u32 h, u8 *p, int n);
int app_host_event_callback (u32 h, u8 *para, int n);
int app_gatt_data_handler (u16 connHandle, u8 *pkt);





int app_le_adv_report_event_handle(u8 *p)
{
	event_adv_report_t *pa = (event_adv_report_t *)p;
	s8 rssi = pa->data[pa->len];


	//// Here user can use ADV report data to do a lot of work ////
#if 1   //@@@@@  just for debug, mac_address filter
		u8 filter_mac[3] = {0x33,0x33,0x33};
		if( memcmp(pa->mac +3, filter_mac, 3) ){  //not equal
			return 0;  //no connect
		}
#endif



	/*********************** Master Create connection demo: Key press or ADV pair packet triggers pair  ********************/
	if(master_smp_pending || master_sdp_pending){ 	 //if previous connection SMP & SDP not finish, can not create a new connection
		return 1;
	}
	if (master_disconnect_connhandle){ //one master connection is in un_pair disconnection flow, do not create a new one
		return 1;
	}

	int master_auto_connect = 0;
	int user_manual_paring = 0;

	//manual paring methods 1: key press triggers
	user_manual_paring = master_pairing_enable && (rssi > -56);  //button trigger pairing(RSSI threshold, short distance)


	#if (BLE_MASTER_SMP_ENABLE)
		master_auto_connect = blc_smp_searchBondingSlaveDevice_by_PeerMacAddress(pa->adr_type, pa->mac);
	#else
		//search in slave mac_address table to find whether this device is an old device which has already paired with master
		//master_auto_connect = user_tbl_slave_mac_search(pa->adr_type, pa->mac);
	#endif


	if(master_auto_connect || user_manual_paring){

		/* send create connection command to Controller, trigger it switch to initiating state. After this command, Controller
		 * will scan all the ADV packets it received but not report to host, to find the specified device(mac_adr_type & mac_adr),
		 * then send a "CONN_REQ" packet, enter to connection state and send a connection complete event
		 * (HCI_SUB_EVT_LE_CONNECTION_COMPLETE) to Host*/
			u8 status = blc_ll_createConnection( SCAN_INTERVAL_100MS, SCAN_WINDOW_100MS, INITIATE_FP_ADV_SPECIFY,  \
									 pa->adr_type, pa->mac, OWN_ADDRESS_PUBLIC, \
									 CONN_INTERVAL_31P25MS, CONN_INTERVAL_31P25MS, 0, CONN_TIMEOUT_4S, \
									 0, 0xFFFF);



		if(status == BLE_SUCCESS){ //create connection success
			#if (!BLE_MASTER_SMP_ENABLE)

			#endif
		}
	}
	/*********************** Master Create connection demo code end  *******************************************************/


	return 0;
}



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
			memset(&cur_master_conn_device, 0, sizeof(dev_char_info_t));

			//save current connect address type and address and conn_handle
			cur_master_conn_device.conn_handle = pCon->handle;
			cur_master_conn_device.peer_adrType = pCon->peer_adr_type;
			memcpy(cur_master_conn_device.peer_addr, pCon->mac, 6);

			#if (BLE_MASTER_SMP_ENABLE)
				master_smp_pending = pCon->handle; // this connection need SMP
			#else

			#endif
		}
	}

	return 0;
}





int 	app_disconnect_event_handle(u8 *p)
{
	event_disconnection_t	*pd = (event_disconnection_t *)p;

	//terminate reason
	if(pd->reason == HCI_ERR_CONN_TIMEOUT){  	//connection timeout

	}
	else if(pd->reason == HCI_ERR_REMOTE_USER_TERM_CONN){  	//peer device send terminate command on link layer

	}
	//master host disconnect( blm_ll_disconnect(current_connHandle, HCI_ERR_REMOTE_USER_TERM_CONN) )
	else if(pd->reason == HCI_ERR_CONN_TERM_BY_LOCAL_HOST){

	}
	else{

	}


	//if previous connection SMP & SDP not finished, clear flag
	if(master_smp_pending == pd->connHandle){
		master_smp_pending = 0;
	}
	if(master_sdp_pending == pd->connHandle){
		master_sdp_pending = 0;
	}

	if(master_disconnect_connhandle == pd->connHandle){  //un_pair disconnection flow finish, clear flag
		master_disconnect_connhandle = 0;
	}

	dev_char_info_delete_by_connhandle(pd->connHandle);


	return 0;
}



//////////////////////////////////////////////////////////
// event call back
//////////////////////////////////////////////////////////
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
				//after controller is set to initiating state by host (blc_ll_createConnection(...) )
				//it will scan the specified device(adr_type & mac), when find this adv packet, send a connection request packet to slave
				//and enter to connection state, send connection complete event. but notice that connection complete not
				//equals to connection establish. connection complete means that master controller set all the ble timing
				//get ready, but has not received any slave packet, if slave rf lost the connection request packet, it will
				//not send any packet to master controller

				app_le_connection_complete_event_handle(p);

			}
			//------hci le event: le connection establish event---------------------------------
			else if(subEvt_code == HCI_SUB_EVT_LE_CONNECTION_ESTABLISH)  //connection establish(telink private event)
			{
				//notice that: this connection event is defined by telink, not a standard ble controller event
				//after master controller send connection request packet to slave, when slave received this packet
				//and enter to connection state, send a ack packet within 6 connection event, master will send
				//connection establish event to host(HCI_SUB_EVT_LE_CONNECTION_ESTABLISH)

				//	blc_le_connection_establish_event_handle(p);
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

		}
		break;

		case GAP_EVT_SMP_CONN_ENCRYPTION_DONE:
		{

		}
		break;


		case GAP_EVT_SMP_SECURITY_PROCESS_DONE:
		{

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



#define			HID_HANDLE_CONSUME_REPORT			25
#define			HID_HANDLE_KEYBOARD_REPORT			29
#define			AUDIO_HANDLE_MIC					52
#define			OTA_HANDLE_DATA						48

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
				u16 attHandle = pAtt->handle0 | pAtt->handle1<<8;

				if(pAtt->opcode == ATT_OP_HANDLE_VALUE_NOTI)  //slave handle notify
				{
						//---------------	consumer key --------------------------
						if(attHandle == HID_HANDLE_CONSUME_REPORT)   //Demo device(825x_ble_sample) Consume Report AttHandle value is 25
						{
							u16 consumer_key = pAtt->dat[0] | pAtt->dat[1]<<8;


							#if (1 && UI_LED_ENABLE)	//Demo effect: when slave send Vol+/Vol- to master, LED GPIO toggle to show the result
								if(consumer_key == MKEY_VOL_UP){
									gpio_toggle(GPIO_LED_GREEN);
								}
								else if(consumer_key == MKEY_VOL_DN){
									gpio_toggle(GPIO_LED_BLUE);
								}
							#endif
						}
						//---------------	keyboard key --------------------------
						else if(attHandle == HID_HANDLE_KEYBOARD_REPORT)   // Demo device(825x_ble_sample) Key Report AttHandle value is 29
						{

						}
						else if(attHandle == AUDIO_HANDLE_MIC)   // Demo device(825x_ble_remote) Key Report AttHandle value is 52
						{

						}
						else
						{

						}
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








/**
 * @brief		user initialization when MCU power on or wake_up from deepSleep mode
 * @param[in]	none
 * @return      none
 */
void user_init_normal(void)
{
	/* random number generator must be initiated here( in the beginning of user_init_nromal).
	 * When deepSleep retention wakeUp, no need initialize again */
	random_generator_init();  //this is must




//////////////////////////// BLE stack Initialization  Begin //////////////////////////////////
	/* for 512K Flash, flash_sector_mac_address equals to 0x76000
	 * for 1M   Flash, flash_sector_mac_address equals to 0xFF000 */
	u8  mac_public[6];
	u8  mac_random_static[6];
	blc_initMacAddress(flash_sector_mac_address, mac_public, mac_random_static);


	//////////// Controller Initialization  Begin /////////////////////////
	blc_ll_initBasicMCU();

	blc_ll_initStandby_module(mac_public);						   //mandatory

    blc_ll_initLegacyAdvertising_module(); 	//adv module: 		 mandatory for BLE slave,

    blc_ll_initLegacyScanning_module(); 		    //scan module: 		 mandatory for BLE master

	blc_ll_initInitiating_module();			//initiate module: 	 mandatory for BLE master

	blc_ll_initAclConnection_module();
	blc_ll_initAclMasterRole_module();
	blc_ll_initAclSlaveRole_module();



	blc_ll_setMaxConnectionNumber( MASTER_MAX_NUM, SLAVE_MAX_NUM);

	blc_ll_setAclMasterConnectionInterval(CONN_INTERVAL_30MS);
	//////////// Controller Initialization  End /////////////////////////




	//////////// HCI Initialization  Begin /////////////////////////
	blc_hci_registerControllerDataHandler (blc_l2cap_pktHandler);

	blc_hci_registerControllerEventHandler(app_controller_event_callback); //controller hci event to host all processed in this func

	/* bluetooth event */
	blc_hci_setEventMask_cmd (HCI_EVT_MASK_DISCONNECTION_COMPLETE);

	/* bluetooth low energy(LE) event */
	blc_hci_le_setEventMask_cmd(		HCI_LE_EVT_MASK_CONNECTION_COMPLETE  \
									|	HCI_LE_EVT_MASK_ADVERTISING_REPORT \
									|   HCI_LE_EVT_MASK_CONNECTION_UPDATE_COMPLETE \
									|   HCI_LE_EVT_MASK_CONNECTION_ESTABLISH);  //connection establish: telink private event   TODO: delete this cause we will support standard HCI
	//////////// HCI Initialization  End /////////////////////////



	//////////// Host Initialization  Begin /////////////////////////
	/* Host Initialization */
	/* GAP initialization must be done before any other host feature initialization !!! */
	blc_gap_init();

	/* L2CAP Initialization */
	blc_l2cap_initAclConnMasterMtuBuffer(mtu_m_rx_fifo, MTU_M_BUFF_SIZE_MAX, 0,0);
	blc_l2cap_initAclConnSlaveMtuBuffer(mtu_s_rx_fifo, MTU_S_BUFF_SIZE_MAX, mtu_s_tx_fifo, MTU_S_BUFF_SIZE_MAX);

	/* GATT Initialization */
	my_gatt_init();
	blc_gatt_register_data_handler(app_gatt_data_handler);

	blc_att_setSlaveRxMTUSize(200);

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
		//user_master_host_pairing_management_init(); 		//TeLink referenced paring&bonding without standard paring in BLE Spec
	#endif

	blc_smp_smpParamInit();


	/* Host (GAP/SMP/GATT/ATT) event process: register host event callback and set event mask */
	blc_gap_registerHostEventHandler( app_host_event_callback );
	blc_gap_setEventMask( GAP_EVT_MASK_SMP_PAIRING_BEAGIN 			|  \
						  GAP_EVT_MASK_SMP_PAIRING_SUCCESS   		|  \
						  GAP_EVT_MASK_SMP_PAIRING_FAIL				|  \
						  GAP_EVT_MASK_SMP_SECURITY_PROCESS_DONE);
	//////////// Host Initialization  End /////////////////////////

//////////////////////////// BLE stack Initialization  End //////////////////////////////////



	#if 0
		blc_ll_setScanParameter(SCAN_TYPE_PASSIVE, SCAN_INTERVAL_100MS, SCAN_INTERVAL_100MS, OWN_ADDRESS_PUBLIC, SCAN_FP_ALLOW_ADV_ANY);
		blc_ll_setScanEnable (BLC_SCAN_ENABLE, DUP_FILTER_DISABLE);
	#endif




	#if (MCU_CORE_TYPE == MCU_CORE_825x)
		rf_set_power_level_index (RF_POWER_P3p01dBm);
	#else
		rf_set_power_level_index (RF_POWER_P3p50dBm);
	#endif



	#if ( PERD_ADV_MODE == SINGLE_PERD_ADV )

		extern void app_single_periodic_adv_set_test(void);
		app_single_periodic_adv_set_test();


	#elif( PERD_ADV_MODE == MULTI_PERD_ADV )

		extern void app_multiple_periodic_adv_set_test(void);
		app_single_periodic_adv_set_test();

	#endif





}


/**
 * @brief		user initialization when MCU wake_up from deepSleep_retention mode
 * @param[in]	none
 * @return      none
 */
void user_init_deepRetn(void)
{

}






/////////////////////////////////////////////////////////////////////
// main loop flow
/////////////////////////////////////////////////////////////////////
int main_loop (void)
{

	////////////////////////////////////// BLE entry /////////////////////////////////
	blc_sdk_main_loop();



	////////////////////////////////////// UI entry /////////////////////////////////
	#if (UI_KEYBOARD_ENABLE)
		proc_keyboard (0,0, 0);
	#endif


	proc_master_role_unpair();



	return 0;
}










#endif // of of (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
