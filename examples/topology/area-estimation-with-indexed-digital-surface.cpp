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
 * @file topology/area-estimation-with-indexed-digital-surface.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/08/28
 *
 * An example file named area-estimation-with-indexed-digital-surface.cpp.
 *
 * This file is part of the DGtal library.
 */

/** 
 * Computing the area of a sphere with an indexed digital
 * surface. First normals are estimated by averaging the trivial
 * normals in a k-neighborhood of each surfel. Then both the corrected
 * area (scalar product of estimated normal with trivial normal) and
 * the averaged area (inverse of L1-norm of estimated normal) is
 * computed per surfel, and summed in order to get area estimation.
 * This example illustrates the use of a \ref DGtal::IndexedDigitalSurface and
 * \ref DGtal::BreadthFirstVisitor onto it. This method is slightly faster than
 * using a \ref DGtal::DigitalSurface.
 *
 * @see \ref dgtal_digsurf_sec5
 *
@verbatim
$ ./examples/topology/area-estimation-with-indexed-digital-surface 13 6
New Block [Creating surface]
  Sphere of radius 13, 6-ring neighborhood
  [OK] Sphere has 3174 vertices/surfels with euler 2
EndBlock [Creating surface] (55.999 ms)
New Block [Estimating normals]
EndBlock [Estimating normals] (274.712 ms)
New Block [Estimating area]
  - true area      = 2123.72
  - corrected area = 2109.58
  - averaged area  = 2150.34
EndBlock [Estimating area] (0.023 ms)
@endverbatim
 *
 *\example topology/area-estimation-with-indexed-digital-surface.cpp
 *
 */


///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/graph/CUndirectedSimpleGraph.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/IndexedDigitalSurface.h"
#include "DGtal/shapes/Shapes.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

int main( int argc, char** argv )
{
  const double        R = argc >= 2 ? atof( argv[ 1 ] ) : 13.0; // radius of ball
  const unsigned int KN = argc >= 3 ? atoi( argv[ 2 ] ) : 6;    // size of neighborhood
  const int           M = (int) ceil( R + 2.0 );
  trace.beginBlock( "Creating surface" );
  trace.info() << "Sphere of radius " << R
	       << ", " << KN << "-ring neighborhood" << std::endl;
  typedef DigitalSetBoundary   < KSpace, DigitalSet >      DigitalSurfaceContainer;
  typedef IndexedDigitalSurface< DigitalSurfaceContainer > DigSurface;
  typedef BreadthFirstVisitor  < DigSurface >              BFSVisitor;
  Point p1( -M, -M, -M );
  Point p2(  M,  M,  M );
  KSpace K;
  K.init( p1, p2, true );
  DigitalSet aSet( Domain( p1, p2 ) );
  Shapes<Domain>::addNorm2Ball( aSet, Point( 0, 0, 0 ), R );
  auto dsc = CountedPtr< DigitalSurfaceContainer >( new DigitalSurfaceContainer( K, aSet ) );
  DigSurface dsurf( dsc );
  trace.info() << "[OK]"
	       << " Sphere has " << dsurf.size() << " vertices/surfels"
	       << " with euler " << dsurf.Euler() << std::endl;
  trace.endBlock();

  trace.beginBlock( "Estimating normals" );
  auto v2n = dsurf.makeVertexMap( RealPoint() );
  for ( auto v : dsurf )
    {
      int          nbv = 0;
      RealPoint normal = RealPoint::zero;
      BFSVisitor bfv( dsurf, v );
      while( ! bfv.finished() )
	{ // Vertex are colored according to the distance to initial seed.
	  auto node    = bfv.current();
	  if ( KN < node.second ) break;
          auto surfel  = dsurf.surfel( node.first );
	  RealPoint nv = RealPoint::zero;
	  Dimension  k = K.sOrthDir( surfel );
	  nv[ k ]      = K.sDirect( surfel, k ) ? 1.0 : -1.0;
	  normal      += nv;
	  nbv         += 1;
	  bfv.expand();
	}
      normal  /= nbv;
      v2n[ v ] = normal.getNormalized();
    }
  trace.endBlock();
  
  trace.beginBlock( "Estimating area" );
  const double area_true = 4.0 * M_PI * R * R;
  double   area_averaged = 0.0;
  double  area_corrected = 0.0;
  for ( auto v : dsurf )
    {
      auto     surfel = dsurf.surfel( v );
      Dimension     k = K.sOrthDir( surfel );
      area_corrected += fabs( v2n[ v ][ k ] );
      area_averaged  += 1.0 / v2n[ v ].norm( RealPoint::L_1 );
    }
  trace.info() << "- true area      = " << area_true << std::endl;
  trace.info() << "- corrected area = " << area_corrected << std::endl;
  trace.info() << "- averaged area  = " << area_averaged << std::endl;
  trace.endBlock();

  return 0;
}
///////////////////////////////////////////////////////////////////////////////
