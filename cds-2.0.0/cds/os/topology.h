/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_OS_TOPOLOGY_H
#define __CDS_OS_TOPOLOGY_H

#include <cds/details/defs.h>

#if CDS_OS_TYPE == CDS_OS_WIN32 || CDS_OS_TYPE == CDS_OS_WIN64 || CDS_OS_TYPE == CDS_OS_MINGW
#   include <cds/os/win/topology.h>
#elif CDS_OS_TYPE == CDS_OS_LINUX
#   include <cds/os/linux/topology.h>
#elif CDS_OS_TYPE == CDS_OS_SUN_SOLARIS
#   include <cds/os/sunos/topology.h>
#elif CDS_OS_TYPE == CDS_OS_HPUX
#   include <cds/os/hpux/topology.h>
#elif CDS_OS_TYPE == CDS_OS_AIX
#   include <cds/os/aix/topology.h>
#elif CDS_OS_TYPE == CDS_OS_FREE_BSD || CDS_OS_TYPE == CDS_OS_OPEN_BSD || CDS_OS_TYPE == CDS_OS_NET_BSD
#   include <cds/os/free_bsd/topology.h>
#elif CDS_OS_TYPE == CDS_OS_OSX
#   include <cds/os/osx/topology.h>
#elif CDS_OS_TYPE == CDS_OS_PTHREAD || CDS_OS_INTERFACE == CDS_OSI_UNIX
#   include <cds/os/posix/fake_topology.h>
#else
#   error Unknown OS. Compilation aborted
#endif

#endif  // #ifndef __CDS_OS_TOPOLOGY_H
