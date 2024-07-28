/*
* Copyright (C) QIUYIXIANG
* 
* This File is the source file of VGA Text Mode 
* And Support different Low-Level Features about VGA Text Operation
* @Date 07-28-2024
*/
#include <arch/monitor/vga.h>

// These Macros Doesn't Need to export to outer interfaces
#define VGA_MAXI_WIDTH      80
#define VGA_MAXI_HEIGHT     25

// Define Default Dark Theme
#define THEME_DARK_DEFAULT_FT       VGA_COLOR_LIGHT_WHITE
#define THEME_DARK_DEFAULT_BK       VGA_COLOR_BLACK
#define THEME_DARK_COLOR            (THEME_DARK_DEFAULT_FT | (THEME_DARK_DEFAULT_BK << 4))

// Define Default Light Theme
#define THEME_LIGHT_DEFAULT_FT      VGA_COLOR_BLACK
#define THEME_LIGHT_DEFAULT_BK      VGA_COLOR_WHITE
#define THEME_LIGHT_COLOR           (THEME_LIGHT_DEFAULT_FT | (THEME_LIGHT_DEFAULT_BK << 4))

#define VGA_BUFFER_START_ADDR       0x000b8000

// Global Variables For VGA

// Current Color
static uint8_t  current_vga_color;
// Current Position (X, Y)
static uint32_t current_row;
static uint32_t current_column;
static uint16_t* vga_buffer_start;

/// Private Helper Function
static inline void __vga_set_color(uint8_t __color){
    current_vga_color = __color;
}
static inline void scroll_up(uint32_t __num){
    /// TODO
}
static inline void scroll_down(uint32_t __num){
    /// TODO
}

/// Public Interfaces Implementation
inline void vga_set_color(_vga_color _font_color,  _vga_color _back_ground_color){
    current_vga_color = (_back_ground_color << 4) | _font_color;
}

inline void vga_clean_screen(void){
    for (uint32_t __row = 0; __row != VGA_MAXI_HEIGHT; ++__row){
        for (uint32_t __column = 0; __column != VGA_MAXI_WIDTH; ++__column){
            *(vga_buffer_start + VGA_MAXI_WIDTH * __row + __column) = (uint16_t)current_vga_color << 8;
        }
    }
}
void vga_putchar(unsigned char _character){
    if (_character == '\n'){
        // Check Whether the Position Near the Boundary
        if (current_row < VGA_MAXI_HEIGHT)
            ++current_row;
        else{
            scroll_up(1);
            --current_row;
        }
        current_column = 0;
    }else if (_character == '\t'){
        // Check Whether the Position Near the Boundary
        if (current_column + 4 < VGA_MAXI_WIDTH)
            current_column += 4;
        else{
            current_column = current_column + 4 - VGA_MAXI_WIDTH;
            ++current_row;
            if (current_row >= VGA_MAXI_HEIGHT){
                scroll_up(1);
                --current_row;
            }
        }
    }else{
        if (current_column >= VGA_MAXI_WIDTH){
            current_column = 0;
            ++current_row;
            if (current_row >= VGA_MAXI_HEIGHT){
                scroll_up(1);
                --current_row;
            }
        }
        *(vga_buffer_start + VGA_MAXI_WIDTH * current_row + current_column) = 
        (uint16_t)current_vga_color << 8 | _character;
        ++current_column;
    }
}

void vga_put_string(const char * _ptr){
    for ( ; *_ptr != '\0'; ++_ptr)
        vga_putchar(*_ptr);
}

inline uint8_t vga_get_color(void){
    return current_vga_color;
}
void vga_init(uint8_t _default_theme){
    vga_buffer_start = (uint16_t*)VGA_BUFFER_START_ADDR;
    current_row = 0;
    current_column = 0;
    if (_default_theme == VGA_THEME_DARK)
        __vga_set_color(THEME_DARK_COLOR);
    else{
        // First Update Current Color Attribute
        __vga_set_color(THEME_LIGHT_COLOR);
        // Using this Color Attribute To Update All Screen
        vga_clean_screen();
    }

}    