// This File Define Some Macros for VAG Text Mode 
// And Support different Low-Level Features about VGA Text Operation
// @Copyright Copyright (C) QIUYIXIANG
// date: 07-28-2024


#ifndef __ARCH_MONITOR_VGA_H__
#define __ARCH_MONITOR_VGA_H__ 1

#include <kernel/types.h>

// Type Define For VGA Color Type
typedef enum __vga_color_attr_{
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
}_vga_color;

// Define For VGA Text Mode Theme
#define VGA_THEME_LIGHT     0
#define VGA_THEME_DARK      1


// Define VGA Function Interfaces
extern void vga_init(uint8_t _default_theme);
extern void vga_set_color(_vga_color _font_color,  _vga_color _back_ground_color);
extern void vga_clean_screen(void);
extern void vga_putchar(unsigned char _character);
extern uint8_t vga_get_color(void);
extern void vga_put_string(const char * _ptr);

#endif