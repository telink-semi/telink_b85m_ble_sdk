/********************************************************************************************************
 * @file	multi_perd_adv.c
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
#include "app_att.h"
#include "app_ui.h"

#if (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
#if (PERD_ADV_MODE == MULTI_PERD_ADV)





/** Number of Supported Advertising Sets, no exceed "ADV_SETS_NUMBER_MAX" */
#define			APP_ADV_SETS_NUMBER						   		2


#define			APP_PERD_ADV_NUMBER							2


_attribute_ble_data_retention_	u8  app_advSet_buffer[ADV_SET_PARAM_LENGTH * APP_ADV_SETS_NUMBER];

_attribute_ble_data_retention_	u8  app_perdAdv_buffer[PERD_ADV_PARAM_LENGTH * APP_PERD_ADV_NUMBER];













void app_multiple_periodic_adv_set_test(void)
{
	blc_ll_initExtendedAdvertising_module();

	blc_ll_initExtendedAdvSetBuffer(app_advSet_buffer, APP_ADV_SETS_NUMBER);

	// Extended, None_Connectable_None_Scannable directed, without auxiliary packet
	blc_ll_setExtAdvParam( ADV_HANDLE0, 		ADV_EVT_PROP_EXTENDED_NON_CONNECTABLE_NON_SCANNABLE_DIRECTED, 	ADV_INTERVAL_30MS, 				ADV_INTERVAL_30MS,
						   BLT_ENABLE_ADV_ALL,	OWN_ADDRESS_PUBLIC, 										    BLE_ADDR_PUBLIC, 				NULL,
						   ADV_FP_NONE,  		TX_POWER_3dBm,												   	BLE_PHY_1M, 					0,
						   BLE_PHY_1M, 	 		ADV_SID_0, 													   	0);


//	blc_ll_setExtAdvData( ADV_HANDLE0, 0 , NULL);








	blc_ll_initPeriodicAdvertising_module();


	blc_ll_initPeriodicAdvParamBuffer(app_perdAdv_buffer, APP_PERD_ADV_NUMBER);

	blc_ll_setPeriodicAdvParam(ADV_HANDLE0, ADV_INTERVAL_30MS, ADV_INTERVAL_30MS, PERD_ADV_PROP_MASK_NONE);



	blc_ll_setPeriodicAdvData




//	blc_ll_setPeriodicAdvEnable(BLC_ADV_ENABLE, ADV_HANDLE0);

//	blc_ll_setPeriodicAdvEnable(BLC_ADV_ENABLE, ADV_HANDLE1);



	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE0, 0 , 0);

	blc_ll_setExtAdvEnable( BLC_ADV_ENABLE, ADV_HANDLE1, 0 , 0);

}









#endif //end of (PERD_ADV_MODE == MULTI_PERD_ADV)
#endif //end of (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
