/**
 * Copyright (C) 2024 QIUYIXIANG
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
#include <kernel/terminal.h>

// Low Layer Hardware Driver Header
#if defined(__CXX_DISPLAY_VGA__) && (__CXX_DISPLAY_VGA__ == 1)
#include <driver/vga/vga.h>
#endif 

void terminal_put_char(char character){
#if defined(__CXX_DISPLAY_VGA__) && (__CXX_DISPLAY_VGA__ == 1)
    vga_put_char(character);
#endif 
}
void terminal_put_string(const char * str){
#if defined(__CXX_DISPLAY_VGA__) && (__CXX_DISPLAY_VGA__ == 1)
    vga_put_string(str);
#endif 
}
void terminal_write(const char * buffer, uint32_t count){
#if defined(__CXX_DISPLAY_VGA__) && (__CXX_DISPLAY_VGA__ == 1)
    vga_write(buffer, count);
#endif 
}
void terminal_init(void){
#if defined(__CXX_DISPLAY_VGA__) && (__CXX_DISPLAY_VGA__ == 1)
    vga_init();
#endif 
    terminal_put_string("[INIT ]\tTERMINAL DEVICE INITIALIZED SUCCESSFULLY!\n");
}