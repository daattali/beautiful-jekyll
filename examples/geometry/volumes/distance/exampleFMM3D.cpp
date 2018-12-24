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
 * @file geometry/volumes/distance/exampleFMM3D.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/23
 *
 * @brief The aim of this example
 * is to use the FMM (fast marching method) class
 * in order to incrementally compute a signed distance
 * field from a digital surface. The resulting field
 * is visualized with QGLViewer
 *
 * This file is part of the DGtal library.
 */

/**
   Example of use the FMM (fast marching method) class in 3D.
@see \ref moduleFMM

This program outputs this image:
@image html exampleFMM3D.png

\example geometry/volumes/distance/exampleFMM3D.cpp
*/



#include <iostream>

#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "ConfigExamples.h"
#include "DGtal/io/viewers/Viewer3D.h"


using namespace std;
using namespace DGtal;
using namespace Z3i;


//image
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/kernel/BasicPointPredicates.h"

//frontier
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/helpers/FrontierPredicate.h"
#include "DGtal/topology/LightExplicitDigitalSurface.h"

// FMM
#include "DGtal/geometry/volumes/distance/FMM.h"

// Standard services - public :
int main( int argc, char** argv )
{


  //Parse options
  //threshold
  int t =0;
  //width
  double maximalDistance = 3.0;


  //////////////////////////////////////////////////////////////////////////////////
  // image binarization and surface extraction
  //types
  typedef ImageContainerBySTLVector<Domain,short int> LabelImage;
  typedef ConstImageAdapter<LabelImage, Domain, functors::Identity, bool, DGtal::functors::Thresholder<LabelImage::Value> > BinaryImage;
  typedef functors::FrontierPredicate<KSpace, BinaryImage> SurfelPredicate;
  typedef LightExplicitDigitalSurface<KSpace, SurfelPredicate> Frontier;

  //reading image
  std::string imageFileName = examplesPath + "samples/Al.100.vol";

  trace.emphase() << imageFileName <<std::endl;
  DGtal::trace.beginBlock("image reading...");
  LabelImage labelImage = VolReader<LabelImage>::importVol( imageFileName);
  DGtal::trace.endBlock();

  DGtal::trace.beginBlock("binarization...");

  functors::Identity g;
  DGtal::functors::Thresholder<LabelImage::Value> thresholder( t );
  BinaryImage binaryImage(labelImage, labelImage.domain(), g, thresholder);
  trace.info() << "threshold: "
         << t
         << std::endl;

  //space and starting bel
  KSpace ks;
  Domain domain = labelImage.domain();
  ks.init( domain.lowerBound(), domain.upperBound(), true );
  KSpace::SCell bel;

  try {
    //getting a bel
    bel = Surfaces<KSpace>::findABel( ks, binaryImage, domain.size() );

    trace.info() << "starting bel: "
     << bel
     << std::endl;

  } catch (DGtal::InputException i) {
    trace.emphase() << "starting bel not found" << std::endl;
    return 0;
  }

  //implicit frontier
  functors::SCellToIncidentPoints<KSpace> functor( ks );
  std::pair<Point,Point> bpair = functor(bel);
  SurfelPredicate surfelPredicate( ks, binaryImage,
           binaryImage( bpair.first ),
           binaryImage( bpair.second ) );
  Frontier frontier( ks, surfelPredicate,
         SurfelAdjacency<KSpace::dimension>( true ), bel );

  DGtal::trace.endBlock();

  //////////////////////////////////////////////////////////////////////////////////
  /// FMM types
  //! [FMMSimpleTypeDef3D]
  typedef ImageContainerBySTLMap<Domain,double> DistanceImage;
  typedef DigitalSetFromMap<DistanceImage> AcceptedPointSet;
  typedef Domain::Predicate DomainPredicate;
  typedef FMM<DistanceImage, AcceptedPointSet, DomainPredicate > FMM;
  //! [FMMSimpleTypeDef3D]

  DGtal::trace.beginBlock("FMM...");

  /// FMM init
  //! [FMMSimpleInit3D]
  DistanceImage imageDistance( domain, 0.0 );
  AcceptedPointSet initialPointSet( imageDistance );
  FMM::initFromBelsRange( ks, frontier.begin(), frontier.end(),
        imageDistance, initialPointSet, 0.5 );
  //! [FMMSimpleInit3D]

  /// FMM main
  //! [FMMUsage3D]
  FMM fmm( imageDistance, initialPointSet, domain.predicate(),
     domain.size(), maximalDistance );
  fmm.compute();
  trace.info() << fmm << std::endl;
  //! [FMMUsage3D]

  DGtal::trace.endBlock();

  //////////////////////////////////////////////////////////////////////////////////
  //visualisation
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();

  //
  GradientColorMap<double> colorMap( 0, 2*maximalDistance );
  colorMap.addColor( Color( 255, 0, 0 ) );
  colorMap.addColor( Color( 0, 250, 0 ) );
  for (DistanceImage::const_iterator it = imageDistance.begin(), itEnd = imageDistance.end();
       it != itEnd; ++it)
    {
      Point p = it->first;
      viewer << CustomColors3D( colorMap(it->second), colorMap(it->second) ) ;
      viewer << p;
    }
  Point p = Point::diagonal(1);
  Vector extent =  (domain.upperBound() - domain.lowerBound()) + p;
  double a = -extent[0]/2, b = extent[1]/2;
  double c = 0, mu = (a+b);
  trace.info() << "clipping plane ("
         << a << ", " << b << ", " << c << ", " << mu << ")"
         << std::endl;
  viewer << CustomColors3D(Color(200, 200, 200, 100),Color(200, 200,200, 20));
  viewer << ClippingPlane(a,b,c,mu);

  viewer << Viewer3D<>::updateDisplay;
  return application.exec();
}
//                                                                           //
