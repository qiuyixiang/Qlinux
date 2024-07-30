// Copyright (C) QIUYIXIANG
// 
// This File Define Some Information About Intel 80386 CPU GDT
// And this file is compatible with i686, x86, x64
// this macros may be used by the kernel for initializing Global Descriptor Table
// @date 07-30-2024

#ifndef __ARCH_I386_GDT_H__
#define __ARCH_I386_GDT_H__  1

#include <kernel/types.h>

// Type Define For Global Descriptor Type
typedef unsigned long long                  __gd_t;
#define GLOBAL_DESCRIPTOR_TABLE_SIZE        8

// Type Define For GDTR (Global Descriptor Table Register)
typedef struct __gdtr_t{
    uint16_t _gdtr_limit;
    uint32_t _gdtr_base_addr;
} __attribute__((packed)) gdtr_t;

// Global Descriptor Register Global Variable Structure
extern gdtr_t gdtr;

// Declaration For GDT Functions 
extern void gdt_init(void);
extern uint64_t* gdt_get_addr(void);
extern uint16_t gdt_get_limit(void);
extern gdtr_t* gdt_get_gdtr(void);
extern void gdt_set_index(uint16_t _index, uint32_t _base_addr, 
                          uint32_t _limit, uint8_t _dpl,
                          uint8_t _type, uint8_t _S);

// Flags Control Macros Version For Global Descriptor Table
#define GDT_VERSION 1   
// Macros For Global Descriptor Table
// S field and Type field control the type of the segment descriptor
#define RING_0                  0x00
#define RING_1                  0x01
#define RING_2                  0x02
#define RING_3                  0x03
/* L Field OF Global Descriptor */
#define GD_L_MODE_64                1
#define GD_L_MODE_NON_64            0
/* AVL Field OF Global Descriptor */
#define GD_AVL_DEFAULT              0
/* P Field OF Global Descriptor */
#define GD_P_PRESENT                1       
#define GD_P_NON_PRESENT            0
/* D/B Field OF Global Descriptor */
#define GD_DB_16_BITS               0
#define GD_DB_32_BITS               1
/* DPL Field OF Global Descriptor */
#define GD_DPL_0                  RING_0
#define GD_DPL_1                  RING_1
#define GD_DPL_2                  RING_2
#define GD_DPL_3                  RING_3
/* G Field OF Global Descriptor */
#define GD_G_BYTES                  0
#define GD_G_4K                     1
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

#if defined(GDT_VERSION) && GDT_VERSION == 1

    // This Version of GDT Macros Construct Each Field Separately
    #define _GDT_CAST_TYPE      unsigned long long
    #define _GDT_OFF_FIELD      32

    /* Base Address Field OF Global Descriptor */
    #define _GD_BASE_LOW(BASE_ADDR)         ((BASE_ADDR & 0xffff) << 16)
    #define _GD_BASE_MIDDLE(BASE_ADDR)      ((_GDT_CAST_TYPE)((BASE_ADDR & 0xff0000) >> 16) << (_GDT_OFF_FIELD + 0))
    #define _GD_BASE_HIGH(BASE_ADDR)        ((_GDT_CAST_TYPE)((BASE_ADDR & 0xff000000) >> 24) << (_GDT_OFF_FIELD + 24))
    #define _GD_BASE_ADDR(BASE_ADDR)        (_GD_BASE_LOW(BASE_ADDR) | _GD_BASE_MIDDLE(BASE_ADDR) \
                                            | _GD_BASE_HIGH(BASE_ADDR))

    /* Limit Field OF Global Descriptor */
    #define _GD_LIMIT_LOW(LIMIT_SIZE)       (LIMIT_SIZE & 0xffff)
    #define _GD_LIMIT_HIGH(LIMIT_SIZE)      ((_GDT_CAST_TYPE)((LIMIT_SIZE & 0xf0000) >> 16) << (_GDT_OFF_FIELD + 16))
    #define _GD_LIMIT(LIMIT_SIZE)           (_GD_LIMIT_LOW(LIMIT_SIZE) | _GD_LIMIT_HIGH(LIMIT_SIZE))

    #define _GD_SET_L(FIELD_L)              ((_GDT_CAST_TYPE)FIELD_L << (_GDT_OFF_FIELD + 21))
    #define _GD_SET_AVL(FIELD_AVL)          ((_GDT_CAST_TYPE)FIELD_AVL << (_GDT_OFF_FIELD + 20))
    #define _GD_SET_P(FIELD_P)              ((_GDT_CAST_TYPE)FIELD_P << (_GDT_OFF_FIELD + 15))
    #define _GD_SET_DB(FIELD_DB)            ((_GDT_CAST_TYPE)FIELD_DB << (_GDT_OFF_FIELD + 22))
    #define _GD_SET_DPL(FIELD_DPL)          ((_GDT_CAST_TYPE)FIELD_DPL << (_GDT_OFF_FIELD + 13))
    #define _GD_SET_G(FIELD_G)              ((_GDT_CAST_TYPE)FIELD_G << (_GDT_OFF_FIELD + 23))
    #define _GD_SET_S(FIELD_S)              ((_GDT_CAST_TYPE)FIELD_S << (_GDT_OFF_FIELD + 12))
    #define _GD_SET_TYPE(FIELD_TYPE)        ((_GDT_CAST_TYPE)FIELD_TYPE << (_GDT_OFF_FIELD + 8))                
#endif 

#if defined(GDT_VERSION) && GDT_VERSION == 2
// This Version of GDT Macros Construct Fields Just Divide into Low and High Two Parts
// TODO:

#endif

// Type Define for Global Descriptor Selector
#define GD_SELECTOR_RPL0        RING_0
#define GD_SELECTOR_RPL1        RING_1
#define GD_SELECTOR_RPL2        RING_2
#define GD_SELECTOR_RPL3        RING_3
#define GD_SELECTOR_TI_GDT              0b000
#define GD_SELECTOR_TI_LDT              0b100
#define GD_SELECTOR(INDEX, TI, RPL)     ((INDEX << 3) | TI | RPL)

#endif