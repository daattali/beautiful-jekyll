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
 * @file topology/cubical-complex-illustrations.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/08/28
 *
 * An example file named cubical-complex-collapse.cpp.
 *
 * This file is part of the DGtal library.
 */

/**
 * Source of examples used to generate illustrations of Cubical Complex module documention.   
 * @see @ref   moduleCubicalComplex
 * @image html cubical-complex-illustrations-X.png "One of the generated illustration: displaying a 2D cubical complex on a Board."
 * @example topology/cubical-complex-illustrations.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/topology/CubicalComplexFunctions.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


int main( int /* argc */, char** /* argv */ )
{

  //! [cubical-complex-illustrations-X]
  using namespace DGtal::Z2i;
  typedef CubicalComplex< KSpace >     CC;

  KSpace K;
  K.init( Point( 0,0 ), Point( 5,3 ), true );
  trace.beginBlock( "Creating Cubical Complex" );
  CC X( K );
  Domain domain( Point( 0,0 ), Point( 5,3 ) );
  X.insertCell( K.uSpel( Point(1,1) ) );
  X.insertCell( K.uSpel( Point(2,1) ) );
  X.insertCell( K.uSpel( Point(3,1) ) );
  X.insertCell( K.uSpel( Point(2,2) ) );
  X.insertCell( K.uSpel( Point(3,2) ) );
  X.insertCell( K.uSpel( Point(4,2) ) );
  X.close();
  trace.endBlock();
  
  trace.beginBlock( "Displays Cubical Complex" );
  Board2D board;
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  board.saveTikZ( "cubical-complex-illustrations-X.tikz" );
  trace.endBlock();
  //! [cubical-complex-illustrations-X]

  //! [cubical-complex-illustrations-S]
  CC S( K );
  S.insertCell( K.uCell( Point( 5, 4 ) ) ); // a linel
  S.insertCell( K.uCell( Point( 4, 4 ) ) ); // a pointel
  S.insertCell( K.uCell( Point( 7, 5 ) ) ); // a pixel
  board << CustomStyle( X.className(), 
                        new CustomColors( Color::Black, Color(60,60,60) ) )
        << S;
  board.saveTikZ( "cubical-complex-illustrations-S.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-S]

  //! [cubical-complex-illustrations-closure]
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color::Red, Color(255,120,120) ) )
        << X.closure( S );
  board.saveTikZ( "cubical-complex-illustrations-closure.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-closure]

  //! [cubical-complex-illustrations-star]
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color::Blue, Color(120,120,255) ) )
        << X.star( S );
  board.saveTikZ( "cubical-complex-illustrations-star.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-star]

  //! [cubical-complex-illustrations-link]
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color::Green, Color(120,255,120) ) )
        << X.link( S );
  board.saveTikZ( "cubical-complex-illustrations-link.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-link]

  //! [cubical-complex-illustrations-bd]
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color::Magenta, Color(255,120,255) ) )
        << X.boundary();
  board.saveTikZ( "cubical-complex-illustrations-bd.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-bd]

  //! [cubical-complex-illustrations-int]
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color::Cyan, Color(120,255,255) ) )
        << X.interior();
  board.saveTikZ( "cubical-complex-illustrations-int.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-int]

  //! [cubical-complex-illustrations-collapse]
  board << domain;
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(80,80,100), Color(180,180,200) ) )
        << X;
  Cell p1 = K.uCell( Point(2,2) );
  Cell p2 = K.uCell( Point(10,6) );
  X[ p1 ] = CC::FIXED;
  X[ p2 ] = CC::FIXED;
  CC::DefaultCellMapIteratorPriority P;
  functions::collapse( X, X.begin(), X.end(), P, true, true, true );
  board << CustomStyle( X.className(), 
                        new CustomColors( Color(255,120,20), Color(255,150,50) ) )
        << X
        << CustomStyle( p1.className(), 
                        new CustomColors( Color::Blue, Color(120,120,255) ) )
        << p1 << p2;
  board.saveTikZ( "cubical-complex-illustrations-collapse.tikz" );
  board.clear();
  //! [cubical-complex-illustrations-collapse]

  return 0;
}
///////////////////////////////////////////////////////////////////////////////
