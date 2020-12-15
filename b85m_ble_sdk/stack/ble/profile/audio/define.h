/********************************************************************************************************
 * @file	define.h
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
#ifndef _DEFINE_H_
#define _DEFINE_H_


#if (AUDIO_PROFILE_EN)


// TODO: TBD
// PACS Service & Characteristic
#define SERVICE_UUID_PUBLISHED_AUDIO_CAPABILITIES            0x2310 //PACS
#define CHARACTERISTIC_UUID_PACS_SINK_PAC                    0x2311 //Mandatory:Read; Optional:Notify
#define CHARACTERISTIC_UUID_PACS_SINK_AUDIO_LOCATION         0x2312 //Mandatory:Read; Optional:Notify,Write
#define CHARACTERISTIC_UUID_PACS_SOURCE_PAC                  0x2313 //Mandatory:Read; Optional:Notify
#define CHARACTERISTIC_UUID_PACS_SOURCE_AUDIO_LOCATION       0x2314 //Mandatory:Read; Optional:Notify,Write
#define CHARACTERISTIC_UUID_PACS_AVAILABLE_AUDIO_CONTEXT     0x2315 //Mandatory:Read,Notify; Optional:
#define CHARACTERISTIC_UUID_PACS_SUPPORTED_AUDIO_CONTEXT     0x2316 //Mandatory:Read; Optional:Notify
// ASCS Service & Characteristic
#define SERVICE_UUID_AUDIO_STREAM_CONTROL                    0x2320 
#define CHARACTERISTIC_UUID_ASCS_ASE                         0x2321 //Read, Notify
#define CHARACTERISTIC_UUID_ASCS_ASE_CONTROL_PPOINT          0x2322 //WriteWithoutResponse, Notify
// BACS Service & Characteristic
#define SERVICE_UUID_BROADCAST_AUDIO_SCAN                    0x2330 //PACS
// CSIS Service & Characteristic
#define SERVICE_UUID_COPRDINATED_SET_IDENTIFICATION          0x2340
#define CHARACTERISTIC_UUID_CSIS_SIRK                        0x2341 //M  Mandatory:Read; Optional:Notify
#define CHARACTERISTIC_UUID_CSIS_SIZE                        0x2342 //O  Mandatory:Read; Optional:Notify
#define CHARACTERISTIC_UUID_CSIS_LOCK                        0x2343 //O  Mandatory:Read,Write,Notify; Optional:
#define CHARACTERISTIC_UUID_CSIS_RANK                        0x2345 //O  Mandatory:Read; Optional:
// RAAS Service & Characteristic
#define SERVICE_UUID_ROUTING_ACTIVE_AUDIO                    0x2350
#define CHARACTERISTIC_UUID_RAAS_SELECTABLE_ARE              0x2351 // Selectable Audio Route Endpoint List
#define CHARACTERISTIC_UUID_RAAS_CONFIGURED_ARE              0x2352 // Configured Audio Routes List
#define CHARACTERISTIC_UUID_RAAS_CONFIGURED_CONTENT          0x2353 // Configured Audio Routes Content Type List
#define CHARACTERISTIC_UUID_RAAS_MODIFY_ARC                  0x2354 // Modify Audio Routing Control Point
// MICS Service & Characteristic
#define SERVICE_UUID_MICROPHONE_CONTROL                      0x2360
#define CHARACTERISTIC_UUID_MICS_MUTE                        0x2361 //M Mandatory:Read,Write,Indicate;   Optional:
#define SERVICE_UUID_AUDIO_INPUT_CONTROL                     0x2365 //O
#define CHARACTERISTIC_UUID_AICS_INPUT_STATE                 0x2366 //M Mandatory:Read,Notify;   Optional:
#define CHARACTERISTIC_UUID_AICS_GAIN_SETTING                0x2367 //M Mandatory:Read;   Optional:
#define CHARACTERISTIC_UUID_AICS_INPUT_TYPE                  0x2368 //M Mandatory:Read;   Optional:
#define CHARACTERISTIC_UUID_AICS_INPUT_STATUS                0x2369 //M Mandatory:Read,Notify;   Optional:
#define CHARACTERISTIC_UUID_AICS_INPUT_CONTROL               0x236A //M Mandatory:Write;   Optional:
#define CHARACTERISTIC_UUID_AICS_INPUT_DESCRIP               0x236B //M Mandatory:Read;   Optional:Write Without Response, Notify

// VOCS Service & Characteristic
#define SERVICE_UUID_VOLUME_OFFSET_CONTROL                   0x2370
// VCS  Service & Characteristic
#define SERVICE_UUID_VOLUME_CONTROL                          0x2380
#define CHARACTERISTIC_UUID_VCS_STATE                        0x2381 //Mandatory:Read,Notify;   Optional:
#define CHARACTERISTIC_UUID_VCS_CONTROL_POINT                0x2382 //Mandatory:Write;   Optional:
#define CHARACTERISTIC_UUID_VCS_FLAGS                        0x2383 //Mandatory:Read,Notify;   Optional:
// MCS  Service & Characteristic
#define SERVICE_UUID_MEDIA_CONTROL                           0x2410
#define CHARACTERISTIC_UUID_MCS_NAME                         0x2411 // Media Player Name
#define CHARACTERISTIC_UUID_MCS_ICON_OBJECT_ID               0x2412 // Media Player Icon Object ID
#define CHARACTERISTIC_UUID_MCS_ICON_URL                     0x2413 // Media Player Icon URL
#define CHARACTERISTIC_UUID_MCS_TRACK_CHANGED                0x2414 // Track Changed
#define CHARACTERISTIC_UUID_MCS_TRACK_TITLE                  0x2415 // Track Title
#define CHARACTERISTIC_UUID_MCS_TRACK_DURATION               0x2416 // Track Duration
#define CHARACTERISTIC_UUID_MCS_TRACK_POSITION               0x2417 // Track Position
#define CHARACTERISTIC_UUID_MCS_PLAYBACK_SPEED               0x2418 // Playback Speed
#define CHARACTERISTIC_UUID_MCS_SEEKING_SPEED                0x2419 // Seeking Speed
#define CHARACTERISTIC_UUID_MCS_SEGMENTS_OBJECT_ID           0x241A // Current Track Segments Object ID
#define CHARACTERISTIC_UUID_MCS_CURRENT_OBJECT_ID            0x241B // Current Track Object ID
#define CHARACTERISTIC_UUID_MCS_NEXT_OBJECT_ID               0x241C // Next Track Object ID
#define CHARACTERISTIC_UUID_MCS_CURRENT_GOUP_OBJECT_ID       0x241D // Current Group Object ID
#define CHARACTERISTIC_UUID_MCS_PARENT_GOUP_OBJECT_ID        0x241E // Parent Group Object ID
#define CHARACTERISTIC_UUID_MCS_PLAYING_ORDER                0x241F // Playing Order
#define CHARACTERISTIC_UUID_MCS_PLAYING_ORDER_SUPPEORTED     0x2421 // Playing Order Supported
#define CHARACTERISTIC_UUID_MCS_MEDIA_STATE                  0x2422 // Media State
#define CHARACTERISTIC_UUID_MCS_MEDIA_CONTROL_POINT          0x2423 // Media Control Point
#define CHARACTERISTIC_UUID_MCS_OPCODES_SUPPORTED            0x2424 // Media Control Point Opcodes Supported
#define CHARACTERISTIC_UUID_MCS_SEARCH_RESULTS_OBJECT_ID     0x2425 // Search Results Object ID
#define CHARACTERISTIC_UUID_MCS_SEARCH_CONTROL_POINT         0x2426 // Search Control Point
#define CHARACTERISTIC_UUID_MCS_CONTENT_CONTROL_ID           0x2427 // Content Control ID (CCID)
// CCS  Service & Characteristic
#define SERVICE_UUID_CALL_CONTROL                            0x2420



///BAP
////////////////////////////////////////////////////////////////////

// Context Type
#define AUDIO_CONTEXT_TYPE_UNSPECIFIED         BIT(0) // Unspecified. Matches any audio content.
#define AUDIO_CONTEXT_TYPE_CONVERSATIONAL      BIT(1) // Conversation between humans as, for example, in telephony or video calls.
#define AUDIO_CONTEXT_TYPE_MEDIA               BIT(2) // Media as, for example, in music, public radio, podcast or video soundtrack.
#define AUDIO_CONTEXT_TYPE_INSTRUCTIONAL       BIT(3) // Instructional audio as, for example, in navigation, traffic announcements or user guidance
#define AUDIO_CONTEXT_TYPE_ATTENTION_SEEKING   BIT(4) // Attention seeking audio as, for example, in beeps signalling arrival of a message or keyboard clicks. 
#define AUDIO_CONTEXT_TYPE_IMMEDIATE_ALERT     BIT(5) // Immediate alerts as, for example, in a low battery alarm, timer expiry or alarm clock.
#define AUDIO_CONTEXT_TYPE_MAN_MACHINE         BIT(6) // Man machine communication as, for example, with voice recognition or virtual assistant.
#define AUDIO_CONTEXT_TYPE_EMERGENCY_ALERT     BIT(7) // Emergency alerts as, for example, with fire alarms or other urgent alerts.
#define AUDIO_CONTEXT_TYPE_RINGTONE            BIT(8) // Ringtone as in a call alert.
#define AUDIO_CONTEXT_TYPE_TV                  BIT(9) // Audio associated with a television program and/or with metadata conforming to the Bluetooth Broadcast TV profile.

// Codec ID
#define AUDIO_CODECID_LC3                      0x00000001

// Audio Codec_Specific_Capabilties parameters
#define AUDIO_CAPTYPE_SUP_SAMPLE_FREQUENCY     0x01 // Supported_Sampling_Frequencies
#define AUDIO_CAPTYPE_SUP_FRAME_DURATION       0x02 // Supported_Frame_Durations
#define AUDIO_CAPTYPE_SUP_CHANNELS_COUNTS      0x03 // Audio_Channel_Counts
#define AUDIO_CAPTYPE_SUP_FRAME_OCTETS	       0x04 // Supported_Octets_Per_Codec_Frame


// Audio Codec_Specific_Configuration parameters
#define AUDIO_CAPTYPE_CFG_SAMPLE_FREQUENCY     0x01 // Sampling_Freqeuncy
#define AUDIO_CAPTYPE_CFG_FRAME_DURATION       0x02 // 
#define AUDIO_CAPTYPE_CFG_CHANNELS_ALLOCATION  0x03 // Audio_Channel_Allocation
#define AUDIO_CAPTYPE_CFG_FRAME_OCTETS	       0x04 // 

// Audio Meta Type
#define AUDIO_METATYPE_PREFERRED_CONTEXTS      0x01 // Preferred_Audio_Contexts
#define AUDIO_METATYPE_STREAMING_CONTEXTS      0x02 // Streaming_Audio_Contexts

// Audio Direction
#define AUDIO_DIRECTION_SINK                   0x01 //Server is Audio Sink
#define AUDIO_DIRECTION_SOURCE                 0x02 //Server is Audio Source

// Audio Support Location (bitfield, for PACS or ASCS)
#define AUDIO_LOCATION_FLAG_FL                 BIT(0)  // Front Left
#define AUDIO_LOCATION_FLAG_FR                 BIT(1)  // Front Right
#define AUDIO_LOCATION_FLAG_FC                 BIT(2)  // Front Center
#define AUDIO_LOCATION_FLAG_LFE1               BIT(3)  // Low Frequency Effects 1
#define AUDIO_LOCATION_FLAG_BL                 BIT(4)  // Back Left 
#define AUDIO_LOCATION_FLAG_BR                 BIT(5)  // Back Right
#define AUDIO_LOCATION_FLAG_FLc                BIT(6)  // Front Left of Center
#define AUDIO_LOCATION_FLAG_FRc                BIT(7)  // Front Right of Center
#define AUDIO_LOCATION_FLAG_BC                 BIT(8)  // Back Center
#define AUDIO_LOCATION_FLAG_LFE2               BIT(9)  // Low Frequency Effects 2
#define AUDIO_LOCATION_FLAG_SiL                BIT(10) // Side Left 
#define AUDIO_LOCATION_FLAG_SiR                BIT(11) // Side Right
#define AUDIO_LOCATION_FLAG_TpFL               BIT(12) // Top Front Left
#define AUDIO_LOCATION_FLAG_TpFR               BIT(13) // Top Front Right
#define AUDIO_LOCATION_FLAG_TpFC               BIT(14) // Top Front Center
#define AUDIO_LOCATION_FLAG_TpC                BIT(15) // Top Center
#define AUDIO_LOCATION_FLAG_TpBL               BIT(16) // Top Back Left
#define AUDIO_LOCATION_FLAG_TpBR               BIT(17) // Top Back Right
#define AUDIO_LOCATION_FLAG_TpSiL              BIT(18) // Top Side Left
#define AUDIO_LOCATION_FLAG_TpSiR              BIT(19) // Top Side Right
#define AUDIO_LOCATION_FLAG_TpBC               BIT(20) // Top Back Center
#define AUDIO_LOCATION_FLAG_BtFC               BIT(21) // Bottom Front Center
#define AUDIO_LOCATION_FLAG_BtFL               BIT(22) // Bottom Front Left
#define AUDIO_LOCATION_FLAG_BtFR               BIT(23) // Bottom Front Right
#define AUDIO_LOCATION_FLAG_FLw                BIT(24) // Front Left Wide
#define AUDIO_LOCATION_FLAG_FRw                BIT(25) // Front Right Wide
#define AUDIO_LOCATION_FLAG_LS                 BIT(26) // Left Surround
#define AUDIO_LOCATION_FLAG_RS                 BIT(27) // Right Surround

// Audio Support Frame Frequency (bitfield, for PACS)
#define AUDIO_FREQUENCY_FLAG_8000              BIT(0) // 8000 Hz
#define AUDIO_FREQUENCY_FLAG_16000             BIT(1) // 16000 Hz
#define AUDIO_FREQUENCY_FLAG_24000             BIT(2) // 24000 Hz
#define AUDIO_FREQUENCY_FLAG_32000             BIT(3) // 32000 Hz
#define AUDIO_FREQUENCY_FLAG_44100             BIT(4) // 44100 Hz
#define AUDIO_FREQUENCY_FLAG_48000             BIT(5) // 48000 Hz
// Audio Frame Frequency (numbric, for ASCS)
#define AUDIO_FREQUENCY_8000                   1 // 8000 Hz
#define AUDIO_FREQUENCY_16000                  2 // 16000 Hz
#define AUDIO_FREQUENCY_24000                  3 // 24000 Hz
#define AUDIO_FREQUENCY_32000                  4 // 32000 Hz
#define AUDIO_FREQUENCY_44100                  5 // 44100 Hz
#define AUDIO_FREQUENCY_48000                  6 // 48000 Hz

// Audio Support Frame Duration (bitfield, for PACS)
#define AUDIO_DURATION_FLAG_7_5                BIT(0)  //
#define AUDIO_DURATION_FLAG_10                 BIT(1)
#define AUDIO_DURATION_FLAG_7_5_PERFERRED      BIT(4)
#define AUDIO_DURATION_FLAG_10_PERFERRED       BIT(5)
// Audio Frame Duration (numbric, for ASCS)
#define AUDIO_DURATION_7_5                     0  //
#define AUDIO_DURATION_10                      1


// Audio Channel
#define AUDIO_CHANNEL_COUNTS_1                 BIT(0)
#define AUDIO_CHANNEL_COUNTS_2                 BIT(1)
#define AUDIO_CHANNEL_COUNTS_3                 BIT(2)
#define AUDIO_CHANNEL_COUNTS_4                 BIT(3)
#define AUDIO_CHANNEL_COUNTS_5                 BIT(4)
#define AUDIO_CHANNEL_COUNTS_6                 BIT(5)
#define AUDIO_CHANNEL_COUNTS_7                 BIT(6)
#define AUDIO_CHANNEL_COUNTS_8                 BIT(7)

// Audio PHY (bitfield, for ASCS)
#define AUDIO_PHY_FLAG_1M                      BIT(0) //LE 1M PHY preferred
#define AUDIO_PHY_FLAG_2M                      BIT(1) //LE 2M PHY preferred
#define AUDIO_PHY_FLAG_CODED                   BIT(2) //LE Coded PHY preferred

// Audio Framing (bitfield, for ASCS)
#define AUDIO_FRAMING_UNFRAMED                 0x00 //Unframed ISOAL PDUs preferred
#define AUDIO_FRAMING_FRAMED                   0x01 //framed ISOAL PDUs preferred


// The Value Of Mute field
#define AUDIO_MUTE_NOT_MUTED                   0x00
#define AUDIO_MUTE_MUTED                       0x01
#define AUDIO_MUTE_DISABLED                    0x02

// Gain Mode field
#define AUDIO_GAIN_MODE_MANUAL_ONLY            0x00
#define AUDIO_GAIN_MODE_AUTOMATIC_ONLY         0x01
#define AUDIO_GAIN_MODE_MANUAL                 0x02
#define AUDIO_GAIN_MODE_AUTOMATIC              0x03

// AICS Input State
#define AUDIO_INPUT_STATE_INACTIVE             0x00
#define AUDIO_INPUT_STATE_ACTIVE               0x01

// TODO: Input Type TBD
// AICS Input Type
#define AUDIO_INPUT_TYPE_LOCAL                 0x01
#define AUDIO_INPUT_TYPE_ISOCHRONOUS_STREAM    0x02
#define AUDIO_INPUT_TYPE_ANALOG_CONNECTOR      0x03
#define AUDIO_INPUT_TYPE_DIGITAL_CONNECTOR     0x04



// Audio Service Type
typedef enum{
	AUDIO_SERVICE_TYPE_PACS = 0,
	AUDIO_SERVICE_TYPE_ASCS,
	AUDIO_SERVICE_TYPE_BASS,
	AUDIO_SERVICE_TYPE_CSIS,
	AUDIO_SERVICE_TYPE_RAAS,
	AUDIO_SERVICE_TYPE_MICS,
	AUDIO_SERVICE_TYPE_VOCS,
	AUDIO_SERVICE_TYPE_VCS,
	AUDIO_SERVICE_TYPE_MCS,
	AUDIO_SERVICE_TYPE_CCS,
	AUDIO_SERVICE_TYPE_MAX,
}AUDIO_SERVICE_TYPE;
enum AUDIO_EVTID_ENUM{
	AUDIO_EVTID_NONE,
	///ASCS Event
	AUDIO_EVTID_ENABLE,   // ASE activated activation is effective
	AUDIO_EVTID_UPDATE,
	AUDIO_EVTID_DISABLE,
	AUDIO_EVTID_RELEASE,
	AUDIO_EVTID_RECV_START,
	AUDIO_EVTID_RECV_STOP,
	
	///PACS Event

	///MICP Event
	AUDIO_EVTID_MICVOL_CHANGE,
	
	///VCS Event
	AUDIO_EVTID_SPKVOL_CHANGE,
	
};



#endif //#if (AUDIO_PROFILE_EN)

#endif //_DEFINE_H_

