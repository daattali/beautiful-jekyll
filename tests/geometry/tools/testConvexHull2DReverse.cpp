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
 * @date 2015/11/07
 *
 * Functions for testing class ConvexHull2D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/tools/Hull2DHelpers.h"
#include "DGtal/geometry/tools/MelkmanConvexHull.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ConvexHull2D 
///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing MelkmanConvexHull insertion from front and back using reverse()" )
{
  typedef PointVector<2, double_t> Point;
  typedef InHalfPlaneBySimple3x3Matrix<Point, double> Functor;  
  DGtal::MelkmanConvexHull<Point, Functor> ch; 
  
  // sequence of points splited from test testConvexHull2D_Thickness:
  //  using  reverse() should produce the same convex hull.

  ch.add(Point(102.2, 50.2));
  ch.add(Point(101.0, 50.0));
  ch.add(Point(101.0, 49.1));
  ch.add(Point(101.2, 48.2));
  ch.add(Point(100.0, 48.2));
  ch.add(Point(100.4, 47.4));
  ch.reverse();
  ch.add(Point(102.2, 51.0));
  ch.add(Point(102.3, 52.3));
  ch.add(Point(103.3, 52.3));
  ch.add(Point(103.2, 53.4));
  ch.add(Point(104.2, 53.2));
  ch.add(Point(104.0, 54.2));
  
  Point pHV,qHV,sHV, pE,qE,sE;
   
  const double thicknessHV = DGtal::functions::Hull2D::computeHullThickness( ch.begin(), ch.end(), 
                                                 DGtal::functions::Hull2D::HorizontalVerticalThickness,
                                                 pHV, qHV, sHV);
  
  const double thicknessE  = DGtal::functions::Hull2D::computeHullThickness(ch.begin(), ch.end(), 
                                                 DGtal::functions::Hull2D::EuclideanThickness,
                                                 pE, qE, sE);

  CAPTURE( thicknessHV );
  CAPTURE( thicknessE  );
  
  SECTION("Testing antipodal points of ConvexHull2D")
    {
      REQUIRE( pHV == Point(101.2, 48.2) );
      REQUIRE( qHV == Point(104.2, 53.2) );
      REQUIRE( sHV == Point(102.3, 52.3) );
    }
  SECTION("Testing antipodal points of ConvexHull2D")
    {
      REQUIRE( pE == Point(101.2, 48.2) );
      REQUIRE( qE == Point(104.2, 53.2) );
      REQUIRE( sE == Point(102.3, 52.3) );
    }
  ch.reverse();
    
  const double thicknessEb = DGtal::functions::Hull2D::computeHullThickness(ch.begin(), ch.end(), 
                                                 DGtal::functions::Hull2D::EuclideanThickness,
                                                 pE, qE, sE);
   
  CAPTURE( thicknessEb );

  SECTION("Testing same antipodal points after hull reversing ")
    {
      REQUIRE( pE == Point(101.2, 48.2) );
      REQUIRE( qE == Point(104.2, 53.2) );
      REQUIRE( sE == Point(102.3, 52.3) );
    }
}

/** @ingroup Tests **/
