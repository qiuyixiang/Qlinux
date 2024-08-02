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

#ifndef __KERNEL_TYPE_H__
#define __KERNEL_TYPE_H__   1

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



