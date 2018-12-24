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
 * @file geometry/curves/estimation/exampleLMST3D.cpp
 * @ingroup Examples
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2015/09/27
 *
 * An example file named LambdaMST3D.
 *
 * This file is part of the DGtal library.
 */


/**
   This example shows the basic usage of the Lambda maximal segment tangent estimation
   in 3D.

@see \ref moduleArithDSSReco

\example geometry/curves/estimation/exampleLMST3D.cpp
*/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iterator>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicTypes.h"
#include "DGtal/helpers/StdDefs.h"

//! [LambdaMST3DHeader]
#include "DGtal/geometry/curves/Naive3DDSSComputer.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"
#include "DGtal/geometry/curves/estimation/LambdaMST3D.h"
//! [LambdaMST3DHeader]
///////////////////////////////////////////////////////////////////////////////


using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////

int main()
{
  //! [LambdaMST3DStandardCtor]
  typedef vector < Point > Container;
  typedef Container::const_iterator ConstIterator;
  typedef Naive3DDSSComputer < ConstIterator, int, 8 > SegmentComputer;
  typedef SaturatedSegmentation < SegmentComputer > Segmentation;
  LambdaMST3D < Segmentation > lmst;
  //! [LambdaMST3DStandardCtor]
  
  // Input points
  Container contour;
  contour.push_back(Point(18,25,18));
  contour.push_back(Point(17,25,19));
  contour.push_back(Point(16,25,20));
  contour.push_back(Point(15,25,21));
  contour.push_back(Point(14,25,22));
  contour.push_back(Point(13,25,23));
  contour.push_back(Point(12,25,24));
  contour.push_back(Point(11,25,25));
  contour.push_back(Point(10,25,26));
  contour.push_back(Point(9,25,27));
  contour.push_back(Point(8,25,28));
  
  //! [LambdaMST3DTangential]
  // Initialization of tangential cover
  Segmentation segmenter ( contour.begin(), contour.end(), SegmentComputer() );
  lmst.attach ( segmenter );
  //! [LambdaMST3DTangential]
  
  //! [LambdaMST3DPoint]
  for ( ConstIterator it = contour.begin(); it != contour.end(); ++it )
    lmst.eval ( it );
  //! [LambdaMST3DPoint]
  
  //! [LambdaMST3DFast]
    lmst.init ( contour.begin(), contour.end() );
    std::vector < RealVector > tangent;
    lmst.eval < std::back_insert_iterator< std::vector < RealVector > > > ( contour.begin(), contour.end(), std::back_insert_iterator< vector < RealVector > > ( tangent ) );
  //! [LambdaMST3DFast]
  
  return 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
