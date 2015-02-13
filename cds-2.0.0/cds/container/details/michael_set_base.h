/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_DETAILS_MICHAEL_SET_BASE_H
#define __CDS_CONTAINER_DETAILS_MICHAEL_SET_BASE_H

#include <cds/intrusive/details/michael_set_base.h>

namespace cds { namespace container {

    /// MichaelHashSet related definitions
    /** @ingroup cds_nonintrusive_helper
    */
    namespace michael_set {

        /// MichaelHashSet traits
        typedef cds::intrusive::michael_set::traits  traits;

        /// Metafunction converting option list to \p michael_set::traits
        template <typename... Options>
        using make_traits = cds::intrusive::michael_set::make_traits< Options... >;

        //@cond
        namespace details {
            using cds::intrusive::michael_set::details::init_hash_bitmask;
            using cds::intrusive::michael_set::details::list_iterator_selector;
            using cds::intrusive::michael_set::details::iterator;
        }
        //@endcond
    }

    //@cond
    // Forward declarations
    template <class GC, class OrderedList, class Traits = michael_set::traits>
    class MichaelHashSet;
    //@endcond

}} // namespace cds::container

#endif // #ifndef __CDS_CONTAINER_DETAILS_MICHAEL_SET_BASE_H
