/********************************************************************************************************
 * @file	struct.h
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
#ifndef _STRUCT_H_
#define _STRUCT_H_


#if (AUDIO_PROFILE_EN)



typedef int(*AudioEventCallback)(u16 evtID, u16 dataLen, u8 *pData);
typedef struct audio_ase_s audio_ase_t;


typedef struct{
	u8 format; //Coding Format of the [ith] PAC record. refer BAP_CODECID_FORMAT_ENUM
	u16 companyID; //Company_ID value of the [ith] PAC record.  Shall be ignored if octet 0 is not 0xFF
	u16 vendorID; //Vendor-specific codec_ID value of the [ith] PAC record. Shall be ignored if octet 0 is not 0xFF
}audio_codec_id_t;


typedef struct{
	u16 connHandle;
	u16 ctrlHandle; //att handle
	u8  aseNum;
	audio_ase_t *pAse;
}audio_event_enable_t;
typedef struct{
	u16 connHandle;
	u16 ctrlHandle; //att handle
	u8  aseNum;
	u16 context;
}audio_event_update_t;
typedef struct{
	u16 connHandle;
	u16 ctrlHandle; //att handle
	u8  aseNum;
}audio_event_disable_t, audio_event_release_t;
typedef struct{
	u16 connHandle;
	u16 ctrlHandle; //att handle
	u8  aseNum;
}audio_event_recvstart_t, audio_event_recvstop_t;


typedef struct{
	u8 mute;
	u8 volume;
}audio_event_spkvol_change_t;

typedef struct{
	u8 numb;
	u8 mute;
	u8 volume;
}audio_event_micvol_change_t;

////////////////////////////////////////////////////////////////////////
#if 0
typedef struct{
	u16 charUUID;
	u16 cccHandle; 
	u16 cccValue;
	u8 maxLen;
	u8 dataLen;
	u16 dataOffset;
	u16 dataHandle;
}audio_sdp_t;

typedef struct{
	#if (AUDIO_MCP_ENABLE)
	audio_sdp_t sdp[1];
	#else
	u32 recv;
	#endif
}audio_slave_t;
typedef struct{
	u32 resv;
}audio_master_t;
#endif
struct audio_ase_s{ // 36Bytes
	// APP Param 
	u8  codecId[5];
	u8  direction;
	u8  frequency;
	u8  duration;
	u16 context;  // Metadata
	u16 frameOcts;
	u32 location;
	
	// Link Layer Param
	u8  cigID;
	u8  cisID;
	u8  PHY;
	u8  RTN; //Retransmission_Number
	u16 maxSDU;
	u16 latency;
	u8  framing;
	u8  delay[3];
	u8  interval[3];
	//
	u8  state;
	u16 flags;
	u16 avaContext;
};


typedef struct{
	u8 isConn;
	u8 isSlave;
	u16 handle;
	u16 flags[AUDIO_SERVICE_TYPE_MAX];
	//union{
	//	u32 resv;
	//	audio_slave_t slave;
	//	audio_master_t master;
	//}u;
	#if (AUDIO_ASCP_ENABLE)
	audio_ase_t ase[AUDIO_ASE_MAX_COUNT];
	#endif // AUDIO_ASCP_ENABLE
}audio_handle_t;

typedef struct{
	AUDIO_SERVICE_TYPE type;
	void (*Handler)(audio_handle_t *pHandle);
	int (*SetService)(attribute_t *pService);
	int (*SetConnState)(audio_handle_t *pHandle, u8 isSlave, u8 connState);
}audio_ctrl_t;





#endif //AUDIO_PROFILE_EN

#endif //_STRUCT_H_

