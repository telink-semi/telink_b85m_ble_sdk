/********************************************************************************************************
 * multi_adv_set.c
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
#if (ADV_SET_MODE == MULTI_ADV_SET)


const u8	tbl_advData_0 [] = {
	 17,	DT_COMPLETE_LOCAL_NAME, 				'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A',
	 2, 	DT_FLAGS, 								0x05,
	 3, 	DT_APPEARANCE, 					  		0x80, 0x01,
	 5, 	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID, 	0x12, 0x18, 0x0F, 0x18,
};

const u8	tbl_scanRsp_0 [] = {
	 17,	DT_COMPLETE_LOCAL_NAME, 				'A','A','A','A','A','A','A','A','A','A','A','A','A','A','A','A',
	 2, 	DT_FLAGS, 								0x05,
	 3, 	DT_APPEARANCE, 					  		0x80, 0x01,
	 5, 	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID, 	0x12, 0x18, 0x0F, 0x18,
};


const u8	tbl_advData_1 [] = {
	 17,	DT_COMPLETE_LOCAL_NAME, 				'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B',
	 2, 	DT_FLAGS, 								0x05,
	 3, 	DT_APPEARANCE, 					  		0x80, 0x01,
	 5, 	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID, 	0x12, 0x18, 0x0F, 0x18,
};

const u8	tbl_scanRsp_1 [] = {
	 17,	DT_COMPLETE_LOCAL_NAME, 				'B','B','B','B','B','B','B','B','B','B','B','B','B','B','B','B',
	 2, 	DT_FLAGS, 								0x05,
	 3, 	DT_APPEARANCE, 					  		0x80, 0x01,
	 5, 	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID, 	0x12, 0x18, 0x0F, 0x18,
};



const u8	tbl_advData_2 [] = {
	 17,	DT_COMPLETE_LOCAL_NAME, 				'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
	 2, 	DT_FLAGS, 								0x05,
	 3, 	DT_APPEARANCE, 					  		0x80, 0x01,
	 5, 	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID, 	0x12, 0x18, 0x0F, 0x18,
};

const u8	tbl_scanRsp_2 [] = {
	 17,	DT_COMPLETE_LOCAL_NAME, 				'C','C','C','C','C','C','C','C','C','C','C','C','C','C','C','C',
	 2, 	DT_FLAGS, 								0x05,
	 3, 	DT_APPEARANCE, 					  		0x80, 0x01,
	 5, 	DT_INCOMPLT_LIST_16BIT_SERVICE_UUID, 	0x12, 0x18, 0x0F, 0x18,
};






 	/** Number of Supported Advertising Sets, no exceed "ADV_SETS_NUMBER_MAX" */
	#define	APP_ADV_SETS_NUMBER						   				3

	/** Maximum Advertising Data Length */
	#define APP_MAX_LENGTH_ADV_DATA									1024

	/** Maximum Scan Response Data Length */
	#define APP_MAX_LENGTH_SCAN_RESPONSE_DATA		  				1024


	_attribute_data_retention_	u8  app_advSet_buffer[ADV_SET_PARAM_LENGTH * APP_ADV_SETS_NUMBER];


	#if 0
		//adv_set 1: Legacy, connectable_scannable
		_attribute_data_retention_	u8	app_primaryAdvPkt_buffer_1[MAX_LENGTH_PRIMARY_ADV_PKT_LEGACY];

		//adv_set 2: Extended, None_Connectable_None_Scannable undirected, with auxiliary packet
		_attribute_data_retention_	u8	app_primaryAdvPkt_buffer_2[MAX_LENGTH_PRIMARY_ADV_PKT_EXTENDED];

		//adv_set 3: Extended, Scannable, Undirected
		_attribute_data_retention_	u8	app_primaryAdvPkt_buffer_3[MAX_LENGTH_PRIMARY_ADV_PKT_EXTENDED];

		//adv_set 3: Extended, Connectable, Undirected
		_attribute_data_retention_	u8	app_primaryAdvPkt_buffer_4[MAX_LENGTH_PRIMARY_ADV_PKT_EXTENDED];





	_attribute_data_retention_	u8	app_secondaryAdvPkt_buffer[MAX_LENGTH_SECOND_ADV_PKT * APP_ADV_SETS_NUMBER];
	#endif


	_attribute_data_retention_	u8 	app_advData_buffer[APP_MAX_LENGTH_ADV_DATA	* APP_ADV_SETS_NUMBER];


	_attribute_data_retention_	u8 	app_scanRspData_buffer[APP_MAX_LENGTH_SCAN_RESPONSE_DATA * APP_ADV_SETS_NUMBER];


void app_multiple_adv_set_test(void)
{



	blc_ll_initExtendedAdvertising_module();


	blc_ll_initExtendedAdvSetBuffer(app_advSet_buffer, APP_ADV_SETS_NUMBER);

	blc_ll_initExtAdvDataBuffer(app_advData_buffer, APP_MAX_LENGTH_ADV_DATA);

	blc_ll_initExtScanRspDataBuffer(app_scanRspData_buffer, APP_MAX_LENGTH_SCAN_RESPONSE_DATA);


#if 0
	/* adv_set 0: Legacy, Unconnectable Undirected
	   adv_set 1: Legacy, Unconnectable Undirected
	   adv_set 2: Legacy, Unconnectable Undirected */

	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED,  ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

	blc_ll_setExtAdvData( ADV_HANDLE0,  sizeof(tbl_advData_0) , (u8 *)tbl_advData_0);


	blc_ll_setExtAdvParam( ADV_HANDLE1, 		ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED,  ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_1, 													   0);

	blc_ll_setExtAdvData( ADV_HANDLE1,  sizeof(tbl_advData_1) , (u8 *)tbl_advData_1);



	blc_ll_setExtAdvParam( ADV_HANDLE2, 		ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED,  ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_2, 													   0);

	blc_ll_setExtAdvData( ADV_HANDLE2,  sizeof(tbl_advData_2) , (u8 *)tbl_advData_2);



#elif 1
	/* adv_set 0: Legacy, Connectable_Scannable, Undirected
	   adv_set 1: Legacy, Connectable_Scannable, Undirected
	   adv_set 2: Legacy, Connectable_Scannable, Undirected */
	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_LEGACY_CONNECTABLE_SCANNABLE_UNDIRECTED,  		   ADV_INTERVAL_25MS, 			    ADV_INTERVAL_25MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

	blc_ll_setExtAdvData	( ADV_HANDLE0,  sizeof(tbl_advData_0), (u8 *)tbl_advData_0);
	blc_ll_setExtScanRspData( ADV_HANDLE0,  sizeof(tbl_scanRsp_0), (u8 *)tbl_scanRsp_0);




	blc_ll_setExtAdvParam( ADV_HANDLE1, 		ADV_EVT_PROP_LEGACY_CONNECTABLE_SCANNABLE_UNDIRECTED,  		   ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_1, 													   0);

	blc_ll_setExtAdvData	( ADV_HANDLE1,  sizeof(tbl_advData_1), (u8 *)tbl_advData_1);
	blc_ll_setExtScanRspData( ADV_HANDLE1,  sizeof(tbl_scanRsp_1), (u8 *)tbl_scanRsp_1);



	blc_ll_setExtAdvParam( ADV_HANDLE2, 		ADV_EVT_PROP_LEGACY_CONNECTABLE_SCANNABLE_UNDIRECTED, 		   ADV_INTERVAL_40MS, 			    ADV_INTERVAL_40MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_2, 													   0);

	blc_ll_setExtAdvData	( ADV_HANDLE2,  sizeof(tbl_advData_2), (u8 *)tbl_advData_2);
	blc_ll_setExtScanRspData( ADV_HANDLE1,  sizeof(tbl_scanRsp_2), (u8 *)tbl_scanRsp_2);


#elif 0
	//adv_set 1: Legacy, connectable_scannable
	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED,  ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

	blc_ll_setExtAdvData( ADV_HANDLE0,  sizeof(tbl_advData) , (u8 *)tbl_advData);




	//adv_set 2: Extended, None_Connectable_None_Scannable undirected, with auxiliary packet
	blc_ll_initExtAdvDataBuffer_by_advHandle(ADV_HANDLE1, app_advData_buffer, APP_MAX_LENGTH_ADV_DATA);

	blc_ll_setExtAdvParam( ADV_HANDLE1, 		ADV_EVT_PROP_LEGACY_NON_CONNECTABLE_NON_SCANNABLE_UNDIRECTED,  ADV_INTERVAL_30MS, 				ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										   BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   BLE_PHY_1M, 						0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   0);

	u8	testAdvData[1024];
	for(int i=0;i<1024;i++){
		testAdvData[i]=i;
	}


	blc_ll_setExtAdvData( ADV_HANDLE1, 1024,   testAdvData);





	/* adv_set 3: Extended, Scannable, Undirected */
	blc_ll_initExtScanRspDataBuffer_by_advHandle(ADV_HANDLE2, app_scanRspData_buffer, APP_MAX_LENGTH_SCAN_RESPONSE_DATA);

	blc_ll_setExtAdvParam( ADV_HANDLE2, 		ADV_EVT_PROP_EXTENDED_SCANNABLE_UNDIRECTED, 					ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);


	u8	testScanRspData[1024];
	for(int i=0;i<1024;i++){
		testScanRspData[i]=i;
	}


	//ExtScanRspData: 1010 bytes,   check that APP_MAX_LENGTH_SCAN_RESPONSE_DATA must bigger than 1010
	blc_ll_setExtScanRspData( ADV_HANDLE0, 1010, testScanRspData);


	/* adv_set 4: Extended, Connectable, Undirected */
	blc_ll_setExtAdvParam( ADV_HANDLE3, 		ADV_EVT_PROP_EXTENDED_CONNECTABLE_UNDIRECTED, 					    ADV_INTERVAL_30MS, 			    ADV_INTERVAL_30MS,
							   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
							   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
							   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);

	blc_ll_setExtAdvData( ADV_HANDLE3,  sizeof(tbl_advData) , (u8 *)tbl_advData);
#endif




	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);
	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE1, 0 , 0);
	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE2, 0 , 0);


//	blc_ll_setMaxAdvDelay_for_AdvEvent(MAX_DELAY_0MS);
}


#endif // end of (ADV_SET_MODE == MULTI_ADV_SET)
#endif // of of (FEATURE_TEST_MODE == TEST_EXTENDED_ADVERTISING)
