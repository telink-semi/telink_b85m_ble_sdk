#if (LE_AUDIO_ENABLE)

	.align	2
	.globl	read_bit
	.type	read_bit, @function
read_bit:
	lh	a5,0(a1)        // bp -> a5
	lh	a4,0(a2)        // mask -> a4
	add	a0,a0,a5

	lbu	a0,0(a0)
	bfos	a6,a4,1,15  // mask = mask << 1
	and	a0,a0,a4
	sh	a6,0(a2)        // a5 -> mask
	li	a4,256
	snez	a0,a0

	beq	a6,a4,.L6
	ret
	.align	2
.L6:
	li	a6,1
	sh	a6,0(a2)
	//lh	a5,0(a1)
	add	a5,a5,-1
	sh	a5,0(a1)
	ret

#endif //#if (ALG_LC3_ENABLE)
