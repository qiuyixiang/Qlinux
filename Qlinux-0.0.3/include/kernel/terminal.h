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

#ifndef __KERNEL_TERMINAL_H__
#define __KERNEL_TERMINAL_H__   1

#include <kernel/type.h>

#if defined(__CXX_DISPLAY_VGA__) && (__CXX_DISPLAY_VGA__ == 1)

#define TTY_COLOR_BLACK         VGA_COLOR_BLACK
#define TTY_COLOR_WHITE         VGA_COLOR_WHITE
#define TTY_COLOR_GREEN         VGA_COLOR_GREEN
#define TTY_COLOR_BLUE          VGA_COLOR_BLUE
#define TTY_COLOR_RED           VGA_COLOR_RED
#define TTY_COLOR_GREY          VGA_COLOR_GREY
#define TTY_COLOR_YELLOW        VGA_COLOR_YELLOW

#endif

// Public Function Interface For Kernel Main
extern void terminal_init(void);
extern void terminal_put_char(char character);
extern void terminal_put_string(const char * str);
extern void terminal_write(const char * buffer, uint32_t count);


#endif 