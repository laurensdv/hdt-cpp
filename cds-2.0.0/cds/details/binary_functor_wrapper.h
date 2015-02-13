/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_DETAILS_BINARY_FUNCTOR_WRAPPER_H
#define __CDS_DETAILS_BINARY_FUNCTOR_WRAPPER_H

#include <cds/details/defs.h>

//@cond
namespace cds { namespace details {

    template <typename ReturnType, typename Functor, typename ArgType, typename Accessor>
    struct binary_functor_wrapper {
        typedef ReturnType  return_type;
        typedef Functor     functor_type;
        typedef ArgType     argument_type;
        typedef Accessor    accessor;

        return_type operator()( argument_type const& a1, argument_type const& a2 ) const
        {
            return functor_type()( accessor()( a1 ), accessor()( a2 ));
        }

        template <typename Q>
        return_type operator()( argument_type const& a, Q const& q ) const
        {
            return functor_type()( accessor()(a), q );
        }

        template <typename Q>
        return_type operator()( Q const& q, argument_type const& a ) const
        {
            return functor_type()( q, accessor()(a));
        }

        template <typename Q1, typename Q2>
        return_type operator()( Q1 const& q1, Q2 const& q2 ) const
        {
            return functor_type()( q1, q2 );
        }
    };

    template <typename ArgType, typename Predicate, typename Accessor>
    using predicate_wrapper = binary_functor_wrapper< bool, Predicate, ArgType, Accessor>;

    template <typename ArgType, typename Compare, typename Accessor>
    using compare_wrapper = binary_functor_wrapper< int, Compare, ArgType, Accessor>;

}} // namespace cds::details

//@endcond

#endif // #ifndef __CDS_DETAILS_BINARY_FUNCTOR_WRAPPER_H
