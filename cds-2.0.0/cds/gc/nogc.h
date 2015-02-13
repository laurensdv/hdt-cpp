/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_GC_NOGC_H
#define __CDS_GC_NOGC_H

namespace cds { namespace gc {

    /// No garbage collecting
    /**  @ingroup cds_garbage_collector
        This empty class is used in \p libcds to mark that a template specialization implements
        the container without any garbage collector schema.

        Usually, the container with this "GC" does not support the item removal.
    */
    class nogc
    {
    public:
        //@cond
        /// Faked scan
        static void scan()
        {}
        static void force_dispose()
        {}
        //@endcond
    };

}}  // namespace cds::gc

#endif // #define __CDS_GC_NOGC_H
