// This File Define Some General Types About Kernel Data Structure
// This Header File may be used for compatibility for C and UNIX Standard Data Type
// @Copyright Copyright (C) QIUYIXIANG
// date: 07-28-2024

#ifndef __KERNEL_TYPES__
#define __KERNEL_TYPES__    1

// Type Define For Basic Types for Kernel
typedef unsigned char           _k_uint_8;
typedef unsigned short          _k_uint_16;
typedef unsigned int            _k_uint_32;
typedef unsigned long long      _k_uint_64;
typedef signed char             _k_int_8;
typedef signed short            _k_int_16;
typedef signed int              _k_int_32;
typedef signed long long        _k_int_64;

// Define Types For Compatibility For ANSI/ISO C and UNIX POSIX
typedef _k_uint_8               uint8_t;
typedef _k_uint_16              uint16_t;
typedef _k_uint_32              uint32_t;
typedef _k_uint_64              uint64_t;
typedef _k_int_8                int8_t;
typedef _k_int_16               int16_t;
typedef _k_int_32               int32_t;
typedef _k_int_64               int64_t;
typedef uint32_t                size_t;

#endif


