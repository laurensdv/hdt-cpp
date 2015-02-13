/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_DETAILS_MICHAEL_MAP_BASE_H
#define __CDS_CONTAINER_DETAILS_MICHAEL_MAP_BASE_H

#include <cds/container/details/michael_set_base.h>

namespace cds { namespace container {

    /// MichaelHashMap related definitions
    /** @ingroup cds_nonintrusive_helper
    */
    namespace michael_map {
        /// \p MichaelHashMap traits
        typedef container::michael_set::traits  traits;

        /// Metafunction converting option list to \p michael_map::traits
        template <typename... Options>
        using make_traits = cds::intrusive::michael_set::make_traits< Options... >;

        //@cond
        namespace details {
            using michael_set::details::init_hash_bitmask;
        }
        //@endcond

    }   // namespace michael_map

    //@cond
    // Forward declarations
    template <class GC, class OrderedList, class Traits = michael_map::traits>
    class MichaelHashMap;
    //@endcond

}}  // namespace cds::container


#endif  // ifndef __CDS_CONTAINER_DETAILS_MICHAEL_MAP_BASE_H
