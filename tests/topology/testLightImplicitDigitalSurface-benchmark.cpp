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
 * @file testDigitalSurface.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/09/01
 *
 * Functions for testing class DigitalSurface.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/shapes/Shapes.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LightImplicitDigitalSurface.
///////////////////////////////////////////////////////////////////////////////
namespace DGtal {
  template <typename KSpace, typename PointPredicate>
  bool
  testLightImplicitDigitalSurface( const KSpace & K, 
                                   const PointPredicate & pp,
                                   const typename KSpace::Surfel & bel )
  {
    typedef LightImplicitDigitalSurface<KSpace,PointPredicate> Boundary;
    typedef typename Boundary::SurfelConstIterator ConstIterator;
    
    unsigned int nbok = 0;
    unsigned int nb = 0;
    trace.beginBlock ( "Testing block ... LightImplicitDigitalSurface" );
    trace.beginBlock ( "LightImplicitDigitalSurface instanciation" );
    Boundary boundary( K, pp,
                       SurfelAdjacency<KSpace::dimension>( true ), bel );
    trace.endBlock();
    trace.beginBlock ( "Counting the number of surfels (breadth first traversal)" );
    unsigned int nbsurfels = 0;
    for ( ConstIterator it = boundary.begin(), it_end = boundary.end();
          it != it_end; ++it )
      {
        ++nbsurfels;
      }
    trace.info() << nbsurfels << " surfels found." << std::endl;
    nb++, nbok += nbsurfels == 354382 ? 1 : 0;
    trace.info() << "(" << nbok << "/" << nb << ") "
                   << "nbsurfels == 354382" << std::endl;
    trace.endBlock();
    trace.endBlock();
    return nbok == nb;
  }
  

  template <typename TPoint3>
  struct ImplicitDigitalEllipse3 {
    typedef TPoint3 Point;
    inline
    ImplicitDigitalEllipse3( double a, double b, double c )
      : myA( a ), myB( b ), myC( c )
    {}
    inline
    bool operator()( const TPoint3 & p ) const
    {
      double x = ( (double) p[ 0 ] / myA );
      double y = ( (double) p[ 1 ] / myB );
      double z = ( (double) p[ 2 ] / myC );
    return ( x*x + y*y + z*z ) <= 1.0;
    }
    double myA, myB, myC;
  };
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int, char** )
{
  using namespace Z3i;
  typedef DGtal::ImplicitDigitalEllipse3<Point> ImplicitDigitalEllipse;
  typedef KSpace::SCell Surfel;
  bool res;
  trace.beginBlock ( "Testing class Object" );
  Point p1( -200, -200, -200 );
  Point p2( 200, 200, 200 );
  KSpace K;
  if ( K.init( p1, p2, true ) )
    {
      ImplicitDigitalEllipse ellipse( 180.0, 135.0, 102.0 );
      Surfel bel = Surfaces<KSpace>::findABel( K, ellipse, 10000 );
      res = testLightImplicitDigitalSurface<KSpace, ImplicitDigitalEllipse>
        ( K, ellipse, bel );
    }
  else
    res = false;
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
