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
 * @file io/viewers/viewer3D-5-custom.cpp
 * @ingroup examples/3dViewer
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/19/03
 *
 * Simple example of class Viewer3D.
 *
 * This file is part of the DGtal library.
 */


/**
 * Example of a custom display
 * @see \ref DGtalGLV_Custom
 * \example io/viewers/viewer3D-5-custom.cpp
 * \image html visuModeCustom.png "Example of several custom display ." width=5cm
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/viewers/Viewer3D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{

 QApplication application(argc,argv);

 typedef Viewer3D<> MyViewer;
 MyViewer viewer;
 viewer.show();


 Point p1( -1, -1, -2 );
 Point p2( 2, 2, 3 );
 Domain domain( p1, p2 );
 Point p3( 1, 1, 1 );
 Point p4( 2, -1, 3 );
 Point p5( -1, 2, 3 );
 Point p6( 0, 0, 0 );
 Point p0( 0, 2, 1 );
 viewer <<  SetMode3D( p1.className(), "PavingWired" );
 viewer << p1 << p2 << p3;


 //viewer <<  SetMode3D( p1.className(), "Grid" );
  viewer << CustomColors3D(Color(250, 0,0),Color(250, 0,0));
  viewer << p4 << p5 ;
  viewer <<  SetMode3D( p1.className(), "Both" );
  viewer << CustomColors3D(Color(250, 200,0, 100),Color(250, 0,0, 100));
  viewer << p6;
  viewer << CustomColors3D(Color(250, 200,0, 100),Color(250, 200,0, 20));
  viewer << p0;


  viewer << SetMode3D(domain.className(), "Paving");
  viewer << domain << MyViewer::updateDisplay;


 return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
