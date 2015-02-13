/* SSA.h
 * Copyright (C) 2011, Rodrigo Canovas & Miguel A. Martinez-Prieto
 * all rights reserved.
 * 
 * Abstract class for implementing Compressed String Dictionaries following:
 * 
 *   ==========================================================================
 *    "Compressed String Dictionaries"
 *     Nieves R. Brisaboa, Rodrigo Canovas, Francisco Claude, 
 *     Miguel A. Martinez-Prieto and Gonzalo Navarro.
 *     10th Symposium on Experimental Algorithms (SEA'2011), p.136-147, 2011.
 *   ==========================================================================
 *             
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *                  
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * 
 * Contacting the authors:
 * Rodrigo Canovas:  rcanovas@dcc.uchile.cl
 * Miguel A. Martinez-Prieto:  migumar2@infor.uva.es
 */

#ifndef SSA_WORDS_H
#define SSA_WORDS_H

#include <libcds2/immutable/sequence.h>
#include <libcds2/immutable/bitsequence.h>

#include <libcds2/immutable/mapper.h>
#include <algorithm>

#include "SuffixArray.h"

using namespace std;
using namespace cds;

namespace csd{
	class SSA{
		public:
			SSA(basic::cds_uchar * seq, basic::cds_uint n, bool free_text=false, bool use_sampling=false);
			SSA();
			~SSA();

//			bool set_static_sequence_builder(immutable::SequenceBuilder * ssb);
			bool set_static_bitsequence_builder(immutable::BitSequenceBuilder * sbb);
			bool set_samplesuff(basic::cds_uint sample);

			bool build_index();

			basic::cds_uint size();
			void print_stats();
			basic::cds_uint length();

			basic::cds_uint LF(basic::cds_uint i);
			basic::cds_uint locate_id(basic::cds_uchar * pattern, basic::cds_uint m);
			basic::cds_uint locate(basic::cds_uchar * pattern, basic::cds_uint m, uint32_t **occs);

			basic::cds_uchar * extract_id(basic::cds_uint id, basic::cds_uint max_len);
            static SSA * load(istream &fp);
            void save(ostream & fp);

		protected:
			basic::cds_uint n;
			immutable::Sequence * bwt;

			immutable::BitSequence * sampled;
			basic::cds_uint samplesuff;
			basic::cds_uint * suff_sample;  
			
			basic::cds_uint * occ;
			basic::cds_uint maxV;
			bool built;
			bool free_text;
			bool use_sampling;
			bool *alphabet;	

			/*use only for construction*/
			basic::cds_uchar * _seq;
			basic::cds_uint * _bwt;   
			unsigned long * _sa;   
//			immutable::SequenceBuilder * _ssb;
			immutable::BitSequenceBuilder * _sbb;
			/*******************************/

			void build_bwt();
			void build_sa();
			int cmp(basic::cds_uint i, basic::cds_uint j);
	};

};
#endif
