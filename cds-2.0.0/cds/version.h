/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_VERSION_H
#define __CDS_VERSION_H

// cds library version

#define CDS_VERSION        0x020000

#define CDS_VERSION_MAJOR  ((CDS_VERSION & 0xFF0000)>> 16)
#define CDS_VERSION_MINOR  ((CDS_VERSION & 0x00FF00) >> 8)
#define CDS_VERSION_PATCH  (CDS_VERSION & 0x0000FF)

// CDS_VERSION == CDS_VERSION_MAJOR '.' CDS_VERSION_MINOR '.' CDS_VERSION_PATCH
#define CDS_VERSION_STRING        "2.0.0"

#endif  // #ifndef __CDS_VERSION_H

