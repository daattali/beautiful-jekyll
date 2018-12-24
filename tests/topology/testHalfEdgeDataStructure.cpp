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
 * @file testHalfEdgeDataStructure.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/04
 *
 * Functions for testing class HalfEdgeDataStructure.
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
#include "DGtal/topology/HalfEdgeDataStructure.h"
///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class HalfEdgeDataStructure.
///////////////////////////////////////////////////////////////////////////////
typedef HalfEdgeDataStructure::Triangle         Triangle;
typedef HalfEdgeDataStructure::PolygonalFace    PolygonalFace;
typedef HalfEdgeDataStructure::Edge             Edge;
typedef HalfEdgeDataStructure::Arc              Arc;
typedef HalfEdgeDataStructure::VertexIndexRange VertexIndexRange;

HalfEdgeDataStructure makeTwoTriangles()
{
  std::vector< Triangle > triangles( 2 );
  triangles[0].v = { 0, 1, 2 };
  triangles[1].v = { 2, 1, 3 };

  HalfEdgeDataStructure mesh;
  mesh.build( triangles );
  return mesh;
}

HalfEdgeDataStructure makeThreeTriangles()
{
  std::vector< Triangle > triangles( 3 );
  triangles[0].v = { 0, 1, 2 };
  triangles[1].v = { 2, 1, 3 };
  triangles[2].v = { 2, 3, 0 };

  HalfEdgeDataStructure mesh;
  mesh.build( triangles );
  return mesh;
}

HalfEdgeDataStructure makeTetrahedron()
{
  std::vector< Triangle > triangles( 4 );
  triangles[0].v = { 0, 1, 2 };
  triangles[1].v = { 2, 1, 3 };
  triangles[2].v = { 2, 3, 0 };
  triangles[3].v = { 0, 3, 1 };

  HalfEdgeDataStructure mesh;
  mesh.build( triangles );
  return mesh;
}

HalfEdgeDataStructure makeRibbonWithHole()
{
  std::vector< Triangle > triangles( 6 );
  triangles[0].v = { 0, 1, 2 };
  triangles[1].v = { 2, 1, 3 };
  triangles[2].v = { 2, 3, 4 };
  triangles[3].v = { 4, 3, 5 };
  triangles[4].v = { 4, 5, 0 };
  triangles[5].v = { 0, 5, 1 };
  std::vector< Edge > edges;
  const int kNumVertices
    = HalfEdgeDataStructure::getUnorderedEdgesFromTriangles( triangles, edges );
  HalfEdgeDataStructure mesh;
  mesh.build( kNumVertices, triangles, edges );
  return mesh;
}

HalfEdgeDataStructure makeTriangulatedDisk()
{
  std::vector< Triangle > triangles( 7 );
  triangles[0].v = { 0, 1, 2 };
  triangles[1].v = { 2, 1, 3 };
  triangles[2].v = { 2, 3, 4 };
  triangles[3].v = { 4, 3, 5 };
  triangles[4].v = { 4, 5, 0 };
  triangles[5].v = { 0, 5, 1 };
  triangles[6].v = { 4, 0, 2 };
  std::vector< Edge > edges;
  const int kNumVertices
    = HalfEdgeDataStructure::getUnorderedEdgesFromTriangles( triangles, edges );
  HalfEdgeDataStructure mesh;
  mesh.build( kNumVertices, triangles, edges );
  return mesh;
}

HalfEdgeDataStructure makePyramid()
{
  std::vector< PolygonalFace > faces( 5 );
  faces[ 0 ] = PolygonalFace( { 0, 3, 2, 1 } );
  faces[ 1 ] = PolygonalFace( { 0, 1, 4 } );
  faces[ 2 ] = PolygonalFace( { 1, 2, 4 } );
  faces[ 3 ] = PolygonalFace( { 2, 3, 4 } );
  faces[ 4 ] = PolygonalFace( { 3, 0, 4 } );
  HalfEdgeDataStructure mesh;
  mesh.build( faces );
  return mesh;
}

HalfEdgeDataStructure makeCube()
{
  std::vector< PolygonalFace > faces( 6 );
  faces[ 0 ] = PolygonalFace( { 1, 0, 2, 3 } );
  faces[ 1 ] = PolygonalFace( { 0, 1, 5, 4 } );
  faces[ 2 ] = PolygonalFace( { 1, 3, 7, 5 } );
  faces[ 3 ] = PolygonalFace( { 3, 2, 6, 7 } );
  faces[ 4 ] = PolygonalFace( { 2, 0, 4, 6 } );
  faces[ 5 ] = PolygonalFace( { 4, 5, 7, 6 } );
  HalfEdgeDataStructure mesh;
  mesh.build( faces );
  return mesh;
}

HalfEdgeDataStructure makeBox()
{
  std::vector< PolygonalFace > faces( 6 );
  faces[ 0 ] = PolygonalFace( { 1, 0, 2, 3 } );
  faces[ 1 ] = PolygonalFace( { 0, 1, 5, 4 } );
  faces[ 2 ] = PolygonalFace( { 1, 3, 7, 5 } );
  faces[ 3 ] = PolygonalFace( { 3, 2, 6, 7 } );
  faces[ 4 ] = PolygonalFace( { 2, 0, 4, 6 } );
  faces[ 5 ] = PolygonalFace( { 4, 5, 8, 9 } );
  HalfEdgeDataStructure mesh;
  mesh.build( faces );
  return mesh;
}


SCENARIO( "HalfEdgeDataStructure build", "[halfedge][build]" )
{
  GIVEN( "Two triangles incident by an edge" ) {
    HalfEdgeDataStructure mesh = makeTwoTriangles();
    THEN( "The mesh has 4 vertices, 5 edges, 2 faces, 10 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  4 );
      REQUIRE( mesh.nbEdges()     ==  5 );
      REQUIRE( mesh.nbFaces()     ==  2 );
      REQUIRE( mesh.nbHalfEdges() == 10 );
    }
    THEN( "The mesh has 4 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 4 );
      REQUIRE( bdry[ 0 ] == 0 );
      REQUIRE( bdry[ 1 ] == 1 );
      REQUIRE( bdry[ 2 ] == 2 );
      REQUIRE( bdry[ 3 ] == 3 );
    }
    THEN( "The mesh has 4 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 4 );
      // std::cout << " arc=(" << bdry[ 0 ].first << "," << bdry[ 0 ].second << ")" << std::endl;
      REQUIRE( bdry[ 0 ] == Arc( 0, 2 ) );
      REQUIRE( bdry[ 1 ] == Arc( 1, 0 ) );
      REQUIRE( bdry[ 2 ] == Arc( 2, 3 ) );
      REQUIRE( bdry[ 3 ] == Arc( 3, 1 ) );
    }
  }
  GIVEN( "Three triangles forming a fan around a vertex" ) {
    HalfEdgeDataStructure mesh = makeThreeTriangles();
    THEN( "The mesh has 4 vertices, 6 edges, 3 faces, 12 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  4 );
      REQUIRE( mesh.nbEdges()     ==  6 );
      REQUIRE( mesh.nbFaces()     ==  3 );
      REQUIRE( mesh.nbHalfEdges() == 12 );
    }
    THEN( "The mesh has 3 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 3 );
      REQUIRE( bdry[ 0 ] == 0 );
      REQUIRE( bdry[ 1 ] == 1 );
      REQUIRE( bdry[ 2 ] == 3 );
    }
    THEN( "The mesh has 3 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 3 );
      // std::cout << " arc=(" << bdry[ 0 ].first << "," << bdry[ 0 ].second << ")" << std::endl;
      REQUIRE( bdry[ 0 ] == Arc( 0, 3 ) );
      REQUIRE( bdry[ 1 ] == Arc( 1, 0 ) );
      REQUIRE( bdry[ 2 ] == Arc( 3, 1 ) );
    }
  }
  GIVEN( "Four triangles forming a tetrahedron" ) {
    HalfEdgeDataStructure mesh = makeTetrahedron();
    THEN( "The mesh has 4 vertices, 6 edges, 4 faces, 12 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  4 );
      REQUIRE( mesh.nbEdges()     ==  6 );
      REQUIRE( mesh.nbFaces()     ==  4 );
      REQUIRE( mesh.nbHalfEdges() == 12 );
    }
    THEN( "The mesh has no boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      REQUIRE( bdry.size() == 0 );
    }
    THEN( "The mesh has no boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      REQUIRE( bdry.size() == 0 );
    }
  }
  GIVEN( "A ribbon with a hole" ) {
    HalfEdgeDataStructure mesh = makeRibbonWithHole();
    THEN( "The mesh has 6 vertices, 12 edges, 6 faces, 24 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  6 );
      REQUIRE( mesh.nbEdges()     ==  12 );
      REQUIRE( mesh.nbFaces()     ==  6 );
      REQUIRE( mesh.nbHalfEdges() == 24 );
    }
    THEN( "The mesh has 6 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      REQUIRE( bdry.size() == 6 );
    }
    THEN( "The mesh has 6 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 6 );
      REQUIRE( bdry[ 0 ] == Arc( 0, 2 ) );
      REQUIRE( bdry[ 1 ] == Arc( 1, 5 ) );
      REQUIRE( bdry[ 2 ] == Arc( 2, 4 ) );
      REQUIRE( bdry[ 3 ] == Arc( 3, 1 ) );
      REQUIRE( bdry[ 4 ] == Arc( 4, 0 ) );
      REQUIRE( bdry[ 5 ] == Arc( 5, 3 ) );
    }
  }
  GIVEN( "The same ribbon with his hole closed" ) {
    HalfEdgeDataStructure mesh = makeTriangulatedDisk();
    THEN( "The mesh has 6 vertices, 12 edges, 7 faces, 24 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  6 );
      REQUIRE( mesh.nbEdges()     ==  12 );
      REQUIRE( mesh.nbFaces()     ==  7 );
      REQUIRE( mesh.nbHalfEdges() == 24 );
    }
    THEN( "The mesh has 3 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 3 );
      REQUIRE( bdry[ 0 ] == 1 );
      REQUIRE( bdry[ 1 ] == 3 );
      REQUIRE( bdry[ 2 ] == 5 );
    }
    THEN( "The mesh has 3 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      std::sort( bdry.begin(), bdry.end() );
      REQUIRE( bdry.size() == 3 );
      REQUIRE( bdry[ 0 ] == Arc( 1, 5 ) );
      REQUIRE( bdry[ 1 ] == Arc( 3, 1 ) );
      REQUIRE( bdry[ 2 ] == Arc( 5, 3 ) );
    }
  }
  GIVEN( "A pyramid with a square base" ) {
    HalfEdgeDataStructure mesh = makePyramid();
    THEN( "The mesh has 5 vertices, 8 edges, 5 faces, 16 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  5 );
      REQUIRE( mesh.nbEdges()     ==  8 );
      REQUIRE( mesh.nbFaces()     ==  5 );
      REQUIRE( mesh.nbHalfEdges() == 16 );
    }
    THEN( "The mesh has 0 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      REQUIRE( bdry.size() == 0 );
    }
    THEN( "The mesh has 0 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      REQUIRE( bdry.size() == 0 );
    }
  }
  GIVEN( "A cube" ) {
    HalfEdgeDataStructure mesh = makeCube();
    THEN( "The mesh has 8 vertices, 12 edges, 6 faces, 24 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  8 );
      REQUIRE( mesh.nbEdges()     ==  12 );
      REQUIRE( mesh.nbFaces()     ==  6 );
      REQUIRE( mesh.nbHalfEdges() == 24 );
    }
    THEN( "The mesh has 0 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      REQUIRE( bdry.size() == 0 );
    }
    THEN( "The mesh has 0 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      REQUIRE( bdry.size() == 0 );
    }
  }
  GIVEN( "A box with an open side" ) {
    HalfEdgeDataStructure mesh = makeBox();
    THEN( "The mesh has 10 vertices, 15 edges, 6 faces, 30 half-edges" ) {
      REQUIRE( mesh.nbVertices()  ==  10 );
      REQUIRE( mesh.nbEdges()     ==  15 );
      REQUIRE( mesh.nbFaces()     ==  6 );
      REQUIRE( mesh.nbHalfEdges() == 30 );
    }
    THEN( "The mesh has 6 boundary vertices" ) {
      VertexIndexRange bdry = mesh.boundaryVertices();
      REQUIRE( bdry.size() == 6 );
    }
    THEN( "The mesh has 6 boundary arcs" ) {
      std::vector<Arc> bdry = mesh.boundaryArcs();
      REQUIRE( bdry.size() == 6 );
    }
  }

}

SCENARIO( "HalfEdgeDataStructure neighboring relations", "[halfedge][neighbors]" ){
  GIVEN( "Two triangles incident by an edge" ) {
    HalfEdgeDataStructure mesh = makeTwoTriangles();
    VertexIndexRange nv;
    THEN( "Vertex 0 has 2 neighboring vertices" ) {
      mesh.getNeighboringVertices( 0, nv );
      VertexIndexRange expected = { 1, 2 };
      REQUIRE( nv.size()  ==  2 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 1 has 3 neighboring vertices" ) {
      mesh.getNeighboringVertices( 1, nv );
      VertexIndexRange expected = { 3, 2, 0 };
      REQUIRE( nv.size()  ==  3 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 2 has 3 neighboring vertices" ) {
      mesh.getNeighboringVertices( 2, nv );
      VertexIndexRange expected = { 0, 1, 3 };
      REQUIRE( nv.size()  ==  3 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 3 has 2 neighboring vertices" ) {
      mesh.getNeighboringVertices( 3, nv );
      VertexIndexRange expected = { 2, 1 };
      REQUIRE( nv.size()  ==  2 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
  }
  GIVEN( "A ribbon with a hole" ) {
    HalfEdgeDataStructure mesh = makeRibbonWithHole();
    VertexIndexRange nv;
    THEN( "Vertex 0 has 4 neighboring vertices" ) {
      mesh.getNeighboringVertices( 0, nv );
      VertexIndexRange expected = { 4, 5, 1, 2 };
      REQUIRE( nv.size()  ==  4 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 1 has 4 neighboring vertices" ) {
      mesh.getNeighboringVertices( 1, nv );
      VertexIndexRange expected = { 3, 2, 0, 5 };
      REQUIRE( nv.size()  ==  4 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 2 has 4 neighboring vertices" ) {
      mesh.getNeighboringVertices( 2, nv );
      VertexIndexRange expected = { 0, 1, 3, 4 };
      REQUIRE( nv.size()  ==  4 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
  }

  GIVEN( "A box with an open side" ) {
    HalfEdgeDataStructure mesh = makeBox();
    VertexIndexRange nv;
    THEN( "Vertex 0 has 3 neighboring vertices" ) {
      mesh.getNeighboringVertices( 0, nv );
      VertexIndexRange expected = { 1, 4, 2 };
      REQUIRE( nv.size()  ==  3 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 5 has 4 neighboring vertices" ) {
      mesh.getNeighboringVertices( 5, nv );
      VertexIndexRange expected = { 8, 4, 1, 7 };
      REQUIRE( nv.size()  ==  4 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
    THEN( "Vertex 7 has 3 neighboring vertices" ) {
      mesh.getNeighboringVertices( 7, nv );
      VertexIndexRange expected = { 5, 3, 6 };
      REQUIRE( nv.size()  ==  3 );
      REQUIRE( std::is_permutation( nv.begin(), nv.end(), expected.begin() ) );
    }
  }
}

/** @ingroup Tests **/
