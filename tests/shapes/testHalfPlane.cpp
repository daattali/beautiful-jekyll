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
 * @file testHalfPlane.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2010/07/02
 *
 * This file is part of the DGtal library
 */

/**
 * @brief
 * Aim: simple test of \ref StraightLine and \ref Point2ShapePredicate
 */

#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>
#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/DomainPredicate.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/shapes/fromPoints/StraightLineFrom2Points.h"
#include "DGtal/shapes/fromPoints/Point2ShapePredicate.h"

#include "DGtalCatch.h"


using namespace DGtal;
using namespace DGtal::functors;
using namespace LibBoard;

TEST_CASE( "HalfplaneUnit tests" )
{
  typedef int Coordinate;
  typedef PointVector<2,Coordinate> Point;
  typedef StraightLineFrom2Points<Point> StraightLine;

  Point p(0,0);
  Point q(5,2);
  Point r1(2,0);
  Point r2(0,2);
  Point r3(10,4);
  StraightLine line(p,q);
  
  //halfplane upward oriented and closed 
//! [HalfPlaneTypedefUpClosed]
  typedef Point2ShapePredicate<StraightLine,true,true> UpClosedHalfPlane;
//! [HalfPlaneTypedefUpClosed]
 
  //halfplane upward oriented and open 
  typedef Point2ShapePredicate<StraightLine,true,false> UpOpenHalfPlane; 
  //halfplane downward oriented and closed 
  typedef Point2ShapePredicate<StraightLine,false,true> DownClosedHalfPlane; 

  //Location
  trace.beginBlock("Creation of a halfplane and test some points");
  std::string res;
  trace.info() << "created line:" << std::endl;
  trace.info() << line << std::endl;

//! [HalfPlaneUsage]
  //line is an instance of StraightLine
  UpClosedHalfPlane hp(line);
  trace.info() << hp << std::endl;
    trace.info() << "Does " << r1 << " belongs to hp (no)?" << std::endl;
  REQUIRE( !hp(r1) );
//! [HalfPlaneUsage]
  REQUIRE(hp(r2));
  REQUIRE(hp(r3));


  UpOpenHalfPlane hp2(line);
  REQUIRE(! hp2(r1));
  REQUIRE(hp2(r2));
  REQUIRE( ! hp2(r3) );

  DownClosedHalfPlane hp3(line);
  REQUIRE(hp3(r1));
  REQUIRE(!hp3(r2));
  REQUIRE(hp3(r3));
}
