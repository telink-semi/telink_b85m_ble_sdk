/********************************************************************************************************
 * @file	phy.h
 *
 * @brief	This is the header file for BLE SDK
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
#ifndef PHY_H_
#define PHY_H_

#include "stack/ble/hci/hci_cmd.h"

/**
 * @brief      this function is used to initialize 2M/Coded PHY  feature
 * @param	   none
 * @return     none
 */
void		blc_ll_init2MPhyCodedPhy_feature(void);


/**
 * @brief       this function is used to allows the Host to specify its preferred values for the transmitter PHY and
 *              receiver PHY to be used for all subsequent connections over the LE transport.
 * @param[in]	all_phys - Reference structure: le_phy_prefer_mask_t:
 *                         bit0: The Host has no preference among the transmitter PHYs supported by the Controller
 *                         bit1: The Host has no preference among the receiver PHYs supported by the Controller
 *                         All other bits: Reserved for future use
 * @param[in]	tx_phys - Reference structure: le_phy_prefer_mask_t:
 *                         bit0: The Host prefers to use the LE 1M transmitter PHY (possibly among others)
 *                         bit1: The Host prefers to use the LE 2M transmitter PHY (possibly among others)
 *                         bit2: The Host prefers to use the LE Coded transmitter PHY (possibly among others)
 *                         All other bits: Reserved for future use
 * @param[in]	rx_phys - Reference structure: le_phy_prefer_mask_t
 * @return      status, 0x00:  succeed
 * 					    other: failed
 */
ble_sts_t 	blc_ll_setDefaultPhy(le_phy_prefer_mask_t all_phys, le_phy_prefer_type_t tx_phys, le_phy_prefer_type_t rx_phys);


/**
 * @brief       this function is used to read the current transmitter PHY and receiver PHY on the connection identified
 *              by the Connection_Handle.
 * @param[in]	connHandle - Connection_Handle Range:0x0000 to 0x0EFF
 * @param[out]	para - Reference structure: hci_le_readPhyCmd_retParam_t:
 * 					   Status -  0x00 HCI_LE_Read_PHY command succeeded; 0x01 to 0xFF: HCI_LE_Read_PHY command failed
 * 					   Connection_Handle - Connection_Handle Range:0x0000 to 0x0EFF
 *					   TX_PHY - 1:LE 1M; 2: LE 2M; 3: LE Coded.
 *					   RX_PHY - 1:LE 1M; 2: LE 2M; 3: LE Coded.
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t	blc_ll_readPhy( u16 connHandle, hci_le_readPhyCmd_retParam_t *para);


/**
 * @brief       this function is used to set PHY type for connection
 * @param[in]	connHandle - Connection_Handle Range:0x0000 to 0x0EFF
 * @param[in]	all_phys - preference PHY for TX & RX
 * @param[in]	tx_phys - preference PHY for TX
 * @param[in]	rx_phys - preference PHY for RX
 * @param[in]	phy_options - LE coding indication prefer
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t  	blc_ll_setPhy (	u16 connHandle,					le_phy_prefer_mask_t all_phys,
							le_phy_prefer_type_t tx_phys, 	le_phy_prefer_type_t rx_phys,
							le_ci_prefer_t phy_options);


/**
 * @brief       this function is used to set PHY type for connection, same as API: blc_ll_setPhy
 * @param[in]	connHandle - Connection_Handle Range:0x0000 to 0x0EFF
 * @param[in]	all_phys - preference PHY for TX & RX
 * @param[in]	tx_phys - preference PHY for TX
 * @param[in]	rx_phys - preference PHY for RX
 * @param[in]	phy_options - LE coding indication prefer
 * @return     status, 0x00:  succeed
 * 					   other: failed
 */
ble_sts_t 	blc_hci_le_setPhy(hci_le_setPhyCmd_param_t* para);



/**
 * @brief       This function is used to set LE Coded PHY preference, S2 or S8, or no specific preference.
 * @param[in]	prefer_CI - Reference structure: hci_le_readPhyCmd_retParam_t.
 * @return      status, 0x00:  succeed
 * 					    other: failed
 */
ble_sts_t	blc_ll_setDefaultConnCodingIndication(le_ci_prefer_t prefer_CI);


/**
 * @brief       This function is used to Get the PHY of the specified connection
 * @param[in]	connHandle -  Connection_Handle Range:0x0000 to 0x0EFF
 * @return      le_phy_type_t
 */
le_phy_type_t blc_ll_getAclConnPhy(u16 connHandle);







#endif /* PHY_H_ */
