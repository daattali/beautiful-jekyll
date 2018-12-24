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
 * @file testL1LengthEstimator.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/27
 *
 * Functions for testing class L1LengthEstimator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"


#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/geometry/2d/L1LengthEstimator.h"
#include "DGtal/geometry/2d/TwoStepLocalLengthEstimator.h"
#include "DGtal/geometry/2d/MLPLengthEstimator.h"
#include "DGtal/geometry/2d/FPLengthEstimator.h"
#include "DGtal/geometry/2d/DSSLengthEstimator.h"

#include "ConfigTest.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing Length Estimator classes.
///////////////////////////////////////////////////////////////////////////////
/**
 * L1 test
 *
 */
bool testL1LengthEstimator(std::string &filename)
{

  trace.info() << "Reading GridCurve " << endl;
  
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);

  GridCurve<KhalimskySpaceND<2> > c; //grid curve
  c.initFromVectorStream(instream);

  //////////////////////// L1
  GridCurve<KhalimskySpaceND<2> >::ArrowsRange ra = c.getArrowsRange(); //range
  L1LengthEstimator<  GridCurve<KhalimskySpaceND<2> >::ArrowsRange::ConstIterator > l1length;
  TwoStepLocalLengthEstimator<  GridCurve<KhalimskySpaceND<2> >::ArrowsRange::ConstIterator > locallength(1.0,sqrt(2.0));
    
  l1length.init(1, ra.begin(), ra.end(), c.isClosed());
  trace.info() << "L1 length (h=1) = "<< l1length.eval()<<std::endl;

  l1length.init(10, ra.begin(), ra.end(), c.isClosed());
  trace.info() << "L1 length (h=10) = "<< l1length.eval()<<std::endl;

  ////////////////////// Local 2steps
  TwoStepLocalLengthEstimator<  GridCurve<KhalimskySpaceND<2> >::ArrowsRange::ConstIterator > locallength(1.0,sqrt(2.0));
 
  localength.init(1, ra.begin(), ra.end(), c.isClosed());
  trace.info() << "Local length (h=1) = "<< localength.eval()<<std::endl;

    
  //////////////////////// MLP
  GridCurve<KhalimskySpaceND<2> >::PointsRange rp = c.getPointsRange(); //range
  MLPLengthEstimator<  GridCurve<KhalimskySpaceND<2> >::PointsRange::ConstIterator > MLPlength;
    
  MLPlength.init(1, rp.begin(), rp.end(), c.isClosed());
  trace.info() << "MLP Length (h=1) = "<< MLPlength.eval()<<std::endl;

  MLPlength.init(10, rp.begin(), rp.end(), c.isClosed());
  trace.info() << "MLP Length (h=10) = "<< MLPlength.eval()<<std::endl;

  //////////////////////// FP
  FPLengthEstimator<  GridCurve<KhalimskySpaceND<2> >::PointsRange::ConstIterator > FPlength;
    
  FPlength.init(1, rp.begin(), rp.end(), c.isClosed());
  trace.info() << "FP Length (h=1) = "<< FPlength.eval()<<std::endl;

  FPlength.init(10, rp.begin(), rp.end(), c.isClosed());
  trace.info() << "FP Length (h=10) = "<< FPlength.eval()<<std::endl;

  //////////////////////// DSS
  DSSLengthEstimator<  GridCurve<KhalimskySpaceND<2> >::PointsRange::ConstIterator > DSSlength;
    
  DSSlength.init(1, rp.begin(), rp.end(), c.isClosed());
  trace.info() << "DSS Length (h=1) = "<< DSSlength.eval()<<std::endl;

  DSSlength.init(10, rp.begin(), rp.end(), c.isClosed());
  trace.info() << "DSS Length (h=10) = "<< DSSlength.eval()<<std::endl;

  return true;
}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class LengthEstimators" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  std::string sinus2D4 = testPath + "samples/sinus2D4.dat";



  bool res = testL1LengthEstimator(sinus2D4); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
