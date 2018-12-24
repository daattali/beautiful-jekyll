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
 * @file testCirculator.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/07/05
 *
 * Functions for testing class Circulator.h.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <list>
#include <forward_list>

#include "DGtal/base/Common.h"
#include "DGtal/base/Circulator.h"
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace DGtal;


///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Circulator.
///////////////////////////////////////////////////////////////////////////////

/**
 * Iteration accross the end of a range
 */
template<typename Iterator>
bool testOffset(const Iterator& itb, const Iterator& ite, const vector<int>& groundTruth)
{

  BOOST_CONCEPT_ASSERT(( boost::BidirectionalIterator<Iterator> ));
  BOOST_CONCEPT_ASSERT(( boost::BidirectionalIterator< Circulator<Iterator> > ));

  //list
  copy(itb,ite,ostream_iterator<int>(trace.info(), " ")); 
  trace.info() << " => ";

  //use of Circulators
  vector<int> v; 
  Circulator<Iterator> cb( itb, itb, ite );
  Circulator<Iterator> c( ++cb );
  do {
    v.push_back(*c);
    c++;
  } while (c != cb);

  //offset list
  copy(v.begin(),v.end(),ostream_iterator<int>(trace.info(), " ")); 

  //ground truth
  trace.info() << " ( == ";
  copy(groundTruth.begin(),groundTruth.end(),ostream_iterator<int>(trace.info(), " ")); 
  trace.info() << ")" << std::endl;

  return equal( v.begin(),v.end(),groundTruth.begin() );
}

/**
 * Test of basic operators required for forward circulators
 * @param cont any container
 * @tparam Container model of iterable and pushable container
 */
template<typename Container>
bool basicForwardTest(const Container& cont)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Operators of forward circulator" );
  typedef typename Container::const_iterator I;

  //default construction
  Circulator<I> circ0;
  if ( !(circ0.isValid()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //construction 
  Circulator<I> circ1(cont.begin(), cont.begin(), cont.end());
  if ( circ1.isValid() )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //copy 
  Circulator<I> circ2 = circ1; 
  //assignement
  circ0 = circ1;
  //pre/post-incrementation 
  circ1++; 
  ++circ2;   
  //equality
  if ( (circ0 != circ1) && (circ0 != circ2) && (circ1 == circ2) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //base, begin, end
  if ( (circ0.base() != circ1.base()) 
       && (circ0.base() != circ2.base()) 
       && (circ1.base() == circ2.base()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( (circ0.begin() == circ1.begin()) 
       && (circ0.end() == circ1.end()) 
       && (circ1.begin() == circ2.begin()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //operator *, ->
  if ( (*circ1 == *circ2) && (circ1.operator->() == &(*circ1)) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();
  
  return (nbok == nb);
}

/**
 * Test of basic operators required for bidirectional circulators
 * @param cont any container
 * @tparam Container model of iterable and pushable container
 */
template<typename Container>
bool basicBidirectionalTest(const Container& cont)
{
  ASSERT( cont.size() >= 1 ); 
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Operators of bidirectional circulator" );
  typedef typename Container::const_iterator I;

  //construction/copy 
  Circulator<I> res(cont.begin(), cont.begin(), cont.end());
  Circulator<I> circ1(cont.begin(), cont.begin(), cont.end());
  Circulator<I> circ2 = circ1; 
  //pre/post-incrementation 
  circ1++; 
  ++circ2;   
  if (circ1 == circ2)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  //pre/post-decrementation 
  circ1--; 
  --circ2;   
  if ( (circ1 == circ2) && (circ1 == res) && (circ2 == res) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();
  
  return (nbok == nb);
}

/**
 * Test of basic operators required for random access circulators
 * @param cont any container
 * @tparam Container model of iterable and pushable container
 */
template<typename Container>
bool basicRandomAccessTest(const Container& cont)
{
  ASSERT( cont.size() == 5 ); 

  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Operators of random access circulator" );
  typedef typename Container::const_iterator I;

  //construction/copy 
  Circulator<I> circ1(cont.begin(), cont.begin(), cont.end());
  Circulator<I> circ2 = circ1; 

  trace.info() << "arithmetic operators" << std::endl;
  circ2 += 4;
  if ( (circ2) == (circ1+4) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  circ2 -= 5;
  circ2++;   
  if ( circ1 == circ2 )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  if ( (circ1+3) == (3+circ1) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  circ2 += 7; 
  if ( (circ1+2) == circ2 )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  if ( ((circ1-circ2) + (circ2-circ1)) == (cont.end()-cont.begin()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.info() << "comparison operators" << std::endl;
  if ( (circ1 < circ2) && (circ1 <= circ2) 
       && (circ2 < circ1) && (circ2 <= circ1) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  if ( !( (circ1 > circ2) && (circ1 >= circ2) 
	  && (circ2 > circ1) && (circ2 >= circ1) ) )
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
  trace.beginBlock ( "Testing class Circulator" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.push_back(4);
  v.push_back(5);

  vector<int> v2;
  v2.push_back(2);
  v2.push_back(3);
  v2.push_back(4);
  v2.push_back(5);
  v2.push_back(1);

  vector<int> v3;
  v3.push_back(4);
  v3.push_back(3);
  v3.push_back(2);
  v3.push_back(1);
  v3.push_back(5);

  //incrementation
  trace.beginBlock ( "Iteration" );
  bool res = testOffset(v.begin(),v.end(), v2)
  && testOffset(v.rbegin(),v.rend(), v3)
  && testOffset(v.begin(),v.end(), v2)
  && testOffset(v.rbegin(),v.rend(), v3);
  trace.endBlock();

  //comparisons
  trace.beginBlock ( "Comparison" );
  trace.info() << "(const / not const)" << endl;
  Circulator<vector<int>::iterator> c1( v.begin(), v.begin(), v.end() );
  Circulator<vector<int>::iterator> c2( c1 );
  Circulator<vector<int>::const_iterator> c3( c2 );
  res = res && (c1 == c2) && (c1 == c3);

  trace.info() << "(reverse_iterator<Circulator> / Circulator<reverse_iterator>)" << endl;
  std::reverse_iterator<Circulator<vector<int>::iterator> > rc1( c1 );
  Circulator <vector<int>::reverse_iterator> c4(  v.rend(), v.rbegin(), v.rend() );
  res = res && (rc1.base().base() == c4.base().base());
  trace.info() << "first element: (" << *--rc1 << " == " << *--c4 << ")" << endl;
  res = res && ((*rc1) == (*c4));
  trace.endBlock();

  std::forward_list<int> fl;
  fl.push_front(1);
  fl.push_front(2);
  fl.push_front(3);
  fl.push_front(4);
  fl.push_front(5);
  
  std::list<int> bl; 
  bl.push_back(1);
  bl.push_back(2);
  bl.push_back(3);
  bl.push_back(4);
  bl.push_back(5);

  res = res && 
    basicForwardTest(fl) && 
    basicForwardTest(bl) && 
    basicForwardTest(v) &&
    basicBidirectionalTest(bl) && 
    basicBidirectionalTest(v) &&
    basicRandomAccessTest(v);

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
