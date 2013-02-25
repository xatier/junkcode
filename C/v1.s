	.file	"vet.c"
	.text
	.p2align 4,,15
	.globl	p
	.type	p, @function
p:
.LFB11:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	.p2align 4,,10
	.p2align 3
.L2:
	movq	stdout(%rip), %rsi
	movl	$81, %edi
	call	_IO_putc
	jmp	.L2
	.cfi_endproc
.LFE11:
	.size	p, .-p
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	call	p
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.7.2"
	.section	.note.GNU-stack,"",@progbits
