
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
 * @file testArithmeticalDSSComputer.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 *
 * @date 2010/07/02
 *
 * This file is part of the DGtal library
 */

/**
 * Description of testArithmeticalDSSComputer <p>
 * Aim: simple test of \ref ArithmeticalDSSComputer
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
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/io/boards/Board2D.h"

#include "DGtal/geometry/curves/CDynamicBidirectionalSegmentComputer.h"
#include "DGtal/io/boards/CDrawableWithBoard2D.h"

using namespace DGtal;
using namespace std;
using namespace LibBoard;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ArithmeticalDSSComputer.
///////////////////////////////////////////////////////////////////////////////
/**
 * Test for 4-connected points
 *
 */
bool testDSS4drawing()
{

  typedef PointVector<2,int> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef ArithmeticalDSSComputer<Iterator,int,4> DSS4Computer;  

  std::vector<Point> contour;
  contour.push_back(Point(0,0));
  contour.push_back(Point(1,0));
  contour.push_back(Point(1,1));
  contour.push_back(Point(2,1));
  contour.push_back(Point(2,1));
  contour.push_back(Point(3,1));
  contour.push_back(Point(3,2));
  contour.push_back(Point(4,2));
  contour.push_back(Point(5,2));
  contour.push_back(Point(6,2));
  contour.push_back(Point(6,3));
  contour.push_back(Point(6,4));

  
  // Adding step
  trace.beginBlock("Add points while it is possible and draw the result");

  DSS4Computer theDSS4Computer;  
  theDSS4Computer.init( contour.begin() );
  trace.info() << theDSS4Computer << std::endl;

  while ( (theDSS4Computer.end() != contour.end())
    &&(theDSS4Computer.extendFront()) ) {}

  trace.info() << theDSS4Computer << std::endl;

  DSS4Computer::Primitive theDSS4 = theDSS4Computer.primitive(); 
  HyperRectDomain< SpaceND<2,int> > domain( Point(0,0), Point(10,10) );

  Board2D board;
  board.setUnit(Board::UCentimeter);
    
  board << SetMode(domain.className(), "Grid")
	<< domain;    
  board << SetMode("PointVector", "Grid");

  board << SetMode(theDSS4.className(), "Points") 
	<< theDSS4;
  board << SetMode(theDSS4.className(), "BoundingBox") 
	<< theDSS4;
    
  board.saveSVG("DSS4.svg");
  

  trace.endBlock();

  return true;  
}

/**
 * Test for 8-connected points
 *
 */
bool testDSS8drawing()
{

  typedef PointVector<2,int> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef ArithmeticalDSSComputer<Iterator,int,8> DSS8Computer;  

  std::vector<Point> boundary;
  boundary.push_back(Point(0,0));
  boundary.push_back(Point(1,1));
  boundary.push_back(Point(2,1));
  boundary.push_back(Point(3,2));
  boundary.push_back(Point(4,2));
  boundary.push_back(Point(5,2));
  boundary.push_back(Point(6,3));
  boundary.push_back(Point(6,4));

  // Good Initialisation
  trace.beginBlock("Add points while it is possible and draw the result");
  DSS8Computer theDSS8Computer;    
  theDSS8Computer.init( boundary.begin() );

  trace.info() << theDSS8Computer << std::endl;

  while ( (theDSS8Computer.end()!=boundary.end())
	  &&(theDSS8Computer.extendFront()) ) {}

  trace.info() << theDSS8Computer << std::endl;

  DSS8Computer::Primitive theDSS8 = theDSS8Computer.primitive(); 
  HyperRectDomain< SpaceND<2,int> > domain( Point(0,0), Point(10,10) );
    
  Board2D board;
  board.setUnit(Board::UCentimeter);
    
  board << SetMode(domain.className(), "Paving")
	<< domain;    
  board << SetMode("PointVector", "Both");

  board << SetMode(theDSS8.className(), "Points") 
	<< theDSS8;
  board << SetMode(theDSS8.className(), "BoundingBox") 
	<< theDSS8;
        
  board.saveSVG("DSS8.svg");

  trace.endBlock();

  return true;  
}

/**
 * checking consistency between extension and retractation.
 *
 */
bool testExtendRetractFront()
{

  typedef PointVector<2,int> Point;

  std::vector<Point> contour;
  contour.push_back(Point(0,0));
  contour.push_back(Point(1,0));
  contour.push_back(Point(1,1));
  contour.push_back(Point(2,1));
  contour.push_back(Point(3,1));
  contour.push_back(Point(3,2));
  contour.push_back(Point(4,2));
  contour.push_back(Point(5,2));
  contour.push_back(Point(6,2));
  contour.push_back(Point(6,3));

  typedef std::vector<Point>::const_iterator Iterator;
  typedef std::vector<Point>::const_reverse_iterator ReverseIterator;
  typedef ArithmeticalDSSComputer<Iterator,int,4> Computer;
  typedef ArithmeticalDSSComputer<ReverseIterator,int,4> ReverseComputer;
  typedef Computer::Primitive Primitive; 

  std::deque<Primitive> v1,v2;

  trace.beginBlock("Checking consistency between adding and removing");

  //forward scan and store each DSS
  trace.info() << "forward scan" << std::endl;

  Computer c;
  c.init( contour.begin() );
  v1.push_back( c.primitive() );   

  while ( (c.end() != contour.end())
    &&(c.extendFront()) ) {
    v1.push_back( c.primitive() );
  }
  ASSERT(contour.size() == v1.size()); 

  //backward scan
  trace.info() << "backward scan" << std::endl;

  ReverseComputer rc; 
  rc.init( contour.rbegin() ); 

  while ( (rc.end() != contour.rend())
          &&(rc.extendFront()) ) 
    {
    }

  //removing step and store each DSS for comparison
  trace.info() << "removing" << std::endl;

  v2.push_front( rc.primitive() );
  while (rc.retractBack()) {
    v2.push_front( rc.primitive() );
  }    
  ASSERT(v1.size() == v2.size());
    
  //comparison
  trace.info() << "comparison" << std::endl;

  bool isOk = true;
  for (unsigned int k = 0; k < v1.size(); k++) {
    if (v1.at(k) != v2.at(k)) 
      isOk = false;
    trace.info() << "DSS :" << k << std::endl;
    trace.info() << v1.at(k) << std::endl << v2.at(k) << std::endl;
  }

  if (isOk) 
    trace.info() << "ok for the " << v1.size() << " DSS" << std::endl;
  else 
    trace.info() << "failure" << std::endl;

  trace.endBlock();

  return isOk;
}

template<typename Iterator>
bool testIsInsideForOneQuadrant(const Iterator& k, const Iterator& l, const Iterator& ite) 
{
  ASSERT(k < l); 
  ASSERT(l < ite); 

  typedef ArithmeticalDSSComputer<Iterator,int,4> DSS4;  
  DSS4 theDSS4;

  theDSS4.init( k );
  while ( (theDSS4.end() != l )
          &&(theDSS4.extendFront()) ) {}

  ASSERT( theDSS4.isValid() ); 

  //all DSS points are in the DSS
  bool flagIsInside = true; 
  for (Iterator i = theDSS4.begin(); i != theDSS4.end(); ++i)
    {
      if ( !theDSS4.isInDSS(i) )
	  flagIsInside = false; 
    } 
  //all other points are not in the DSS
  bool flagIsOutside = true; 
  for (Iterator i = l; i != ite; ++i)
    {
      if ( theDSS4.isInDSS(i) )
	flagIsOutside = false; 
    }
  return (flagIsInside && flagIsOutside); 
}

/**
 * checking isDSL and isDSS methods
 */
bool testIsInside()
{

  typedef PointVector<2,int> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef std::vector<Point>::reverse_iterator ReverseIterator;

  int nb = 0; 
  int nbok = 0; 

  std::vector<Point> contour;
  contour.push_back(Point(0,0));
  contour.push_back(Point(1,1));
  contour.push_back(Point(2,1));
  contour.push_back(Point(3,1));
  contour.push_back(Point(4,1));
  contour.push_back(Point(4,2));
  contour.push_back(Point(5,2));
  contour.push_back(Point(6,2));
  contour.push_back(Point(6,3));
  contour.push_back(Point(7,3));

  std::vector<Point> contour2;
  contour2.push_back(Point(0,0));
  contour2.push_back(Point(1,-1));
  contour2.push_back(Point(2,-1));
  contour2.push_back(Point(3,-1));
  contour2.push_back(Point(4,-1));
  contour2.push_back(Point(4,-2));
  contour2.push_back(Point(5,-2));
  contour2.push_back(Point(6,-2));
  contour2.push_back(Point(6,-3));
  contour2.push_back(Point(7,-3));

  trace.beginBlock("isInside tests for each of the four quadrants");
  { //Quadrant 1
    Iterator itb = contour.begin() + 1;
    Iterator ite = itb + 8;  
    if (testIsInsideForOneQuadrant(itb, ite, contour.end()) )
      nbok++; 
    nb++; 
    trace.info() << nbok << " / " << nb << " quadrants" << std::endl; 
  }

  { //quadrant 2
    ReverseIterator itb = contour2.rbegin() + 1;
    ReverseIterator ite = itb + 8;  
    if (testIsInsideForOneQuadrant(itb, ite, contour2.rend()) )
      nbok++; 
    nb++; 
    trace.info() << nbok << " / " << nb << " quadrants" << std::endl; 
  }

  { //quadrant 3
    ReverseIterator itb = contour.rbegin() + 1;
    ReverseIterator ite = itb + 8;  
    if (testIsInsideForOneQuadrant(itb, ite, contour.rend()) )
      nbok++; 
    nb++; 
    trace.info() << nbok << " / " << nb << " quadrants" << std::endl; 
  }

  { //quadrant 4
    Iterator itb = contour2.begin() + 1;
    Iterator ite = itb + 8;  
    if (testIsInsideForOneQuadrant(itb, ite, contour2.end()) )
      nbok++; 
    nb++; 
    trace.info() << nbok << " / " << nb << " quadrants" << std::endl; 
  }
  trace.endBlock();

  return (nb == nbok); 
}

#ifdef WITH_BIGINTEGER
/**
 * Test for 4-connected points
 * with big coordinates
 */
bool testBIGINTEGER()
{
  bool flag = false;


  typedef DGtal::BigInteger Coordinate;
  typedef PointVector<2,Coordinate> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef ArithmeticalDSSComputer<Iterator,Coordinate,4> DSS4;  



  trace.beginBlock("Add some points of big coordinates");

  std::vector<Point> contour;
  contour.push_back(Point(1000000000,1000000000));  
  contour.push_back(Point(1000000001,1000000000));
  contour.push_back(Point(1000000002,1000000000));
  contour.push_back(Point(1000000003,1000000000));
  contour.push_back(Point(1000000003,1000000001));
  contour.push_back(Point(1000000004,1000000001));
  contour.push_back(Point(1000000005,1000000001));
  contour.push_back(Point(1000000005,1000000002));

  DSS4 theDSS4;
  theDSS4.init( contour.begin() );
  while ( (theDSS4.end() != contour.end())
          &&(theDSS4.extendFront()) ) {}

  trace.info() << theDSS4 << " " << theDSS4.isValid() << std::endl;

  Coordinate mu;
  mu = "-3000000000";
  if( (theDSS4.a() == 2)
      &&(theDSS4.b() == 5)
      &&(theDSS4.mu() == mu)
      &&(theDSS4.omega() == 7) ) {
    flag = true;
  } else {
    flag = false;
  }

  trace.endBlock();

  return flag;
}

#endif

/**
 * Test for corners
 * in 8-connected curves
 * (not compatible steps)
 */
bool testCorner()
{

  typedef PointVector<2,int> Point;
  typedef std::vector<Point>::iterator Iterator;
  typedef ArithmeticalDSSComputer<Iterator,int,8> DSS8;  

  std::vector<Point> boundary;
  boundary.push_back(Point(10,10));
  boundary.push_back(Point(10,11));
  boundary.push_back(Point(11,11));

  trace.beginBlock("test Corner with 8-adjacency");

  DSS8 theDSS8;
  theDSS8.init(boundary.begin());
  std::cerr << theDSS8 << std::endl; 
  theDSS8.extendFront();
  std::cerr << theDSS8 << std::endl; 
  bool res = ( !theDSS8.extendFront() );
  std::cerr << theDSS8 << std::endl; 

  trace.endBlock();
 
  return res; 
}



void testArithmeticalDSSComputerConceptChecking()
{
   typedef PointVector<2,int> Point; 
   typedef std::vector<Point>::iterator Iterator; 
   typedef ArithmeticalDSSComputer<Iterator,int,8> ArithDSS; 
   BOOST_CONCEPT_ASSERT(( concepts::CDynamicBidirectionalSegmentComputer<ArithDSS> ));
}


int main(int argc, char **argv)
{

  trace.beginBlock ( "Testing class ArithmeticalDSSComputer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

   
  {//concept checking
    testArithmeticalDSSComputerConceptChecking();
  }
  
  bool res = testDSS4drawing() 
    && testDSS8drawing()
    && testExtendRetractFront()
    && testCorner()
#ifdef WITH_BIGINTEGER
    && testBIGINTEGER()
#endif
    && testIsInside()
    ;
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;

}
