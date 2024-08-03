/**
 * Copyright (C) 2024 QIUYIXIANG
 * Project : Qlinux
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

#include <kernel/config.h>

// Include Header Files According to Architecture
#if defined(__CXX_ARCH__) && (__CXX_ARCH__ == i386)
#include <boot/boot.h>
#include <cpu/cpu.h>
#endif

#if defined(__CXX_ARCH__) && (__CXX_ARCH__ == x86_64)
#include <cpu/cpu.h>
#endif

// General Purpose Headers (Compatible With All Hardware Platform)
#include <kernel/terminal.h>
#include <kernel/type.h>

// Using GNU Grub Multiboot Will Have Two Arguments
#if defined(__CXX_MULTIBOOT__) && (__CXX_MULTIBOOT__ != 0)
void kernel_main(uint32_t _mb_checksum, uint32_t * _mb_info_table)
#else
// Other BootLoader Initialization 
void kernel_main(uint32_t * _boot_info_table)
#endif
{
    /// Initialize Terminal Device
    terminal_init();
#if defined(__CXX_MULTIBOOT__) && (__CXX_MULTIBOOT__ != 0)
    /// BootLoader Configuration (Only for Multiboot)
    boot_init(_mb_checksum, _mb_info_table);
#else 
    boot_init(_boot_info_table);
#endif
    /// Initialize CPU State
    cpu_init();

    while (1){
        
    }
    
}


