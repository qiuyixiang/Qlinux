// Kernel Basic Types 
// This header file will include some basic types and macros for kernel use

// some utility functions and Macros are defined here for 
//  further adapt with Unix POSIX interface and data types

#ifndef __KERNEL_K_TYPES__
#define __KERNEL_K_TYPES__      1
#define __USING_UNIX_DATA_TYPE__    01l

// Type Define for Build-in C type

typedef unsigned char       _k_uint_8;
typedef unsigned short      _k_uint_16;
typedef unsigned int        _k_uint_32;
typedef unsigned long long  _k_uint_64;

typedef signed char         _k_int_8;
typedef signed short        _k_int_16;
typedef signed int          _k_int_32;
typedef signed long long    _k_int_64;

// Type for Compatible for UNIX POSIX and ANSI/ISO C Standard basic Type Define 

#if defined(__USING_UNIX_DATA_TYPE__) && (__USING_UNIX_DATA_TYPE__ == 01l)

#define uint8_t         _k_uint_8
#define uint16_t        _k_uint_16
#define uint32_t        _k_uint_32
#define uint64_t        _k_uint_64
#define int8_t          _k_int_8
#define int16_t         _k_int_16
#define int32_t         _k_int_32
#define int64_t         _k_int_64

#endif

#define __ASM__                 __asm__
#define __VOLATILE__            volatile
#define __INLINE_ASM__          __ASM__ __VOLATILE__

#endif