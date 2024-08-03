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

#ifndef __ARCH_I386_CPU_H__
#define __ARCH_I386_CPU_H__     1

#include <kernel/type.h>

// Public Function Interface For Kernel Main
extern void cpu_init(void);

// Reversed Function For Inner Implementation Of i386 CPU
#define i386_update_segment_cs(CS)  __asm__ volatile(       \
                                    "pushw %0 \n\t"         \
                                    "pushl $flash \n\t"     \
                                    "retf \n\t"             \
                                    "flash: nop \n\t"       \
                                    :: "r"(CS)              \
                                );
extern void i386_update_segment(uint16_t DS, uint16_t FS, uint16_t GS, uint16_t ES, uint16_t SS);

#endif





