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
 * @file geometry/curves/exampleAlphaThickSegment.cpp
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
   This example a simple alpha-thick segment recognition given from a freeman chain contour.
   @see \ref moduleAlphaThickSegmentReco

   @image html exampleAlphaThickSegment.png "Simple example of some alpha-thick segments recognition with alpha = 2, 5  and 15."
   @image latex exampleAlphaThickSegment.png "Simple example of some alpha-thick segments recognition with alpha = 2, 5  and 15." width=6cm
   \example geometry/curves/exampleAlphaThickSegment.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/readers/PointListReader.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main(  )
{
  trace.beginBlock ( "Example exampleAlphaThickSegment" );


  typedef FreemanChain<Z2i::Space::Integer>::ConstIterator FCConstIterator;
  typedef  AlphaThickSegmentComputer< Z2i::Point, FCConstIterator > AlphaThickSegmentComputer2D;
  Board2D aBoard;

  // Reading input contour
  std::string freemanChainFilename = examplesPath + "samples/contourS.fc";
  fstream fst;
  fst.open (freemanChainFilename.c_str(), ios::in);
  FreemanChain<Z2i::Space::Integer> fc(fst);
  fst.close();
  aBoard << fc;

  //construction of an AlphaThickSegmentComputer2D from the freemanchain iterator
  AlphaThickSegmentComputer2D anAlphaSegment(15), anAlphaSegment2(5), anAlphaSegment3(2);
  anAlphaSegment.init(fc.begin());                           
  while (anAlphaSegment.end() != fc.end() && 
         anAlphaSegment.extendFront()) {
  }
  aBoard << anAlphaSegment;  
  
  anAlphaSegment2.init(fc.begin());
  while (anAlphaSegment2.end() != fc.end() && anAlphaSegment2.extendFront()) {
  }
  aBoard  << CustomStyle( anAlphaSegment2.className(), new CustomColors( DGtal::Color::Blue, DGtal::Color::None ) );  
  aBoard << anAlphaSegment2;
  
  // Example of thickness definition change: usin the euclidean thickness definition.
  //! [exampleAlphaThickSegmentEuclDef]
  AlphaThickSegmentComputer2D anAlphaSegment2Eucl(5, functions::Hull2D::EuclideanThickness);
  //! [exampleAlphaThickSegmentEuclDef]

  anAlphaSegment2Eucl.init(fc.begin());
  while (anAlphaSegment2Eucl.end() != fc.end() && 
         anAlphaSegment2Eucl.extendFront()) {
  }

  aBoard << CustomStyle( anAlphaSegment2Eucl.className(), 
                         new CustomColors( DGtal::Color(20, 250, 255), DGtal::Color::None ) ); 
  aBoard << anAlphaSegment2Eucl;

  
  FCConstIterator fcIt = fc.begin();
  while (anAlphaSegment3.extendFront(*fcIt)) {
    fcIt++;
  }


  aBoard  << CustomStyle( anAlphaSegment3.className(), new CustomColors( DGtal::Color::Green, DGtal::Color::None ) );  
  aBoard << anAlphaSegment3;
  
 

  aBoard.saveEPS("exampleAlphaThickSegment.eps");

  trace.endBlock();
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
