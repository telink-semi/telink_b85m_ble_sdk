/********************************************************************************************************
 * single_adv_set.c
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     June. 8, 2020
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

#if (FEATURE_TEST_MODE == TEST_EXTENDED_ADVERTISING)
#if (ADV_SET_MODE == SINGLE_ADV_SET)







//Legacy, Unconnectable Undirected
#define ADV_EVENT_PROP__LEGACY_UNCONNECTABLE										0

//Legacy, Connectable_Scannable, Undirected
#define ADV_EVENT_PROP__LEGACY_CONN_SCAN											1

// Extended, None_Connectable_None_Scannable undirected, without auxiliary packet
#define ADV_EVENT_PROP__EXT_NONE_NONE_SCAN_UNDIRECTED__WITHOUT_AUX_PKT				10

// Extended, None_Connectable_None_Scannable directed, without auxiliary packet
#define ADV_EVENT_PROP__EXT_NONE_NONE_SCAN_DIRECTED__WITHOUT_AUX_PKT				11

// Extended, None_Connectable_None_Scannable undirected, with auxiliary packet
#define ADV_EVENT_PROP__EXT_NONE_CONN_NONE_SCAN_UNDIRECTED__WITH_AUX_PKT			12

// Extended, None_Connectable_None_Scannable Directed, with auxiliary packet
#define ADV_EVENT_PROP__EXT_NONE_CONN_NONE_SCAN_DIRECTED__WITH_AUX_PKT				13

// Extended, Scannable, Undirected
#define ADV_EVENT_PROP__EXT_SCAN_UNDIRECTED											14

// Extended, Connectable, Undirected
#define ADV_EVENT_PROP__EXT_CONN_UNDIRECTED											15


/* for user to select adv_event_property when single adv_set is tested */
#define ADV_EVENT_PROPERTY_SELECT													ADV_EVENT_PROP__EXT_NONE_CONN_NONE_SCAN_UNDIRECTED__WITH_AUX_PKT










#if 1

	const u8	tbl_advData[] = {
		 17,   0x09, 'E','a','g','l','e',' ', 's','a','m', 'p','l','e', 'T','e','s', 't',
		 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
		 0x03, 0x19, 0x80, 0x01, 					// 384, Generic Remote Control, Generic category
		 0x05, 0x02, 0x12, 0x18, 0x0F, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
	};

	const u8	tbl_scanRsp [] = {
		 17,   0x09, 'E','a','g','l','e',' ', 's','a','m', 'p','l','e', 'T','e','s', 't',
		 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
		 0x03, 0x19, 0x80, 0x01, 					// 384, Generic Remote Control, Generic category
		 0x05, 0x02, 0x12, 0x18, 0x0F, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
	};

#else

const u8	tbl_advData[] = {
	 0x09, 0x09, 'T','L','K','_','M','4','S','3',
	 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
	 0x03, 0x19, 0x80, 0x01, 					// 384, Generic Remote Control, Generic category
	 0x05, 0x02, 0x12, 0x18, 0x0F, 0x18,		// incomplete list of service class UUIDs (0x1812, 0x180F)
};

const u8	tbl_scanRsp [] = {
	 0x09, 0x09, 'T','L','K','_','M','4','S','3',
};

#endif








/** Number of Supported Advertising Sets, no exceed "ADV_SETS_NUMBER_MAX" */
#define	APP_ADV_SETS_NUMBER						   				1

/** Maximum Advertising Data Length,   (if legacy ADV, max length 31 bytes is enough) */
#define APP_MAX_LENGTH_ADV_DATA									1024

/** Maximum Scan Response Data Length, (if legacy ADV, max length 31 bytes is enough) */
#define APP_MAX_LENGTH_SCAN_RESPONSE_DATA		  				31








_attribute_data_retention_	u8  app_advSet_buffer[ADV_SET_PARAM_LENGTH * 1];

//_attribute_data_retention_	u8	app_primaryAdvPkt_buffer[MAX_LENGTH_PRIMARY_ADV_PKT * 1];

//_attribute_data_retention_	u8	app_secondary_adv_pkt[MAX_LENGTH_SECOND_ADV_PKT * 1];

_attribute_data_retention_	u8 	app_advData_buffer[APP_MAX_LENGTH_ADV_DATA	* 1];

_attribute_data_retention_	u8 	app_scanRspData_buffer_[APP_MAX_LENGTH_SCAN_RESPONSE_DATA * 1];




u8	testAdvData[1024];

void app_single_adv_set_test(void)
{

	blc_ll_initExtendedAdvertising_module();


	blc_ll_initExtendedAdvSetBuffer(app_advSet_buffer, APP_ADV_SETS_NUMBER);


	blc_ll_initExtAdvDataBuffer(app_advData_buffer, APP_MAX_LENGTH_ADV_DATA);


	blc_ll_initExtScanRspDataBuffer(app_scanRspData_buffer_, APP_MAX_LENGTH_SCAN_RESPONSE_DATA);


	u32 my_adv_interval_min = ADV_INTERVAL_20MS;  //30mS timing error
	u32 my_adv_interval_max = ADV_INTERVAL_20MS;


#if (ADV_EVENT_PROPERTY_SELECT == ADV_EVENT_PROP__LEGACY_UNCONNECTABLE)
	//Legacy, non_connectable_non_scannable

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED,  my_adv_interval_min, 			my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

	blc_ll_setExtAdvData( ADV_HANDLE0, sizeof(tbl_advData), (u8 *)tbl_advData);

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);
#elif (ADV_EVENT_PROPERTY_SELECT == ADV_EVENT_PROP__LEGACY_CONN_SCAN)
	//Legacy, Connectable_Scannable, Undirected

	blc_ll_initConnection_module();				//connection module  mandatory for BLE slave/master
	blc_ll_initSlaveRole_module();				//slave module: 	 mandatory for BLE slave,

	////// Host Initialization  //////////
	blc_gap_peripheral_init();    //gap initialization
	extern void my_att_init ();
	my_att_init (); //gatt initialization
	blc_l2cap_register_handler (blc_l2cap_packet_receive);  	//l2cap initialization
	blc_smp_peripheral_init(); 									//SMP initialization



	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_LEGACY_CONNECTABLE_SCANNABLE_UNDIRECTED,  my_adv_interval_min, 			my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

	blc_ll_setExtAdvData( ADV_HANDLE0, sizeof(tbl_advData), (u8 *)tbl_advData);

	blc_ll_setExtScanRspData( ADV_HANDLE0,  sizeof(tbl_scanRsp), (u8 *)tbl_scanRsp);

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);

#elif (ADV_EVENT_PROPERTY_SELECT == ADV_EVENT_PROP__EXT_NONE_NONE_SCAN_UNDIRECTED__WITHOUT_AUX_PKT)
	// Extended, None_Connectable_None_Scannable undirected, without auxiliary packet

//	u16 event_prop = ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED;
	u16 event_prop = ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED | ADV_EVT_PROP_EXTENDED_MASK_TX_POWER_INCLUDE;

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		event_prop, 												   my_adv_interval_min,				my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

//	blc_ll_setExtAdvData( ADV_HANDLE0, 0 , NULL);   //do not set ADV data, or set it with advData_len "0"

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);


#elif (ADV_EVENT_PROPERTY_SELECT == ADV_EVENT_PROP__EXT_NONE_NONE_SCAN_DIRECTED__WITHOUT_AUX_PKT)
	// Extended, None_Connectable_None_Scannable directed, without auxiliary packet

	u8 test_peer_type = BLE_ADDR_PUBLIC;  // BLE_ADDR_RANDOM
	u8 test_peer_mac[6] = {0x11,0x11,0x11,0x11,0x11,0x11};

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_DIRECTED,  my_adv_interval_min,				my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   test_peer_type, 					test_peer_mac,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

//	blc_ll_setExtAdvData( ADV_HANDLE0, 0 , NULL);   //do not set ADV data, or set it with advData_len "0"

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);


#elif (ADV_EVENT_PROPERTY_SELECT == ADV_EVENT_PROP__EXT_NONE_CONN_NONE_SCAN_UNDIRECTED__WITH_AUX_PKT)
	// Extended, None_Connectable_None_Scannable undirected, with auxiliary packet

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED, my_adv_interval_min, 			my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);

	for(int i=0;i<1024;i++){
		testAdvData[i] = i;
	}

//	blc_ll_setExtAdvData( ADV_HANDLE0,    31, (u8 *)testAdvData);
	blc_ll_setExtAdvData( ADV_HANDLE0, 	 200, testAdvData);
//	blc_ll_setExtAdvData( ADV_HANDLE0, 	 400, testAdvData);
//	blc_ll_setExtAdvData( ADV_HANDLE0, 	 600, testAdvData);
//	blc_ll_setExtAdvData( ADV_HANDLE0,  1024, testAdvData);
//
	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);


#elif (ADV_EVENT_PROPERTY_SELECT == ADV_EVENT_PROP__EXT_NONE_CONN_NONE_SCAN_DIRECTED__WITH_AUX_PKT)
	// Extended, None_Connectable_None_Scannable Directed, with auxiliary packet

	u8 test_peer_type = BLE_ADDR_RANDOM;  // BLE_ADDR_RANDOM
	u8 test_peer_mac[6] = {0x11,0x11,0x11,0x11,0x11,0x11};

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_DIRECTED,
																												my_adv_interval_min, 			my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    test_peer_type, 				test_peer_mac,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);


	for(int i=0;i<1024;i++){
		testAdvData[i]=i;
	}

	blc_ll_setExtAdvData( ADV_HANDLE0,  1024, testAdvData);

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);


#elif 0 // Extended, Scannable, Undirected


	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_SCANNABLE_UNDIRECTED, 					my_adv_interval_min, 			my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);

	//Extended Scannable Event do not have ADV data

	u8	testScanRspData[1024];
	for(int i=0;i<1024;i++){
		testScanRspData[i]=i;
	}


		blc_ll_setExtScanRspData( ADV_HANDLE0, 1024, testScanRspData);



		blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);


#elif 0 // Extended, Connectable, Undirected

	blc_ll_initConnection_module();				//connection module  mandatory for BLE slave/master
	blc_ll_initSlaveRole_module();				//slave module: 	 mandatory for BLE slave,

	blc_ll_initChannelSelectionAlgorithm_2_feature();

	////// Host Initialization  //////////
	blc_gap_peripheral_init();    //gap initialization
	extern void my_att_init ();
	my_att_init (); //gatt initialization
	blc_l2cap_register_handler (blc_l2cap_packet_receive);  	//l2cap initialization
	blc_smp_peripheral_init(); 									//SMP initialization

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_CONNECTABLE_UNDIRECTED, 					my_adv_interval_min, 			my_adv_interval_max,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);

	blc_ll_setExtAdvData( ADV_HANDLE0, sizeof(tbl_advData) , (u8 *)tbl_advData);


	//Extended Connectable Event do not have scan_rsp data

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);

#else

#endif



//	blc_ll_setAuxAdvChnIdxByCustomers(1); //debug chn_2406
//	blc_ll_setMaxAdvDelay_for_AdvEvent(MAX_DELAY_0MS);
}


#endif // end of (ADV_SET_MODE == SINGLE_ADV_SET)
#endif // end of (FEATURE_TEST_MODE == TEST_EXTENDED_ADVERTISING)
