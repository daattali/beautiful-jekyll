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
 * @file geometry/curves/exampleDSLSubsegment.cpp
 * @ingroup Examples
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 *
 * @date 2013/07/10
 *
 * An example file named exampleDSLSubsegment.
 *
 * This file is part of the DGtal library.
 */


/**
   Example of DSLSubsegment.
   \example geometry/curves/exampleDSLSubsegment.cpp
**/



///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

#include <map>
#include "DGtal/geometry/curves/DSLSubsegment.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/arithmetic/IntegerComputer.h"



using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( )
{
  trace.beginBlock ( "Example exampleDSLSubsegment" );


  typedef DGtal::int32_t Integer;
  typedef long double Number;

  // Define the DSLSubsegment: the first template parameter specifies
  // the type of integer used for computations, the second one is the
  // type of the input DSL characteristics (Integer in this case).
  typedef DGtal::DSLSubsegment<Integer,Integer> DSLSubseg;

  typedef DSLSubseg::Point Point;

  // Define the two endpoints of the subsegment
  Point A(1,5);
  Point B(6,9);

  // Compute the minimal characteristics of the subsegment [AB] of the
  // 8-connected DSL of characteristics (2,3,15). The algorithm using
  // the Farey fan is used in this case. If the string is set to
  // "localCH", the algorithm using local convex hull is used: the
  // result is the same but the computation time is a bit longer.
  DSLSubseg D1(2,3,15,A,B,"farey");

  // Display the result
  std::cout << "a=" << D1.getA() << " b=" << D1.getB() << " mu=" << D1.getMu() << std::endl;

  // Define a DSL subsegment with floating-point input
  // characteristics.
  typedef DGtal::DSLSubsegment<Integer,Number> DSLSubsegD;

  // Same as before, except that the last parameter is the precision used for
  // floating-point geometric predicates. The algorithm used is an
  // adaptation of the Farey fan algorithm for floating-point input data.
  DSLSubsegD D2(0.6666,5,A,B,0.00005);

  // Display the result
  std::cout << "a=" << D2.getA() << " b=" << D2.getB() << " mu=" << D2.getMu() << std::endl;



  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
