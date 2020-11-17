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
#include "vendor/common/blt_common.h"

#include "app_buffer.h"

#include "hci_tr.h"




#define     MY_APP_ADV_CHANNEL					BLT_ENABLE_ADV_ALL
#define 	MY_ADV_INTERVAL_MIN					ADV_INTERVAL_30MS
#define 	MY_ADV_INTERVAL_MAX					ADV_INTERVAL_40MS




//////////////////////////////////////////////////////////////////////////////
//	Adv Packet, Response Packet
//////////////////////////////////////////////////////////////////////////////
const u8	tbl_advData[] = {
	 0x05, 0x09, 't', 'H', 'C', 'I',
	 0x02, 0x01, 0x05, 							// BLE limited discoverable mode and BR/EDR not supported
};

const u8	tbl_scanRsp [] = {
	 0x07, 0x09, 't', 'H', 'C', 'I', '0', '1',	//scan name " tHCI01"
};


/////////////////////////////////////blc_register_hci_handler for spp//////////////////////////////
int rx_from_uart_cb (void)//UART data send to Master,we will handler the data as CMD or DATA
{
	if(my_fifo_get(&hci_rxfifo) == 0)
	{
		return 0;
	}

	u8* p = my_fifo_get(&hci_rxfifo);

	u16 rx_len = *(u16*)p; //dma len use 2 byte should be sufficient

	if (rx_len)
	{
	#if (UI_LED_ENABLE)
		gpio_toggle(GPIO_LED_RED);
	#endif

		//printf("Rx form UART\n");
	#if HCI_TR_EN
		blc_hci_handler(&p[0], rx_len - 4);
	#else
		blc_hci_handler(&p[4], rx_len - 4);
	#endif

		my_fifo_pop(&hci_rxfifo);

		return 1;
	}

	return 0;
}

uart_data_t T_txdata_buf;
int tx_to_uart_cb (void)
{
	u8 *p = NULL;

	static u32 txLoopTick;
	if(clock_time_exceed(txLoopTick, 8000)){  //Tx task loop period interval: 8000us
		txLoopTick = clock_time();
	}
	else{
		return 0;
	}

	p = my_fifo_get (&hci_txfifo);


	if (p && !uart_tx_is_busy ())
	{
		memcpy(&T_txdata_buf.data, p + 2, p[0]+p[1]*256);
		T_txdata_buf.len = p[0]+p[1]*256 ;
		//printf("Tx to UART\n");
		if (uart_dma_send((u8 *)(&T_txdata_buf)))
		{
		#if (UI_LED_ENABLE)
			gpio_toggle(GPIO_LED_GREEN);
		#endif

			my_fifo_pop (&hci_txfifo);

			return 1;
		}
	}


	return 0;
}

///////////////////////////////////////////

/**
 * @brief      use initialization
 * @param[in]  none.
 * @return     none.
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

#if (APP_DUMP_EN)
	my_usb_init(0x120, &print_fifo);
	usb_set_pin_en ();
#endif


	// Fifo initialization function should be called before  blc_ll_initAclConnection_module()
	/* all ACL connection share same RX FIFO */
	if(blc_ll_initAclConnRxFifo(app_acl_rxfifo, ACL_RX_FIFO_SIZE, ACL_RX_FIFO_NUM) != BLE_SUCCESS)	{ while(1); }
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


#if (MCU_CORE_TYPE == MCU_CORE_825x)
	rf_set_power_level_index (RF_POWER_P3p01dBm);
#else
	rf_set_power_level_index (RF_POWER_P3p50dBm);
#endif

	blc_ll_initChannelSelectionAlgorithm_2_feature();
	
	
	//////////// HCI Initialization  Begin /////////////////////////
#if (HCI_NEW_FIFO_FEATURE_ENABLE)
	/* HCI RX FIFO */
	if(blc_ll_initHciRxFifo(app_hci_rxfifo, HCI_RX_FIFO_SIZE, HCI_RX_FIFO_NUM) != BLE_SUCCESS)	{ BLMS_ERR_DEBUG(DBG_HCI_FIFO, 0xCC110222); while(1); }
	/* HCI TX FIFO */
	if(blc_ll_initHciTxFifo(app_hci_txfifo, HCI_TX_FIFO_SIZE, HCI_TX_FIFO_NUM) != BLE_SUCCESS) { BLMS_ERR_DEBUG(DBG_HCI_FIFO, 0xCC110224)while(1); }
	/* HCI RX ACL FIFO */
	if(blc_ll_initHciRxAclFifo(app_hci_rxAclfifo, HCI_RX_ACL_FIFO_SIZE, HCI_RX_ACL_FIFO_NUM) != BLE_SUCCESS)	{ BLMS_ERR_DEBUG(DBG_HCI_FIFO, 0xCC110226);while(1); }
#endif
	
	/* HCI Data && Event */
	blc_hci_registerControllerDataHandler (blc_hci_sendACLData2Host);
	blc_hci_registerControllerEventHandler(blc_hci_send_data); //controller hci event to host all processed in this func

	//bluetooth event
	blc_hci_setEventMask_cmd (HCI_EVT_MASK_DISCONNECTION_COMPLETE);
	//bluetooth low energy(LE) event, all enable
	blc_hci_le_setEventMask_cmd( 0xFFFFFFFF );
	blc_hci_le_setEventMask_2_cmd( 0x7FFFFFFF );


	////// ADV and Scan CONFIG  //////////
#if 0
	blc_ll_setAdvData( (u8 *)tbl_advData, sizeof(tbl_advData) );
	blc_ll_setScanRspData( (u8 *)tbl_scanRsp, sizeof(tbl_scanRsp));
	blc_ll_setAdvParam(ADV_INTERVAL_30MS, ADV_INTERVAL_30MS, ADV_TYPE_CONNECTABLE_UNDIRECTED, OWN_ADDRESS_PUBLIC, 0, NULL, BLT_ENABLE_ADV_ALL, ADV_FP_NONE);
	blc_ll_setAdvEnable(0);  //ADV disable

	blc_ll_setScanParameter(SCAN_TYPE_PASSIVE, SCAN_INTERVAL_200MS, SCAN_WINDOW_200MS, OWN_ADDRESS_PUBLIC, SCAN_FP_ALLOW_ADV_ANY);
	blc_ll_setScanEnable (BLC_SCAN_DISABLE, DUP_FILTER_DISABLE);
#endif

	////////////////// SPP initialization ///////////////////////////////////
	#if (HCI_ACCESS==HCI_USE_USB)
		usb_bulk_drv_init (0);
		blc_register_hci_handler (blc_hci_rx_from_usb, blc_hci_tx_to_usb);

		usb_dp_pullup_en (1);  //open USB enum
	#else ///(HCI_ACCESS == HCI_USE_UART)
		//note: dma addr must be set first before any other uart initialization!
		uart_recbuff_init((u8*)hci_rxfifo.p, (u16)hci_rxfifo.size);
		uart_gpio_set(UART_TX_PB1, UART_RX_PB0);
		uart_reset();  //will reset uart digital registers from 0x90 ~ 0x9f, so uart setting must set after this reset

		#if (MCU_CORE_TYPE == MCU_CORE_825x)
			//baud rate: 115200
			#if   (CLOCK_SYS_CLOCK_HZ == 16000000)
				uart_init(9, 13, PARITY_NONE, STOP_BIT_ONE);
			#elif (CLOCK_SYS_CLOCK_HZ == 24000000)
				uart_init(12, 15, PARITY_NONE, STOP_BIT_ONE);
			#elif (CLOCK_SYS_CLOCK_HZ == 32000000)
				uart_init(30, 8, PARITY_NONE, STOP_BIT_ONE);//uart_init_baudrate();
			#elif (CLOCK_SYS_CLOCK_HZ == 48000000)
				uart_init(25, 15, PARITY_NONE, STOP_BIT_ONE);
			#endif
		#else ///8278 use 1000000 for xiaomi project.
			//baud rate: 1000000
			#if   (CLOCK_SYS_CLOCK_HZ == 16000000)
				uart_init(0, 15, PARITY_NONE, STOP_BIT_ONE);
			#elif (CLOCK_SYS_CLOCK_HZ == 24000000)
				uart_init(1, 11, PARITY_NONE, STOP_BIT_ONE);
			#elif (CLOCK_SYS_CLOCK_HZ == 32000000)
				uart_init(1, 15, PARITY_NONE, STOP_BIT_ONE);//uart_init_baudrate();
			#elif (CLOCK_SYS_CLOCK_HZ == 48000000)
				uart_init(2, 15, PARITY_NONE, STOP_BIT_ONE);
			#endif
		#endif

		#if HCI_TR_EN
			uart_dma_enable(0, 1); 	                    //UART data in hardware buffer moved by DMA, so we need enable them first
			irq_set_mask(FLD_IRQ_DMA_EN);
			dma_chn_irq_enable(FLD_DMA_CHN_UART_TX, 1); //UART RX/TX DMA IRQ enable
			uart_irq_enable(1, 0);  	                //UART RX/TX IRQ no need, disable them
			uart_ndma_irq_triglevel(1,1);

			HCI_Tr_Init(&hci_rxfifo);
		#else
			uart_dma_enable(1, 1); 	//UART data in hardware buffer moved by DMA, so we need enable them first
			irq_set_mask(FLD_IRQ_DMA_EN);
			dma_chn_irq_enable(FLD_DMA_CHN_UART_RX | FLD_DMA_CHN_UART_TX, 1);   	//UART RX/TX DMA IRQ enable
			uart_irq_enable(0, 0);  	//UART RX/TX IRQ no need, disable them
		#endif

		blc_register_hci_handler(rx_from_uart_cb, tx_to_uart_cb);				//customized uart handler
	#endif
	////////////////// End SPP initialization ///////////////////////////////////
}


void user_init_deepRetn(void)
{

}


void main_loop (void)
{
	////////////////////////////////////// BLE entry /////////////////////////////////
	blc_sdk_main_loop();



	////////////////////////////////////// UI entry /////////////////////////////////


}




