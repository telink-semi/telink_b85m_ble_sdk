/********************************************************************************************************
 * @file	ble_controller.h
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
#ifndef BLE_CONTROLLER_H_
#define BLE_CONTROLLER_H_


#include "ble_common.h"
#include "ble_format.h"


#include "hci/hci.h"
#include "hci/hci_const.h"
#include "hci/hci_cmd.h"
#include "hci/hci_event.h"
#include "hci/usb_desc.h"

#include "ll/ll.h"

#include "ll/acl_conn/acl_conn.h"
#include "ll/acl_conn/acl_slave.h"
#include "ll/acl_conn/acl_master.h"


#include "ll/adv/adv.h"
#include "ll/adv/leg_adv.h"
#include "ll/adv/ext_adv.h"
#include "ll/adv/perd_adv.h"

#include "ll/scan/scan.h"
#include "ll/scan/leg_scan.h"
#include "ll/scan/ext_scan.h"
#include "ll/scan/sync.h"

#include "ll/init/init.h"
#include "ll/init/leg_init.h"
#include "ll/init/ext_init.h"


#include "ial/ial.h"
#include "ll/iso/iso.h"

#include "ll/iso/bis.h"
#include "ll/iso/bis_bcst.h"
#include "ll/iso/bis_sync.h"
#include "ll/iso/cis.h"
#include "ll/iso/cis_master.h"
#include "ll/iso/cis_slave.h"


#include "whitelist/whitelist.h"

#include "csa/csa.h"

#include "phy/phy.h"
#include "phy/phy_test.h"



/*********************************************************/
//Remove when file merge to SDK //
#include "ble_stack.h"
#include "ll/ll_stack.h"
#include "ll/acl_conn/acl_stack.h"
#include "ll/adv/adv_stack.h"
#include "ll/scan/scan_stack.h"
#include "ll/init/init_stack.h"
#include "ial/ial_stack.h"
#include "ll/iso/iso_stack.h"
#include "whitelist/whitelist_stack.h"
#include "csa/csa_stack.h"
#include "phy/phy_stack.h"

#include "ble_config.h"
#include "debug.h"
#include "trace.h"
/*********************************************************/

#endif /* BLE_H_ */
