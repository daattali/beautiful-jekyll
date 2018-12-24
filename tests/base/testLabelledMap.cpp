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
 * @file testLabelledMap.cpp
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
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/base/LabelledMap.h"

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
  c1.insert( std::make_pair(idx, v) );
  c2.insert( std::make_pair(idx, v) );
}

template <typename VContainer1, typename LContainer2>
bool
checkInsert( VContainer1 & v, LContainer2 & l,
	     unsigned int nb )
{
  for ( unsigned int i = 0; i < nb; ++i )
    {
      unsigned int idx = rand() % ( l.max_size() );
      double val = ( (double)rand() ) / RAND_MAX;
      insert( v, l, idx, val );
    }
  return isEqual( v, l );
}

template <typename VContainer1, typename LContainer2>
void erase( VContainer1 & c1, LContainer2 & c2, unsigned int idx )
{
  c1.erase( idx );
  c2.erase( idx );
}

template <typename VContainer1, typename LContainer2>
bool
checkErase( VContainer1 & v, LContainer2 & l,
	    unsigned int nb )
{
  for ( unsigned int i = 0; i < nb; ++i )
    {
      unsigned int idx = rand() % ( l.max_size() );
      erase( v, l, idx );
      //std::cout << "  (" << i << "/" << nb << ") l=" << l << std::endl; 
    }
  return isEqual( v, l );
}

template <typename AContainer>
void display( ostream & out, const AContainer & C )
{
  out << "C = ";
  for ( typename AContainer::const_iterator it = C.begin(), it_end = C.end();
        it != it_end; ++it )
    {
      out << " (" << (*it).first << "," << (*it).second << ")";
    }
  out << std::endl;
}
int main()
{
  typedef LabelledMap<double, 32, DGtal::uint16_t, 2, 7> MyLabelledMap;
  BOOST_CONCEPT_ASSERT(( boost::AssociativeContainer< MyLabelledMap > ));
  BOOST_CONCEPT_ASSERT(( boost::PairAssociativeContainer< MyLabelledMap > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< MyLabelledMap > ));
  // BOOST_CONCEPT_ASSERT(( boost::ForwardIterator< MyIndexedList::Iterator > ));
  // BOOST_CONCEPT_ASSERT(( boost::ForwardIterator< MyIndexedList::ConstIterator > ));
  unsigned int nb = 0;
  unsigned int nbok = 0;
  trace.beginBlock ( "Testing LabelledMap" );
  MyLabelledMap l;
  map<unsigned int, double> v;
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 3, 4.5 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 0, 10.1 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 1, 3.7 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 2, 8.4 );
  insert( v, l, 1, 2.1 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  display( std::cout, v );
  insert( v, l, 1, -3.0 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 15, -13.1 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  insert( v, l, 2, -7.1 );
  ++nb, nbok += isEqual( v, l ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  // MyLabelledMap::Iterator it = l.insert( l.begin(), std::make_pair( 7, 4.4 ) );
  // std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  // it = l.insert( it, std::make_pair( 9, 5.5 ) );
  // l.insert( it, std::make_pair( 9, 10.5 ) );
  // std::cout << "(" << nbok << "/" << nb << ") l=" << l << std::endl; 
  ++nb, nbok += checkInsert( v, l, 1000 ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") 1000 insertions l=" << l << std::endl; 
  ++nb, nbok += checkErase( v, l, 1000 ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") 1000 deletions l=" << l << std::endl; 
  trace.endBlock();
  trace.beginBlock ( "Testing LabelledMap" );
  ++nb, nbok += checkInsert( v, l, 10 ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") 10 deletions l=" << l << std::endl; 
  std::pair< MyLabelledMap::Iterator,
             MyLabelledMap::Iterator > pair1 = l.equal_range( 7 );
  std::cout << "Range(7)=[" << (*pair1.first).first << "," << (*pair1.second).first << ")" << std::endl;
  ++nb, nbok += ( pair1.first == l.lower_bound( 7 ) ) ? 1 : 0;
  ++nb, nbok += ( pair1.second == l.upper_bound( 7 ) ) ? 1 : 0;
  std::cout << "(" << nbok << "/" << nb << ") equal_range, lower_bound." << std::endl; 
  
  trace.endBlock();

  // Test related to pull request #973 about copy constructor & operator when using at less 3 blocks.
  typedef LabelledMap<double, 32, DGtal::uint16_t, 2, 3> MyOtherLabelledMap;
  trace.beginBlock ( "Testing LabelledMap copy constructor and copy operator" );
  MyOtherLabelledMap ll;

  for ( unsigned int size = 0; size <= 2 + 3 + 2; ++size )
    {
      for (unsigned int i = 0; i < size; ++i)
        ll[i] = i;
      
      MyOtherLabelledMap ll_ccopy(ll);
      MyOtherLabelledMap ll_ocopy; ll_ocopy = ll;

      for (unsigned int i = 0; i < size; ++i)
        ll[i] = 10*i+1;

      bool csuccess = true;
      bool osuccess = true;
      for (unsigned int i = 0; i < size; ++i)
        {
          csuccess &= ll_ccopy[i] == i;
          osuccess &= ll_ocopy[i] == i;
        }

      ++nb; nbok += csuccess ? 1 : 0;
      std::cout << "(" << nbok << "/" << nb << ") ll_copy_constructed=" << ll_ccopy << std::endl;
      
      ++nb; nbok += osuccess ? 1 : 0;
      std::cout << "(" << nbok << "/" << nb << ") ll_copied=" << ll_ocopy << std::endl;
    }

  trace.endBlock();

  return ( nb == nbok ) ? 0 : 1;
}
/** @ingroup Tests **/
