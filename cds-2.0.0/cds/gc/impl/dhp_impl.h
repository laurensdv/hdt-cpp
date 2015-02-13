/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_GC_IMPL_DHP_IMPL_H
#define __CDS_GC_IMPL_DHP_IMPL_H

#include <cds/threading/model.h>

//@cond
namespace cds { namespace gc {

    namespace dhp {

        inline Guard::Guard()
        {
            cds::threading::getGC<DHP>().allocGuard( *this );
        }

        inline Guard::~Guard()
        {
            cds::threading::getGC<DHP>().freeGuard( *this );
        }

        template <size_t Count>
        inline GuardArray<Count>::GuardArray()
        {
            cds::threading::getGC<DHP>().allocGuard( *this );
        }

        template <size_t Count>
        inline GuardArray<Count>::~GuardArray()
        {
            cds::threading::getGC<DHP>().freeGuard( *this );
        }
    } // namespace dhp


    inline DHP::thread_gc::thread_gc(
        bool    bPersistent
        )
        : m_bPersistent( bPersistent )
    {
        if ( !cds::threading::Manager::isThreadAttached() )
            cds::threading::Manager::attachThread();
    }

    inline DHP::thread_gc::~thread_gc()
    {
        if ( !m_bPersistent )
            cds::threading::Manager::detachThread();
    }

    inline /*static*/ void DHP::thread_gc::alloc_guard( cds::gc::dhp::details::guard& g )
    {
        return cds::threading::getGC<DHP>().allocGuard(g);
    }
    inline /*static*/ void DHP::thread_gc::free_guard( cds::gc::dhp::details::guard& g )
    {
        cds::threading::getGC<DHP>().freeGuard(g);
    }

    inline void DHP::scan()
    {
        cds::threading::getGC<DHP>().scan();
    }

}} // namespace cds::gc
//@endcond

#endif // #ifndef __CDS_GC_IMPL_DHP_IMPL_H
