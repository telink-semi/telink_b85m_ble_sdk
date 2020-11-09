/********************************************************************************************************
 * @file	ext_rf.h
 *
 * @brief	This is the header file for B91
 *
 * @author	BLE Group
 * @date	2020
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
#ifndef DRIVERS_8258_EXT_EXT_RF_H_
#define DRIVERS_8258_EXT_EXT_RF_H_

#include "tl_common.h"

#define	RF_BLE_PACKET_VALIDITY_CHECK(p)		(RF_BLE_PACKET_LENGTH_OK(p) && RF_BLE_PACKET_CRC_OK(p))

/* Different process for different MCU: ******************************************/
/*
 * While rf rx dma fifo is moving data,audio dma fifo is also moving data.
 * The rx fifo dma length may not be updated, instead, write to other ram addresses.
 * Result in ble disconnection.
 * Need to write rx dma write_num_en 0,And use the new crc verification method.
 */
#ifndef FIX_RF_DMA_REWRITE
#define FIX_RF_DMA_REWRITE					0 //Kite/Vulture not have this HW problem,Eagle A0 must open it
#endif
/**********************************************************************************/


#define reg_rf_ll_ctrl3			REG_ADDR8(0xf16)
enum{
	FLD_RF_R_TX_EN_DLY_EN         =	BIT(0),
	FLD_RF_R_PLL_RESET_EN         =	BIT(1),
	FLD_RF_R_CMD_SCHDULE_EN       =	BIT(2),
	FLD_RF_R_PLL_EN_MAN           =	BIT(3),
	FLD_RF_R_T_TX_EN_DLY          =	BIT_RNG(4,7),
};

#define reg_rf_ll_cmd_schedule   	reg_rf_ll_cmd_sch //REG_ADDR32(0xf18)
#define reg_rf_ll_rx_fst_timeout	reg_rf_rx_1st_timeout //REG_ADDR32(0xf28)


/**
 * @brief    This function serves to enable zb_rt[telink's ble irq entry] interrupt source.
 * @return  none
 */
static inline void zb_rt_irq_enable(void)
{
	reg_irq_mask |= FLD_IRQ_ZB_RT_EN;
}

/**
 * @brief    This function serves to disable zb_rt [telink's ble irq entry] interrupt source.
 * @return  none
 */
static inline void zb_rt_irq_disable(void)
{
	reg_irq_mask &= ~FLD_IRQ_ZB_RT_EN;
}

static inline void ble_rf_set_rx_dma(unsigned char *buff, unsigned char fifo_size_div_16)
{
	reg_dma_rf_rx_addr = (u16)(u32)buff;
	reg_dma_rf_rx_size = fifo_size_div_16;
}

static inline void ble_rf_set_tx_dma(unsigned char fifo_dep, unsigned char fifo_byte_size)
{

}

/**
 * @brief   	This function serves to judge the statue of  RF receive.
 * @return  	none.
 */
static inline unsigned char rf_receiving_flag(void)
{
	//if the value of [5:4] of the reg_0x448 is 0b10 or 0b11, it means that the RF is in the receiving packet phase.(confirmed by junwen)
	return (((read_reg8(0x448)>>5)& 1) == 1);
}

/**
 * @brief   This function serves to settle adjust for RF Tx.
 * @param   txstl_us - adjust TX settle time.
 * @return  none
 */
static inline void 	rf_tx_settle_adjust(unsigned short txstl_us)
{
	REG_ADDR16(0xf04) = txstl_us;
}

/**
 * @brief  	   This function serves to set the max length of rx packet.Use byte_len to limit what DMA
 * 			   moves out will not exceed the buffer size we define.And old chip do this through dma size.
 * @param[in]  byte_len  the longest of rx packet.
 * @return     none.
 */
static inline void rf_set_rx_maxlen(unsigned int byte_len)
{
	REG_ADDR8(0x431) = byte_len; //#define reg_rf_rxtmaxlen			REG_ADDR8(0x431)
}

/**
 * @brief   This function serves to triggle accesscode in coded Phy mode.
 * @param   none.
 * @return  none.
 */
static inline void rf_trigle_codedPhy_accesscode(void)
{
	WRITE_REG8(0x405, REG_ADDR8(0x405) | BIT(7));
}

#endif

