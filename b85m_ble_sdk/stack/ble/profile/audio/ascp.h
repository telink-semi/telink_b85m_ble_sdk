/********************************************************************************************************
 * @file	ascp.h
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
#ifndef _ASCP_H_
#define _ASCP_H_

#if (AUDIO_ASCP_ENABLE)


typedef enum{
	ASCS_ASE_STATE_IDLE                 = 0x00,
	ASCS_ASE_STATE_CODEC_CONFIGURED     = 0x01,
	ASCS_ASE_STATE_QoS_CONFIGURED       = 0x02,
	ASCS_ASE_STATE_ENABING              = 0x03,
	ASCS_ASE_STATE_STREAMING            = 0x04,
	ASCS_ASE_STATE_DISABLING            = 0x05,
	ASCS_ASE_STATE_RELEASING            = 0x06,
}ASCS_ASE_STATE_ENUM;

typedef enum{
	ASCS_OPCODE_CONFIG_CODEC            = 0x01,
	ASCS_OPCODE_CONFIG_QOS              = 0x02,
	ASCS_OPCODE_CONFIG_ENABLE           = 0x03,
	ASCS_OPCODE_CONFIG_RECV_START       = 0x04,
	ASCS_OPCODE_CONFIG_DISABLE          = 0x05,
	ASCS_OPCODE_CONFIG_RECV_STOP        = 0x06,
	ASCS_OPCODE_CONFIG_UPDATE_METADATA  = 0x07,
	ASCS_OPCODE_CONFIG_RELEASE          = 0x08,
}ASCS_OPCODE_ENUM;
typedef enum{
	ASCS_ERRCODE_NONE                   = 0x0000,
	ASCS_ERRCODE_UNSUPPORTED_OPCODE     = 0x0001,
	ASCS_ERRCODE_TRUNCATED_OPERATION    = 0x0002,
	ASCS_ERRCODE_INVALID_ASE_ID         = 0x0003,
	ASCS_ERRCODE_INVALID_ASE_STATE      = 0x0004,
	ASCS_ERRCODE_UNSUPPORTED_CAPABILITY = 0x0005, // need  ASCS_REASON_ENUM
	ASCS_ERRCODE_UNSUPPORTED_CONFIG     = 0x0006, // need  ASCS_REASON_ENUM
	ASCS_ERRCODE_REJECTED_CONFIG        = 0x0007, // need  ASCS_REASON_ENUM
	ASCS_ERRCODE_INVALID_CONFIG         = 0x0008, // need  ASCS_REASON_ENUM
	ASCS_ERRCODE_UNSUPPORTED_METADATA   = 0x0009, // need  Value of the Metadata Type field in error
	ASCS_ERRCODE_REJECTED_METADATA		= 0x000A, // need  Value of the Metadata Type field in error
	ASCS_ERRCODE_INVALID_METADATA 		= 0x000B, // need  Value of the Metadata Type field in error
	ASCS_ERRCODE_INSUFFICIENT_RESOURCE  = 0x000C,
	ASCS_ERRCODE_UNSPECIFIED_ERROR      = 0x000D,
}ASCS_ERRCODE_ENUM;
typedef enum{
	ASCS_REASON_DIRECTION               = 0x01,
	ASCS_REASON_CODEC_ID                = 0x02,
	ASCS_REASON_CONFIG_LENGTH           = 0x03,
	ASCS_REASON_CONFIG                  = 0x04,
	ASCS_REASON_SDU_INTERVAL            = 0x05,
	ASCS_REASON_FRAMING                 = 0x06,
	ASCS_REASON_PHY                     = 0x07,
	ASCS_REASON_SDU_SIZE                = 0x08,
	ASCS_REASON_RETRANS_NUMBER          = 0x09,
	ASCS_REASON_MAX_LATENCY             = 0x0A,
	ASCS_REASON_PRESENT_DELAY           = 0x0B,
	ASCS_REASON_METADATA_LENGTH         = 0x0C,
}ASCS_REASON_ENUM;

#define ASCS_FLAG_BUSY                 0x0100
#define ASCS_FLAG_EVENT                0x0200


#define ASCS_ASE_FLAG_ENABLE           0x0001
#define ASCS_ASE_FLAG_UPDATE           0x0002
#define ASCS_ASE_FLAG_REVC_START       0x0004
#define ASCS_ASE_FLAG_REVC_STOP        0x0008
#define ASCS_ASE_FLAG_RELEASE          0x0010
#define ASCS_ASE_FLAG_DISABLE          0x0020


typedef struct{ // 42Bytes
	u8  direction;                    /*<! audio sink and audio source*/
	
	u8  prefSDUMinInterval[3];        /*<! Range: 0x0000FF - 0xFFFFFF */
	u8  prefSDUMaxInterval[3];        /*<! Range: 0x0000FF - 0xFFFFFF */
	u8  prefFraming;                  /*<! Preferred Frame            */
	u8  prefPHY;                      /*<! Preferred PHY              */
	u16 prefMaxSDU;
	u8  prefRetransmitNum;            /*<! Range: 0x00 - 0x0F         */
	u16 prefMaxTransportLatency;      /*<! Range: 0x0005C0x0FA0       */
	u8  prefMinPresentationDelay[3];  /*<! Unit: us                   */
	u8  prefMaxPresentationDelay[3];  /*<! Unit: us                   */
	
	u8  codecId[5];
	u8  codecSpecificCfgLen;
	u8  codecSpecificCfg[16];          /*<! max = 16Byte. Shall exist only if the Codec_Specific_Configuration_Length field is not 0x00. */
}ascp_state_codec_t;
typedef struct{ // 15Bytes
	u8  cigID;
	u8  cisID;
	u8  SDUInterval[3];
	u8  framing;              // refer AUDIO_FRAMING_UNFRAMED
	u8  PHY;                  // refer AUDIO_PHY_FLAG_1M
	u16 maxSDU;               /*<! Range: 0x00C0xFFF        */
	u8  retransmitNum;        /*<! Range: 0x00C0x0F          */
	u16 maxTransportLatency;  /*<! Range: 0x0005C0x0FA0      */
	u8  presentationDelay[3]; /*<! Unit: us                  */
}ascp_state_qos_t;
typedef struct{ // 7Bytes
	u8  cigID;
	u8  cisID;
	u8  metaDataLen;
	u8  metaData[4];
}ascp_state_enable_t, ascp_state_disable_t, ascp_state_stream_t;
typedef struct{
	u8 aseID;
	u8 state; // refer ASCS_ASE_STATE_ENUM
	union{
		ascp_state_codec_t   codec;
		ascp_state_qos_t     qos;
		ascp_state_enable_t  enable;
		ascp_state_disable_t disable;
		ascp_state_stream_t  stream;
	}u;
}ascp_state_t;

typedef struct{
	u8  SDUMinInterval[3];        /*<! Range: 0x0000FF - 0xFFFFFF */
	u8  SDUMaxInterval[3];        /*<! Range: 0x0000FF - 0xFFFFFF */
	u8  framing;                  /*<! Preferred Frame            */
	u8  PHY;                      /*<! Preferred PHY              */
	u16 maxSDU;
	u8  retransmitNum;            /*<! Range: 0x00 - 0x0F         */
	u16 maxTransportLatency;      /*<! Range: 0x0005C0x0FA0      */
	u8  minPresentationDelay[3];  /*<! Unit: us                   */
	u8  maxPresentationDelay[3];  /*<! Unit: us                   */
}ascp_preferred_param_t;
typedef struct{
	u8  frequency;
	u8  duration;
	u16 frameOcts;
	u32 allocation;
}ascp_specific_param_t;
typedef struct{
	u16 preferredContext;
	u16 streamingContext;
}ascp_metadata_param_t;

typedef struct{ // 4Bytes
	u16 attHandle;
	u16 aclHandle;
	u8* pAseCCC;
}ascp_ase_t;

typedef struct{
	u8 aseCount;
	u16 ctrlHandle;
	ascp_ase_t ase[AUDIO_ASE_MAX_COUNT];
}ascp_ctrl_t;


int blc_audioAscpRead(u16 connHandle, void *p);
int blc_audioAscpWrite(u16 connHandle, void *p);

int blc_audioAscpRelease(u16 connHandle, u8 aseNum);
int blc_audioAscpStartRecv(u16 connHandle, u8 isStart, u8 aseNum);


#endif //AUDIO_ASCP_ENBALE

#endif //_ASCP_H_

