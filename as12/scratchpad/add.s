	.file	"add.cc"
	.globl	y
	.data
	.align 4
	.type	y, @object
	.size	y, 4
y:
	.long	42
	.globl	z
	.bss
	.align 4
	.type	z, @object
	.size	z, 4
z:
	.zero	4
	.globl	a
	.align 32
	.type	a, @object
	.size	a, 40
a:
	.zero	40
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
	subl	$48, %esp
	movl	$0, z
	movl	z, %eax
	movl	$5, a(,%eax,4)
	movl	a+8, %eax
	movl	%eax, -4(%ebp)
	addl	$1, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	%eax, %eax
	movl	%eax, y
	movl	$7, -16(%ebp)
	movl	z, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.9.1"
	.section	.note.GNU-stack,"",@progbits
