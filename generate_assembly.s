	.file	"generate_assembly.c"
	.text
	.p2align 4
	.globl	generate_asm_approximation
	.type	generate_asm_approximation, @function
generate_asm_approximation:
.LFB5280:
	.cfi_startproc
	endbr64
	vmulss	8(%rdi), %xmm0, %xmm0
	movl	$0, %edx
	vaddss	4(%rdi), %xmm0, %xmm0
	vcvttss2sil	%xmm0, %eax
	testl	%eax, %eax
	cmovs	%edx, %eax
	movq	16(%rdi), %rdx
	cmpl	%eax, (%rdi)
	cmovle	(%rdi), %eax
	cltq
	vmovss	(%rdx,%rax,4), %xmm0
	ret
	.cfi_endproc
.LFE5280:
	.size	generate_asm_approximation, .-generate_asm_approximation
	.p2align 4
	.globl	generate_asm_approx_simd
	.type	generate_asm_approx_simd, @function
generate_asm_approx_simd:
.LFB5281:
	.cfi_startproc
	endbr64
	vbroadcastss	8(%rdi), %xmm0
	vbroadcastss	4(%rdi), %xmm1
	vmulps	(%rdx), %xmm0, %xmm0
	movq	16(%rdi), %rdx
	vaddps	%xmm1, %xmm0, %xmm0
	vpxor	%xmm1, %xmm1, %xmm1
	vcvttps2dq	%xmm0, %xmm0
	vpmaxsd	%xmm1, %xmm0, %xmm0
	vbroadcastss	(%rdi), %xmm1
	vpminsd	%xmm1, %xmm0, %xmm0
	vmovd	%xmm0, %eax
	cltq
	vmovss	(%rdx,%rax,4), %xmm1
	vpextrd	$1, %xmm0, %eax
	vmovss	%xmm1, (%rsi)
	cltq
	vmovss	(%rdx,%rax,4), %xmm1
	vpextrd	$2, %xmm0, %eax
	vmovss	%xmm1, 4(%rsi)
	cltq
	vmovss	(%rdx,%rax,4), %xmm1
	vpextrd	$3, %xmm0, %eax
	vmovss	%xmm1, 8(%rsi)
	cltq
	vmovss	(%rdx,%rax,4), %xmm0
	vmovss	%xmm0, 12(%rsi)
	ret
	.cfi_endproc
.LFE5281:
	.size	generate_asm_approx_simd, .-generate_asm_approx_simd
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
