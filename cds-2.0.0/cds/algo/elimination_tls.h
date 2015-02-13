/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_ALGO_ELIMINATION_TLS_H
#define __CDS_ALGO_ELIMINATION_TLS_H

#include <cds/algo/base.h>

namespace cds { namespace algo { namespace elimination {

    // Forwards
    struct operation_desc;

    /// Per-thread elimination record
    /** @headerfile cds/algo/elimination.h
    */
    struct record
    {
        operation_desc *    pOp ;   ///< Operation descriptor

        /// Initialization
        record()
            : pOp( nullptr )
        {}

        /// Checks if the record is free
        bool is_free() const
        {
            return pOp == nullptr;
        }
    };

}}} // cds::algo::elimination

#endif // #ifndef __CDS_ALGO_ELIMINATION_TLS_H
