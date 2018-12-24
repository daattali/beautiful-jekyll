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
 * @file testTriangulatedSurface.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/06
 *
 * Functions for testing class TriangulatedSurface.
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
#include "DGtal/shapes/TriangulatedSurface.h"
#include "DGtal/shapes/MeshHelpers.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class TriangulatedSurface.
///////////////////////////////////////////////////////////////////////////////

typedef PointVector<3,double>             RealPoint;
typedef TriangulatedSurface< RealPoint >  TriMesh;
typedef TriMesh::VertexRange              VertexRange;
typedef TriMesh::ArcRange                 ArcRange;
typedef TriMesh::Arc                      Arc;
typedef TriMesh::Face                     Face;
typedef TriMesh::Vertex                   Vertex;
typedef TriMesh::PositionsMap             PositionsMap;

TriMesh makeTwoTriangles()
{
  TriMesh mesh;
  mesh.addVertex( RealPoint( 0, 0, 0 ) );
  mesh.addVertex( RealPoint( 1, 0, 0 ) );
  mesh.addVertex( RealPoint( 0, 1, 0 ) );
  mesh.addVertex( RealPoint( 1, 1, 1 ) );
  mesh.addTriangle( 0, 1, 2 );
  mesh.addTriangle( 2, 1, 3 );
  mesh.build();
  return mesh;
}

SCENARIO( "TriangulatedSurface< RealPoint3 > build tests", "[trisurf][build]" )
{
  GIVEN( "Two triangles incident by an edge" ) {
    TriMesh trimesh = makeTwoTriangles();
    THEN( "The mesh has 4 vertices, v0 has 2 neighbors, v1 has 3 neighbors, etc" ) {
      REQUIRE( trimesh.size() == 4 );
      REQUIRE( trimesh.degree( 0 ) == 2 );
      REQUIRE( trimesh.degree( 1 ) == 3 );
      REQUIRE( trimesh.degree( 2 ) == 3 );
      REQUIRE( trimesh.degree( 3 ) == 2 );
    }
    THEN( "Euler number is 1 as is the Euler number of a disk." )
      {
	REQUIRE( trimesh.nbVertices() == 4 );
	REQUIRE( trimesh.nbEdges() == 5 );
	REQUIRE( trimesh.nbFaces() == 2 );
	REQUIRE( trimesh.Euler() == 1 );
      }
    THEN( "Breadth-first visiting the mesh from vertex 3, visit 3, then {1,2}, then 0." )
      {
        BreadthFirstVisitor< TriMesh > visitor( trimesh, 3 );
        std::vector<int> vertices;
        std::vector<int> distances;
        while ( ! visitor.finished() )
          {
            vertices.push_back( visitor.current().first );
            distances.push_back( visitor.current().second );
            visitor.expand();
          }
        REQUIRE( vertices.size() == 4 );
        REQUIRE( distances.size() == 4 );
        int expected_vertices1[] = { 3, 1, 2, 0};
        int expected_vertices2[] = { 3, 2, 1, 0};
        int expected_distance [] = { 0, 1, 1, 2};
        bool vertices_ok
          = std::equal( vertices.begin(), vertices.end(), expected_vertices1 )
          || std::equal( vertices.begin(), vertices.end(), expected_vertices2 );
        REQUIRE( vertices_ok );
        bool distances_ok
          = std::equal( distances.begin(), distances.end(), expected_distance );
        REQUIRE( distances_ok );
      }      
    THEN( "The mesh has 4 boundary vertices" ) {
      VertexRange bv = trimesh.allBoundaryVertices();
      std::sort( bv.begin(), bv.end() );
      int expected_bv [] = { 0, 1, 2, 3};
      REQUIRE( bv.size() == 4 );
      bool bv_ok = std::equal( bv.begin(), bv.end(), expected_bv );
      REQUIRE( bv_ok );
    }
    THEN( "The mesh has 4 boundary arcs" ) {
      ArcRange ba = trimesh.allBoundaryArcs();
      REQUIRE( ba.size() == 4 );
    }
    THEN( "The face along (1,2) is a triangle (0,1,2)" ) {
      Arc  a12      = trimesh.arc( 1, 2 );
      Face f        = trimesh.faceAroundArc( a12 );
      ArcRange    A = trimesh.arcsAroundFace( f );
      VertexRange T = trimesh.verticesAroundFace( f );
      REQUIRE( A.size() == 3 );
      REQUIRE( T.size() == 3 );
      REQUIRE( trimesh.head( A[ 0 ] ) == T[ 0 ] );
      REQUIRE( trimesh.head( A[ 1 ] ) == T[ 1 ] );
      REQUIRE( trimesh.head( A[ 2 ] ) == T[ 2 ] );
      std::sort( T.begin(), T.end() );
      REQUIRE( T[ 0 ] == 0 );
      REQUIRE( T[ 1 ] == 1 );
      REQUIRE( T[ 2 ] == 2 );
    }
    THEN( "The face along (2,1) is a triangle (2,1,3)" ) {
      Arc  a21      = trimesh.arc( 2, 1 );
      Face f        = trimesh.faceAroundArc( a21 );
      VertexRange T = trimesh.verticesAroundFace( f );
      REQUIRE( T.size() == 3 );
      std::sort( T.begin(), T.end() );
      REQUIRE( T[ 0 ] == 1 );
      REQUIRE( T[ 1 ] == 2 );
      REQUIRE( T[ 2 ] == 3 );
    }
    THEN( "The mesh has the barycenter (0.5, 0.5, 0.25) " ) {
      PositionsMap positions = trimesh.positions();
      RealPoint b;
      for ( Vertex v = 0; v < trimesh.size(); ++v )
        b += positions( v );
      b /= 4;
      REQUIRE( b[ 0 ] == 0.5 );
      REQUIRE( b[ 1 ] == 0.5 );
      REQUIRE( b[ 2 ] == 0.25 );
    }
    THEN( "We can convert the triangulated surface to a mesh and vice versa" ) {
      Mesh<RealPoint> mesh;
      MeshHelpers::triangulatedSurface2Mesh( trimesh, mesh );
      TriMesh trimesh2;
      MeshHelpers::mesh2TriangulatedSurface( mesh, trimesh2 );
      REQUIRE( mesh.nbVertex() == trimesh.nbVertices() );
      REQUIRE( mesh.nbFaces()  == trimesh.nbFaces() );
      REQUIRE( trimesh2.nbVertices() == trimesh.nbVertices() );
      REQUIRE( trimesh2.nbArcs()     == trimesh.nbArcs() );
      REQUIRE( trimesh2.nbFaces()    == trimesh.nbFaces() );
    }
    THEN( "We can iterate over the vertices" ) {
      PositionsMap positions       = trimesh.positions();
      RealPoint    exp_positions[] = { { 0,0,0 }, { 1,0,0 }, { 0,1,0 }, { 1,1,1 } };
      for ( auto it = trimesh.begin(), itE = trimesh.end(); it != itE; ++it ) {
	REQUIRE( positions[ *it ] == exp_positions[ *it ] );
      }
    }
  }
}

SCENARIO( "TriangulatedSurface< RealPoint3 > concept check tests", "[trisurf][concepts]" )
{
  BOOST_CONCEPT_ASSERT(( concepts::CUndirectedSimpleGraph< TriMesh > ));
}

/** @ingroup Tests **/
