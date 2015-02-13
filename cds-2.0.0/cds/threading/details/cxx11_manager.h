/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_THREADING_DETAILS_CXX11_MANAGER_H
#define __CDS_THREADING_DETAILS_CXX11_MANAGER_H

#include <cds/threading/details/_common.h>

#ifndef CDS_CXX11_THREAD_LOCAL_SUPPORT
#   error "The compiler does not support C++11 thread_local keyword. You cannot use CDS_THREADING_CXX11 threading model."
#endif

//@cond
namespace cds { namespace threading {

    //@cond
    struct cxx11_internal {
        typedef unsigned char  ThreadDataPlaceholder[ sizeof(ThreadData) ];
        static thread_local ThreadDataPlaceholder CDS_DATA_ALIGNMENT(8) s_threadData;
        static thread_local ThreadData * s_pThreadData;
    };
    //@endcond

    /// cds::threading::Manager implementation based on c++11 thread_local declaration
    CDS_CXX11_INLINE_NAMESPACE namespace cxx11 {

        /// Thread-specific data manager based on c++11 thread_local feature
        class Manager {
        private :
            //@cond

            static ThreadData * _threadData()
            {
                return cxx11_internal::s_pThreadData;
            }

            static ThreadData * create_thread_data()
            {
                if ( !cxx11_internal::s_pThreadData ) {
                    cxx11_internal::s_pThreadData = new (cxx11_internal::s_threadData) ThreadData();
                }
                return cxx11_internal::s_pThreadData;
            }

            static void destroy_thread_data()
            {
                if ( cxx11_internal::s_pThreadData ) {
                    ThreadData * p = cxx11_internal::s_pThreadData;
                    cxx11_internal::s_pThreadData = nullptr;
                    p->ThreadData::~ThreadData();
                }
            }
            //@endcond

        public:
            /// Initialize manager (empty function)
            /**
                This function is automatically called by cds::Initialize
            */
            static void init()
            {}

            /// Terminate manager (empty function)
            /**
                This function is automatically called by cds::Terminate
            */
            static void fini()
            {}

            /// Checks whether current thread is attached to \p libcds feature or not.
            static bool isThreadAttached()
            {
                return _threadData() != nullptr;
            }

            /// This method must be called in beginning of thread execution
            static void attachThread()
            {
                create_thread_data()->init();
            }

            /// This method must be called in end of thread execution
            static void detachThread()
            {
                assert( _threadData() );

                if ( _threadData()->fini() )
                    destroy_thread_data();
            }

            /// Returns ThreadData pointer for the current thread
            static ThreadData * thread_data()
            {
                ThreadData * p = _threadData();
                assert( p );
                return p;
            }

            /// Get gc::HP thread GC implementation for current thread
            /**
                The object returned may be uninitialized if you did not call attachThread in the beginning of thread execution
                or if you did not use gc::HP.
                To initialize gc::HP GC you must constuct cds::gc::HP object in the beginning of your application
            */
            static gc::HP::thread_gc_impl&   getHZPGC()
            {
                assert( _threadData()->m_hpManager != nullptr );
                return *(_threadData()->m_hpManager);
            }

            /// Get gc::DHP thread GC implementation for current thread
            /**
                The object returned may be uninitialized if you did not call attachThread in the beginning of thread execution
                or if you did not use gc::DHP.
                To initialize gc::DHP GC you must constuct cds::gc::DHP object in the beginning of your application
            */
            static gc::DHP::thread_gc_impl&   getDHPGC()
            {
                assert( _threadData()->m_dhpManager != nullptr );
                return *(_threadData()->m_dhpManager);
            }

            //@cond
            static size_t fake_current_processor()
            {
                return _threadData()->fake_current_processor();
            }
            //@endcond
        };

    } // namespace cxx11

}} // namespace cds::threading
//@endcond

#endif // #ifndef __CDS_THREADING_DETAILS_CXX11_MANAGER_H
