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
	movl	%esi, %eax
	movl	%esi, %ecx
	movl	%esi, %edx
	.align	16, 0x90
.LBB0_1:                                # %bb
                                        # =>This Inner Loop Header: Depth=1
	leal	2(%eax), %edi
	cmpl	$1999999999, %esi       # imm = 0x773593FF
	movl	$-1, %ebp
	movl	$1, %ebx
	cmovll	%ebx, %ebp
	movl	%ebp, 20(%esp)          # 4-byte Spill
	cmovgel	%eax, %edi
	setl	%al
	movzbl	%al, %eax
	addl	%eax, %ecx
	cmpl	$200000000, %esi        # imm = 0xBEBC200
	setg	%bl
	movzbl	%bl, %ebx
	movl	%ebx, 28(%esp)          # 4-byte Spill
	xorl	$1, %eax
	addl	%ebx, %edx
	xorl	$1, %ebx
	movl	%ebx, 32(%esp)          # 4-byte Spill
	cmpl	$1999999999, %esi       # imm = 0x773593FF
	leal	4(%ebx,%ecx), %ebx
	movl	32(%esp), %ebp          # 4-byte Reload
	leal	1(%ebp,%ecx), %ebp
	cmovgel	%ebp, %ebx
	addl	%eax, %edx
	movl	28(%esp), %ecx          # 4-byte Reload
	leal	(%eax,%ecx), %eax
	movl	%eax, 24(%esp)          # 4-byte Spill
	cmpl	$1, %esi
	je	.LBB0_4
# BB#2:                                 # %bb
                                        #   in Loop: Header=BB0_1 Depth=1
	cmpl	$2, %esi
	jne	.LBB0_7
# BB#3:                                 # %bb.bb8_crit_edge
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	28(%esp), %eax          # 4-byte Reload
	leal	1(%eax,%eax), %eax
	movl	%eax, 28(%esp)          # 4-byte Spill
	jmp	.LBB0_5
.LBB0_4:                                # %bb7
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%ebp
	movl	$3, 28(%esp)            # 4-byte Folded Spill
.LBB0_5:                                # %bb8
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%edx
	leal	3(%ebp), %ecx
	cmpl	$1999999999, %esi       # imm = 0x773593FF
	movl	$-1, %eax
	movl	$1, %ebx
	cmovll	%ebx, %eax
	cmovgel	%ebp, %ecx
	addl	32(%esp), %ecx          # 4-byte Folded Reload
	addl	%eax, %edi
	addl	28(%esp), %edi          # 4-byte Folded Reload
	addl	24(%esp), %edx          # 4-byte Folded Reload
	incl	%esi
	cmpl	$2000000000, %esi       # imm = 0x77359400
	movl	%edi, %eax
	jne	.LBB0_1
	jmp	.LBB0_6
.LBB0_7:                                # %bb9
                                        #   in Loop: Header=BB0_1 Depth=1
	addl	20(%esp), %edi          # 4-byte Folded Reload
	movl	28(%esp), %eax          # 4-byte Reload
	leal	1(%edi,%eax,2), %eax
	addl	24(%esp), %edx          # 4-byte Folded Reload
	addl	32(%esp), %ebx          # 4-byte Folded Reload
	incl	%esi
	cmpl	$2000000000, %esi       # imm = 0x77359400
	movl	%ebx, %ecx
	jne	.LBB0_1
# BB#8:                                 # %bb17
	movl	%eax, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ebx, 4(%esp)
.LBB0_9:                                # %bb17
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
.LBB0_6:                                # %bb17_new
	movl	%edi, 12(%esp)
	movl	%edx, 8(%esp)
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
