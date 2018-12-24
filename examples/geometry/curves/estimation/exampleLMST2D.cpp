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
 * @file geometry/curves/estimation/exampleLMST2D.cpp
 * @ingroup Examples
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2015/09/27
 *
 * An example file named LambdaMST2D.
 *
 * This file is part of the DGtal library.
 */

/**
   This example shows the basic usage of the Lambda maximal segment tangent estimation
   in 2D.

@see \ref moduleArithDSSReco

\example geometry/curves/estimation/exampleLMST2D.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iterator>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/helpers/StdDefs.h"

//! [LambdaMST2DHeader]
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"
#include "DGtal/geometry/curves/estimation/LambdaMST2D.h"
//! [LambdaMST2DHeader]
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  //! [LambdaMST2DStandardCtor]
  typedef vector < Point > Container;
  typedef Container::const_iterator ConstIterator;
  typedef ArithmeticalDSSComputer < ConstIterator, int, 8 > SegmentComputer;
  typedef SaturatedSegmentation<SegmentComputer> Segmentation;
  LambdaMST2D < Segmentation > lmst;
  //! [LambdaMST2DStandardCtor]
  
  // Input points
  Container contour;
  contour.push_back(Point(18,18));
  contour.push_back(Point(17,19));
  contour.push_back(Point(16,20));
  contour.push_back(Point(15,21));
  contour.push_back(Point(14,22));
  contour.push_back(Point(13,23));
  contour.push_back(Point(12,24));
  contour.push_back(Point(11,25));
  contour.push_back(Point(10,26));
  contour.push_back(Point(9,27));
  contour.push_back(Point(8,28));
  
  //! [LambdaMST2DTangential]
  // Initialization of tangential cover
  Segmentation segmenter ( contour.begin(), contour.end(), SegmentComputer() );
  lmst.attach ( segmenter );
  //! [LambdaMST2DTangential]
  
  //! [LambdaMST2DPoint]
  for ( ConstIterator it = contour.begin(); it != contour.end(); ++it )
    lmst.eval ( it );
  //! [LambdaMST2DPoint]
  
  //! [LambdaMST2DFast]
  lmst.init ( contour.begin(), contour.end() );
  std::vector < RealVector > tangent;
  lmst.eval < back_insert_iterator< vector < RealVector > > > ( contour.begin(), contour.end(),  back_inserter ( tangent ) );
  //! [LambdaMST2DFast]
  
  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
