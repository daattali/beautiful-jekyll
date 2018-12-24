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
 * @file topology/khalimskySpaceScanner.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/04/30
 *
 * An example file named KhalimskySpaceScanner.
 *
 * This file is part of the DGtal library.
 */

/**
 * A simple example illustrating different way to scan a Khalimsky
 * space. This program outputs these images:
 * 
 * @see \ref dgtal_ctopo_sec8
 *
 * <table>
 * <TR>
 * <td> @image html khalimskySpaceScanner1.png </td>
 * <td> @image html khalimskySpaceScanner2.png </td>
 * </TR>
 * </TABLE>
 *
 * \example topology/khalimskySpaceScanner.cpp
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  trace.beginBlock ( "Example KhalimskySpaceScanner" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  
  Board2D boardScan1; // for 2D display
  Board2D boardScan2; // for 2D display
  

  Z2i::KSpace K;
  Z2i::Point plow(0,0);
  Z2i::Point pup(3,2);
  
  Z2i::Domain dom (plow, pup);
  boardScan1 << SetMode( dom.className(), "Paving" )
        << dom;
  boardScan2 << SetMode( dom.className(), "Paving" )
        << dom;
  
  K.init( dom.lowerBound(),dom.upperBound(), true );
  

  
 Z2i::KSpace::Cell q = K.uSpel(plow);
 Z2i::KSpace::Cell p = K.uSpel(plow);
 
  
 Z2i::Vector shift;
 Z2i::KSpace::Cell prec=p;
 bool first=true;
 // Simple way to scan Khalimsky space 
 do 
   {
     boardScan1 << p;
     if(first){
       first=false;
       prec=p;
       continue;
     }
     // Drawing the scan arrows
     boardScan1.setPenColor( Color( 30, 30, 200 ));
     shift =   K.uCoords(p)-K.uCoords(prec);  
      Display2DFactory::draw(boardScan1, shift, K.uCoords(prec));
     prec=p;     
   }
 while ( K.uNext( p, K.uFirst(p), K.uLast(p) ) ); 
 
 
 

 // Other way to scan Khalimsky space by controlling axis order
 Z2i::Vector shiftq;
 Z2i::KSpace::Cell precq = q;
 bool firstq = true;
 using KPS = Z2i::KPreSpace;
 for ( KPS::Cell qq = K.uGetMax(q, 0); K.uIsInside(qq, 0); qq = KPS::uGetDecr(qq, 0) )
   {
     for ( KPS::uSetKCoord( qq, K.uFirst( qq, 1 ), 1 ); K.uIsInside(qq, 1); qq = KPS::uGetIncr(qq, 1) )
       {
         q = K.uCell( qq );
         boardScan2 << q;
         if(firstq){
             firstq = false;
             precq = q;
             continue;
         }
         // Drawing the scan arrows
         shiftq = K.uCoords(q) - K.uCoords(precq);
         boardScan2.setPenColor( Color( 30, 30, 200 ));
         Display2DFactory::draw(boardScan2, shiftq, K.uCoords(precq));
         precq = q;
       }
   }
 
 boardScan1.saveSVG("khalimskySpaceScanner1.svg");
 boardScan1.saveFIG("khalimskySpaceScanner1.fig");
 
 boardScan2.saveSVG("khalimskySpaceScanner2.svg");
 boardScan2.saveFIG("khalimskySpaceScanner2.fig");
  
  return 0;

}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

