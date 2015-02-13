/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_THREADING_DETAILS_MSVC_MANAGER_H
#define __CDS_THREADING_DETAILS_MSVC_MANAGER_H

#if !( CDS_COMPILER == CDS_COMPILER_MSVC || (CDS_COMPILER == CDS_COMPILER_INTEL && CDS_OS_INTERFACE == CDS_OSI_WINDOWS))
#   error "threading/details/msvc_manager.h may be used only with Microsoft Visual C++ / Intel C++ compiler"
#endif

#include <cds/threading/details/_common.h>

//@cond
namespace cds { namespace threading {

    //@cond
    struct msvc_internal {
        typedef unsigned char  ThreadDataPlaceholder[ sizeof(ThreadData) ];
        __declspec( thread ) static ThreadDataPlaceholder s_threadData;
        __declspec( thread ) static ThreadData * s_pThreadData;
    };
    //@endcond

    /// cds::threading::Manager implementation based on Microsoft Visual C++ __declspec( thread ) construction
    CDS_CXX11_INLINE_NAMESPACE namespace msvc {

        /// Thread-specific data manager based on MSVC __declspec( thread ) feature
        class Manager {
        private :
            //@cond
            static ThreadData * _threadData()
            {
                return msvc_internal::s_pThreadData;
            }

            static ThreadData * create_thread_data()
            {
                if ( !msvc_internal::s_pThreadData ) {
                    msvc_internal::s_pThreadData = new (msvc_internal::s_threadData) ThreadData();
                }
                return msvc_internal::s_pThreadData;
            }

            static void destroy_thread_data()
            {
                if ( msvc_internal::s_pThreadData ) {
                    msvc_internal::s_pThreadData->ThreadData::~ThreadData();
                    msvc_internal::s_pThreadData = nullptr;
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
                ThreadData * pData = _threadData();
                return pData != nullptr;
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

            /// Returns internal ThreadData pointer for the current thread
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
                assert( _threadData()->m_hpManager );
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
                assert( _threadData()->m_dhpManager );
                return *(_threadData()->m_dhpManager);
            }

            //@cond
            static size_t fake_current_processor()
            {
                return _threadData()->fake_current_processor();
            }
            //@endcond
        };

    } // namespace msvc
}} // namespace cds::threading
//@endcond

#endif // #ifndef __CDS_THREADING_DETAILS_MSVC_MANAGER_H