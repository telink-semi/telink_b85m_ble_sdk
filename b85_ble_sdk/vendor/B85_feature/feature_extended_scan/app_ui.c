/********************************************************************************************************
 * @file	 app_ui.c
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

#include "app_buffer.h"
#include "app_ui.h"


#include "application/keyboard/keyboard.h"
#include "application/usbstd/usbkeycode.h"


#if (FEATURE_TEST_MODE == TEST_EXTENDED_SCAN)


int	master_pairing_enable = 0;
int master_unpair_enable = 0;

int master_disconnect_connhandle;   //mark the master connection which is in un_pair disconnection flow




int master_auto_connect = 0;
int user_manual_paring;
















#if (UI_KEYBOARD_ENABLE)

_attribute_data_retention_	int 	key_not_released;


#define CONSUMER_KEY   	   			1
#define KEYBOARD_KEY   	   			2
#define PAIR_UNPAIR_KEY   	   		3

_attribute_data_retention_	u8 		key_type;

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
			key_type = CONSUMER_KEY;
			u16 consumer_key;
			if(key0 == CR_VOL_UP){  	//volume up
				consumer_key = MKEY_VOL_UP;
			}
			else if(key0 == CR_VOL_DN){ //volume down
				consumer_key = MKEY_VOL_DN;
			}

		}
		else{
			key_type = PAIR_UNPAIR_KEY;

			if(key0 == BTN_PAIR)   //Manual pair triggered by Key Press
			{
				master_pairing_enable = 1;
			}
			else if(key0 == BTN_UNPAIR) //Manual un_pair triggered by Key Press
			{
				/*Here is just Telink Demonstration effect. Cause the demo board has limited key to use, only one "un_pair" key is
				 available. When "un_pair" key pressed, we will choose and un_pair one device in connection state */
				if(conn_master_num){ //at least 1 master connection exist

					if(!master_disconnect_connhandle){  //if one master un_pair disconnection flow not finish, here new un_pair not accepted

						// We choose the earliest connected device to un_pair, conn_dev_list[0] is the earliest connected device.
						// Attention: when conn_master_num none zero, conn_dev_list[0].conn_state is definite 1, no need to judge
						master_unpair_enable = conn_dev_list[0].conn_handle;  //mark connHandle on master_unpair_enable

					}
				}
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

			if(master_unpair_enable){
				master_unpair_enable = 0;
			}
		}
	}


}



_attribute_data_retention_		static u32 keyScanTick = 0;


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























void proc_master_role_unpair(void)
{



	//terminate and un_pair process, Telink demonstration effect: triggered by "un_pair" key press
	if(master_unpair_enable){

		dev_char_info_t* dev_char_info = dev_char_info_search_by_connhandle(master_unpair_enable); //connHandle has marked on on master_unpair_enable

		if( dev_char_info ){ //un_pair device in still in connection state

			if(blc_ll_disconnect(master_unpair_enable, HCI_ERR_REMOTE_USER_TERM_CONN) == BLE_SUCCESS){

				master_disconnect_connhandle = master_unpair_enable; //mark conn_handle

				master_unpair_enable = 0;  //every "un_pair" key can only triggers one connection disconnect


				// delete this device information(mac_address and distributed keys...) on FLash
				#if (BLE_MASTER_SMP_ENABLE)
					blc_smp_deleteBondingSlaveInfo_by_PeerMacAddress(dev_char_info->peer_adrType, dev_char_info->peer_addr);
				#else
					//user_tbl_slave_mac_delete_by_adr(dev_char_info->peer_adrType, dev_char_info->peer_addr);
				#endif
			}

		}
		else{ //un_pair device can not find in device list, it's not connected now

			master_unpair_enable = 0;  //every "un_pair" key can only triggers one connection disconnect
		}

	}
}










#endif // of of (FEATURE_TEST_MODE == TEST_EXTENDED_SCAN)


