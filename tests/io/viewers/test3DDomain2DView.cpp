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
 * @file test3DDomain2DView.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/05/11
 *
 * Functions for testing class 3DDomain2DView.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
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
 Viewer3D<> viewer;
 viewer.setWindowTitle("simpleViewer");
 viewer.show();
 trace.beginBlock ( "Testing class 3DDomain2DView" );

 Z2i::Point p1( 0, 0 );
 Z2i::Point p2( 10, 15 );

 Z3i::Point p13D( 0, 0, 0 );
 Z3i::Point p23D( 10, 15, 0 );

 Z3i::Point p13Dt( 20, 20, 20 );
 Z3i::Point p23Dt( 30, 35, 20 );

 Z3i::Point p13Dtt( 40, 20, 20 );
 Z3i::Point p23Dtt( 50, 35, 20 );

 HyperRectDomain<Z2i::Space> dom ( p1,p2 );
 HyperRectDomain<Z2i::Space> dom2 ( p1,p2 );
 HyperRectDomain<Z2i::Space> dom3 ( p1,p2 );

 HyperRectDomain<Z2i::Space> dom4 ( p1,p2 );
 HyperRectDomain<Z2i::Space> dom5 ( p1,p2 );
 HyperRectDomain<Z2i::Space> dom6 ( p1,p2 );

 HyperRectDomain<Z2i::Space> dom7 ( p1,p2 );
 HyperRectDomain<Z2i::Space> dom8 ( p1,p2 );
 HyperRectDomain<Z2i::Space> dom9 ( p1,p2 );

 viewer << p13D << p23D << p13Dt << p23Dt << p13Dtt << p23Dtt;
 viewer << dom << dom2 << dom3;
 viewer << SetMode3D( dom4.className(), "Grid" );
 viewer << dom4 << dom5 << dom6;
 viewer << SetMode3D( dom4.className(), "Grid" );
 viewer << dom7 << dom8 << dom9;

 viewer << Update2DDomainPosition<Space, KSpace>(0, Viewer3D<Space, KSpace>::xDirection, 0, 0, 0);
 viewer << Update2DDomainPosition<Space, KSpace>(1, Viewer3D<Space, KSpace>::yDirection, 0, 0, 0);
 viewer << Update2DDomainPosition<Space, KSpace>(2, Viewer3D<Space, KSpace>::zDirection, 0, 0, 0);

 viewer << Update2DDomainPosition<Space, KSpace>(3, Viewer3D<Space, KSpace>::xDirection, 0, 0, 0);
 viewer << Update2DDomainPosition<Space, KSpace>(4, Viewer3D<Space, KSpace>::yDirection, 0, 0, 0);
 viewer << Update2DDomainPosition<Space, KSpace>(5, Viewer3D<Space, KSpace>::zDirection, 0, 0, 0);

 viewer << Update2DDomainPosition<Space, KSpace>(6, Viewer3D<Space, KSpace>::xDirection, 0, 0, 0);
 viewer << Update2DDomainPosition<Space, KSpace>(7, Viewer3D<Space, KSpace>::yDirection, 0, 0, 0);
 viewer << Update2DDomainPosition<Space, KSpace>(8, Viewer3D<Space, KSpace>::zDirection, 0, 0, 0);

 viewer << DGtal::Translate2DDomain(3, 20, 20 ,20);
 viewer << DGtal::Translate2DDomain(4, 20, 20 ,20);
 viewer << DGtal::Translate2DDomain(5, 20, 20 ,20);

 viewer << DGtal::Translate2DDomain(6, 40, 20 ,20);
 viewer << DGtal::Translate2DDomain(7, 40, 20 ,20);
 viewer << DGtal::Translate2DDomain(8, 40, 20 ,20);

 viewer <<  Viewer3D<>::updateDisplay;

 bool res = application.exec();
 trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
 trace.endBlock();
 return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
