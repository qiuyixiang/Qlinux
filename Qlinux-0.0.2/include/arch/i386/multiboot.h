// This File Define Some Information About GNU MultiBoot 0.96 Specification
// Current File Using GNU GRUB Legacy
// these macros may be used by the kernel and the boot header
// @date 07-28-2024
// @copyright (C) QIUYIXIANG

#ifndef __ARCH_I386_MULTIBOOT_H__
#define __ARCH_I386_MULTIBOOT_H__  1

// Macro for not generating Coding for asm 
#if !defined(__USING_ASM__) && (__USING_ASM__ != 1)

// Define For MultiBoot Compatible Type
typedef unsigned char           mb_u8;
typedef unsigned short          mb_u16;
typedef unsigned int            mb_u32;
typedef unsigned long long      mb_u64;

#endif

// Macros For MultiBoot Header
#define MB_HD_MAGIC_HEADER                  0x1BADB002u
#define MB_HD_4K_BOUNDARY                   0b0001u
#define MB_HD_NON_4K_BOUNDARY               0b0000u
#define MB_HD_NON_DETECT_MEMORY             0b0000u
#define MB_HD_DETECT_MEMORY                 0b0010u
#define MB_HD_DISPLAY_NO_PREFERENCE         0b0000u
#define MB_HD_DISPLAY_PREFERENCE            0b0100u
#define MB_HD_FLAGS                         (MB_HD_4K_BOUNDARY | MB_HD_DETECT_MEMORY | MB_HD_DISPLAY_NO_PREFERENCE)
#define MB_HD_CHECKSUM                      -(MB_HD_MAGIC_HEADER + MB_HD_FLAGS)

// Macros For MultiBoot Verification
#define MB_CHECK_SUCCESS                    0x2BADB002

#endif