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
 * @file io/viewers/viewer3D-7-planes.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class COBANaivePlaneComputer.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows the recognition of a simple digital plane with
   the COBA algorithm (class COBANaivePlaneComputer). Green points belong to
   the naive plane.  There is no naive plane containing the green
   points and any one of the red points.

@see \ref moduleCOBANaivePlaneRecognition_sec2

@verbatim
$ ./examples/io/viewers/viewer3D-7-planes
@endverbatim

@image html coba-naive-plane.png "Piece of naive plane containing the four green points. There is no naive plane containing also any one of the red points."
@image latex coba-naive-plane.png "Piece of naive plane containing the four green points. There is no naive plane containing also any one of the red points." width=5cm

\example io/viewers/viewer3D-7-planes.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/viewers/Viewer3D.h"
#include "DGtal/geometry/surfaces/COBANaivePlaneComputer.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :
template <typename Viewer3D, typename Domain, typename Predicate>
void
displayPredicate( Viewer3D & viewer,
                  const Domain & domain, const Predicate & pred )
{
  for ( typename Domain::ConstIterator itB = domain.begin(), itE = domain.end();
        itB != itE; ++itB )
    {
      if ( pred( *itB ) )
        viewer << *itB;
    }
}

int main( int argc, char** argv )
{
  using namespace Z3i;

  QApplication application(argc,argv);
  trace.beginBlock ( "Testing class COBANaivePlaneComputer" );

  unsigned int nbok = 0;
  unsigned int nb = 0;

  typedef COBANaivePlaneComputer<Z3, BigInteger> PlaneComputer;
  typedef PlaneComputer::Primitive Primitive;
  PlaneComputer plane;

  plane.init( 2, 100, 1, 1 );
  Point pt0( 0, 0, 0 );
  bool pt0_inside = plane.extend( pt0 );
  trace.info() << "(" << nbok << "/" << nb << ") Plane=" << plane
               << std::endl;
  Point pt1( 8, 1, 3 );
  bool pt1_inside = plane.extend( pt1 );
  ++nb, nbok += pt1_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt1
               << " Plane=" << plane << std::endl;
  Point pt2( 2, 7, 1 );
  bool pt2_inside = plane.extend( pt2 );
  ++nb, nbok += pt2_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt2
               << " Plane=" << plane << std::endl;

  Point pt3( 0, 5, 12 );
  bool pt3_inside = plane.extend( pt3 );
  ++nb, nbok += pt3_inside == false ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt3
               << " Plane=" << plane << std::endl;

  Point pt4( -5, -5, 10 );
  bool pt4_inside = plane.extend( pt4 );
  ++nb, nbok += pt4_inside == false ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt4
               << " Plane=" << plane << std::endl;

  Point pt5 = pt0 + pt1 + pt2 + Point( 0, 0, 1 );
  bool pt5_inside = plane.extend( pt5 );
  ++nb, nbok += pt5_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt5
               << " Plane=" << plane << std::endl;

  Point pt6 = Point( 1, 0, 1 );
  bool pt6_inside = plane.extend( pt6 );
  ++nb, nbok += pt6_inside == true ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") add " << pt5
               << " Plane=" << plane << std::endl;

  Primitive strip = plane.primitive();
  trace.info() << "strip=" << strip
               << " axis=" << strip.mainAxis()
               << " axiswidth=" << strip.axisWidth()
               << " diag=" << strip.mainDiagonal()
               << " diagwidth=" << strip.diagonalWidth()
               << std::endl;
  ++nb, nbok += strip.axisWidth() < 1.0 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") axiswidth < 1 "
               << std::endl;
  ++nb, nbok += strip.diagonalWidth() < sqrt(3.0) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") axiswidth < sqrt(3) "
               << std::endl;
  trace.emphase() << ( nbok == nb ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  typedef Viewer3D<> MyViewer;
  MyViewer viewer;
  viewer.show();
  Color red( 255, 0, 0 );
  Color green( 0, 255, 0 );
  Color grey( 200, 200, 200 );
  Domain domain( Point( -5, -5, -5 ), Point( 12, 12, 12 ) );
  viewer << ( pt0_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt0;
  viewer << ( pt1_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt1;
  viewer << ( pt2_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt2;
  viewer << ( pt3_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt3;
  viewer << ( pt4_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt4;
  viewer << ( pt5_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt5;
  viewer << ( pt6_inside ? CustomColors3D( green, green ) : CustomColors3D( red, red ) ) << pt6;
  viewer << CustomColors3D( grey, grey );
  displayPredicate( viewer, domain, strip );

  viewer << MyViewer::updateDisplay;


  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
