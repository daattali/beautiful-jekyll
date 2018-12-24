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
 * @file testLambdaMST3D.cpp
 * @ingroup Tests
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, A3SI, France
 *
 * @date 2014/10/03
 *
 * Functions for testing class LambdaMST3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/PointListReader.h"
#include "DGtal/geometry/curves/Naive3DDSSComputer.h"
#include "DGtal/geometry/curves/estimation/LambdaMST3D.h"
#include "DGtal/geometry/curves/SaturatedSegmentation.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LambdaMST3D.
///////////////////////////////////////////////////////////////////////////////

class testLambdaMST3D
{
  typedef DGtal::Z3i::Point Point;
  typedef DGtal::Z2i::Point Point2D;
  typedef std::vector < Point > Range;
  typedef std::list < Point2D > Range2D;
  typedef Range::const_iterator ConstIterator;
  typedef Range2D::const_iterator ConstIterator2D;
  typedef Naive3DDSSComputer < ConstIterator, int, 8 > SegmentComputer;
  typedef SaturatedSegmentation<SegmentComputer> Segmentation;
  typedef ArithmeticalDSSComputer < ConstIterator2D, int, 8 > SegmentComputer2D;
  typedef SaturatedSegmentation<SegmentComputer2D> Segmentation2D;
private:
  Range curve;
public:
  testLambdaMST3D ()
  {
    fstream inputStream;
    inputStream.open ( (testPath + "samples/sinus3D.dat").c_str(), std::ios::in );
    try {
      curve = PointListReader<Point>::getPointsFromInputStream ( inputStream );
      if ( curve.size() == 0) throw IOException();
    } catch (DGtal::IOException & ioe) {
      trace.error() << "Size is null." << endl;
    }
  }
  bool lambda64ByPoint ()
  {
    Segmentation segmenter ( curve.begin(), curve.end(), SegmentComputer() );
    LambdaMST3D < Segmentation > lmst64;
    lmst64.attach ( segmenter );
    lmst64.init ( curve.begin(), curve.end() );
    for ( ConstIterator it = curve.begin(); it != curve.end(); ++it )
    {
      lmst64.eval ( it );
    }
    return true;
  }
  bool lambda64()
  {
    Segmentation segmenter ( curve.begin(), curve.end(), SegmentComputer() );
    LambdaMST3D < Segmentation > lmst64;
    lmst64.attach ( segmenter );
    lmst64.init ( curve.begin(), curve.end() );
    vector < RealVector > tangent;
    lmst64.eval < back_insert_iterator< vector < RealVector > > > ( curve.begin(), curve.end(), back_insert_iterator< vector < RealVector > > ( tangent ) );
    return true;
  }
};


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int , char**  )
{
    bool res = true;
    testLambdaMST3D testLMST;
    trace.beginBlock ( "Testing LambdaMST3D" );
        trace.beginBlock ( "Testing point only calculation" );
          res &= testLMST.lambda64ByPoint();
        trace.endBlock();
        trace.beginBlock ( "Testing calculation for whole curve" );
           res &= testLMST.lambda64();
        trace.endBlock();
    trace.endBlock();
    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
