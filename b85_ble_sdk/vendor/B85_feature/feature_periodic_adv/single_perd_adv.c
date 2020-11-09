/********************************************************************************************************
 * single_perd_adv.c
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     2020-6-10
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


#include "app_att.h"
#include "app_ui.h"
#include "app_config.h"
#if (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
#if (PERD_ADV_MODE == SINGLE_PERD_ADV)





_attribute_data_retention_	u8  app_advSet_buffer[ADV_SET_PARAM_LENGTH * 1];

_attribute_data_retention_	u8  app_perdAdv_buffer[PERD_ADV_PARAM_LENGTH * 1];






void app_single_periodic_adv_set_test(void)
{

	blc_ll_initExtendedAdvertising_module();

	blc_ll_initExtendedAdvSetBuffer(app_advSet_buffer, 1);

	// Extended, None_Connectable_None_Scannable directed, without auxiliary packet
	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_DIRECTED, 	ADV_INTERVAL_30MS, 				ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);


//	blc_ll_setExtAdvData( ADV_HANDLE0, 0 , NULL);








	blc_ll_initPeriodicAdvertising_module();


	blc_ll_initPeriodicAdvParamBuffer(app_perdAdv_buffer, 1);

	blc_ll_setPeriodicAdvParam(ADV_HANDLE0, ADV_INTERVAL_30MS, ADV_INTERVAL_30MS, PERD_ADV_PROP_MASK_NONE);



//	blc_ll_setPeriodicAdvData(ADV_HANDLE0, );




//	blc_ll_setPeriodicAdvEnable(BLC_ADV_ENABLE, ADV_HANDLE0);



	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);

}



















#endif //end of (PERD_ADV_MODE == MULTI_PERD_ADV)
#endif //end of (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
