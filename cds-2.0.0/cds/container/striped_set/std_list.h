/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_CONTAINER_STRIPED_SET_STD_LIST_ADAPTER_H
#define __CDS_CONTAINER_STRIPED_SET_STD_LIST_ADAPTER_H

#include <functional>   // ref
#include <list>
#include <algorithm>    // std::lower_bound
#include <cds/container/striped_set/adapter.h>

//@cond
namespace cds { namespace container {
    namespace striped_set {

        // Copy policy for std::list
        template <typename T, typename Alloc>
        struct copy_item_policy< std::list< T, Alloc > >
        {
            typedef std::list< T, Alloc > list_type;
            typedef typename list_type::iterator iterator;

            void operator()( list_type& list, iterator itInsert, iterator itWhat )
            {
                itInsert = list.insert( itInsert, *itWhat );
            }
        };

        // Swap policy for std::list
        template <typename T, typename Alloc>
        struct swap_item_policy< std::list< T, Alloc > >
        {
            typedef std::list< T, Alloc > list_type;
            typedef typename list_type::iterator iterator;

            void operator()( list_type& list, iterator itInsert, iterator itWhat )
            {
                typename list_type::value_type newVal;
                itInsert = list.insert( itInsert, newVal );
                std::swap( *itWhat, *itInsert );
            }
        };

        // Move policy for std::list
        template <typename T, typename Alloc>
        struct move_item_policy< std::list< T, Alloc > >
        {
            typedef std::list< T, Alloc > list_type;
            typedef typename list_type::iterator iterator;

            void operator()( list_type& list, iterator itInsert, iterator itWhat )
            {
                list.insert( itInsert, std::move( *itWhat ) );
            }
        };
    }   // namespace striped_set
}} // namespace cds::container

namespace cds { namespace intrusive { namespace striped_set {

    /// std::list adapter for hash set bucket
    template <typename T, class Alloc, typename... Options>
    class adapt< std::list<T, Alloc>, Options... >
    {
    public:
        typedef std::list<T, Alloc>     container_type          ;   ///< underlying container type

    private:
        /// Adapted container type
        class adapted_container: public cds::container::striped_set::adapted_sequential_container
        {
        public:
            typedef typename container_type::value_type value_type  ;   ///< value type stored in the container
            typedef typename container_type::iterator      iterator ;   ///< container iterator
            typedef typename container_type::const_iterator const_iterator ;    ///< container const iterator

            static bool const has_find_with = true;
            static bool const has_erase_with = true;

        private:
            //@cond
            typedef typename cds::opt::details::make_comparator_from_option_list< value_type, Options... >::type key_comparator;


            typedef typename cds::opt::select<
                typename cds::opt::value<
                    typename cds::opt::find_option<
                        cds::opt::copy_policy< cds::container::striped_set::move_item >
                        , Options...
                    >::type
                >::copy_policy
                , cds::container::striped_set::copy_item, cds::container::striped_set::copy_item_policy<container_type>
                , cds::container::striped_set::swap_item, cds::container::striped_set::swap_item_policy<container_type>
                , cds::container::striped_set::move_item, cds::container::striped_set::move_item_policy<container_type>
            >::type copy_item;

            struct find_predicate
            {
                bool operator()( value_type const& i1, value_type const& i2) const
                {
                    return key_comparator()( i1, i2 ) < 0;
                }

                template <typename Q>
                bool operator()( Q const& i1, value_type const& i2) const
                {
                    return key_comparator()( i1, i2 ) < 0;
                }

                template <typename Q>
                bool operator()( value_type const& i1, Q const& i2) const
                {
                    return key_comparator()( i1, i2 ) < 0;
                }
            };
            //@endcond

        private:
            //@cond
            container_type  m_List;
#       if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
            // GCC C++ lib bug:
            // In GCC, the complexity of std::list::size() is O(N)
            // (see http://gcc.gnu.org/bugzilla/show_bug.cgi?id=49561)
            // Fixed in GCC 5
            size_t          m_nSize ;   // list size
#       endif
            //@endcond

        public:
            adapted_container()
#       if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                : m_nSize(0)
#       endif
            {}

            template <typename Q, typename Func>
            bool insert( const Q& val, Func f )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), val, find_predicate() );
                if ( it == m_List.end() || key_comparator()( val, *it ) != 0 ) {
                    value_type newItem( val );
                    it = m_List.insert( it, newItem );
                    f( *it );

#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                    ++m_nSize;
#           endif
                    return true;
                }

                // key already exists
                return false;
            }

            template <typename... Args>
            bool emplace( Args&&... args )
            {
                value_type val(std::forward<Args>(args)...);
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), val, find_predicate() );
                if ( it == m_List.end() || key_comparator()( val, *it ) != 0 ) {
                    it = m_List.emplace( it, std::move( val ) );
#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                    ++m_nSize;
#           endif
                    return true;
                }
                return false;
            }

            template <typename Q, typename Func>
            std::pair<bool, bool> ensure( const Q& val, Func func )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), val, find_predicate() );
                if ( it == m_List.end() || key_comparator()( val, *it ) != 0 ) {
                    // insert new
                    value_type newItem( val );
                    it = m_List.insert( it, newItem );
                    func( true, *it, val );
#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                    ++m_nSize;
#           endif
                    return std::make_pair( true, true );
                }
                else {
                    // already exists
                    func( false, *it, val );
                    return std::make_pair( true, false );
                }
            }

            template <typename Q, typename Func>
            bool erase( const Q& key, Func f )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), key, find_predicate() );
                if ( it == m_List.end() || key_comparator()( key, *it ) != 0 )
                    return false;

                // key exists
                f( *it );
                m_List.erase( it );
#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                --m_nSize;
#           endif

                return true;
            }

            template <typename Q, typename Less, typename Func>
            bool erase( Q const& key, Less pred, Func f )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), key, pred );
                if ( it == m_List.end() || pred( key, *it ) || pred( *it, key ) )
                    return false;

                // key exists
                f( *it );
                m_List.erase( it );
#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                --m_nSize;
#           endif

                return true;
            }

            template <typename Q, typename Func>
            bool find( Q& val, Func f )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), val, find_predicate() );
                if ( it == m_List.end() || key_comparator()( val, *it ) != 0 )
                    return false;

                // key exists
                f( *it, val );
                return true;
            }

            template <typename Q, typename Less, typename Func>
            bool find( Q& val, Less pred, Func f )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), val, pred );
                if ( it == m_List.end() || pred( val, *it ) || pred( *it, val ) )
                    return false;

                // key exists
                f( *it, val );
                return true;
            }

            /// Clears the container
            void clear()
            {
                m_List.clear();
            }

            iterator begin()                { return m_List.begin(); }
            const_iterator begin() const    { return m_List.begin(); }
            iterator end()                  { return m_List.end(); }
            const_iterator end() const      { return m_List.end(); }

            void move_item( adapted_container& /*from*/, iterator itWhat )
            {
                iterator it = std::lower_bound( m_List.begin(), m_List.end(), *itWhat, find_predicate() );
                assert( it == m_List.end() || key_comparator()( *itWhat, *it ) != 0 );

                copy_item()( m_List, it, itWhat );
#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                ++m_nSize;
#           endif
            }

            size_t size() const
            {
#           if defined(__GLIBCXX__ ) && !( CDS_COMPILER == CDS_COMPILER_GCC && CDS_COMPILER_VERSION >= 50000 )
                return m_nSize;
#           else
                return m_List.size();
#           endif

            }
        };

    public:
        typedef adapted_container type ; ///< Result of \p adapt metafunction

    };
}}}


//@endcond

#endif // #ifndef __CDS_CONTAINER_STRIPED_SET_STD_LIST_ADAPTER_H
