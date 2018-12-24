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
 * @file testMetricBalls.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/11
 *
 * Functions for testing class MetricBalls.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::functors;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class MetricBalls.
///////////////////////////////////////////////////////////////////////////////


template <int norm>
bool testExactMetricBalls()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(64,64));
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, norm> Metric;
  Z2i::DigitalSet set(domain);
  
  set.insertNew(Z2i::Point(32,32));
  typedef NotPointPredicate< Z2i::DigitalSet > NegPred;
  // SetPredicate<Z2i::DigitalSet> setpred(set); 
  NegPred predicate( set );
  
  typedef  DistanceTransformation< Z2i::Space, NegPred, Metric> DT;
  Metric metric;
  DT dt( &domain, &predicate, &metric);
  
  
  Board2D board;
  typedef HueShadeColorMap<typename DT::Value,2> Hue;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Hue> (board, dt,
                                  0.0,
                                  32*sqrt(2)/2.0);
  
  std::string title = "image-ball-" +  boost::lexical_cast<string>( norm )+".png" ;
#ifdef WITH_CAIRO
  board.saveCairo(title.c_str(), Board2D::CairoPNG );
#endif  
  return nbok == nb;
}

bool testInexactMetricBalls(double norm)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  Z2i::Domain domain(Z2i::Point(0,0), Z2i::Point(64,64));
  typedef InexactPredicateLpSeparableMetric<Z2i::Space> Metric;
  Z2i::DigitalSet set(domain);
  
  set.insertNew(Z2i::Point(32,32));
  typedef NotPointPredicate< Z2i::DigitalSet > NegPred;
  // SetPredicate<Z2i::DigitalSet> setpred(set); 
  NegPred predicate( set );
  
  typedef  DistanceTransformation< Z2i::Space, NegPred, Metric> DT;
  Metric metric(norm);
  DT dt( &domain, &predicate, &metric);
  
  
  Board2D board;
  typedef HueShadeColorMap< DT::Value,2> Hue;
  board.setUnit ( LibBoard::Board::UCentimeter );
  Display2DFactory::drawImage<Hue> (board, dt,
                                  0.0,
                                  32*sqrt(2)/2.0);
  
  std::string title = "image-ball-" +  boost::lexical_cast<string>( norm )+".png" ;
#ifdef WITH_CAIRO
  board.saveCairo(title.c_str(), Board2D::CairoPNG );
#endif  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class MetricBalls" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testExactMetricBalls<2>()
    && testExactMetricBalls<1>()
    && testExactMetricBalls<4>()
    && testExactMetricBalls<8>()
    && testInexactMetricBalls(1.4)
    && testInexactMetricBalls(43.1)
    && testInexactMetricBalls(0.8)
    ; // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
