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
 * @file topology/ctopo-1s-3d.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/05/13
 *
 * An example file named ctopo-1-3d.cpp.
 *
 * This file is part of the DGtal library.
 */

/**
 * A simple example of cellular grid space with several cells
 * instantiated and visualized in 3D. This program outputs this image.
 * 
 * @see \ref dgtal_ctopo_sec6
 *  
 * @image html ctopo-1s-3d.png
 * 
 * \example topology/ctopo-1s-3d.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/viewers/Viewer3D.h"

#include "DGtal/io/DrawWithDisplay3DModifier.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::Z3i;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  // for 3D display with Viewer3D
  QApplication application(argc,argv);

  KSpace K;
  Point plow(0,0,0);
  Point pup(3,3,2);
  Domain domain( plow, pup );
  K.init( plow, pup, true );

  typedef Viewer3D<Space, KSpace> MyViewer;
  MyViewer viewer(K);
  viewer.show();
  //viewer << SetMode3D( domain.className(), "Paving" );

  SCell ptlow = K.sPointel( plow ); // pointel (0*2,0*2, 0*2)
  SCell ptup1 = K.sPointel( pup );  // pointel (3*2,3*2, 2*2)
  SCell ptup2 = K.sTranslation( ptup1, Point::diagonal() ); // pointel (4*2, 4*2, 3*2)

  viewer << ptlow << ptup1 << ptup2;

  // drawing cells of dimension 0
  SCell p1= K.sCell(Point(0,0,2),false);  // pointel (0*2,0*2,2*2)
  SCell p2= K.sCell(Point(0,2,2));  // ...
  SCell p3= K.sCell(Point(2,2,2),false);
  SCell p4= K.sCell(Point(2,0,2));
  SCell p5= K.sCell(Point(0,0,4),false);
  SCell p6= K.sCell(Point(0,2,4));
  SCell p7= K.sCell(Point(2,2,4), false);
  SCell p8= K.sCell(Point(2,0,4));
  viewer << p1 << p2 << p3 << p4 << p5 << p6 << p7 << p8;

  // drawing Cells of dimension 1
  SCell linel0 = K.sCell( Point( 1, 0, 2 ) );  // linel (2*1+1, 0, 2*2)
  SCell linel1 = K.sCell( Point( 1, 2, 2 ) );  // ...
  SCell linel2 = K.sCell( Point( 0, 1, 2 ) );
  SCell linel3 = K.sCell( Point( 2, 1, 2 ) );

  SCell linel4 = K.sCell( Point( 1, 0, 4 ) );
  SCell linel5 = K.sCell( Point( 1, 2, 4 ) );
  SCell linel6 = K.sCell( Point( 0, 1, 4 ) );
  SCell linel7 = K.sCell( Point( 2, 1, 4 ) );

  SCell linel8 = K.sCell( Point( 0, 0, 3 ) );
  SCell linel9 = K.sCell( Point( 0, 2, 3 ) );
  SCell linel10 = K.sCell( Point( 2, 0, 3 ) );
  SCell linel11 = K.sCell( Point( 2, 2, 3 ) );


  SCell linel12 = K.sCell( Point( 3, 2, 2 ) );

  viewer << linel0<< linel1<< linel2 << linel3 ;
  viewer << linel4<< linel5<< linel6 << linel7 ;
  viewer << linel8<< linel9<< linel10 << linel11 << linel12;

  // drawing cells of dimension 2

  SCell surfelA = K.sCell( Point( 2, 1, 3 ) ); // surfel (2*2,2*1+1,2*3+1)
  SCell surfelB = K.sCell( Point( 1, 0, 1 ) ); // surfel (2*1,2*0,2*1+1)
  SCell surfelC = K.sCell( Point( 2, 1, 1 ),false ); // surfel (2*2,2*1+1,2*1+1)
  viewer << surfelA << surfelB << surfelC;

  // drawing cells of dimension 3
  SCell vox1 = K.sCell( Point( 3, 3, 3 ) ); // voxel (2*3+1,2*3+1,2*3+1)
  SCell vox2 = K.sCell( Point( 1, 1, 3 ) ,false ); // voxel (2*1+1,2*1+1,2*3+1)
  viewer << vox1 << vox2;


  viewer << CameraPosition(-2.9, 2.96, 2.64)
   << CameraDirection(0.6, -0.43, 0.65)
   << CameraUpVector(0.32, 0.900, 0.29);

  viewer<< MyViewer::updateDisplay;
  return application.exec();

  return 0;
}
///////////////////////////////////////////////////////////////////////////////
