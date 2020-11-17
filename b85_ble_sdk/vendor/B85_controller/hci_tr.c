/********************************************************************************************************
 * @file	hci_tr.c
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


#include "hci_tr.h"
#include "drivers.h"
#include "stack/ble/hci/hci.h"

//#define DEBUG

#ifdef DEBUG
/*!  Debug */
#define DBG_CHN0_PIN GPIO_PD0
#define DBG_CHN1_PIN GPIO_PD1
#define DBG_CHN2_PIN GPIO_PD6
#define DBG_CHN3_PIN GPIO_PD7
#define DBG_CHN4_PIN GPIO_PA2
#define DBG_CHN5_PIN GPIO_PA3

#define COUNTOF(x)  (sizeof((x))/sizeof((x)[0]))

#define DBG_CHN0_TOG  gpio_toggle(DBG_CHN0_PIN);
#define DBG_CHN1_TOG  gpio_toggle(DBG_CHN1_PIN);
#define DBG_CHN2_TOG  gpio_toggle(DBG_CHN2_PIN);
#define DBG_CHN3_TOG  gpio_toggle(DBG_CHN3_PIN);
#define DBG_CHN4_TOG  gpio_toggle(DBG_CHN4_PIN);
#define DBG_CHN5_TOG  gpio_toggle(DBG_CHN5_PIN);
#endif

/*!  HCI Transmit Type */
#define HCI_TR_TYPE_NONE      0x00
#define HCI_TR_TYPE_CMD       0x01
#define HCI_TR_TYPE_ACL       0x02
#define HCI_TR_TYPE_SCO       0x03
#define HCI_TR_TYPE_EVENT     0x04


/*! HCI Transmit State */
enum{
	HCI_TR_STATE_INIT   = 0x00,
	HCI_TR_STATE_IDLE   = 0x01,
	HCI_TR_STATE_RCVING = 0x02,
	HCI_TR_STATE_RCVED  = 0x03,
	HCI_TR_STATE_ERR    = 0x04,
};

/*!  HCI Transmit main control block */
typedef struct{
	u8            *pCurRxBuf;
	u16            rxCnt;
	u16            frameHeadLen;
	u16            paramLen;
	u8             trState;
	u8             trType;
	my_fifo_t      *rxFifo;
}HciTrCB_t;

HciTrCB_t hciTrCb;

void HCI_Tr_TimeInit(u16 ms)
{
	timer0_set_mode(TIMER_MODE_SYSCLK, 0, ms * 1000* 32);
	//reg_tmr_ctrl |= BIT(0);
}

static void HCI_Tr_TimeEnable(void)
{
	reg_tmr0_tick = 0;
	reg_tmr_ctrl |= BIT(0);
}

static void HCI_Tr_TimeDisable(void)
{
	reg_tmr0_tick = 0;
	reg_tmr_ctrl &= ~BIT(0);
}

void HCI_Tr_Init(my_fifo_t *pRxFifo)
{
	hciTrCb.rxFifo = pRxFifo;

	hciTrCb.pCurRxBuf = NULL;
	hciTrCb.rxCnt = 0;

	hciTrCb.frameHeadLen = 0;
	hciTrCb.paramLen = 0;

	hciTrCb.trState = HCI_TR_STATE_INIT;
	hciTrCb.trType = HCI_TR_TYPE_NONE;

	HCI_Tr_TimeInit(1);

#ifdef DEBUG
	u16 debugPin[] = {DBG_CHN0_PIN, DBG_CHN1_PIN, DBG_CHN2_PIN, DBG_CHN3_PIN,
			          DBG_CHN4_PIN, DBG_CHN5_PIN};
	for(int i=0 ;i<COUNTOF(debugPin); i++)
	{
		gpio_set_func(debugPin[i], AS_GPIO);
		gpio_set_input_en(debugPin[i], 0);
		gpio_set_output_en(debugPin[i], 1);
	}
#endif
}

u8 rxIndex = 0;
static u8 HCI_Tr_ReceiveByte(void)
{
	u8 data = REG_ADDR8(0x90 + rxIndex);
	rxIndex++;
	rxIndex = rxIndex & 0x03;
	return data;
}

_attribute_ram_code_
void HCI_Tr_RxHandler(void)
{
	u8 res = HCI_Tr_ReceiveByte();

	my_fifo_t *pFifo = hciTrCb.rxFifo;

	switch(hciTrCb.trState)
	{
	case HCI_TR_STATE_INIT:
		hciTrCb.trState = HCI_TR_STATE_IDLE;
		break;

	case HCI_TR_STATE_IDLE:
	{
		HCI_Tr_TimeEnable();
		hciTrCb.trType = HCI_TR_TYPE_NONE;
		hciTrCb.rxCnt = 0;

		switch(res)
		{
		case HCI_TR_TYPE_CMD:
			hciTrCb.frameHeadLen = 3;
			break;
		case HCI_TR_TYPE_ACL:
			hciTrCb.frameHeadLen = 4;
			break;
		case HCI_TR_TYPE_EVENT:
			hciTrCb.frameHeadLen = 2;
			break;
		default:
			hciTrCb.frameHeadLen = 0;
			return;
		}

		if( pFifo->wptr - pFifo->rptr >= pFifo->num){
			return; //have no memory.
		}

		hciTrCb.pCurRxBuf = my_fifo_wptr(pFifo);
		hciTrCb.pCurRxBuf[hciTrCb.rxCnt++] = res;

		hciTrCb.trType   = res;
		hciTrCb.paramLen = 0;
		hciTrCb.trState  = HCI_TR_STATE_RCVING;
		break;
	}
	case HCI_TR_STATE_RCVING:
	{
		HCI_Tr_TimeEnable();

		hciTrCb.pCurRxBuf[hciTrCb.rxCnt++] = res;

		if(hciTrCb.frameHeadLen == hciTrCb.rxCnt - 1)
		{
			u8 *p = NULL;
			if(hciTrCb.trType == HCI_TR_TYPE_ACL){
				p = hciTrCb.pCurRxBuf + hciTrCb.rxCnt - 2;
				hciTrCb.paramLen = (p[1]<<8) + p[0];
			}
			else if(hciTrCb.trType == HCI_TR_TYPE_CMD || hciTrCb.trType == HCI_TR_TYPE_EVENT){
				p = hciTrCb.pCurRxBuf + hciTrCb.rxCnt - 1;
				hciTrCb.paramLen = p[0];
			}
			else{
				/* We will never be here */
				hciTrCb.paramLen = 0xff00;
				hciTrCb.trState = HCI_TR_STATE_IDLE;
				HCI_Tr_TimeDisable();
			}

			if(hciTrCb.paramLen == 0){
				my_fifo_next(pFifo);
				hciTrCb.trState = HCI_TR_STATE_IDLE;
				HCI_Tr_TimeDisable();
				break;
			}
			else if(hciTrCb.paramLen + hciTrCb.rxCnt > hciTrCb.rxFifo->size){
				hciTrCb.trState = HCI_TR_STATE_IDLE;
				HCI_Tr_TimeDisable();
				break;
			}
		}

		if(hciTrCb.paramLen != 0)
		{
			if(hciTrCb.rxCnt == 1 + hciTrCb.frameHeadLen + hciTrCb.paramLen){
				my_fifo_next(pFifo);
				hciTrCb.trState = HCI_TR_STATE_IDLE;
				HCI_Tr_TimeDisable();
			}
			else if(hciTrCb.rxCnt > 1 + hciTrCb.frameHeadLen + hciTrCb.paramLen){
				hciTrCb.trState = HCI_TR_STATE_IDLE;
				HCI_Tr_TimeDisable();
			}
		}
		break;
	}

	case HCI_TR_STATE_ERR:

	default:
		hciTrCb.trState = HCI_TR_STATE_IDLE;
		HCI_Tr_TimeDisable();
		break;
	}
}

_attribute_ram_code_
void HCI_Tr_IRQHandler(void)
{
	/* UART Normal Rx IRQ */
	if(REG_ADDR8(0x9d) & 0x08)
	{
		REG_ADDR8(0x9d) = 0x08;

		HCI_Tr_RxHandler();
	}

	/* UART DMA Tx IRQ */
	if(reg_dma_irq_status & BIT(1)) {
		reg_dma_irq_status = BIT(1);//clear
	}

	/* Timer timeout IRQ */
	if(reg_tmr_sta & BIT(0)){
		reg_tmr_sta = BIT(0);
		HCI_Tr_TimeDisable();
		hciTrCb.trState = HCI_TR_STATE_IDLE;
	}
}

