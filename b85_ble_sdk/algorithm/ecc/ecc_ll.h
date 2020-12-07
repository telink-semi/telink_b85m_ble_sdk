/********************************************************************************************************
 * @file	ecc_ll.h
 *
 * @brief	This is the source file for BLE SDK
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

#ifndef ECC_LL_H_
#define ECC_LL_H_


const u8 blt_ecc_dbg_priv_key[32];
const u8 blt_ecc_dbg_pub_key[64];


/**
* @brief		This function is used to register the random number function needed for ECC calculation
* @param		none
* @return		none
*/
void 			blt_ecc_init(void);

/**
* @brief		This function is used to generate an ECDH public-private key pairs
* @param[out]  pub[64]:  output ecdh public key
* @param[out]  priv[64]: output ecdh private key
* @param[in]   use_dbg_key: 0: Non-debug key , others: debug key
* @return		1:  success
*              0: failure
*/
int 			blt_ecc_gen_key_pair(unsigned char pub[64], unsigned char priv[32], bool use_dbg_key);

/**
* @brief		This function is used to calculate DHKEY based on the peer public key and own private key
* @param[in]   peer_pub_key[64]: peer public key
* @param[in]   own_priv_key[32]: own private key
* @param[out]  out_dhkey[32]: dhkey key
* @return		1:  success
*              0: failure
*/
int 			blt_ecc_gen_dhkey(const unsigned char peer_pub[64], const unsigned char own_priv[32], unsigned char out_dhkey[32]);




#endif /* ECC_LL_H_ */




