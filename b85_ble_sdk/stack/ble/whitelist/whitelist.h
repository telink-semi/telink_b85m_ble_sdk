/********************************************************************************************************
 * @file	whitelist.h
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
#ifndef LL_WHITELIST_H_
#define LL_WHITELIST_H_



/**
 * @brief      reset whitelist
 * @param[in]  none
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t ll_whiteList_reset(void);


/**
 * @brief      add a device form whitelist
 * @param[in]  type - device mac address type
 * @param[in]  addr - device mac address
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t ll_whiteList_add(u8 type, u8 *addr);


/**
 * @brief      delete a device from whitelist
 * @param[in]  type - device mac address type
 * @param[in]  addr - device mac address
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t ll_whiteList_delete(u8 type, u8 *addr);


/**
 * @brief      get whitelist size
 * @param[out] pointer to size
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t ll_whiteList_getSize(u8 *returnPublicAddrListSize) ;


/**
 * @brief      reset resolvinglist
 * @param[in]  none
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t  ll_resolvingList_reset(void);


/**
 * @brief      add a device to resolvinglist
 * @param[in]  peerIdAddrType - device mac address type
 * @param[in]  peerIdAddr - device mac address
 * @param[in]  peer_irk - peer IRK pointer
 * @param[in]  local_irk - local IRK pointer
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t  ll_resolvingList_add(u8 peerIdAddrType, u8 *peerIdAddr, u8 *peer_irk, u8 *local_irk);


/**
 * @brief      delete a device from resolvinglist
 * @param[in]  peerIdAddrType - device mac address type
 * @param[in]  peerIdAddr - device mac address
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t  ll_resolvingList_delete(u8 peerIdAddrType, u8 *peerIdAddr);


/**
 * @brief      enable resolvinglist resolution
 * @param[in]  resolutionEn - 1: enable; 0:disable
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t  ll_resolvingList_setAddrResolutionEnable (u8 resolutionEn);




#endif /* LL_WHITELIST_H_ */
