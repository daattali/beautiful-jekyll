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
 * @file
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class COBAStandardPlaneComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/geometry/surfaces/CAdditivePrimitiveComputer.h"
#include "DGtal/geometry/surfaces/COBAGenericStandardPlaneComputer.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class COBAGenericStandardPlaneComputer.
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :
template <typename Integer>
Integer getRandomInteger( const Integer & first, const Integer & after_last )
{
  Integer r = (Integer) rand();
  return ( r % (after_last - first) ) + first;
}

template <typename Domain>
std::vector<typename Domain::Point> pointsInStandardPlane
( const Domain & domain,
  typename Domain::Integer a, 
  typename Domain::Integer b,
  typename Domain::Integer c,
  typename Domain::Integer mu )
{
  typedef typename Domain::Integer Integer;
  typedef typename Domain::Point Point;
  typedef typename Domain::ConstIterator ConstIterator;
  std::vector<Point> pts;
  Integer mup = mu + abs(a) + abs(b) + abs(c);
  for ( ConstIterator it = domain.begin(), itE = domain.end();
        it != itE; ++it )
    {
      Point p = *it;
      Integer r = a * p[ 0 ] + b * p[ 1 ] + c * p[ 2 ];
      if ( ( mu <= r ) && ( r < mup ) )
        pts.push_back( p );
    }
  return pts;
}

template <typename PlaneComputer >
bool checkCOBAGenericStandardPlaneComputer
( PlaneComputer & computer, unsigned int nbplanes, int diameter )
{
  typedef typename PlaneComputer::Space Space;
  typedef HyperRectDomain<Space> Domain;
  typedef typename Space::Integer Integer;
  typedef typename Space::Point Point;
  unsigned int nb = 0;
  unsigned int nbok = 0;
  Domain domain( Point( -diameter, -diameter, -diameter ),
                 Point(  diameter,  diameter,  diameter ) );
  Integer a, b, c, mu;
  for ( unsigned int p = 0; p < nbplanes; ++p )
    {
      do {
        a = getRandomInteger( -diameter, diameter+1 );
        b = getRandomInteger( -diameter, diameter+1 );
        c = getRandomInteger( -diameter, diameter+1 );
      }
      while ( ( a == 0 ) && ( b == 0 ) && ( c == 0 ) );
      mu = getRandomInteger( -diameter, diameter );
      std::vector<Point> pts = pointsInStandardPlane( domain, a, b, c, mu );
      computer.init( 2*diameter, 1, 1 );
      ++nb, nbok += computer.extend( pts.begin(), pts.end() ) ? 1 : 0;
      trace.info() << "Primitive=" << computer.primitive() << std::endl;
      trace.info() << "(" << nbok << "/" << nb << ") extend " 
                   << pts.size() << " points of plane " 
                   << mu << " <= " << a << "*x+" << b << "*y+" << c << "*z+"
                   << " < " << (mu+a+b+c) << std::endl;
      computer.init( 2*diameter, 1, 1 );
      std::random_shuffle( pts.begin(), pts.end() );
      ++nb, nbok += computer.extend( pts.begin(), pts.end() ) ? 1 : 0;
      trace.info() << "Primitive=" << computer.primitive() << std::endl;
      trace.info() << "(" << nbok << "/" << nb << ") extend " 
                   << pts.size() << " shuffled points of plane " 
                   << mu << " <= " << a << "*x+" << b << "*y+" << c << "*z+"
                   << " < " << (mu+a+b+c) << std::endl;
    }
  return nb == nbok;
}


int main( int /*argc*/, char** /*argv*/ )
{
  using namespace Z3i;

  typedef COBAGenericStandardPlaneComputer<Space, int64_t> PlaneComputer;
  
  bool ok;
  PlaneComputer plane;
  plane.init( 100, 1, 1 );
  ok = plane.extend( Point(0,0,0) );
  trace.info() << "Point(0,0,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(1,0,0) );
  trace.info() << "Point(1,0,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(0,1,0) );
  trace.info() << "Point(0,1,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(1,1,0) );
  trace.info() << "Point(1,1,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(2,0,0) );
  trace.info() << "Point(2,0,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(0,2,0) );
  trace.info() << "Point(0,2,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(0,2,0) );
  trace.info() << "Point(0,2,0) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  ok = plane.extend( Point(1,1,1) );
  trace.info() << "Point(1,1,1) is " << ( ok ? "ok" : "ko" ) << std::endl;
  trace.info() << plane << std::endl;
  checkCOBAGenericStandardPlaneComputer( plane, 5, 20 );

  return 0;
}
