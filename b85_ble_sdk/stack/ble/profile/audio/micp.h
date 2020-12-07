/********************************************************************************************************
 * @file	micp.h
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
#ifndef _MICP_H_
#define _MICP_H_

#if (AUDIO_MICP_ENABLE)


#define MICP_OPCODE_SET_GAIN                   0x01
#define MICP_OPCODE_UNMUTE                     0x02
#define MICP_OPCODE_MUTE                       0x03
#define MICP_OPCODE_MANUAL_MODE                0x04
#define MICP_OPCODE_AUTOMATIC_MODE             0x05

#define MICP_ERRCODE_INVALID_CHANGE_COUNTER    0x80
#define MICP_ERRCODE_OPCODE_NOT_SUPPPORTED     0x81
#define MICP_ERRCODE_MUTE_DISABLED             0x82
#define MICP_ERRCODE_VALUE_OUT_OF_RANGE        0x83
#define MICP_ERRCODE_MODE_CHANGE_NOT_ALLOWED   0x84


#define MICP_FLAG_BUSY                         0x0100
#define MICP_FLAG_EVENT                        0x0200

#define MICP_AI_STATE_CHANGE                   0x0001
#define MICP_AI_STATUS_CHANGE                  0x0002


typedef struct{
	u16 recv;
	u16 ctrlHandle;
	u16 stateHandle;
	u16 statusHandle;

	u8* pGainValue;
	u8* pStateValue;
	u8* pStatusValue;
	u8* pStateCCCValue;
	u8* pStatusCCCValue;
}aicp_ctrl_t;

typedef struct{
	u8  recv;
	u8  aicsCount;
	u16 muteHandle;
	u8* pMuteValue;
	aicp_ctrl_t aics[AUDIO_AICS_COUNT];
}micp_ctrl_t;


int blc_audioMicpRead(u16 connHandle, void *p);
int blc_audioMicpWrite(u16 connHandle, void *p);


#endif //AUDIO_MICP_ENBALE

#endif //_MICP_H_

