/*
 * File: CSD_Cache2.cpp
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
#include "StringDictionaryCache2.h"

StringDictionaryCache2::StringDictionaryCache2(StringDictionary *child) : child(child)
{
	assert(child);
	elements = child->numElements();

	array.resize(child->numElements(), NULL);
}


StringDictionaryCache2::~StringDictionaryCache2()
{
	for(std::vector<unsigned char *>::iterator it = array.begin(); it != array.end(); ++it) {
		unsigned char *value = *it;
//		if(value!=NULL) {
//			child->freeString(*it);
//		}
	}

	delete child;
}

uint StringDictionaryCache2::locate(uchar *s, uint len)
{
	// FIXME: Not implemented
	return child->locate(s, len);
}


uchar* StringDictionaryCache2::extract(uint id)
{
	if(id<1 || id>array.size()) {
		return NULL;
	}

	if(array[id-1]!=NULL) {
		return array[id-1];
	}

	// Not found, fetch and add
	uchar *value = child->extract(0, &id);

	array[id-1] = value;

	return value;
}

void StringDictionaryCache2::freeString(const unsigned char *str) {
	// Do nothing, all freed on destruction.
}

uint64_t StringDictionaryCache2::getSize()
{
	return child->getSize();
}

void StringDictionaryCache2::save(ofstream &fp)
{
	child->save(fp);
}

StringDictionary* StringDictionaryCache2::load(ifstream &fp)
{
	throw "Not imlemented";
}
