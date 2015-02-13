/*
    This file is a part of libcds - Concurrent Data Structures library
    Version: 2.0.0

    (C) Copyright Maxim Khizhinsky (libcds.dev@gmail.com) 2006-2014
    Distributed under the BSD license (see accompanying file license.txt)

    Source code repo: http://github.com/khizmax/libcds/
    Download: http://sourceforge.net/projects/libcds/files/
*/

#ifndef __CDS_DETAILS_BIT_REVERSE_COUNTER_H
#define __CDS_DETAILS_BIT_REVERSE_COUNTER_H

#include <cds/algo/bitop.h>

//@cond
namespace cds { namespace bitop {

    template <typename Counter = size_t>
    class bit_reverse_counter
    {
    public:
        typedef Counter     counter_type;

    private:
        counter_type        m_nCounter;
        counter_type        m_nReversed;
        int                 m_nHighBit;

    public:
        bit_reverse_counter()
            : m_nCounter(0)
            , m_nReversed(0)
            , m_nHighBit(-1)
        {}

        counter_type inc()
        {
            ++m_nCounter;
            int nBit;
            for ( nBit = m_nHighBit - 1; nBit >= 0; --nBit ) {
                if ( !cds::bitop::complement( m_nReversed, nBit ))
                    break;
            }
            if ( nBit < 0 ) {
                m_nReversed = m_nCounter;
                ++m_nHighBit;
            }
            return m_nReversed;
        }

        counter_type dec()
        {
            --m_nCounter;
            int nBit;
            for ( nBit = m_nHighBit - 1; nBit >= 0; --nBit ) {
                if ( cds::bitop::complement( m_nReversed, nBit ) )
                    break;
            }
            if ( nBit < 0 ) {
                m_nReversed = m_nCounter;
                --m_nHighBit;
            }
            return m_nReversed;
        }

        counter_type    value() const
        {
            return m_nCounter;
        }

        counter_type    reversed_value() const
        {
            return m_nReversed;
        }
    };

}}   // namespace cds::bitop
//@endcond

#endif // #ifndef __CDS_DETAILS_BIT_REVERSE_COUNTER_H
