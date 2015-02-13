/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_STRIPED_MAP_STD_HASH_MAP_ADAPTER_H
#define __CDS_CONTAINER_STRIPED_MAP_STD_HASH_MAP_ADAPTER_H

#include <cds/container/striped_set/adapter.h>
#if (CDS_COMPILER == CDS_COMPILER_MSVC || (CDS_COMPILER == CDS_COMPILER_INTEL && CDS_OS_INTERFACE == CDS_OSI_WINDOWS)) && _MSC_VER < 1600    // MS VC 2008
#   include <cds/container/striped_map/std_hash_map_vc.h>
#else
#   include <cds/container/striped_map/std_hash_map_std.h>
#endif

#endif // #ifndef __CDS_CONTAINER_STRIPED_MAP_STD_HASH_MAP_ADAPTER_H
