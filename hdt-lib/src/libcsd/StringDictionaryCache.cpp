/*
 * File: CSD_Cache.cpp
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

#include <stdlib.h>

#include <string.h>
#include "StringDictionaryCache.h"

StringDictionaryCache::StringDictionaryCache(StringDictionary *child) : child(child)//, cacheint(65536), cachestr(1024)
{
	assert(child);
	elements = child->numElements();
}


StringDictionaryCache::~StringDictionaryCache()
{
	delete child;
}

uint StringDictionaryCache::locate(uchar *s, uint len)
{
	// FIXME: Not working.
#if 0
	LRU_Str::const_iterator it = cachestr.find((char *)s);

	if (it != cachestr.end()) {
		// Key found: retrieve its associated value
		cout << "1retrieving: " << it.key() << " -> " << it.value() << endl;
		return it.value();
	} else {
		// Key not found: compute and insert the value
		cout << "1not found" << s << endl;
		uint32_t value = child->locate(s, len);
		cachestr[(char *)s] = value;
		return value;
	}
#endif
	return child->locate(s, len);
}


uchar* StringDictionaryCache::extract(uint id)
{
	return child->extract(0, &id);
#if 0
	LRU_Int::const_iterator it = cacheint.find(id);

	if (it != cacheint.end()) {
		// Key found: retrieve its associated value
		//cout << "2retrieving: " << it.key() << " -> " << it.value() << endl;
		size_t len = it.value().length();
		unsigned char *ptr = (unsigned char *)malloc((1+len)*sizeof(unsigned char));
		strncpy((char *)ptr, (const char *)it.value().c_str(), len);
		ptr[len]='\0';
		return ptr;
	} else {
		// Key not found: compute and insert the value
		//cout << "2not found: " << id << endl;
		char *value = (char *) child->extract(id);

		string str(value);

		cacheint[id] = str;

		return (unsigned char *)value;
	}
#endif
}

void StringDictionaryCache::freeString(uchar *str) {
	// Do nothing.
}

uint64_t StringDictionaryCache::getSize()
{
	return child->getSize();
}

void StringDictionaryCache::save(ofstream &fp)
{
	child->save(fp);
}

StringDictionary* StringDictionaryCache::load(istream &fp)
{
	throw "Not imlemented";
}
