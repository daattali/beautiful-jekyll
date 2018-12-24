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
 * @file testArithmeticalDSS.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/06/28
 *
 * Functions for testing class ArithmeticalDSS.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <boost/iterator/iterator_concepts.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/geometry/curves/ArithmeticalDSL.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ArithmeticalDSL.
///////////////////////////////////////////////////////////////////////////////
/**
 * Test of the main operators
 * @tparam DSL a model of arithmetical DSL, 
 * either naive or standard 
 */
template <typename DSL>
bool mainTest()
{
  BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate<DSL> ));
  
  typedef typename DSL::Point Point; 

  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Main operators..." );

  //operateur constructeur, copie, affectation
  trace.info() << "constructor, copy, assignement, equality" << std::endl; 

  DSL dsl(0, 1, 0); 
  DSL dsl2 = dsl; 
  DSL dsl3(1, 1, 0);
  DSL dsl4 = dsl3; 
  dsl3 = dsl2 = dsl; 

  //egalite, difference
  DSL dsl5(0, -1, 0); 
  
  if ( (dsl == dsl2)
       &&(dsl == dsl3)
       &&(dsl != dsl4)
       &&(dsl == dsl5) )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;

  //validite
  trace.info() << "valid dsl" << std::endl; 
  if ( dsl.isValid() && dsl3.isValid() && dsl5.isValid() ) 
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;

  DSL dsl6(0, 0, 1); 

  trace.info() << "not valid dsl" << std::endl; 
  if (!dsl6.isValid()) 
    nbok++; 
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;

  //accessors
  trace.info() << "a,b,mu,omega accessors" << std::endl; 

  if ( (dsl.a() == 0)&&(dsl.b() == 1)&&(dsl.mu() == 0)&&(dsl.omega() == 1) )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;


  DSL dsl7(5, 8, 0); 
  
  trace.info() << "remainder, position, tests" << std::endl; 
  trace.info() << dsl7 << std::endl; 

  if ( (dsl7.isValid()) 
       && (dsl7.remainder( Point(8,5) ) == 0)
       &&(dsl7.remainder( Point(16,10) ) == 0)
       &&(dsl7.remainder( Point(3,2) ) == -1)
       &&(dsl7.remainder( Point(5,3) ) == 1) )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;
 
  if ( (dsl7.orthogonalPosition( Point(0,0) ) == 0)
       &&(dsl7.orthogonalPosition( Point(8,5) ) == 89)
       &&(dsl7.orthogonalPosition( Point(1,0) ) == 8)
       &&(dsl7.orthogonalPosition( Point(-1,0) ) == -8) )
    nbok++; 
  nb++; 

  if ( ( dsl7.before( Point(0,0), Point(8,5) ) )
       &&(!dsl7.before( Point(8,5), Point(0,0) ) )
       &&( dsl7.beforeOrEqual( Point(0,0), Point(8,5) ) )
       &&(!dsl7.beforeOrEqual( Point(8,5), Point(0,0) ) )
       &&( dsl7.before( Point(-1,0), Point(1,0) ) )
       &&( !dsl7.before( Point(1,0), Point(-1,0) ) )
       &&( !dsl7.before( Point(8,5), Point(8,5) ) )
       &&( dsl7.beforeOrEqual( Point(8,5), Point(8,5) ) )
       )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;

  if ( (dsl7.isInDSL( Point(0,0) ))
       &&(dsl7.isInDSL( Point(16,10) ))
       &&(dsl7.isInDSL( Point(5,3) ))
       &&(!dsl7.isInDSL( Point(3,2) )) )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;

  if ( (dsl7( Point(0,0) ))
       &&(dsl7( Point(16,10) ))
       &&(dsl7( Point(5,3) ))
       &&(!dsl7( Point(3,2) ))
       &&(!dsl7( Point(-1,0) ))
       &&(dsl7( Point(-1,-1) )) )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;

  trace.info() << "shift" << std::endl; 
  if ( (dsl.remainder(dsl.shift()) == dsl.omega()) 
       && (DSL::toCoordinate(dsl.omega()) == dsl.patternLength()) )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;

  if ( (dsl7.getPoint() == Point(0,0)) 
       &&(DSL(5,8,dsl7.omega()-1).getPoint() == Point(0,0)+dsl.shift())
       &&(DSL(5,8,dsl7.omega()).getPoint() == Point(0,0)+dsl.shift())
       &&(DSL(5,8,dsl7.omega()+1).getPoint() == Point(0,0)+2*dsl.shift())
       &&(DSL(5,8,-dsl7.omega()+1).getPoint() == Point(0,0))
       &&(DSL(5,8,-dsl7.omega()).getPoint() == Point(0,0)-dsl.shift())
       &&(DSL(5,8,-dsl7.omega()-1).getPoint() == Point(0,0)-dsl.shift())
       )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;

            
  trace.endBlock();
  
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
/**
 * Test of the range services 
 * @param dsl an instance of DSL of null intercept
 * @pre mu, the lower bound, must be equal to zero
 * @tparam DSL a model of arithmetical DSL, 
 * either naive or standard 
 */
template <typename DSL>
bool rangeTest(const DSL& dsl)
{
  typedef typename DSL::Point Point; 

  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Range/Iterator services..." );
  trace.info() << dsl << std::endl; 

  Point origin = dsl.getPoint();
  Point first = Point(origin[0]-dsl.b(), origin[1]-dsl.a());
  Point last = Point(first[0]+dsl.b(), first[1]+dsl.a()); 
  trace.info() << "from " << first << " to " << last << std::endl; 

  if (dsl.isValid())
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
  	       << std::endl;

  {//forward pass  
    typedef typename DSL::ConstIterator I; 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<I> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::RandomAccessTraversalConcept<I> ));
    bool res = true; 
    int c = 0; 
    for (I it = dsl.begin(first), itEnd = dsl.end(last); 
	 ( (it != itEnd)&&(res)&&(c<100) ); 
	 ++it, ++c)
      {
	trace.info() << "(" << it->operator[](0) << "," << it->operator[](1) << ") ";  
	if ( !dsl(*it) )
	  res = false; 
      }
    trace.info() << " : " << c << " points " << std::endl; 
    trace.info() << std::endl; 

    if ( (res)&&(c == (dsl.omega()+1)) ) 
      nbok++; 
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") "
		 << std::endl;
  }

  {//backward pass
    typedef typename DSL::ConstReverseIterator I; 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<I> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::RandomAccessTraversalConcept<I> ));
    bool res = true; 
    int c = 0; 
    for (I it = dsl.rbegin(last), itEnd = dsl.rend(first); 
	 ( (it != itEnd)&&(res)&&(c<100) ); 
	 ++it, ++c)
      {
	trace.info() << "(" << it->operator[](0) << "," << it->operator[](1) << ") ";  
	if ( !dsl(*it) )
	  res = false; 
      }
    trace.info() << " : " << c << " points " << std::endl; 
    trace.info() << std::endl; 

    if ( (res)&&(c == (dsl.omega()+1)) ) 
      nbok++; 
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") "
		 << std::endl;
  }

  {//random access services  
    typedef typename DSL::ConstIterator I; 
    BOOST_CONCEPT_ASSERT(( boost_concepts::ReadableIteratorConcept<I> )); 
    BOOST_CONCEPT_ASSERT(( boost_concepts::RandomAccessTraversalConcept<I> ));
    bool res = true; 
    int c = 0; 
    I itBegin = dsl.begin(first); 
    for (I it = itBegin, itEnd = dsl.end(last); 
	 ( (it != itEnd)&&(res)&&(c<100) ); 
	 ++it, ++c)
      {
	trace.info() << "(" << it->operator[](0) << "," << it->operator[](1) << ") " << it.remainder() << ", ";  
	I it2 = ( itBegin + c ); 
	if ( (it != it2) || ((it2 - itBegin) != c) )
	  res = false; 
      }
    int n = c; 
    trace.info() << " : " << c << " points " << std::endl; 
    trace.info() << std::endl; 

    if (res) 
      nbok++; 
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") "
		 << std::endl;

    --n; 
    c = 0; 
    for (I it = (itBegin+n), itEnd = itBegin; 
	 ( (it!=itEnd)&&(res)&&(c < 100) );
	 --it, ++c )
      {
	trace.info() << "(" << it->operator[](0) << "," << it->operator[](1) << ") " << it.remainder() << ", ";  
	I it2 = ( (itBegin+n) - c ); 
	if ( (it != it2) || (((itBegin+n) - it2) != c) )
	  res = false; 
      }

    if (res) 
      nbok++; 
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") "
		 << std::endl;
  }


  trace.endBlock();
  
  return nbok == nb;
}



template <typename DSL>
bool sameOctantTest(const DSL& dsl1, const DSL& dsl2)
{
  trace.beginBlock ( "Test same octant" );
  trace.info() << dsl1  << " " << dsl2 << std::endl; 
  
  typename DSL::Octant::first_type oc;
  
  return dsl1.sameOctant(dsl2,&oc);

  trace.endBlock();


}


template <typename DSL>
typename DSL::Octant testOctant(const typename DSL::Coordinate & a, const typename DSL::Coordinate & b)
{
  
  DSL aDSL(a,b,0);
  trace.info() << aDSL << std::endl;
  
  return aDSL.octant();
  
}



///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ArithmeticalDSL" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  //main operators
  bool res = mainTest<DGtal::ArithmeticalDSL<DGtal::int32_t> >()
#ifdef WITH_BIGINTEGER
    && mainTest<DGtal::ArithmeticalDSL<DGtal::int32_t, DGtal::BigInteger, 4> >()
#endif
    && mainTest<DGtal::NaiveDSL<DGtal::int32_t> >()
    && mainTest<DGtal::StandardDSL<DGtal::int32_t> >()
    ; 

  {   //range services for 8 adjacency
    typedef DGtal::ArithmeticalDSL<DGtal::int32_t> DSL; 

    res = res 
      && rangeTest( DSL(5, 8, 16) )
      && rangeTest( DSL(8, 5, 14) )
      && rangeTest( DSL(5, -8, 14) )
      && rangeTest( DSL(8, -5, 14) )
      && rangeTest( DSL(-5, 8, 14) )
      && rangeTest( DSL(-8, 5, 14) )
      && rangeTest( DSL(-5, -8, 14) )
      && rangeTest( DSL(-8, -5, 14) )
      && rangeTest( DSL(1, 0, 14) )
      && rangeTest( DSL(0, -1, 14) )
      && rangeTest( DSL(0, 1, 14) )
      && rangeTest( DSL(-1, 0, 14) )
      && rangeTest( DSL(1, 1, 14) )
      && rangeTest( DSL(1, -1, 14) )
      && rangeTest( DSL(-1, 1, 14) )
      && rangeTest( DSL(-1, -1, 14) )
      ;
  }


  {  //range services for 4 adjacency
    typedef DGtal::ArithmeticalDSL<DGtal::int32_t, DGtal::int32_t, 4> DSL; 
    
    res = res 
      && rangeTest( DSL(5, 8, -16) )
      && rangeTest( DSL(8, 5, -17) )
      && rangeTest( DSL(5, -8, -17) )
      && rangeTest( DSL(8, -5, -17) )
      && rangeTest( DSL(-5, 8, -17) )
      && rangeTest( DSL(-8, 5, -17) )
      && rangeTest( DSL(-5, -8, -17) )
      && rangeTest( DSL(-8, -5, -17) )
      && rangeTest( DSL(1, 0, -17) )
      && rangeTest( DSL(0, -1, -17) )
      && rangeTest( DSL(0, 1, -17) )
      && rangeTest( DSL(-1, 0, -17) )
      ;
  }


  { // same octant test
    typedef DGtal::ArithmeticalDSL<DGtal::int32_t> DSL; 
   
    res = res 
      && sameOctantTest(DSL(5,8,16),DSL(1,2,3))==true 
      && sameOctantTest(DSL(5,8,16),DSL(2,1,3))==false
      && sameOctantTest(DSL(2,2,16),DSL(6,3,3))==true
      && sameOctantTest(DSL(2,2,16),DSL(3,3,3))==true
      && sameOctantTest(DSL(5,-8,16),DSL(0,-2,3))==true 
      && sameOctantTest(DSL(5,8,16),DSL(-2,1,3))==false
      ;
  }
  
  // ---------------- octant tests -------------------------
  
  {
  typedef ArithmeticalDSL<DGtal::int32_t, DGtal::int32_t, 8> DSL;
  typedef DSL::Octant Octant;
  
  trace.beginBlock("Test octant computation");
  
  res = res 
    && testOctant<DSL>(0,0) == Octant(-1,-1)
    && testOctant<DSL>(0,5) == Octant(0,7)
    && testOctant<DSL>(0,-5) == Octant(3,4)
    && testOctant<DSL>(5,0) == Octant(1,2)
    && testOctant<DSL>(-5,0) == Octant(5,6)
    && testOctant<DSL>(1,1) == Octant(0,1)
    && testOctant<DSL>(1,-1) == Octant(2,3)
    && testOctant<DSL>(-1,1) == Octant(6,7)
    && testOctant<DSL>(-1,-1) == Octant(4,5)
    ; 

  }

#ifdef WITH_BIGINTEGER
  {
    typedef DGtal::ArithmeticalDSL<DGtal::int32_t, DGtal::BigInteger, 4> DSL; 
    res = res && rangeTest( DSL(5, 8, -26) ) && rangeTest( DSL(5, 8, 13) )
      && rangeTest( DSL(5, 8, -17) ) && rangeTest( DSL(5, 8, 11313) ); 
  }
  // Warning: BOOST_CONCEPT_ASSERT(( boost_concepts::RandomAccessTraversalConcept<I> )); 
  // does not accept DGtal::BigInteger as a difference type for random access iterators
  // because it uses methods is_signed and is_integer of std::numeric_limits
  // { //does not compile 
  //   typedef DGtal::ArithmeticalDSL<DGtal::BigInteger, DGtal::BigInteger, 4> DSL; 
  //   res = res && rangeTest( DSL(5, 8, 123654) ); 
  // }
#endif

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
