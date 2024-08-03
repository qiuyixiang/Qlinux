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

#ifndef __ARCH_I386_GDT_H__
#define __ARCH_I386_GDT_H__     1

#include <kernel/type.h>

typedef struct __gd{
    uint64_t seg_limit_low          :   16;
    uint64_t seg_base_addr_low      :   16;
    uint64_t seg_base_addr_middle   :   8;
    uint64_t seg_type_field         :   4;
    uint64_t seg_S_field            :   1;
    uint64_t seg_dpl_field          :   2;
    uint64_t seg_p_field            :   1;
    uint64_t seg_limit_high         :   4;
    uint64_t seg_avl_field          :   1;
    uint64_t seg_l_field            :   1;
    uint64_t seg_DB_field           :   1;
    uint64_t seg_G_field            :   1;
    uint64_t seg_base_addr_high     :   8;
}__attribute__((packed)) __gd_t;

struct __gdtr_t{
    uint16_t _gdt_limit;
    uint32_t _gdt_base_addr;
}__attribute__((packed));

extern void __cpu_gdt_init(void);

#endif