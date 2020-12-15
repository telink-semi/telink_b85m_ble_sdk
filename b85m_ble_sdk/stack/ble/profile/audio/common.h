/********************************************************************************************************
 * @file	common.h
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
#ifndef _COMMON_H_
#define _COMMON_H_

#if (AUDIO_PROFILE_EN)


#define AudioWord8ArrayIsEqual(array, word)   ((array)[0] == ((word) & 0xFF) && (array)[1] == (((word) & 0xFF00)>>8))
#define AudioIsThisUUID2(uuid, value)         AudioWord8ArrayIsEqual(uuid, value)

#define AudioValueSplit3Array(Array, value) \
	(Array)[0] = (value) & 0xFF; \
	(Array)[1] = ((value) & 0xFF00) >> 8; \
	(Array)[2] = ((value) & 0xFF0000) >> 24; 
	

typedef struct{
	u16 handle;
	u8 uuidLen;
	u8 dataLen;
	u8 *pCCC;
	u8 *pUuid;
	u8 *pData;
}audio_char_param_t;
typedef struct{
	u8  isValid;
	u8  cccValue;
	u16 charUUID;
	u16 dataHandle;
	u16 cccHandle;
//	u16 sAttHandle;
//	u16 eAttHandle;
}audio_char_sdp_t;

static inline u8 blc_audioGetBitCount(u32 value)
{
	u8 count;
	
	count = 0;
	while(value){
		count ++;
		value &= (value-1);
	}
	
	return count;
}

u8 blc_audioFindNextChar(attribute_t *pServer, u8 *pOffset, 
	                      audio_char_param_t *pParam);

ble_sts_t blc_audioPushHandleValue(u16 connHandle, u16 attHandle, u8 opcode, u8 *p, int len);


int blc_audioSendEvent(u16 evtID, u16 dataLen, u8 *pData);


#if (AUDIO_SDP_ENABLE)

u8 blc_audioSdpIsStart(void);
u8 blc_audioSdpIsValid(void);

u8 blc_audioSdpIsBusy(void);
int blc_audioSdpSetParam(u16 handle, u16 srvUuid, u16 charCount, u16 *pCharUUID);
int blc_audioSdpStart(u16 handle, u16 timeout); //timeout: ms
void blc_audioSdpStop(u16 handle);
int blc_audioGattDataHandler(u16 connHandle, u8 *p);

void blc_audioSdpHandler(void);
#endif //AUDIO_SDP_ENABLE


#endif //AUDIO_PROFILE_EN

#endif //_COMMON_H_

