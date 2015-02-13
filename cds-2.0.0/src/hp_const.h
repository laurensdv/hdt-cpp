/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDSIMPL_HP_CONST_H
#define __CDSIMPL_HP_CONST_H

/*
    File: hp_const.h

    Michael's Hazard Pointer reclamation schema global constants
    Gidenstam's reclamation schema global constants

    Editions:
        2008.03.10    Maxim.Khiszinsky    Created
*/

namespace cds { namespace gc {

    //---------------------------------------------------------------
    // Hazard Pointers reclamation schema constants
    namespace hp {
        // Max number of threads expected
        static const size_t c_nMaxThreadCount     = 100;

        // Number of Hazard Pointers per thread
        static const size_t c_nHazardPointerPerThread = 8;
    } // namespace hp

} /* namespace gc */ }    /* namespace cds */

#endif    // #ifndef __CDSIMPL_HZP_CONST_H
