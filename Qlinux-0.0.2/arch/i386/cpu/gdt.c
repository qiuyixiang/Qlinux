/*
* Copyright (C) QIUYIXIANG
* 
* This File is About i386 Global Descriptor 
* Some Initialize And Constructor Function Defined here
* @Date 07-30-2024
*/

#include <arch/i386/gdt.h>
#include <kernel/macros.h>

#define __GDT_DEBUGGER__    1

// This is the private global descriptor array
// Invisible For Outer Space
__gd_t __gdt[GLOBAL_DESCRIPTOR_TABLE_SIZE];
uint16_t __gdt_limit = sizeof(__gd_t) * GLOBAL_DESCRIPTOR_TABLE_SIZE - 1;
// Visible For All Kernel Space
gdtr_t gdtr;

static inline void __lgdt(uint32_t __gdtr_base, uint16_t __gdtr_limit){
    gdtr._gdtr_base_addr = __gdtr_base;
    gdtr._gdtr_limit = __gdtr_limit;
#if defined(__GDT_DEBUGGER__) && __GDT_DEBUGGER__ == 2
    __ASM_BOCHS_DEBUGGER__
#endif 
    __INLINE_ASM__("lgdt %0": : "m"(gdtr));
}

// Public Interface
inline uint64_t* gdt_get_addr(void){
    return (uint64_t*)&__gdt[0];
}
inline uint16_t gdt_get_limit(void){
    return __gdt_limit;
}
inline gdtr_t* gdt_get_gdtr(void){
    return &gdtr;
}
inline void gdt_set_index(uint16_t _index, uint32_t _base_addr, uint32_t _limit, 
                        uint8_t _dpl, uint8_t _type, uint8_t _S){
// Safeguard for Index == 0 which is a reversed placeholder
    if (_index == 0){
        __gdt[0] = (__gd_t)0x0000000000000000;
        return;
    }
#if defined(GDT_VERSION) && GDT_VERSION == 1
    __gdt[_index] = _GD_BASE_ADDR(_base_addr) | _GD_LIMIT(_limit) | _GD_SET_DPL(_dpl)
                    | _GD_SET_TYPE(_type) | _GD_SET_S(_S) |  _GD_SET_AVL(GD_AVL_DEFAULT)
                    | _GD_SET_L(GD_L_MODE_NON_64) | _GD_SET_DB(GD_DB_32_BITS)
                    | _GD_SET_P(GD_P_PRESENT) | _GD_SET_G(GD_G_4K);
#endif

#if defined(GDT_VERSION) && GDT_VERSION == 2
    // TODO
#endif
}
// Some Inner Macros
#define MAXI_LIMIT_ADDR         0xfffff
#define GD_BASE_ADDRESS_ZERO    0x00000000
void gdt_init(void){
    /*
     * Global Descriptor Structure
     * Index 0      : Reversed 
     * Index 1      : Ring 0 Code Segment
     * Index 2      : Ring 0 Data Segment
     * Index 3      : Ring 3 Code Segment
     * Index 4      : Ring 3 Data Segment
     * Index 5 - 7  : Reversed 
    */
    gdt_set_index(0, GD_BASE_ADDRESS_ZERO, 0x00000, 0x0, 0x0, 0x0);
    gdt_set_index(1, GD_BASE_ADDRESS_ZERO, MAXI_LIMIT_ADDR, GD_DPL_0, 
                GD_TYPE_CODE(GD_TYPE_CODE_RD, GD_TYPE_CODE_NON_CONF), GD_S_NON_SYSTEM);
    gdt_set_index(2, GD_BASE_ADDRESS_ZERO, MAXI_LIMIT_ADDR, GD_DPL_0, 
                GD_TYPE_DATA(GD_TYPE_DATA_WR, GD_TYPE_DATA_NON_ED), GD_S_NON_SYSTEM);
    gdt_set_index(3, GD_BASE_ADDRESS_ZERO, MAXI_LIMIT_ADDR, GD_DPL_3, 
                GD_TYPE_CODE(GD_TYPE_CODE_RD, GD_TYPE_CODE_NON_CONF), GD_S_NON_SYSTEM);
    gdt_set_index(4, GD_BASE_ADDRESS_ZERO, MAXI_LIMIT_ADDR, GD_DPL_3, 
                GD_TYPE_DATA(GD_TYPE_DATA_WR, GD_TYPE_DATA_NON_ED), GD_S_NON_SYSTEM);
    // Update GDTR (Global Descriptor Table Register)
    __lgdt((uint32_t)gdt_get_addr(), gdt_get_limit());
}
