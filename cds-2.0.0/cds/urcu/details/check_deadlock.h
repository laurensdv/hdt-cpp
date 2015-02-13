/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef _CDS_URCU_DETAILS_CHECK_DEADLOCK_H
#define _CDS_URCU_DETAILS_CHECK_DEADLOCK_H

#include <cds/urcu/options.h>

//@cond
namespace cds { namespace urcu { namespace details {

    template <class RCU, typename PolicyType>
    struct check_deadlock_policy
    {
        static void check()
        {
            assert( !RCU::is_locked() );
            if ( RCU::is_locked() )
                throw cds::urcu::rcu_deadlock();
        }
    };

    template <class RCU>
    struct check_deadlock_policy< RCU, cds::opt::v::rcu_no_check_deadlock>
    {
        static void check()
        {}
    };

    template <class RCU>
    struct check_deadlock_policy< RCU, cds::opt::v::rcu_assert_deadlock>
    {
        static void check()
        {
            assert( !RCU::is_locked() );
        }
    };

}}} // namespace cds::urcu::details
//@endcond

#endif // #ifndef _CDS_URCU_DETAILS_CHECK_DEADLOCK_H
