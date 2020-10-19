	.file	"generate_assembly.c"
	.text
	.p2align 4,,15
	.globl	generate_asm_approximation
	.type	generate_asm_approximation, @function
generate_asm_approximation:
.LFB4752:
	.cfi_startproc
	vmulss	8(%rdi), %xmm0, %xmm0
	movl	$0, %edx
	vaddss	4(%rdi), %xmm0, %xmm0
	vcvttss2si	%xmm0, %eax
	testl	%eax, %eax
	cmovs	%edx, %eax
	cmpl	%eax, (%rdi)
	movq	16(%rdi), %rdx
	cmovle	(%rdi), %eax
	cltq
	vmovss	(%rdx,%rax,4), %xmm0
	ret
	.cfi_endproc
.LFE4752:
	.size	generate_asm_approximation, .-generate_asm_approximation
	.p2align 4,,15
	.globl	generate_asm_approx_simd
	.type	generate_asm_approx_simd, @function
generate_asm_approx_simd:
.LFB4753:
	.cfi_startproc
	vbroadcastss	8(%rdi), %xmm0
	vmulps	(%rdx), %xmm0, %xmm0
	vbroadcastss	4(%rdi), %xmm1
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
.LFE4753:
	.size	generate_asm_approx_simd, .-generate_asm_approx_simd
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
