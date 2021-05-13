/*
 *******************************************************************************
 *  FileName  : hci_dfu_port.c
 *  Created on: 2021-05-07
 *  Author    : GaoQiu
 *  Copyright :
 *******************************************************************************
 */
#include "hci_dfu_port.h"
#include "hci_tr_def.h"

#include "drivers.h"
#include "common/string.h"
#include "stack/ble/hci/hci_stack.h"
#include "stack/ble/ble_common.h"

/**
 *******************************************************************************
 * FLash API
 *******************************************************************************
 */
_attribute_ram_code_ void FLASH_WritePage(u32 addr, u8 *pData, u32 len)
{
#if 0
	u32 offset = 0;
	while(len)
	{
		u32 dataLen = (len>=16) ? 16:len;
		flash_write_page(addr + offset, dataLen, pData);

		pData  += dataLen;
		offset += dataLen;
		len    -= dataLen;
	}
#else
	flash_write_page(addr, len, pData);
#endif
}

_attribute_ram_code_ void FLASH_ReadPage(u32 addr, u8 *pData, u32 len)
{
	flash_read_page(addr, len, pData);
}

_attribute_ram_code_ void FLASH_EraseSector(u32 addr)
{
	flash_erase_sector(addr);
}

void MCU_Reset(void)
{
	start_reboot();
}

bool UART_IsBusy(void)
{
	return uart_tx_is_busy();
}

/**
 *******************************************************************************
 *  Misc API
 *******************************************************************************
 */
void Hci_Reset(void)
{
	extern ble_sts_t blc_hci_reset(void);
	blc_hci_reset();
}

extern hci_fifo_t bltHci_txfifo;
void Hci_SendCmdCmplEvt(u16 opcode, u8 *pParam, u32 len)
{
	hci_fifo_t *pTxFifo = &bltHci_txfifo;

	if(pTxFifo->wptr - pTxFifo->rptr >= pTxFifo->num){
		return;
	}

	u8 *pBuf = pTxFifo->p + (pTxFifo->wptr & pTxFifo->mask) * pTxFifo->size;
	if(pBuf)
	{
		u8 *p = pBuf;
		UINT16_TO_BSTREAM(p, 1 + HCI_EVT_HEAD_LEN + 3 + len)// 3 = HCI_EVT_TYPE + EVT_CODE + PARAM_LEN

		//HCI evt packet
		UINT8_TO_BSTREAM(p, HCI_TR_TYPE_EVENT);
		UINT8_TO_BSTREAM(p, 0x0E);   //command complete event code.
		UINT8_TO_BSTREAM(p, 3 + len);//command complete event parameter length.

		UINT8_TO_BSTREAM(p, 1);//Num_HCI_Command_Packets
		UINT16_TO_BSTREAM(p, opcode);
		memcpy(p, pParam, len);
		p += len;

		pTxFifo->wptr++;
	}
}

void Hci_SendCmdCmplStatusEvt(u16 opcode, u8 status)
{
	Hci_SendCmdCmplEvt(opcode, &status, 1);
}

void Hci_SendCmdStatusEvt(u16 opcode, u8 status)
{
	hci_fifo_t *pTxFifo = &bltHci_txfifo;

	if(pTxFifo->wptr - pTxFifo->rptr >= pTxFifo->num){
		return;
	}

	u8 *pBuf = pTxFifo->p + (pTxFifo->wptr & pTxFifo->mask) * pTxFifo->size;
	if(pBuf)
	{
		u8 *p = pBuf;
		UINT16_TO_BSTREAM(p, 1 + HCI_EVT_HEAD_LEN + 4)// 3 = HCI_EVT_TYPE + EVT_CODE + PARAM_LEN

		//HCI evt packet
		UINT8_TO_BSTREAM(p, HCI_TR_TYPE_EVENT);
		UINT8_TO_BSTREAM(p, 0x0F);   //command status event code.
		UINT8_TO_BSTREAM(p, 4);      //command status parameter length.

		UINT8_TO_BSTREAM(p, status);
		UINT8_TO_BSTREAM(p, 1);//Num_HCI_Command_Packets
		UINT16_TO_BSTREAM(p, opcode);

		pTxFifo->wptr++;
	}
}


