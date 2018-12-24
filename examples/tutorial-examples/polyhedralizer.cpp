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
 * @file tutorial-examples/polyhedralizer.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/06/21
 *
 * An example file named polyhedralizer.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows how to make a polyhedron surface from a digital object vol file.

@see \ref tutoPolyhedralisation

@verbatim
$ ./examples/tutorial-examples/polyhedralizer
@endverbatim

\image html polyhedral-al-finished-w3.png "The polyhedral surface approaching Al Capone digital object, for width=3/1."
\image latex polyhedral-al-finished-w3.png "The polyhedral surface approaching Al Capone digital object, for width=3/1."

\example examples/tutorial-examples/polyhedralizer.cpp
*/

/**
Example of tutorial 2: making a polyhedron from a digital object
   @see @ref tutoPolyhedralisation
   \image html polyhedral-al-finished-w3.png "The polyhedral surface approaching Al Capone digital object, for width=3/1."
   @example tutorial-examples/polyhedralizer.cpp
 
*/

///////////////////////////////////////////////////////////////////////////////
//! [polyhedralizer-basicIncludes]
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"
//! [polyhedralizer-basicIncludes]

//! [polyhedralizer-includes-readvol]
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
//! [polyhedralizer-includes-readvol]

#include "DGtal/io/Display3D.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"

#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/topology/ImplicitDigitalSurface.h"

#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/geometry/surfaces/COBANaivePlaneComputer.h"
#include "DGtal/geometry/surfaces/ChordNaivePlaneComputer.h"
#include "DGtal/geometry/surfaces/ChordGenericNaivePlaneComputer.h"

#include "DGtal/math/linalg/SimpleMatrix.h"
#include "DGtal/math/linalg/EigenDecomposition.h"

///////////////////////////////////////////////////////////////////////////////

//! [polyhedralizer-typedefs]
using namespace std;
using namespace DGtal;
using namespace Z3i;
//! [polyhedralizer-typedefs]

template <typename T1, typename T2>
struct PairSorted2nd
{
  typedef PairSorted2nd<T1,T2> Self;
  inline PairSorted2nd( const T1& t1, const T2& t2 ) : first( t1 ), second( t2 ) {}
  bool operator<( const Self& other ) const
  {
    return second < other.second;
  }
  T1 first;
  T2 second;
};

template <typename T1, typename T2, typename T3>
struct Triple
{
  T1 first;
  T2 second;
  T3 third;
  Triple( T1 t1 = T1(), T2 t2 = T2(), T3 t3 = T3() )
    : first( t1 ), second( t2 ), third( t3 )
  {}
};

// Least-Square Fit of a plane N.x=mu on points [itB,itE). Returns mu.
template <typename RealVector,
          typename ConstIterator>
double LSF( RealVector& N, ConstIterator itB, ConstIterator itE )
{
  typedef typename RealVector::Component Component;
  typedef SimpleMatrix<Component,3,3> Matrix;
  Matrix A; A.clear();
  unsigned int nb = 0;
  RealVector G = RealVector::zero; // center of gravity
  for ( ConstIterator it = itB; it != itE; ++it )
    {
      G += RealVector( (*it)[ 0 ], (*it)[ 1 ], (*it)[ 2 ] );
      ++nb;
    }
  G /= nb;
  for ( ConstIterator it = itB; it != itE; ++it )
    {
      RealVector p( (*it)[ 0 ], (*it)[ 1 ], (*it)[ 2 ] );
      p -= G;
      for ( Dimension i = 0; i < 3; ++i )
        for ( Dimension j = 0; j < 3; ++j )
          A.setComponent( i, j, A( i, j ) + p[ i ] * p[ j ] );
    }
  // A is Gram matrix. We look for V such that V^t A V / |V|^2 is
  // minimal. It is thus the first eigenvalue.
  Matrix V;
  RealVector values;
  EigenDecomposition<3,Component>::getEigenDecomposition( A, V, values );
  N = V.column( 0 ); // first eigenvector;
  double mu = 0.0;
  for ( ConstIterator it = itB; it != itE; ++it )
    mu += N.dot( *it );
  return mu/(double)nb;
}


int main( int argc, char** argv )
{
  QApplication application(argc,argv);
  string inputFilename = argc > 1 ? argv[ 1 ] : examplesPath+"/samples/Al.100.vol";
  int threshold = argc > 2 ? atoi( argv[ 2 ] ) : 0;
  int widthNum = argc > 3 ? atoi( argv[ 3 ] ) : 2;
  int widthDen = argc > 4 ? atoi( argv[ 4 ] ) : 1;

  //! [polyhedralizer-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageContainerBySTLVector< Domain, int> Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  typedef functors::SimpleThresholdForegroundPredicate<Image> DigitalObject;
  DigitalObject digitalObject( image, threshold );
  trace.endBlock();
  //! [polyhedralizer-readVol]

  //! [polyhedralizer-KSpace]
  trace.beginBlock( "Construct the Khalimsky space from the image domain." );
  KSpace ks;
  bool space_ok = ks.init( image.domain().lowerBound(), image.domain().upperBound(), true );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<endl;
      return 2;
    }
  trace.endBlock();
  //! [polyhedralizer-KSpace]

  //! [polyhedralizer-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( false ); // exterior in all directions.
  //! [polyhedralizer-SurfelAdjacency]

  //! [polyhedralizer-ExtractingSurface]
  trace.beginBlock( "Extracting boundary by tracking the surface. " );
  typedef KSpace::Surfel Surfel;
  Surfel start_surfel = Surfaces<KSpace>::findABel( ks, digitalObject, 100000 );
  typedef ImplicitDigitalSurface< KSpace, DigitalObject > MyContainer;
  typedef DigitalSurface< MyContainer > MyDigitalSurface;
  typedef MyDigitalSurface::ConstIterator ConstIterator;
  MyContainer container( ks, digitalObject, surfAdj, start_surfel );
  MyDigitalSurface digSurf( container );
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << endl;
  trace.endBlock();
  //! [polyhedralizer-ExtractingSurface]

  //! [polyhedralizer-ComputingPlaneSize]
  // First pass to find biggest planes.
  trace.beginBlock( "Decomposition first pass. Computes all planes so as to sort vertices by the plane size." );
  typedef BreadthFirstVisitor<MyDigitalSurface> Visitor;
  typedef ChordGenericNaivePlaneComputer<Z3,Z3::Point, DGtal::int64_t> NaivePlaneComputer;
  map<Surfel,unsigned int> v2size;
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    v2size[ *it ] = 0;
  int j = 0;
  int nb = digSurf.size();
  NaivePlaneComputer planeComputer;
  vector<Point> layer;
  vector<Surfel> layer_surfel;
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    {
      if ( ( (++j) % 50 == 0 ) || ( j == nb ) ) trace.progressBar( j, nb );
      Surfel v = *it;
      planeComputer.init( widthNum, widthDen );
      // The visitor takes care of all the breadth-first traversal.
      Visitor visitor( digSurf, v );
      layer.clear();
      layer_surfel.clear();
      Visitor::Size currentSize = visitor.current().second;
      while ( ! visitor.finished() )
        {
          Visitor::Node node = visitor.current();
          v = node.first;
          int axis = ks.sOrthDir( v );
          Point p = ks.sCoords( ks.sDirectIncident( v, axis ) );
          if ( node.second != currentSize )
            {
              bool isExtended = planeComputer.extend( layer.begin(), layer.end() );
              if ( isExtended )
                {
                  for ( vector<Surfel>::const_iterator it_layer = layer_surfel.begin(),
                          it_layer_end = layer_surfel.end(); it_layer != it_layer_end; ++it_layer )
                    {
                      ++v2size[ *it_layer ];
                    }
                  layer_surfel.clear();
                  layer.clear();
                  currentSize = node.second;
                }
              else
                break;
            }
          layer_surfel.push_back( v );
          layer.push_back( p );
          visitor.expand();
        }
    }
  // Prepare queue
  typedef PairSorted2nd<Surfel,int> SurfelWeight;
  priority_queue<SurfelWeight> Q;
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    Q.push( SurfelWeight( *it, v2size[ *it ] ) );
  trace.endBlock();
  //! [polyhedralizer-ComputingPlaneSize]

  //! [polyhedralizer-segment]
  // Segmentation into planes
  trace.beginBlock( "Decomposition second pass. Visits vertices from the one with biggest plane to the one with smallest plane." );
  typedef Triple<NaivePlaneComputer, Color, pair<RealVector,double> > RoundPlane;
  set<Surfel> processedVertices;
  vector<RoundPlane*> roundPlanes;
  map<Surfel,RoundPlane*> v2plane;
  j = 0;
  while ( ! Q.empty() )
    {
      if ( ( (++j) % 50 == 0 ) || ( j == nb ) ) trace.progressBar( j, nb );
      Surfel v = Q.top().first;
      Q.pop();
      if ( processedVertices.find( v ) != processedVertices.end() ) // already in set
        continue; // process to next vertex

      RoundPlane* ptrRoundPlane = new RoundPlane;
      roundPlanes.push_back( ptrRoundPlane ); // to delete them afterwards.
      v2plane[ v ] = ptrRoundPlane;
      ptrRoundPlane->first.init( widthNum, widthDen );
      ptrRoundPlane->third = make_pair( RealVector::zero, 0.0 );
      // The visitor takes care of all the breadth-first traversal.
      Visitor visitor( digSurf, v );
      layer.clear();
      layer_surfel.clear();
      Visitor::Size currentSize = visitor.current().second;
      while ( ! visitor.finished() )
        {
          Visitor::Node node = visitor.current();
          v = node.first;
          Dimension axis = ks.sOrthDir( v );
          Point p = ks.sCoords( ks.sDirectIncident( v, axis ) );
          if ( node.second != currentSize )
            {
              bool isExtended = ptrRoundPlane->first.extend( layer.begin(), layer.end() );
              if ( isExtended )
                {
                  for ( vector<Surfel>::const_iterator it_layer = layer_surfel.begin(),
                          it_layer_end = layer_surfel.end(); it_layer != it_layer_end; ++it_layer )
                    {
                      Surfel s = *it_layer;
                      processedVertices.insert( s );
                      if ( v2plane.find( s ) == v2plane.end() )
                        v2plane[ s ] = ptrRoundPlane;
                    }
                  layer.clear();
                  layer_surfel.clear();
                  currentSize = node.second;
                }
              else break;
            }
          layer_surfel.push_back( v );
          layer.push_back( p );
          if ( processedVertices.find( v ) != processedVertices.end() )
            // surfel is already in some plane.
            visitor.ignore();
          else
            visitor.expand();
        }
      if ( visitor.finished() )
        {
          for ( vector<Surfel>::const_iterator it_layer = layer_surfel.begin(),
                  it_layer_end = layer_surfel.end(); it_layer != it_layer_end; ++it_layer )
            {
              Surfel s = *it_layer;
              processedVertices.insert( s );
              if ( v2plane.find( s ) == v2plane.end() )
                v2plane[ s ] = ptrRoundPlane;
            }
        }
      // Assign random color for each plane.
      ptrRoundPlane->second = Color( rand() % 192 + 64, rand() % 192 + 64, rand() % 192 + 64, 255 );
    }
  trace.endBlock();
  //! [polyhedralizer-segment]

  //! [polyhedralizer-lsf]
  for ( vector<RoundPlane*>::iterator
          it = roundPlanes.begin(), itE = roundPlanes.end();
        it != itE; ++it )
    {
      NaivePlaneComputer& computer = (*it)->first;
      RealVector normal;
      double mu = LSF( normal, computer.begin(), computer.end() );
      (*it)->third = make_pair( normal, mu );
    }
  //! [polyhedralizer-lsf]

  //! [polyhedralizer-projection]
  map<Surfel, RealPoint> coordinates;
  for ( map<Surfel,RoundPlane*>::const_iterator
          it = v2plane.begin(), itE = v2plane.end();
        it != itE; ++it )
    {
      Surfel v = it->first;
      RoundPlane* rplane = it->second;
      Point p = ks.sKCoords( v );
      RealPoint rp( (double)p[ 0 ]/2.0, (double)p[ 1 ]/2.0, (double)p[ 2 ]/2.0 );
      double mu = rplane->third.second;
      RealVector normal = rplane->third.first;
      double lambda = mu - rp.dot( normal );
      coordinates[ v ] = rp + lambda*normal;
    }
  typedef vector<Surfel> SurfelRange;
  map<Surfel, RealPoint> new_coordinates;
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    {
      Surfel s = *it;
      SurfelRange neighbors;
      back_insert_iterator<SurfelRange> writeIt = back_inserter( neighbors );
      digSurf.writeNeighbors( writeIt, *it );
      RealPoint x = RealPoint::zero;
      for ( SurfelRange::const_iterator its = neighbors.begin(), itsE = neighbors.end();
            its != itsE; ++its )
        x += coordinates[ *its ];
      new_coordinates[ s ] = x / neighbors.size();
    }
  //! [polyhedralizer-projection]

  //! [polyhedralizer-MakeMesh]
  typedef unsigned int Number;
  typedef Mesh<RealPoint> MyMesh;
  typedef MyMesh::MeshFace MeshFace;
  typedef MyDigitalSurface::FaceSet FaceSet;
  typedef MyDigitalSurface::VertexRange VertexRange;
  map<Surfel, Number> index;   // Numbers all vertices.
  Number nbv = 0;
  MyMesh polyhedron( true );
  // Insert all projected surfels as vertices of the polyhedral surface.
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    {
      polyhedron.addVertex( new_coordinates[ *it ] );
      index[ *it ] = nbv++;
    }
  // Define faces of the mesh. Outputs closed faces.
  FaceSet faces = digSurf.allClosedFaces();
  for ( typename FaceSet::const_iterator itf = faces.begin(), itf_end = faces.end();
        itf != itf_end; ++itf )
    {
      MeshFace mface( itf->nbVertices );
      VertexRange vtcs = digSurf.verticesAroundFace( *itf );
      int i = 0;
      for ( typename VertexRange::const_iterator itv = vtcs.begin(), itv_end = vtcs.end();
            itv != itv_end; ++itv )
        {
          mface[ i++ ] = index[ *itv ];
        }
      polyhedron.addFace( mface, Color( 255, 243, 150, 255 ) );
    }
  //! [polyhedralizer-MakeMesh]

  //! [polyhedralizer-visualization]
  typedef Viewer3D<Space,KSpace> MyViewer3D;
  MyViewer3D viewer( ks );
  viewer.show();
  bool isOK = polyhedron >> "test.off";
  bool isOK2 = polyhedron >> "test.obj";
  viewer << polyhedron;
  viewer << MyViewer3D::updateDisplay;
  application.exec();
  //! [polyhedralizer-visualization]

  //! [polyhedralizer-freeMemory]
  for ( vector<RoundPlane*>::iterator
          it = roundPlanes.begin(), itE = roundPlanes.end();
        it != itE; ++it )
    delete *it;
  //! [polyhedralizer-freeMemory]

  if (isOK && isOK2)
    return 0;
  else
    return 1;
}
