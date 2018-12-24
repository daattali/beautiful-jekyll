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
 * @file testFP.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/01/26
 *
 * Functions for testing class FP.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/FP.h"
#include "DGtal/io/boards/Board2D.h"

#include "ConfigTest.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class FP.
///////////////////////////////////////////////////////////////////////////////



/**
 * Test 
 *
 */
bool testFP(string filename)
{

  using namespace DGtal;

  trace.info() << endl;
  trace.info() << "Reading GridCurve from " << filename << endl;
  
  ifstream instream; // input stream
  instream.open (filename.c_str(), ifstream::in);

  //range of points
  typedef int Coordinate; 
  typedef KhalimskySpaceND<2,Coordinate> Kspace; //space
  GridCurve<Kspace> c; //building grid curve
  c.initFromVectorStream(instream);
  typedef GridCurve<Kspace >::PointsRange Range;//range
  Range r = c.getPointsRange();//building range


  //faithful polyon
  trace.info() << "Building FP (process digital curve as"; 
  trace.info() << ( (c.isClosed())?"closed":"open" ) << ")" << endl;

  bool res = true; 
  if (c.isClosed())
    {
      typedef FP<Range::ConstCirculator,Coordinate,4> FP; 
      FP theFP( r.c(), r.c() );
      res = theFP.isValid();       
    }
  else 
    {
      typedef FP<Range::ConstIterator,Coordinate,4> FP; 
      FP theFP( r.begin(), r.end() );
      res = theFP.isValid(); 
    }
  return res;
 
}

template <typename Range1, typename Range2>
bool compare(const Range1& pts, const Range2& groundTruth)
{

  DGtal::GridCurve<> curve;
  curve.initFromPointsRange(pts.begin(), pts.end()); 

  typedef DGtal::GridCurve<>::PointsRange::ConstCirculator   ConstCirculator;
  typedef DGtal::FP<ConstCirculator, DGtal::Z2i::Integer, 4>                FaithfulPolygon;
  FaithfulPolygon theFP( curve.getPointsRange().c(), curve.getPointsRange().c() );

  return ( (theFP.polygon().size() == groundTruth.size()) && 
	   std::equal(theFP.polygon().begin(), theFP.polygon().end(), groundTruth.begin()) ); 
}

bool stoppingCriterionTest()
{
  using namespace DGtal;
  using namespace Z2i;

  int nbok = 0; 
  int nb = 0; 

  trace.beginBlock ( "Stopping criterion" );

  { //inflection part, one leaning point
    std::vector<Point> pts, pts2;
    pts.push_back(Point(0,0)); 
    pts.push_back(Point(1,0)); 
    pts.push_back(Point(1,1)); 
    pts.push_back(Point(2,1)); 
    pts.push_back(Point(3,1)); 
    pts.push_back(Point(3,0)); 
    pts.push_back(Point(4,0)); 
    pts.push_back(Point(4,1)); 
    pts.push_back(Point(4,2)); 
    pts.push_back(Point(3,2)); 
    pts.push_back(Point(2,2)); 
    pts.push_back(Point(1,2)); 
    pts.push_back(Point(0,2));
    pts.push_back(Point(-1,2)); 
    pts.push_back(Point(-2,2)); 
    pts.push_back(Point(-2,1)); 
    pts.push_back(Point(-2,0)); 
    pts.push_back(Point(-1,0)); 
    
    pts2.push_back(Point(1,1)); 
    pts2.push_back(Point(3,1)); 
    pts2.push_back(Point(3,0)); 
    pts2.push_back(Point(4,0)); 
    pts2.push_back(Point(4,2)); 
    pts2.push_back(Point(-2,2)); 
    pts2.push_back(Point(-2,0)); 
    pts2.push_back(Point(1,0)); 
    
    if(compare(pts, pts2))
      nbok++; 
    nb++; 
    
    trace.info() << nbok << " / " << nb << std::endl; 
  }

  { //inflection part, two distinct leaning points
    std::vector<Point> pts, pts2;
    pts.push_back(Point(0,0)); 
    pts.push_back(Point(1,0)); 
    pts.push_back(Point(1,1)); 
    pts.push_back(Point(2,1)); 
    pts.push_back(Point(3,1)); 
    pts.push_back(Point(4,1)); 
    pts.push_back(Point(4,0)); 
    pts.push_back(Point(5,0)); 
    pts.push_back(Point(5,1)); 
    for (int i = 5; i >= -2; --i)
      pts.push_back(Point(i,2)); 
    pts.push_back(Point(-2,1)); 
    pts.push_back(Point(-2,0)); 
    pts.push_back(Point(-1,0)); 
    
    pts2.push_back(Point(1,1)); 
    pts2.push_back(Point(4,1)); 
    pts2.push_back(Point(4,0)); 
    pts2.push_back(Point(5,0)); 
    pts2.push_back(Point(5,2)); 
    pts2.push_back(Point(-2,2)); 
    pts2.push_back(Point(-2,0)); 
    pts2.push_back(Point(1,0)); 
    
    if(compare(pts, pts2))
      nbok++; 
    nb++; 
    
    trace.info() << nbok << " / " << nb << std::endl; 
  }

  { //convex part, one leaning point
    std::vector<Point> pts, pts2;
    pts.push_back(Point(0,0)); 
    pts.push_back(Point(1,0)); 
    pts.push_back(Point(1,1)); 
    pts.push_back(Point(2,1)); 
    pts.push_back(Point(3,1)); 
    pts.push_back(Point(3,2)); 
    for (int i = 3; i >= -2; --i)
      pts.push_back(Point(i,3)); 
    pts.push_back(Point(-2,2)); 
    pts.push_back(Point(-2,1)); 
    pts.push_back(Point(-2,0)); 
    pts.push_back(Point(-1,0)); 

    //FP begins at the last leaning point of the first MS
    pts2.push_back(Point(1,0)); 
    pts2.push_back(Point(3,1)); 
    pts2.push_back(Point(3,3)); 
    pts2.push_back(Point(-2,3)); 
    pts2.push_back(Point(-2,0)); 
    
    if(compare(pts, pts2))
      nbok++; 
    nb++; 
    
    trace.info() << nbok << " / " << nb << std::endl; 
  }

  { //convex part, two distinct leaning points
    std::vector<Point> pts, pts2;
    pts.push_back(Point(0,0)); 
    pts.push_back(Point(1,0)); 
    pts.push_back(Point(1,1)); 
    pts.push_back(Point(2,1)); 
    pts.push_back(Point(3,1)); 
    pts.push_back(Point(3,2)); 
    for (int i = 3; i >= -1; --i)
      pts.push_back(Point(i,3)); 
    pts.push_back(Point(-1,2)); 
    pts.push_back(Point(-1,1)); 
    pts.push_back(Point(-1,0)); 
    
    //FP begins at the last leaning point of the first MS
    pts2.push_back(Point(3,1)); 
    pts2.push_back(Point(3,3)); 
    pts2.push_back(Point(-1,3)); 
    pts2.push_back(Point(-1,0)); 
    pts2.push_back(Point(1,0)); 
    
    if(compare(pts, pts2))
      nbok++; 
    nb++; 
    
    trace.info() << nbok << " / " << nb << std::endl; 
  }
  trace.endBlock();

  return (nb == nbok); 
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  using namespace DGtal;

  trace.beginBlock ( "Testing class FP" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  string sinus2D4 = testPath + "samples/sinus2D4.dat";
  string square = testPath + "samples/smallSquare.dat";
  string dss = testPath + "samples/DSS.dat";

  bool res = testFP(sinus2D4)
    && testFP(square)
    && testFP(dss)
    && stoppingCriterionTest()
    ;

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
