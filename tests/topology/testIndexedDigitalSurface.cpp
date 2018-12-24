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
 * @file testIndexedDigitalSurface.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/06
 *
 * Functions for testing class IndexedDigitalSurface.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
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
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class IndexedDigitalSurface.
///////////////////////////////////////////////////////////////////////////////


SCENARIO( "IndexedDigitalSurface< DigitalSetBoundary > build tests", "[idxdsurf][build]" )
{
  typedef DigitalSetBoundary< KSpace, DigitalSet > DigitalSurfaceContainer;
  typedef IndexedDigitalSurface< DigitalSurfaceContainer > DigSurface;
  Point p1( -5, -5, -5 );
  Point p2(  5,  5,  5 );
  KSpace K;
  K.init( p1, p2, true );
  DigitalSet aSet( Domain( p1, p2 ) );
  Shapes<Domain>::addNorm2Ball( aSet, Point( 0, 0, 0 ), 3 );
  DigSurface dsurf;
  bool build_ok = dsurf.build( new DigitalSurfaceContainer( K, aSet ) );
  GIVEN( "A digital set boundary over a ball of radius 3" ) {
    THEN( "Build of underlying half-edge data structure should be ok" ) {
      REQUIRE( build_ok == true );
    }
    THEN( "The indexed digital surface has 174 vertices, 348 edges, 176 edges, and Euler=2 as the sphere" ) {
      REQUIRE( dsurf.nbVertices() == 174 );
      REQUIRE( dsurf.nbEdges() == 348 );
      REQUIRE( dsurf.nbFaces() == 176 );
      REQUIRE( dsurf.Euler() == 2 );
    }
    THEN( "All vertices have 4 neighbors" ) {
      REQUIRE( dsurf.degree( 0 ) == 4 );
      REQUIRE( dsurf.degree( 17 ) == 4 );
      REQUIRE( dsurf.degree( 54) == 4 );
      REQUIRE( dsurf.degree( 102 ) == 4 );
    }
    THEN( "Vertices corresponds to surfels, Arcs to linels, Faces to pointels" ) {
      REQUIRE( K.sDim( dsurf.surfel( 0 ) ) == 2 );
      REQUIRE( K.sDim( dsurf.surfel( 17 ) ) == 2 );
      REQUIRE( K.sDim( dsurf.linel( 0  ) ) == 1 );
      REQUIRE( K.sDim( dsurf.linel( 25 ) ) == 1 );
      REQUIRE( K.sDim( dsurf.pointel( 0 ) ) == 0 );
      REQUIRE( K.sDim( dsurf.pointel( 25 ) ) == 0 );
    }
    THEN( "Linels of opposite arcs are opposite cells" ) {
      REQUIRE( K.sOpp( dsurf.linel( 15 ) ) == dsurf.linel( dsurf.opposite( 15 ) ) );
      REQUIRE( K.sOpp( dsurf.linel( 34 ) ) == dsurf.linel( dsurf.opposite( 34 ) ) );
      REQUIRE( K.sOpp( dsurf.linel( 112 ) ) == dsurf.linel( dsurf.opposite( 112 ) ) );
      REQUIRE( K.sOpp( dsurf.linel( 200 ) ) == dsurf.linel( dsurf.opposite( 200 ) ) );
    }
    THEN( "Breadth-first visiting the digital surface from vertex 0 goes to a distance 13." ) {
      BreadthFirstVisitor< DigSurface > visitor( dsurf, 0 );
      std::vector<int> vertices;
      std::vector<int> distances;
      while ( ! visitor.finished() )
	{
	  vertices.push_back( visitor.current().first );
	  distances.push_back( visitor.current().second );
	  visitor.expand();
	}
      REQUIRE( vertices.size() == 174 );
      REQUIRE( distances.size() == 174 );
      REQUIRE( distances.back() == 13 );
    }      
  }
}

SCENARIO( "IndexedDigitalSurface< RealPoint3 > concept check tests", "[idxdsurf][concepts]" )
{
  typedef DigitalSetBoundary< KSpace, DigitalSet > DigitalSurfaceContainer;
  typedef IndexedDigitalSurface< DigitalSurfaceContainer > DigSurface;
  BOOST_CONCEPT_ASSERT(( concepts::CUndirectedSimpleGraph< DigSurface > ));
}

/** @ingroup Tests **/
