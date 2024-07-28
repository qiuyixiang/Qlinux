/* 
* Copyright (C) QIUYIXIANG
*
* Linker Script For Building This Project
*/


/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)

SECTIONS{
    /* Start Address Of The Kernel */
    . = 0x100000;
    /* Text Segment */
    .text BLOCK(4K) : ALIGN(4K){
        *(.multiboot)
        *(.text)
    }
    /* Read Only Data Segment */
    .rodata BLOCK(4K) : ALIGN(4K){
        *(.rodata)
    }
    /* Read-Write Data (Initialized) */
    .data BLOCK(4K) : ALIGN(4K){
        *(.data)
    }
    /* Read-Write Data (Uninitialized) and Stack */
    .bss BLOCK(4K) : ALIGN(4K){
        *(COMMON)
        *(.bss)
    }
}

