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
	subl	$36, %esp
	xorl	%esi, %esi
	call	clock
	movl	%eax, 16(%esp)          # 4-byte Spill
	movl	%esi, %ecx
	movl	%esi, %edi
	movl	%esi, %ebx
	movl	$1, %ebp
	.align	16, 0x90
.LBB0_1:                                # %bb
                                        # =>This Inner Loop Header: Depth=1
	movl	%esi, %eax
	movl	$1717986919, %edx       # imm = 0x66666667
	imull	%edx
	movl	%edx, %eax
	shrl	$31, %eax
	sarl	$3, %edx
	addl	%eax, %edx
	imull	$20, %edx, %eax
	movl	%esi, %edx
	subl	%eax, %edx
	leal	2(%ecx), %eax
	cmpl	$1499999999, %esi       # imm = 0x59682EFF
	cmovgel	%ecx, %eax
	setl	%cl
	movzbl	%cl, %ecx
	movl	%ecx, 32(%esp)          # 4-byte Spill
	addl	%ecx, %edi
	cmpl	$200000000, %esi        # imm = 0xBEBC200
	setg	%cl
	movzbl	%cl, %ecx
	movl	%ecx, 28(%esp)          # 4-byte Spill
	addl	%ecx, %ebx
	xorl	$1, 32(%esp)            # 4-byte Folded Spill
	addl	32(%esp), %ebx          # 4-byte Folded Reload
	xorl	$1, %ecx
	movl	%ecx, 20(%esp)          # 4-byte Spill
	cmpl	$1, %edx
	leal	1(%ecx,%edi), %ecx
	je	.LBB0_3
# BB#2:                                 # %bb
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	28(%esp), %edi          # 4-byte Reload
	leal	1(%edi,%edi), %edi
	movl	%edi, 24(%esp)          # 4-byte Spill
	cmpl	$2, %edx
	je	.LBB0_4
	jmp	.LBB0_5
.LBB0_3:                                # %bb7
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%ecx
	movl	$3, 24(%esp)            # 4-byte Folded Spill
.LBB0_4:                                # %bb8
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%ebx
.LBB0_5:                                # %bb9
                                        #   in Loop: Header=BB0_1 Depth=1
	leal	3(%ecx), %edi
	cmpl	$1499999999, %esi       # imm = 0x59682EFF
	movl	$-1, %edx
	cmovll	%ebp, %edx
	cmovgel	%ecx, %edi
	addl	20(%esp), %edi          # 4-byte Folded Reload
	addl	%edx, %eax
	addl	24(%esp), %eax          # 4-byte Folded Reload
	movl	32(%esp), %ecx          # 4-byte Reload
	addl	28(%esp), %ecx          # 4-byte Folded Reload
	addl	%ecx, %ebx
	incl	%esi
	cmpl	$2000000000, %esi       # imm = 0x77359400
	movl	%eax, %ecx
	jne	.LBB0_1
# BB#6:                                 # %bb17
	movl	%eax, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	$.L.str, (%esp)
	call	printf
	movl	$10, (%esp)
	call	putchar
	call	clock
	subl	16(%esp), %eax          # 4-byte Folded Reload
	movl	$274877907, %ecx        # imm = 0x10624DD3
	imull	%ecx
	movl	%edx, %eax
	shrl	$31, %eax
	sarl	$6, %edx
	addl	%eax, %edx
	movl	%edx, 4(%esp)
	movl	$.L.str1, (%esp)
	call	printf
	addl	$36, %esp
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
	.asciz	 "%d %d %d "
	.size	.L.str, 10

	.type	.L.str1,@object         # @.str1
.L.str1:
	.asciz	 "%ld\n"
	.size	.L.str1, 5


	.section	.note.GNU-stack,"",@progbits
