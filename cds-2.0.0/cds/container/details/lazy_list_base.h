/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_DETAILS_LAZY_LIST_BASE_H
#define __CDS_CONTAINER_DETAILS_LAZY_LIST_BASE_H

#include <cds/container/details/base.h>
#include <cds/intrusive/details/lazy_list_base.h>
#include <cds/urcu/options.h>

namespace cds { namespace container {

    /// LazyList ordered list related definitions
    /** @ingroup cds_nonintrusive_helper
    */
    namespace lazy_list {
        /// LazyList traits
        /**
            Either \p compare or \p less or both must be specified.
        */
        struct traits
        {
            /// allocator used to allocate new node
            typedef CDS_DEFAULT_ALLOCATOR   allocator;

            /// Key comparing functor
            /**
                No default functor is provided. If the option is not specified, the \p less is used.
            */
            typedef opt::none                       compare;

            /// Specifies binary predicate used for key comparing
            /**
                Default is \p std::less<T>.
            */
            typedef opt::none                       less;

            /// Lock type used to lock modifying items
            /**
                Default is cds::lock::Spin
            */
            typedef cds::lock::Spin                 lock_type;

            /// back-off strategy used
            typedef cds::backoff::Default           back_off;

            /// Item counting feature; by default, disabled. Use \p cds::atomicity::item_counter to enable item counting
            typedef atomicity::empty_item_counter     item_counter;

            /// C++ memory ordering model
            /**
                Can be \p opt::v::relaxed_ordering (relaxed memory model, the default)
                or \p opt::v::sequential_consistent (sequentially consisnent memory model).
            */
            typedef opt::v::relaxed_ordering        memory_model;

            /// RCU deadlock checking policy (only for \ref cds_intrusive_LazyList_rcu "RCU-based LazyList")
            /**
                List of available options see \p opt::rcu_check_deadlock
            */
            typedef opt::v::rcu_throw_deadlock      rcu_check_deadlock;

            //@cond
            // LazyKVList: supporting for split-ordered list
            // key accessor (opt::none = internal key type is equal to user key type)
            typedef opt::none                       key_accessor;

            //@endcond
        };

        /// Metafunction converting option list to \p lazy_list::traits
        /**
            \p Options are:
            - \p opt::lock_type - lock type for node-level locking. Default \p is cds::lock::Spin. Note that <b>each</b> node
                of the list has member of type \p lock_type, therefore, heavy-weighted locking primitive is not
                acceptable as candidate for \p lock_type.
            - \p opt::compare - key compare functor. No default functor is provided.
                If the option is not specified, the \p opt::less is used.
            - \p opt::less - specifies binary predicate used for key compare. Default is \p std::less<T>.
            - \p opt::back_off - back-off strategy used. If the option is not specified, \p cds::backoff::Default is used.
            - \p opt::item_counter - the type of item counting feature. Default is disabled (\p atomicity::empty_item_counter).
                To enable item counting use \p atomicity::item_counter.
            - \p opt::allocator - the allocator used for creating and freeing list's item. Default is \ref CDS_DEFAULT_ALLOCATOR macro.
            - \p opt::memory_model - C++ memory ordering model. Can be \p opt::v::relaxed_ordering (relaxed memory model, the default)
                or \p opt::v::sequential_consistent (sequentially consisnent memory model).
        */
        template <typename... Options>
        struct make_traits {
#   ifdef CDS_DOXYGEN_INVOKED
            typedef implementation_defined type ;   ///< Metafunction result
#   else
            typedef typename cds::opt::make_options<
                typename cds::opt::find_type_traits< traits, Options... >::type
                ,Options...
            >::type   type;
#endif
        };


    } // namespace lazy_list

    // Forward declarations
    template <typename GC, typename T, typename Traits=lazy_list::traits>
    class LazyList;

    template <typename GC, typename Key, typename Value, typename Traits=lazy_list::traits>
    class LazyKVList;

    // Tag for selecting lazy list implementation
    /**
        This struct is empty and it is used only as a tag for selecting LazyList
        as ordered list implementation in declaration of some classes.

        See \p split_list::traits::ordered_list as an example.
    */
    struct lazy_list_tag
    {};

}}  // namespace cds::container


#endif  // #ifndef __CDS_CONTAINER_DETAILS_LAZY_LIST_BASE_H
