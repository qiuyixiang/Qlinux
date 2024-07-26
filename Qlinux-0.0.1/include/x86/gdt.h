// This File Define Some Macros for GDT Attributes
// Reference Manual : Intel IA-32 Developer Manual Volume 3
// Global Descriptor Table

// Create on 07/25/2023

#ifndef __X86_GDT__
#define __X86_GDT__     1

// A Reverse Switch Macro for more Advanced GDT operation
#define MACRO_USING_C_GDT       1
#define _GD_BASE_OFFSET         32

// Global Descriptor Macros 

// Single New Type For Global Descriptor with fixed size : 8 bytes
// And this macro is just used as type-cast
#define __GD_TYPE               unsigned long long
// Because of the simplicity of this kernel, only 16 Global descriptor is enough to use.
#define __GDT_SIZE              16

/* Segment Base Address */
// Set Segment Base Address
#define __GD_SET_BASE_LOW(_BASE_LOW_ADDR)               ((_BASE_LOW_ADDR) << 16)
#define __GD_SET_BASE_MIDDLE(_BASE_MIDDLE_ADDR)         (_BASE_MIDDLE_ADDR)
#define __GD_SET_BASE_HIGH(_BASE_HIGH_ADDR)             ((_BASE_HIGH_ADDR) << 24)
#define __GD_BASE_LOW(_BASE_ADDR)                       __GD_SET_BASE_LOW(_BASE_ADDR & 0xffff)
#define __GD_BASE_HIGH(_BASE_ADDR)                      ((__GD_SET_BASE_HIGH(_BASE_ADDR >> 24)) |               \
                                                        (__GD_SET_BASE_MIDDLE((_BASE_ADDR >> 16) & 0xff)))
#define _GD_SET_BASE_ADDR(_BASE_ADDR)                   (((__GD_TYPE)(__GD_BASE_HIGH(_BASE_ADDR)) << 32) |      \
                                                        __GD_BASE_LOW(_BASE_ADDR))
                                                        
/* Segment Limit */                                                        
// Macros for Global Descriptor Segment Limit
#define __GD_SET_SEG_LIMIT_LOW(_SEG_LIMIT)               ((_SEG_LIMIT) & 0xffff)
#define __GD_SET_SEG_LIMIT_HIGH(_SEG_LIMIT)              ((_SEG_LIMIT) << 16)
#define _GD_SET_SEG_LIMIT(_SEG_LIMIT)                   (((__GD_TYPE)(_GD_SET_SEG_LIMIT_HIGH((_SEG_LIMIT & 0xf0000) >> 16)) << 32) \
                                                        | _GD_SET_SEG_LIMIT_LOW(_SEG_LIMIT))

/* Segment Type */
// All of this attribute dependent on S field, this is non-system segment
// Data Segment
#define _GD_DATA_WRITE              0b0010
#define _GD_DATA_NON_WRITE          0b0000
#define _GD_DATA_NON_ACC            0b0000
#define _GD_DATA_ACC                0b0001
#define _GD_DATA_RD                 0b0000
#define _GD_DATA_ED                 0b0100
#define _GD_DATA_NON_ED             0b0000
#define _GD_CON_DATA(_WR, _ED)      (_GD_DATA_RD | _WR | _ED)
// Code Segment
#define _GD_CODE_EXE                0b1000
#define _GD_CODE_ACC                0b1001
#define _GD_CODE_NON_ACC            0b1000
#define _GD_CODE_CONF               0b1100
#define _GD_CODE_NON_CONF           0b1000
#define _GD_CODE_RD                 0b1010
#define _GD_CODE_NON_RD             0b1000
#define _GD_CON_CODE(_CONF, _RD)    (_GD_CODE_EXE | _CONF | _RD)
// Construct Segment Type using Constructor Macros
#define _GD_SET_SEG_TYPE(_SEG_TYPE)                     ((__GD_TYPE)_SEG_TYPE << (_GD_BASE_OFFSET + 8))   

/* Segment S Type */
#define _GD_S_SYS           0
#define _GD_S_NON_SYS       1
#define _GD_SET_SEG_S_TYPE(_SEG_S_TYPE)                 ((__GD_TYPE)_SEG_S_TYPE << (_GD_BASE_OFFSET + 12))

/* Segment Present Flag */
#define _GD_PRESENT         1
#define _GD_NOT_PRESENT     0
#define _GD_SET_SEG_P_FLAG(_SEG_P_FLAG)                 ((__GD_TYPE)_SEG_P_FLAG << (_GD_BASE_OFFSET + 15))

/* Segment Available Flag (Reversed For Operating System Use) */
#define _GD_REVERSED_DEFAULT    0
#define _GD_SET_SEG_REVERSED_FLAG(_SEG_REVERSED_FLAG)   ((__GD_TYPE)_SEG_REVERSED_FLAG << (_GD_BASE_OFFSET + 20))

/* Segment granularity flag */
#define _GD_G_BYTE      0
#define _GB_G_4KB       1
#define _GD_SET_SEG_G(_SEG_G)                           ((__GD_TYPE)_SEG_G << (_GD_BASE_OFFSET + 23))

/* Segment descriptor privilege level flag */
#define _GD_DPL_0       0b00
#define _GD_DPL_1       0b01
#define _GD_DPL_2       0b10
#define _GD_DPL_3       0b11
#define _GD_SET_SEG_DPL(_SEG_DPL)                       ((__GD_TYPE)_SEG_DPL << (_GD_BASE_OFFSET + 13))

/* Segment Contain 64-bits Coding flags */
#define _GD_BIT64       1
#define _GD_BIT32       0
#define _GD_SET_SEG_BIT64(_SEG_BIT64)                   ((__GD_TYPE)_SEG_BIT64 << (_GD_BASE_OFFSET + 21))

/* Segment Default Operation Size */
#define _GD_DB_BIT16    0
#define _GD_DB_BIT32    1
#define _GD_SET_SEG_DB(_SEG_DB)                         ((__GD_TYPE)_SEG_DB << (_GD_BASE_OFFSET + 22))

// Type Define For Global Descriptor Table
typedef unsigned long long      _gd_t;
typedef unsigned long long*     _gd_ptr_t;

/// @brief This is the global static array of GDT
/// Access this array through include the header file
/// This Special Data Structure is part of kernel
extern _gd_t __gdt[__GDT_SIZE];

#endif