/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_DETAILS_IS_ALIGNED_H
#define __CDS_DETAILS_IS_ALIGNED_H

#include <cds/details/defs.h>

namespace cds { namespace details {

    /// Checks if the pointer \p p has \p ALIGN byte alignment
    /**
        \p ALIGN must be power of 2.

        The function is mostly intended for run-time assertion
    */
    template <int ALIGN, typename T>
    static inline bool is_aligned(T const * p)
    {
        return (((uintptr_t)p) & uintptr_t(ALIGN - 1)) == 0;
    }

    /// Checks if the pointer \p p has \p nAlign byte alignment
    /**
        \p nAlign must be power of 2.

        The function is mostly intended for run-time assertion
    */
    template <typename T>
    static inline bool is_aligned(T const * p, size_t nAlign)
    {
        return (((uintptr_t)p) & uintptr_t(nAlign - 1)) == 0;
    }

}} // namespace cds::details

#endif // #ifndef __CDS_DETAILS_IS_ALIGNED_H
