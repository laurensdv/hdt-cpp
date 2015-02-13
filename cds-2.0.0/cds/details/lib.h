/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_LIB_H
#define __CDS_LIB_H
//@cond

#include <cds/details/defs.h>

#ifndef CDS_BUILD_LIB

#ifdef _DEBUG
#   define  CDS_LIB_DEBUG_SUFFIX "_debug"
#else
#   define  CDS_LIB_DEBUG_SUFFIX ""
#endif

#if CDS_COMPILER == CDS_COMPILER_MSVC
#   pragma comment( lib, "libcds-" CDS_PROCESSOR__NICK "-" CDS_COMPILER__NICK CDS_LIB_DEBUG_SUFFIX )
#elif CDS_COMPILER == CDS_COMPILER_INTEL
#   pragma comment( lib, "libcds-" CDS_PROCESSOR__NICK "-" CDS_COMPILER__NICK CDS_LIB_DEBUG_SUFFIX )
#endif

#undef CDS_LIB_DEBUG_SUFFIX

#endif // #ifndef CDS_BUILD_LIB

//@endcond
#endif // #ifndef __CDS_LIB_H
