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
 * @file topology/digitalSurfaceSlice.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/29
 *
 * An example file named digitalSurfaceSlice.
 *
 * This file is part of the DGtal library.
 */

/**
 * Extracting 3D surface slice with  DigitalSurfaceTracker.
 * @see @ref  dgtal_helpsurf_sec2
 * @image html digitalSurfaceSlice.png  "Extraction of 2 surface slice associated to one surfel."
 * @example topology/digitalSurfaceSlice.cpp
 *
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

#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"

#include "ConfigExamples.h"

///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace DGtal;
using namespace Z3i;
///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  // for 3D display with Viewer3D
  QApplication application(argc,argv);

  //! [digitalSurfaceSlice-readVol]
  trace.beginBlock( "Reading vol file into an image." );
  typedef ImageSelector < Domain, int>::Type Image;
  std::string inputFilename = examplesPath + "samples/Al.100.vol";
  Image image = VolReader<Image>::importVol(inputFilename);
  DigitalSet set3d (image.domain());
  SetFromImage<DigitalSet>::append<Image>(set3d, image,
                                          0, 1 );
  Viewer3D<> viewer;
  viewer.show();
  trace.endBlock();
  //! [digitalSurfaceSlice-readVol]

  //! [digitalSurfaceSlice-KSpace]
  trace.beginBlock( "Construct the Khalimsky space from the image domain." );
  KSpace ks;
  bool space_ok = ks.init( image.domain().lowerBound(),
                           image.domain().upperBound(), true );
  if (!space_ok)
    {
      trace.error() << "Error in the Khamisky space construction."<<std::endl;
      return 2;
    }
  trace.endBlock();
  //! [digitalSurfaceSlice-KSpace]

  //! [digitalSurfaceSlice-SurfelAdjacency]
  typedef SurfelAdjacency<KSpace::dimension> MySurfelAdjacency;
  MySurfelAdjacency surfAdj( true ); // interior in all directions.
  //! [digitalSurfaceSlice-SurfelAdjacency]

  //! [digitalSurfaceSlice-ExtractingSurface]
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
  trace.info() << "Digital surface has " << digSurf.size() << " surfels."
               << std::endl;
  trace.endBlock();
  //! [digitalSurfaceSlice-ExtractingSurface]

  //! [digitalSurfaceSlice-ExtractingSlice]
  trace.beginBlock( "Extract slices." );
  typedef MyDigitalSurface::DigitalSurfaceTracker MyTracker;
  typedef DigitalSurface2DSlice< MyTracker > My2DSlice;
  //Extract an initial boundary cell
  Surfel surf = *digSurf.begin();
  MyTracker* tracker1 = digSurf.container().newTracker( surf );
  MyTracker* tracker2 = digSurf.container().newTracker( surf );
  // Extract the bondary contour associated to the initial surfel in
  // its first direction
  My2DSlice slice1( tracker1, *(ks.sDirs( surf )) );
  // Extract the bondary contour associated to the initial surfel in
  // its second direction
  My2DSlice slice2( tracker2, *++(ks.sDirs( surf )) );
  delete tracker1;
  delete tracker2;
  trace.endBlock();
  //! [digitalSurfaceSlice-ExtractingSlice]

  ASSERT( slice1.start() == slice1.begin() );
  ASSERT( slice1.cstart() == slice1.c() );
  ASSERT( *slice1.begin() == surf );
  ASSERT( *slice1.c() == surf );
  ASSERT( *slice1.start() == surf );
  ASSERT( *slice1.cstart() == surf );
  ASSERT( *slice1.rcstart() == surf );
  ASSERT( slice1.rcstart() == slice1.rc() );
  ASSERT( *slice1.rc() == surf );
  ASSERT( *(slice1.c()+1) == *(slice1.begin()+1) );
  ASSERT( *(slice1.rc()+1) == *(slice1.rbegin()) );

  //! [digitalSurfaceSlice-displayingAll]
  trace.beginBlock( "Display all with QGLViewer." );
  // Displaying all the surfels in transparent mode
  viewer << SetMode3D( surf.className(), "Transparent");
  for( MyDigitalSurface::ConstIterator it = theSetOfSurfels.begin(),
         it_end = theSetOfSurfels.end(); it != it_end; ++it )
    viewer<< *it;

  // Displaying First surfels cut with gradient colors.;
  GradientColorMap<int> cmap_grad( 0, slice1.size() );
  cmap_grad.addColor( Color( 50, 50, 255 ) );
  cmap_grad.addColor( Color( 255, 0, 0 ) );
  cmap_grad.addColor( Color( 255, 255, 10 ) );

  // Need to avoid surfel superposition (the surfel size in increased)
  viewer << Viewer3D<>::shiftSurfelVisu;
  viewer << SetMode3D( surf.className(), "");
  viewer.setFillColor(Color(180, 200, 25, 255));

  int d=0;
  for ( My2DSlice::ConstIterator it = slice1.begin(),
          it_end = slice1.end(); it != it_end; ++it )
    {
      Color col= cmap_grad(d);
      viewer.setFillColor(Color(col.red(),col.green() ,col.blue(), 255));
      viewer<< *it;
      d++;
    }

  GradientColorMap<int> cmap_grad2( 0, slice2.size() );
  cmap_grad2.addColor( Color( 50, 50, 255 ) );
  cmap_grad2.addColor( Color( 255, 0, 0 ) );
  cmap_grad2.addColor( Color( 255, 255, 10 ) );

  d=0;
  for ( My2DSlice::ConstIterator it = slice2.begin(),
          it_end = slice2.end(); it != it_end; ++it )
    {
      Color col= cmap_grad2(d);
      viewer.setFillColor(Color(col.red(),col.green() ,col.blue(), 255));
      viewer<< *it;
      d++;
    }

  // One need once again to avoid superposition.
  viewer << Viewer3D<>::shiftSurfelVisu;
  viewer.setFillColor(Color(18, 200, 25, 255));
  viewer << surf ;
  viewer << Viewer3D<>::updateDisplay;
  trace.endBlock();

  return application.exec();
  //! [digitalSurfaceSlice-displayingAll]
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
