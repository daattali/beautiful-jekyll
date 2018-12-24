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
 * @file
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 *
 * @date 2010/03/03
 *
 * This file is part of the DGtal library
 */

/**
 * Description of test_trace' <p>
 * Aim: simple test of \ref MeasureOfStraighLines
 */

#include <cstdio>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/math/MeasureOfStraightLines.h"


using namespace DGtal;
using namespace std;



/**
 * Compute the measure of the unit square [0,1]x[0,1]
 *
 * Expected value : sqrt{2}/2
 **/
void testUnitSquare()
{
    vector<double> a;
    vector<double> b;

    a.push_back(0);
    b.push_back(0);
    a.push_back(1);
    b.push_back(0);
    a.push_back(1);
    b.push_back(1);
    a.push_back(0);
    b.push_back(1);

    MeasureOfStraightLines measure;


    trace.info() << "Measure of the Straight of Lines of the unit square = " << measure.computeMeasure(a,b)<< std::endl;
    trace.emphase() <<"Expected value = 0.707107 (sqrt(2)/2)"<<endl;
}


/**
 * Compute the measure of the unit square [0,1]x[0,1]
 *
 * Expected value : sqrt{2}/2
 **/
void testUnitSquareCentroid()
{
    vector<double> a;
    vector<double> b;

    a.push_back(0);
    b.push_back(0);
    a.push_back(1);
    b.push_back(0);
    a.push_back(1);
    b.push_back(1);
    a.push_back(0);
    b.push_back(1);

    MeasureOfStraightLines measure;

    trace.info() << "Centroid measure of the unit square = (" << measure.computeCentroidA(a,b)
    << ","<<measure.computeCentroidB(a,b)<<")"<<std::endl;
    trace.emphase() <<"Expected value = (0.4142,0.5)"<<endl;
}


int main(int argc, char **argv)
{
  trace.beginBlock ( "Testing class MeasureOfStraightLines" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  testUnitSquare();
  testUnitSquareCentroid();
  
  trace.endBlock();
  
  return 0;
}

/** @ingroup Tests **/
