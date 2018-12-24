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
 * @file testPreimage.cpp
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
 * @brief Aim: simple test of Preimage2D
 * @see testStabbingLineComputer.cpp
 */

#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>




#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/DomainPredicate.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/io/boards/Board2D.h"

#include "DGtal/shapes/fromPoints/StraightLineFrom2Points.h"
#include "DGtal/geometry/tools/Preimage2D.h"


#include "ConfigTest.h"


using namespace DGtal;


int main()
{

  std::string filename = testPath + "samples/DSS.dat";
  std::ifstream instream; // input stream
  instream.open (filename.c_str(), std::ifstream::in);
  
  typedef KhalimskySpaceND<2,int> KSpace; 
  GridCurve<KSpace> c; //grid curve
  c.initFromVectorStream(instream);


  trace.beginBlock("Simple preimage test");

  typedef StraightLineFrom2Points<GridCurve<KSpace>::Point> StraightLine;
  StraightLine aStraightLine; //instance of straight line
  typedef Preimage2D<StraightLine> Preimage2D;

  GridCurve<KSpace>::IncidentPointsRange r = c.getIncidentPointsRange(); //range
  GridCurve<KSpace>::IncidentPointsRange::ConstReverseIterator it (r.rbegin()); //iterators
  GridCurve<KSpace>::IncidentPointsRange::ConstReverseIterator itEnd (r.rend()); 

  //preimage computation
  Preimage2D thePreimage(it->first, it->second, aStraightLine);
  ++it; 
  while ( (it != itEnd) &&
              (thePreimage.addBack(it->first, it->second)) )
  {
    trace.info() << (it - r.rbegin()) << std::endl << thePreimage << std::endl;
    ++it;
  }

  trace.endBlock();

  return 0;
}
