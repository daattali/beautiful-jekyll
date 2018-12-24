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
 * @file doc-examples/demo-kernel-1.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @date 2011/03/05
 *
 * An example file named demo-kernel-1.
 *
 * This file is part of the DGtal library.
 */

/**
 * Example of DGtal kernel and export with Board2D.
 *  \image html exampleDemoKernel-1.png "Display 2D points in its domain and export woth Board2D."
 *  \example doc-examples/demo-kernel-1.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  // define digital space and domain
  typedef DGtal::SpaceND<2, DGtal::int32_t> MySpace;
  typedef MySpace::Point MyPoint;
  typedef HyperRectDomain<MySpace> MyDomain;
  // define points in this domain
  MyPoint p1(-3,-4);
  MyPoint p2(10,4);
  MyPoint p3(5,1);
  MyDomain domain(p1,p2);
  // 2D display
  Board2D board; 
  board << domain;
  board << p1 << p2 << p3;
  board.saveSVG("demo-kernel-1.svg");
  board.saveEPS("demo-kernel-1.eps");
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
