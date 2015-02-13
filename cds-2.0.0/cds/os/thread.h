/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_OS_THREAD_H
#define __CDS_OS_THREAD_H

#include <thread>
#include <cds/details/defs.h>

#if CDS_OS_TYPE == CDS_OS_WIN32 || CDS_OS_TYPE == CDS_OS_WIN64 || CDS_OS_TYPE == CDS_OS_MINGW
#    include <cds/os/win/thread.h>
#else
#    include <cds/os/posix/thread.h>
#endif

namespace cds { namespace OS {

    /// Default backoff::yield implementation
    static inline void    backoff()
    {
        std::this_thread::yield();
    }
}} // namespace cds::OS

#endif    // #ifndef __CDS_OS_THREAD_H
