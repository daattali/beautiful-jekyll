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
 * @file io/viewers/demo-kernel-2.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @date 2011/03/05
 *
 * An example file named demo-kernel-domain.
 *
 * This file is part of the DGtal library.
 */


/**
 * Example of Domain and Point display in Viewer3D.
 *  @see @ref moduleDisplay3D 
 * \image html demo-kernel-2.png " " 
 *  \example io/viewers/demo-kernel-2.cpp
 **/



///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/viewers/Viewer3D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
  QApplication application(argc,argv);
  typedef DGtal::SpaceND<3, DGtal::int32_t> MySpace;
  typedef MySpace::Point MyPoint;
  typedef HyperRectDomain<MySpace> MyDomain;
  MyPoint p1( 0, 0, 0 );
  MyPoint p2( 5, 5 ,5 );
  MyPoint p3( 2, 3, 4 );
  MyDomain domain( p1, p2 );
  Viewer3D<> viewer; // for 3D visualization
  viewer.show();
  viewer << domain;
  viewer << p1 << p2 << p3;
  viewer<< Viewer3D<>::updateDisplay;
  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
