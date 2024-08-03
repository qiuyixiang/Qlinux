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

#include <driver/vga/vga.h>
#include <kernel/macro.h>

#define VGA_MAXI_COLUMN             80
#define VGA_MAXI_ROW                25
#define VGA_BUFFER_START_ADDR       0xb8000

#define VGA_DEFAULT_FONT_COLOR      VGA_COLOR_LIGHT_WHITE
#define VGA_DEFAULT_BACK_COLOR      VGA_COLOR_BLACK
#define VGA_DEFAULT_COLUMN          0
#define VGA_DEFAULT_ROW             0
#define VGA_DEFAULT_TAB_SIZE        4


uint16_t* __vga_buffer_start;
uint8_t __vga_color_attribute;
// Current Cursor Position
uint32_t __vga_cursor_column;
uint32_t __vga_cursor_row; 

// These Scroll Function Only Deal With Data Transfer 
// Don't Care About Cursor Position
// The User of These function must make sure that the cursor position
// update properly
static void __vga_scroll_up(uint16_t __row){
    (void)__row;
}


// Public Interface Functions
void vga_put_char(char __character){
    /// Deal With Different Character
    if (__character == '\n'){
        if (__vga_cursor_row + 1 < VGA_MAXI_ROW){
            __vga_cursor_row++;
            __vga_cursor_column = VGA_DEFAULT_COLUMN;
        }else{
            __vga_scroll_up(1);
            __vga_cursor_column = VGA_DEFAULT_COLUMN;
        }
    }else if (__character == '\t'){
        if (__vga_cursor_column + VGA_DEFAULT_TAB_SIZE < VGA_MAXI_COLUMN)
            __vga_cursor_column += VGA_DEFAULT_TAB_SIZE;
        else{
            __vga_cursor_column = (__vga_cursor_column + VGA_DEFAULT_TAB_SIZE) - VGA_MAXI_COLUMN;
            if (__vga_cursor_row + 1 < VGA_MAXI_ROW)
                __vga_cursor_row++;
            else
                __vga_scroll_up(1);
        }
    }else{
        if (__vga_cursor_column + 1 >= VGA_MAXI_COLUMN){
            if (__vga_cursor_row + 1 < VGA_MAXI_ROW)
                __vga_cursor_row++;
            else
                __vga_scroll_up(1);
            __vga_cursor_column = VGA_DEFAULT_COLUMN;
        }
        *(__vga_buffer_start + __vga_cursor_row * VGA_MAXI_COLUMN + __vga_cursor_column) 
            = __character | ((uint16_t)__vga_color_attribute << 8);
        ++__vga_cursor_column;
    }
}
ALWAYS_INLINE void vga_put_string(const char *__ptr){
    for (const char * __char_buffer = __ptr; *__char_buffer != '\0'; ++__char_buffer)
        vga_put_char(*__char_buffer);
}
ALWAYS_INLINE void vga_write(const char *__ptr, uint32_t __count){
    for (; __count; --__count, ++__ptr)
        vga_put_char(*__ptr);
}

ALWAYS_INLINE void vga_set_font_color(vga_color_attr __color){
    __vga_color_attribute |= __color;
}
ALWAYS_INLINE void vga_set_bk_color(vga_color_attr __color){
    __vga_color_attribute |= (__color << 4);
}
ALWAYS_INLINE void vga_set_theme(vga_color_attr __font, vga_color_attr __back_ground){
    vga_set_font_color(__font);
    vga_set_bk_color(__back_ground);
}
void vga_clear_screen(){
    for (uint32_t __row = 0; __row != VGA_MAXI_ROW; ++__row){
        for (uint32_t __column = 0; __column != VGA_MAXI_COLUMN; ++__column)
            *(__vga_buffer_start + __row * VGA_MAXI_COLUMN + __column) = 
                ((uint16_t)__vga_color_attribute << 8) | (uint16_t)'\0';
    }
}

void vga_init(void){
    __vga_buffer_start = (uint16_t*)VGA_BUFFER_START_ADDR;
    __vga_cursor_column = VGA_DEFAULT_COLUMN;
    __vga_cursor_row = VGA_DEFAULT_ROW;
    __vga_color_attribute = (VGA_DEFAULT_BACK_COLOR << 4) | VGA_DEFAULT_FONT_COLOR;

    vga_clear_screen();
    vga_put_string("[INIT ]\tDISPLAY MODE VGA INITIALIZED SUCCESSFULLY!\n");
}