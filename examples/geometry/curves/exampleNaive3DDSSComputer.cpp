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
 * @file geometry/curves/exampleNaive3DDSSComputer.cpp
 * @ingroup Examples
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2015/09/27
 *
 * An example file named Naive3DDSSComputer.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows the basic usage of a naive 3D DSS recognition. 

@see \ref moduleArithDSSReco

\example geometry/curves/exampleNaive3DDSSComputer.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/helpers/StdDefs.h"

//! [Naive3DDSSComputerHeader]
#include "DGtal/geometry/curves/Naive3DDSSComputer.h"
//! [Naive3DDSSComputerHeader]
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  using namespace Z3i;
  
  //! [Naive3DDSSComputerStandardCtor]
  // Container of digital points
  typedef std::vector<Z3::Point> Container;
  // Iterator on the container
  typedef Container::const_iterator ConstIterator;
  // Naive3DDSS computer
  typedef Naive3DDSSComputer< ConstIterator, int, 8 > DSSComputer;  
  // Construction of the computer
  DSSComputer theDSSComputer;    
  //! [Naive3DDSSComputerStandardCtor]
  
  // Input points
  Container contour;
  contour.push_back(Z3::Point(18,25,18));
  contour.push_back(Z3::Point(17,25,19));
  contour.push_back(Z3::Point(16,25,20));
  contour.push_back(Z3::Point(15,25,21));
  contour.push_back(Z3::Point(14,25,22));
  contour.push_back(Z3::Point(13,25,23));
  contour.push_back(Z3::Point(12,25,24));
  contour.push_back(Z3::Point(11,25,25));
  contour.push_back(Z3::Point(10,25,26));
  contour.push_back(Z3::Point(9,25,27));
  contour.push_back(Z3::Point(8,25,28));
  
  //! [Naive3DDSSComputerStandardExtension]
  // Add points while it is possible
  theDSSComputer.init( contour.begin() );
  while ( ( theDSSComputer.end() != contour.end() ) &&
    ( theDSSComputer.extendFront() ) ) {}
    //! [Naive3DDSSComputerStandardExtension]
    
  // Trace to the standard output
  theDSSComputer.selfDisplay( cout );
  
  //! [Naive3DDSSComputerStandardPrimitiveValid]
  theDSSComputer.validArithmeticalDSS2d( 0 );  
  //! [Naive3DDSSComputerStandardPrimitiveValid]
  
  //! [Naive3DDSSComputerStandardPrimitive]
  DSSComputer::ArithmeticalDSSComputer2d theDSS = theDSSComputer.arithmeticalDSS2d( 0 );  
  //! [Naive3DDSSComputerStandardPrimitive]
  
  
  //! [Naive3DDSSComputerStandardParams]
  DSSComputer::Point3d directionZ3;
  DSSComputer::PointR3d intercept;
  DSSComputer::PointR3d thikness;
  theDSSComputer.getParameters ( directionZ3, intercept, thikness );
  //! [Naive3DDSSComputerStandardParams]
  
  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
