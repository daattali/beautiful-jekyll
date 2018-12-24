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
 * @file geometry/curves/exampleArithDSSIterator.cpp
 * @ingroup Examples
 * @author Isabelle Sivignon (\c isabelle.sivignon@gipsa-lab.grenoble-inp.fr )
 * gipsa-lab Grenoble Images Parole Signal Automatique (CNRS, UMR 5216), CNRS, France
 *
 * @date 2013/07/10
 *
 * An example file named exampleArithDSSIterator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
///////////////////////////////////////////////////////////////////////////////

#include "DGtal/geometry/curves/ArithDSSIterator.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"


using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Example exampleArithDSSIterator" );

  typedef Z2i::Integer Integer;
  typedef ArithDSSIterator<Integer,8> DSSIterator;
  typedef ArithmeticalDSSComputer<DSSIterator,Integer,8> ArithDSS;
  typedef Z2i::Point Point;
  
  Point A(1,5);
  Integer xMax = 6;
  
  // Define an iterator over the 8-connected DSS of characteristics
  // (2,3,15) and initial point A 
  DSSIterator  it(2,3,-15,A);
  
  // Use this iterator in the ArithmeticalDSS recognition algorithm.
  // The result gives the minimal characteristics of the subsegment of
  // the DSL (2,3,15) between the point A and the point of abscissa
  // equal to xMax. 
  ArithDSS myDSS(it);
  
  while ( (*(myDSS.end()))[0] <=xMax && myDSS.extendFront())
    {}
  
  //Display the result.
  std::cout << myDSS.a() << " " << myDSS.b() << " " << myDSS.mu();
  
  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
