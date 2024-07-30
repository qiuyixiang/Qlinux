/*
* Copyright (C) QIUYIXIANG
* 
* Main File For Qlinux Kernel And the whole Project
* This File Control all of the project and source files
* And Include the main loop of the kernel procedure
* Including User Space and Kernel Space and also include 
* some general Hardware and Software Interaction parts.
*
* @Date 07-28-2024
*/

// kernel Related Header Files
#include <kernel/types.h>

// Architecture Related Header Files
#include <arch/i386/multiboot.h>
#include <arch/i386/gdt.h>
#include <arch/monitor/vga.h>

/* Kernel Initialization Function Specification
*  This Function will Initialized Some Firmware and Hardware Driver
*  And Create Kernel Data Structure about some Hardware and 
*  Architecture  Related Information Table
*  After Initialization it will call _kernel_main_
*/  
void _kernel_init_(uint32_t __mb_verify, uint32_t* __mb_info_tb){

    // Initialize VGA Monitor
    vga_init(VGA_THEME_DARK);
    vga_put_string("[INIT]\tVGA Text Display Mode Initialized Successfully \n");
    // Check MultiBoot Success Flags
    if (__mb_verify == MB_CHECK_SUCCESS)
        vga_put_string("[CHECK]\tMultiBoot Header CHECKSUM Check Finished !\n");
    // Initialize Global Descriptor Table And Update Segment Selectors
    gdt_init();
    gdtr_t * gdtr_register = gdt_get_gdtr();
    if (gdtr_register->_gdtr_limit == gdt_get_limit() && gdtr_register->_gdtr_base_addr == (uint32_t)gdt_get_addr())
        vga_put_string("[INIT]\tGlobal Descriptor Initialized Successfully \n");
    else
        vga_put_string("[ERROR]\tGlobal Descriptor Initialized Failed Try It Again Later !!!\n");
    vga_put_string("[INIT]\tSegment Register Selector Initialized Successfully \n");
    (void)__mb_info_tb;
    while (1)
    {
        
    }
    
}

