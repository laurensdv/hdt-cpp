/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_THREADING_DETAILS_GCC_H
#define __CDS_THREADING_DETAILS_GCC_H

#include <cds/threading/details/gcc_manager.h>

#ifndef CDS_CXX11_INLINE_NAMESPACE_SUPPORT
namespace cds { namespace threading {

    using gcc::Manager;

}} // namespace cds::threading
#endif

#endif // #ifndef __CDS_THREADING_DETAILS_GCC_H
