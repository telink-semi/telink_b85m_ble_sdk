/********************************************************************************************************
 * @file	handle.h
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
#ifndef _HANDLE_H_
#define _HANDLE_H_


#if (AUDIO_PROFILE_EN)


#define CAP_HANDLE_FILTER_NONE               0x00
#define CAP_HANDLE_FILTER_ONLY               0x80 //just myself
#define CAP_HANDLE_FILTER_COOR               0x40 //just myself and coordinated with me
#define CAP_HANDLE_FILTER_CONN               0x01
#define CAP_HANDLE_FILTER_SLAVE              0x02
#define CAP_HANDLE_FILTER_MASTER             0x04
#define CAP_HANDLE_FILTER_SLAVE_CONN         (CAP_HANDLE_FILTER_SLAVE|CAP_HANDLE_FILTER_CONN)
#define CAP_HANDLE_FILTER_MASTER_CONN        (CAP_HANDLE_FILTER_MASTER|CAP_HANDLE_FILTER_CONN)
#define CAP_HANDLE_FILTER_COOR_CONN          (CAP_HANDLE_FILTER_COOR|CAP_HANDLE_FILTER_CONN)
#define CAP_HANDLE_FILTER_SLAVE_COOR_CONN    (CAP_HANDLE_FILTER_SLAVE|CAP_HANDLE_FILTER_COOR|CAP_HANDLE_FILTER_CONN)
#define CAP_HANDLE_FILTER_MASTER_COOR_CONN   (CAP_HANDLE_FILTER_MASTER|CAP_HANDLE_FILTER_COOR|CAP_HANDLE_FILTER_CONN)


audio_handle_t *blc_audioGetHandle(void);
audio_handle_t *blc_audioFindHandle(u16 handle);
void blc_audioSetFlag(u16 handle, u16 filter, u16 flag, AUDIO_SERVICE_TYPE srvType);
void blc_audioAddFlag(u16 handle, u16 filter, u16 flag, AUDIO_SERVICE_TYPE srvType);
void blc_audioClrFlag(u16 handle, u16 filter, u16 flag, AUDIO_SERVICE_TYPE srvType);


#endif //AUDIO_PROFILE_EN

#endif //_HANDLE_H_

