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
 * @file topology/ctopo-1.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @date 2011/03/05
 *
 * An example file named ctopo-1.
 *
 * This file is part of the DGtal library.
 */


/**
 * A simple example of cellular grid space with several cells
 * instantiated and visualized. This program outputs this image.
 *
 * @see \ref dgtal_ctopo_sec5
 * 
 * @image html ctopo-1.png
 *
 * \example topology/ctopo-1.cpp
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z2i;
///////////////////////////////////////////////////////////////////////////////

int main()
{
  KSpace K;
  Point plow(-3,-2);
  Point pup(5,3);
  Domain domain( plow, pup );
  Board2D board; // for 2D display
  K.init( plow, pup, true );
  board << SetMode( domain.className(), "Paving" )
        << domain;
  Cell pixlow = K.uSpel( plow ); // pixel (-3*2+1,-2*2+1)
  Cell ptlow = K.uPointel( plow ); // pointel (-3*2,-2*2)
  Cell pixup = K.uSpel( pup ); // pixel (5*2+1,3*2+1)
  Cell ptup1 = K.uPointel( pup );   // pointel (5*2,3*2)
  Cell ptup2 = K.uTranslation( ptup1, Point::diagonal() ); // pointel (6*2,4*2)
  Cell linelb = K.uCell( Point( 1, 0 ) ); // linel (1,0) bottom
  Cell linelt = K.uCell( Point( 1, 2 ) ); // linel (1,2) top
  Cell linell = K.uCell( Point( 0, 1 ) ); // linel (0,1) left
  Cell linelr = K.uCell( Point( 2, 1 ) ); // linel (2,1) right
  board << CustomStyle( ptlow.className(),
                        new CustomColors( Color( 0, 0, 200 ),
                                          Color( 100, 100, 255 ) ) )
        << ptlow << ptup2;
  board << CustomStyle( pixlow.className(),
                        new CustomColors( Color( 200, 0, 0 ),
                                          Color( 255, 100, 100 ) ) )
        << pixlow << pixup;
  board << CustomStyle( linelb.className(),
                        new CustomColors( Color( 0, 200, 0 ),
                                          Color( 100, 255, 100 ) ) )
        << linelb << linelt << linell << linelr;
  board.saveSVG("ctopo-1.svg");
  board.saveEPS("ctopo-1.eps");
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
