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
 * @file testInHalfPlane.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/22
 *
 * Functions for testing models of COrientationFunctor2.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"

#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"

#include "DGtal/geometry/tools/determinant/COrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBy2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"

#include "DGtal/geometry/tools/determinant/InGeneralizedDiskOfGivenRadius.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class InHalfPlane.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 * @param f any orientation functor
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor>
bool testInHalfPlane(OrientationFunctor f)
{
  BOOST_CONCEPT_ASSERT(( concepts::COrientationFunctor2<OrientationFunctor> )); 

  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );
  trace.info() << f << endl; 

  typedef typename OrientationFunctor::Value Value; 
  typedef typename OrientationFunctor::Point Point; 
  Point a(0,0); 
  Point b(5,2);
 
  //first quadrant
  f.init(a, b); 
  if (f( Point(2,1) ) == NumberTraits<Value>::ONE)
    nbok++;   //a, b, (2,1) are CCW oriented
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (f( Point(3,1) ) == -NumberTraits<Value>::ONE)
    nbok++;   //a, b, (3,1) are CW oriented
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (f( Point(10,4) ) == NumberTraits<Value>::ZERO)
    nbok++;   //a, b, (10,4) belong to the same line
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();
  
  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 */
bool testInGeneralizedDiskOfGivenRadius()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef PointVector<2, DGtal::int16_t> Point; 
  typedef AvnaimEtAl2x2DetSignComputer<DGtal::int64_t> DetComputer; 
  typedef InGeneralizedDiskOfGivenRadius<Point, DetComputer> Functor; 
  BOOST_CONCEPT_ASSERT(( concepts::COrientationFunctor2<Functor> )); 
  typedef Functor::Value Value; 

  Value res; 

  trace.beginBlock ( "Infinite radius..." );

  Functor f_inf; //infinite radius by default 
  trace.info() << f_inf << " " << f_inf.isValid() << endl; 

  f_inf.init( Point(0,0), Point(5,2) );
  res = f_inf( Point(7,3) ); 
  trace.info() << res << " > 0 " << std::endl; 
  if ( res > NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  f_inf.init( Point(0,0), Point(5,2) );
  res = f_inf( Point(8,3) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  f_inf.init( Point(0,0), Point(5,2) );
  res = f_inf( Point(10,4) ); 
  trace.info() << res << " == 0 " << std::endl; 
  if ( res == NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  Functor f_inf2(false); //infinite radius too, but with another orientation 
  trace.info() << f_inf2 << " " << f_inf2.isValid() << endl; 

  f_inf2.init( Point(0,0), Point(5,2) );
  res = f_inf2( Point(7,3) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  f_inf2.init( Point(0,0), Point(5,2) );
  res = f_inf2( Point(8,3) ); 
  trace.info() << res << " > 0 " << std::endl; 
  if ( res > NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  f_inf2.init( Point(0,0), Point(5,2) );
  res = f_inf2( Point(10,4) ); 
  trace.info() << res << " == 0 " << std::endl; 
  if ( res == NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();

  trace.beginBlock ( "Finite radius..." );

  Functor f5(true, 25, 1); //radius 5 with positive orientation 
  trace.info() << f5 << " " << f5.isValid() << endl; 

  f5.init( Point(5,0), Point(0,5) );
  res = f5( Point(-4,1) ); 
  trace.info() << res << " > 0 " << std::endl; 
  if ( res > NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f5( Point(-5,1) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f5( Point(-3,4) ); 
  trace.info() << res << " == 0 " << std::endl; 
  if ( res == NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f5( Point(-1,6) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f5( Point(-1,7) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  Functor f52(false, 25, 1); //radius 5 with negative orientation 
  trace.info() << f52 << " " << f52.isValid() << endl; 

  f52.init( Point(-5,0), Point(0,5) );
  res = f52( Point(4,1) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f52( Point(3,1) ); 
  trace.info() << res << " < 0 " << std::endl; 
  if ( res < NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f52( Point(5,1) ); 
  trace.info() << res << " > 0 " << std::endl; 
  if ( res > NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f52( Point(3,4) ); 
  trace.info() << res << " == 0 " << std::endl; 
  if ( res == NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f52( Point(4,3) ); 
  trace.info() << res << " == 0 " << std::endl; 
  if ( res == NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f52( Point(1,6) ); 
  trace.info() << res << " > 0 " << std::endl; 
  if ( res > NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  res = f52( Point(1,7) ); 
  trace.info() << res << " > 0 " << std::endl; 
  if ( res > NumberTraits<Value>::ZERO )
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();

  
  return nbok == nb;
}
///////////////////////////////////////////////////////////////////////////////
// Standard services - public :
int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class InHalfPlane" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  typedef PointVector<2, DGtal::int16_t> Point; 

  bool res = true; 

  typedef Simple2x2DetComputer<DGtal::int32_t, DGtal::int64_t> DetComputer; 
  typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> Functor1; 
  res = res && testInHalfPlane( Functor1() );
 
  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int32_t> Functor2; 
  res = res && testInHalfPlane( Functor2() );

  res = res && testInGeneralizedDiskOfGivenRadius(); 

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
