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
	movl	$1, %ebp
	.align	16, 0x90
.LBB0_1:                                # %bb
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$200000000, %esi        # imm = 0xBEBC200
	setg	%bl
	movzbl	%bl, %edi
	movl	%edi, 28(%esp)          # 4-byte Spill
	addl	%edi, %edx
	leal	2(%eax), %ebx
	cmpl	$1999999999, %esi       # imm = 0x773593FF
	cmovgel	%eax, %ebx
	setl	%al
	movzbl	%al, %eax
	addl	%eax, %ecx
	xorl	$1, %edi
	movl	%edi, 20(%esp)          # 4-byte Spill
	leal	1(%edi,%ecx), %ecx
	movl	%ecx, 32(%esp)          # 4-byte Spill
	xorl	$1, %eax
	addl	%eax, %edx
	cmpl	$1, %esi
	je	.LBB0_3
# BB#2:                                 # %bb
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	28(%esp), %ecx          # 4-byte Reload
	leal	1(%ecx,%ecx), %ecx
	movl	%ecx, 24(%esp)          # 4-byte Spill
	cmpl	$2, %esi
	je	.LBB0_4
	jmp	.LBB0_5
.LBB0_3:                                # %bb7
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	32(%esp)                # 4-byte Folded Spill
	movl	$3, 24(%esp)            # 4-byte Folded Spill
.LBB0_4:                                # %bb8
                                        #   in Loop: Header=BB0_1 Depth=1
	incl	%edx
.LBB0_5:                                # %bb9
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	32(%esp), %ecx          # 4-byte Reload
	leal	3(%ecx), %ecx
	cmpl	$1999999999, %esi       # imm = 0x773593FF
	movl	$-1, %edi
	cmovll	%ebp, %edi
	cmovgel	32(%esp), %ecx          # 4-byte Folded Reload
	addl	20(%esp), %ecx          # 4-byte Folded Reload
	addl	%edi, %ebx
	addl	24(%esp), %ebx          # 4-byte Folded Reload
	addl	28(%esp), %eax          # 4-byte Folded Reload
	addl	%eax, %edx
	incl	%esi
	cmpl	$2000000000, %esi       # imm = 0x77359400
	movl	%ebx, %eax
	jne	.LBB0_1
# BB#6:                                 # %bb17
	movl	%ebx, 12(%esp)
	movl	%edx, 8(%esp)
	movl	%ecx, 4(%esp)
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
