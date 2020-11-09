/********************************************************************************************************
 * @file     app_config.h
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

#pragma once

#include "../feature_config.h"

#if (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)



#if (__PROJECT_8258_FEATURE_TEST__)
	#define CHIP_TYPE				CHIP_TYPE_825x
#else
	#define CHIP_TYPE				CHIP_TYPE_827x
#endif




#define MASTER_MAX_NUM								4
#define SLAVE_MAX_NUM								3






#define SINGLE_PERD_ADV								0	//single periodic ADV
#define MULTI_PERD_ADV								1   //multiple periodic ADV

/* for user to select adv_set test mode*/
#define	PERD_ADV_MODE								SINGLE_PERD_ADV









///////////////////////// Feature Configuration////////////////////////////////////////////////
#define BLE_SLAVE_SMP_ENABLE						1   //1 for smp,  0 no security
#define BLE_MASTER_SMP_ENABLE						0   //1 for smp,  0 no security





///////////////////// Flash Sector Usage Configuration for 512K Flash //////////////////////////
/*If Slave or Master SMP enable, default 0x78000~0x7BFFF (4 sector, 16K) is used for SMP pairing
  information storage, it is set in BLE stack library, same as initialization below:
  blc_smp_configPairingSecurityInfoStorageAddressAndSize(FLASH_ADR_SMP_PAIRING, FLASH_SMP_PAIRING_MAX_SIZE)
  First 8K is for normal use, second 8K is a backup to guarantee SMP information never lose.  */
#if (BLE_SLAVE_SMP_ENABLE || BLE_MASTER_SMP_ENABLE)
	#define FLASH_ADR_SMP_PAIRING					0x78000
	#define FLASH_SMP_PAIRING_MAX_SIZE				(2*4096)   //normal 8K + backup 8K = 16K
#endif

/*If Master SMP disable, 0x7C000~0x7CFFF 1 sector is for paring information storage */
#if (!BLE_MASTER_SMP_ENABLE)
	#define FLASH_ADR_CUSTOM_PAIRING         		0x7C000
	#define FLASH_CUSTOM_PAIRING_MAX_SIZE     		4096
#endif





#define	UI_KEYBOARD_ENABLE							1
#define UI_LED_ENABLE								1




#if (UI_KEYBOARD_ENABLE)   // if test pure power, kyeScan GPIO setting all disabled
		//---------------  KeyMatrix PB2/PB3/PB4/PB5 -----------------------------
		#define	MATRIX_ROW_PULL					PM_PIN_PULLDOWN_100K
		#define	MATRIX_COL_PULL					PM_PIN_PULLUP_10K

		#define	KB_LINE_HIGH_VALID				0   //dirve pin output 0 when keyscan, scanpin read 0 is valid


		#define			CR_VOL_UP				0xf0  ////
		#define			CR_VOL_DN				0xf1

		#define BTN_PAIR				0x01
		#define BTN_UNPAIR				0x02

		#define		KB_MAP_NORMAL	{	CR_VOL_UP,	CR_VOL_DN ,	 \
										BTN_PAIR,	BTN_UNPAIR }


		//////////////////// KEY CONFIG (EVK board) ///////////////////////////
		#define  KB_DRIVE_PINS  {GPIO_PB4, GPIO_PB5}
		#define  KB_SCAN_PINS   {GPIO_PB2, GPIO_PB3}

		//drive pin as gpio
		#define	PB4_FUNC				AS_GPIO
		#define	PB5_FUNC				AS_GPIO

		//drive pin need 100K pulldown
		#define	PULL_WAKEUP_SRC_PB4		MATRIX_ROW_PULL
		#define	PULL_WAKEUP_SRC_PB5		MATRIX_ROW_PULL

		//drive pin open input to read gpio wakeup level
		#define PB4_INPUT_ENABLE		1
		#define PB5_INPUT_ENABLE		1

		//scan pin as gpio
		#define	PB2_FUNC				AS_GPIO
		#define	PB3_FUNC				AS_GPIO

		//scan  pin need 10K pullup
		#define	PULL_WAKEUP_SRC_PB2		MATRIX_COL_PULL
		#define	PULL_WAKEUP_SRC_PB3		MATRIX_COL_PULL

		//scan pin open input to read gpio level
		#define PB2_INPUT_ENABLE		1
		#define PB3_INPUT_ENABLE		1


		#define		KB_MAP_NUM		KB_MAP_NORMAL
		#define		KB_MAP_FN		KB_MAP_NORMAL

#endif


#if (UI_LED_ENABLE)
	#define	GPIO_LED_RED			GPIO_PD5
	#define	GPIO_LED_WHITE			GPIO_PD4
	#define	GPIO_LED_GREEN			GPIO_PD3
	#define	GPIO_LED_BLUE			GPIO_PD2

	#define PD2_FUNC				AS_GPIO
	#define PD3_FUNC				AS_GPIO
	#define PD4_FUNC				AS_GPIO
	#define PD5_FUNC				AS_GPIO

	#define	PD2_OUTPUT_ENABLE		1
	#define	PD3_OUTPUT_ENABLE		1
	#define PD4_OUTPUT_ENABLE		1
	#define	PD5_OUTPUT_ENABLE		1

	#define LED_ON_LEVAL 			1 		//gpio output high voltage to turn on led
#endif






/////////////////// Clock  /////////////////////////////////
#define	SYS_CLK_TYPE										SYS_CLK_32M_Crystal

#if(SYS_CLK_TYPE == SYS_CLK_32M_Crystal)
	#define CLOCK_SYS_CLOCK_HZ  							32000000
#elif(SYS_CLK_TYPE == SYS_CLK_48M_Crystal)
	#define CLOCK_SYS_CLOCK_HZ  							48000000
#endif

enum{
	CLOCK_SYS_CLOCK_1S = CLOCK_SYS_CLOCK_HZ,
	CLOCK_SYS_CLOCK_1MS = (CLOCK_SYS_CLOCK_1S / 1000),
	CLOCK_SYS_CLOCK_1US = (CLOCK_SYS_CLOCK_1S / 1000000),
};


/////////////////// watchdog  //////////////////////////////
#define MODULE_WATCHDOG_ENABLE		0
#define WATCHDOG_INIT_TIMEOUT		500  //ms

#if (UART_PRINT_DEBUG_ENABLE)
	//the baud rate should not bigger than 1M(system timer clock is constant 16M)
	#define PRINT_BAUD_RATE             		1000000//1M baud rate,should Not bigger than 1Mb/s
	#define DEBUG_INFO_TX_PIN           		GPIO_PA0
	#define PULL_WAKEUP_SRC_PA0         		PM_PIN_PULLUP_10K
	#define PA0_OUTPUT_ENABLE         			1
	#define PA0_DATA_OUT                     	1 //must
	#include "application/print/u_printf.h"
#endif


#if(DEBUG_GPIO_ENABLE)


	#define GPIO_CHN0							GPIO_PD0
	#define GPIO_CHN1							GPIO_PD1
	#define GPIO_CHN2							GPIO_PD6
    #define GPIO_CHN3							GPIO_PD7
	#define GPIO_CHN4							GPIO_PA2
	#define GPIO_CHN5							GPIO_PA3
	#define GPIO_CHN6							GPIO_PA4
	#define GPIO_CHN7							GPIO_PB0
	#define GPIO_CHN8							GPIO_PC0
	#define GPIO_CHN9							GPIO_PC1
	#define GPIO_CHN10							GPIO_PC2
	#define GPIO_CHN11							GPIO_PC3
	#define GPIO_CHN12							GPIO_PC4
	#define GPIO_CHN13							GPIO_PC5
	#define GPIO_CHN14							GPIO_PC6
	#define GPIO_CHN15							GPIO_PC7

	#define PD0_OUTPUT_ENABLE					1
	#define PD1_OUTPUT_ENABLE					1
	#define PD6_OUTPUT_ENABLE					1
	#define PD7_OUTPUT_ENABLE					1
	#define PA2_OUTPUT_ENABLE					1
	#define PA3_OUTPUT_ENABLE					1
	#define PA4_OUTPUT_ENABLE					1
	#define PB0_OUTPUT_ENABLE					1
	#define PC0_OUTPUT_ENABLE					1
	#define PC1_OUTPUT_ENABLE					1
	#define PC2_OUTPUT_ENABLE					1
	#define PC3_OUTPUT_ENABLE					1
	#define PC4_OUTPUT_ENABLE					1
	#define PC5_OUTPUT_ENABLE					1
	#define PC6_OUTPUT_ENABLE					1
	#define PC7_OUTPUT_ENABLE					1

	#define DBG_CHN0_LOW		gpio_write(GPIO_CHN0, 0)
	#define DBG_CHN0_HIGH		gpio_write(GPIO_CHN0, 1)
	#define DBG_CHN0_TOGGLE		gpio_toggle(GPIO_CHN0)
	#define DBG_CHN1_LOW		gpio_write(GPIO_CHN1, 0)
	#define DBG_CHN1_HIGH		gpio_write(GPIO_CHN1, 1)
	#define DBG_CHN1_TOGGLE		gpio_toggle(GPIO_CHN1)
	#define DBG_CHN2_LOW		gpio_write(GPIO_CHN2, 0)
	#define DBG_CHN2_HIGH		gpio_write(GPIO_CHN2, 1)
	#define DBG_CHN2_TOGGLE		gpio_toggle(GPIO_CHN2)
	#define DBG_CHN3_LOW		gpio_write(GPIO_CHN3, 0)
	#define DBG_CHN3_HIGH		gpio_write(GPIO_CHN3, 1)
	#define DBG_CHN3_TOGGLE		gpio_toggle(GPIO_CHN3)
	#define DBG_CHN4_LOW		gpio_write(GPIO_CHN4, 0)
	#define DBG_CHN4_HIGH		gpio_write(GPIO_CHN4, 1)
	#define DBG_CHN4_TOGGLE		gpio_toggle(GPIO_CHN4)
	#define DBG_CHN5_LOW		gpio_write(GPIO_CHN5, 0)
	#define DBG_CHN5_HIGH		gpio_write(GPIO_CHN5, 1)
	#define DBG_CHN5_TOGGLE		gpio_toggle(GPIO_CHN5)
	#define DBG_CHN6_LOW		gpio_write(GPIO_CHN6, 0)
	#define DBG_CHN6_HIGH		gpio_write(GPIO_CHN6, 1)
	#define DBG_CHN6_TOGGLE		gpio_toggle(GPIO_CHN6)
	#define DBG_CHN7_LOW		gpio_write(GPIO_CHN7, 0)
	#define DBG_CHN7_HIGH		gpio_write(GPIO_CHN7, 1)
	#define DBG_CHN7_TOGGLE		gpio_toggle(GPIO_CHN7)
	#define DBG_CHN8_LOW		gpio_write(GPIO_CHN8, 0)
	#define DBG_CHN8_HIGH		gpio_write(GPIO_CHN8, 1)
	#define DBG_CHN8_TOGGLE		gpio_toggle(GPIO_CHN8)
	#define DBG_CHN9_LOW		gpio_write(GPIO_CHN9, 0)
	#define DBG_CHN9_HIGH		gpio_write(GPIO_CHN9, 1)
	#define DBG_CHN9_TOGGLE		gpio_toggle(GPIO_CHN9)
	#define DBG_CHN10_LOW		gpio_write(GPIO_CHN10, 0)
	#define DBG_CHN10_HIGH		gpio_write(GPIO_CHN10, 1)
	#define DBG_CHN10_TOGGLE	gpio_toggle(GPIO_CHN10)
	#define DBG_CHN11_LOW		gpio_write(GPIO_CHN11, 0)
	#define DBG_CHN11_HIGH		gpio_write(GPIO_CHN11, 1)
	#define DBG_CHN11_TOGGLE	gpio_toggle(GPIO_CHN11)
	#define DBG_CHN12_LOW		gpio_write(GPIO_CHN12, 0)
	#define DBG_CHN12_HIGH		gpio_write(GPIO_CHN12, 1)
	#define DBG_CHN12_TOGGLE	gpio_toggle(GPIO_CHN12)
	#define DBG_CHN13_LOW		gpio_write(GPIO_CHN13, 0)
	#define DBG_CHN13_HIGH		gpio_write(GPIO_CHN13, 1)
	#define DBG_CHN13_TOGGLE	gpio_toggle(GPIO_CHN13)
	#define DBG_CHN14_LOW		gpio_write(GPIO_CHN14, 0)
	#define DBG_CHN14_HIGH		gpio_write(GPIO_CHN14, 1)
	#define DBG_CHN14_TOGGLE	gpio_toggle(GPIO_CHN14)
	#define DBG_CHN15_LOW		gpio_write(GPIO_CHN15, 0)
	#define DBG_CHN15_HIGH		gpio_write(GPIO_CHN15, 1)
	#define DBG_CHN15_TOGGLE	gpio_toggle(GPIO_CHN15)
#else
	#define DBG_CHN0_LOW
	#define DBG_CHN0_HIGH
	#define DBG_CHN0_TOGGLE
	#define DBG_CHN1_LOW
	#define DBG_CHN1_HIGH
	#define DBG_CHN1_TOGGLE
	#define DBG_CHN2_LOW
	#define DBG_CHN2_HIGH
	#define DBG_CHN2_TOGGLE
	#define DBG_CHN3_LOW
	#define DBG_CHN3_HIGH
	#define DBG_CHN3_TOGGLE
	#define DBG_CHN4_LOW
	#define DBG_CHN4_HIGH
	#define DBG_CHN4_TOGGLE
	#define DBG_CHN5_LOW
	#define DBG_CHN5_HIGH
	#define DBG_CHN5_TOGGLE
	#define DBG_CHN6_LOW
	#define DBG_CHN6_HIGH
	#define DBG_CHN6_TOGGLE
	#define DBG_CHN7_LOW
	#define DBG_CHN7_HIGH
	#define DBG_CHN7_TOGGLE
	#define DBG_CHN8_LOW
	#define DBG_CHN8_HIGH
	#define DBG_CHN8_TOGGLE
	#define DBG_CHN9_LOW
	#define DBG_CHN9_HIGH
	#define DBG_CHN9_TOGGLE
	#define DBG_CHN10_LOW
	#define DBG_CHN10_HIGH
	#define DBG_CHN10_TOGGLE
	#define DBG_CHN11_LOW
	#define DBG_CHN11_HIGH
	#define DBG_CHN11_TOGGLE
	#define DBG_CHN12_LOW
	#define DBG_CHN12_HIGH
	#define DBG_CHN12_TOGGLE
	#define DBG_CHN13_LOW
	#define DBG_CHN13_HIGH
	#define DBG_CHN13_TOGGLE
	#define DBG_CHN14_LOW
	#define DBG_CHN14_HIGH
	#define DBG_CHN14_TOGGLE
	#define DBG_CHN15_LOW
	#define DBG_CHN15_HIGH
	#define DBG_CHN15_TOGGLE
#endif  //end of DEBUG_GPIO_ENABLE





/////////////////// set default   ////////////////

#include "vendor/common/default_config.h"



#endif // of of (FEATURE_TEST_MODE == TEST_PERIODIC_ADVERTISING)
