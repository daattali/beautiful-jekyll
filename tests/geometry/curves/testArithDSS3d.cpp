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
 * @file testArithDSS3d.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2011/06/01
 *
 * This file is part of the DGtal library
 */

/**
 * Description of testArithDSS3d <p>
 * Aim: simple test of \ref StandardDSS6Computer
 */




#include <iostream>
#include <iterator>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>

#include "DGtal/base/Common.h"
#include "DGtal/base/Exceptions.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/geometry/curves/StandardDSS6Computer.h"
#include "DGtal/geometry/curves/GreedySegmentation.h"

using namespace DGtal;
using namespace std;


///////////////////////////////////////////////////////////////////////////////
// Functions for testing class StandardDSS6Computer.
///////////////////////////////////////////////////////////////////////////////
/**
 * simple test
 *
 */
bool testDSSreco()
{

  typedef PointVector<3,int> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef StandardDSS6Computer<Iterator,int,4> SegmentComputer;  
  
  std::vector<Point> sequence;
  sequence.push_back(Point(0,0,0));
  sequence.push_back(Point(1,0,0));
  sequence.push_back(Point(2,0,0));
  sequence.push_back(Point(2,1,0));
  sequence.push_back(Point(2,1,1));
  sequence.push_back(Point(3,1,1));
  sequence.push_back(Point(4,1,1));
  sequence.push_back(Point(4,2,1));
  sequence.push_back(Point(4,2,2));
  sequence.push_back(Point(5,2,2));
  sequence.push_back(Point(6,2,2));
  sequence.push_back(Point(6,3,2));
  sequence.push_back(Point(6,3,3));
  sequence.push_back(Point(6,4,3));
  sequence.push_back(Point(6,4,4));
  sequence.push_back(Point(6,5,4));
  
  // Adding step
  trace.beginBlock("Add points while it is possible and display the result");

  SegmentComputer algo;  
  Iterator i = sequence.begin();  
  algo.init(i);
  trace.info() << "init with " << (*i) << std::endl;

    while ( (algo.end() != sequence.end())
	    && algo.extendFront()) {
      trace.info() << "extended with " << (*(--algo.end())) << std::endl;
    }
    

    trace.info() << algo << " " << algo.isValid() << std::endl;

    trace.endBlock();

  return ( algo.isValid() && (algo.end() == (sequence.begin()+13)) );  
}


/**

 * segmentation test
 *
 */
bool testSegmentation()
{

  typedef PointVector<3,int> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef StandardDSS6Computer<Iterator,int,4> SegmentComputer;  
  typedef GreedySegmentation<SegmentComputer> Decomposition;

  std::vector<Point> sequence;
  sequence.push_back(Point(0,0,0));
  sequence.push_back(Point(1,0,0));
  sequence.push_back(Point(2,0,0));
  sequence.push_back(Point(2,1,0));
  sequence.push_back(Point(2,1,1));
  sequence.push_back(Point(3,1,1));
  sequence.push_back(Point(4,1,1));
  sequence.push_back(Point(4,2,1));
  sequence.push_back(Point(4,2,2));
  sequence.push_back(Point(5,2,2));
  sequence.push_back(Point(6,2,2));
  sequence.push_back(Point(6,3,2));
  sequence.push_back(Point(6,3,3));
  sequence.push_back(Point(6,4,3));
  sequence.push_back(Point(6,4,4));
  sequence.push_back(Point(6,5,4));
  
  //Segmentation
  trace.beginBlock("Segmentation test");
    
    SegmentComputer algo;
    Decomposition theDecomposition(sequence.begin(), sequence.end(), algo);
           
    unsigned int c = 0;
    Decomposition::SegmentComputerIterator i = theDecomposition.begin();
    for ( ; i != theDecomposition.end(); ++i) {
      SegmentComputer currentSegmentComputer(*i);
      trace.info() << currentSegmentComputer << std::endl;  //standard output
      c++;
    } 

  trace.endBlock();
  return (c==2);
}


void testStandardDSS6ComputerConceptChecking()
{
  typedef PointVector<3,int> Point;
  typedef std::vector<Point>::const_iterator ConstIterator; 
  typedef StandardDSS6Computer<ConstIterator,int,4> ArithDSS3d; 

  trace.beginBlock("Concept checking");

  BOOST_CONCEPT_ASSERT(( concepts::CForwardSegmentComputer<ArithDSS3d> ));
  
  trace.endBlock();

}



int main(int argc, char **argv)
{
  trace.beginBlock ( "Testing class ArithmeticalDSSComputer" );
 
  testStandardDSS6ComputerConceptChecking();  
    
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testDSSreco() 
        && testSegmentation()

  ;
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;

}
