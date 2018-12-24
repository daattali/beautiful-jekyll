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
 * @file geometry/tools/determinant/exampleInHalfPlane.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/28
 *
 * An example file named exampleInHalfPlane.
 *
 * This file is part of the DGtal library.
 */

/**
  Example of geometric predicates.
  @see @ref moduleGeometricPredicates
  \example geometry/tools/determinant/exampleInHalfPlane.cpp
**/



///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"

#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/SimpleIncremental2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"
#include "DGtal/geometry/tools/determinant/Filtered2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBy2x2DetComputer.h"
//! [FunctorIncludes]
#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
//! [FunctorIncludes]
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

bool 
basicUsage()
{
  //! [DomainDefinition]
  //domain definition
  typedef SpaceND< 2, DGtal::int16_t > DigitalSpace;
  typedef HyperRectDomain< DigitalSpace > Domain; 
  typedef Domain::Point Point; 
  Domain domain( Point(-32767,-32767), Point(32767,32767) ); 
  //! [DomainDefinition]

  //! [ProblemStatement]
  Point P, Q, R; 
  P = Point(0,0); 
  Q = Point(5,2); 
  R = Point(2,1); 
  //problem: are P, Q, R counter-clockwise oriented ?
  //! [ProblemStatement]

  //! [FunctorDefinition]
  //orientation functor
  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int32_t> OrientationFunctor; 
  OrientationFunctor orientationFunctor;
  //! [FunctorDefinition]

  //! [PredicateDefinition]
  //geometric predicate
  PredicateFromOrientationFunctor2<OrientationFunctor> 
    pointPredicate( orientationFunctor ); 
  //! [PredicateDefinition]

  //! [FunctorInitialization]
  //initialization
  pointPredicate.init( P, Q ); 
  //which is equivalent to 
  //orientationFunctor.init( P, Q );
  //because the predicate stores a pointer to the functor
  //! [FunctorInitialization]

  bool isCCW; 
  //! [PredicateUsage]
  //decision
  isCCW = pointPredicate( R ); 
  //which is equivalent to the following shortcut:
  //isCCW = pointPredicate( P, Q, R ); 
  //! [PredicateUsage]

  return isCCW; 
}

void
advice()
{
  {
  //! [FunctorDefinition30]
  //for coordinates of 30 (not zero) bits
  typedef PointVector<2, DGtal::int32_t> Point; 
  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int64_t> Functor; 
  //! [FunctorDefinition30]
  Functor *a = new Functor();
  BOOST_VERIFY(a);
  }

  {
  //! [FunctorDefinition52]
  //for coordinates of 52 (not zero) bits
  typedef PointVector<2, DGtal::int64_t> Point;  
  typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
  typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
  typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> Functor; 
  //! [FunctorDefinition52]
  Functor *a = new Functor();
  BOOST_VERIFY(a);
  //NB. using double as coordinate type is slightly faster than using DGtal::int64_t
  //typedef PointVector<2, double> Point;  
  }

  {
  //! [FunctorDefinition62]
  //for coordinates of 62 (not zero) bits
  typedef PointVector<2, DGtal::int64_t> Point; 
  typedef AvnaimEtAl2x2DetSignComputer<DGtal::int64_t> DetComputer; 
  typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> Functor; 
  //! [FunctorDefinition62]
  Functor *a= new Functor();
  BOOST_VERIFY( a);
  }

  {
  //! [FunctorDefinition62bis]
  //for coordinates of 62 (not zero) bits
  //if long double is implemented as the 80-bit extended precision type
  typedef PointVector<2, DGtal::int64_t> Point;  
  typedef AvnaimEtAl2x2DetSignComputer<long double> DetComputer; 
  typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
  typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> Functor; 
  Functor *a = new Functor();
  BOOST_VERIFY(a == a);
  //! [FunctorDefinition62bis]
  }

#ifdef WITH_BIGINTEGER
  {
  //! [FunctorDefinition62plus]
  //for arbitrary coordinates
  typedef PointVector<2, DGtal::BigInteger> Point; 
  typedef Simple2x2DetComputer<DGtal::BigInteger> DetComputer; 
  typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> Functor; 
  Functor *a= new Functor();
  BOOST_VERIFY( a);
  //! [FunctorDefinition62plus]
  }
#endif

}

int main( int argc, char** argv )
{
  trace.beginBlock ( "Example exampleInHalfPlane" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  basicUsage(); 
  advice(); 

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
