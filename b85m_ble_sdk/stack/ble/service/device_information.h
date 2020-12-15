/********************************************************************************************************
 * @file	device_information.h
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
#pragma once

#include "tl_common.h"
#include "../ble_common.h"


/** @addtogroup  TELINK_BLE_STACK TELINK BLE Stack
 *  @{
 */

/** @addtogroup  SERVICE_MODULE Service
 *  @{
 */


/** @addtogroup  DEVICE_INFO_Module Device Information
 *  @{
 */
 
/** @addtogroup  DEVICE_INFO_Constant Device Information Constants
 *  @{
 */

/**
 *  @brief  Definition for Characteristics UUID
 */

/** @addtogroup device_char_uuid Device Information Characteristc UUID
 * @{
 */

#define CHARACTERISTIC_UUID_MANU_NAME_STRING                    0x2A29
#define CHARACTERISTIC_UUID_MODEL_NUM_STRING                    0x2A24
#define CHARACTERISTIC_UUID_SERIAL_NUM_STRING                   0x2A25
#define CHARACTERISTIC_UUID_HW_REVISION_STRING                  0x2A27
#define CHARACTERISTIC_UUID_FW_REVISION_STRING                  0x2A26
#define CHARACTERISTIC_UUID_SW_REVISION_STRING                  0x2A28
#define CHARACTERISTIC_UUID_SYSTEM_ID                           0x2A23
#define CHARACTERISTIC_UUID_IEEE_11073_CERT_LIST                0x2A2A
#define CHARACTERISTIC_UUID_PNP_ID                              0x2A50

/** @} end of group device_char_uuid */


/** @addtogroup  IEEE_AUTHORITATIVE_BODY_VALUES IEEE Authoritative Body Values
 *  @{
 */

/**
 *  @brief  IEEE 11073 authoritative body values
 */
#define IEEE_11073_BODY_EMPTY                                   0
#define IEEE_11073_BODY_IEEE                                    1
#define IEEE_11073_BODY_CONTINUA                                2
#define IEEE_11073_BODY_EXP                                     254

/** @} end of group IEEE_AUTHORITATIVE_BODY_VALUES */




/** @addtogroup  SYSTEM_ID_LEN System Id Len
 *  @{
 */

/**
 *  @brief  Definition for System ID length
 */
#define SYSTEM_ID_LEN                                           8

/** @} end of group SYSTEM_ID_LEN */



/** @addtogroup  PNP_ID_LEN PnP ID Len
 *  @{
 */

/**
 *  @brief  Definition for PnP ID length
 */
#define DEVINFO_PNP_ID_LEN                                      7

/** @} end of group PNP_ID_LEN */

/** @} end of group DEVICE_INFO_Constant */



 /** @addtogroup  DEVICE_INFORMATION_Variables Device Information Variables
 *  @{
 */

/**
 *  @brief  External variable for device information Attribute tables
 */

extern  attribute_t devInfo_attrTbl[];

/**
 *  @brief  External variable for device information attribute size
 */
extern u16         devInfo_attrSize;

/** @} end of group DEVICE_INFORMATION_Variables */




 /** @addtogroup  PUBLIC_FUNCTION Device Information APIs
 *  @{
 */



/** @} end of group PUBLIC_FUNCTION */

/** @} end of group DEVICE_INFO_Module */

/** @} end of group SERVICE_MODULE */

/** @} end of group TELINK_BLE_STACK */
