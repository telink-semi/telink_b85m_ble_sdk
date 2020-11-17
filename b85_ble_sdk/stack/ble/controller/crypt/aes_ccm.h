/********************************************************************************************************
 * @file	aes_ccm.h
 *
 * @brief	for TLSR chips
 *
 * @author	BLE GROUP
 * @date	2020.06
 *
 * @par		Copyright (c) 2020, Telink Semiconductor (Shanghai) Co., Ltd.
 *			All rights reserved.
 *
 *			The information contained herein is confidential property of Telink
 *          Semiconductor (Shanghai) Co., Ltd. and is available under the terms
 *          of Commercial License Agreement between Telink Semiconductor (Shanghai)
 *          Co., Ltd. and the licensee or the terms described here-in. This heading
 *          MUST NOT be removed from this file.
 *
 *          Licensee shall not delete, modify or alter (or permit any third party to delete, modify, or  
 *          alter) any information contained herein in whole or in part except as expressly authorized  
 *          by Telink semiconductor (shanghai) Co., Ltd. Otherwise, licensee shall be solely responsible  
 *          for any claim to the extent arising out of or relating to such deletion(s), modification(s)  
 *          or alteration(s).
 *
 *          Licensees are granted free, non-transferable use of the information in this
 *          file under Mutual Non-Disclosure Agreement. NO WARRENTY of ANY KIND is provided.
 *
 *******************************************************************************************************/
#pragma  once

#include "stack/ble/ble_format.h"

#define AES_BLOCK_SIZE     16


//#define		SUCCESS			0
enum {
    AES_SUCC = SUCCESS,
    AES_NO_BUF,               
    AES_FAIL,
};


typedef struct {
	u32		pkt;
	u8		dir;
	u8		iv[8];
} ble_cyrpt_nonce_t;


typedef struct {
	u32					enc_pno;
	u32					dec_pno;
	u8					sk[16];			//session key
	ble_cyrpt_nonce_t	nonce;
	u8					st;
	u8					enable;			//1: slave enable; 2: master enable
	u8					mic_fail;
} ble_crypt_para_t;


struct CCM_FLAGS_TAG {
    union {
        struct {
            u8 L : 3;
            u8 M : 3;
            u8 aData :1;
            u8 reserved :1;            
        } bf;
        u8 val;
    };
};

typedef struct CCM_FLAGS_TAG ccm_flags_t;


typedef struct {
    union {
        u8 A[AES_BLOCK_SIZE];
        u8 B[AES_BLOCK_SIZE];
    } bf;
    
    u8 tmpResult[AES_BLOCK_SIZE];
    u8 newAstr[AES_BLOCK_SIZE];
} aes_enc_t;


enum{
	CRYPT_NONCE_TYPE_ACL = 0,
	CRYPT_NONCE_TYPE_CIS = 1,
	CRYPT_NONCE_TYPE_BIS = 2,
};

typedef union {
	struct{
		u8 enEncFlg:1; //enable encryption
		u8 noneType:2; //ACL, CIS, BIS
		u8 decMicFail:1;//Decryption status
		u8 role:1;     //ll_ccm_enc: Master role must use 1, Slave role must use 0;
        			   //ll_ccm_dec: Master role must use 0, Slave role must use 1;
		u8 rsvd:3;     //Rsvd
	};
	u8 cryptBitsInfo;
}cryptBitsInfo_t;

typedef struct {
	u64					txPayloadCnt; //Packet counter for Tx
	u64					rxPayloadCnt; //Packet counter for Rx
	u8					sk[16];   	  //Session key
	ble_cyrpt_nonce_t	ccmNonce;     //CCM nonce format
	cryptBitsInfo_t     cryptBitsInfo;//To save Ram
	u16                 rsvd;         //For align
	llPhysChnPdu_t*     pllPhysChnPdu;//LL physical channel PDU
} leCryptCtrl_t;



/**
 * @brief   	this function is used to initialize the aes_ccm initial value
 * @param[in]   ltk - encryption key, LTK
 * @param[in]   skdm -
 * @param[in]   skds -
 * @param[in]   ivm -
 * @param[in]   ivs -
 * @param[in]   pd - Reference structure ble_crypt_para_t
 * @return  	none
 */
void aes_ll_ccm_encryption_init (u8 *ltk, u8 *skdm, u8 *skds, u8 *ivm, u8 *ivs, ble_crypt_para_t *pd);



/**
 * @brief   	this function is used to encrypt the aes_ccm value
 * @param[in]   pkt - plaint_text
 * @param[in]   master - ll_ccm_enc: Master role must use 1, Slave role must use 0;
                         ll_ccm_dec: Master role must use 0, Slave role must use 1;
 * @param[in]   pd - Reference structure ble_crypt_para_t
 * @return  	none
 */
void aes_ll_ccm_encryption(u8 *pkt, int master, ble_crypt_para_t *pd);



/**
 * @brief   	this function is used to encrypt the aes_ccm value, version2
 * @param[in]   pd - Reference structure leCryptCtrl_t
 * @return  	none
 */
void aes_ll_ccm_encryption_v2(leCryptCtrl_t *pd);



/**
 * @brief   	this function is used to decrypt the aes_ccm value
 * @param[in]   pkt - plaint_text
 * @param[in]   master - ll_ccm_enc: Master role must use 1, Slave role must use 0;
                         ll_ccm_dec: Master role must use 0, Slave role must use 1;
 * @param[in]   pd - Reference structure ble_crypt_para_t
 * @return  	0: decryption succeeded; 1: decryption failed
 */
int  aes_ll_ccm_decryption(u8 *pkt, int master, ble_crypt_para_t *pd);



/**
 * @brief   	this function is used to decrypt the aes_ccm value, version2
 * @param[in]   pd - Reference structure leCryptCtrl_t
 * @return  	0: decryption succeeded; 1: decryption failed
 */
int  aes_ll_ccm_decryption_v2(leCryptCtrl_t *pd);




/**
 * @brief   	this function is used to encrypt the plaintext
 * @param[in]   *key - aes key
 * @param[in]   *plaintext - plaint_text
 * @param[in]   *result - return encrypt result
 * @return  	none.
 */
void aes_ll_encryption(u8* key, u8* plaintext, u8 *result);



/**
 * @brief   	this function is used to decrypt the plaintext
 * @param[in]   *key - aes key
 * @param[in]   *plaintext - plaint_text
 * @param[in]   *result - return decrypt result
 * @return  	none.
 */
void aes_ll_decryption(u8* key, u8* plaintext, u8 *result);


/**
 * @brief   	this function is used to encrypt the packet for link layer
 * @param[in]   *key - aes key
 * @param[in]   *r - the plaintext
 * @param[in]   *p1 - packet buffer2
 * @param[in]   *p2 - packet buffer2
 * @param[in]   *result - the result of encrypt
 * @return  	none.
 */
void aes_ll_c1(u8 * key, u8 * r, u8 *p1, u8 *p2, u8 * result);

/**
 * @brief   	this function is used to encrypt the packet for link layer
 * @param[in]   *key - aes key
 * @param[in]   *r1 - the plaintext1
 * @param[in]   *r2 - the plaintext2
 * @param[in]   *result - the result of encrypt
 * @return  	none.
 */
void aes_ll_s1(u8 * key, u8 * r1, u8 * r2, u8 * result);

