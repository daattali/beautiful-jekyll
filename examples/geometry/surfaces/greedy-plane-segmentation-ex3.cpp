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
 * @file geometry/surfaces/greedy-plane-segmentation-ex3.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/10/01
 *
 * An example file named greedy-plane-segmentation-ex3.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>

#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"

#include "DGtal/io/Display3D.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/geometry/surfaces/COBANaivePlaneComputer.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

//! [greedy-plane-segmentation-ex3-typedefs]
using namespace Z3i;
typedef DGtal::int64_t InternalInteger;
typedef COBANaivePlaneComputer<Z3,InternalInteger> NaivePlaneComputer;
// We choose the DigitalSetBoundary surface container in order to
// segment connected or unconnected surfaces.
typedef DigitalSetBoundary<KSpace,DigitalSet> MyDigitalSurfaceContainer;
typedef DigitalSurface<MyDigitalSurfaceContainer> MyDigitalSurface;
typedef MyDigitalSurface::ConstIterator ConstIterator;
typedef MyDigitalSurface::Vertex Vertex;
typedef MyDigitalSurface::SurfelSet SurfelSet;
typedef SurfelSet::iterator SurfelSetIterator;
typedef BreadthFirstVisitor<MyDigitalSurface> Visitor;
/**
   Simple type to memorize a plane and associated information (a color
   here).
*/
struct SegmentedPlane {
  NaivePlaneComputer plane;
  Color color;
};
struct VertexSize {
  Vertex v;
  unsigned int size;
  inline VertexSize( const Vertex & aV, unsigned int aSize )
    : v( aV ), size( aSize )
  {}
};

inline
bool operator<( const VertexSize & vs1, const VertexSize & vs2 )
{
  return vs1.size < vs2.size;
}
//! [greedy-plane-segmentation-ex3-typedefs]

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  //! [greedy-plane-segmentation-ex3-parseCommandLine]
   trace.info() << "Segments the surface at given threshold within given volume into digital planes of rational width num/den." << std::endl;
  // Setting default options: ----------------------------------------------
  // input file used:
   string inputFilename =   examplesPath + "samples/Al.100.vol" ;
    trace.info() << "input file used " << inputFilename << std::endl;
  // parameter threshold
    unsigned int threshold = 0;
    trace.info() << "the value that defines the isosurface in the image (an integer between 0 and 255)= " << threshold<< std::endl;
   // parameter widthNum
   unsigned int widthNum = 1;
   trace.info() << "the numerator of the rational width (a non-null integer) =" << widthNum<< std::endl;
   // parameter widthDen
   unsigned int widthDen = 1;
   trace.info() << "the denominator of the rational width (a non-null integer)= " << widthDen<< std::endl;
  //! [greedy-plane-segmentation-ex3-parseCommandLine]

  //! [greedy-plane-segmentation-ex3-loadVolume]
  QApplication application(argc,argv);
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image, threshold,255);
  //! [greedy-plane-segmentation-ex3-loadVolume]

  //! [greedy-plane-segmentation-ex3-makeSurface]
  trace.beginBlock( "Set up digital surface." );
  // We initializes the cellular grid space used for defining the
  // digital surface.
  KSpace ks;
  bool ok = ks.init( set3d.domain().lowerBound(),
                     set3d.domain().upperBound(), true );
  if ( ! ok ) std::cerr << "[KSpace.init] Failed." << std::endl;
  SurfelAdjacency<KSpace::dimension> surfAdj( true ); // interior in all directions.
  MyDigitalSurfaceContainer* ptrSurfContainer =
    new MyDigitalSurfaceContainer( ks, set3d, surfAdj );
  MyDigitalSurface digSurf( ptrSurfContainer ); // acquired
  trace.endBlock();
  //! [greedy-plane-segmentation-ex3-makeSurface]

  //! [greedy-plane-segmentation-ex3-segment]
  Point p;
  Dimension axis;
  unsigned int j = 0;
  unsigned int nb = digSurf.size();

  // First pass to find biggest planes.
  trace.beginBlock( "1) Segmentation first pass. Computes all planes so as to sort vertices by the plane size." );
  std::map<Vertex,unsigned int> v2size;
  NaivePlaneComputer planeComputer;
  std::priority_queue<VertexSize> Q;
  std::vector<Point> layer;
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    {
      if ( ( (++j) % 50 == 0 ) || ( j == nb ) ) trace.progressBar( j, nb );
      Vertex v = *it;
      axis = ks.sOrthDir( v );
      planeComputer.init( axis, 500, widthNum, widthDen );
      // The visitor takes care of all the breadth-first traversal.
      Visitor visitor( digSurf, v );
      layer.clear();
      Visitor::Size currentSize = visitor.current().second;
      while ( ! visitor.finished() )
        {
          Visitor::Node node = visitor.current();
          v = node.first;
          axis = ks.sOrthDir( v );
          p = ks.sCoords( ks.sDirectIncident( v, axis ) );
          if ( node.second != currentSize )
            {
              // std::cerr << "Layer " << currentSize << ", size=" << layer.size() << std::endl;
              bool isExtended = planeComputer.extend( layer.begin(), layer.end() );
              if ( ! isExtended )
                break;
              layer.clear();
              currentSize = node.second;
            }
          layer.push_back( p );
          visitor.expand();
        }
      // std::cerr << v << " -> " << planeComputer.size() << std::endl;
      Q.push( VertexSize( v, planeComputer.size() ) );
    }
  trace.endBlock();

  trace.beginBlock( "2) Segmentation second pass. Visits vertices from the one with biggest plane to the one with smallest plane." );
  std::set<Vertex> processedVertices;
  std::map<Vertex,SegmentedPlane*> v2plane;
  std::vector<SegmentedPlane*> segmentedPlanes;
  j = 0;
  while ( ! Q.empty() )
    {
      if ( ( (++j) % 50 == 0 ) || ( j == nb ) ) trace.progressBar( j, nb );
      Vertex v = Q.top().v;
      Q.pop();
      if ( processedVertices.find( v ) != processedVertices.end() ) // already in set
        continue; // process to next vertex

      SegmentedPlane* ptrSegment = new SegmentedPlane;
      segmentedPlanes.push_back( ptrSegment ); // to delete them afterwards.
      axis = ks.sOrthDir( v );
      ptrSegment->plane.init( axis, 500, widthNum, widthDen );
      // The visitor takes care of all the breadth-first traversal.
      Visitor visitor( digSurf, v );
      while ( ! visitor.finished() )
        {
          Visitor::Node node = visitor.current();
          v = node.first;
          if ( processedVertices.find( v ) == processedVertices.end() )
            { // Vertex is not in processedVertices
              axis = ks.sOrthDir( v );
              p = ks.sCoords( ks.sDirectIncident( v, axis ) );
              bool isExtended = ptrSegment->plane.extend( p );
              if ( isExtended )
                { // surfel is in plane.
                  processedVertices.insert( v );
                  v2plane[ v ] = ptrSegment;
                  visitor.expand();
                }
              else // surfel is not in plane and should not be used in the visit.
                visitor.ignore();
            }
          else // surfel is already in some plane.
            visitor.ignore();
        }
      // Assign random color for each plane.
      ptrSegment->color = Color( rand() % 256, rand() % 256, rand() % 256, 255 );
    }
  trace.endBlock();
  //! [greedy-plane-segmentation-ex3-segment]

  //! [greedy-plane-segmentation-ex3-visualization]
  Viewer3D<> viewer( ks );
  viewer.show();
  Color col( 255, 255, 120 );
  for ( std::map<Vertex,SegmentedPlane*>::const_iterator
          it = v2plane.begin(), itE = v2plane.end();
        it != itE; ++it )
    {
      viewer << CustomColors3D( it->second->color, it->second->color );
      viewer << ks.unsigns( it->first );
    }
  viewer << Viewer3D<>::updateDisplay;
  //! [greedy-plane-segmentation-ex3-visualization]

  //! [greedy-plane-segmentation-ex3-freeMemory]
  for ( std::vector<SegmentedPlane*>::iterator
          it = segmentedPlanes.begin(), itE = segmentedPlanes.end();
        it != itE; ++it )
    delete *it;
  segmentedPlanes.clear();
  v2plane.clear();
  //! [greedy-plane-segmentation-ex3-freeMemory]

  return application.exec();
}
///////////////////////////////////////////////////////////////////////////////
