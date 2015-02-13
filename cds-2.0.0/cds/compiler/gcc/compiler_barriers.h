/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_COMPILER_GCC_COMPILER_BARRIERS_H
#define __CDS_COMPILER_GCC_COMPILER_BARRIERS_H

#define CDS_COMPILER_RW_BARRIER  __asm__ __volatile__ ( "" ::: "memory" )
#define CDS_COMPILER_R_BARRIER   CDS_COMPILER_RW_BARRIER
#define CDS_COMPILER_W_BARRIER   CDS_COMPILER_RW_BARRIER

#endif  // #ifndef __CDS_COMPILER_GCC_COMPILER_BARRIERS_H
