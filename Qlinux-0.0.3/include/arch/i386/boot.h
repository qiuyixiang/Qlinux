/**
 * Copyright (C) 2024 QIUYIXIANG
 * Project : Qlinux
 * 
 * MIT License
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

#ifndef __ARCH_I386_BOOT_H__
#define __ARCH_I386_BOOT_H__   1

#include <kernel/type.h>

#if defined(__CXX_MULTIBOOT__) && (__CXX_MULTIBOOT__ != 0)
// Include MultiBoot Header 
#if (__CXX_MULTIBOOT__ == 1)
#include <arch/i386/multiboot.h>
#endif 
#if (__CXX_MULTIBOOT__ == 2)
#include <arch/i386/multiboot2.h>
#endif

#endif

extern void boot_init(uint32_t _mb_checksum, uint32_t * _mb_info_table);

#endif