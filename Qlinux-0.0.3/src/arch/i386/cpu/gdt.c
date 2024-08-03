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

#include <cpu/gdt.h>
#include <cpu/cpu.h>
#include <kernel/terminal.h>
#include <kernel/macro.h>


// Macros For Intel I386 Global Descriptor Table
#define RING_0                  0
#define RING_1                  1
#define RING_2                  2
#define RING_3                  3

/* Field L OF Global Descriptor */
#define GD_L_64_BITS           1
#define GD_L_32_BITS           0
/* Field AVL OF Global Descriptor */
#define GD_AVL_DEFAULT         0
#define GD_AVL_TRUE            1
#define GD_AVL_FALSE           0
/* Field D/B OF Global Descriptor */
#define GD_DB_16_BITS          0
#define GD_DB_32_BITS          1
/* Field DPL OF Global Descriptor */
#define GD_DPL_0               RING_0
#define GD_DPL_1               RING_1
#define GD_DPL_2               RING_2
#define GD_DPL_3               RING_3
/* Field G OF Global Descriptor */
#define GD_G_BYTE              0
#define GD_G_4K                1
/* Field P OF Global Descriptor */
#define GD_P_PRESENT           1
#define GD_P_NON_PRESENT       0

/* Based Address OF Global Descriptor */
#define _GD_BASE_ADDR_LOW(_ADDR)          (_ADDR & 0xffff)
#define _GD_BASE_ADDR_MIDDLE(_ADDR)       ((_ADDR & 0x00ff0000) >> 16)
#define _GD_BASE_ADDR_HIGH(_ADDR)         ((_ADDR & 0xff000000) >> 24)

/* Limit Offset OF Global Descriptor */
#define _GD_LIMIT_LOW(LIMIT)              (LIMIT & 0x0ffff)
#define _GD_LIMIT_HIGH(LIMIT)             ((LIMIT & 0xf0000) >> 16)

/* S Field OF Global Descriptor */
#define GD_S_SYSTEM                 0
#define GD_S_NON_SYSTEM             1

/* Type Field OF Global Descriptor */
#define GD_TYPE_CODE_RD             0b1010
#define GD_TYPE_CODE_NON_RD         0b1000
#define GD_TYPE_CODE_CONF           0b1100
#define GD_TYPE_CODE_NON_CONF       0b1000
#define GD_TYPE_DATA_WR             0b0010
#define GD_TYPE_DATA_NON_WR         0b0000
#define GD_TYPE_DATA_ED             0b0100
#define GD_TYPE_DATA_NON_ED         0b0000

#define _GD_TYPE_CODE               0b1000
#define _GD_TYPE_DATA               0b0000
#define _GD_TYPE_FIELD_DATA(_WR, _ED)       (_WR | _ED  | _GD_TYPE_DATA)
#define _GD_TYPE_FIELD_CODE(_RD, _CONF)     (_RD | _CONF | _GD_TYPE_CODE)

#define GD_TYPE_DATA(WR, ED)        _GD_TYPE_FIELD_DATA(WR, ED)
#define GD_TYPE_CODE(RD, CONF)      _GD_TYPE_FIELD_CODE(RD, CONF)

// Macros For Selector
#define GD_SELECTOR_RPL0        RING_0
#define GD_SELECTOR_RPL1        RING_1
#define GD_SELECTOR_RPL2        RING_2
#define GD_SELECTOR_RPL3        RING_3

#define GD_SELECTOR_TI_GDT              0b000
#define GD_SELECTOR_TI_LDT              0b100
#define GD_SELECTOR(INDEX, TI, RPL)     ((INDEX << 3) | TI | RPL)

#define DEFAULT_BASE_ADDRESS            0x00000000
#define DEFAULT_LIMIT_OFFSET            0xfffff

// Static Variables and Macro
#define DEFAULT_DESCRIPTOR_VALUE    0x0000000000000000
#define MAXI_DESCRIPTOR_TABLE_SIZE  8
static __gd_t __gdt[MAXI_DESCRIPTOR_TABLE_SIZE];

static ALWAYS_INLINE void _init_gdt_0(void * __start, uint32_t __count){
    for (unsigned char * __buffer = (unsigned char *)__start; __count; --__count, ++__buffer)
        *__buffer = 0x00;
}
static void __cpu_set_gdt_index(uint16_t __seg_index, uint32_t __seg_base_addr, uint32_t __seg_limit,
                                 uint8_t __seg_dpl, uint8_t __seg_S, uint8_t __seg_type){
    if (__seg_index >= MAXI_DESCRIPTOR_TABLE_SIZE)
        return;
    if (__seg_index == 0){
        _init_gdt_0((void*)&__gdt[0], sizeof(__gd_t));
        return;
    }
    __gdt[__seg_index].seg_base_addr_high = _GD_BASE_ADDR_HIGH(__seg_base_addr);
    __gdt[__seg_index].seg_base_addr_middle = _GD_BASE_ADDR_MIDDLE(__seg_base_addr);
    __gdt[__seg_index].seg_base_addr_low = _GD_BASE_ADDR_LOW(__seg_base_addr);
    __gdt[__seg_index].seg_limit_low = _GD_LIMIT_LOW(__seg_limit);
    __gdt[__seg_index].seg_limit_high = _GD_LIMIT_HIGH(__seg_limit);
    __gdt[__seg_index].seg_p_field = GD_P_PRESENT;
    __gdt[__seg_index].seg_avl_field = GD_AVL_DEFAULT;
    __gdt[__seg_index].seg_l_field = GD_L_32_BITS;
    __gdt[__seg_index].seg_DB_field = GD_DB_32_BITS;
    __gdt[__seg_index].seg_G_field = GD_G_4K;
    __gdt[__seg_index].seg_type_field = __seg_type;
    __gdt[__seg_index].seg_S_field = __seg_S;
    __gdt[__seg_index].seg_dpl_field = __seg_dpl;

}
static void __cpu_lgdt(uint32_t _gdt_addr, uint16_t _gdt_limit){
    struct __gdtr_t gdtr_l;
    gdtr_l._gdt_base_addr = _gdt_addr;
    gdtr_l._gdt_limit = _gdt_limit;
    __asm__ volatile( "lgdt %0":: "m"(gdtr_l));
}
void __cpu_gdt_init(void){
/*
* Global Descriptor Structure
* Index 0      : Reserved 
* Index 1      : Ring 0 Code Segment
* Index 2      : Ring 0 Data Segment
* Index 3      : Ring 3 Code Segment
* Index 4      : Ring 3 Data Segment
* Index 5 - 7  : Reserved 
*/
    // The CPU Memory Manage Model : Flat Model
    // Initialized Segment Descriptor And Global Descriptor Table
    __cpu_set_gdt_index(0, DEFAULT_DESCRIPTOR_VALUE, 0x00000, 0, 0, 0);
    __cpu_set_gdt_index(1, DEFAULT_BASE_ADDRESS, DEFAULT_LIMIT_OFFSET, GD_DPL_0, 
                        GD_S_NON_SYSTEM, GD_TYPE_CODE(GD_TYPE_CODE_RD, GD_TYPE_CODE_NON_CONF));
    __cpu_set_gdt_index(2, DEFAULT_BASE_ADDRESS, DEFAULT_LIMIT_OFFSET, GD_DPL_0,
                        GD_S_NON_SYSTEM, GD_TYPE_DATA(GD_TYPE_DATA_WR, GD_TYPE_DATA_NON_ED));
    __cpu_set_gdt_index(3, DEFAULT_BASE_ADDRESS, DEFAULT_LIMIT_OFFSET, GD_DPL_3, 
                        GD_S_NON_SYSTEM, GD_TYPE_CODE(GD_TYPE_CODE_RD, GD_TYPE_CODE_NON_CONF));
    __cpu_set_gdt_index(4, DEFAULT_BASE_ADDRESS, DEFAULT_LIMIT_OFFSET, GD_DPL_3,
                        GD_S_NON_SYSTEM, GD_TYPE_DATA(GD_TYPE_DATA_WR, GD_TYPE_DATA_NON_ED));
    __cpu_lgdt((uint32_t)__gdt, sizeof(__gd_t) * MAXI_DESCRIPTOR_TABLE_SIZE - 1);
    terminal_put_string("[INIT ]\tI386 CPU SEGMENT DESCRIPTOR TABLE (GDT) INITIALIZED SUCCESSFULLY!\n");

    const uint16_t SELECTOR_CODE_RING0  =   GD_SELECTOR(1, GD_SELECTOR_TI_GDT, GD_SELECTOR_RPL0);
    const uint16_t SELECTOR_DATA_RING0  =   GD_SELECTOR(2, GD_SELECTOR_TI_GDT, GD_SELECTOR_RPL0);
    i386_update_segment(SELECTOR_DATA_RING0, SELECTOR_DATA_RING0, SELECTOR_DATA_RING0,
                        SELECTOR_DATA_RING0, SELECTOR_DATA_RING0);
    
    i386_update_segment_cs(SELECTOR_CODE_RING0);
    terminal_put_string("[RESET]\tI386 CPU SEGMENT SELECTOR RESET SUCCESSFULLY!\n");
}