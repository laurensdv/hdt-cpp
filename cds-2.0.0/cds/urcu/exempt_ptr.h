/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_URCU_EXEMPT_PTR_H
#define __CDS_URCU_EXEMPT_PTR_H

#include <type_traits>
#include <cds/details/defs.h>

namespace cds { namespace urcu {

    //@cond
    namespace details {
        template <typename Node, typename Value>
        struct conventional_exempt_member_cast
        {
            Value * operator()( Node * p ) const
            {
                return &p->m_Value;
            }
        };

        template <typename Node, typename Value>
        struct conventional_exempt_pair_cast
        {
            Value * operator()( Node * p ) const
            {
                return &p->m_Data;
            }
        };
    } // namespace details
    //@endcond

    /// Exempt pointer for RCU
    /**
        This special pointer class is intended for returning extracted node from RCU-based container.
        The destructor (and \p release() member function) invokes <tt>RCU::retire_ptr< Disposer >()</tt> function to dispose the node.
        For non-intrusive containers from \p cds::container namespace \p Disposer is usually an invocation
        of node deallocator. For intrusive containers the disposer can be empty or it can trigger an event "node can be reused safely".
        In any case, the exempt pointer concept keeps RCU semantics.

        You don't need use this helper class directly. Any RCU-based container typedefs a simplified version of this template.

        Template arguments:
        - \p RCU - one of \ref cds_urcu_gc "RCU type"
        - \p NodeType - container's node type
        - \p ValueType - value type stored in container's node. For intrusive containers it is the same as \p NodeType
        - \p Disposer - a disposer functor
        - \p Cast - a functor for casting from \p NodeType to \p ValueType. For intrusive containers
            the casting is usually disabled, i.e. \p Cast is \p void.
    */
    template <
        class RCU,
        typename NodeType,
        typename ValueType,
        typename Disposer,
#ifdef CDS_DOXYGEN_INVOKED
        typename Cast
#else
        typename Cast=details::conventional_exempt_member_cast<NodeType, ValueType>
#endif
    >
    class exempt_ptr
    {
        //@cond
        struct trivial_cast {
            ValueType * operator()( NodeType * p ) const
            {
                return p;
            }
        };
        //@endcond
    public:
        typedef RCU         rcu         ;   ///< RCU type - one of <tt>cds::urcu::gc< ... ></tt>
        typedef NodeType    node_type   ;   ///< Node type
        typedef ValueType   value_type  ;   ///< Value type
        typedef Disposer    disposer    ;   ///< Disposer calling when release
        /// Functor converting \p node_type to \p value_type
        typedef typename std::conditional< std::is_same< Cast, void >::value, trivial_cast, Cast>::type node_to_value_cast;

    private:
        //@cond
        node_type *     m_pNode;
        //@endcond

    public:
        /// Constructs empty pointer
        exempt_ptr() CDS_NOEXCEPT
            : m_pNode( nullptr )
        {}

        //@cond
        /// Creates exempt pointer for \p pNode. Only for internal use.
        explicit exempt_ptr( node_type * pNode ) CDS_NOEXCEPT
            : m_pNode( pNode )
        {}
        explicit exempt_ptr( std::nullptr_t ) CDS_NOEXCEPT
            : m_pNode( nullptr )
        {}
        //@endcond

        /// Move ctor
        exempt_ptr( exempt_ptr&& p ) CDS_NOEXCEPT
            : m_pNode( p.m_pNode )
        {
            p.m_pNode = nullptr;
        }

        /// The exempt pointer is not copy-constructible
        exempt_ptr( exempt_ptr const& ) = delete;

        /// Releases the pointer
        ~exempt_ptr()
        {
            release();
        }

        /// Checks if the pointer is \p nullptr
        bool empty() const CDS_NOEXCEPT
        {
            return m_pNode == nullptr;
        }

        /// \p bool operator returns <tt>!empty()</tt>
        explicit operator bool() const CDS_NOEXCEPT
        {
            return !empty();
        }

        /// Dereference operator
        value_type * operator->() const CDS_NOEXCEPT
        {
            return !empty() ? node_to_value_cast()(m_pNode) : nullptr;
        }

        /// Returns a reference to the value
        value_type& operator *() CDS_NOEXCEPT
        {
            assert( !empty());
            return *node_to_value_cast()( m_pNode );
        }

        /// Move assignment. Can be called only outside of RCU critical section
        exempt_ptr& operator =( exempt_ptr&& p ) CDS_NOEXCEPT
        {
            release();
            m_pNode = p.m_pNode;
            p.m_pNode = nullptr;
            return *this;
        }

        /// The exempt pointer is not copy-assignable
        exempt_ptr& operator=(exempt_ptr const&) = delete;

        /// Disposes the pointer. Should be called only outside of RCU critical section
        void release()
        {
            if ( !empty() ) {
                assert( !rcu::is_locked() );
                rcu::template retire_ptr<disposer>( m_pNode );
                m_pNode = nullptr;
            }
        }
    };
}} // namespace cds::urcu

#endif //#ifndef __CDS_URCU_EXEMPT_PTR_H
