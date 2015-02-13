/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_GC_DETAILS_HP_TYPE_H
#define __CDS_GC_DETAILS_HP_TYPE_H

#include <cds/gc/details/retired_ptr.h> // free_retired_ptr_func

//@cond
namespace cds {
    namespace gc {
        namespace hp {

            /// Hazard pointer
            typedef void *    hazard_pointer;

            /// Pointer to function to free (destruct and deallocate) retired pointer of specific type
            typedef cds::gc::details::free_retired_ptr_func free_retired_ptr_func;
        }
    }
}
//@endcond

#endif // #ifndef __CDS_GC_DETAILS_HP_TYPE_H


