	.file	"test.opt.bc"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:                                 # %entry
	subl	$20, %esp
	leal	12(%esp), %eax
	movl	%eax, 8(%esp)
	leal	16(%esp), %eax
	movl	%eax, 4(%esp)
	movl	$.L.str, (%esp)
	call	__isoc99_scanf
	movl	16(%esp), %eax
	movl	12(%esp), %ecx
	leal	(%ecx,%eax,2), %edx
	imull	%ecx, %edx
	imull	%eax, %eax
	addl	%edx, %eax
	movl	%eax, 4(%esp)
	movl	$.L.str1, (%esp)
	call	printf
	addl	$20, %esp
	ret
.Ltmp0:
	.size	main, .Ltmp0-main

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "%d %d"
	.size	.L.str, 6

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "%d"
	.size	.L.str1, 3


	.section	.note.GNU-stack,"",@progbits
