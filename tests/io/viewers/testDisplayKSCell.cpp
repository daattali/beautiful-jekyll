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
 * @file testDisplayKSCell.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/05/30
 *
 * Functions for testing class DisplayKSCell.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;



///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/viewers/Viewer3D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing Display of display of KS space Cell.
///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{

 QApplication application(argc,argv);


 KSpace K;
 Point plow(0,0,0);
 Point pup(3,3,2);
 Domain domain( plow, pup );
 K.init( plow, pup, true );

 Viewer3D<Space, KSpace> viewer(K);
 viewer.show();
 trace.beginBlock ( "Testing display KSCell in Viewer 3D" );
 //viewer << SetMode3D( domain.className(), "Paving" );
 // if the domain is visible can't see the cubes inside
 // viewer << domain;


 // Drawing cell of dimension 3
 Cell voxelA = K.uCell(Point(1, 1, 1));
 SCell voxelB = K.sCell(Point(1, 1, 3));
 viewer << voxelB<< voxelA;//

 // drawing cells of dimension 2
 SCell surfelA = K.sCell( Point( 2, 1, 3 ) );
 SCell surfelB = K.sCell( Point( 1, 0, 1 ), false );
 Cell surfelC = K.uCell( Point( 1, 2, 1 ) );
 SCell surfelD = K.sCell( Point( 1, 1, 0 ) );
 Cell surfelE = K.uCell( Point( 1, 1, 2 ) );
 viewer << surfelA << surfelB << surfelC << surfelD << surfelE;

 Cell linelA = K.uCell(Point(2, 1 ,2));
 SCell linelB = K.sCell(Point(2, 2 ,1));
 SCell linelC = K.sCell(Point(1, 2 ,2), false);
 viewer << linelA << linelB << linelC;


 Cell center = K.uCell(Point(5,5,5));
// Testing display of oriented surfels:
 SCell ssurfelXZ = K.sCell( Point( 5, 6, 5 ), false );
 SCell ssurfelXY = K.sCell( Point( 5, 5, 6 ), false );
 SCell ssurfelZY = K.sCell( Point( 6, 5, 5 ), false );
 viewer<< center;

 SCell ssurfelXZo = K.sCell( Point( 5, 4, 5 ), false );
 SCell ssurfelXYo = K.sCell( Point( 5, 5, 4 ), false );
 SCell ssurfelZYo = K.sCell( Point( 4, 5, 5 ), false );

 viewer << ssurfelXZ << ssurfelXY << ssurfelZY;
 viewer << ssurfelXZo << ssurfelXYo << ssurfelZYo;

 // Testing display oriented pointels
 Cell pointelA = K.uCell(Point(2, 2, 2));
 SCell pointelB = K.sCell(Point(4, 4, 4), true);
 SCell pointelC = K.sCell(Point(6, 4, 4), false);
 SCell linelAC = K.sCell(Point(5, 4, 4), false);
 viewer << pointelA << pointelB << pointelC << linelAC;

 viewer <<  Viewer3D<>::updateDisplay;

 bool res =  application.exec();
 trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
 trace.endBlock();
 return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
