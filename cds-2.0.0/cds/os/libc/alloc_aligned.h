/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_OS_LIBC_ALLOC_ALIGNED_H
#define __CDS_OS_LIBC_ALLOC_ALIGNED_H

#include <stdlib.h>

//@cond none
namespace cds { namespace OS {
    CDS_CXX11_INLINE_NAMESPACE namespace libc {
        /// Allocates memory on a specified alignment boundary
        static inline void * aligned_malloc(
            size_t nSize,       ///< Size of the requested memory allocation
            size_t nAlignment   ///< The alignment value, which must be an integer power of 2
            )
        {
            return ::memalign( nAlignment, nSize );
        }

        /// Frees a block of memory that was allocated with aligned_malloc.
        static inline void aligned_free(
            void * pBlock   ///< A pointer to the memory block that was returned to the aligned_malloc function
            )
        {
            ::free( pBlock );
        }
    }   // namespace libc

#ifndef CDS_CXX11_INLINE_NAMESPACE_SUPPORT
    using libc::aligned_malloc;
    using libc::aligned_free;
#endif

}} // namespace cds::OS
//@endcond

#endif // #ifndef __CDS_OS_LIBC_ALLOC_ALIGNED_H

