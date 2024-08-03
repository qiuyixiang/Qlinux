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

#ifndef __DRIVER_VGA_VAG_H__
#define __DRIVER_VGA_VAG_H__    1

#include <kernel/type.h>

typedef enum __vga_color_attr{
    VGA_COLOR_BLACK         =   0,
    VGA_COLOR_BLUE          =   1,
    VGA_COLOR_GREEN         =   2,
    VGA_COLOR_SYAN          =   3,
    VGA_COLOR_RED           =   4,
    VGA_COLOR_MAGENTA       =   5,
    VGA_COLOR_BROWN         =   6,
    VGA_COLOR_WHITE         =   7,
    VGA_COLOR_GREY          =   8,
    VGA_COLOR_LIGHT_BLUE    =   9,
    VGA_COLOR_LIGHT_GREEN   =   10,
    VGA_COLOR_LIGHT_CYAN    =   11,
    VGA_COLOR_LIGHT_RED     =   12,
    VGA_COLOR_LIGHT_MAGENTA =   13,
    VGA_COLOR_YELLOW        =   14,
    VGA_COLOR_LIGHT_WHITE   =   15
}vga_color_attr;

// VGA Public Function Interface
extern void vga_init(void);

extern void vga_put_char(char __character);
extern void vga_put_string(const char * __ptr);
extern void vga_write(const char * __ptr, uint32_t __count);

extern void vga_set_font_color(vga_color_attr __color);
extern void vga_set_bk_color(vga_color_attr __color);
extern void vga_set_theme(vga_color_attr __font, vga_color_attr __back_ground);
extern void vga_clear_screen();

#endif