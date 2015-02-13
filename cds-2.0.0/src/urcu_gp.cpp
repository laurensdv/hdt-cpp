/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#include <cds/urcu/details/gp.h>

namespace cds { namespace urcu { namespace details {

    template<> CDS_EXPORT_API singleton_vtbl * gp_singleton_instance< general_instant_tag >::s_pRCU = nullptr;
    template<> CDS_EXPORT_API singleton_vtbl * gp_singleton_instance< general_buffered_tag >::s_pRCU = nullptr;
    template<> CDS_EXPORT_API singleton_vtbl * gp_singleton_instance< general_threaded_tag >::s_pRCU = nullptr;

}}} // namespace cds::urcu::details
