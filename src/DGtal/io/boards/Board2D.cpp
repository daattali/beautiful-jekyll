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
 * @file Board2D.cpp
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/10/11
 *
 * Implementation of methods defined in Board2D.h
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// class Board2D
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

/**
 * Destructor.
 */
DGtal::Board2D::~Board2D()
{
}

/** 
 * Constructs a new board and sets the background color, if any.
 * 
 * @param aBackgroundColor A color for the drawing's background.
 */
DGtal::Board2D::Board2D( const Color & aBackgroundColor )
  : LibBoard::Board( aBackgroundColor ),
    myStyles()
{
  this->setUnit(LibBoard::Board::UCentimeter);
}

/** 
 * Copy constructor.
 * 
 * @param other The object to be copied.
 */
DGtal::Board2D::Board2D( const Board2D & other )
  : LibBoard::Board( other ),
    myStyles( other.myStyles )
{
}

/**
 * Assignment.
 * @param other the object to copy.
 * @return a reference on 'this'.
 */
DGtal::Board2D & 
DGtal::Board2D::operator= ( const Board2D & other )
{
  if ( this != &other )
    {
      LibBoard::Board::operator=( other );
      myStyles = other.myStyles;
    }
  return *this;
}


///////////////////////////////////////////////////////////////////////////////
// Interface - public :

/**
 * Writes/Displays the object on an output stream.
 * @param out the output stream where the object is written.
 */
void
DGtal::Board2D::selfDisplay ( std::ostream & out ) const
{
    out << "[Board2D]";
}

/**
 * Checks the validity/consistency of the object.
 * @return 'true' if the object is valid, 'false' otherwise.
 */
bool
DGtal::Board2D::isValid() const
{
    return true;
}



///////////////////////////////////////////////////////////////////////////////
// Internals - private :

//                                                                           //
///////////////////////////////////////////////////////////////////////////////
