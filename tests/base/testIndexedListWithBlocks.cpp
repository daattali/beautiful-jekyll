/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file testIndexedListWithBlocks.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 *
 * @date 2012/07/02
 *
 * This file is part of the DGtal library
 */

//#define TRACE_BITS

#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/IndexedListWithBlocks.h"
#include "DGtal/base/Labels.h"

using namespace DGtal;
using namespace std;

template <typename Container1, typename Container2>
bool
isEqual( Container1 & c1, Container2 & c2 )
{
  return ( c1.size() == c2.size() )
    && std::equal( c1.begin(), c1.end(), c2.begin() );
}

template <typename VContainer1, typename LContainer2>
void insert( VContainer1 & c1, LContainer2 & c2, unsigned int idx, double v )
{
  c1.insert( c1.begin() + idx, v );
  c2.insert( idx, v );
}

template <typename VContainer1, typename LContainer2>
bool
checkInsert( VContainer1 & v, LContainer2 & l,
	     unsigned int nb )
{
  for ( unsigned int i = 0; i < nb; ++i )
    {
      unsigned int idx = rand() % ( l.size() + 1 );
      double val = ( (double)rand() ) / RAND_MAX;
      insert( v, l, idx, val );
    }
  return isEqual( v, l );
}

template <typename VContainer1, typename LContainer2>
void erase( VContainer1 & c1, LContainer2 & c2, unsigned int idx )
{
  c1.erase( c1.begin() + idx );
  c2.erase( idx );
}

template <typename VContainer1, typename LContainer2>
bool
checkErase( VContainer1 & v, LContainer2 & l,
	    unsigned int nb )
{
  for ( unsigned int i = 0; i < nb; ++i )
    {
      unsigned int idx = rand() % ( l.size() );
      erase( v, l, idx );
    }
  return isEqual( v, l );
}


int main()
{
  typedef IndexedListWithBlocks<double, 2, 10> MyIndexedList;
  BOOST_CONCEPT_ASSERT(( boost::Container< MyIndexedList > ));
  BOOST_CONCEPT_ASSERT(( boost::ForwardIterator< MyIndexedList::Iterator > ));
  BOOST_CONCEPT_ASSERT(( boost::ForwardIterator< MyIndexedList::ConstIterator > ));
  unsigned int nb = 0;
  unsigned int nbok = 0;
  trace.beginBlock ( "Testing IndexedListWithBlocks" );
  MyIndexedList l;
  vector<double> v;
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 0, 4.5 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 0, 10.1 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 1, 3.7 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 2, 8.4 );
  insert( v, l, 1, 2.1 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 2, -3.0 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, (unsigned int)v.size(), -13.1 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  ++nb; nbok += checkInsert( v, l, 10000 ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") 10000 insertions" << std::endl; 
  ++nb; nbok += checkErase( v, l, 10000 ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") 10000 deletions l=" << l << std::endl; 
  trace.endBlock();
  return ( nb == nbok ) ? 0 : 1;
}
/** @ingroup Tests **/
