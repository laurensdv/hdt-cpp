/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#include <cds/os/topology.h>

#if CDS_OS_TYPE == CDS_OS_OSX

#include <sys/types.h>
#include <sys/sysctl.h>

namespace cds { namespace OS { CDS_CXX11_INLINE_NAMESPACE namespace OS_X {

    unsigned int topology::s_nProcessorCount = 0;

    void topology::init()
    {
        size_t len = sizeof( s_nProcessorCount );
        if ( sysctlbyname("hw.logicalcpu", &s_nProcessorCount, &len, nullptr, 0 ) != 0 )
            s_nProcessorCount = 1;
    }

    void topology::fini()
    {}
}}} // namespace cds::OS::Linux

#endif  // #if CDS_OS_TYPE == CDS_OS_OSX
