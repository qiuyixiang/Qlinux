/**
 * Copyright (C) 2024 QIUYIXIANG
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


/// This Header Files Using GNU GRUB Multiboot 1

#ifndef __ARCH_I386_MULTIBOOT_H__
#define __ARCH_I386_MULTIBOOT_H__   1

#ifndef __ASM_FILE__

#include <kernel/type.h>

#endif

// Macros For ASM and C
#define MB_HD_MAGIC_HEADER              0x1BADB002
#define _MB_HD_FLAGS_4K_ALIGN           0b001
#define _MB_HD_FLAGS_DETECT_MEM         0b010
#define _MB_HD_FLAGS_VIDEO_MODE         0b000
#define MB_HD_FLAGS                     (_MB_HD_FLAGS_4K_ALIGN | _MB_HD_FLAGS_DETECT_MEM | _MB_HD_FLAGS_VIDEO_MODE)
#define MB_HD_CHECK_SUM                 -(MB_HD_FLAGS + MB_HD_MAGIC_HEADER)

#define MB_VALID_CHECKSUM_EAX           0x2BADB002
#endif



