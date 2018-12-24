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
 * @file geometry/curves/exampleGridCurve3d-2.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/03
 *
 * An example file for GridCurve, defined as a sequence of 2-scells, in a 3d Khalimsky space.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows how to use GridCurve as a sequence of 2-scells in a 3d Khalimsky space. 

@verbatim
$ ./examples/geometry/curves/exampleGridCurve3d-2
@endverbatim

Note that the data type you want to display may be passed as argument as follows: 
@verbatim
$ ./examples/geometry/curves/exampleGridCurve3d-2 gridcurve
@endverbatim

This command line produces the following output: 

@image html exampleGridCurveCat.png "Slice of a digital surface"
@image latex exampleGridCurveCat.png "Slice of a digital surface"


@see \ref moduleGridCurveAnalysis

\example geometry/curves/exampleGridCurve3d-2.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/topology/SetOfSurfels.h"
#include "DGtal/topology/DigitalSurface2DSlice.h"
#include "DGtal/topology/helpers/Surfaces.h"

#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/kernel/sets/DigitalSetInserter.h"
#include "DGtal/io/Color.h"

#include "DGtal/geometry/curves/GridCurve.h"

#include "ConfigExamples.h"



///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace DGtal;
using namespace Z3i;
///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  trace.info() << "exampleGridCurve3d-2: the type of data to be displayed "
	       << "may be given as argument as follows: "
	       << argv[0] << " inner" << endl; 
  trace.info() << "Available types are: gridcurve (default), inner, outer, incident" << endl;

  string type = (argc > 1) ? string(argv[1]) : "gridcurve";
  trace.info() << "Chosen type: " << type << endl; 

  //vol reading and digital set construction
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  std::string inputFilename = examplesPath + "samples/cat10.vol";
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  setFromImage( image, DigitalSetInserter<DigitalSet>(set3d), 1);
  trace.info() << set3d.size() << " voxels." << std::endl;
  trace.endBlock();

  //Khalimsky space construction
  trace.beginBlock( "Construct the Khalimsky space from the image domain." );
  KSpace ks;
  trace.endBlock();

  //digital surface construction
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.

  trace.beginBlock( "Extracting boundary by scanning the space. " );
  typedef KSpace::Surfel Surfel;
  typedef KSpace::SurfelSet SurfelSet;
  typedef SetOfSurfels< KSpace, SurfelSet > MySetOfSurfels;
  typedef DigitalSurface< MySetOfSurfels > MyDigitalSurface;
  MySetOfSurfels theSetOfSurfels( ks, surfAdj );
  Surfaces<KSpace>::sMakeBoundary( theSetOfSurfels.surfelSet(),
                                   ks, set3d,
                                   image.domain().lowerBound(),
                                   image.domain().upperBound() );
  MyDigitalSurface digSurf( theSetOfSurfels );
  trace.info() << digSurf.size() << " surfels." << std::endl;
  trace.endBlock();

  //slice retrieving
  trace.beginBlock( "Extracting slice and constructing a grid curve. " );
  typedef MyDigitalSurface::DigitalSurfaceTracker MyTracker;
  typedef DigitalSurface2DSlice< MyTracker > My2DSlice;

  //Extract an initial boundary cell
  Surfel surf = *digSurf.begin();
  MyTracker* tracker = digSurf.container().newTracker( surf );

  // Extract the bondary contour associated to the initial surfel in
  // its first direction
  My2DSlice slice( tracker, *(ks.sDirs( surf )) );
  delete tracker;

  //! [exampleGridCurve3d-Construction]
  GridCurve<KSpace> gc(ks);
  gc.initFromSCellsRange( slice.begin(), slice.end() );
  //! [exampleGridCurve3d-Construction]

  trace.endBlock();


  // for 3D display with Viewer3D
  QApplication application(argc,argv);
  trace.beginBlock( "Display all with QGLViewer." );
  Viewer3D<Space, KSpace> viewer(ks);
  viewer.show();
  // Displaying all the surfels in transparent mode
  viewer << SetMode3D( surf.className(), "Transparent");
  for( MyDigitalSurface::ConstIterator it = theSetOfSurfels.begin(),
         it_end = theSetOfSurfels.end(); it != it_end; ++it )
    viewer<< *it;


  // Displaying slice
  viewer << Viewer3D<Space, KSpace>::shiftSurfelVisu;
  viewer << SetMode3D( surf.className(), "");
  viewer.setFillColor( Color( 50, 50, 255 ) );

  if (type == "gridcurve")
    {
      viewer  << gc;
    }
  else if (type == "inner")
    {
      viewer << gc.getInnerPointsRange();
    }
  else if (type == "outer")
    {
      viewer << gc.getOuterPointsRange();
    }
  else if (type == "incident")
    {
      viewer << gc.getIncidentPointsRange();
    }
  else
    {
      trace.info() << "Display type not known." << std::endl;
    }

  viewer << Viewer3D<Space, KSpace>::updateDisplay;
  trace.endBlock();

  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
