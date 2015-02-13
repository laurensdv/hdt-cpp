/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_OS_POSIX_FAKE_TOPOLOGY_H
#define __CDS_OS_POSIX_FAKE_TOPOLOGY_H

#ifndef __CDS_OS_TOPOLOGY_H
#   error "<cds/os/topology.h> must be included instead"
#endif

#include <cds/os/details/fake_topology.h>
#include <unistd.h>

namespace cds { namespace OS {
    CDS_CXX11_INLINE_NAMESPACE namespace posix {
        /// Fake system topology
        struct topology {
            /// Logical processor count for the system. Always returns 1
            static unsigned int processor_count()
            {
                return 1;
            }

            /// Get current processor number
            /**
                Always returns 0
            */
            static unsigned int current_processor()
            {
                return 0;
            }

            /// Synonym for \ref current_processor
            static unsigned int native_current_processor()
            {
                return current_processor();
            }

            //@cond
            static void init()
            {}
            static void fini()
            {}
            //@endcond
        };
    }   // namespace posix

#ifndef CDS_CXX11_INLINE_NAMESPACE_SUPPORT
    using posix::topology;
#endif

}}  // namespace cds::OS

#endif  // #ifndef __CDS_OS_POSIX_FAKE_TOPOLOGY_H
