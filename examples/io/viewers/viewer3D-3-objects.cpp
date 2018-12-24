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
 * @file io/viewers/viewer3D-3-objects.cpp
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
 * Example of 6-18 digital Adjacencies visualization  with Viewer3D.
 * @see \ref DGtalGLV_ModeEx
 * \example io/viewers/viewer3D-3-objects.cpp
 * \image html visu6-18Adj.png " 6-18 digital Adjacencies visualization  with Viewer3D."
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/io/Color.h"
#include "DGtal/helpers/StdDefs.h"
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

 Point p1( 0, 0, 0 );
 Point p2( 10, 10 , 10 );
 Domain domain( p1, p2 );


 DigitalSet shape_set( domain );
 Shapes<Domain>::addNorm1Ball( shape_set, Point( 5, 5, 5 ), 2 );
 Shapes<Domain>::addNorm2Ball( shape_set, Point( 3, 3, 3 ), 2 );
 viewer <<  CustomColors3D(Color(250, 200,0, 100),Color(250, 200,0, 25));
 viewer << shape_set;

 Object6_18 shape( dt6_18, shape_set );
 viewer << SetMode3D( shape.className(), "DrawAdjacencies" );
 viewer << shape;

 Object18_6 shape2( dt18_6, shape_set );
 viewer << SetMode3D( shape2.className(), "DrawAdjacencies" );
 //viewer << shape2;

 viewer<< MyViewer::updateDisplay;
 return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
