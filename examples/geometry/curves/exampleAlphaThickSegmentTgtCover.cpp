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
 * @file geometry/curves/exampleAlphaThickSegmentTgtCover.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/11/08
 *
 * An example file named exampleAlphaThickSegmentTgtCover.
 *
 * This file is part of the DGtal library.
 */



/**
   This example shows the tangential cover of an noisy contour from the alpha-thick segment primitive with alpha = 4.
   @see \ref moduleAlphaThickSegmentReco

   @image html exampleAlphaThickSegmentTgtCoverAll_Single.png "Tangential cover with alpha-thick segments with alpha = 4"
   @image latex exampleAlphaThickSegmentTgtCoverAll_Single.png "Tangential cover with alpha-thick segments with alpha = 4" width=6cm
   \example geometry/curves/exampleAlphaThickSegmentTgtCover.cpp
*/



///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
//! [SaturatedAlphaThickCoverHeader]
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"
#include "DGtal/base/Circulator.h"
//! [SaturatedAlphaThickCoverHeader]
//! [SaturatedAlphaThickCoverHeaderSingle]
#include "DGtal/geometry/curves/SegmentComputerUtils.h"
//! [SaturatedAlphaThickCoverHeaderSingle]


#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  trace.beginBlock ( "Example of AlphaThickSegment tangential cover obtained from SaturatedSegmentation" );

  //! [SaturatedAlphaThickCoverTypes]
  typedef std::vector<Z2i::RealPoint>::const_iterator RAConstIterator;
  typedef Circulator<RAConstIterator> ConstCirculator;
  typedef AlphaThickSegmentComputer<Z2i::RealPoint, ConstCirculator> AlphaThickSegmentComputer2D;
  typedef SaturatedSegmentation<AlphaThickSegmentComputer2D> AlphaSegmentation;
  //! [SaturatedAlphaThickCoverTypes]


  Board2D aBoard, aBoard2;
  std::string file = examplesPath + "samples/contourSnoisy.sdp";
  std::vector<Z2i::RealPoint> aContour = PointListReader<Z2i::RealPoint>::getPointsFromFile (file);

  // displaying contour
  aBoard << SetMode(aContour[0].className(), "Grid"); 
  aBoard2 << SetMode(aContour[0].className(), "Grid"); 
  std::vector<LibBoard::Point> poly;
  for (unsigned int i = 0; i< aContour.size(); i++)  poly.push_back(LibBoard::Point(aContour[i][0], aContour[i][1]));
  aBoard.setPenColor(DGtal::Color(200, 200, 200));
  aBoard.fillPolyline(poly);
  aBoard2.setPenColor(DGtal::Color(200, 200, 200));
  aBoard2.fillPolyline(poly);

  //! [SaturatedAlphaThickCoverCirculator]
  Circulator<RAConstIterator> circulator (aContour.begin(), aContour.begin(), aContour.end());
  //! [SaturatedAlphaThickCoverCirculator]

  //! [SaturatedAlphaThickCoverComputerSeg]
  AlphaThickSegmentComputer2D computer(4, functions::Hull2D::EuclideanThickness);
  AlphaSegmentation segmentator(circulator, circulator, computer);
  //! [SaturatedAlphaThickCoverComputerSeg]  
  
  //! [SaturatedAlphaThickCoverDisplay]
  AlphaSegmentation::SegmentComputerIterator i = segmentator.begin();
  AlphaSegmentation::SegmentComputerIterator end = segmentator.end();

  for ( ; i != end; ++i) {
    AlphaThickSegmentComputer2D current(*i);
    aBoard << SetMode(current.className(), "BoundingBox");
    aBoard << current;
  }
  //! [SaturatedAlphaThickCoverDisplay]
  aBoard.saveEPS("exampleAlphaThickSegmentTgtCover.eps");
  trace.endBlock();

  trace.beginBlock ( "Example of AlphaThickSegment tangential cover obtained for a single point" );

  // Displaying Tangential cover associated to a single point:
  
  //! [SaturatedAlphaThickCoverSingleInit]
  unsigned int index = 80;
  firstMaximalSegment(computer, circulator+index, circulator, circulator);
  AlphaThickSegmentComputer2D first (computer);
  lastMaximalSegment(computer, circulator+index, circulator, circulator);
  AlphaThickSegmentComputer2D last (computer);
  //! [SaturatedAlphaThickCoverSingleInit]  
  
  aBoard2.setPenColor(DGtal::Color::Blue);
  aBoard2.fillCircle((*(circulator+index))[0], (*(circulator+index))[1], 1.0);
  //! [SaturatedAlphaThickCoverDisplaySingle]  
  while(first.end() != last.end()){
    aBoard2 << SetMode(first.className(), "BoundingBox");
    aBoard2 << first;
    nextMaximalSegment(first, circulator);
  }
  aBoard2 << last;
  //! [SaturatedAlphaThickCoverDisplaySingle]
  
  stringstream name;
  name << "exampleAlphaThickSegmentTgtCoverPoint" << index<< ".eps";
  aBoard2.saveEPS(name.str().c_str());
  trace.endBlock();
  



  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
