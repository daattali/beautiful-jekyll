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
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/01/03
 *
 * Functions for testing class Viewer3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Viewer3D.
///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{

 QApplication application(argc,argv);
 Viewer3D<> viewer;
 viewer.setWindowTitle("simpleViewer");
 viewer.show();


 trace.beginBlock ( "Testing class for  Viewer3D" );


 Point p1( 14, 14, 14 );
 Point p2( 27, 27, 27 );
 Domain domain( p1, p2 );

 viewer << CustomColors3D(Color(20, 20, 20, 50),Color(20, 0,250,30));
 viewer << SetMode3D(domain.className(), "Grid");
 viewer << domain;

 DigitalSet shape_set( domain );
 Shapes<Domain>::addNorm1Ball( shape_set, Point( 13, 23, 13 ), 7 );
   viewer << CustomColors3D(Color(250, 200,0, 100),Color(250, 200,0, 50));

 viewer << shape_set ;
 DigitalSet shape_set2( domain );
 Shapes<Domain>::addNorm1Ball( shape_set2, Point( 24, 15, 12 ), 12 );
 viewer << shape_set2 ;

 DigitalSet shape_set3( domain );
 Shapes<Domain>::addNorm2Ball( shape_set3, Point( 11, 15, 12 ), 12 );
 viewer << CustomColors3D(Color(250, 20,0, 190),Color(220, 20,20, 250));
 viewer << shape_set3 ;




  Point pp1( -1, -1, -2 );
  Point pp2( 2, 2, 3 );


  Domain domain2( pp1, pp2 );
  Point pp3( 1, 1, 1 );
  Point pp4( 2, -1, 5 );
  Point pp5( -1, 2, 3 );
  Point pp6( 0, 0, 0 );
  Point pp0( 0, 2, 1 );

  //viewer<< m;
  viewer <<  SetMode3D( pp1.className(), "Paving" );
  viewer << pp1 << pp2 << pp3;

  //viewer <<  SetMode3D( pp1.className(), "Grid" );
  viewer << CustomColors3D(Color(250, 0,0),Color(250, 0,0));
  viewer <<  SetMode3D( pp1.className(), "PavingWired" );
  viewer << pp4 << pp5 ;
  viewer <<  SetMode3D( pp1.className(), "Both" );
  viewer << CustomColors3D(Color(250, 200,0, 100),Color(250, 0,0, 100));
  viewer << pp6;
  viewer << CustomColors3D(Color(250, 200,0, 100),Color(250, 200,0, 20));
  viewer << pp0;


  viewer << SetMode3D(domain.className(), "Paving");
  viewer << domain2 << Display3D<Space, KSpace>::updateDisplay;


 bool res = application.exec();
 trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
 trace.endBlock();
 return res ? 0 : 1;


}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

