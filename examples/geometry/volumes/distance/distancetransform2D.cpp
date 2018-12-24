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
 * @file geometry/volumes/distance/distancetransform2D.cpp
 * @ingroup Examples
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/11/28
 *
 * An example file named distancetransform2D. The aim of this example
 * is to demonstrate the distance transformation package of the DGtal
 * library. Using a simple random seed example, we compute the
 * distance transformation (linear in time algorithm) using the L1,
 * Linfinity and L2 metrics.
 *
 * This file is part of the DGtal library.
 */


/**
   Example of distance transformation in dimension 2.

   @see \ref moduleVolumetric
   \image  html  example-DT-L2.png "Distance transform with L2 norm."
   \example geometry/volumes/distance/distancetransform2D.cpp
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

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

/** 
 * Set to a given value a random set of @a nb points.
 * 
 * @param image the  image
 * @param nb the number of random points to insert
 * @param value the value to add at each random point
 */
template<typename Image>
void randomSeeds(Image &image, const unsigned int nb, const int value)
{
  typename Image::Point p, low = image.domain().lowerBound();
  typename Image::Vector ext;

  ext = image.extent();

  for (unsigned int k = 0 ; k < nb; k++)
  {
    for (unsigned int dim = 0; dim < Image::dimension; dim++)
      p[dim] = rand() % (ext[dim]) +  low[dim];
    
    image.setValue(p, value);
  }
}

int main()
{
  trace.beginBlock ( "Example distancetransform2D" );

  //! [DTDef]
  Z2i::Point a ( 0, 0 );
  Z2i::Point b ( 127, 127);
  
  //Input image with unsigned char values
  typedef ImageSelector<Z2i::Domain, unsigned int>::Type Image;
  Image image ( Z2i::Domain(a, b ));

  //We fill the image with the 128 value
  for ( Image::Iterator it = image.begin(), itend = image.end();it != itend; ++it)
    (*it)=128;
  //We generate 16 seeds with 0 values.
  randomSeeds(image,16,0);
  //! [DTDef]

  //Input shape output
  typedef GrayscaleColorMap<Image::Value> Gray;
  Board2D board;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Gray>(board, image, (unsigned int)0, (unsigned int)129);
  board.saveSVG("inputShape.svg");

  //! [DTPredicate]
  //Point Predicate from random seed image
  typedef functors::SimpleThresholdForegroundPredicate<Image> PointPredicate;
  PointPredicate predicate(image,0);
  //! [DTPredicate]  

  //! [DTCompute]
  typedef  DistanceTransformation<Z2i::Space, PointPredicate, Z2i::L2Metric> DTL2;
  typedef  DistanceTransformation<Z2i::Space, PointPredicate, Z2i::L1Metric> DTL1;
 
 
  DTL2 dtL2(image.domain(), predicate, Z2i::l2Metric);
  DTL1 dtL1(image.domain(), predicate, Z2i::l1Metric);
  //! [DTCompute]


  DTL2::Value maxv2=0;
  //We compute the maximum DT value on the L2 map
  for ( DTL2::ConstRange::ConstIterator it = dtL2.constRange().begin(), itend = dtL2.constRange().end();it != itend; ++it)
    if ( (*it) > maxv2)  maxv2 = (*it);
 
  DTL1::Value maxv1=0;
  //We compute the maximum DT value on the L1 map
  for ( DTL1::ConstRange::ConstIterator it = dtL1.constRange().begin(), itend = dtL1.constRange().end();it != itend; ++it)
    if ( (*it) > maxv1)  maxv1 = (*it);
  
  //! [DTColormaps]
  //Colormap used for the SVG output
  typedef HueShadeColorMap<DTL2::Value, 2> HueTwice;
  //! [DTColormaps]


  
  
  trace.warning() << dtL2 << " maxValue= "<<maxv2<< endl;
  board.clear();
  Display2DFactory::drawImage<HueTwice>(board, dtL2, 0.0, maxv2 + 1);
  board.saveSVG ( "example-DT-L2.svg" );

  trace.warning() << dtL1 << " maxValue= "<<maxv1<< endl;
  board.clear();
  Display2DFactory::drawImage<HueTwice>(board, dtL1, 0.0, maxv1 + 1);
  board.saveSVG ( "example-DT-L1.svg" );

  //Explicit export with ticked colormap
  //We compute the maximum DT value on the L2 map
  board.clear();
  TickedColorMap<double, GradientColorMap<double> > ticked(0.0,maxv2, Color::White);
  ticked.addRegularTicks(5, 0.5);
  ticked.finalize();
  ticked.colormap()->addColor( Color::Red );
  ticked.colormap()->addColor( Color::Black );
  for ( DTL2::Domain::ConstIterator it = dtL2.domain().begin(), itend = dtL2.domain().end();it != itend; ++it)
  {
    board<< CustomStyle((*it).className(),new CustomColors(ticked(dtL2(*it)),ticked(dtL2(*it))));
    board << *it;
  }
  board.saveSVG("example-DT-L2-ticked.svg");
  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
