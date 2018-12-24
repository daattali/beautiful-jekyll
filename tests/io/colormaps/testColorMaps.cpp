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
 * @file testColorMaps.cpp
 * @ingroup Tests
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/16
 *
 * Functions for testing the ColorMap classes.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/CColorMap.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/ColorBrightnessColorMap.h"
#include "DGtal/io/colormaps/SimpleDistanceColorMap.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/RandomColorMap.h"
#include "DGtal/io/boards/Board2D.h"
#include "Board/PSFonts.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace LibBoard;
  
///////////////////////////////////////////////////////////////////////////////
// Function template for testing ColorMap classes. 
///////////////////////////////////////////////////////////////////////////////
template <typename TColorMap>
void addColorMapSample( const char * name,
      const TColorMap & aColorMap, 
      const typename TColorMap::Value step,
      Board & board )
{ 
  BOOST_CONCEPT_ASSERT(( concepts::CColorMap<TColorMap> ));

  typedef typename TColorMap::Value Value;
  board.translate( 0, 15 );
  board.setPenColor(Color::Black);
  board.setFont( LibBoard::Fonts::Courier, 12 );  // todo with Cairo
  board.drawText( -250, 0, name );      // todo with Cairo
  board.setPenColor(Color::None);
  for ( Value x = aColorMap.min(); x <= aColorMap.max(); x += step ) {
    board.setFillColor( aColorMap( x ) );
    board.drawRectangle( static_cast<double>( x ),
       10,
       static_cast<double>( step ),
       10 );
  }
} 

bool testGrayscaleColorMap()
{
  unsigned int nbok = 0;
  unsigned int nb = 6;

  trace.beginBlock("Colormap 0..255");
  { 
    GrayscaleColorMap<unsigned char> cmap(0,255);
    
    Color c0 = cmap(0);
    trace.info(); 
    cerr << int(c0.red())
   << "," << int(c0.green()) << "," << int(c0.blue()) << std::endl;
    nbok += ( c0 == Color::Black );
    
    Color c128 = cmap(128);
    trace.info(); 
    cerr << int(c128.red())
   << "," << int(c128.green()) << "," << int(c128.blue()) << std::endl;
    nbok += ( c128 == Color(128,128,128) );
    
    Color c255 = cmap(255);
    trace.info();
    cerr << int(c255.red())
   << "," << int(c255.green()) << "," << int(c255.blue()) << std::endl;
    nbok += ( c255 == Color::White );
  }
  trace.endBlock();
  
  trace.beginBlock("Colormap 64..128");
  {
    GrayscaleColorMap<unsigned char> cmap(64,128);
    Color c0 = cmap(64);
    trace.info();
    cerr << int(c0.red())
   << "," << int(c0.green()) << "," << int(c0.blue()) << std::endl;
    nbok += ( c0 == Color::Black );

    Color c255 = cmap(128);
    trace.info(); 
    cerr << int(c255.red())
   << "," << int(c255.green()) << "," << int(c255.blue()) << std::endl;
    nbok += ( c255 == Color::White );    
  }
  trace.endBlock();

  trace.beginBlock("Static method");
  {
    Color c = GrayscaleColorMap<unsigned char>::getColor(0,128,128);
    trace.info() << "Should be white: ";
    cerr << int(c.red())
   << "," << int(c.green()) << "," << int(c.blue()) << std::endl;
    nbok += (c == Color::White);

    c = GrayscaleColorMap<unsigned char>::getColor(0,128,64);
    trace.info() << "Should be around 127,127,127: ";
    cerr << int(c.red())
   << "," << int(c.green()) << "," << int(c.blue()) << std::endl;

    trace.endBlock();
  }
  return nbok == nb;
}

int main()
{
  Board board;
  trace.beginBlock ( "Testing GrayscaleColorMap" );
  bool res1 = testGrayscaleColorMap();
  trace.emphase() << ( res1 ? "Passed." : "Error." ) << endl;
  trace.endBlock();
 
  GrayscaleColorMap<int> cmap_gray( 0, 500);
  addColorMapSample( "Grayscale", cmap_gray, 1, board );

  ColorBrightnessColorMap<int> cmap_red( 0, 500, Color::Red );
  addColorMapSample( "Brightness", cmap_red, 1, board );

  ColorBrightnessColorMap<int, DGTAL_RGB2INT(0,0,255) > cmap_blue( 0, 500 );
  addColorMapSample( "Bright (Blue)", cmap_blue, 1, board );

  HueShadeColorMap<int,2> cmap_hsv( 0, 500);
  addColorMapSample( "HueShade", cmap_hsv, 1, board );

  HueShadeColorMap<int,2> cmap_cyclic5( 0, 500 );
  addColorMapSample( "HueShade (2x)", cmap_cyclic5, 1, board );

  HueShadeColorMap<int, 10> cmap_cyclic10( 0, 500 );
  addColorMapSample( "HueShade (10x)", cmap_cyclic10, 1, board );

  RandomColorMap cmap_random(0,500, Color::Green, Color::Red);
  cmap_random.addColor(Color::Red);
  cmap_random.addColor(Color::Blue);
  cmap_random.addColor(Color::Yellow);

  const int yellow = DGTAL_RGB2INT(255,255,0);
  const int red = DGTAL_RGB2INT(255,0,0);
  GradientColorMap<int, CMAP_CUSTOM, yellow, red> cmap_gradient( 0, 500 );
  addColorMapSample( "Gradient (Y->R)", cmap_gradient, 1, board );

  GradientColorMap<int> cmap_grad3( 0, 500 );
  cmap_grad3.addColor( Color::Green );
  cmap_grad3.addColor( Color::Yellow );
  cmap_grad3.addColor( Color::Red );
  addColorMapSample( "Gradient (G->Y->R)", cmap_grad3, 1, board );

  cmap_grad3.clearColors();
  cmap_grad3.addColor( Color::Blue );
  cmap_grad3.addColor( Color::White );
  cmap_grad3.addColor( Color::Red );
  addColorMapSample( "Gradient (B->W->R)", cmap_grad3, 1, board );

  GradientColorMap<int> cool_gradient( 0, 500, CMAP_COOL );
  addColorMapSample( "Gradient (Cool)", cool_gradient, 1, board );

  GradientColorMap<int> copper_gradient( 0, 500, CMAP_COPPER );
  addColorMapSample( "Gradient (Copper)", copper_gradient, 1, board );

  GradientColorMap<int> hot_gradient( 0, 500, CMAP_HOT );
  addColorMapSample( "Gradient (Hot)", hot_gradient, 1, board );

  GradientColorMap<int,CMAP_JET> jet_gradient( 0, 500 );
  addColorMapSample( "Gradient (Jet)", jet_gradient, 1, board );

  addColorMapSample( "Gradient (Spring)",
         GradientColorMap<int,CMAP_SPRING>( 0, 500 ),
         1,
         board );
  addColorMapSample( "Gradient (Summer)",
         GradientColorMap<int>( 0, 500, CMAP_SUMMER ),
         1,
         board );
  addColorMapSample( "Gradient (Autumn)",
         GradientColorMap<int>( 0, 500, CMAP_AUTUMN ),
         1,
         board );
  addColorMapSample( "Gradient (Winter)",
         GradientColorMap<int>( 0, 500, CMAP_WINTER ),
         1,
         board );
  addColorMapSample( "Random", cmap_random, 1, board );  

  SimpleDistanceColorMap<int> dt(0,500, false);
  addColorMapSample( "SimpleDistanceColorMap", dt, 1, board );

  SimpleDistanceColorMap<int> dtticks(0,500, true);
  addColorMapSample( "SimpleDistanceColorMap (ticks)", dtticks, 1, board );

  
  board.saveEPS( "colormaps.eps" );
  board.saveSVG( "colormaps.svg" );
  board.saveTikZ( "colormaps.tikz" );
  
#ifdef WITH_CAIRO
  board.saveCairo("colormaps-cairo.pdf", Board2D::CairoPDF);
#endif

  return ( res1 ) ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
