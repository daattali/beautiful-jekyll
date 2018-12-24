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
 * @file Color.cpp
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/07/17
 *
 * Implementation of methods defined in Color.h
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtal/io/Color.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// class Color
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :


DGtal::Color::Color( const unsigned int rgb, unsigned char aAlphaValue )
 :myAlpha( aAlphaValue )
{
  myRed = ( rgb & 0xFF0000u ) >> 16;
  myGreen = ( rgb & 0xFF00u ) >> 8;
  myBlue = rgb & 0xFF;
}


DGtal::Color &
DGtal::Color::setRGBA( const DGtal::uint32_t aRGBA )
{
  myRed = ( aRGBA & 0xFF000000u ) >> 24;
  myGreen = ( aRGBA & 0xFF0000u ) >> 16;
  myBlue = ( aRGBA & 0xFF00u ) >> 8;
  myAlpha = aRGBA & 0xFF;
  return *this;
}


DGtal::Color &
DGtal::Color::setRGBf( float aRedValue,
           float aGreenValue,
           float aBlueValue,
           float aAlphaValue  ) {
  if ( aRedValue > 1.0f ) aRedValue = 1.0f;
  if ( aRedValue < 0.0f ) aRedValue = 0.0f;
  myRed = static_cast<unsigned char>( 255 * aRedValue );
  if ( aGreenValue > 1.0f ) aGreenValue = 1.0f;
  if ( aGreenValue < 0.0f ) aGreenValue = 0.0f;
  myGreen = static_cast<unsigned char>( 255 * aGreenValue );
  if ( aBlueValue > 1.0f ) aBlueValue = 1.0f;
  if ( aBlueValue < 0.0f ) aBlueValue = 0.0f;
  myBlue = static_cast<unsigned char>( 255 * aBlueValue );
  if ( aAlphaValue > 1.0f ) aAlphaValue = 1.0f;
  if ( aAlphaValue < 0.0f ) aAlphaValue = 0.0f;
  myAlpha = static_cast<unsigned char>( 255 * aAlphaValue );
  return *this;
}



bool
DGtal::Color::operator==( const Color & aColor ) const
{
  return myRed == aColor.myRed
    && myGreen == aColor.myGreen
    && myBlue == aColor.myBlue
    && myAlpha == aColor.myAlpha;
}

bool
DGtal::Color::operator!=( const Color & aColor ) const
{
  return myRed != aColor.myRed
    || myGreen != aColor.myGreen
    || myBlue != aColor.myBlue
    || myAlpha != aColor.myAlpha;
}

bool
DGtal::Color::operator<( const Color & aColor ) const
{
  if ( myRed < aColor.myRed )
    return true;
  if ( myRed == aColor.myRed ) {
    if ( myGreen < aColor.myGreen )
      return true;
    if ( myGreen == aColor.myGreen ) {
      if ( myBlue < aColor.myBlue )
  return true;
      if ( myBlue == aColor.myBlue )
  return myAlpha < aColor.myAlpha;
    }
  }
  return false;
}


void
DGtal::Color::flushPostscript( std::ostream & stream ) const
{
  stream << ((double)myRed/255.0) << " "
   << ((double)myGreen/255.0) << " "
   << ((double)myBlue/255.0) << " srgb\n";
}

string
DGtal::Color::postscript() const
{
  char buffer[255];
  secured_sprintf( buffer, 255, "%.4f %.4f %.4f", myRed/255.0, myGreen/255.0, myBlue/255.0 );
  return buffer;
}

string
DGtal::Color::svg() const
{
  char buffer[255];
  if ( *this == DGtal::Color::None ) return "none";
  secured_sprintf( buffer, 255, "rgb(%d,%d,%d)",myRed, myGreen, myBlue );
  return buffer;
}

string
DGtal::Color::svgAlpha( const char * prefix ) const
{
  char buffer[255];
  if ( myAlpha == 255 || *this == DGtal::Color::None ) return "";
  secured_sprintf( buffer, 255, " %s-opacity=\"%f\"", prefix, myAlpha/255.0f );
  return buffer;
}

string
DGtal::Color::tikz() const
{
  // see tex/generic/pgf/utilities/pgfutil-plain.def for color definitions
  char buffer[255];
  if ( *this == DGtal::Color::None ) return "none";
  if ( *this == DGtal::Color::Black ) return "black";
  if ( *this == DGtal::Color::Gray ) return "gray";
  if ( *this == DGtal::Color::White ) return "white";
  if ( *this == DGtal::Color::Red ) return "red";
  if ( *this == DGtal::Color::Green ) return "green!50!black";
  if ( *this == DGtal::Color::Lime ) return "green";
  if ( *this == DGtal::Color::Blue ) return "blue";
//  if ( *this == DGtal::Color::Cyan ) return "cyan";
//  if ( *this == DGtal::Color::Magenta ) return "magenta";
//  if ( *this == DGtal::Color::Yellow ) return "yellow";
  if ( *this == DGtal::Color::Silver ) return "white!75!black";
  if ( *this == DGtal::Color::Purple ) return "gray"; // ???: Is Color::Purple meant to be equal to Color::Gray?
  if ( *this == DGtal::Color::Navy ) return "blue!50!black";
//  if ( *this == DGtal::Color::Aqua ) return "cyan"; // ???: Is Color::Aqua meant to be equal to Color::Cyan?
  secured_sprintf( buffer, 255, "{rgb,255:red,%d;green,%d;blue,%d}", myRed, myGreen, myBlue );
  return buffer;
}



/**
 * Destructor.
 */
DGtal::Color::~Color()
{
}



///////////////////////////////////////////////////////////////////////////////
// Interface - public :

const DGtal::Color DGtal::Color::None(0,0,0,0);
const DGtal::Color DGtal::Color::Black((unsigned char)0,(unsigned char)0,(unsigned char)0);
const DGtal::Color DGtal::Color::Gray((unsigned char)128,(unsigned char)128,(unsigned char)128);
const DGtal::Color DGtal::Color::White((unsigned char)255,(unsigned char)255,(unsigned char)255);
const DGtal::Color DGtal::Color::Red((unsigned char)255,(unsigned char)0,(unsigned char)0);
const DGtal::Color DGtal::Color::Green((unsigned char)0,(unsigned char)128,(unsigned char)0);
const DGtal::Color DGtal::Color::Lime((unsigned char)0,(unsigned char)255,(unsigned char)0);
const DGtal::Color DGtal::Color::Blue((unsigned char)0,(unsigned char)0,(unsigned char)255);
const DGtal::Color DGtal::Color::Cyan((unsigned char)0,(unsigned char)255,(unsigned char)255);
const DGtal::Color DGtal::Color::Magenta((unsigned char)255,(unsigned char)0,(unsigned char)255);
const DGtal::Color DGtal::Color::Yellow((unsigned char)255,(unsigned char)255,(unsigned char)0);
const DGtal::Color DGtal::Color::Silver((unsigned char)190,(unsigned char)190,(unsigned char)190);
const DGtal::Color DGtal::Color::Purple((unsigned char)128,(unsigned char)128,(unsigned char)128);
const DGtal::Color DGtal::Color::Navy((unsigned char)0,(unsigned char)0,(unsigned char)128);
const DGtal::Color DGtal::Color::Aqua((unsigned char)0,(unsigned char)255,(unsigned char)255);


/**
 * Writes/Displays the object on an output stream.
 * @param out the output stream where the object is written.
 */
void
DGtal::Color::selfDisplay ( std::ostream & out ) const
{
  out << "[Color] RGBA("<<(int)myRed<<","<<(int)myGreen<<","<<(int)myBlue<<","<<(int)myAlpha<<")";
}

/**
 * Checks the validity/consistency of the object.
 * @return 'true' if the object is valid, 'false' otherwise.
 */
bool
DGtal::Color::isValid() const
{
    return true;
}



///////////////////////////////////////////////////////////////////////////////
// Internals - private :

//                                                                           //
///////////////////////////////////////////////////////////////////////////////
