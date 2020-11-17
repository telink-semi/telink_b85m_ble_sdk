/********************************************************************************************************
 * @file	utility.h
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
#pragma once
#include "types.h"

#define abs(a)   (((a)>0)?((a)):(-(a)))

#define cat2(i,j)       i##j
#define cat3(i,j,k)     i##j##k

#ifndef min
#define min(a,b)	((a) < (b) ? (a) : (b))
#endif

#ifndef min2
#define min2(a,b)	((a) < (b) ? (a) : (b))
#endif

#ifndef min3
#define min3(a,b,c)	min2(min2(a, b), c)
#endif

#ifndef max2
#define max2(a,b)	((a) > (b) ? (a): (b))
#endif

#ifndef max3
#define max3(a,b,c)	max2(max2(a, b), c)
#endif

#define OFFSETOF(s, m) 			((unsigned int) &((s *)0)->m)
#define ROUND_INT(x, r)			(((x) + (r) - 1) / (r) * (r))
#define ROUND_TO_POW2(x, r)		(((x) + (r) - 1) & ~((r) - 1))

//  direct memory access
#define U8_GET(addr)			(*(volatile unsigned char  *)(addr))
#define U16_GET(addr)			(*(volatile unsigned short *)(addr))
#define U32_GET(addr)			(*(volatile unsigned int  *)(addr))

#define U8_SET(addr, v)			(*(volatile unsigned char  *)(addr) = (unsigned char)(v))
#define U16_SET(addr, v)		(*(volatile unsigned short *)(addr) = (unsigned short)(v))
#define U32_SET(addr, v)		(*(volatile unsigned int  *)(addr) = (v))

#define U8_INC(addr)			U8_GET(addr) += 1
#define U16_INC(addr)			U16_GET(addr) += 1
#define U32_INC(addr)			U32_GET(addr) += 1

#define U8_DEC(addr)			U8_GET(addr) -= 1
#define U16_DEC(addr)			U16_GET(addr) -= 1
#define U32_DEC(addr)			U32_GET(addr) -= 1

#define U8_CPY(addr1,addr2)		U8_SET(addr1, U8_GET(addr2))
#define U16_CPY(addr1,addr2)	U16_SET(addr1, U16_GET(addr2))
#define U32_CPY(addr1,addr2)	U32_SET(addr1, U32_GET(addr2))

#define MAKE_U16(h,l) 			((unsigned short)(((h) << 8) | (l)))
#define MAKE_U24(a,b,c)			((unsigned int)(((a) << 16) | ((b) << 8) | (c)))
#define MAKE_U32(a,b,c,d)		((unsigned int)(((a) << 24) | ((b) << 16) | ((c) << 8) | (d)))

#define BOUND(x, l, m)			((x) < (l) ? (l) : ((x) > (m) ? (m) : (x)))
#define SET_BOUND(x, l, m)		((x) = BOUND(x, l, m))
#define BOUND_INC(x, m)			do{++(x); (x) = (x) < (m) ? (x) :0;} while(0)
#define BOUND_INC_POW2(x, m)	do{								\
									(x) = ((x)+1) & (m-1);		\
								}while(0)

#define IS_POWER_OF_2(x)		(!(x & (x-1)))
#define IS_LITTLE_ENDIAN 		(*(unsigned short*)"\0\xff" > 0x100)

#define IMPLIES(x, y) 			(!(x) || (y))

// x > y ? 1 : (x ==y : 0 ? -1)
#define COMPARE(x, y) 			(((x) > (y)) - ((x) < (y)))
#define SIGN(x) 				COMPARE(x, 0)

// better than xor swap:  http://stackoverflow.com/questions/3912699/why-swap-with-xor-works-fine-in-c-but-in-java-doesnt-some-puzzle
#define SWAP(x, y, T) 			do { T tmp = (x); (x) = (y); (y) = tmp; } while(0)
#define SORT2(a, b, T) 			do { if ((a) > (b)) SWAP((a), (b), T); } while (0)

#define foreach(i, n) 			for(int i = 0; i < (n); ++i)
#define foreach_range(i, s, e) 	for(int i = (s); i < (e); ++i)
#define foreach_arr(i, arr) 	for(int i = 0; i < ARRAY_SIZE(arr); ++i)
//  round robbin foreach,   从上一个指定的点开始，遍历,  h 是一个静态变量或全局变量，要记住上一次的位置。h 初始值是n !!!
#define foreach_hint(i, n, h) 	for(int i = 0, ++h, h=h<n?h:0; i < n; ++h, h=h<n?h:0)

#define ARRAY_SIZE(a) 			(sizeof(a) / sizeof(*a))

#define everyN(i, n) 			++(i); (i)=((i) < N ? (i) : 0); if(0 == (i))

#define U16_HI(a)    (((a) >> 8) & 0xFF)
#define U16_LO(a)    ((a) & 0xFF)

#define U32_BYTE0(a) ((a) & 0xFF)
#define U32_BYTE1(a) (((a) >> 8) & 0xFF)
#define U32_BYTE2(a) (((a) >> 16) & 0xFF)
#define U32_BYTE3(a) (((a) >> 24) & 0xFF)



void swapN (unsigned char *p, int n);
void swapX(const u8 *src, u8 *dst, int len);

void swap24(u8 dst[3], const u8 src[3]);
void swap32(u8 dst[4], const u8 src[4]);
void swap48(u8 dst[6], const u8 src[6]);
void swap56(u8 dst[7], const u8 src[7]);

void swap64(u8 dst[8], const u8 src[8]);

void swap128(u8 dst[16], const u8 src[16]);

void flip_addr(u8 *dest, u8 *src);

static inline u64 mul64_32x32(u32 u, u32 v)
{
#if 1 //Kite/Vulture's HW do not support HW long mul, here must open
    u32  u0,   v0,   w0;
    u32  u1,   v1,   w1,   w2,   t;
    u32  x, y;

    u0   =   u & 0xFFFF;
    u1   =   u >> 16;
    v0   =   v & 0xFFFF;
    v1   =   v >> 16;
    w0   =   u0 * v0;
    t    =   u1 * v0 + (w0 >> 16);
    w1   =   t & 0xFFFF;
    w2   =   t >> 16;
    w1   =   u0 * v1 + w1;

    //x is high 32 bits, y is low 32 bits

    x = u1 * v1 + w2 + (w1 >> 16);
    y = u * v;


    return(((u64)x << 32) | y);
#else
    return (u64)u*v;
#endif
}

u32 __div64_32(u64 *dividend, u32 divisor);
u64 __div64_64(u64 *dividend, u64 divisor);

static inline u64 div64_32(u64 dividend, u32 divisor)
{
	u64 result = dividend;
	__div64_32(&result, divisor);
	return result;
}

static inline u32 div64_32mod(u64 dividend, u32 divisor)
{
	u64 result = dividend;
	return __div64_32(&result, divisor);
}

static inline u64 div64_64(u64 dividend, u64 divisor)
{
	u64 result = dividend;
	__div64_64(&result, divisor);
	return result;
}

static inline u64 div64_64mod(u64 dividend, u64 divisor)
{
	u64 result = dividend;
	return __div64_64(&result, divisor);
}


typedef	struct {
	u32		size;
	u16		num;
	u8		wptr;
	u8		rptr;
	u8*		p;
}	my_fifo_t;

void my_fifo_init (my_fifo_t *f, int s, u8 n, u8 *p);
u8* my_fifo_wptr (my_fifo_t *f);
u8* my_fifo_wptr_v2 (my_fifo_t *f);
void my_fifo_next (my_fifo_t *f);
int my_fifo_push (my_fifo_t *f, u8 *p, int n);
void my_fifo_pop (my_fifo_t *f);
u8 * my_fifo_get (my_fifo_t *f);

#define		MYFIFO_INIT(name,size,n)			u8 name##_b[size * n]={0};my_fifo_t name = {size,n,0,0, name##_b}

#if (1) //DEBUG_USB_LOG_EN
#define		MYFIFO_INIT_IRAM(name,size,n)		/*__attribute__ ((aligned (4)))*/ __attribute__((section(".retention_data"))) u8 name##_b[size * n]__attribute__((aligned(4)))/*={0}*/;\
												__attribute__((section(".retention_data"))) my_fifo_t name = {size,n,0,0, name##_b}
#endif

#define		DATA_LENGTH_ALLIGN4(n)				((n + 3) / 4 * 4)


/*DLE Tx buffer len = DMA(4) + Header(2) + DLE + MIC(4) = DLE + 10*/
#define 	ACL_DLE_TX_FIFO_SIZE(n)				(((n+10) + 15) / 16 *16)

/*DLE RX buffer len = DMA(4) + Header(2) + DLE + MIC(4) + CRC(3) + ExtraInfor(8)  = DLE + 21*/
#define 	ACL_DLE_RX_FIFO_SIZE(n)				(((n+10) + 21) / 16 *16)

/*HCI TX RX buffer len = uart_fifo+ dma 4byte */
#define 	HCI_FIFO_SIZE(n)					(((n+2+4) + 15) / 16 *16)

												/*
												 * DMA_LEN(4B)+Hdr(2B)+PLD(251B)+MIC(4B)+CRC(3B)+TLK_PKT_INFO(8B)
												 *             **use 2B enough**
												 */
#define		ISO_PDU_SIZE_ALLIGN16(n)			(((n + 21) + 15) / 16 * 16) //4+2+4+2+4+3+8


/*
 * DMA_LEN(4B)+Hdr(2B)+PLD(251B)+MIC(4B)+CRC(3B)+TLK_PKT_INFO(12B)
 *             **use 2B enough**
 */
#define		ISO_BIS_RX_PDU_SIZE_ALLIGN16(n)			(((n + 25) + 15) / 16 * 16) //4+2+4+2+4+3+12


#define		ATT_ALLIGN4_DMA_BUFF(n)				(((n + 10) + 3) / 4 * 4)
/*
 * DMA_len(4) + type(1) + len(1) + l2cap_len(2) + cid(2) + sud_len(2) + mic(4)
 */
#define		L2CAP_ALLIGN4_KFRAM_DMA_BUFF(n)		(((n + 16) + 3) / 4 * 4)

#define		IAL_SDU_ALLIGN4_BUFF(n) 			(((n + 16) + 3) / 4 * 4)

#define		HCI_ISO_ALLIGN4_BUFF(n)				(((n + 4) + 3) / 4 * 4) //DMA len 4



typedef	struct {
	u16		fifo_size;
	u8		fifo_num;
	u8		conn_num;
	u8		*p;
}	multi_conn_fifo_t;

#define		MULTI_CONN_FIFO_INIT(name,fifo_size,fifo_num,conn_num)		u8 name##_b[fifo_size*fifo_num*conn_num]={0}; multi_conn_fifo_t name = {fifo_size,fifo_num,conn_num, name##_b}
