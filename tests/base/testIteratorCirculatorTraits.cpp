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
 * @file testIteratorCirculatorTraits.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/21
 *
 * Functions for testing class IteratorCirculatorTraits.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <list>
#include <vector>
#include <forward_list>

#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/ReverseIterator.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/ConstIteratorAdapter.h"
#include "DGtal/base/IteratorAdapter.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class IteratorCirculatorTraits.
///////////////////////////////////////////////////////////////////////////////

/**
 * Comparison between the type of (circular) iterator and T
 * @tparam IC iterator or circulator
 * @tparam T type to compare with (IteratorType or CircularType).
 */
template< typename IC, typename T> 
inline
bool compareType( IC, T ){
  return boost::is_same< 
    typename IteratorCirculatorTraits<IC>::Type, 
    T >::value; 
}

/**
 * Comparison between the category of (circular) iterator and T
 * @tparam IC iterator or circulator
 * @tparam T type to compare with (Forward-, Bidirectional- and RandomAccessCategory).
 */
template< typename IC, typename T> 
inline
bool compareCategory( IC, T ){
  return boost::is_same< 
    typename IteratorCirculatorTraits<IC>::Category, 
    T >::value; 
}

/**
 * Test of the IteratorCirculatorTraits class
 * (Type and Category).
 */
bool testIteratorCirculatorTraits()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing tags for various (circular) iterators..." );

  //forward list
  trace.info() << "forward list" << std::endl;
  std::forward_list<int> fl;
  if ( compareType( fl.begin(), IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( fl.begin(), ForwardCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  Circulator< std::forward_list<int>::iterator > cfl(fl.begin(), fl.begin(), fl.end()); 
  if ( compareType( cfl, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( cfl, ForwardCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  
  //list
  trace.info() << "list" << std::endl;
  std::list<int> bl;
  if ( compareType( bl.begin(), IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( bl.begin(), BidirectionalCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  Circulator< std::list<int>::iterator > cbl(bl.begin(), bl.begin(), bl.end()); 
  if ( compareType( cbl, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( cbl, BidirectionalCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  //vector
  trace.info() << "vector" << std::endl;
  std::vector<int> v; 
  if ( compareType( v.begin(), IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( v.begin(), RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  Circulator< std::vector<int>::iterator > cv(v.begin(), v.begin(), v.end()); 
  if ( compareType( cv, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( cv, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  //basic array
  trace.info() << "basic array" << std::endl;
  int t[5] = {1, 2, 3, 4, 5};
  if ( compareType( t, IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( t, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  Circulator< int* > ct(t+1, t, t+5); 
  if ( compareType( ct, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( ct, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();
  
  return (nbok == nb);
}

/**
 * Test of the IteratorCirculatorTraits class on adapters
 * (Type and Category).
 */
bool testIteratorCirculatorTraitsAndAdapters()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing tags for adapters (ReverseIterator, (Const)IteratorAdapter) " );

  int t[5] = {1, 2, 3, 4, 5};
  //reverse
  trace.info() << "ReverseIterator" << std::endl;
  typedef ReverseIterator< int* > RI; 
  RI rt(t+5); 
  if ( compareType( rt, IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( rt, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //const adapter
  trace.info() << "ConstIteratorAdapter" << std::endl;
  typedef ConstIteratorAdapter< int*, functors::Identity, int > IA1; 
  IA1 at1( t, functors::Identity() ); 
  if ( compareType( at1, IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( at1, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //adapter
  trace.info() << "IteratorAdapter" << std::endl;
  typedef IteratorAdapter< int*, functors::Identity, int > IA2; 
  IA2 at2( t, functors::Identity() ); 
  if ( compareType( at2, IteratorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( at2, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  //with circulators
  typedef Circulator< int* > CI; 

  //reverse circ, circ reverse,
  trace.info() << "ReverseIterator<Circulator> and Circulator<ReverseIterator>" << std::endl; 
  Circulator< RI > crt( rt, RI(t+5), RI(t) ); 
  if ( compareType( crt, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( crt, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  ReverseIterator< CI > rct( CI(t+5, t, t+5) ); 
  if ( compareType( rct, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( rct, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  //const iterator adapter circ, circ const iterator adapter
  trace.info() << "ConstIteratorAdapter of Circulator and Circulator of ConstIteratorAdapter" << std::endl; 
  Circulator< IA1 > cat1( at1, at1, IA1(t+5, functors::Identity()) ); 
  if ( compareType( cat1, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( cat1, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  ConstIteratorAdapter< CI, functors::Identity, int > a1ct( CI(t+5, t, t+5), functors::Identity() ); 
  if ( compareType( a1ct, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( a1ct, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  //iterator adapter circ, circ iterator adapter
  trace.info() << "IteratorAdapter of Circulator and Circulator of IteratorAdapter" << std::endl; 
  Circulator< IA2 > cat2( at2, at2, IA2(t+5, functors::Identity()) ); 
  if ( compareType( cat2, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( cat2, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  ConstIteratorAdapter< CI, functors::Identity, int > a2ct( CI(t+5, t, t+5), functors::Identity() ); 
  if ( compareType( a2ct, CirculatorType() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( compareCategory( a2ct, RandomAccessCategory() ) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();
  
  return (nbok == nb);
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class IteratorCirculatorTraits" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testIteratorCirculatorTraits() && testIteratorCirculatorTraitsAndAdapters();

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
