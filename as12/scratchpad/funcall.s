	.file	"funcall.cc"
	.text
	.globl	_Z6squarePii
	.type	_Z6squarePii, @function
_Z6squarePii:
.LFB0:
	.cfi_startproc
	movl	4(%esp), %ecx
	movl	8(%esp), %edx
	testl	%edx, %edx
	jle	.L1
	movl	%ecx, %eax
	leal	(%ecx,%edx,4), %ecx
.L3:
	movl	(%eax), %edx
	imull	%edx, %edx
	movl	%edx, (%eax)
	addl	$4, %eax
	cmpl	%ecx, %eax
	jne	.L3
.L1:
	rep ret
	.cfi_endproc
.LFE0:
	.size	_Z6squarePii, .-_Z6squarePii
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	subl	$48, %esp
	.cfi_def_cfa_offset 52
	movl	$0, %eax
.L6:
	movl	%eax, 8(%esp,%eax,4)
	addl	$1, %eax
	cmpl	$10, %eax
	jne	.L6
	pushl	$10
	.cfi_def_cfa_offset 56
	leal	12(%esp), %eax
	pushl	%eax
	.cfi_def_cfa_offset 60
	call	_Z6squarePii
	movl	$0, %eax
	addl	$56, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.1"
	.section	.note.GNU-stack,"",@progbits
