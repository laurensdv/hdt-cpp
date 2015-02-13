/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_INTRUSIVE_LAZY_LIST_NOGC_H
#define __CDS_INTRUSIVE_LAZY_LIST_NOGC_H

#include <mutex>        // unique_lock
#include <cds/intrusive/details/lazy_list_base.h>
#include <cds/gc/nogc.h>

namespace cds { namespace intrusive {
    namespace lazy_list {
        /// Lazy list node for \p gc::nogc
        /**
            Template parameters:
             - Lock - lock type. Default is \p cds::lock::Spin
             - Tag - a \ref cds_intrusive_hook_tag "tag"
        */
        template <
#ifdef CDS_DOXYGEN_INVOKED
            typename Lock = cds::lock::Spin,
            typename Tag = opt::none
#else
            typename Lock,
            typename Tag
#endif
        >
        struct node<gc::nogc, Lock, Tag>
        {
            typedef gc::nogc    gc;   ///< Garbage collector
            typedef Lock        lock_type;  ///< Lock type
            typedef Tag         tag;  ///< tag

            atomics::atomic<node *> m_pNext; ///< pointer to the next node in the list
            mutable lock_type   m_Lock;      ///< Node lock

            node()
                : m_pNext( nullptr )
            {}
        };
    }   // namespace lazy_list


    /// Lazy ordered single-linked list (template specialization for \p gc::nogc)
    /** @ingroup cds_intrusive_list
        \anchor cds_intrusive_LazyList_nogc

        This specialization is append-only list when no item
        reclamation may be performed. The class does not support deleting of list item.

        See \ref cds_intrusive_LazyList_hp "LazyList" for description of template parameters.
    */
    template <
        typename T
#ifdef CDS_DOXYGEN_INVOKED
        ,class Traits = lazy_list::traits
#else
        ,class Traits
#endif
    >
    class LazyList<gc::nogc, T, Traits>
    {
    public:
        typedef gc::nogc gc;         ///< Garbage collector
        typedef T        value_type; ///< type of value stored in the list
        typedef Traits   traits;    ///< Traits template parameter

        typedef typename traits::hook    hook;      ///< hook type
        typedef typename hook::node_type node_type; ///< node type

#   ifdef CDS_DOXYGEN_INVOKED
        typedef implementation_defined key_comparator  ;    ///< key comparison functor based on opt::compare and opt::less option setter.
#   else
        typedef typename opt::details::make_comparator< value_type, traits >::type key_comparator;
#   endif
        typedef typename traits::back_off  back_off;   ///< Back-off strategy
        typedef typename traits::disposer  disposer;   ///< disposer
        typedef typename get_node_traits< value_type, node_type, hook>::type node_traits;    ///< node traits
        typedef typename lazy_list::get_link_checker< node_type, traits::link_checker >::type link_checker;   ///< link checker

        typedef typename traits::item_counter item_counter;  ///< Item counting policy used
        typedef typename traits::memory_model  memory_model; ///< C++ memory ordering (see lazy_list::traits::memory_model)

        //@cond
        // Rebind traits (split-list support)
        template <typename... Options>
        struct rebind_traits {
            typedef LazyList<
                gc
                , value_type
                , typename cds::opt::make_options< traits, Options...>::type
            >   type;
        };
        //@endcond

    protected:
        typedef node_type *     auxiliary_head   ;   ///< Auxiliary head type (for split-list support)

    protected:
        node_type       m_Head;        ///< List head (dummy node)
        node_type       m_Tail;        ///< List tail (dummy node)
        item_counter    m_ItemCounter; ///< Item counter

        //@cond

        /// Position pointer for item search
        struct position {
            node_type *     pPred   ;    ///< Previous node
            node_type *     pCur    ;    ///< Current node

            /// Locks nodes \p pPred and \p pCur
            void lock()
            {
                pPred->m_Lock.lock();
                pCur->m_Lock.lock();
            }

            /// Unlocks nodes \p pPred and \p pCur
            void unlock()
            {
                pCur->m_Lock.unlock();
                pPred->m_Lock.unlock();
            }
        };

        class auto_lock_position {
            position&   m_pos;
        public:
            auto_lock_position( position& pos )
                : m_pos(pos)
            {
                pos.lock();
            }
            ~auto_lock_position()
            {
                m_pos.unlock();
            }
        };
        //@endcond

    protected:
        //@cond
        void clear_links( node_type * pNode )
        {
            pNode->m_pNext.store( nullptr, memory_model::memory_order_relaxed );
        }

        template <class Disposer>
        void dispose_node( node_type * pNode, Disposer disp )
        {
            clear_links( pNode );
            disp( node_traits::to_value_ptr( *pNode ));
        }

        template <class Disposer>
        void dispose_value( value_type& val, Disposer disp )
        {
            dispose_node( node_traits::to_node_ptr( val ), disp );
        }

        void link_node( node_type * pNode, node_type * pPred, node_type * pCur )
        {
            assert( pPred->m_pNext.load(memory_model::memory_order_relaxed) == pCur );

            pNode->m_pNext.store( pCur, memory_model::memory_order_release );
            pPred->m_pNext.store( pNode, memory_model::memory_order_release );
        }
        //@endcond

    protected:
        //@cond
        template <bool IsConst>
        class iterator_type
        {
            friend class LazyList;

        protected:
            value_type * m_pNode;

            void next()
            {
                assert( m_pNode != nullptr );

                node_type * pNode = node_traits::to_node_ptr( m_pNode );
                node_type * pNext = pNode->m_pNext.load(memory_model::memory_order_relaxed);
                if ( pNext != nullptr )
                    m_pNode = node_traits::to_value_ptr( pNext );
            }

            iterator_type( node_type * pNode )
            {
                m_pNode = node_traits::to_value_ptr( pNode );
            }

        public:
            typedef typename cds::details::make_const_type<value_type, IsConst>::pointer   value_ptr;
            typedef typename cds::details::make_const_type<value_type, IsConst>::reference value_ref;

            iterator_type()
                : m_pNode( nullptr )
            {}

            iterator_type( const iterator_type& src )
                : m_pNode( src.m_pNode )
            {}

            value_ptr operator ->() const
            {
                return m_pNode;
            }

            value_ref operator *() const
            {
                assert( m_pNode != nullptr );
                return *m_pNode;
            }

            /// Pre-increment
            iterator_type& operator ++()
            {
                next();
                return *this;
            }

            /// Post-increment
            iterator_type operator ++(int)
            {
                iterator_type i(*this);
                next();
                return i;
            }

            iterator_type& operator = (const iterator_type& src)
            {
                m_pNode = src.m_pNode;
                return *this;
            }

            template <bool C>
            bool operator ==(iterator_type<C> const& i ) const
            {
                return m_pNode == i.m_pNode;
            }
            template <bool C>
            bool operator !=(iterator_type<C> const& i ) const
            {
                return m_pNode != i.m_pNode;
            }
        };
        //@endcond

    public:
        /// Forward iterator
        typedef iterator_type<false>    iterator;
        /// Const forward iterator
        typedef iterator_type<true>     const_iterator;

        /// Returns a forward iterator addressing the first element in a list
        /**
            For empty list \code begin() == end() \endcode
        */
        iterator begin()
        {
            iterator it( &m_Head );
            ++it        ;   // skip dummy head
            return it;
        }

        /// Returns an iterator that addresses the location succeeding the last element in a list
        /**
            Do not use the value returned by <tt>end</tt> function to access any item.

            The returned value can be used only to control reaching the end of the list.
            For empty list \code begin() == end() \endcode
        */
        iterator end()
        {
            return iterator( &m_Tail );
        }

        /// Returns a forward const iterator addressing the first element in a list
        const_iterator begin() const
        {
            return cbegin();
        }
        /// Returns a forward const iterator addressing the first element in a list
        const_iterator cbegin() const
        {
            const_iterator it( const_cast<node_type *>(&m_Head) );
            ++it;   // skip dummy head
            return it;
        }

        /// Returns an const iterator that addresses the location succeeding the last element in a list
        const_iterator end() const
        {
            return cend();
        }
        /// Returns an const iterator that addresses the location succeeding the last element in a list
        const_iterator cend() const
        {
            return const_iterator( const_cast<node_type *>(&m_Tail) );
        }

    public:
        /// Default constructor initializes empty list
        LazyList()
        {
            static_assert( (std::is_same< gc, typename node_type::gc >::value), "GC and node_type::gc must be the same type" );
            m_Head.m_pNext.store( &m_Tail, memory_model::memory_order_relaxed );
        }

        /// Destroys the list object
        ~LazyList()
        {
            clear();
            assert( m_Head.m_pNext.load(memory_model::memory_order_relaxed) == &m_Tail );
            m_Head.m_pNext.store( nullptr, memory_model::memory_order_relaxed );
        }

        /// Inserts new node
        /**
            The function inserts \p val in the list if the list does not contain
            an item with key equal to \p val.

            Returns \p true if \p val is linked into the list, \p false otherwise.
        */
        bool insert( value_type& val )
        {
            return insert_at( &m_Head, val );
        }

        /// Ensures that the \p item exists in the list
        /**
            The operation performs inserting or changing data with lock-free manner.

            If the item \p val not found in the list, then \p val is inserted into the list.
            Otherwise, the functor \p func is called with item found.
            The functor signature is:
            \code
            struct functor {
                void operator()( bool bNew, value_type& item, value_type& val );
            };
            \endcode
            with arguments:
            - \p bNew - \p true if the item has been inserted, \p false otherwise
            - \p item - item of the list
            - \p val - argument \p val passed into the \p ensure function
            If new item has been inserted (i.e. \p bNew is \p true) then \p item and \p val arguments
            refers to the same thing.

            The functor may change non-key fields of the \p item.
            While the functor \p f is calling the item \p item is locked.

            Returns <tt> std::pair<bool, bool>  </tt> where \p first is true if operation is successfull,
            \p second is true if new item has been added or \p false if the item with \p key
            already is in the list.
        */

        template <typename Func>
        std::pair<bool, bool> ensure( value_type& val, Func func )
        {
            return ensure_at( &m_Head, val, func );
        }

        /// Finds the key \p key
        /** \anchor cds_intrusive_LazyList_nogc_find_func
            The function searches the item with key equal to \p key
            and calls the functor \p f for item found.
            The interface of \p Func functor is:
            \code
            struct functor {
                void operator()( value_type& item, Q& key );
            };
            \endcode
            where \p item is the item found, \p key is the <tt>find</tt> function argument.

            The functor may change non-key fields of \p item.
            While the functor \p f is calling the item found \p item is locked.

            The function returns \p true if \p key is found, \p false otherwise.
        */
        template <typename Q, typename Func>
        bool find( Q& key, Func f )
        {
            return find_at( &m_Head, key, key_comparator(), f );
        }
        //@cond
        template <typename Q, typename Func>
        bool find( Q const& key, Func f )
        {
            return find_at( &m_Head, key, key_comparator(), f );
        }
        //@endcond

        /// Finds the key \p key using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_intrusive_LazyList_nogc_find_func "find(Q&, Func)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p pred must imply the same element order as the comparator used for building the list.
        */
        template <typename Q, typename Less, typename Func>
        bool find_with( Q& key, Less pred, Func f )
        {
            CDS_UNUSED( pred );
            return find_at( &m_Head, key, cds::opt::details::make_comparator_from_less<Less>(), f );
        }
        //@cond
        template <typename Q, typename Less, typename Func>
        bool find_with( Q const& key, Less pred, Func f )
        {
            CDS_UNUSED( pred );
            return find_at( &m_Head, key, cds::opt::details::make_comparator_from_less<Less>(), f );
        }
        //@endcond

        /// Finds the key \p key
        /** \anchor cds_intrusive_LazyList_nogc_find_val
            The function searches the item with key equal to \p key
            and returns pointer to value found or \p nullptr.
        */
        template <typename Q>
        value_type * find( Q const& key )
        {
            return find_at( &m_Head, key, key_comparator() );
        }

        /// Finds the key \p key using \p pred predicate for searching
        /**
            The function is an analog of \ref cds_intrusive_LazyList_nogc_find_val "find(Q const&)"
            but \p pred is used for key comparing.
            \p Less functor has the interface like \p std::less.
            \p pred must imply the same element order as the comparator used for building the list.
        */
        template <typename Q, typename Less>
        value_type * find_with( Q const& key, Less pred )
        {
            CDS_UNUSED( pred );
            return find_at( &m_Head, key, cds::opt::details::make_comparator_from_less<Less>() );
        }

        /// Clears the list
        /**
            The function unlink all items from the list.
            For each unlinked item the item disposer \p disp is called after unlinking.

            This function is not thread-safe.
        */
        template <typename Disposer>
        void clear( Disposer disp )
        {
            node_type * pHead = m_Head.m_pNext.exchange( &m_Tail, memory_model::memory_order_release );

            while ( pHead != &m_Tail ) {
                node_type * p = pHead->m_pNext.load(memory_model::memory_order_relaxed);
                dispose_node( pHead, disp );
                pHead = p;
            }
        }

        /// Clears the list using default disposer
        /**
            The function clears the list using default (provided in class template) disposer functor.
        */
        void clear()
        {
            clear( disposer() );
        }

        /// Checks if the list is empty
        bool empty() const
        {
            return m_Head.m_pNext.load(memory_model::memory_order_relaxed) == &m_Tail;
        }

        /// Returns list's item count
        /**
            The value returned depends on opt::item_counter option. For atomicity::empty_item_counter,
            this function always returns 0.

            <b>Warning</b>: even if you use real item counter and it returns 0, this fact is not mean that the list
            is empty. To check list emptyness use \ref empty() method.
        */
        size_t size() const
        {
            return m_ItemCounter.value();
        }

    protected:
        //@cond
        // split-list support
        bool insert_aux_node( node_type * pNode )
        {
            return insert_aux_node( &m_Head, pNode );
        }

        // split-list support
        bool insert_aux_node( node_type * pHead, node_type * pNode )
        {
            assert( pHead != nullptr );
            assert( pNode != nullptr );

            // Hack: convert node_type to value_type.
            // In principle, auxiliary node can be non-reducible to value_type
            // We assume that comparator can correctly distinguish aux and regular node.
            return insert_at( pHead, *node_traits::to_value_ptr( pNode ) );
        }

        bool insert_at( node_type * pHead, value_type& val )
        {
            link_checker::is_empty( node_traits::to_node_ptr( val ) );
            position pos;
            key_comparator  cmp;

            while ( true ) {
                search( pHead, val, pos, key_comparator() );
                {
                    auto_lock_position alp( pos );
                    if ( validate( pos.pPred, pos.pCur )) {
                        if ( pos.pCur != &m_Tail && cmp( *node_traits::to_value_ptr( *pos.pCur ), val ) == 0 ) {
                            // failed: key already in list
                            return false;
                        }
                        else {
                            link_node( node_traits::to_node_ptr( val ), pos.pPred, pos.pCur );
                            ++m_ItemCounter;
                            return true;
                        }
                    }
                }
            }
        }

        iterator insert_at_( node_type * pHead, value_type& val )
        {
            if ( insert_at( pHead, val ))
                return iterator( node_traits::to_node_ptr( val ));
            return end();
        }


        template <typename Func>
        std::pair<iterator, bool> ensure_at_( node_type * pHead, value_type& val, Func func )
        {
            position pos;
            key_comparator  cmp;

            while ( true ) {
                search( pHead, val, pos, key_comparator() );
                {
                    auto_lock_position alp( pos );
                    if ( validate( pos.pPred, pos.pCur )) {
                        if ( pos.pCur != &m_Tail && cmp( *node_traits::to_value_ptr( *pos.pCur ), val ) == 0 ) {
                            // key already in the list

                            func( false, *node_traits::to_value_ptr( *pos.pCur ) , val );
                            return std::make_pair( iterator( pos.pCur ), false );
                        }
                        else {
                            // new key
                            link_checker::is_empty( node_traits::to_node_ptr( val ) );

                            link_node( node_traits::to_node_ptr( val ), pos.pPred, pos.pCur );
                            func( true, val, val );
                            ++m_ItemCounter;
                            return std::make_pair( iterator( node_traits::to_node_ptr( val )), true );
                        }
                    }
                }
            }
        }

        template <typename Func>
        std::pair<bool, bool> ensure_at( node_type * pHead, value_type& val, Func func )
        {
            std::pair<iterator, bool> ret = ensure_at_( pHead, val, func );
            return std::make_pair( ret.first != end(), ret.second );
        }

        template <typename Q, typename Compare, typename Func>
        bool find_at( node_type * pHead, Q& val, Compare cmp, Func f )
        {
            position pos;

            search( pHead, val, pos, cmp );
            if ( pos.pCur != &m_Tail ) {
                std::unique_lock< typename node_type::lock_type> al( pos.pCur->m_Lock );
                if ( cmp( *node_traits::to_value_ptr( *pos.pCur ), val ) == 0 )
                {
                    f( *node_traits::to_value_ptr( *pos.pCur ), val );
                    return true;
                }
            }
            return false;
        }

        template <typename Q, typename Compare>
        value_type * find_at( node_type * pHead, Q& val, Compare cmp)
        {
            iterator it = find_at_( pHead, val, cmp );
            if ( it != end() )
                return &*it;
            return nullptr;
        }

        template <typename Q, typename Compare>
        iterator find_at_( node_type * pHead, Q& val, Compare cmp)
        {
            position pos;

            search( pHead, val, pos, cmp );
            if ( pos.pCur != &m_Tail ) {
                std::unique_lock< typename node_type::lock_type> al( pos.pCur->m_Lock );
                if ( cmp( *node_traits::to_value_ptr( *pos.pCur ), val ) == 0 )
                {
                    return iterator( pos.pCur );
                }
            }
            return end();
        }

        //@endcond

    protected:
        //@cond
        template <typename Q, typename Compare>
        void search( node_type * pHead, const Q& key, position& pos, Compare cmp )
        {
            const node_type * pTail = &m_Tail;

            node_type * pCur = pHead;
            node_type * pPrev = pHead;

            while ( pCur != pTail && ( pCur == pHead || cmp( *node_traits::to_value_ptr( *pCur ), key ) < 0 )) {
                pPrev = pCur;
                pCur = pCur->m_pNext.load(memory_model::memory_order_acquire);
            }

            pos.pCur = pCur;
            pos.pPred = pPrev;
        }

        static bool validate( node_type * pPred, node_type * pCur )
        {
            return pPred->m_pNext.load(memory_model::memory_order_acquire) == pCur;
        }

        //@endcond
    };

}}  // namespace cds::intrusive

#endif  // #ifndef __CDS_INTRUSIVE_LAZY_LIST_NOGC_H
