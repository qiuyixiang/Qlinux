# This File Is Used For MultiBoot Specification Header
# Accoring MultiBoot Specification This File Need To Define Some Header Information
# Multiboot Bootloader has already loader the kernel to memory and enter Protected Mode
# @date 07-28-2024
# @copyright (C) QIUYIXIANG


# This Macro Specify Don't Include Some ASM unrelated Type Define
#define __USING_ASM__ 1

# Using MultiBoot Version 1
#if defined(__MULTIBOOT_VERSION__) && (__MULTIBOOT_VERSION__ == 1)
#include <arch/i386/multiboot.h>

# MultiBoot Header For MultiBoot Version 1
.section .multiboot
    .align 4
    .long MB_HD_MAGIC_HEADER
    .long MB_HD_FLAGS
    .long MB_HD_CHECKSUM

# The Stack on x86 must be 16-byte aligned according to the
# System V ABI standard
.section .bss
    .align 16
    # The Size of the Stack is 16 Kib
    _kernel_stack_bottom:
        .skip 16384  
    _kernel_stack_top:

# This is the entry of the kernel, after Bootloader load kernel to the memory
# It will jump here and execute the following code
.section .text
.global _start
.extern _kernel_init_
.type _start, @function
_start:
    # Set Kernel Stack Position
    movl $_kernel_stack_top, %esp

    # Call Kernel Initialization Function Defined In C
    # Accroding to the C ANSI/ISO Function Call Specification __cdecl__
    # The Argument Push into the stack from right to left
    # Kernel Init Specification :
    # void _kernel_init_(uint32_t __mb_verify, uint32_t* __mb_info_tb)
    pushl %ebx
    pushl %eax
    call _kernel_init_
    
    # Because return from _kernel_init is meaningless so just wait for power off
    cli
_hlt:
    hlt 
    jmp _hlt
#endif

# Using MultiBoot Version 2
#if defined(__MULTIBOOT_VERSION__) && (__MULTIBOOT_VERSION__ == 2)
#include <arch/i386/multiboot2.h>
#endif




