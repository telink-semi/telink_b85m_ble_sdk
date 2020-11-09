/********************************************************************************************************
 * @file	ext_scan.h
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
#ifndef LL_SCAN_EXT_H_
#define LL_SCAN_EXT_H_

#include "stack/ble/hci/hci_cmd.h"






/**
 * @brief      for user to initialize extended scanning module
 * 			   notice that only one module can be selected between legacy scanning module and extended scanning module
 * @param	   none
 * @return     none
 */
void 		blc_ll_initExtendedScanning_module(void);









/**
 * @brief      set the extended scan parameters to be used on the advertising physical channels,
 *             scan_phys can be only 1M PHY or Coded PHY, but can not be both of them
 * @param[in]  ownAddrType - Own_Address_Type
 * @param[in]  scanFilterPolicy - Scanning_Filter_Policy
 * @param[in]  scan_phys - Scanning_PHYs, "SCAN_PHY_1M" or "SCAN_PHY_CODED"
 * @param[in]  scanType
 * @param[in]  scan_interval
 * @param[in]  scan_window
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t 	blc_ll_setExtScanParam ( own_addr_type_t  ownAddrType, 	scan_fp_type_t scanFilterPolicy,	scan_phy_t	scan_phys,
										   scan_type_t 	   	scanType,    	u16 		   scan_interval, 		u16 scan_window);



/**
 * @brief      set the extended scan parameters to be used on the advertising physical channels,
 *             scan_phys must be both 1M PHY and Coded PHY.
 * @param[in]  ownAddrType - Own_Address_Type
 * @param[in]  scanFilterPolicy - Scanning_Filter_Policy
 * @param[in]  scan_phys - Scanning_PHYs, LE 1M PHY or LE Coded PHY or both, must be "SCAN_PHY_1M_CODED"
 * @param[in]  scanType_0
 * @param[in]  scan_interval_0
 * @param[in]  scan_window_0
 * @param[in]  scanType_1
 * @param[in]  scan_interval_1
 * @param[in]  scan_window_1
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t 	blc_ll_setExtScanParam_2_phy ( own_addr_type_t  ownAddrType, 	scan_fp_type_t scanFilterPolicy,	scan_phy_t	scan_phys,
										   scan_type_t 	 	scanType_0,    	u16 		   scan_interval_0, 	u16 scan_window_0,
										   scan_type_t 	 	scanType_1,    	u16 		   scan_interval_1, 	u16 scan_window_1);




/**
 * @brief	   enable or disable extended scanning.
 * @param[in]  extScan_en
 * @param[in]  filter_duplicate
 * @param[in]  duration - Scan duration
 * @param[in]  period - Time interval from when the Controller started its last Scan_Duration until it begins the
 * 			   subsequent Scan_Duration.
 * @return     Status - 0x00: command succeeded; 0x01-0xFF: command failed
 */
ble_sts_t 	blc_ll_setExtScanEnable (scan_en_t  extScan_en, 	dupFilter_en_t filter_duplicate,	u16 duration,	u16 period);





#endif /* LL_SCAN_EXT_H_ */
