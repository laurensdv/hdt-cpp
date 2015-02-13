/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_COMPILER_CLANG_DEFS_H
#define __CDS_COMPILER_CLANG_DEFS_H

/*
    Known issues:
        Error compiling 64bit boost.atomic on clang 3.4 - 3.5, see https://svn.boost.org/trac/boost/ticket/9610
        Solution: use boost 1.56 +
*/

// Compiler version
#define CDS_COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)

// Compiler name
#define  CDS_COMPILER__NAME    ("clang " __clang_version__)
#define  CDS_COMPILER__NICK    "clang"

#if CDS_COMPILER_VERSION < 30300
#   error "Compiler version error. Clang version 3.3.0 and above is supported"
#endif

#if defined(_LIBCPP_VERSION) && !defined(CDS_USE_BOOST_ATOMIC)
    // Note: Clang libc++ atomic leads to program crash.
    // So, we use libcds atomic implementation
#   define CDS_USE_LIBCDS_ATOMIC
#endif

#include <cds/compiler/gcc/compiler_macro.h>

#define alignof __alignof__

// C++11 inline namespace
#define CDS_CXX11_INLINE_NAMESPACE_SUPPORT

#define CDS_CONSTEXPR    constexpr

#define CDS_NOEXCEPT_SUPPORT        noexcept
#define CDS_NOEXCEPT_SUPPORT_(expr) noexcept(expr)

// C++11 thread_local keyword
#define CDS_CXX11_THREAD_LOCAL_SUPPORT

// Full SFINAE support
#define CDS_CXX11_SFINAE

// *************************************************
// Alignment macro

#define CDS_TYPE_ALIGNMENT(n)   __attribute__ ((aligned (n)))
#define CDS_CLASS_ALIGNMENT(n)  __attribute__ ((aligned (n)))
#define CDS_DATA_ALIGNMENT(n)   __attribute__ ((aligned (n)))


#include <cds/compiler/gcc/compiler_barriers.h>

#endif // #ifndef __CDS_COMPILER_GCC_DEFS_H
