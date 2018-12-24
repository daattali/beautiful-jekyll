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
 * @file testMagickReader.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2018/01/30
 *
 * Functions for testing class MagickReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/readers/MagickReader.h"
#include "DGtal/io/boards/Board2D.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MagickReader.
////////////////////////////////////////////////////////////////
///////////////

struct Color2Gray{
  Color2Gray(){}
  unsigned char operator()(const Color &c) const
  {
    return (c.red() + c.green() + c.blue())%256;
  }
};

TEST_CASE( "Magick Reader" )
{
  SECTION("Color->grayscale")
  {
    //Default image selector = STLVector
    typedef ImageSelector<Z2i::Domain, unsigned char>::Type Image;
    
    std::string filename = testPath + "samples/color64.png";
    
    trace.info()<<"Importing: "<<filename<<endl;
    
    MagickReader<Image, Color2Gray> reader;
    Image img = reader.importImage( filename , Color2Gray());
    
    Board2D board;
    typedef HueShadeColorMap<unsigned char,2> HueTwice;
    
    board.setUnit(LibBoard::Board::UCentimeter);
    Display2DFactory::drawImage<HueTwice>(board, img, (unsigned char)0, (unsigned char)255);
    board.saveSVG("testMagick-export.svg");
    
    REQUIRE(img.isValid());
    REQUIRE(img.extent() == Z2i::Vector(64,64));
  }
  
  SECTION("Color->Color")
  {
    typedef ImageSelector<Z2i::Domain, Color>::Type ImageColor;
    
    std::string filename = testPath + "samples/color64.png";
    
    trace.info()<<"Importing: "<<filename<<endl;
    
    MagickReader<ImageColor> reader;
    ImageColor img = reader.importImage( filename );
    
    Color a = img( Z2i::Point(1,1));
    CAPTURE( a );
    img.setValue( Z2i::Point(1,1), Color(13,13,13));
    a = img( Z2i::Point(1,1));
    CAPTURE( a );
    
    REQUIRE(img.isValid());
    REQUIRE(img.extent() == Z2i::Vector(64,64));
  }
}

