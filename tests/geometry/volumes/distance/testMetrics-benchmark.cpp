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
 * @file testMetrics-benchmark.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/03
 *
 * Functions for testing class Metrics-benchmark.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
#include <boost/lexical_cast.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Metrics-benchmark.
///////////////////////////////////////////////////////////////////////////////

template<int p>
bool runATest( unsigned int maxTest)
{
  ExactPredicateLpSeparableMetric<Z3i::Space, p> exactMetric;
  InexactPredicateLpSeparableMetric<Z3i::Space> approxMetric(p);
  double sum=0.0, d=0,d2=0, MSE=0;
  std::string txt = "Testing Exponent" +   boost::lexical_cast<string>(p);
  
    
  DGtal::Dimension dim = 1000;
  trace.beginBlock(txt);
  trace.beginBlock("Exact Predicate run");
  for(unsigned int i=0; i< maxTest; ++i)
    {
      Z3i::Point P( rand() % dim,rand() % dim ,rand() % dim );
      Z3i::Point Q( rand() % dim, rand() % dim, rand() % dim);
      sum += exactMetric(P,Q);
    }

  trace.endBlock();
  
  trace.beginBlock("Inexact Predicate run");
 for(unsigned int i=0; i< maxTest; ++i)
    {
      Z3i::Point P( rand() % dim,rand() % dim ,rand() % dim );
      Z3i::Point Q( rand() % dim, rand() % dim, rand() % dim);
      sum += approxMetric(P,Q);
    }
  trace.endBlock();
  

  trace.beginBlock("Both with comparison run");
  for(unsigned int i=0; i< maxTest; ++i)
    {
      Z3i::Point P( rand() % dim,rand() % dim ,rand() % dim );
      Z3i::Point Q( rand() % dim, rand() % dim, rand() % dim);
      d = exactMetric(P,Q);
      d2 = approxMetric(P,Q);
      MSE += (d-d2)*(d-d2);
    }
  trace.endBlock();
  trace.info() << "Mean Square Error = "<<MSE<<std::endl;
  trace.endBlock();
  return true;
}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Metrics-benchmark" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = runATest<2>(1000000) &&
    runATest<4>(10000000);
    runATest<6>(1000000);
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
