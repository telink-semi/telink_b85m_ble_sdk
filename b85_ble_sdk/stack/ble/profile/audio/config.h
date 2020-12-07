/********************************************************************************************************
 * @file	config.h
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
#ifndef _CONFIG_H_
#define _CONFIG_H_


#define AUDIO_PROFILE_EN           0


#if AUDIO_PROFILE_EN
	#define AUDIO_HANDLE_COUNT     2
	#define AUDIO_ASE_MAX_COUNT    2 // <=8

	#define AUDIO_SLAVE_ENABLE     1
	#define AUDIO_MASTER_ENABLE    0
	
	#define AUDIO_MCP_ENABLE       1
	#define AUDIO_CCP_ENABLE       0

	#define AUDIO_PACP_ENABLE      1
	#define AUDIO_ASCP_ENABLE      1
	#define AUDIO_BASP_ENABLE      0
	#define AUDIO_CSIP_ENABLE      1
	#define AUDIO_MICP_ENABLE      1
	#define AUDIO_RAAP_ENABLE      0
	#define AUDIO_VOCP_ENABLE      0
	#define AUDIO_VCP_ENABLE       1
#else
	#define AUDIO_SLAVE_ENABLE     0
	#define AUDIO_MASTER_ENABLE    0

	#define AUDIO_MCP_ENABLE       0
	#define AUDIO_CCP_ENABLE       0

	#define AUDIO_PACP_ENABLE      0
	#define AUDIO_ASCP_ENABLE      0
	#define AUDIO_BASP_ENABLE      0
	#define AUDIO_CSIP_ENABLE      0
	#define AUDIO_MICP_ENABLE      0
	#define AUDIO_RAAP_ENABLE      0
	#define AUDIO_VOCP_ENABLE      0
	#define AUDIO_VCP_ENABLE       0
#endif


#if (AUDIO_MASTER_ENABLE || (AUDIO_SLAVE_ENABLE && (AUDIO_RAAP_ENABLE \
	|| AUDIO_CCP_ENABLE || AUDIO_MCP_ENABLE)))
	#define AUDIO_SDP_ENABLE       1
#else
	#define AUDIO_SDP_ENABLE       0
#endif

#if (AUDIO_MICP_ENABLE)
	#define AUDIO_AICS_COUNT       2 // <=6
#endif

#if (AUDIO_VCP_ENABLE)
	#define AUDIO_VCP_VOLUME_MAX   100
	#define AUDIO_VCP_VOLUME_STEP  10
#endif

#if (AUDIO_MCP_ENABLE)
	#define AUDIO_MCP_SUPPORT_CHAR_COUNT      9
	//Media Player Name, Track Changed, Track Title, Track Duration, Track Position,
	//Media State, Content Control ID (CCID), Media Control Point, Media Control Point Opcodes Supported
	
#endif


#if (AUDIO_ASCP_ENABLE)
	#define AUDIO_PERFERRED_SDU_MIN_INTERVAL          0x001D4C // 7.5ms // Range: 0x0000FF-0xFFFFF    Units:us
	#define AUDIO_PERFERRED_SDU_MAX_INTERVAL          0x0186A0 // 100ms // Range: 0x0000FF-0xFFFFFF   Units:us
	#define AUDIO_PERFERRED_FRAMING                   0x00 // 0x00-Unframe, 0x01-frame ISOAL PDUs
	#define AUDIO_PERFERRED_PHY                       0x01 // BIT(0)-1M, BIT(1)-2M, BIT(2)-Coded
	#define AUDIO_PERFERRED_MAX_SDU                   240 // Range: 0x0000-0x0FFF
	#define AUDIO_PERFERRED_RETRANSMIT_NUM            3 // Range: 0x00-0x0F
	#define AUDIO_PERFERRED_MAX_TRANSPORT_LATECY      40 // Range: 0x0005-0x0FA0    Units:ms
	#define AUDIO_PERFERRED_MIN_PRESENTATION_DELAY    0x002EE0 // 12ms // Range: 0x000000-0xFFFFFF,   Units:us
	#define AUDIO_PERFERRED_MAX_PRESENTATION_DELAY    0x004E20 // 20ms // Range: 0x000000-0xFFFFFF,   Units:us
#endif //AUDIO_ASCP_ENABLE




#endif //_CONFIG_H_

