/********************************************************************************************************
 * @file	iso_config.h
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
#ifndef ISO_CONFIG_H_
#define ISO_CONFIG_H_

/******************************* Macro & Enumeration & Structure Definition for Stack Begin, user can not use!!!!  *****/
#ifndef			LL_CIG_NUM_MAX
#define 		LL_CIG_NUM_MAX              					2
#endif


#ifndef			LL_CIS_SLAVE_NUM_MAX
#define 		LL_CIS_SLAVE_NUM_MAX              				2
#endif

#ifndef			LL_CIS_IN_CIG_NUM_MAX
#define 		LL_CIS_IN_CIG_NUM_MAX              				4
#endif


#ifndef			LL_SE_IN_CIG_NUM_MAX
#define 		LL_SE_IN_CIG_NUM_MAX              				16
#endif


#ifndef			LL_MASTER_SLAVE_CIS_NUM_MAX
#define 		LL_MASTER_SLAVE_CIS_NUM_MAX              		(LL_CIS_SLAVE_NUM_MAX + LL_CIS_IN_CIG_NUM_MAX*LL_CIG_NUM_MAX)
#endif


/******************************* Macro & Enumeration & Structure Definition for Stack End ******************************/




#endif /* ISO_CONFIG_H_ */
