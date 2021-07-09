/********************************************************************************************************
 * @file	ota.h
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
#ifndef OTA_H_
#define OTA_H_


/**
 * @brief 	Legacy OTA command
 */
#define CMD_OTA_VERSION						0xFF00	//client -> server
#define CMD_OTA_START						0xFF01	//client -> server
#define CMD_OTA_END							0xFF02	//client -> server

/**
 * @brief 	Extended OTA command, optional
 */
#define CMD_OTA_START_EXT					0xFF03	//client -> server
#define CMD_OTA_FW_VERSION_REQ				0xFF04	//client -> server
#define CMD_OTA_FW_VERSION_RSP				0xFF05	//server -> client
#define CMD_OTA_RESULT						0xFF06	//server -> client


extern int	ota_program_bootAddr;
extern int	ota_program_offset;


/**
 * @brief 	Multiple boot address enumeration
 */
typedef enum{
	MULTI_BOOT_ADDR_0x20000 	= 0x20000,	//128 K
	MULTI_BOOT_ADDR_0x40000		= 0x40000,  //256 K
	MULTI_BOOT_ADDR_0x80000	    = 0x80000,  //512 K
}multi_boot_addr_e;



/**
 * @brief	OTA result
 */
enum{
	//0x00
	OTA_SUCCESS 			= 0,			//success
	OTA_DATA_PACKET_SEQ_ERR,				//OTA data packet sequence number error: repeated OTA PDU or lost some OTA PDU
	OTA_PACKET_INVALID,						//invalid OTA packet: 1. invalid OTA command; 2. addr_index out of range; 3.not standard OTA PDU length
	OTA_DATA_CRC_ERR,						//packet PDU CRC err

	//0x04
	OTA_WRITE_FLASH_ERR,					//write OTA data to flash ERR
 	OTA_DATA_UNCOMPLETE,					//lost last one or more OTA PDU
 	OTA_FLOW_ERR,		    				//peer device send OTA command or OTA data not in correct flow
 	OTA_FW_CHECK_ERR,						//firmware CRC check error

	//0x08
	OTA_VERSION_COMPARE_ERR,				//the version number to be update is lower than the current version
	OTA_PDU_LEN_ERR,						//PDU length error: not 16*n, or not equal to the value it declare in "CMD_OTA_START_EXT" packet
	OTA_FIRMWARE_MARK_ERR,		    		//firmware mark error: not generated by telink's BLE SDK
	OTA_FW_SIZE_ERR,						//firmware size error: no firmware_size; firmware size too small or too big

	//0x0C
	OTA_DATA_PACKET_TIMEOUT,	   			//time interval between two consequent packet exceed a value(user can adjust this value)
 	OTA_TIMEOUT,							//OTA flow total timeout
 	OTA_FAIL_DUE_TO_CONNECTION_TERMIANTE,	//OTA fail due to current connection terminate(maybe connection timeout or local/peer device terminate connection)
};




/**
 *  @brief data structure of OTA command "CMD_OTA_START"
 */
typedef struct {
	u16  	ota_cmd;
} ota_start_t;

/**
 *  @brief data structure of OTA command "CMD_OTA_START_EXT"
 */
typedef struct {
	u16  	ota_cmd;
	u8		pdu_length;			//must be: 16*n(n is in range of 1 ~ 15); pdu_length: 16,32,48,...240
	u8		version_compare;	//0: no version compare; 1: only higher version can replace lower version
} ota_startExt_t;


/**
 *  @brief data structure of OTA command "CMD_OTA_END"
 */
typedef struct {
	u16  	ota_cmd;
	u16		adr_index_max;
	u16		adr_index_max_xor;
} ota_end_t;


/**
 *  @brief data structure of OTA command "CMD_OTA_RESULT"
 */
typedef struct {
	u16  	ota_cmd;
	u8		result;
} ota_result_t;



/**
 *  @brief data structure of OTA command "CMD_OTA_FW_VERSION_REQ"
 */
typedef struct {
	u16  	ota_cmd;
	u16		version_num;
	u8		version_compare;   //1: only higher version can replace lower version
} ota_versionReq_t;


/**
 *  @brief data structure of OTA command "CMD_OTA_FW_VERSION_RSP"
 */
typedef struct {
	u16  	ota_cmd;
	u16		version_num;
	u8		version_accept;      //1: accept firmware update; 0: reject firmware update(version compare enable, and compare result: fail)
} ota_versionRsp_t;



typedef struct{
	u16 adr_index;
	u8	data[16];
	u16 crc_16;
}ota_pdu16_t;


unsigned long crc32_half_cal(unsigned long crc, unsigned char* input, unsigned long* table, int len);
unsigned long crc32_cal(unsigned long crc, unsigned char* input, unsigned long* table, int len);



#endif /* OTA_H_ */
