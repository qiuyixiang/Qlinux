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
#include <arch/i386/cpu.h>

#define __CPU_DEBUGGER__       1

// Update CPU Segment Registers
void cpu_update_segment_reg(uint16_t DS, uint16_t SS, 
                            uint16_t FS, uint16_t GS, uint16_t ES){
#if defined(__CPU_DEBUGGER__) && (__CPU_DEBUGGER__ == 2)
    __ASM_BOCHS_DEBUGGER__
#endif
    __asm__ volatile(
        "movw %0, %%ds \n\t"
        "movw %1, %%ss \n\t"
        "movw %2, %%fs \n\t"
        "movw %3, %%gs \n\t"
        "movw %4, %%es \n\t"
        : : "r"(DS), "r"(SS), "r"(FS), "r"(GS), "r"(ES)
        : "memory", "cc"
    );
}
inline void cpu_enable_interrupt(void){
    __asm__ volatile("sti");
}
inline void cpu_disable_interrupt(void){
    __asm__ volatile("cli");
}
inline void cpu_wait(void){
    __asm__ volatile("hlt");
}