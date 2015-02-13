/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_STRIPED_MAP_BOOST_FLAT_MAP_ADAPTER_H
#define __CDS_CONTAINER_STRIPED_MAP_BOOST_FLAT_MAP_ADAPTER_H

#include <boost/version.hpp>
#if BOOST_VERSION < 104800
#   error "For boost::container::flat_map you must use boost 1.48 or above"
#endif

#include <cds/container/striped_set/adapter.h>
#include <boost/container/flat_map.hpp>

//#if CDS_COMPILER == CDS_COMPILER_MSVC && CDS_COMPILER_VERSION >= 1700
//#   error "boost::container::flat_map is not compatible with MS VC++ 11"
//#endif


//@cond
namespace cds { namespace container {
    namespace striped_set {

        // Copy policy for map
        template <typename Key, typename T, typename Traits, typename Alloc>
        struct copy_item_policy< boost::container::flat_map< Key, T, Traits, Alloc > >
            : public details::boost_map_copy_policies<boost::container::flat_map< Key, T, Traits, Alloc > >::copy_item_policy
        {};

        // Swap item policy
        template <typename Key, typename T, typename Traits, typename Alloc>
        struct swap_item_policy< boost::container::flat_map< Key, T, Traits, Alloc > >
            : public details::boost_map_copy_policies<boost::container::flat_map< Key, T, Traits, Alloc > >::swap_item_policy
        {};

        // Move policy for map
        template <typename Key, typename T, typename Traits, typename Alloc>
        struct move_item_policy< boost::container::flat_map< Key, T, Traits, Alloc > >
            : public details::boost_map_copy_policies<boost::container::flat_map< Key, T, Traits, Alloc > >::move_item_policy
        {};
    }   // namespace striped_set
}} // namespace cds::container

namespace cds { namespace intrusive { namespace striped_set {

    template <typename Key, typename T, class Traits, class Alloc, typename... Options>
    class adapt< boost::container::flat_map< Key, T, Traits, Alloc>, Options... >
    {
    public:
        typedef boost::container::flat_map< Key, T, Traits, Alloc>     container_type          ;   ///< underlying container type
        typedef cds::container::striped_set::details::boost_map_adapter< container_type, Options... >    type;
    };
}}} // namespace cds::intrusive::striped_set

//@endcond

#endif // #ifndef __CDS_CONTAINER_STRIPED_MAP_BOOST_FLAT_MAP_ADAPTER_H
