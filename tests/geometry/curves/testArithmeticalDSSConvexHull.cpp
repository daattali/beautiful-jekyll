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
 * @file testArithmeticalDSSConvexHull.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/02/11
 *
 * Functions for testing class ArithmeticalDSSConvexHull.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/ArithmeticalDSL.h"
#include "DGtal/geometry/curves/ArithmeticalDSSConvexHull.h"
#include "DGtal/geometry/curves/ArithmeticalDSS.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/arithmetic/LatticePolytope2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace functions; 

///////////////////////////////////////////////////////////////////////////////
// Functions for testing functions smartCH and reversedSmartCH.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// smartCH
/**
 * Applies smartCH on a segment starting from (0,0)
 * and contained in a given arithmetical DSL
 * @param aDSL any DSL
 * @return 'true' if the algorithm returns correct values, 'false' otherwise
 * @tparam DSL an arithmeticalDSS type (either naive or standard)
 */
template <typename DSL>
bool basicTest(const DSL& aDSL)
{ 
  typedef typename DSL::Point Point; 
  typedef typename DSL::Vector Vector; 
  typedef typename DSL::Integer Integer; 
  typedef typename DSL::Position Position; 
  
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "One simple test..." );

  trace.info() << aDSL << std::endl; 

  //forward test
  Position l = (2*aDSL.patternLength()); 
  std::vector<Point> lch, uch; 
  Vector v = smartCH( aDSL, Point(0,0), l,
		      std::back_inserter(uch), std::back_inserter(lch) );

  if (v == Vector(aDSL.b(),aDSL.a())) //eq. 7
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;
  if ( aDSL.remainder(lch.back()) == aDSL.mu()-1 ) //eq. 8
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl; //eq. 8
  if ( aDSL.remainder(uch.back()) == aDSL.mu() )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  //test on the size of the convex hulls
  double bound = NumberTraits<Integer>::castToDouble(aDSL.patternLength()); 
  unsigned int threshold = (unsigned int) std::ceil( std::log(bound) / std::log(1.618) );
  if ( (lch.size()+uch.size()-1) <= threshold )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();

  return (nbok == nb);  
}

/**
 * Applies smartCH on a segment starting from (0,0)
 * and contained in a naive DSL of slope @a a, @a b with 
 * various intercepts
 * @param a numerator of the slope
 * @param b denominator of the slope
 * @return 'true' if the tests passed, 'false' otherwise
 * @tparam DSL an arithmeticalDSL type (either naive or standard)
 */
template <typename DSL>
bool basicTest(typename DSL::Coordinate a, 
	       typename DSL::Coordinate b)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  DSL aDSL(a,b,0); 
  for (typename DSL::Integer mu = 0; ( (-mu < aDSL.omega())&&(nbok == nb) ); --mu)
    {
      if (basicTest(DSL(a,b,mu)))
	nbok++; 
      nb++; 
    }

  return (nbok == nb);    
}

/**
 * Testing function.
 */
bool testWithoutLengthConstraint()
{
  trace.beginBlock ( "Testing block (without length constraint)..." );

  bool res = true; 
  res = res 
    && basicTest<NaiveDSL<DGtal::int32_t> >(5,8)
    && basicTest<NaiveDSL<DGtal::int32_t> >(8,13)
    && basicTest<NaiveDSL<DGtal::int32_t> >(12,29)
    && basicTest<NaiveDSL<DGtal::int32_t> >(29,70)
    && basicTest<NaiveDSL<DGtal::int32_t> >(70,29)
    && basicTest<NaiveDSL<DGtal::int32_t> >(-29,70)
    && basicTest<NaiveDSL<DGtal::int32_t> >(-70,29)
    && basicTest<NaiveDSL<DGtal::int32_t> >(29,-70)
    && basicTest<NaiveDSL<DGtal::int32_t> >(70,-29)
    && basicTest<NaiveDSL<DGtal::int32_t> >(-29,-70)
    && basicTest<NaiveDSL<DGtal::int32_t> >(-70,-29)

    && basicTest<StandardDSL<DGtal::int32_t> >(5,8)
    && basicTest<StandardDSL<DGtal::int32_t> >(8,13)
    && basicTest<StandardDSL<DGtal::int32_t> >(12,29)
    && basicTest<StandardDSL<DGtal::int32_t> >(29,70)
    && basicTest<StandardDSL<DGtal::int32_t> >(70,29)
    && basicTest<StandardDSL<DGtal::int32_t> >(-29,70)
    && basicTest<StandardDSL<DGtal::int32_t> >(-70,29)
    && basicTest<StandardDSL<DGtal::int32_t> >(29,-70)
    && basicTest<StandardDSL<DGtal::int32_t> >(70,-29)
    && basicTest<StandardDSL<DGtal::int32_t> >(-29,-70)
    && basicTest<StandardDSL<DGtal::int32_t> >(-70,-29)


    && basicTest<NaiveDSL<DGtal::int32_t> >(33, 109)
    && basicTest<NaiveDSL<DGtal::int32_t> >(109, 360)
    && basicTest<NaiveDSL<DGtal::int32_t> >(8, 73)
    && basicTest<NaiveDSL<DGtal::int32_t,DGtal::int64_t> >(30, 43)
#ifdef WITH_BIGINTEGER
    && basicTest<NaiveDSL<DGtal::int32_t,DGtal::BigInteger> >(57, 520)
    && basicTest<NaiveDSL<DGtal::BigInteger,DGtal::BigInteger> >(157, 225)
#endif

    ; 

  trace.endBlock();

  return res; 
}


/**
 * Compares smartCH to the algorithm of Charrier and Buzer, 
 * implemented in LatticePolytope2D. 
 * @param a (positive) numerator of the slope
 * @param b (positive) denominator of the slope
 * @pre b is greater than a, which is greater than 0. 
 * @return 'true' if the two algorithms return the same results, 
 * 'false' otherwise
 * @tparam DSL an arithmeticalDSL type (either naive or standard)
 */
template <typename DSL>
bool comparisonLeftHull(typename DSL::Coordinate a, typename DSL::Coordinate b)
{
  ASSERT(a >= 0); 
  ASSERT(b >= 0); 
  ASSERT(a < b); 

  typedef typename DSL::Point Point; 
  typedef typename DSL::Vector Vector; 
  typedef typename DSL::Coordinate Coordinate; 

  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Comparison ..." );
  DSL inputDSL(a,b,0); 

  trace.info() << a << " " << b << std::endl; 
  trace.info() << "testing every mu between 0 and -" << inputDSL.omega() << std::endl; 

  for (typename DSL::Integer mu = 0; ( (mu-1 >= -inputDSL.omega())&&(nbok == nb) ); --mu)
    {
      trace.info() << "mu=" << mu << ", testing every length between 1 and 2*" << inputDSL.omega() << std::endl; 
      inputDSL = DSL(a,b,mu); 

      for (typename DSL::Position l = 1; ( (l <= 2*inputDSL.patternLength())&&(nbok == nb) ); ++l)
	{
	  //trace.info() << "l=" << l << std::endl; 

	  //smartCH
	  std::vector<Point> lch, uch; 
	  Vector v = smartCH( inputDSL, Point(0,0), l,
			      std::back_inserter(uch), std::back_inserter(lch) );

	  // std::copy( lch.begin(), lch.end(), std::ostream_iterator<Point>(std::cout, " ") ); 
	  // std::cout << std::endl; 
	  // std::copy( uch.begin(), uch.end(), std::ostream_iterator<Point>(std::cout, " ") ); 
	  // std::cout << std::endl; 

	  Vector shift = -inputDSL.shift(); 
	  //algorithm of Charrier and Buzer 
	  typedef SpaceND<2, Coordinate> Space2; 
	  typedef LatticePolytope2D<Space2> CIP; 
	  CIP cip; 
	  typename CIP::HalfSpace line( typename CIP::Vector(a,-b), mu ); 
	  typename CIP::HalfSpace line2( typename CIP::Vector(a,-b), mu-1 ); 
	  //NB: since only closed half-space are used, 
	  // we must run the procedure twice, for mu and mu-1
	  // in order to get the lower left hull (not included)
	  // and the upper left hull (included)
	  typename CIP::HalfSpace constraint( typename CIP::Vector(shift[1],-shift[0]), l ); 
	  std::vector<typename CIP::Point> inch, outch, inch2, outch2; 
	  inch.push_back( typename CIP::Point(shift[0],shift[1]) ); 
	  inch2.push_back( typename CIP::Point(shift[0],shift[1]) ); 
	  ASSERT( line(inch[0]) ); 
	  ASSERT( constraint(inch[0]) ); 
	  outch.push_back( typename CIP::Point(0,0) ); 
	  outch2.push_back( typename CIP::Point(0,0) ); 
	  ASSERT( (!line2(outch[0])) ); 
	  ASSERT( constraint(outch[0]) ); 
	  typename CIP::Vector vBezout(1,0); 
	  cip.getAllPointsOfHull(inch, outch, vBezout, line, constraint); 
	  cip.getAllPointsOfHull(inch2, outch2, vBezout, line2, constraint); 

	  // std::copy( inch2.begin(), inch2.end(), std::ostream_iterator<typename CIP::Point>(std::cout, " ") ); 
	  // std::cout << std::endl; 
	  // std::copy( outch.begin(), outch.end(), std::ostream_iterator<typename CIP::Point>(std::cout, " ") ); 
	  // std::cout << std::endl; 

	  //comparisons
	  std::unique(inch2.begin(), inch2.end()); 
	  if (std::equal(lch.begin(), lch.end(), inch2.begin()))
	    nbok++; 
	  nb++; 

	  std::unique(outch.begin(), outch.end()); 
	  if (std::equal(uch.begin(), uch.end(), outch.begin()))
	    nbok++; 
	  nb++;
 
	}
    }

  trace.endBlock();

  return (nbok == nb);    
}

/**
 * Testing function.
 */
bool testWithLengthConstraint()
{
  trace.beginBlock ( "Testing block (with length constraint)..." );

  bool res = true; 
  res = res 
    && comparisonLeftHull<NaiveDSL<DGtal::int32_t> >(5,8)
    && comparisonLeftHull<NaiveDSL<DGtal::int32_t> >(8,13)
    && comparisonLeftHull<NaiveDSL<DGtal::int32_t> >(12,29)
    && comparisonLeftHull<NaiveDSL<DGtal::int32_t> >(29,70)

    && comparisonLeftHull<StandardDSL<DGtal::int32_t> >(5,8)
    && comparisonLeftHull<StandardDSL<DGtal::int32_t> >(8,13)
    && comparisonLeftHull<StandardDSL<DGtal::int32_t> >(12,29)
    && comparisonLeftHull<StandardDSL<DGtal::int32_t> >(29,70)
    ; 

  trace.endBlock();

  return res;    
}

/**
 * Computes the minimal parameters of a subsegment with smartCH
 * @param aDSL DSL containing the subsegment
 * @param x minimal position
 * @param y maximal position
 * @pre x != y
 * @return the computed DSL of minimal parameters
 * @tparam DSL an arithmetical DSL (either naive or standard)
 */
template <typename DSL>
DSL smartCHSubsegment(const DSL& aDSL, 
		      typename DSL::Position x, typename DSL::Position y)
{
  ASSERT((y-x) > 0); 

  typedef typename DSL::Point Point; 
  typedef typename DSL::Vector Vector;
  typedef typename DSL::Integer Integer; 
 
  Point startingPoint = aDSL.getPoint(x);  

  //running smartCH
  std::vector<Point> lch, uch; 
  Vector v = smartCH( aDSL, startingPoint, (y-x),
		      std::back_inserter(uch), std::back_inserter(lch) );

  //computing the slope and the remainder of the last upper leaning point 
  Point upperLeaningPoint = uch.back(); 
  Integer intercept = (static_cast<Integer>(upperLeaningPoint[0])*static_cast<Integer>(v[1])
		       -static_cast<Integer>(upperLeaningPoint[1])*static_cast<Integer>(v[0])); 

  // trace.info() << "(" << v[1] << ", " << v[0] << ", " << intercept  << ")" << std::endl; 
  return DSL( v[1],v[0],intercept ); 
}


/**
 * Computes the minimal parameters of a subsegment 
 * with the classical recognition algorithm, 
 * implemented in ArithmeticalDSS. 
 * @param aDSL DSL containing the subsegment
 * @param x minimal position
 * @param y maximal position
 * @pre x != y
 * @return the computed DSL of minimal parameters
 * @tparam DSL an arithmetical DSL (either naive or standard)
 */
template <typename DSL>
DSL trivialSubsegment(const DSL& aDSL, 
		      typename DSL::Position x, typename DSL::Position y)
{
  ASSERT((y-x) > 0); 

  typedef typename DSL::Point Point; 
  typedef typename DSL::Coordinate Coordinate; 
  typedef typename DSL::Integer Integer; 
  typedef typename DSL::ConstIterator ConstIterator; 
  typedef ArithmeticalDSS<Coordinate,Integer,DSL::foregroundAdjacency> DSS; 

  Point startingPoint = aDSL.getPoint(x); 
  ASSERT( aDSL(startingPoint) ); 
  Point endingPoint = aDSL.getPoint(y); 
  ASSERT( aDSL(endingPoint) ); 

  ConstIterator it = aDSL.begin(startingPoint); 
  ConstIterator ite = aDSL.end(endingPoint); 
  ASSERT (it != ite); 

  DSS dss = DSS(*it); 
  for (++it; (it != ite); ++it)
    {
      dss.extendFront(*it); 
    }

  //trace.info() << "(" << dss.a() << ", " << dss.b() << ", " << dss.mu() << ")" << std::endl; 
  return DSL(dss.a(), dss.b(), dss.mu());  
}


/**
 * Compares smartCH to the classical incremental recognition algorithm for 
 * one subgement of a given DSL
 * @param aDSL DSL containing the subsegment
 * @param x minimal position
 * @param y maximal position
 * @return 'true' if results match, 'false' otherwise
 * @tparam DSL an arithmetical DSL (either naive or standard)
 */
template <typename DSL>
bool comparisonSubsegment(const DSL& aDSL, 
			  typename DSL::Position x, typename DSL::Position y)
{
  DSL dsl1 = smartCHSubsegment(aDSL, x, y); 
  DSL dsl2 = trivialSubsegment(aDSL, x, y); 

  return (dsl1 == dsl2); 
}

/**
 * Compares smartCH to the classical incremental recognition algorithm
 * for various intercepts and lengths
 * @param a numerator of the slope
 * @param b denominator of the slope
 * @return 'true' if the two algorithms return the same results, 
 * 'false' otherwise
 * @tparam DSL an arithmetical DSL (either naive or standard)
 */
template <typename DSL>
bool comparisonSubsegment(typename DSL::Coordinate a, typename DSL::Coordinate b)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Subsegment comparison ..." );

  DSL aDSL(a, b, 0); 
  for (typename DSL::Integer mu = 0; ( (mu-1 >= -aDSL.omega())&&(nbok == nb) ); --mu)
    {
      //trace.info() << "mu=" << mu << std::endl; 
     
      typename DSL::Position f = -aDSL.patternLength(); 
      for (typename DSL::Position l = 1; ( (l <= 2*aDSL.patternLength())&&(nbok == nb) ); ++l)
	{
	  //trace.info() << "f=" << f << " l=" << l << std::endl; 
	    
	  if (comparisonSubsegment(DSL(a, b, mu), f, f+l))
	    nbok++;
	  nb++; 
	}
      
    }
  
  trace.endBlock(); 
  
  return (nb == nbok); 
}

/**
 * Testing function.
 */
bool testSubsegment()
{
  trace.beginBlock ( "Testing block for the subsegment problem..." );

  bool res = true; 
  res = res 
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(5,8)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(8,13)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(12,29)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(29,70)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(8,5)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(-5,8)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(-8,5)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(5,-8)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(8,-5)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(-5,-8)
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t> >(-8,-5)

    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(5,8)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(8,13)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(12,29)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(29,70)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(8,5)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(-5,8)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(-8,5)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(5,-8)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(8,-5)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(-5,-8)
    && comparisonSubsegment<StandardDSL<DGtal::int32_t> >(-8,-5)

#ifdef WITH_BIGINTEGER
    && comparisonSubsegment<NaiveDSL<DGtal::int32_t,DGtal::BigInteger> >(5,8)
    && comparisonSubsegment<NaiveDSL<DGtal::BigInteger,DGtal::BigInteger> >(5,8)
#endif
    ; 

  trace.endBlock();

  return res;    
}

///////////////////////////////////////////////////////////////////////////////
// reversedSmartCH
/**
 * Applies reversedSmartCH on a segment starting from (0,0)
 * and contained in a given arithmetical DSL
 * @param aDSL any DSL
 * @return 'true' if the algorithm returns correct values, 'false' otherwise
 * @tparam DSL an arithmeticalDSL type (either naive or standard)
 */
template <typename DSL>
bool basicTest2(const DSL& aDSL)
{ 
  typedef typename DSL::Point Point; 
  typedef typename DSL::Vector Vector; 
  typedef typename DSL::Coordinate Coordinate; 
  typedef typename DSL::Integer Integer; 
  typedef typename DSL::Position Position; 
  
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "One simple test..." );

  //bounding DSS
  typedef ArithmeticalDSS<Coordinate, Integer, DSL::foregroundAdjacency> DSS;
  Point A(0,0); 
  Position l = (2*aDSL.patternLength());
  Point B = aDSL.getPoint( aDSL.position(A) + l + 1 ); 
  DSS dss(aDSL.begin(A), aDSL.begin(B) ); 

  trace.info() << dss << std::endl; 

  //computation
  std::vector<Point> lch, uch; 
  Vector v = reversedSmartCH( dss, NumberTraits<Position>::ZERO,
			     std::back_inserter(uch), std::back_inserter(lch) );

  trace.info() << v << lch.back() << uch.back() << std::endl; 

  if ( (uch.back() == A) && (lch.back() == A - aDSL.shift()) )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl; 

  Vector LU = lch.back() - uch.back(); 
  if ( (v[0]*LU[1] - v[1]*LU[0]) == NumberTraits<Coordinate>::ONE )
    nbok++; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();

  return (nbok == nb);  
}

/**
 * Applies reversedSmartCH on a segment starting from (0,0)
 * and contained in a naive DSL of slope @a a, @a b with 
 * various intercepts
 * @param a numerator of the slope
 * @param b denominator of the slope
 * @return 'true' if the tests passed, 'false' otherwise
 * @tparam DSL an arithmeticalDSL type (either naive or standard)
 */
template <typename DSL>
bool basicTest2(typename DSL::Coordinate a, 
	       typename DSL::Coordinate b)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  DSL aDSL(a,b,0); 
  for (typename DSL::Integer mu = 0; ( (-mu < aDSL.omega())&&(nbok == nb) ); --mu)
    {
      if (basicTest2(DSL(a,b,mu)))
	nbok++; 
      nb++; 
    }

  return (nbok == nb);    
}

/**
 * Testing function.
 */
bool testWithoutLengthConstraint2()
{
  trace.beginBlock ( "Testing block (without length constraint)..." );

  bool res = true; 
  res = res 
    && basicTest2<NaiveDSL<DGtal::int32_t> >(5,8)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(8,13)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(12,29)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(29,70)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(70,29)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(-29,70)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(-70,29)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(29,-70)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(70,-29)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(-29,-70)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(-70,-29)

    && basicTest2<StandardDSL<DGtal::int32_t> >(5,8)
    && basicTest2<StandardDSL<DGtal::int32_t> >(8,13)
    && basicTest2<StandardDSL<DGtal::int32_t> >(12,29)
    && basicTest2<StandardDSL<DGtal::int32_t> >(29,70)
    && basicTest2<StandardDSL<DGtal::int32_t> >(70,29)
    && basicTest2<StandardDSL<DGtal::int32_t> >(-29,70)
    && basicTest2<StandardDSL<DGtal::int32_t> >(-70,29)
    && basicTest2<StandardDSL<DGtal::int32_t> >(29,-70)
    && basicTest2<StandardDSL<DGtal::int32_t> >(70,-29)
    && basicTest2<StandardDSL<DGtal::int32_t> >(-29,-70)
    && basicTest2<StandardDSL<DGtal::int32_t> >(-70,-29)


    && basicTest2<NaiveDSL<DGtal::int32_t> >(33, 109)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(109, 360)
    && basicTest2<NaiveDSL<DGtal::int32_t> >(8, 73)
    && basicTest2<NaiveDSL<DGtal::int32_t,DGtal::int64_t> >(30, 43)
#ifdef WITH_BIGINTEGER
    && basicTest2<NaiveDSL<DGtal::int32_t,DGtal::BigInteger> >(57, 520)
    && basicTest2<NaiveDSL<DGtal::BigInteger,DGtal::BigInteger> >(157, 225)
#endif

    ; 

  trace.endBlock();

  return res; 
}

/**
 * Computes the minimal parameters of a subsegment with reversedSmartCH
 * @param aDSS DSS containing the subsegment
 * @param aBound maximal position
 * @return the computed DSL of minimal parameters
 * @tparam DSS an arithmetical DSS (either naive or standard)
 */
template <typename DSS>
typename DSS::DSL reversedSmartCHSubsegment(const DSS& aDSS, 
					   typename DSS::Position aBound)
{
  ASSERT( (aBound - aDSS.position(aDSS.back())) > 0 ); 

  typedef typename DSS::Point Point; 
  typedef typename DSS::Vector Vector;
  typedef typename DSS::Integer Integer; 
  typedef typename DSS::DSL DSL; 
  
  Point startingPoint = aDSS.dsl().getPoint(aBound);  

  //running reversedSmartCH
  std::vector<Point> lch, uch; 
  Vector v = reversedSmartCH( aDSS, aBound,
			     std::back_inserter(uch), std::back_inserter(lch) );

  //computing the slope and the remainder of the last upper leaning point 
  Point upperLeaningPoint = uch.back(); 
  Integer intercept = (static_cast<Integer>(upperLeaningPoint[0])*static_cast<Integer>(v[1])
		       -static_cast<Integer>(upperLeaningPoint[1])*static_cast<Integer>(v[0])); 

  //trace.info() << "(" << v[1] << ", " << v[0] << ", " << intercept  << ")" << std::endl; 
  return DSL( v[1],v[0],intercept ); 
}

/**
 * Compares reversedSmartCH to the classical incremental recognition algorithm for 
 * one subgement of a greater DSS
 * @param aDSS DSS containing the subsegment
 * @param aBound maximal position
 * @return 'true' if results match, 'false' otherwise
 * @tparam DSS an arithmetical DSS (either naive or standard)
 */
template <typename DSS>
bool comparisonSubsegment2(const DSS& aDSS, typename DSS::Position aBound)
{
  typedef typename DSS::DSL DSL; 
  DSL dsl1 = reversedSmartCHSubsegment(aDSS, aBound); 
  DSL dsl2 = trivialSubsegment(aDSS.dsl(), aDSS.position(aDSS.back()), aBound); 

  return (dsl1 == dsl2); 
}



/**
 * Compares reversedSmartCH to the classical incremental recognition algorithm
 * for various intercepts and lengths
 * @param a numerator of the slope
 * @param b denominator of the slope
 * @return 'true' if the two algorithms return the same results, 
 * 'false' otherwise
 * @tparam DSL an arithmetical DSL (either naive or standard)
 */
template <typename DSL>
bool comparisonSubsegment2(typename DSL::Coordinate a, typename DSL::Coordinate b)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Subsegment comparison ..." );

  DSL aDSL(a, b, 0); 
  for (typename DSL::Integer mu = 0; ( (mu-1 >= -aDSL.omega())&&(nbok == nb) ); --mu)
    {
      trace.info() << "mu=" << mu << std::endl; 

      //computation of a bounding DSS
      typedef typename DSL::Point Point; 
      typedef typename DSL::Coordinate Coordinate; 
      typedef typename DSL::Integer Integer; 
      typedef ArithmeticalDSS<Coordinate,Integer,DSL::foregroundAdjacency> DSS; 

      Point startingPoint = aDSL.getPoint(0); 
      ASSERT( aDSL(startingPoint) ); 
      Point endingPoint = aDSL.getPoint(2*aDSL.patternLength()+1); 
      ASSERT( aDSL(endingPoint) ); 

      DSS dss = DSS(aDSL.begin(startingPoint), aDSL.begin(endingPoint)); 

      //test for a left subsegment
      for (typename DSL::Position l = 1; ( (l <= 2*aDSL.patternLength())&&(nbok == nb) ); ++l)
	{
	  trace.info() << "l=" << l << std::endl; 

	  if (comparisonSubsegment2(dss, l))
	    nbok++;
	  nb++; 
	}

    }

  trace.endBlock(); 

  return (nb == nbok); 
}

/**
 * Testing function.
 */
bool testSubsegment2()
{
  trace.beginBlock ( "Testing block for the subsegment problem..." );

  bool res = true; 
  res = res 
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(5,8)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(8,13)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(12,29)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(29,70)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(8,5)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(-5,8)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(-8,5)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(5,-8)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(8,-5)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(-5,-8)
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t> >(-8,-5)

    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(5,8)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(8,13)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(12,29)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(29,70)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(8,5)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(-5,8)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(-8,5)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(5,-8)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(8,-5)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(-5,-8)
    && comparisonSubsegment2<StandardDSL<DGtal::int32_t> >(-8,-5)

#ifdef WITH_BIGINTEGER
    && comparisonSubsegment2<NaiveDSL<DGtal::int32_t,DGtal::BigInteger> >(5,8)
    && comparisonSubsegment2<NaiveDSL<DGtal::BigInteger,DGtal::BigInteger> >(5,8)
#endif
    ; 

  trace.endBlock();

  return res;    
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :
int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ArithmeticalDSSConvexHull" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  if (argc >= 4)
    { //basic test with a specified DSL
      std::istringstream issb(argv[1]); 
      int b; 
      issb >> b; 
      std::istringstream issa(argv[2]); 
      int a; 
      issa >> a; 
      if ( (a <= 0)||(b <= 0) )
	{
	  std::cerr << " a and b should be strictly positive " << std::endl; 
	  return 1;
	} 
      std::istringstream issmu(argv[3]); 
      int mu; 
      issmu >> mu; 
      if ( (mu > 0)||(mu <= -(std::max(std::abs(a),std::abs(b)))) )
	{
	  std::cerr << " mu should be within the range ]-max(|a|,|b|); 0] " << std::endl; 
	  return 1;
	} 

      bool res = basicTest( NaiveDSL<DGtal::int32_t>(a,b,mu) ) 
	&& comparisonSubsegment( NaiveDSL<DGtal::int32_t>(a,b,mu),0,5 );
      trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
      return res ? 0 : 1;
    }

  //all automatic tests
  bool res = true; 
  res = res 
    && testWithoutLengthConstraint()
    && testWithLengthConstraint()
    && testSubsegment() 
    && testWithoutLengthConstraint2()
    && testSubsegment2()    
    ; 

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
