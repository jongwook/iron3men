	.file	"<stdin>"
	.text
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
# BB#0:                                 # %bb.nph
	pushl	%ebp
	pushl	%ebx
	pushl	%edi
	pushl	%esi
	subl	$20, %esp
	movl	$9, 12(%esp)
	movl	$EdgeProfCounters, 8(%esp)
	movl	$0, 4(%esp)
	movl	$0, (%esp)
	call	llvm_start_edge_profiling
	incl	EdgeProfCounters+4
	incl	EdgeProfCounters
	xorl	%esi, %esi
	movl	%esi, %edi
	movl	%esi, %ebx
	movl	$1, %eax
	jmp	.LBB0_1
	.align	16, 0x90
.LBB0_8:                                # %bb8.bb_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	addl	$3, %ebp
	incl	EdgeProfCounters+32
	movl	%ebp, %eax
.LBB0_1:                                # %bb
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$80, %esi
	movl	$-1, %ebp
	movl	$1, %ecx
	cmovll	%ecx, %ebp
	leal	-1(%ebp,%eax), %ecx
	setl	%dl
	addl	%eax, %ebp
	cmpl	$10, %esi
	cmovgl	%ecx, %ebp
	movzbl	%dl, %eax
	setg	%cl
	movzbl	%cl, %ecx
	addl	%ebx, %ecx
	movl	%eax, %ebx
	xorl	$1, %ebx
	addl	%ecx, %ebx
	cmpl	$1, %esi
	je	.LBB0_5
# BB#2:                                 # %bb
                                        #   in Loop: Header=BB0_1 Depth=1
	leal	2(%eax,%edi), %edi
	cmpl	$2, %esi
	jne	.LBB0_4
# BB#3:                                 # %bb.bb7_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+16
	jmp	.LBB0_6
.LBB0_4:                                # %bb.bb8_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+8
	jmp	.LBB0_7
.LBB0_5:                                # %bb6
                                        #   in Loop: Header=BB0_1 Depth=1
	leal	1(%eax,%edi), %edi
	incl	EdgeProfCounters+20
	incl	EdgeProfCounters+12
	addl	$2, %edi
.LBB0_6:                                # %bb7
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	EdgeProfCounters+24
	incl	%ebx
.LBB0_7:                                # %bb8
                                        #   in Loop: Header=BB0_1 Depth=1
	leal	2(%ebp), %eax
	movl	%eax, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	$.L.str, (%esp)
	call	printf
	incl	%esi
	cmpl	$100, %esi
	jne	.LBB0_8
# BB#9:                                 # %return
	incl	EdgeProfCounters+28
	addl	$20, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	ret
.Ltmp0:
	.size	main, .Ltmp0-main

	.type	.L.str,@object          # @.str
	.section	.rodata.str1.1,"aMS",@progbits,1
.L.str:
	.asciz	 "%d %d %d"
	.size	.L.str, 9

	.type	EdgeProfCounters,@object # @EdgeProfCounters
	.local	EdgeProfCounters        # @EdgeProfCounters
	.comm	EdgeProfCounters,36,16

	.section	.note.GNU-stack,"",@progbits
