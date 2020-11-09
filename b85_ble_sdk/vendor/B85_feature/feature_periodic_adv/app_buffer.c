/********************************************************************************************************
 * @file     app_buffer.c
 *
 * @brief    for TLSR chips
 *
 * @author	 BLE Group
 * @date     June. 2, 2020
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
#include "app_config.h"


#if (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)



/********************* ACL connection LinkLayer TX & RX data FIFO allocation, Begin *******************************/

/** all connections share same RX FIFO */
MYFIFO_INIT(blt_rxfifo, 64, 16);


/*Note: different connections have their own TX FIFO, master and slave set independently
 * Tx FIFO size = Extra_Len(10) + then align 4bytes
 */

/** master connection TX FIFO,  40*8*MASTER_MAX_NUM */
MULTI_CONN_FIFO_INIT(blt_m_txfifo, 40, 8, MASTER_MAX_NUM);

/** slave  connection TX FIFO,  40*8*SLAVE_MAX_NUM */
MULTI_CONN_FIFO_INIT(blt_s_txfifo, 40, 8, SLAVE_MAX_NUM);

/******************** ACL connection LinkLayer TX & RX data FIFO allocation, End ***********************************/






/***************** ACL connection L2CAP layer MTU TX & RX data FIFO allocation, Begin ********************************/
_attribute_data_retention_	u8 mtu_m_rx_fifo[MASTER_MAX_NUM * MTU_M_BUFF_SIZE_MAX];

_attribute_data_retention_	u8 mtu_s_rx_fifo[SLAVE_MAX_NUM * MTU_S_BUFF_SIZE_MAX];
_attribute_data_retention_	u8 mtu_s_tx_fifo[SLAVE_MAX_NUM * MTU_S_BUFF_SIZE_MAX];
/***************** ACL connection L2CAP layer MTU TX & RX data FIFO allocation, End **********************************/













#endif // of of (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
