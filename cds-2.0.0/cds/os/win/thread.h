/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_OS_WIN_THREAD_H
#define __CDS_OS_WIN_THREAD_H

#include <windows.h>

namespace cds { namespace OS {
    /// Windows-specific functions
    CDS_CXX11_INLINE_NAMESPACE namespace Win32 {

        /// OS-specific type of thread identifier
        typedef DWORD           ThreadId;

        /// Get current thread id
        static inline ThreadId get_current_thread_id()
        {
            return ::GetCurrentThreadId();
        }

        /// Tests whether the thread is alive
        static inline bool is_thread_alive( ThreadId id )
        {
            HANDLE h = ::OpenThread( SYNCHRONIZE, FALSE, id );
            if ( h == nullptr )
                return false;
            ::CloseHandle( h );
            return true;
        }
    }    // namespace Win32

    //@cond
    CDS_CONSTEXPR const Win32::ThreadId c_NullThreadId = 0;

#ifndef CDS_CXX11_INLINE_NAMESPACE_SUPPORT
    using Win32::ThreadId;
    using Win32::get_current_thread_id;
    using Win32::is_thread_alive;
#endif
    //@endcond

}} // namespace cds::OS

#endif // #ifndef __CDS_OS_WIN_THREAD_H
