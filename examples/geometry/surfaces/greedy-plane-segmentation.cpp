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
 * @file geometry/surfaces/greedy-plane-segmentation.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/10/01
 *
 * An example file named greedy-plane-segmentation.
 *
 * This file is part of the DGtal library.
 */


/**
   This example shows a greedy segmentation into naive planes of the surface at threshold 0 within volume Al.100.vol.

   Colors for each plane are chosen randomly. Surfels in the same plane have the same color.

@see \ref moduleCOBANaivePlaneRecognition_sec5

@verbatim
# naive plane: width=1/1
$ ./examples/geometry/surfaces/greedy-plane-segmentation -i ./examples/samples/Al.100.vol -t 0 -w 1 -d 1
@endverbatim

@image html greedy-plane-segmentation-al-w1.png "Greedy segmentation of Al capone into naive planes."
@image latex greedy-plane-segmentation-al-w1.png "Greedy segmentation of Al capone into naive planes." width=6cm

\example geometry/surfaces/greedy-plane-segmentation.cpp
*/
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iostream>

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


//! [greedy-plane-segmentation-typedefs]
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
//! [greedy-plane-segmentation-typedefs]

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{

  //! [greedy-plane-segmentation-parseCommandLine]
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

  //! [greedy-plane-segmentation-parseCommandLine]

  //! [greedy-plane-segmentation-loadVolume]
  QApplication application(argc,argv);
  typedef ImageSelector < Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image, threshold,255);
  //! [greedy-plane-segmentation-loadVolume]

  //! [greedy-plane-segmentation-makeSurface]
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
  //! [greedy-plane-segmentation-makeSurface]

  //! [greedy-plane-segmentation-segment]
  trace.beginBlock( "Segment into planes." );
  std::set<Vertex> processedVertices;
  std::vector<SegmentedPlane*> segmentedPlanes;
  std::map<Vertex,SegmentedPlane*> v2plane;
  Point p;
  Dimension axis;
  unsigned int j = 0;
  unsigned int nb = digSurf.size();
  for ( ConstIterator it = digSurf.begin(), itE= digSurf.end(); it != itE; ++it )
    {
      if ( ( (++j) % 50 == 0 ) || ( j == nb ) ) trace.progressBar( j, nb );
      Vertex v = *it;
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
  //! [greedy-plane-segmentation-segment]

  //! [greedy-plane-segmentation-visualization]
  Viewer3D<> viewer( ks );
  viewer.show();
  for ( std::map<Vertex,SegmentedPlane*>::const_iterator
          it = v2plane.begin(), itE = v2plane.end();
        it != itE; ++it )
    {
      viewer << CustomColors3D( it->second->color, it->second->color );
      viewer << ks.unsigns( it->first );
    }
  viewer << Viewer3D<>::updateDisplay;
  //! [greedy-plane-segmentation-visualization]

  //! [greedy-plane-segmentation-freeMemory]
  for ( std::vector<SegmentedPlane*>::iterator
          it = segmentedPlanes.begin(), itE = segmentedPlanes.end();
        it != itE; ++it )
    delete *it;
  segmentedPlanes.clear();
  v2plane.clear();
  //! [greedy-plane-segmentation-freeMemory]

  return application.exec();
}
///////////////////////////////////////////////////////////////////////////////
