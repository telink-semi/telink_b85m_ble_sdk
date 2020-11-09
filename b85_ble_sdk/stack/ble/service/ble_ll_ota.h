/********************************************************************************************************
 * @file	ble_ll_ota.h
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
#ifndef BLE_LL_OTA_H_
#define BLE_LL_OTA_H_


#define CMD_OTA_FW_VERSION					0xff00
#define CMD_OTA_START						0xff01
#define CMD_OTA_END							0xff02
#define CMD_OTA_VERSION_REQUEST				0xff10
#define CMD_OTA_VERSION_RESPONSE			0xff11
#define CMD_OTA_START_LONG_PACKET			0xff12
#define CMD_OTA_RESULT						0xff13


/**
 * @brief	OTA result
 */
enum{
	OTA_SUCCESS = 0,     	//success
	OTA_PACKET_LOSS,     	//lost one or more OTA PDU
	OTA_DATA_CRC_ERR,    	//data CRC err
	OTA_WRITE_FLASH_ERR,  	//write OTA data to flash ERR
 	OTA_DATA_UNCOMPLETE,  	//lost last one or more OTA PDU
 	OTA_TIMEOUT, 		  	//total timeout
	OTA_FW_CHECK_ERR,		//firmware CRC check error
	OTA_FW_TYPE_ERR,		//firmware type error
	OTA_VERSION_NUMBER_ERR, //the version number to be update is lower than the current version
	OTA_PDU_LARGER_DLE,		//OTA PDU is larger than DLE supported
	OTA_PDU_ERR,			//OTA PDU is not equal to 64 or 128
 	OTA_RF_PACKET_TIMEOUT,	//timeout between RF packet
	OTA_IS_DOING,			//OTA is running, only one device can run OTA at the same time.
};


/**
 * @brief	Telink defined OTA start Callback Declaration
 */
typedef void (*ota_startCb_t)(void);

/**
 * @brief	Telink defined OTA version Callback Declaration
 */
typedef void (*ota_versionCb_t)(void);

/**
 * @brief		Telink defined OTA result indicate Callback Declaration
 * @param[in]   result - OTA result
 */
typedef void (*ota_resIndicateCb_t)(int result);




/**
 * @brief      This function is used to register OTA start command callback
 * @param[in]  cb - callback function
 * @return     none
 */
void bls_ota_registerStartCmdCb(ota_startCb_t cb);

/**
 * @brief      This function is used to register OTA version command callback
 * @param[in]  cb - callback function
 * @return     none
 */
void bls_ota_registerVersionReqCb(ota_versionCb_t cb);

/**
 * @brief      This function is used to register OTA result callback
 * @param[in]  cb - callback function
 * @return     none
 */
void bls_ota_registerResultIndicateCb(ota_resIndicateCb_t cb);

/**
 * @brief      This function is used to set OTA timeout
 * @param[in]  timeout_us - timeout value, unit: uS
 * @return     none
 */
void bls_ota_setTimeout(u32 timeout_us);

/**
 * @brief		Telink defined OTA write callback
 * @param[in]   *p - rf_packet_att_write_t/rf_packet_att_executeWriteReq_t
 */
extern int otaWrite(u16 connHandle, void * p);

/**
 * @brief		Telink defined OTA read callback
 * @param[in]   *p - rf_packet_att_readBlob_t
 */
extern int otaRead(u16 connHandle, void * p);

//firmware_size_k  must be 4k aligned
/**
 * @brief      This function is used to set maximum firmware size and OTA boot address except address 0
 * @param[in]  firmware_size_k - maximum firmware size, unit: K Byte, must 4K Byte aligned
 * @param[in]  boot_addr - timeout value, unit: uS
 * @return     none
 */
void bls_ota_set_fwSize_and_fwBootAddr(int firmware_size_k, int boot_addr);


/**
 * @brief      This function is used to clear OTA firmware data buffer, ready for next OTA
 * 			   this must be done after every OTA
 * @param[in]  none
 * @return     none
 */
void bls_ota_clearNewFwDataArea(void);


/**
 * @brief      CRC16 used in OTA data check.
 * 			   this must be done after every OTA
 * @param[in]  *pD - data buffer address
 * @param[in]  *len - data length
 * @return     none
 */
unsigned short crc16 (unsigned char *pD, int len);

#endif /* BLE_LL_OTA_H_ */
