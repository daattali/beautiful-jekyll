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
//LICENSE-END
/**
 * @file testMostCenteredMSEstimator.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2011/06/28
 *
 * This file is part of the DGtal library
 */

/**
 * Description of testMostCenteredMSEstimator <p>
 */

#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>




#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/io/boards/Board2D.h"

#include "DGtal/topology/KhalimskySpaceND.h"

#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/estimation/MostCenteredMaximalSegmentEstimator.h"
#include "DGtal/geometry/curves/estimation/CCurveLocalGeometricEstimator.h"


#include "ConfigTest.h"


using namespace DGtal;
using namespace std;
using namespace LibBoard;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MostCenteredMaximalSegmentEstimator
///////////////////////////////////////////////////////////////////////////////

/**
 * Test
 *
 */
template<typename I>
bool test(const I& itb, const I& ite)
{
  typedef I ConstIterator;//constIterator
  typedef typename IteratorCirculatorTraits<ConstIterator>::Value Point; 
  typedef ArithmeticalDSSComputer<ConstIterator,typename Point::Coordinate,4> SegmentComputer;//segmentComputer
  typedef TangentVectorFromDSSEstimator<SegmentComputer> SCEstimator; //functor
  typedef typename SCEstimator::Quantity Value; //value
  typedef MostCenteredMaximalSegmentEstimator<SegmentComputer,SCEstimator> Estimator;//estimator
  BOOST_CONCEPT_ASSERT(( concepts::CCurveLocalGeometricEstimator< Estimator > ));
  SegmentComputer sc;
  SCEstimator f; 

  Estimator e(sc,f); 
  e.init(1,itb,ite);

  unsigned int nb = 0; 
  unsigned int nbok = 0; 
  std::vector<Value> v1, v2, v3; 

  {
    trace.info() << "Eval at one element" << endl;
    if (isNotEmpty(itb, ite))
      {
	ConstIterator it = itb; 
	do 
	  {
	    Value q = e.eval(it);  
	    cout << q << " "; 
	    v1.push_back( q ); 
	    ++it; 
	  } while (it != ite); 
      }
    cout << endl;
  }

  {
    trace.info() << "Eval for each element between begin and end " << endl;
    e.eval(itb, ite, std::back_inserter(v2));

    for (typename std::vector<Value>::iterator i = v2.begin(); i != v2.end(); ++i) {
      cout << *i << " "; 
    }
    cout << endl;
  }

  nbok += ( ( v1.size() == v2.size() ) &&
	    ( std::equal(v1.begin(), v1.end(), v2.begin() ) ) )?1:0; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 

  if ( (ite-itb) >= 10) 
    {

      trace.info() << "Eval for each element between begin+4 and begin+9 " << endl;

      e.eval((itb+4),(itb+9),std::back_inserter(v3));

      for (typename vector<Value>::iterator i = v3.begin(); i != v3.end(); ++i) {
  	cout << *i << " "; 
      }
      cout << endl;

      nbok += ( (v3.size() == 5) &&
  		( std::equal( (v1.begin()+4), (v1.begin()+9), v3.begin()) ) )?1:0; 
      nb++; 

      trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
    }

  return (nb == nbok); 
}

/**
 * Applying test on a given data file 
 *
 */
bool testEval(string filename)
{

  trace.info() << endl;
  trace.info() << "Reading GridCurve from " << filename << endl;
  
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);
  typedef KhalimskySpaceND<2> Kspace; //space
  GridCurve<Kspace> c; //building grid curve
  c.initFromVectorStream(instream);
  typedef GridCurve<Kspace >::PointsRange Range;//range
  Range r = c.getPointsRange();//building range

  trace.info() << "Building Estimator (process range as"; 
  trace.info() << ( (c.isClosed())?"closed":"open" ) << ")" << endl;

  if (c.isClosed())
    return test(r.c(), r.c()); 
  else 
    return test(r.begin(), r.end()); 

}

/////////////////////////////////////////////////////////////////////////
//////////////// MAIN ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv)
{
  
  trace.beginBlock ( "Testing class MostCenteredMaximalSegmentEstimator" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  std::string sinus2D4 = testPath + "samples/sinus2D4.dat";
  std::string square = testPath + "samples/smallSquare.dat";
  std::string dss = testPath + "samples/DSS.dat";

  bool res = testEval(sinus2D4)
    && testEval(square)
    && testEval(dss)
    //other tests
    ;
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;

}
