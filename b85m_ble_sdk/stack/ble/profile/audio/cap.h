/********************************************************************************************************
 * @file	cap.h
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
#ifndef _CAP_H_
#define _CAP_H_


#include "stack/ble/profile/audio/config.h"
#include "stack/ble/profile/audio/define.h"
#include "stack/ble/profile/audio/struct.h"
#include "stack/ble/profile/audio/common.h"
#include "stack/ble/profile/audio/handle.h"


#if (AUDIO_PROFILE_EN)


//#define AUDIO_BUFFER_NEEDLEN()   (AUDIO_HANDLE_COUNT*sizeof(audio_handle_t))


int blc_audioCapInit(void);
void blc_audioCapLoop(void);

int blc_audioRegisterEventCB(AudioEventCallback pCB);
bool blc_audioSetConnState(u16 connHandle, u8 isSlave, u8 connState); //connState: 0-disconn, 1-new conn, 2-reconn
int blc_audioSetService(AUDIO_SERVICE_TYPE srvType, attribute_t *pService);

#if (AUDIO_PACP_ENABLE)
extern int blc_audioPacpRead(u16 connHandle, void *p);
extern int blc_audioPacpWrite(u16 connHandle, void *p);
#endif //AUDIO_PACP_ENABLE

#if (AUDIO_ASCP_ENABLE)
extern int blc_audioAscpRead(u16 connHandle, void *p);
extern int blc_audioAscpWrite(u16 connHandle, void *p);
#endif //AUDIO_PACP_ENABLE


#if (AUDIO_CSIP_ENABLE)
extern int blc_audioCsipRead(u16 connHandle, void *p);
extern int blc_audioCsipWrite(u16 connHandle, void *p);
extern void blc_audioCsisGeneratePsri(u8 sirk[16], u8 prand[3], u8 psri[6]);
extern bool blc_audioCsisPsriIsResolved(u8 sirk[16], u8 psri[6]);
#endif //AUDIO_CSIP_ENABLE

#if (AUDIO_MICP_ENABLE)
extern int blc_audioMicpRead(u16 connHandle, void *p);
extern int blc_audioMicpWrite(u16 connHandle, void *p);
#endif //AUDIO_MICP_ENABLE

#if (AUDIO_VCP_ENABLE)
extern int blc_audioVcpRead(u16 connHandle, void *p);
extern int blc_audioVcpWrite(u16 connHandle, void *p);
#endif //AUDIO_VCP_ENBALE


#endif //AUDIO_PROFILE_EN

#endif //_CAP_H_

