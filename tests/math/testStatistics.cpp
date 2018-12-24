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
 * @file testStatistics.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/24
 *
 * Functions for testing class Statistics.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <vector>
#include "DGtal/math/Statistic.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Statistics.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testStatistics()
{
  unsigned int nbok = 0;
  unsigned int nb = 3;
  
  trace.beginBlock ( "Testing Statistics ..." );

  Statistic<double> stat;
  
  for(unsigned int k=0; k < 1000; k++)
    stat.addValue((double)k);
  
  stat.terminate();
  
  trace.info() << "Mean value = "<<stat.mean()  << std::endl;
  nbok += (stat.mean()==499.5) ? 1 : 0; 
  trace.info() << "Variance value = "<<stat.variance()<<std::endl;
  trace.info() << "Max value = "<<stat.max()<<std::endl;
  nbok += (stat.max()==999) ? 1 : 0; 
  trace.info() << "Min value = "<<stat.min()<<std::endl;
  nbok += (stat.min()==0)  ? 1 : 0; 
 
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testStatisticsSaving()
{
  unsigned int nbok = 0;
  unsigned int nb = 4;
  
  trace.beginBlock ( "Testing Statistics with saving option ..." );

  Statistic<double> stat(true);
  
  
  for(unsigned int k=0; k < 100; k++)
    stat.addValue(99);
  stat.addValue(88);
  for(unsigned int k=0; k < 100; k++)
    stat.addValue(77);
  
  stat.terminate();
  
  trace.info() << "Mean value = "<<stat.mean()  << std::endl;
  nbok += (stat.mean()==88) ? 1 : 0; 
  trace.info() << "Variance value = "<<stat.variance()<<std::endl;
  trace.info() << "Max value = "<<stat.max()<<std::endl;
  nbok += (stat.max()==99) ? 1 : 0; 
  trace.info() << "Min value = "<<stat.min()<<std::endl;
  nbok += (stat.min()==77)  ? 1 : 0; 
  trace.info() << "Median value = "<<stat.median()<<std::endl;
  nbok += (stat.median()==88)  ? 1 : 0; 
 
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Statistics" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testStatistics(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;

  trace.beginBlock ( "Testing class Statistics (with option for saving samples)" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res2 = testStatisticsSaving(); // && ... other tests
  trace.emphase() << ( res2 ? "Passed." : "Error." ) << endl;


  trace.endBlock();
  return (res &&res2) ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
