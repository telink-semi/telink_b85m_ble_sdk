#if (LE_AUDIO_ENABLE)

	.align	2
	.globl	dprod_q15
	.type	dprod_q15, @function
dprod_q15:
	srli    a3,a2,0x2
	c.mv	a4,a1
	c.mv	a5,a0
	c.li	a0,0
	c.li	a1,0
L2:
	c.addi	a3,-1
	lw	    a7,0(a5)
	lw	    a6,0(a4)
	lw      t0,4(a5)
	lw      t1,4(a4)
	smalda	a0,a7,a6
	c.addi	a5,8
	c.addi	a4,8
	smalda	a0,t0,t1
	c.bnez	a3,L2

L4:
	ret


#endif //#if (LE_AUDIO_ENABLE)
