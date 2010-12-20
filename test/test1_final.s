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
	subl	$44, %esp
	xorl	%esi, %esi
	call	clock
	movl	%eax, 20(%esp)          # 4-byte Spill
	movl	%esi, %eax
	movl	%esi, %ecx
	movl	%esi, %edi
	.align	16, 0x90
.LBB0_1:                                # %bb
                                        # =>This Inner Loop Header: Depth=1
	leal	2(%eax), %ebx
	cmpl	$1499999999, %esi       # imm = 0x59682EFF
	movl	$-1, %ebp
	movl	$1, %edx
	cmovll	%edx, %ebp
	movl	%ebp, 24(%esp)          # 4-byte Spill
	cmovgel	%eax, %ebx
	setl	%al
	movzbl	%al, %eax
	addl	%eax, %ecx
	cmpl	$200000000, %esi        # imm = 0xBEBC200
	setg	%dl
	movzbl	%dl, %edx
	movl	%edx, 40(%esp)          # 4-byte Spill
	xorl	$1, %eax
	addl	%edx, %edi
	xorl	$1, %edx
	movl	%edx, 36(%esp)          # 4-byte Spill
	cmpl	$1499999999, %esi       # imm = 0x59682EFF
	leal	4(%edx,%ecx), %ebp
	leal	1(%edx,%ecx), %ecx
	movl	%ecx, 32(%esp)          # 4-byte Spill
	cmovgel	%ecx, %ebp
	addl	%eax, %edi
	movl	40(%esp), %edx          # 4-byte Reload
	leal	(%eax,%edx), %eax
	movl	%eax, 28(%esp)          # 4-byte Spill
	movl	%esi, %eax
	movl	$1717986919, %ecx       # imm = 0x66666667
	imull	%ecx
	movl	%edx, %eax
	shrl	$31, %eax
	sarl	$3, %edx
	addl	%eax, %edx
	imull	$20, %edx, %eax
	movl	%esi, %ecx
	subl	%eax, %ecx
	cmpl	$1, %ecx
	je	.LBB0_4
# BB#2:                                 # %bb
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpl	$2, %ecx
	jne	.LBB0_7
# BB#3:                                 # %bb.bb8_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	40(%esp), %eax          # 4-byte Reload
	leal	1(%eax,%eax), %eax
	movl	%eax, 40(%esp)          # 4-byte Spill
	jmp	.LBB0_5
.LBB0_4:                                # %bb7
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	32(%esp)                # 4-byte Folded Spill
	movl	$3, 40(%esp)            # 4-byte Folded Spill
.LBB0_5:                                # %bb8
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%edi
	movl	32(%esp), %eax          # 4-byte Reload
	leal	3(%eax), %ecx
	cmpl	$1499999999, %esi       # imm = 0x59682EFF
	movl	$-1, %edx
	movl	$1, %ebp
	cmovll	%ebp, %edx
	cmovgel	%eax, %ecx
	addl	36(%esp), %ecx          # 4-byte Folded Reload
	addl	%edx, %ebx
	addl	40(%esp), %ebx          # 4-byte Folded Reload
	addl	28(%esp), %edi          # 4-byte Folded Reload
	incl	%esi
	cmpl	$2000000000, %esi       # imm = 0x77359400
	movl	%ebx, %eax
	jne	.LBB0_1
	jmp	.LBB0_6
.LBB0_7:                                # %bb9
                                        #   in Loop: Header=BB0_1 Depth=1
	addl	24(%esp), %ebx          # 4-byte Folded Reload
	movl	40(%esp), %eax          # 4-byte Reload
	leal	1(%ebx,%eax,2), %eax
	addl	28(%esp), %edi          # 4-byte Folded Reload
	addl	36(%esp), %ebp          # 4-byte Folded Reload
	incl	%esi
	cmpl	$2000000000, %esi       # imm = 0x77359400
	movl	%ebp, %ecx
	jne	.LBB0_1
# BB#8:                                 # %bb17
	movl	%eax, 12(%esp)
	movl	%edi, 8(%esp)
	movl	%ebp, 4(%esp)
.LBB0_9:                                # %bb17
	movl	$.L.str, (%esp)
	call	printf
	movl	$10, (%esp)
	call	putchar
	call	clock
	subl	20(%esp), %eax          # 4-byte Folded Reload
	movl	$274877907, %ecx        # imm = 0x10624DD3
	imull	%ecx
	movl	%edx, %eax
	shrl	$31, %eax
	sarl	$6, %edx
	addl	%eax, %edx
	movl	%edx, 4(%esp)
	movl	$.L.str1, (%esp)
	call	printf
	addl	$44, %esp
	popl	%esi
	popl	%edi
	popl	%ebx
	popl	%ebp
	ret
.LBB0_6:                                # %bb17_new
	movl	%ebx, 12(%esp)
	movl	%edi, 8(%esp)
	movl	%ecx, 4(%esp)
	jmp	.LBB0_9
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
