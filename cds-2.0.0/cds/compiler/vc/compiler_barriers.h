/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_COMPILER_VC_COMPILER_BARRIERS_H
#define __CDS_COMPILER_VC_COMPILER_BARRIERS_H

#if CDS_COMPILER_VERSION < 1700
    // VC++ up to vc10

#   include <intrin.h>

#   pragma intrinsic(_ReadWriteBarrier)
#   pragma intrinsic(_ReadBarrier)
#   pragma intrinsic(_WriteBarrier)

#   define CDS_COMPILER_RW_BARRIER  _ReadWriteBarrier()
#   define CDS_COMPILER_R_BARRIER   _ReadBarrier()
#   define CDS_COMPILER_W_BARRIER   _WriteBarrier()

#else
    // MS VC11+
#   include <atomic>

#   define CDS_COMPILER_RW_BARRIER  std::atomic_thread_fence( std::memory_order_acq_rel )
#   define CDS_COMPILER_R_BARRIER   CDS_COMPILER_RW_BARRIER
#   define CDS_COMPILER_W_BARRIER   CDS_COMPILER_RW_BARRIER

#endif

#endif  // #ifndef __CDS_COMPILER_VC_COMPILER_BARRIERS_H
