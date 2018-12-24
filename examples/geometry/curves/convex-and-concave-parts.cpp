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
 * @file geometry/curves/convex-and-concave-parts.cpp
 * @ingroup Examples
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2011/01/24
 *
 * An example file named convex-and-concave-parts.
 *
 * This file is part of the DGtal library.
 */
/**
   This example outputs the cover of an open digital curve by maximal DSSs. 
Maximal DSSs are displayed in blue, green, yellow in convex, concave, inflexion parts respectively. 
Ends are black. 
Convex (resp. concave) parts are defined as sequences of maximal DSSs of increasing (resp. decreasing) slope. 

@verbatim
$ ./examples/geometry/curves/convex-and-concave-parts
@endverbatim

Note that the chain code of the input digital curve may be passed as argument as follows: 
@verbatim
$ ./examples/geometry/curves/convex-and-concave-parts 0300303303033030303000010101011010110100000303303033030303
@endverbatim


@image html convex-and-concave-parts.png "Decomposition into convex and concave parts"
@image latex convex-and-concave-parts.png "Decomposition into convex and concave parts"


@see \ref moduleArithDSSReco and \ref moduleGridCurveAnalysis

\example geometry/curves/convex-and-concave-parts.cpp
*/

///////////////////////////////////////////////////////////////////////////////
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include "DGtal/base/Common.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/Color.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"
///////////////////////////////////////////////////////////////////////////////
#include "ConfigExamples.h"

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////

/**
 * @brief Function that draws the maximal segments
 * with a color that depends on the local convexity:
 * - blue in a convex part,
 * - green in a concave part,
 * - yellow in an inflection part (both convex and concave),
 * - black in an end part (of a connected part).
 *
 * @param itb begin iterator on an ArithmeticalDSSComputer
 * @param ite end iterator on an ArithmeticalDSSComputer
 * @param aBoard board to draw
 *
 * @tparam Iterator a model of forward iterator and
 * CSegmentComputerIterator
 * @tparam Board a Board2D type
 */
template <typename Iterator, typename Board>
void drawCCP(const Iterator& itb, const Iterator& ite, Board& aBoard)
{

  //choose the drawing mode
  aBoard << SetMode( "ArithmeticalDSS", "BoundingBox" );
  //prepare the drawing style and the pen color
  string aStyleName = "ArithmeticalDSS/BoundingBox";
  CustomPenColor* aPenColor;

  //for each maximal segment
  for (Iterator i(itb); i != ite; ++i) {

    //get the current maximal segment
    typedef typename Iterator::SegmentComputer::Primitive DSS;
    DSS maximalDSS = i->primitive();

    //if located at the end of a connected part
    if ( !(i.intersectNext() && i.intersectPrevious()) ) {

      aPenColor = new CustomPenColor( Color::Black );

      //otherwise
    } else {

      //get the points located before and after the maximal segment
      typedef typename DSS::Point Point;
      Point beforeFirst = *(--(i->begin()));
      Point afterLast = *(i->end());

      //remainders and bounds
      typedef typename DSS::Integer Integer;
      Integer r1 = maximalDSS.remainder(beforeFirst);
      Integer r2 = maximalDSS.remainder(afterLast);
      Integer mu = maximalDSS.mu();
      Integer omega = maximalDSS.omega();

      //configurations
      if ( (r1<=mu-1)&&(r2<=mu-1) ) {                    //concave
        aPenColor = new CustomPenColor( Color::Green);
      } else if ( (r1>=mu+omega)&&(r2>=mu+omega) ) {     //convex
        aPenColor = new CustomPenColor( Color::Blue );
      } else if ( (r1>=mu+omega)&&(r2<=mu-1) ) {         //convex to concave
        aPenColor = new CustomPenColor( Color::Yellow );
      } else if ( (r1<=mu-1)&&(r2>=mu+omega) ) {         //concave to convex
        aPenColor = new CustomPenColor( Color::Yellow );
      } else {                                           //pb
        aPenColor = new CustomPenColor( Color::Red );
      }

    }

    // draw the maximal segment on the board
    aBoard << CustomStyle( aStyleName, aPenColor )
           << maximalDSS;

  }

}

/**
 * @brief Perform a saturated segmentation into
 * maximal digital straight segments of a given
 * range of integer points and draw the result.
 * @param itb begin iterator
 * @param ite end iterator
 * @param aBoard board to draw
 *
 * @tparam Iterator a model of forward iterator on
 * digital points
 * @tparam Board a Board2D type
 */
template <typename Iterator, typename Board>
void segmentationIntoMaximalDSSs(const Iterator& itb, const Iterator& ite,
                                 Board& aBoard)
{
  typedef typename IteratorCirculatorTraits<Iterator>::Value::Coordinate Coordinate;

  //choose the primitive computer and the segmentation
  typedef ArithmeticalDSSComputer<Iterator,Coordinate,4> RecognitionAlgorithm;
  typedef SaturatedSegmentation<RecognitionAlgorithm> Segmentation;

  //create the segmentation
  RecognitionAlgorithm algo;
  Segmentation s(itb,ite,algo);

  //draw the result
  drawCCP(s.begin(), s.end(), aBoard);
}


/**
 * @brief Program that draws the maximal segments
 * of digital curve whose chain code may be given
 * as an argument. The chain code must be a sequence
 *  of characters belonging to the set {0,1,2,3}.
 * @param argc number of arguments
 * @param argv array of arguments
 * @return 0
 */
int main( int argc, char** argv )
{

  trace.beginBlock ( "Example convex-and-concave-parts" );

  Board2D aBoard; //create a board

  //create a chain code
  string codes;
  if (argc >= 2) codes = argv[1];
  else codes = "030030330303303030300001010101101011010000030330303303030300001010110101011010000033";

  stringstream ss(stringstream::in | stringstream::out);
  ss << "0 0 " << codes << endl;
  FreemanChain<int> theContour( ss );

  trace.info() << "Processing of " << ss.str() << endl;

  //draw the digital contour
  aBoard
   << SetMode( "PointVector", "Grid" )
   << theContour;

  //draw the maximal segments
  segmentationIntoMaximalDSSs(theContour.begin(), theContour.end(), aBoard);

  //save the drawing
  aBoard.saveSVG("convex-and-concave-parts.svg");
  #ifdef WITH_CAIRO
    aBoard.saveCairo("convex-and-concave-parts.png"); 
  #endif

  trace.endBlock();

  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
