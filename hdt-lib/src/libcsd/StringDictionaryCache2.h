/*
 * File: CSD_Cache2.hpp
 * Last modified: $Date: 2011-08-21 05:35:30 +0100 (dom, 21 ago 2011) $
 * Revision: $Revision: 180 $
 * Last modified by: $Author: mario.arias $
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
 * Contacting the authors:
 *   Mario Arias:               mario.arias@gmail.com
 *   Javier D. Fernandez:       jfergar@infor.uva.es
 *   Miguel A. Martinez-Prieto: migumar2@infor.uva.es
 *
 */

#ifndef _CSDCACHE2_H
#define _CSDCACHE2_H

#include <iostream>
#include <cassert>
#include <string>
#include <string.h>
#include <set>

using namespace std;

#include <HDTListener.hpp>

#include "StringDictionary.h"


class StringDictionaryCache2 : public StringDictionary
{
private:
	StringDictionary *child;
	vector<unsigned char *> array;

  public:		
    /** General constructor **/
	StringDictionaryCache2(StringDictionary *child);

    /** General destructor. */
    ~StringDictionaryCache2();
    
    /** Returns the ID that identify s[1..length]. If it does not exist,
	returns 0.
	@s: the string to be located.
	@len: the length (in characters) of the string s.
    */
    uint locate(uchar *s, uint len);

    /** Returns the string identified by id.
	@id: the identifier to be extracted.
    */
    uchar * extract(uint id);

    void freeString(const unsigned char *str);

    /** Obtains the original Tdict from its CSD_PFC representation. Each string is
	separated by '\n' symbols.
	@dict: the plain uncompressed dictionary.
	@return: number of total symbols in the dictionary.
    */
    unsigned int decompress(unsigned char **dict);

    /** Returns the size of the structure in bytes. */
    uint64_t getSize();

    /** Stores a CSD_PFC structure given a file pointer.
	@fp: pointer to the file saving a CSD_PFC structure.
    */
    void save(ofstream & fp);

    /** Loads a CSD_PFC structure from a file pointer.
	@fp: pointer to the file storing a CSD_PFC structure. */
    static StringDictionary * load(ifstream & fp);

    StringDictionary *getChild() {
    	return child;
    }
  };

#endif  
