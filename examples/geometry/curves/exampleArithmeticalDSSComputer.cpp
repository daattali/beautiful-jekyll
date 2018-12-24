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
 * @file geometry/curves/exampleArithmeticalDSSComputer.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/14
 *
 * An example file named ArithmeticalDSSComputer.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows the basic usage of a 4-connected standard segment computer, 
an object devoted to the on-line recognition of 4-connected standard DSSs.  

@see \ref moduleArithDSSReco

\example geometry/curves/exampleArithmeticalDSSComputer.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/helpers/StdDefs.h"

//! [ArithmeticalDSSComputerHeader]
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
//! [ArithmeticalDSSComputerHeader]
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  

  using namespace Z2i;

  //! [ArithmeticalDSSComputerStandardCtor]
  // Container of digital points
  typedef std::vector<Z2::Point> Container;
  // Iterator on the container
  typedef Container::const_iterator ConstIterator;
  // StandardDSS4 computer
  typedef StandardDSS4Computer<ConstIterator> DSSComputer;  
  // Construction of the computer
  DSSComputer theDSSComputer;    
  //! [ArithmeticalDSSComputerStandardCtor]

  // Input points
  Container contour;
  contour.push_back(Z2::Point(0,0));
  contour.push_back(Z2::Point(1,0));
  contour.push_back(Z2::Point(1,1));
  contour.push_back(Z2::Point(2,1));
  contour.push_back(Z2::Point(3,1));
  contour.push_back(Z2::Point(3,2));
  contour.push_back(Z2::Point(4,2));
  contour.push_back(Z2::Point(5,2));
  contour.push_back(Z2::Point(6,2));
  contour.push_back(Z2::Point(6,3));
  contour.push_back(Z2::Point(6,4));
    
  //! [ArithmeticalDSSComputerStandardExtension]
  // Add points while it is possible
  theDSSComputer.init( contour.begin() );
  while ( ( theDSSComputer.end() != contour.end() ) &&
	  ( theDSSComputer.extendFront() ) ) {}
  //! [ArithmeticalDSSComputerStandardExtension]

  // Trace to the standard output
  cout << theDSSComputer << endl;

  //! [ArithmeticalDSSComputerStandardPrimitive]
  DSSComputer::Primitive theDSS = theDSSComputer.primitive();  
  //! [ArithmeticalDSSComputerStandardPrimitive]

  // Trace to the standard output
  cout << theDSS << endl;

  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
