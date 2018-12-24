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
 * @file geometry/curves/greedy-dss-decomposition.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2010/11/26
 *
 * An example file named greedy-dss-decomposition.
 *
 * This file is part of the DGtal library.
 */

/**
 *
 * \example geometry/curves/greedy-dss-decomposition.cpp
 * This example outputs a greedy segmentation of a closed and 4-connected digital curve into DSSs. 
 *
 *  @verbatim
 * $ ./examples/geometry/curves/greedy-dss-decomposition
 * @endverbatim
 *
 * @image html greedy-dss-decomposition.png "Greedy segmentation into DSSs"
 * @image latex greedy-dss-decomposition.png "Greedy segmentation into DSSs"
 *
 *
 * @see \ref moduleArithDSSReco and \ref moduleGridCurveAnalysis
 *
 * @see geometry/curves/greedy-dss-decomposition.cpp
 */

///////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include <iostream>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main( )
{
  trace.beginBlock ( "Example dgtalboard-5-greedy-dss" );

  typedef FreemanChain<int> Contour4; 
  typedef ArithmeticalDSSComputer<Contour4::ConstIterator,int,4> DSS4;
  typedef GreedySegmentation<DSS4> Decomposition4;

  // A Freeman chain code is a string composed by the coordinates of the first pixel, and the list of elementary displacements. 
  std::stringstream ss(stringstream::in | stringstream::out);
  ss << "31 16 11121212121212212121212212122122222322323233323333333323333323303330330030300000100010010010001000101010101111" << endl;
  
  // Construct the Freeman chain
  Contour4 theContour( ss );

  // Segmentation
  Decomposition4 theDecomposition( theContour.begin(),theContour.end(),DSS4() );

  // Draw the domain and the contour
  Point p1( 0, 0 );
  Point p2( 31, 31 );
  Domain domain( p1, p2 );
  Board2D aBoard;
  aBoard << SetMode( domain.className(), "Grid" )
	 << domain
    	 << SetMode( "PointVector", "Grid" ); 

  // Draw each segment
  string styleName = "";
  for ( Decomposition4::SegmentComputerIterator 
	  it = theDecomposition.begin(),
	  itEnd = theDecomposition.end();
	it != itEnd; ++it ) 
    {
      aBoard << SetMode( "ArithmeticalDSS", "Points" )
	     << it->primitive(); 
      aBoard << SetMode( "ArithmeticalDSS", "BoundingBox" )
	     << CustomStyle( "ArithmeticalDSS/BoundingBox", 
       			     new CustomPenColor( Color::Blue ) )
	     << it->primitive();
    } 

  
  aBoard.saveSVG("greedy-dss-decomposition.svg");
  aBoard.saveEPS("greedy-dss-decomposition.eps");
  #ifdef WITH_CAIRO
    aBoard.saveCairo("greedy-dss-decomposition.png"); 
  #endif

  trace.endBlock();

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
