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
 * @file testHistogram.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/10/25
 *
 * Functions for testing class Histogram.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/math/Statistic.h"
#include "DGtal/math/Histogram.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Histogram.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
double getRandomNumber( double first, double last )
{
  double v = ((double)rand()) / (double) RAND_MAX;
  return v * ( last - first ) + first;
}

bool testHistogramUniform()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  Statistic<double> stat( true );
  for(unsigned int k=0; k < 1000; k++)
    stat.addValue( getRandomNumber( -1.0, 1.0 ) );
  stat.terminate();
  Histogram<double> hist;
  hist.init( Histogram<double>::Scott, stat );
  hist.addValues( stat.begin(), stat.end() );
  hist.terminate();
  for ( unsigned int i = 0; i < hist.size(); ++i )
    std::cout << i << " " << hist.pdf( i ) << " " << hist.cdf( i ) << std::endl;
  ++nb; nbok += hist.cdf( hist.size()-1 ) > 0.9999 ? 1 : 0;
  return nbok == nb;
}

bool testHistogramGaussian()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  Statistic<double> stat( true );
  for(unsigned int k=0; k < 1000; k++)
    stat.addValue( getRandomNumber( -1.0, 1.0 ) + getRandomNumber( -1.0, 1.0 ) );
  stat.terminate();
  Histogram<double> hist;
  hist.init( Histogram<double>::Scott, stat );
  hist.addValues( stat.begin(), stat.end() );
  hist.terminate();
  for ( unsigned int i = 0; i < hist.size(); ++i )
    std::cout << i << " " << hist.pdf( i ) << " " << hist.cdf( i ) << std::endl;
  ++nb; nbok += hist.cdf( hist.size()-1 ) > 0.9999 ? 1 : 0;
  return nbok == nb;
}

bool testHistogramGaussian2()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  Statistic<double> stat( true );
  for(unsigned int k=0; k < 1000; k++)
    stat.addValue( getRandomNumber( -1.0, 1.0 ) + getRandomNumber( -1.0, 1.0 )
                   + getRandomNumber( -1.0, 1.0 ) );
  stat.terminate();
  Histogram<double> hist;
  hist.init( Histogram<double>::Scott, stat );
  hist.addValues( stat.begin(), stat.end() );
  hist.terminate();
  for ( unsigned int i = 0; i < hist.size(); ++i )
    std::cout << i << " " << hist.pdf( i ) << " " << hist.cdf( i ) << std::endl;
  ++nb; nbok += hist.cdf( hist.size()-1 ) > 0.9999 ? 1 : 0;
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int, char** )
{
  trace.beginBlock ( "Testing class Histogram" );

  bool res = testHistogramUniform()
    && testHistogramGaussian()
    && testHistogramGaussian2();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;

  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
