/********************************************************************************************************
 * @file	device_manage.h
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
#ifndef APP_DEVICE_H_
#define APP_DEVICE_H_


#include "vendor/common/user_config.h"


#ifndef MASTER_MAX_NUM
#define MASTER_MAX_NUM         						4
#endif

#ifndef SLAVE_MAX_NUM
#define SLAVE_MAX_NUM     							4
#endif

#ifndef BLE_MASTER_SIMPLE_SDP_ENABLE
#define BLE_MASTER_SIMPLE_SDP_ENABLE				0
#endif



#if (BLE_MASTER_SIMPLE_SDP_ENABLE)
	#ifndef PEER_SLAVE_USE_RPA_EN
	#define PEER_SLAVE_USE_RPA_EN					0	//peer slave device use RPA(resolvable private address)
	#endif

	#ifndef FLASH_SDP_ATT_ADRRESS
	#define FLASH_SDP_ATT_ADRRESS                	0xF6000    //for master: store peer slave device's ATT handle
	#endif

	#ifndef FLASH_SDP_ATT_MAX_SIZE
	#define FLASH_SDP_ATT_MAX_SIZE				 	(2*4096)   //8K flash for ATT HANLDE storage
	#endif
#endif





#define DEVICE_CHAR_INFO_MAX_NUM		(MASTER_MAX_NUM + SLAVE_MAX_NUM)    //4 master, 3 slave most



#define CHAR_HANDLE_MAX					8
/***************** connection character device information ****************************
 *
 * Demo master device char_handle(ATT handle) define as follows, assuming that peer device(BLE slave) is TELINK HID device
 *   char_handle[0] :  MIC
 *   char_handle[1] :  Speaker
 *   char_handle[2] :  OTA
 *   char_handle[3] :  Consume Report In
 *   char_handle[4] :  Key Report In
 *   char_handle[5] :
 *   char_handle[6] :  BLE Module, SPP Server to Client
 *   char_handle[7] :  BLE Module, SPP Client to Server
 *************************************************************************************/

typedef struct {
	u8 id_adrType;					//identity address type
	u8 id_addr[6];					//identity address
	u8 reserved;
	u8 irk[16];
} rpa_addr_t;



//Attention: manual set 4 byte aligned
typedef struct
{
	u16 	conn_handle;
	u8 		conn_state;				// 1: connect;  0: disconnect
	u8		char_handle_valid;      // 1: peer device's attHandle is available;   0: peer device's attHandle not available

	u8		rsvd[4];  				//just for debug, 16 byte aligned, convenient to see

	u8		peer_adrType;
	u8		peer_addr[6];
	u8		peer_RPA;         //RPA: resolvable private address
	//rpa_addr_t *pPeer_RPA;    //only when peer  mac_address is RPA, this pointer is useful

#if 0   //for local multi_mac_address
	u8		local_adrType;
	u8		local_addr[6];
	u8		local_RPA;        //RPA: resolvable private address
	//rpa_addr_t *pLocal_RPA;   //only when local mac_address is RPA, this pointer is useful
#endif

	u16		char_handle[CHAR_HANDLE_MAX];

}dev_char_info_t;


extern dev_char_info_t	conn_dev_list[];


extern int	conn_master_num;
extern int	conn_slave_num;

/**
 * @brief       Used for add device information to conn_dev_list.
 * @param[in]   dev_char_info       - Pointer point to data buffer.
 * @return      0: success
 *              1: failed
 */
int 	dev_char_info_insert (dev_char_info_t* dev_char_info);

/**
 * @brief       Used for add peer device service ATThandle.
 * @param[in]   dev_char_info       - Pointer point to data buffer.
 * @return      0: success
 *              1: failed
 */
int 	dev_char_info_add_peer_att_handle (dev_char_info_t* dev_char_info);

/**
 * @brief       Used for delete device information from conn_dev_list by connHandle
 * @param[in]   connhandle       - connection handle.
 * @return      0: success
 *              1: no find
 */
int 	dev_char_info_delete_by_connhandle (u16 connhandle);

/**
 * @brief       Used for delete device information from conn_dev_list by peer mac_address
 * @param[in]   adr_type       - peer address type.
 * @param[in]   addr           - Pointer point to peer address.
 * @return      0: success
 *              1: no find
 */
int 	dev_char_info_delete_by_peer_mac_address (u8 adr_type, u8* addr);


/**
 * @brief       Get device information by  peer device address.
 * @param[in]   adr_type       - peer address type.
 * @param[in]   addr           - Pointer point to peer address.
 * @return      0: no find
 *             !0: found
 */
dev_char_info_t* 	dev_char_info_search_by_peer_mac_address (u8 adr_type, u8* addr);

/**
 * @brief       Get device information by connection handle.
 * @param[in]   connhandle       - connection handle.
 * @return      0: no find
 *             !0: found
 */
dev_char_info_t* 	dev_char_info_search_by_connhandle (u16 connhandle);

#if 0
/**
 * @brief       Delete device information by local address.
 * @param[in]   adr_type       - peer address type.
 * @param[in]   addr           - Pointer point to peer address.
 * @return      0: success
 *              1: no find
 */
int 	dev_char_info_delete_by_local_mac (u8 adr_type, u8* addr);

/**
 * @brief       Get device information by  local device address.
 * @param[in]   adr_type       - peer address type.
 * @param[in]   addr           - Pointer point to peer address.
 * @return      0: no find
 *             !0: found
 */
dev_char_info_t* 	dev_char_info_search_by_local_mac (u8 adr_type, u8* addr);
#endif

/**
 * @brief       Used for judge if current device conn_handle
 * @param[in]   connhandle       - connection handle.
 * @return
 */
bool	dev_char_info_is_connection_state_by_conn_handle(u16 connhandle);


#if 0
static inline u16 	dev_char_info_get_conn_handle_by_slave_index (int slave_index)
{
	return conn_dev_list[slave_index].conn_handle;
}


static inline u16 	dev_char_info_get_conn_handle_by_master_index (int master_index)
{
	return conn_dev_list[master_index].conn_handle;
}
#endif












#if (BLE_MASTER_SIMPLE_SDP_ENABLE)

#define ATT_BOND_MARK 		0x5A
#define ATT_ERASE_MARK		0x00


typedef struct{
	u8	flag;
	u8	adr_type;
	u8	addr[6];

	u8	rsvd[8];  //very important: 16 byte aligned, to avoid different flash page write for a sequence data

#if (PEER_SLAVE_USE_RPA_EN)
	u8  irk[16];   //TODO: if peer device mac_adress is RPA(resolvable private address), IRK will be used
#endif

	u16	char_handle[CHAR_HANDLE_MAX];
}dev_att_t;


/**
 * @brief       Use for store peer device att handle to flash.
 * @param[in]   dev_char_info    Pointer point to peer device ATT handle info.
 * @return      0: failed
 *             !0: return falsh address
 */
int		dev_char_info_store_peer_att_handle(dev_char_info_t* dev_char_info);

/**
 * @brief       Get peer device att handle info by peer address
 * @param[in]   adr_type         address type
 * @param[in]   addr             Pointer point to peer address buffer
 * @param[out]  dev_att          Pointer point to dev_att_t
 * @return      0: failed
 *             !0: return falsh address
 */
int		dev_char_info_search_peer_att_handle_by_peer_mac(u8 adr_type, u8* addr, dev_att_t * dev_att);


/**
 * @brief       Delete peer device att handle info by peer address
 * @param[in]   adr_type         address type
 * @param[in]   addr             Pointer point to peer address buffer
 * @return      0: success
 *              1: not find
 */
int		dev_char_info_delete_peer_att_handle_by_peer_mac(u8 addrType, u8 *addr);

#endif












#endif /* APP_DEVICE_H_ */
