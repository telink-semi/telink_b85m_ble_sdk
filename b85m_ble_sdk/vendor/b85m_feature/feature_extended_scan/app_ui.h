/********************************************************************************************************
 * @file	 app_ui.h
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

#if (FEATURE_TEST_MODE == TEST_EXT_SCAN)

#ifndef APP_UI_H_
#define APP_UI_H_



extern 	int	master_pairing_enable;
extern 	int master_unpair_enable;

extern	int master_disconnect_connhandle;

extern	int master_auto_connect;
extern	int user_manual_paring;


void proc_keyboard (u8 e, u8 *p, int n);



void proc_master_role_unpair(void);




#endif /* APP_UI_H_ */



#endif // of of (FEATURE_TEST_MODE == TEST_EXT_SCAN)
