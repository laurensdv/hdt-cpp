/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_OS_TIMER_H
#define __CDS_OS_TIMER_H

#include <cds/details/defs.h>

#if CDS_OS_TYPE == CDS_OS_WIN32 || CDS_OS_TYPE == CDS_OS_WIN64 || CDS_OS_TYPE == CDS_OS_MINGW
#    include <cds/os/win/timer.h>
#elif CDS_OS_TYPE == CDS_OS_LINUX
#    include <cds/os/linux/timer.h>
#elif CDS_OS_TYPE == CDS_OS_SUN_SOLARIS
#    include <cds/os/sunos/timer.h>
#elif CDS_OS_TYPE == CDS_OS_HPUX
#    include <cds/os/hpux/timer.h>
#elif CDS_OS_TYPE == CDS_OS_AIX
#    include <cds/os/aix/timer.h>
#elif CDS_OS_TYPE == CDS_OS_FREE_BSD
#   include <cds/os/free_bsd/timer.h>
#elif CDS_OS_TYPE == CDS_OS_OSX
#   include <cds/os/osx/timer.h>
#elif CDS_OS_TYPE == CDS_OS_PTHREAD || CDS_OS_INTERFACE == CDS_OSI_UNIX
#   include <cds/os/posix/timer.h>
#else
//************************************************************************
// Other OSes
//************************************************************************
#    error Unknown operating system. Compilation aborted.
#endif

#endif    // #ifndef __CDS_OS_TIMER_H
