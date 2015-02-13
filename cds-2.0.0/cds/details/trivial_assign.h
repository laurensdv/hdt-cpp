/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_DETAILS_TRIVIAL_ASSIGN_H
#define __CDS_DETAILS_TRIVIAL_ASSIGN_H

#include <cds/details/defs.h>

//@cond
namespace cds { namespace details {

    template <typename Dest, typename Source>
    struct trivial_assign
    {
        Dest& operator()( Dest& dest, const Source& src )
        {
            return dest = src;
        }
    };
}}  // namespace cds::details
//@endcond

#endif // #ifndef __CDS_DETAILS_TRIVIAL_ASSIGN_H
