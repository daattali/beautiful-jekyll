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
 * @file doc-examples/labelledMapBestParameters.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @date 2011/03/05
 *
 * An example file named labelledMapBestParameters.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/LabelledMap.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
void usage()
{
  cerr << "Usage: ./labelledMapBestParameters <L> <p> <q>" << endl
       << "       Tries to find the best values N and M which will minimized" << endl
       << "       the memory usage of a LabelledMap, for the distribution" << endl
       << "       specified by the parameters." << endl
       << "       - L: max number of labels." << endl
       << "       - p: If there is a possibility to have a data, this probability is used to define a geometric distribution that defines the number of data (ie valid labels) at this place. The smaller, the higher is the expectation. 0.5 means E(X) = 1.." << endl
       << "       - q: probability that there is no data at this location." << endl;
}
int main( int argc, char** argv )
{
  typedef double Data;
  if ( argc < 4 ) 
    {
      usage();
      return 1;
    }

  std::pair< unsigned int, unsigned int > res =
    DGtal::detail::argminLabelledMapMemoryUsageForGeometricDistribution<Data>
    ( atoi( argv[ 1 ] ), atof( argv[ 3 ] ), atof( argv[ 2 ] ) );
  cout << res.first << " " << res.second << endl;
  return 0;
}
