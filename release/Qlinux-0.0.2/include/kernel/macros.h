/*
* Copyright (C) QIUYIXIANG
*
* This File Define Some General Macros For Qlinux
* Include Test Macros, Info Macros and ASM Macros
* Date: 07-28-2024
*/

#ifndef __KERNEL_MACROS_H__
#define __KERNEL_MACROS_H__ 1

// Assembly Related Macros
#define __INLINE_ASM__(_INSTRUCTION)        __asm__ volatile(_INSTRUCTION)
#define __ASM_BOCHS_DEBUGGER__              __asm__ volatile("xchg %bx, %bx");

#endif