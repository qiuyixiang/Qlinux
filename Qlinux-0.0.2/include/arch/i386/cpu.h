/*
* Copyright (C) QIUYIXIANG
* 
* This File is About x86 x86_64 i386 CPU Operation
* Functions And Structures about :
*   - general purpose registers
*   - IO port operations
*   - segment registers
*   - control registers
*   - system registers
* @Date 07-30-2024
*/

#ifndef __ARCH_I386_CPU_H__
#define __ARCH_I386_CPU_H__     1

#define USING_I386_CPU          1
#include <kernel/types.h>
#include <kernel/macros.h>

/// CPU Related Function Declaration
extern void cpu_update_segment_reg(uint16_t DS, uint16_t SS, 
                                uint16_t FS, uint16_t GS, uint16_t ES);
extern void cpu_enable_interrupt(void);
extern void cpu_disable_interrupt(void);
extern void cpu_wait(void);

#define cpu_update_segment_reg_cs(CS)     __asm__ volatile(         \
                                            "pushw %0 \n\t"         \
                                            "pushl $flash \n\t"     \
                                            "retf \n\t"             \
                                            "flash:\n\t"            \   
                                            ::"i"(CS)               \
                                        )
#endif