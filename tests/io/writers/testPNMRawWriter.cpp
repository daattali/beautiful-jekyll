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
 * @file
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/22
 *
 * Functions for testing class PNMWriter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/ColorBrightnessColorMap.h"
#include "DGtal/io/colormaps/RandomColorMap.h"
#include "DGtal/io/colormaps/BasicColorToScalarFunctors.h"
#include "DGtal/base/BasicFunctors.h"

#include "DGtal/io/writers/PGMWriter.h"
#include "DGtal/io/writers/PPMWriter.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/writers/RawWriter.h"
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class PNMWriter.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testPNMWriter()
{
  
  trace.beginBlock ( "Testing block ..." );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;
  typedef HueShadeColorMap<unsigned char> Hue;
  typedef HueShadeColorMap<unsigned char,2> HueTwice;
  typedef GrayscaleColorMap<unsigned char> Gray;
  // Gradient using the "Jet" preset.
  typedef GradientColorMap<unsigned char, CMAP_JET > Jet;
  // Gradient from black to red.
  const int BlackColor = DGTAL_RGB2INT(0,0,0);
  const int RedColor = DGTAL_RGB2INT(255,0,0);
  typedef GradientColorMap< unsigned char, CMAP_CUSTOM, BlackColor, RedColor > RedShade1;
  // Gradient from black to red, using a ColorBrightnessColorMap.
  typedef ColorBrightnessColorMap< unsigned char, RedColor > RedShade2;

  Point a ( 1, 1);
  Point b ( 16, 16);
  typedef ImageSelector<Domain, unsigned char>::Type Image;
  Image image(Domain(a,b));
  for(unsigned int i=0 ; i < 256; i++)
    image[i] = i;

  PPMWriter<Image,Hue>::exportPPM("export-hue.ppm",image, Hue(0,255) );
  PPMWriter<Image,HueTwice>::exportPPM("export-hue-twice.ppm",image,HueTwice(0,255));
  PGMWriter<Image>::exportPGM("export-hue-twice.pgm",image);
  PPMWriter<Image,Gray>::exportPPM("export-gray.ppm",image, Gray(0,255));
  PPMWriter<Image,Jet>::exportPPM("export-jet.ppm",image,Jet(0,255));
  PPMWriter<Image,RedShade1>::exportPPM("export-red1.ppm",image,RedShade1(0,255));
  PPMWriter<Image,RedShade2>::exportPPM("export-red2.ppm",image,RedShade2(0,255));

  //TestingFunctor
  typedef DGtal::functors::Composer< Jet, functors::RedChannel, unsigned char> RedFunctor;
  RedFunctor redFunctor( Jet(0,255), functors::RedChannel() ) ;
  PGMWriter<Image, RedFunctor>::exportPGM("export-jet-red.pgm",image, redFunctor);
  

  //test Raw export
  RawWriter<Image>::exportRaw8("export-hue-twice.raw",image);

  //test Image export with libboard
  Board2D  board;
  board.setUnit(LibBoard::Board::UCentimeter);
  Display2DFactory::drawImage<HueTwice>(board, image, (unsigned char)0, (unsigned char)255);
  board.saveSVG("export-hue-twice.svg");

  trace.endBlock();
  
  return true;
}


bool testRWIssue254()
{
   trace.beginBlock ( "Testing R/W on PPM Writer (issue 254) ..." );

  typedef SpaceND<2> TSpace;
  typedef TSpace::Point Point;
  typedef HyperRectDomain<TSpace> Domain;

  Point a ( 0, 0);
  Point b ( 15, 15);
  typedef ImageSelector<Domain, unsigned char>::Type Image;
  Domain domain(a,b); 
  Image image(domain);
  for(unsigned int i=0 ; i < 256; i++)
    image[i] = i;

  PGMWriter<Image>::exportPGM("export-gray-first.pgm",image);
  
  Image imageRead = PGMReader<Image>::importPGM("export-gray-first.pgm");

  PGMWriter<Image>::exportPGM("export-gray-second.pgm",imageRead);

  trace.info() << image<<std::endl;
  trace.info() << imageRead<<std::endl;
  
  
  bool ok = true;
  for(Image::Domain::ConstIterator it = image.domain().begin(),
	itend = image.domain().end();
      it != itend;
      ++it)
    ok = (image(*it) == imageRead(*it));
    
  trace.endBlock();
  return ok;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class PNMWriter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << std::endl;
  
  bool res = testPNMWriter() && testRWIssue254(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << std::endl;
  trace.endBlock();
  return res ? 0 : 1;
}

//                                                                           //
///////////////////////////////////////////////////////////////////////////////
