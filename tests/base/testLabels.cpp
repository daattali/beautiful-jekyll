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
 * @file testLabels.cpp
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
#include <bitset>
#include "DGtal/base/Common.h"
#include "DGtal/base/Labels.h"

using namespace DGtal;


template <typename Container1, typename Container2>
bool
isEqual( Container1 & c1, Container2 & c2 )
{
  if ( c1.size() == c2.size() )
    {
      for ( unsigned int i = 0; i < c1.size(); ++i )
        {
          if ( c1.test( i ) != c2.test( i ) )
            return false;
        }
      return true;
    }
  return false;
}

template <typename VContainer1, typename LContainer2>
void insert( VContainer1 & c1, LContainer2 & c2, unsigned int idx )
{
  c1.set( idx );
  c2.set( idx );
}

template <typename VContainer1, typename LContainer2>
bool
checkInsert( VContainer1 & v, LContainer2 & l,
	     unsigned int nb )
{
  for ( unsigned int i = 0; i < nb; ++i )
    {
      unsigned int idx = rand() % ( l.size() );
      insert( v, l, idx );
    }
  return isEqual( v, l );
}

template <typename VContainer1, typename LContainer2>
void erase( VContainer1 & c1, LContainer2 & c2, unsigned int idx )
{
  c1.reset( idx );
  c2.reset( idx );
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
  typedef Labels<80, DGtal::uint32_t> MyLabels;
  typedef MyLabels::ConstIterator LabelsConstIterator;
  typedef std::bitset<80> MyBitset;

  BOOST_CONCEPT_ASSERT(( boost::ForwardIterator< LabelsConstIterator > ));

  unsigned int nb = 0;
  unsigned int nbok = 0;
  trace.beginBlock ( "Testing Labels" );
  MyLabels l;
  MyBitset v;
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 15 );
  insert( v, l, 4 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 62 );
  insert( v, l, 4 );
  insert( v, l, 78 );
  insert( v, l, 31 );
  insert( v, l, 32 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  checkInsert( v, l, 40 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  checkErase( v, l, 200 );
  ++nb; nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl;
  for ( LabelsConstIterator it = l.begin(), it_end = l.end();
        it != it_end; ++it )
    std::cout << " " << *it;
  std::cout << std::endl;

  trace.endBlock();

  // Test related to pull request #971 & #972
  typedef Labels<32, DGtal::uint32_t> MySmallLabels;
  typedef MySmallLabels::ConstIterator SmallLabelsConstIterator;
  typedef std::bitset<32> MySmallBitset;
  
  trace.beginBlock ( "Testing one word long Labels" );
  MySmallLabels ll;
  MySmallBitset vv;

  ++nb; nbok += isEqual( vv, ll ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") small_l=" << ll << std::endl; 

  insert( vv, ll, 15 );
  insert( vv, ll, 4 );
  insert( vv, ll, 31 );
  ++nb; nbok += isEqual( vv, ll ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") small_l=" << ll << std::endl; 

  erase( vv, ll, 15 );
  ++nb; nbok += isEqual( vv, ll ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") small_l=" << ll << std::endl; 
  
  // Check insertion at index 0
  insert( vv, ll, 0 );
  ++nb; nbok += isEqual( vv, ll ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") small_l=" << ll << std::endl; 

  // Check bit count computation
  ++nb; nbok += ll.count() == 3 ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") small_l.count()=" << ll.count() << std::endl;

  // Compare with size computed with iterators
  unsigned int cnt = 0;
  for ( SmallLabelsConstIterator it = ll.begin(), it_end = ll.end(); it != it_end; ++cnt, ++it) {}
  ++nb; nbok += cnt == 3 ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") small_l bit count with iterators=" << cnt << std::endl;
  
  trace.endBlock();

  return ( nb == nbok ) ? 0 : 1;
}
/** @ingroup Tests **/
