/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_INTRUSIVE_STRIPED_SET_BOOST_SG_SET_ADAPTER_H
#define __CDS_INTRUSIVE_STRIPED_SET_BOOST_SG_SET_ADAPTER_H

#include <boost/intrusive/sg_set.hpp>
#include <cds/intrusive/striped_set/adapter.h>

//@cond
namespace cds { namespace intrusive { namespace striped_set {

#if CDS_COMPILER == CDS_COMPILER_INTEL && CDS_COMPILER_VERSION <= 1500
    template <typename T, typename O1, typename O2, typename O3, typename O4, typename... Options>
    class adapt< boost::intrusive::sg_set< T, O1, O2, O3, O4 >, Options... >
    {
    public:
        typedef boost::intrusive::sg_set< T, O1, O2, O3, O4 >  container_type;   ///< underlying intrusive container type

    public:
        typedef details::boost_intrusive_set_adapter<container_type>   type;  ///< Result of the metafunction
    };
#else
    template <typename T, typename... BIOptons, typename... Options>
    class adapt< boost::intrusive::sg_set< T, BIOptons... >, Options... >
    {
    public:
        typedef boost::intrusive::sg_set< T, BIOptons... >  container_type  ;   ///< underlying intrusive container type

    public:
        typedef details::boost_intrusive_set_adapter<container_type>   type ;  ///< Result of the metafunction
    };
#endif
}}} // namespace cds::intrusive::striped_set
//@endcond

#endif // #ifndef __CDS_INTRUSIVE_STRIPED_SET_BOOST_SG_SET_ADAPTER_H
