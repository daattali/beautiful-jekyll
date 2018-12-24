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
 * @file images/exampleConstImageAdapter.cpp
 * @ingroup Examples
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/12/4
 *
 * @brief An example file for ConstImageAdapter.
 *
 * This file is part of the DGtal library.
 */

/**
 *  Example of ConstImageAdapter.
   @see @ref constimage
   \image html logImage.png " 16x16 image: (1,1) to (16,16) adapted from with a log scale functor." 
 *  \example images/exampleConstImageAdapter.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"

#include "DGtal/io/boards/Board2D.h"

//! [include]
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"

#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ConstImageAdapter.h"
//! [include]

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
///////////////////////////////////////////////////////////////////////////////


//! [LogScaleFunctor]
template <typename Scalar>
struct LogScaleFunctor {

  LogScaleFunctor() {};
  double operator()(const Scalar &a) const
  {
    return std::log( 1 + NumberTraits<Scalar>::castToDouble(a) );
  }
  
};
//! [LogScaleFunctor]


int main( /*int argc, char** argv*/ )
{
  using namespace Z2i;
  
  Board2D aBoard;
  
//! [def]
  typedef HueShadeColorMap<unsigned char> HueShade;     // a simple HueShadeColorMap varying on 'unsigned char' values
  typedef HueShadeColorMap<double> HueShadeDouble;      // a simple HueShadeColorMap varying on 'double' values
  typedef GrayscaleColorMap<unsigned char> Gray;        // a simple GrayscaleColorMap varying on 'unsigned char' values
  
  functors::Identity df;                                    // a simple functor that just returns its argument
//! [def]

  trace.beginBlock("image");

//! [image_creation]
  typedef ImageContainerBySTLVector<Domain, unsigned char> Image;
  Domain domain(Point(1,1), Point(16,16));
  Image image(domain);
//! [image_creation]

//! [image_filling]
  unsigned char i = 0;
  for (Image::Iterator it = image.begin(); it != image.end(); ++it)
      *it = i++;
//! [image_filling]
  
  aBoard.clear();
  Display2DFactory::drawImage<HueShade>(aBoard, image, (unsigned char)0, (unsigned char)255);
  aBoard.saveSVG("image.svg");
  
  trace.endBlock();
  
  trace.beginBlock("subImage");
  
//! [ConstImageAdapterForSubImage_creation]
  typedef ConstImageAdapter<Image, Domain, functors::Identity, Image::Value, functors::Identity > ConstImageAdapterForSubImage;
  Domain subDomain(Point(1,1), Point(8,8));
  ConstImageAdapterForSubImage subImage(image, subDomain, df, df);
//! [ConstImageAdapterForSubImage_creation]
  
  aBoard.clear();
  Display2DFactory::drawImage<HueShade>(aBoard, subImage, (unsigned char)0, (unsigned char)255);
  aBoard.saveSVG("subImage.svg");
    
  trace.endBlock();
  
  trace.beginBlock("specificImage");
  
//! [specificDomain_creation]
  DigitalSet set(domain);
  for( unsigned int y=0; y < 17; y++)
    for( unsigned int x=0; x < 17; x++)
        if ((x%2) && (y%2))
          set.insertNew(Point(x,y));
        
  DigitalSetDomain<DigitalSet> specificDomain(set);
//! [specificDomain_creation]

//! [ConstImageAdapterForSpecificImage_creation]
  typedef ConstImageAdapter<Image, DigitalSetDomain<DigitalSet>, functors::Identity, Image::Value, functors::Identity > ConstImageAdapterForSpecificImage;
  ConstImageAdapterForSpecificImage specificImage(image, specificDomain, df, df);
//! [ConstImageAdapterForSpecificImage_creation]
  
  aBoard.clear();
  Display2DFactory::drawImage<HueShade>(aBoard, specificImage, (unsigned char)0, (unsigned char)255);
  aBoard.saveSVG("specificImage.svg");
    
  trace.endBlock();
  
  trace.beginBlock("thresholderImage");
  
//! [ConstImageAdapterForThresholderImage_creation]
  typedef ConstImageAdapter<Image, Domain, functors::Identity, bool, DGtal::functors::Thresholder<Image::Value> > ConstImageAdapterForThresholderImage;
  DGtal::functors::Thresholder<Image::Value> t(127);
  ConstImageAdapterForThresholderImage thresholderImage(image, domain, df, t);
//! [ConstImageAdapterForThresholderImage_creation]
  
  aBoard.clear();
  Display2DFactory::drawImage<Gray>(aBoard, thresholderImage, (unsigned char)0, (unsigned char)1);
  aBoard.saveSVG("thresholderImage.svg");
    
  trace.endBlock();
  
  trace.beginBlock("logImage");
  
//! [ConstImageAdapterForLogScale_creation]
  typedef ConstImageAdapter<Image, Domain, functors::Identity, double, LogScaleFunctor<Image::Value> > ConstImageAdapterForLogScale;
  LogScaleFunctor<Image::Value> logScale;
  ConstImageAdapterForLogScale logImage(image, domain, df, logScale);
//! [ConstImageAdapterForLogScale_creation]
  
  aBoard.clear();
  Display2DFactory::drawImage<HueShadeDouble>(aBoard, logImage, 0.0, logScale(255));
  aBoard.saveSVG("logImage.svg");
    
  trace.endBlock();
  
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
