/********************************************************************************************************
 * @file	device_manage.c
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
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"

#include "device_manage.h"




/*
 * Used for store information of connected devices.
 *
 * 0 ~ (MASTER_MAX_NUM - 1) is for master,  MASTER_MAX_NUM ~ (MASTER_MAX_NUM + SLAVE_MAX_NUM - 1) s for slave
 *
 * e.g.    MASTER_MAX_NUM	SLAVE_MAX_NUM			master					  slave
 *                1				  1				conn_dev_list[0]		conn_dev_list[1]
 *                2				  2				conn_dev_list[0..1]		conn_dev_list[2..3]
 *                3				  2				conn_dev_list[0..2]		conn_dev_list[3..4]
 *                4				  3				conn_dev_list[0..3]		conn_dev_list[4..6]
 */
dev_char_info_t	conn_dev_list[DEVICE_CHAR_INFO_MAX_NUM];

/*
 * Special Design: when a device connection terminate, e.g. device index is 1, we will not only remove conn_dev_list[1],
 * 				   but also copy conn_dev_list[2] (assume that this device is in connection state) to conn_dev_list[1],
 * 				   			copy conn_dev_list[3] (assume that this device is in connection state) to conn_dev_list[2],
 * 				   			......
 *
 * So for 4 master 3 slave demo, the relationship between device in connection state and conn_master_num/conn_slave_num is as follows��
 *
 * 			conn_master_num	   					device in connection state
 *
 * 				   1		  						conn_dev_list[0]
 * 				   2								conn_dev_list[0]/conn_dev_list[1]
 * 				   3								conn_dev_list[0]/conn_dev_list[1]/conn_dev_list[2]
 * 				   4								conn_dev_list[0]/conn_dev_list[1]/conn_dev_list[2]/conn_dev_list[3]
 *
 * 			conn_slave_num
 *
 * 				   1		  						conn_dev_list[4]
 * 				   2								conn_dev_list[4]/conn_dev_list[5]
 * 				   3								conn_dev_list[4]/conn_dev_list[5]/conn_dev_list[6]
 *
 *     			.conn_state must be 1, conn_dev_list[2].conn_state
 */
int conn_master_num = 0;   //current master number in connection state
int conn_slave_num = 0;    //current slave number in connection state






/**
 * @brief       Used for add device information to conn_dev_list.
 * @param[in]   dev_char_info       - Pointer point to data buffer.
 * @return      0: success
 *              1: failed
 */
int dev_char_info_insert (dev_char_info_t* dev_char_info)
{
	int index = 100;
	if( dev_char_info->conn_handle & BLM_CONN_HANDLE ){  //master
		if(conn_master_num < MASTER_MAX_NUM){
			index = conn_master_num;
			conn_master_num ++;
		}
	}
	else if( dev_char_info->conn_handle & BLS_CONN_HANDLE ){  //slave
		if(conn_slave_num < SLAVE_MAX_NUM){
			index = MASTER_MAX_NUM + conn_slave_num;
			conn_slave_num ++;
		}
	}

	if(index < MASTER_MAX_NUM + SLAVE_MAX_NUM){
		memcpy(&conn_dev_list[index], dev_char_info, sizeof(dev_char_info_t));
		conn_dev_list[index].conn_state = 1;

		return 0;   //success
	}
	else{
		return 1;   //fail
	}

}





/**
 * @brief       Used for add peer device service ATThandle.
 * @param[in]   dev_char_info       - Pointer point to data buffer.
 * @return      0: success
 *              1: failed
 */
int dev_char_info_add_peer_att_handle (dev_char_info_t* dev_char_info)
{
	int i;
	for(i=0; i< conn_master_num; i++){
		if( conn_dev_list[i].conn_handle == dev_char_info->conn_handle){
			break;
		}
	}

	if( i < conn_master_num){
		for(int j=0; j<CHAR_HANDLE_MAX;  j++){
			conn_dev_list[i].char_handle[j] = dev_char_info->char_handle[j];
		}

		conn_dev_list[i].char_handle_valid = 1;

		return 0;   //success
	}
	else{
		return 1;   //fail
	}
}




/**
 * @brief       Used for delete device information from conn_dev_list by connHandle
 * @param[in]   connhandle       - connection handle.
 * @return      0: success
 *              1: no find
 */
int dev_char_info_delete_by_connhandle (u16 connhandle)
{
	foreach (i, DEVICE_CHAR_INFO_MAX_NUM)
	{
		if(conn_dev_list[i].conn_handle == connhandle && conn_dev_list[i].conn_state)  //match
		{
//			memset(&conn_dev_list[i], 0, sizeof(dev_char_info_t));

			if(connhandle & BLM_CONN_HANDLE){   //master
				memcpy (&conn_dev_list[i], &conn_dev_list[i + 1], (conn_master_num - i - 1) * sizeof (dev_char_info_t));
				conn_master_num --;
				memset(&conn_dev_list[conn_master_num], 0, sizeof(dev_char_info_t));
			}
			else{  //slave
				memcpy (&conn_dev_list[i], &conn_dev_list[i + 1], (conn_slave_num + MASTER_MAX_NUM - i - 1) * sizeof (dev_char_info_t));
				conn_slave_num --;
				memset(&conn_dev_list[conn_slave_num + MASTER_MAX_NUM], 0, sizeof(dev_char_info_t));
			}

			return 0;
		}
	}
	return 1;  //no find the peer device address.
}


/**
 * @brief       Used for delete device information from conn_dev_list by peer mac_address
 * @param[in]   adr_type       - peer address type.
 * @param[in]   addr           - Pointer point to peer address.
 * @return      0: success
 *              1: no find
 */
int 	dev_char_info_delete_by_peer_mac_address (u8 adr_type, u8* addr)
{
	foreach (i, DEVICE_CHAR_INFO_MAX_NUM)
	{
		if(conn_dev_list[i].conn_state)
		{
			int mac_match = 0;
			if( IS_RESOLVABLE_PRIVATE_ADDR(adr_type, addr) ){
				//TODO
			}
			else{
				if(adr_type == conn_dev_list[i].peer_adrType && (!memcmp (addr, conn_dev_list[i].peer_addr, 6)) ){
					mac_match = 1;
				}
			}

			u16 connhandle = conn_dev_list[i].conn_handle;

			if(mac_match){
				if(connhandle & BLM_CONN_HANDLE){   //master
					memcpy (&conn_dev_list[i], &conn_dev_list[i + 1], (conn_master_num - i - 1) * sizeof (dev_char_info_t));
					memset(&conn_dev_list[conn_master_num], 0, sizeof(dev_char_info_t));
					conn_master_num --;
				}
				else{  //slave
					memcpy (&conn_dev_list[i], &conn_dev_list[i + 1], (conn_slave_num + MASTER_MAX_NUM - i - 1) * sizeof (dev_char_info_t));
					memset(&conn_dev_list[conn_slave_num + MASTER_MAX_NUM], 0, sizeof(dev_char_info_t));
					conn_slave_num --;
				}

				return 0;
			}

		}
	}

	return 1;  //no find the peer device address.
}







/**
 * @brief       Get device information by connection handle.
 * @param[in]   connhandle       - connection handle.
 * @return      0: no find
 *             !0: found
 */
dev_char_info_t* dev_char_info_search_by_connhandle (u16 connhandle)
{
	foreach (i, DEVICE_CHAR_INFO_MAX_NUM)
	{
		if(conn_dev_list[i].conn_handle == connhandle && conn_dev_list[i].conn_state)
		{
			return &conn_dev_list[i];   // find the peer device
		}
	}

	return 0;  // no find the peer device
}




/**
 * @brief       Get device information by  peer device address.
 * @param[in]   adr_type       - peer address type.
 * @param[in]   addr           - Pointer point to peer address.
 * @return      0: no find
 *             !0: found
 */
dev_char_info_t* dev_char_info_search_by_peer_mac_address (u8 adr_type, u8* addr)
{
	foreach (i, DEVICE_CHAR_INFO_MAX_NUM)
	{

		int mac_match = 0;
		if( IS_RESOLVABLE_PRIVATE_ADDR(adr_type, addr) ){
			//TODO
		}
		else{
			if(adr_type == conn_dev_list[i].peer_adrType && (!memcmp (addr, conn_dev_list[i].peer_addr, 6)) ){
				mac_match = 1;
			}
		}

		if(mac_match){
			return &conn_dev_list[i];   // find the peer device
		}
	}

	return 0;  // no find the peer device
}





/**
 * @brief       Get device information by connection handle.
 * @param[in]   connhandle       - connection handle.
 * @return      0: no find
 *             !0: found
 */
bool	dev_char_info_is_connection_state_by_conn_handle(u16 connhandle)
{
	foreach (i, DEVICE_CHAR_INFO_MAX_NUM)
	{
		if(conn_dev_list[i].conn_handle == connhandle && conn_dev_list[i].conn_state)
		{
			return TRUE;
		}
	}

	return FALSE;
}




#if (BLE_MASTER_SIMPLE_SDP_ENABLE)
/**
 * @brief       Use for store peer device att handle to flash.
 * @param[in]   dev_char_info    Pointer point to peer device ATT handle info.
 * @return      0: failed
 *             !0: return falsh address
 */
int		dev_char_info_store_peer_att_handle(dev_char_info_t* pdev_char)
{
	u8 mark;
	u32 current_flash_adr;
	for(current_flash_adr = FLASH_SDP_ATT_ADRRESS; current_flash_adr < (FLASH_SDP_ATT_ADRRESS + FLASH_SDP_ATT_MAX_SIZE); current_flash_adr += sizeof(dev_att_t) )
	{
		flash_read_page(current_flash_adr, 1, &mark);

		if( mark == U8_MAX){

			flash_write_page( current_flash_adr + OFFSETOF(dev_att_t, adr_type),  7, (u8 *)&pdev_char->peer_adrType);  // peer_adrType(1)+peer_addr(6)

#if (PEER_SLAVE_USE_RPA_EN)
			if( IS_RESOLVABLE_PRIVATE_ADDR(pdev_char->peer_adrType, pdev_char->peer_addr) ){
				//TODO, store irk to flash
			}
#endif

//			 char_handle[0] :  MIC
//			 char_handle[1] :  Speaker
//			 char_handle[2] :  OTA
//			 char_handle[3] :  Consume Report
//			 char_handle[4] :  Key Report
//			 char_handle[5] :
//			 char_handle[6] :  BLE Module, SPP Server to Client
//			 char_handle[7] :  BLE Module, SPP Client to Server
			flash_write_page( current_flash_adr + OFFSETOF(dev_att_t, char_handle) + 2*2,  2, (u8 *)&pdev_char->char_handle[2]);   //save OTA att_handle
			flash_write_page( current_flash_adr + OFFSETOF(dev_att_t, char_handle) + 3*2,  2, (u8 *)&pdev_char->char_handle[3]);   //save Consume Report att_handle
			flash_write_page( current_flash_adr + OFFSETOF(dev_att_t, char_handle) + 4*2,  2, (u8 *)&pdev_char->char_handle[4]);   //save Key Report att_handle

			mark = ATT_BOND_MARK;
			flash_write_page( current_flash_adr,  1, (u8 *)&mark);

			return current_flash_adr;  //Store Success
		}
	}






	return 0;  //Store Fail
}


/**
 * @brief       Get peer device att handle info by peer address
 * @param[in]   adr_type         address type
 * @param[in]   addr             Pointer point to peer address buffer
 * @param[out]  dev_att          Pointer point to dev_att_t
 * @return      0: failed
 *             !0: return falsh address
 */
int		dev_char_info_search_peer_att_handle_by_peer_mac(u8 adr_type, u8* addr, dev_att_t* pdev_att)
{


	u8 mark;
	u32 current_flash_adr;
	for(current_flash_adr = FLASH_SDP_ATT_ADRRESS; current_flash_adr < (FLASH_SDP_ATT_ADRRESS + FLASH_SDP_ATT_MAX_SIZE); current_flash_adr += sizeof(dev_att_t) )
	{
		flash_read_page(current_flash_adr, 1, &mark);

		if(mark == U8_MAX){
			return 0;   //Search Fail
		}
		else if(mark == ATT_ERASE_MARK){
			continue;   //Search for next unit
		}
		else if( mark == ATT_BOND_MARK)
		{
			flash_read_page(current_flash_adr, sizeof(dev_att_t), (u8 *)pdev_att);

			int addr_match = 0;
#if (PEER_SLAVE_USE_RPA_EN)
			if( IS_RESOLVABLE_PRIVATE_ADDR(pdev_att->adr_type, pdev_att->addr) ){
				//TODO, resolve address by irk
				if(0){
					addr_match = 1;
				}

			}
			else
#endif
			{
				if( adr_type == pdev_att->adr_type && !memcmp(addr, pdev_att->addr, 6 )){  //match
					addr_match = 1;
				}
			}

			if(addr_match){
				return current_flash_adr;
			}


		}


	}

	return 0;   //Search Fail

}

/**
 * @brief       Delete peer device att handle info by peer address
 * @param[in]   adr_type         address type
 * @param[in]   addr             Pointer point to peer address buffer
 * @return      0: success
 *              1: not find
 */
int dev_char_info_delete_peer_att_handle_by_peer_mac(u8 addrType, u8 *addr)
{
	dev_att_t dev_info;

	for(u32 cur_flash_addr = FLASH_SDP_ATT_ADRRESS;
		cur_flash_addr < FLASH_SDP_ATT_ADRRESS + FLASH_SDP_ATT_MAX_SIZE;
		cur_flash_addr += sizeof(dev_att_t))
	{
		u8 flag;
		flash_read_page(cur_flash_addr, 1, &flag);

		//have no device information
		if(flag == 0xff)
			return 1;//not find

		if(flag == ATT_BOND_MARK){
			//only read per device MAC address type and MAC address
			flash_read_page(cur_flash_addr, 8, (u8*)&dev_info);
		#if(PEER_SLAVE_USE_RPA_EN)
			if(IS_RESOLVABLE_PRIVATE_ADDR(addrType, addr)){
				//todo: resolve private address using IRK
			}
			else
		#endif
			{
				if(dev_info.adr_type == addrType && !memcmp(dev_info.addr, addr, 6)){
					u8 temp = ATT_ERASE_MARK;
					flash_write_page(cur_flash_addr, 1, (u8*)&temp);
					return 0;//find
				}
			}
		}
	}
	return 1;//not find
}


#endif  //end of BLE_MASTER_SIMPLE_SDP_ENABLE






