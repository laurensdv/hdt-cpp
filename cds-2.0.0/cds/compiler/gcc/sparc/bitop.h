/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_COMPILER_GCC_SPARC_BITOP_H
#define __CDS_COMPILER_GCC_SPARC_BITOP_H

//@cond none
namespace cds {
    namespace bitop { namespace platform { namespace gcc { namespace Sparc {

        // MSB - return index (1..64) of most significant bit in nArg. If nArg == 0 return 0
        // Source: UltraSPARC Architecture 2007
        //
        // Test result: this variant and its variation about 100 times slower then generic implementation :-(
        static inline int sparc_msb64( atomic64u_t nArg )
        {
            atomic64u_t result;
            asm volatile (
                "neg %[nArg], %[result] \n\t"
                "xnor %[nArg], %[result], %%g5 \n\t"
                "popc %%g5, %[result] \n\t"
                "movrz %[nArg], %%g0, %[result] \n\t"
                : [result] "=r" (result)
                : [nArg] "r" (nArg)
                : "g5"
            );
            return result;
        }

        // MSB - return index (1..32) of most significant bit in nArg. If nArg == 0 return 0
        static inline int sparc_msb32( uint32_t nArg )
        {
            return sparc_msb64( (atomic64u_t) nArg );
        }

    }} // namespace gcc::Sparc

    using namespace gcc::Sparc;

}}}    // namespace cds::bitop::platform
//@endcond

#endif // #ifndef __CDS_COMPILER_GCC_SPARC_BITOP_H
