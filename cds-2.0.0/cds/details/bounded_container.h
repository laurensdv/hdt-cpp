/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_BOUNDED_CONTAINER_H
#define __CDS_BOUNDED_CONTAINER_H

namespace cds {
    /// Bounded container
    /**
        If a container has upper limit of item then it should be based on bounded_container class.
        Example of those containers: cyclic queue (cds::container::TsigasCycleQueue)
    */
    struct bounded_container {};
}    // namespace cds

#endif    // __CDS_BOUNDED_CONTAINER_H
