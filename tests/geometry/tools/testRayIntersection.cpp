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
 * @file testRayIntersection.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/08/14
 *
 * Functions for testing class RayIntersection.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/tools/RayIntersectionPredicates.h"

/// Shape
#include "DGtal/shapes/implicit/ImplicitBall.h"

/// Digitization
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class RayIntersection.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
template<typename Point>
bool testRayIntersection()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing RayTriangle ..." );
  
  typedef RayIntersectionPredicate<Point> Ray;
  Ray  ray(Point(0,0,0), Point(1,1,1));

  trace.info() << "Ray intersection with 222-triangle  "<<std::endl;
  nbok += ray(Point(2,0,0),Point(0,0,2),Point(0,2,0)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true " << std::endl;

  trace.info() << "Ray intersection with reversed 222-triangle "<<std::endl;
  nbok += ray(Point(2,0,0),Point(0,2,0),Point(0,0,2)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true (no culling) " << std::endl;

  Ray  ray2(Point(100,0,0), Point(1,1,1));
  trace.info() << "Ray intersection wrong ray with 222-triangle"<<std::endl;
  nbok += !ray2(Point(2,0,0),Point(0,2,0),Point(0,0,2)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "false (no intersection)" << std::endl;
   

  Ray  ray3(Point(0,0,0), Point(-1,-1,-1));
  trace.info() << "Ray intersection reversed ray with 222-triangle "<<std::endl;
  nbok += !ray3(Point(2,0,0),Point(0,2,0),Point(0,0,2)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "false (reversed ray)" << std::endl;


  trace.info() << "Ray intersection with -2-2-2-triangle "<<std::endl;
  nbok += !ray(Point(-2,0,0),Point(0,-2,0),Point(0,0,-2)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "false (reversed triangle)" << std::endl;

  Ray  ray4(Point(2,2,0), Point(-1,-1,0));
  trace.info() << "Ray intersection in plane  "<<std::endl;
  nbok += !ray4(Point(0,0,0),Point(0,1,0),Point(1,1,0)) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "false (in plane)" << std::endl;


  trace.endBlock();
  
  return nbok == nb;
}

bool testRayQuadIntersection()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing RayQuad ..." );

  using namespace Z3i;
  
  typedef RayIntersectionPredicate<Point> Ray;
  Ray  ray(Point(0,0,0), Point(1,1,1));

  trace.info() << "Ray intersection with huge quad   "<<std::endl;
  nbok += ray(Point(10,0,0),Point(10,100,0),
              Point(10,0,100),Point(10,100,100) ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true " << std::endl;
  trace.info()<<std::endl;

  trace.info() << "Ray intersection with far quad   "<<std::endl;
  nbok += !ray(Point(10,0,0),Point(10,1,0),
               Point(10,0,1),Point(10,1,1) ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "false " << std::endl;
  trace.info()<<std::endl;

  trace.endBlock();
  
  return nbok == nb;
}

bool testRaySurfelIntersection()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing RaySurfel ..." );

  using namespace Z3i;
  
  KSpace k;

  k.init(Point(0,0,0), Point(10,10,10), true);
  
  typedef RayIntersectionPredicate<KSpace::Cell::Point> Ray;
  Ray  ray(KSpace::Cell::Point(0,0,0), 
           KSpace::Cell::Point(2,1,1));

  KSpace::Surfel surf =  k.sCell( Point( 2,1,1) );
  KSpace::Surfel surf2 =  k.sCell( Point( 2,7,7) );
  
  trace.info() << "Ray intersection with surf   "<<std::endl;
  nbok += ray(surf)  ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "true " << std::endl;
  trace.info()<<std::endl;
  
  trace.info() << "Ray intersection with surf2  "<<std::endl;
  nbok += !ray(surf2 ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "false " << std::endl;
  trace.info()<<std::endl;

  trace.endBlock();
  
  return nbok == nb;
}


bool testRaySurface()
{
  typedef ImplicitBall<Z3i::Space> ImplicitShape;
  typedef GaussDigitizer<Z3i::Space, ImplicitShape> DigitalShape;
  typedef LightImplicitDigitalSurface<Z3i::KSpace,DigitalShape> Boundary;
  typedef DigitalSurface< Boundary > MyDigitalSurface;
  trace.beginBlock(" Ray shooting in digital surface");
  trace.beginBlock( "Shape initialisation ..." );
  ImplicitShape ishape( Z3i::RealPoint( 0, 0 ,0), 12 );
  DigitalShape dshape;
  dshape.attach( ishape );
  dshape.init( Z3i::RealPoint( -20.0, -20.0 ,-20.0 ), Z3i::RealPoint( 20.0, 20.0, 20.0  ), 1.0 );
  Z3i::KSpace K;
  if ( !K.init( dshape.getLowerBound(), dshape.getUpperBound(), true ) )
  {
    trace.error() << "Problem with Khalimsky space init" << std::endl;
    return false;
  }

  Z3i::KSpace::Surfel bel = Surfaces<Z3i::KSpace>::findABel( K, dshape, 10000 );
  Boundary boundary( K, dshape, SurfelAdjacency<Z3i::KSpace::dimension>( true ), bel );
  MyDigitalSurface surf ( boundary );
  trace.endBlock();


  trace.beginBlock(" Ray shooting the shape");
  
  RayIntersectionPredicate<Z3i::KSpace::Cell::Point> ray(Z3i::KSpace::Cell::Point(0,0,0),
                                                         Z3i::KSpace::Cell::Point(2,2,2));

  RayIntersectionPredicate<Z3i::KSpace::Cell::Point> ray2(Z3i::KSpace::Cell::Point(0,0,0),
                                                          Z3i::KSpace::Cell::Point(1,0,0));

  MyDigitalSurface::ConstIterator it = std::find_if(surf.begin(), surf.end(), ray); 
  trace.info() << "Ray shooting returns : "<< *it<<std::endl;

  MyDigitalSurface::ConstIterator it2 = std::find_if(surf.begin(), surf.end(), ray2); 
  trace.info() << "Ray shooting returns : "<< *it2<<std::endl;
  
  trace.endBlock();
  trace.endBlock();

  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class RayIntersection" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testRayIntersection<Z3i::Point>() 
    && testRayIntersection<Z3i::RealPoint>()
    && testRayQuadIntersection()
    && testRaySurfelIntersection()
    && testRaySurface(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
