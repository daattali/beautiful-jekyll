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
 * @file testSegmentComputerEstimators.cpp
 * @author Tristan Roussillon (\c
 * tristan.roussillon@liris.cnrs.fr ) Laboratoire d'InfoRmatique en
 * Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS,
 * France
 *
 *
 * @date 2011/06/28

 * Functions for testing classes in SegmentComputerEstimators.h
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cmath>
#include "DGtal/base/Common.h"


#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/StabbingCircleComputer.h"
#include "DGtal/geometry/curves/estimation/SegmentComputerEstimators.h"

#include "DGtal/io/boards/Board2D.h"


#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace LibBoard;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing classes in SegmentComputerEstimators.h.
///////////////////////////////////////////////////////////////////////////////


/**
 * Tangent from DSS
 *
 */
template<typename DSSComputer>
bool testTangentFromDSS(
     const typename DSSComputer::ConstIterator& itb,
     const typename DSSComputer::ConstIterator& ite  )
{


  trace.info() << "feeding segment computer " << endl;

  DSSComputer dss;  
  DGtal::longestSegment( dss, itb, ite ); 

  trace.info() << dss << endl;
  trace.info() << endl;

  trace.info() << "building and using the functor " << endl;
  const double epsilon = 0.00001;

  int nb = 0; 
  int nbok = 0; 

  { //angle
    TangentAngleFromDSSEstimator<DSSComputer> f; 
    f.attach(dss); 
    double q1 = f.eval(itb); 
    double q2 = std::atan2((double)dss.a(),(double)dss.b());
    trace.info() << "Tangent orientation : " << q1 << " == " << q2 << endl;
    nbok += (std::abs(q1 - q2) < epsilon)?1:0;
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
  }

  { //vector
    TangentVectorFromDSSEstimator<DSSComputer> f; 
    typedef typename TangentVectorFromDSSEstimator<DSSComputer>::Quantity Quantity; 
    f.attach(dss); 
    Quantity q1 = f.eval(itb); 
    Quantity q2 = Quantity(dss.b(), dss.a()); 
    trace.info() << "Tangent vector : " << q1 << " == " << q2 << endl;
    nbok += (q1 == q2)?1:0; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
  }

  { //unit vector
    TangentFromDSSEstimator<DSSComputer> f; 
    typedef typename TangentFromDSSEstimator<DSSComputer>::Quantity Quantity; 
    f.attach(dss); 
    Quantity q1 = f.eval(itb); 
    double n = std::sqrt( (double)dss.a()*dss.a() + (double)dss.b()*dss.b() );
    Quantity q2 = Quantity((double)dss.b()/n, (double)dss.a()/n); 
    trace.info() << "Normalized tangent vector : " << q1 << " == " << q2 << endl;
    nbok += ((std::abs(q1[0] - q2[0]) < epsilon)&&(std::abs(q1[1] - q2[1]) < epsilon))?1:0; 
    nb++; 
    trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
  }

  return (nb == nbok); 
}

/**
 * Estimations from DCA
 *
 */
template<typename DCAComputer>
bool testFromDCA(
     const typename DCAComputer::ConstIterator& itb,
     const typename DCAComputer::ConstIterator& ite  )
{


  trace.info() << "feeding segment computer " << endl;

  DCAComputer dca;  
  DGtal::longestSegment( dca, itb, ite ); 

  trace.info() << dca << endl;
  trace.info() << endl;

  trace.info() << "building and using the functor " << endl;
  const double epsilon = 0.00001;

  int nb = 0; 
  int nbok = 0; 

  { //curvature
    CurvatureFromDCAEstimator<DCAComputer,false> f; 
    f.init(1.0, itb, ite);
    f.attach(dca); 
    double q1 = f.eval(itb);
    f.init(0.1, itb, ite); 
    double q2 = f.eval(itb);    
    trace.info() << "Curvature (h=1): " << q1 << std::endl; 
    trace.info() << "Curvature (h=0.1): " << q2 << std::endl; 
    nbok += ((q1 >= 0)&&(q1 < 1)&&(q2 >= 0)&&(q2 < 10)
	     &&(std::abs(q2-(10*q1)) < epsilon))?1:0; 
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
  }

  { //tangent
    TangentFromDCAEstimator<DCAComputer> f; 
    f.attach(dca); 
    typedef typename TangentFromDCAEstimator<DCAComputer>::Quantity Quantity; 
    typename DCAComputer::ConstIterator it = DGtal::getMiddleIterator(itb, ite); 
    Quantity q1 = f.eval( it ); 
    trace.info() << "Tangent: " << q1 << " == [PointVector] {1, 0} " << std::endl; 
    nbok += (std::abs(q1[0]-1.0) < epsilon)
      && (std::abs(q1[1]) < epsilon) ? 1 : 0; 
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
  }

  { //position
    DistanceFromDCAEstimator<DCAComputer> f; 
    typedef typename DistanceFromDCAEstimator<DCAComputer>::Quantity Quantity; 
    typename DCAComputer::ConstIterator it = DGtal::getMiddleIterator(itb, ite);
    f.init(1.0, itb, ite);
    f.attach(dca); 
    Quantity q1 = f.eval( it ); 
    trace.info() << "Position (h=1): " << q1.first << " (<=0), " << q1.second << " (>0) " << std::endl; 
    f.init(0.1, itb, ite);
    f.attach(dca); 
    Quantity q2 = f.eval( it ); 
    trace.info() << "Position (h=0.1): " << q2.first << " (<=0), " << q2.second << " (>0) " << std::endl; 
    nbok += ( (q1.first < epsilon)
	      && (q1.second > -epsilon)
	      && (std::abs((q1.second - q1.first) - 1) < epsilon)
	      && (q2.first < epsilon)
	      && (q2.second > -epsilon) 
	      && (std::abs((q2.second - q2.first) - 0.1) < epsilon) )? 1 : 0; 
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ")" << std::endl; 
  }

  return (nb == nbok); 
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing segment computer functors" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = true; 

  //types
  typedef PointVector<2,int> Point;


  //------------------------------------------ DSS
  {
    typedef std::vector<Point> Range;
    typedef Range::iterator ConstIterator;
    typedef ArithmeticalDSSComputer<ConstIterator,int,4> DSS4;  
    typedef ArithmeticalDSSComputer<ConstIterator,int,8> DSS8;  

    //input points
    Range curve4;
    curve4.push_back(Point(0,0));
    curve4.push_back(Point(1,0));
    curve4.push_back(Point(1,1));
    curve4.push_back(Point(2,1));
    curve4.push_back(Point(3,1));
    curve4.push_back(Point(3,2));
    curve4.push_back(Point(4,2));
    curve4.push_back(Point(5,2));
    curve4.push_back(Point(6,2));
    curve4.push_back(Point(6,3));
    curve4.push_back(Point(7,3));

    Range curve8;
    curve8.push_back(Point(0,0));
    curve8.push_back(Point(1,1));
    curve8.push_back(Point(2,1));
    curve8.push_back(Point(3,2));
    curve8.push_back(Point(4,2));
    curve8.push_back(Point(5,2));
    curve8.push_back(Point(6,3));
    curve8.push_back(Point(7,3));
    curve8.push_back(Point(8,4));
    curve8.push_back(Point(9,4));
    curve8.push_back(Point(10,5));

    //tests
    res = res && testTangentFromDSS<DSS4>(curve4.begin(), curve4.end())
      && testTangentFromDSS<DSS8>(curve8.begin(), curve8.end());
  }
  //------------------------------------------ DCA
  {
    typedef std::pair<Point,Point> Pair; 
    typedef std::vector<Pair> Range;
    typedef Range::const_iterator ConstIterator; 
    typedef StabbingCircleComputer<ConstIterator> DCA;  

    Range curve; 
    curve.push_back(std::make_pair(Point(0,0),Point(0,1))); 
    curve.push_back(std::make_pair(Point(1,0),Point(1,1))); 

    curve.push_back(std::make_pair(Point(2,1),Point(2,2))); 
    curve.push_back(std::make_pair(Point(3,1),Point(3,2))); 
    curve.push_back(std::make_pair(Point(4,1),Point(4,2))); 

    curve.push_back(std::make_pair(Point(5,2),Point(5,3))); 
    curve.push_back(std::make_pair(Point(6,2),Point(6,3))); 
    curve.push_back(std::make_pair(Point(7,2),Point(7,3))); 
    curve.push_back(std::make_pair(Point(8,2),Point(8,3))); 
    curve.push_back(std::make_pair(Point(9,2),Point(9,3))); 

    curve.push_back(std::make_pair(Point(10,1),Point(10,2))); 
    curve.push_back(std::make_pair(Point(11,1),Point(11,2))); 
    curve.push_back(std::make_pair(Point(12,1),Point(12,2))); 

    curve.push_back(std::make_pair(Point(13,0),Point(13,1))); 
    curve.push_back(std::make_pair(Point(14,0),Point(14,1))); 

    res = res && testFromDCA<DCA>(curve.begin(), curve.end())
      && testFromDCA<DCA>(curve.begin()+2, curve.begin()+12);
  }

  //----------------------------------------------------------
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
