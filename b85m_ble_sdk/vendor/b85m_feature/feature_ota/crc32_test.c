/********************************************************************************************************
 * @file	crc32_test.c
 *
 * @brief	This is the source file for BLE SDK
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
#include "tl_common.h"
#include "drivers.h"
#include "stack/ble/ble.h"
#include "app_config.h"
#include "app.h"

#if 0


static const unsigned long crc32_tbl[256] = {
    0x00000000L, 0x77073096L, 0xEE0E612CL, 0x990951BAL, 0x076DC419L,
    0x706AF48FL, 0xE963A535L, 0x9E6495A3L, 0x0EDB8832L, 0x79DCB8A4L,
    0xE0D5E91EL, 0x97D2D988L, 0x09B64C2BL, 0x7EB17CBDL, 0xE7B82D07L,
    0x90BF1D91L, 0x1DB71064L, 0x6AB020F2L, 0xF3B97148L, 0x84BE41DEL,
    0x1ADAD47DL, 0x6DDDE4EBL, 0xF4D4B551L, 0x83D385C7L, 0x136C9856L,
    0x646BA8C0L, 0xFD62F97AL, 0x8A65C9ECL, 0x14015C4FL, 0x63066CD9L,
    0xFA0F3D63L, 0x8D080DF5L, 0x3B6E20C8L, 0x4C69105EL, 0xD56041E4L,
    0xA2677172L, 0x3C03E4D1L, 0x4B04D447L, 0xD20D85FDL, 0xA50AB56BL,
    0x35B5A8FAL, 0x42B2986CL, 0xDBBBC9D6L, 0xACBCF940L, 0x32D86CE3L,
    0x45DF5C75L, 0xDCD60DCFL, 0xABD13D59L, 0x26D930ACL, 0x51DE003AL,
    0xC8D75180L, 0xBFD06116L, 0x21B4F4B5L, 0x56B3C423L, 0xCFBA9599L,
    0xB8BDA50FL, 0x2802B89EL, 0x5F058808L, 0xC60CD9B2L, 0xB10BE924L,
    0x2F6F7C87L, 0x58684C11L, 0xC1611DABL, 0xB6662D3DL, 0x76DC4190L,
    0x01DB7106L, 0x98D220BCL, 0xEFD5102AL, 0x71B18589L, 0x06B6B51FL,
    0x9FBFE4A5L, 0xE8B8D433L, 0x7807C9A2L, 0x0F00F934L, 0x9609A88EL,
    0xE10E9818L, 0x7F6A0DBBL, 0x086D3D2DL, 0x91646C97L, 0xE6635C01L,
    0x6B6B51F4L, 0x1C6C6162L, 0x856530D8L, 0xF262004EL, 0x6C0695EDL,
    0x1B01A57BL, 0x8208F4C1L, 0xF50FC457L, 0x65B0D9C6L, 0x12B7E950L,
    0x8BBEB8EAL, 0xFCB9887CL, 0x62DD1DDFL, 0x15DA2D49L, 0x8CD37CF3L,
    0xFBD44C65L, 0x4DB26158L, 0x3AB551CEL, 0xA3BC0074L, 0xD4BB30E2L,
    0x4ADFA541L, 0x3DD895D7L, 0xA4D1C46DL, 0xD3D6F4FBL, 0x4369E96AL,
    0x346ED9FCL, 0xAD678846L, 0xDA60B8D0L, 0x44042D73L, 0x33031DE5L,
    0xAA0A4C5FL, 0xDD0D7CC9L, 0x5005713CL, 0x270241AAL, 0xBE0B1010L,
    0xC90C2086L, 0x5768B525L, 0x206F85B3L, 0xB966D409L, 0xCE61E49FL,
    0x5EDEF90EL, 0x29D9C998L, 0xB0D09822L, 0xC7D7A8B4L, 0x59B33D17L,
    0x2EB40D81L, 0xB7BD5C3BL, 0xC0BA6CADL, 0xEDB88320L, 0x9ABFB3B6L,
    0x03B6E20CL, 0x74B1D29AL, 0xEAD54739L, 0x9DD277AFL, 0x04DB2615L,
    0x73DC1683L, 0xE3630B12L, 0x94643B84L, 0x0D6D6A3EL, 0x7A6A5AA8L,
    0xE40ECF0BL, 0x9309FF9DL, 0x0A00AE27L, 0x7D079EB1L, 0xF00F9344L,
    0x8708A3D2L, 0x1E01F268L, 0x6906C2FEL, 0xF762575DL, 0x806567CBL,
    0x196C3671L, 0x6E6B06E7L, 0xFED41B76L, 0x89D32BE0L, 0x10DA7A5AL,
    0x67DD4ACCL, 0xF9B9DF6FL, 0x8EBEEFF9L, 0x17B7BE43L, 0x60B08ED5L,
    0xD6D6A3E8L, 0xA1D1937EL, 0x38D8C2C4L, 0x4FDFF252L, 0xD1BB67F1L,
    0xA6BC5767L, 0x3FB506DDL, 0x48B2364BL, 0xD80D2BDAL, 0xAF0A1B4CL,
    0x36034AF6L, 0x41047A60L, 0xDF60EFC3L, 0xA867DF55L, 0x316E8EEFL,
    0x4669BE79L, 0xCB61B38CL, 0xBC66831AL, 0x256FD2A0L, 0x5268E236L,
    0xCC0C7795L, 0xBB0B4703L, 0x220216B9L, 0x5505262FL, 0xC5BA3BBEL,
    0xB2BD0B28L, 0x2BB45A92L, 0x5CB36A04L, 0xC2D7FFA7L, 0xB5D0CF31L,
    0x2CD99E8BL, 0x5BDEAE1DL, 0x9B64C2B0L, 0xEC63F226L, 0x756AA39CL,
    0x026D930AL, 0x9C0906A9L, 0xEB0E363FL, 0x72076785L, 0x05005713L,
    0x95BF4A82L, 0xE2B87A14L, 0x7BB12BAEL, 0x0CB61B38L, 0x92D28E9BL,
    0xE5D5BE0DL, 0x7CDCEFB7L, 0x0BDBDF21L, 0x86D3D2D4L, 0xF1D4E242L,
    0x68DDB3F8L, 0x1FDA836EL, 0x81BE16CDL, 0xF6B9265BL, 0x6FB077E1L,
    0x18B74777L, 0x88085AE6L, 0xFF0F6A70L, 0x66063BCAL, 0x11010B5CL,
    0x8F659EFFL, 0xF862AE69L, 0x616BFFD3L, 0x166CCF45L, 0xA00AE278L,
    0xD70DD2EEL, 0x4E048354L, 0x3903B3C2L, 0xA7672661L, 0xD06016F7L,
    0x4969474DL, 0x3E6E77DBL, 0xAED16A4AL, 0xD9D65ADCL, 0x40DF0B66L,
    0x37D83BF0L, 0xA9BCAE53L, 0xDEBB9EC5L, 0x47B2CF7FL, 0x30B5FFE9L,
    0xBDBDF21CL, 0xCABAC28AL, 0x53B39330L, 0x24B4A3A6L, 0xBAD03605L,
    0xCDD70693L, 0x54DE5729L, 0x23D967BFL, 0xB3667A2EL, 0xC4614AB8L,
    0x5D681B02L, 0x2A6F2B94L, 0xB40BBE37L, 0xC30C8EA1L, 0x5A05DF1BL,
    0x2D02EF8DL
};


static unsigned long crc32_half_tbl[16] = {
	0x00000000, 0x1db71064, 0x3b6e20c8, 0x26d930ac,
	0x76dc4190, 0x6b6b51f4, 0x4db26158, 0x5005713c,
	0xedb88320, 0xf00f9344, 0xd6d6a3e8, 0xcb61b38c,
	0x9b64c2b0, 0x86d3d2d4, 0xa00ae278, 0xbdbdf21c
};

static unsigned long AA_crc_table[256];
static unsigned long AA_crc_half_table[16];

//λת
static unsigned long bitrev(unsigned long input, int bw)
{
    int i;
    unsigned long var;
    var = 0;
    for(i=0;i<bw;i++)
    {
        if(input & 0x01)
        {
            var |= 1<<(bw-1-i);
        }
        input>>=1;
    }
    return var;
}


void crc32_init(unsigned long poly, unsigned long* table)
{
    int i;
    int j;
    unsigned long c;

    poly=bitrev(poly,32);
    for(i=0; i<256; i++)
    {
        c = i;
        for (j=0; j<8; j++)
        {
            if(c&1)
            {
                c=poly^(c>>1);
            }
            else
            {
                c=c>>1;
            }
        }
        table[i] = c;
    }
}



void crc32_half_init(unsigned long poly, unsigned long* table)
{
    int i;
    int j;
    unsigned long c;

    poly=bitrev(poly,32);
    for(i=0; i<16; i++)
    {
        c = i;
        for (j=0; j<4; j++)
        {
            if(c&1)
            {
                c=poly^(c>>1);
            }
            else
            {
                c=c>>1;
            }
        }
        table[i] = c;
    }
}

#if 0
unsigned long crc32_cal(unsigned long crc, unsigned char* input, unsigned long* table, int len)
{
    unsigned char* pch = input;
    for(int i=0; i<len; i++)
    {
        crc = (crc>>8) ^ table[(crc^*pch) & 0xff];
        pch++;
    }

    return crc;
}
#endif


#if 0
unsigned long crc32_half_cal(unsigned long crc, unsigned char* input, unsigned long* table, int len)
{
    unsigned char* pch = input;
    for(int i=0; i<len; i++)
    {
        crc = (crc>>4) ^ table[(crc^*pch) & 0x0f];
        pch++;
    }

    return crc;
}
#endif




u8 test16[16] =   {0x11, 0x34, 0x67, 0xfd, 0x11, 0x34, 0x67, 0xfd, 0x11, 0x34, 0x67, 0xfd, 0x11, 0x34, 0x67, 0xfd};
//test16ֽڲ£
u8 test32[32] =   { 0x01,0x01, 0x04,0x03, 0x07,0x06, 0x0d,0x0f, 0x01,0x01, 0x04,0x03, 0x07, 0x06, 0x0d,0x0f, \
					0x01,0x01, 0x04,0x03, 0x07,0x06, 0x0d,0x0f, 0x01,0x01, 0x04,0x03, 0x07, 0x06, 0x0d,0x0f };


u8 test16_Another[16] = {0x12, 0x34, 0x67, 0xfd, 0x14, 0xb4, 0x62, 0x8c, 0xc9, 0xf0, 0x17, 0xd5, 0x5f, 0xaa, 0xba, 0xc9};
//test16_2ֽڲ£
u8 test32_Another[32] = {0x02,0x01, 0x04,0x03, 0x07,0x06, 0x0d,0x0f, 0x04,0x01, 0x04,0x0b, 0x02,0x06, 0x0c,0x08,  \
				   0x09,0x0c, 0x00,0x0f, 0x07,0x01, 0x05,0x0d, 0x0f,0x05, 0x0a,0x0a, 0x0a,0x0b, 0x09,0x0c	};



unsigned long AAA_crc_res1;
unsigned long AAA_crc_res2;
unsigned long AAA_crc_res3;
unsigned long AAA_crc_res4;

unsigned long AAA_crc_res5;


unsigned long AAA_crc_half_res1;
unsigned long AAA_crc_half_res2;
unsigned long AAA_crc_half_res3;
unsigned long AAA_crc_half_res4;
unsigned long AAA_crc_half_res5;


void crc32_test(void)
{

	sleep_us(500000);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ʱͳ
//ע⣺Ĵ洢3ַʽ1.ԤõtableֱӴ洢flash; 2.Ԥõtable洢ȫֱ ; 3.localջУÿ¼
//ֻ3ַʽҪ

	//crc32 table[256*4]Ӧbyteλݵcrc㣩ʱ 1.6 ms
	//ıAA_crc_tableԤȶflashϵcrc32_tbl϶һģΪcrc32_tblҲʹpolyֵΪ0x04C11DB7ģ
    DBG_CHN0_HIGH;
    crc32_init(0x04C11DB7, AA_crc_table);  //1600us
    DBG_CHN0_LOW;


    //crc32 half table[16*4]Ӧbyteλݵcrc㣩.ʱ150us
	//ıAA_crc_half_tableԤȶflashϵcrc32_half_tbl϶һģΪcrc32_half_tblҲʹpolyֵΪ0x04C11DB7ģ
    DBG_CHN1_HIGH;
    crc32_half_init(0x04C11DB7, AA_crc_half_table);  //150us
    DBG_CHN1_LOW;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////ַͬһݽcrc32ļ㣬һֻsram/flash/timingϸв
    //crcֵȫʹ 0xFFFFFFFF
    AAA_crc_res1 = 0xFFFFFFFF;
    AAA_crc_res2 = 0xFFFFFFFF;
    AAA_crc_half_res1 = 0xFFFFFFFF;
    AAA_crc_half_res2 = 0xFFFFFFFF;

#if 0
    //1.bytecrc32sramϵıAA_crc_tableռ1K byte sramAA_crc_tableʱ64us
    DBG_CHN0_HIGH;
    AAA_crc_res1 = crc32_cal(AAA_crc_res1, test16, AA_crc_table, 16);  //99e17457
    DBG_CHN0_LOW;

    //2.bytecrc32flashϵıcrc32_tblռ1K byte Flashʱ212us
    DBG_CHN1_HIGH;
    AAA_crc_res2 = crc32_cal(AAA_crc_res2, test16, crc32_tbl, 16);  //99e17457
    DBG_CHN1_LOW;
#endif

    //3.bytecrc32sramϵıcrc32_tblռ64 byte sramAA_crc_tableʱ100us
    DBG_CHN2_HIGH;
    AAA_crc_half_res1 = crc32_half_cal(AAA_crc_half_res1, test32, AA_crc_half_table, 32);  //99e17457
    DBG_CHN2_LOW;

    //4.bytecrc32flashϵıcrc32_half_tblռ64 byte Flashʱ136us
    DBG_CHN3_HIGH;
    AAA_crc_half_res2 = crc32_half_cal(AAA_crc_half_res2, test32, crc32_half_tbl, 32);    //99e17457
    DBG_CHN3_LOW;


    u8 pFwDat[16] = {0x25, 0xA0, 0x00, 0x00,  0x00, 0x00, 0x5D, 0x02,  0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00,0x00};
    int ota_fw_len = 16;
	u8 ota_dat[240*2];  //maximum 240 Bytes
	for(int i=0; i<ota_fw_len; i++){
		ota_dat[i*2]   = pFwDat[i] & 0x0f;
		ota_dat[i*2+1] = pFwDat[i]>>4;
	}
//	my_dump_str_data(DBG_OTA_FLOW, "FW CRC", &blotaSvr.fw_crc_init, 4);
	blotaSvr.fw_crc_init = 0xFFFFFFFF;
	blotaSvr.fw_crc_init = crc32_half_cal(blotaSvr.fw_crc_init, ota_dat, (unsigned long* )crc32_half_tbl, ota_fw_len*2); //9a f9 7c da
	write_log32(blotaSvr.fw_crc_init);



#if 0
////////////////////////ַͬһݽcrc32ļ㣬һֻsram/flash/timingϸв
	//crcֵȫʹ 0xFFFFFFFF
    AAA_crc_res3 = 0xFFFFFFFF;
    AAA_crc_res4 = 0xFFFFFFFF;
    AAA_crc_half_res3 = 0xFFFFFFFF;
    AAA_crc_half_res4 = 0xFFFFFFFF;

	//1.bytecrc32sramϵıAA_crc_tableռ1K byte sramAA_crc_tableʱ64us
	DBG_CHN0_HIGH;
	AAA_crc_res3 = crc32_cal(AAA_crc_res3, test16_Another, AA_crc_table, 16);  //d0c7d4de
	DBG_CHN0_LOW;

	//2.bytecrc32flashϵıcrc32_tblռ1K byte Flashʱ212us
	DBG_CHN1_HIGH;
	AAA_crc_res4 = crc32_cal(AAA_crc_res4, test16_Another, crc32_tbl, 16);  //d0c7d4de
	DBG_CHN1_LOW;

	//3.bytecrc32sramϵıcrc32_tblռ64 byte sramAA_crc_tableʱ80us
	DBG_CHN2_HIGH;
	AAA_crc_half_res3 = crc32_half_cal(AAA_crc_half_res3, test32_Another, AA_crc_half_table, 32);  //d0c7d4de
	DBG_CHN2_LOW;

	//4.bytecrc32flashϵıcrc32_half_tblռ64 byte Flashʱ136us
	DBG_CHN3_HIGH;
	AAA_crc_half_res4 = crc32_half_cal(AAA_crc_half_res4, test32_Another, crc32_half_tbl, 32);    //d0c7d4de
	DBG_CHN3_LOW;







	AAA_crc_res5 = 0xFFFFFFFF;
	DBG_CHN0_HIGH;
    AAA_crc_res5 = crc32_cal(AAA_crc_res5, "1234567890", AA_crc_table, 10);
    AAA_crc_res5 ^= 0xFFFFFFFF;  //261daee5עǱ
    write_reg32(0x40004, AAA_crc_res5);
    DBG_CHN0_LOW;



    //16 bytetest16_Another2 8byteǰ8ĽΪ8crc_init֤Ƿһ
    // d0c7d4de ǰһ
    u32 temp0 = crc32_cal(0xFFFFFFFF, test16_Another, AA_crc_table, 8);
    u32 temp1 = crc32_cal(temp0, test16_Another + 8, AA_crc_table, 8);
    write_reg32(0x40004, temp1);  //8255 0x40004IC 0x8004


    write_reg8(0x40000, 0x33);  //8255 0x40000IC 0x8000
    if(AAA_crc_res5){
        while(1);
    }
    write_reg8(0x40000, 0x44);   //8255 0x40000IC 0x8000
#endif
}



#endif
