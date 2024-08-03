/**
 * Copyright (C) 2024 QIUYIXIANG
 * Project : Qlinux
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#define __ASM_FILE__    1

#if defined(__CXX_MULTIBOOT__) && (__CXX_MULTIBOOT__ == 1)
#include <boot/multiboot.h>

#define STACK_SIZE  0x4000
.section .multiboot
    .align 4
    .long MB_HD_MAGIC_HEADER
    .long MB_HD_FLAGS
    .long MB_HD_CHECK_SUM

# Kernel Stack Here
.section .bss
    .align 16
    _kernel_stack_base:
    .skip STACK_SIZE        # 16 Kib
    _kernel_stack_top:

.section .text

.global _start
.extern kernel_main

.type kernel_main, @function
.type _start, @function

# Kernel Entry Address
_start:
    # Set Up Kernel Stack
    movl $_kernel_stack_top, %esp

    push %ebp
    movl %esp, %ebp

    # void kernel_main(uint32_t _mb_checksum, uint32_t * _mb_info_table);
    pushl %ebx
    pushl %eax

    call kernel_main

    nop
    cli
# Wait for power off
_hlt:
    hlt
    jmp _hlt

#endif

#if defined(__CXX_MULTIBOOT__) && (__CXX_MULTIBOOT__ == 2)
#include <boot/multiboot2.h>
#endif












