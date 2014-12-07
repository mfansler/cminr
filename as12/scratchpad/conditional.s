	.file	"conditional.cc"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$-1, -4(%ebp)
	movl	$0, -8(%ebp)
	cmpl	$0, -4(%ebp)
	je	.L2
	movl	$2, -8(%ebp)
	jmp	.L3
.L2:
	movl	$0, -8(%ebp)
.L3:
	cmpl	$0, -4(%ebp)
	jns	.L4
	movl	-4(%ebp), %eax
	imull	-4(%ebp), %eax
	movl	%eax, -8(%ebp)
.L4:
	movl	$30, -4(%ebp)
	movl	$1, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.1"
	.section	.note.GNU-stack,"",@progbits
