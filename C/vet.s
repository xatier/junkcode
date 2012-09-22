	.file	"vet.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$1, -12(%rbp)
	movl	$13, -8(%rbp)
	movl	$5566, -4(%rbp)
	movl	$0, -20(%rbp)
	jmp	.L2
.L3:
	movl	-12(%rbp), %eax
	imull	-8(%rbp), %eax
	addl	-20(%rbp), %eax
	movl	-12(%rbp), %edx
	movl	%edx, %ecx
	imull	-4(%rbp), %ecx
	movl	%ecx, -36(%rbp)
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	-36(%rbp)
	movl	%eax, -16(%rbp)
	addl	$1, -20(%rbp)
.L2:
	cmpl	$999, -20(%rbp)
	jle	.L3
	movl	-16(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
