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
 * @file geometry/volumes/distance/toricdomainvolumetric.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2016/10/17
 *
 * An example file named toricdomainvolumetric. The aim of this example
 * is to demonstrate the volumetric analysis functions on toric
 * domains.
 *
 * This file is part of the DGtal library.
 */


/**
   Example of a toric distance transform construction in dimension 2 for the
   Euclidean metric.

   @see \ref toricVol
   \example geometry/volumes/distance/toricdomainvolumetric.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/TickedColorMap.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/SimpleThresholdForegroundPredicate.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
int main()
{

  //! [DTDef]
  using namespace std;
  using namespace DGtal;
  using namespace Z2i;

  Point a ( 0, 0 );
  Point b ( 32, 16);

  //Input image with unsigned char values
  typedef ImageSelector<Domain, unsigned int>::Type Image;
  Image image ( Domain(a, b ));

  //We fill the image with the 128 value
  for ( Image::Iterator it = image.begin(), itend = image.end();it != itend; ++it)
    (*it)=128;

  //We add 3 seeds with 0 values.
  image.setValue(Point(16,2), 0);
  image.setValue(Point(2,11), 0);
  image.setValue(Point(30,15), 0);
  //! [DTDef]

  trace.beginBlock ( "Example toricdomainvolumetric" );
  //Input shape output
  typedef GrayscaleColorMap<Image::Value> Gray;
  Board2D board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Gray>(board, image, (unsigned int)0, (unsigned int)129);
  board.saveSVG("toric-inputShape.svg");

  //! [DTPredicate]
  //Point Predicate from random seed image
  typedef functors::SimpleThresholdForegroundPredicate<Image> PointPredicate;
  PointPredicate predicate(image,0);
  //! [DTPredicate]

  //! [DTComputeToric]
  typedef  DistanceTransformation<Space, PointPredicate, L2Metric> DTL2;
  typedef  DistanceTransformation<Space, PointPredicate, L2Metric> DTL2Toric;

  //Regular 2D domain
  DTL2 dtL2(image.domain(), predicate, l2Metric);
  //Full toric 2D domain
  DTL2Toric dtL2Toric(image.domain(), predicate, l2Metric, {{true, true}} );
  //! [DTComputeToric]

  //! [DTComputePartialToric]
  typedef  DistanceTransformation<Space, PointPredicate, L2Metric> DTL2ToricX;
  typedef  DistanceTransformation<Space, PointPredicate, L2Metric> DTL2ToricY;

  // 2D domain that is periodic along the first dimension.
  DTL2ToricX dtL2ToricX( image.domain(), predicate, l2Metric, {{true,  false}} );
  // 2D domain that is periodic along the second dimension.
  DTL2ToricY dtL2ToricY( image.domain(), predicate, l2Metric, {{false, true}} );
  //! [DTComputePartialToric]

  //We compute the maximum DT value on the L2 map
  const DTL2::Value       maxv2       = * (std::max_element(dtL2.constRange().begin(), dtL2.constRange().end()));
  const DTL2Toric::Value  maxvtoric   = * (std::max_element(dtL2Toric.constRange().begin(), dtL2Toric.constRange().end()));
  const DTL2ToricX::Value maxvtoricX  = * (std::max_element(dtL2ToricX.constRange().begin(), dtL2ToricX.constRange().end()));
  const DTL2ToricY::Value maxvtoricY  = * (std::max_element(dtL2ToricY.constRange().begin(), dtL2ToricY.constRange().end()));

  // Color map based on the maximal value for all maps (in order to compare results with similar colors).
  const auto maxvall = std::max( { maxv2, maxvtoric, maxvtoricX, maxvtoricY } );

  //! [DTColormaps]
  //Colormap used for the SVG output
  typedef HueShadeColorMap<DTL2::Value, 1> HueTwice;
  //! [DTColormaps]

  trace.warning() << "DT maxValue= " << maxv2 << endl;
  board.clear();
  Display2DFactory::drawImage<HueTwice>(board, dtL2, 0.0, maxvall + 1);
  board.saveSVG ( "toric-example-DT-L2.svg" );

  trace.warning() <<  "Full toric maxValue= " << maxvtoric << endl;
  board.clear();
  Display2DFactory::drawImage<HueTwice>(board, dtL2Toric, 0.0, maxvall + 1);
  board.saveSVG ( "toric-example-DT-L2-toric.svg" );

  trace.warning() <<  "1th dimension periodic maxValue= " << maxvtoricX << endl;
  board.clear();
  Display2DFactory::drawImage<HueTwice>(board, dtL2ToricX, 0.0, maxvall + 1);
  board.saveSVG ( "toric-example-DT-L2-toricX.svg" );

  trace.warning() <<  "2nd dimension periodic maxValue= " << maxvtoricY << endl;
  board.clear();
  Display2DFactory::drawImage<HueTwice>(board, dtL2ToricY, 0.0, maxvall + 1);
  board.saveSVG ( "toric-example-DT-L2-toricY.svg" );

  //Explicit export with ticked colormap
  //We compute the maximum DT value on the L2 map
  TickedColorMap<double, GradientColorMap<double> > ticked(0.0,maxv2, Color::White);
  ticked.addRegularTicks(3, 0.5);
  ticked.finalize();
  ticked.colormap()->addColor( Color::Red );
  ticked.colormap()->addColor( Color::Black );
  board.clear();
  for ( auto it = dtL2.domain().begin(), itend = dtL2.domain().end();it != itend; ++it)
  {
    board<< CustomStyle((*it).className(),new CustomColors(ticked(dtL2(*it)),ticked(dtL2(*it))));
    board << *it;
  }
  board.saveSVG("toric-example-DT-L2-ticked.svg");

  board.clear();
  for ( auto it = dtL2Toric.domain().begin(), itend = dtL2Toric.domain().end();it != itend; ++it)
  {
    board<< CustomStyle((*it).className(),new CustomColors(ticked(dtL2Toric(*it)),ticked(dtL2Toric(*it))));
    board << *it;
  }
  board.saveSVG("toric-example-DT-L2-ticked-toric.svg");

  board.clear();
  for ( auto it = dtL2ToricX.domain().begin(), itend = dtL2ToricX.domain().end();it != itend; ++it)
  {
    board<< CustomStyle((*it).className(),new CustomColors(ticked(dtL2ToricX(*it)),ticked(dtL2ToricX(*it))));
    board << *it;
  }
  board.saveSVG("toric-example-DT-L2-ticked-toricX.svg");

  board.clear();
  for ( auto it = dtL2ToricY.domain().begin(), itend = dtL2ToricY.domain().end();it != itend; ++it)
  {
    board<< CustomStyle((*it).className(),new CustomColors(ticked(dtL2ToricY(*it)),ticked(dtL2ToricY(*it))));
    board << *it;
  }
  board.saveSVG("toric-example-DT-L2-ticked-toricY.svg");

  //Voronoi vector output
  board.clear();
  board << dtL2.domain();
  for ( auto it = dtL2.domain().begin(), itend = dtL2.domain().end();it != itend; ++it)
    if ( dtL2.getVoronoiVector(*it) != *it )
      Display2DFactory::draw(board,dtL2.getVoronoiVector(*it) - (*it), (*it));
  board.saveSVG("toric-example-Voro-L2.svg");

  board.clear();
  board << dtL2Toric.domain();
  for ( auto it = dtL2Toric.domain().begin(), itend = dtL2Toric.domain().end();it != itend; ++it)
    if ( dtL2Toric.getVoronoiVector(*it) != *it )
      Display2DFactory::draw(board, dtL2Toric.getVoronoiVector(*it) - (*it), (*it));
  board.saveSVG("toric-example-Voro-L2-toric.svg");

  board.clear();
  board << dtL2Toric.domain();
  for ( auto it = dtL2Toric.domain().begin(), itend = dtL2Toric.domain().end();it != itend; ++it)
    if ( dtL2Toric.getVoronoiVector(*it) != *it )
      Display2DFactory::draw(board, dtL2Toric.projectPoint(dtL2Toric.getVoronoiVector(*it)) - (*it), (*it));
  board.saveSVG("toric-example-Voro-L2-toric-projected.svg");

  board.clear();
  board << dtL2ToricX.domain();
  for ( auto it = dtL2ToricX.domain().begin(), itend = dtL2ToricX.domain().end();it != itend; ++it)
    if ( dtL2ToricX.getVoronoiVector(*it) != *it )
      Display2DFactory::draw(board, dtL2ToricX.getVoronoiVector(*it) - (*it), (*it));
  board.saveSVG("toric-example-Voro-L2-toricX.svg");

  board.clear();
  board << dtL2ToricY.domain();
  for ( auto it = dtL2ToricY.domain().begin(), itend = dtL2ToricY.domain().end();it != itend; ++it)
    if ( dtL2ToricY.getVoronoiVector(*it) != *it )
      Display2DFactory::draw(board, dtL2ToricY.getVoronoiVector(*it) - (*it), (*it));
  board.saveSVG("toric-example-Voro-L2-toricY.svg");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
