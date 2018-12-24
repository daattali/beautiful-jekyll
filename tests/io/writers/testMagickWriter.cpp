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
 * @file testMagickWriter.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2017/12/30
 *
 * Functions for testing class MagickWriter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/writers/MagickWriter.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;
///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MagickWriter.
///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing MagickWriter" )
{
  //Create an image 
  Domain domain(Point(0,0), Point(64,48));
  typedef ImageContainerBySTLVector<Domain, unsigned char> Image;
  Image image(domain);
  unsigned char t=0;
  for(auto p: image.domain())
  {
    image.setValue(p, t);
    t =  ((int)t + 1)%255;
  }
  HueShadeColorMap<unsigned char,2>  cmap(0,255);
  
  SECTION("Testing feature io/writers/ of MagickWriter")
    {
      REQUIRE(( MagickWriter<Image,HueShadeColorMap<unsigned char,2>>::exportMagick("magickwriter.png", image, cmap ) ));
      REQUIRE(( MagickWriter<Image,HueShadeColorMap<unsigned char,2>>::exportMagick("magickwriter.jpg", image, cmap ) ));
      REQUIRE(( MagickWriter<Image,HueShadeColorMap<unsigned char,2>>::exportMagick("magickwriter.gif", image, cmap ) ));
      REQUIRE(( MagickWriter<Image,HueShadeColorMap<unsigned char,2>>::exportMagick("magickwriter.bmp", image, cmap ) ));
    }
}

/** @ingroup Tests **/
