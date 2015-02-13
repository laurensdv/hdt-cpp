/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_DETAILS_GUARDED_PTR_CAST_H
#define __CDS_CONTAINER_DETAILS_GUARDED_PTR_CAST_H
//@cond

#include <cds/details/defs.h>

namespace cds { namespace container { namespace details {

    template <typename Node, typename T>
    struct guarded_ptr_cast_set {
        T * operator()(Node* pNode ) const CDS_NOEXCEPT
        {
            return &(pNode->m_Value);
        }
    };

    template <typename Node, typename T>
    struct guarded_ptr_cast_map {
        T * operator()(Node* pNode ) const CDS_NOEXCEPT
        {
            return &(pNode->m_Data);
        }
    };

}}} // namespace cds::container::details

//@endcond
#endif // #ifndef __CDS_CONTAINER_DETAILS_GUARDED_PTR_CAST_H
