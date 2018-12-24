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
 * @file geometry/curves/greedyAlphaThickDecomposition.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/01/30
 *
 * An example file named exampleAlphaThickSegment
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows the greedy decomposition of an noisy contour from the alpha-thick segment primitive with alpha = 4.
   @see \ref moduleAlphaThickSegmentReco

   @image html examplegreedyAlphaThickDecomposition.png "Greedy decomposition with alpha-thick segments with alpha = 4"
   @image latex examplegreedyAlphaThickDecomposition.png "Greedy decomposition with alpha-thick segment with alpha = 4" width=6cm
   \example geometry/curves/greedyAlphaThickDecomposition.cpp
*/



///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"
#include <DGtal/io/readers/GenericReader.h>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Example of greedy alpha thick segment  decompotion" );
  
  typedef  std::vector<Z2i::RealPoint>::const_iterator ConstIterator;
  typedef  AlphaThickSegmentComputer<Z2i::RealPoint, ConstIterator > AlphaThickSegmentComputer2D;
  
  Board2D aBoard;
  std::string file = examplesPath + "samples/contourSnoisy.sdp";
  std::vector<Z2i::RealPoint> aContour = PointListReader<Z2i::RealPoint>::getPointsFromFile (file);

  typedef GreedySegmentation<AlphaThickSegmentComputer2D> DecompositionAT;

  // displaying contour
  aBoard << SetMode(aContour[0].className(), "Grid"); 
  std::vector<LibBoard::Point> poly;
  for (unsigned int i = 0; i< aContour.size(); i++)  poly.push_back(LibBoard::Point(aContour[i][0], aContour[i][1]));
  aBoard.setPenColor(DGtal::Color::Gray);
  aBoard.fillPolyline(poly);
  
  // Computing greedy Alpha Thick decomposition.
  //! [greedyAlphaThickDecompositionModeDisplay]
  aBoard << SetMode("AlphaThickSegment", "BoundingBox");
  //! [greedyAlphaThickDecompositionModeDisplay]
  
  //! [greedyAlphaThickDecompositionAlgo]
  DecompositionAT theDecomposition(aContour.begin(), aContour.end(), AlphaThickSegmentComputer2D(4)); 
  //! [greedyAlphaThickDecompositionAlgo]

  //! [greedyAlphaThickDecompositionDisplay]  
  for ( DecompositionAT::SegmentComputerIterator 
           it = theDecomposition.begin(),
           itEnd = theDecomposition.end();
         it != itEnd; ++it ) 
     {
       aBoard << CustomStyle( (*it).className(), 
                              new CustomPenColor( Color::Blue ) );
       aBoard<< *it;
     } 
  //! [greedyAlphaThickDecompositionDisplay]  

  aBoard.saveEPS("greedyAlphaThickDecomposition.eps");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
