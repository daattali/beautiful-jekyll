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
 * @file io/viewers/viewer3D-10-interaction.cpp
 * @ingroup examples/3dViewer
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @author Bertrand Kerautret (\c bertrand.kerautret@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Lorraine, France
 *
 * @date 2014/10/12
 *
 * Simple example of class Viewer3D.
 *
 * This file is part of the DGtal library.
 */

/** 
 * Simple selection of a surfel (with shift + left click) with the
 * QGLViewer proposed by DGtal (Viewer3D). You may associates \a names
 * (i.e. integers) to surfels or to group of surfels. You may associate
 * reactions or callback functions to \a named graphical objects (surfels
 * in DGtal 0.9).
 *
 * The red surfel is given the name 10001, the green 10002 and the blue
 * 10003. A specific reaction is associated with surfel 10001, while a
 * common reaction is associated with surfels 10002 and 10003. The
 * reactions simply display the clicked surfel.
 *
 * @see \ref moduleQGLInteraction
 *
 * @verbatim
 * $ ./examples/io/viewers/viewer3D-10-interaction
 * @endverbatim
 *
 *
 * @image html viewer3D-10-interaction.png   "Example of viewer3D interaction with the selection of surfels. "
 *
 * \example io/viewers/viewer3D-10-interaction.cpp
 *
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/viewers/Viewer3D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

typedef Viewer3D<Space,KSpace> MyViewer;
typedef MyViewer::SelectCallbackFct SelectCallbackFct;
typedef KSpace::SCell SCell;

struct BigDataCells
{
  KSpace K;
  std::map< DGtal::int32_t, Z3i::SCell > cells;
};

struct BigDataVoxels
{
  std::map< DGtal::int32_t, Z3i::Point > voxels;
};

int reaction1( void* viewer, DGtal::int32_t name, void* data )
{
  BigDataCells* bg = (BigDataCells*) data;
  stringstream ssMessage;
  ssMessage << "Reaction1 with name " << name << " cell " << bg->K.sKCoords( bg->cells[ name ] )  ;
  ((MyViewer *) viewer)->displayMessage(QString(ssMessage.str().c_str()), 100000);
  trace.info() <<  ssMessage.str() << std::endl;
  return 0;
}
int reaction23( void* viewer, DGtal::int32_t name, void* data )
{
  BigDataCells* bg = (BigDataCells*) data;
  stringstream ssMessage;
  ssMessage <<  "Reaction23 with name " << name << " cell " << bg->K.sKCoords( bg->cells[ name ] );
  ((MyViewer *) viewer)->displayMessage(QString(ssMessage.str().c_str()), 100000);
  trace.info() << ssMessage.str() << std::endl;
  return 0;
}
int reaction4( void* viewer, DGtal::int32_t name, void* data )
{
  BigDataVoxels* bg = (BigDataVoxels*) data;
  stringstream ssMessage;
  ssMessage <<  "Reaction4 with name " << name << " Voxel " << bg->voxels[name] ;
  ((MyViewer *) viewer)->displayMessage(QString(ssMessage.str().c_str()), 100000);
  trace.info() << ssMessage.str() << std::endl;
  return 0;
}
///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  QApplication application(argc,argv);
  BigDataCells data;
  BigDataVoxels dataV;
  Point p1( 0, 0, 0 );
  Point p2( 5, 5 ,5 );
  Point p3( 2, 3, 4 );
  KSpace & K = data.K;
  K.init( p1, p2, true );
  Point v1 = Z3i::Point(10, 10,10);
  Point v2 = Z3i::Point(9, 9, 9);
  Point v3 = Z3i::Point(11, 11,11);
  
  dataV.voxels[4001] = v1;
  dataV.voxels[4002] = v2;
  dataV.voxels[4003] = v3;
  
  
  MyViewer viewer( K );
  viewer.show();
  viewer.displayMessage(QString("You can use [shift + click right] on surfels or voxel to interact ..."), 100000);
  Z3i::SCell surfel1 = K.sCell( Point( 1, 1, 2 ), KSpace::POS );
  Z3i::SCell surfel2 = K.sCell( Point( 3, 3, 4 ), KSpace::NEG );
  Z3i::SCell surfel3 = K.sCell( Point( 5, 6, 5 ), KSpace::POS );
  data.cells[ 10001 ] = surfel1;
  data.cells[ 10002 ] = surfel2;
  data.cells[ 10003 ] = surfel3;
  viewer << SetMode3D( surfel1.className(), "Basic" );
  viewer << SetName3D( 10001 ) << CustomColors3D( Color::Red, Color::Red ) << surfel1;
  viewer << SetName3D( 10002 ) << CustomColors3D( Color::Green, Color::Green ) << surfel2;
  viewer << SetName3D( 10003 ) << CustomColors3D( Color::Blue, Color::Blue ) << surfel3;
  viewer << SetSelectCallback3D( reaction1,  &data, 10001, 10001 );
  viewer << SetSelectCallback3D( reaction23, &data, 10002, 10003 );
 
  // example by using voxel interaction:
  viewer << SetName3D( 4001 ) << v1;
  viewer << SetName3D( 4002 ) << v2;
  viewer << SetName3D( 4003 ) << v3;
  viewer << SetSelectCallback3D( reaction4, &dataV, 4001,4003 );
  viewer<< MyViewer::updateDisplay;
  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
