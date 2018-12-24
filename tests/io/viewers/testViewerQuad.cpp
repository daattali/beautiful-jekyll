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
 KSpace k;

 k.init(Point(2,2,2), Point(4,4,4), true);
 Viewer3D<Space,KSpace> viewer(k);
 viewer.setWindowTitle("simpleViewer");
 viewer.show();


 trace.beginBlock ( "Testing class for  Viewer3D" );

  Point p1( 0, 0, 0 );
  Point p2( 0, 1 , 0);
  Point p3( 1, 1, 0);
  Point p4(1, 0, 0 );
  Point p5( 2, 0 , 0);
  Point p6( 2, 1, 0);
  RealVector n(1,1,1);
  RealVector n2(0,1,1);

  viewer.addQuadWithNormal(p1,p2,p3,p4, n.getNormalized(), true);
  viewer.addQuadWithNormal(p4,p5,p6,p3, n2.getNormalized(), true);

  Cell surfel = k.uCell( Point( 2,3,3) );
  SCell surfel2 = k.sCell( Point( 6,3,3), KSpace::POS);
  SCell surfel3 = k.sCell( Point( 8,3,3), KSpace::NEG  );

  viewer << SetMode3D( surfel.className(), "Basic" );

  Display3DFactory<Space,KSpace>::drawUnorientedSurfelWithNormal( viewer, surfel, n2.getNormalized());

  Display3DFactory<Space,KSpace>::drawOrientedSurfelWithNormal( viewer, surfel2, n2.getNormalized());

  Display3DFactory<Space,KSpace>::drawOrientedSurfelWithNormal( viewer, surfel3, n2.getNormalized());





  viewer  << Display3D<Space, KSpace>::updateDisplay;

  bool res = application.exec();






  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
