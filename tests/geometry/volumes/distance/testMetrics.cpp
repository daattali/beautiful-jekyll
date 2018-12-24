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
 * @file testMetrics.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/08/29
 *
 * Functions for testing class Metrics.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/geometry/volumes/distance/CSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/CPowerSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpPowerSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Metrics.
///////////////////////////////////////////////////////////////////////////////
bool testMetrics()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing separable metrics l_2 ..." );

  Z2i::Point a( 0,0), b(5, 0), bb(5,-10), bbb(5,5),c(10,0), d(3,3);
  Z2i::Point starting( 0, 5), endpoint(10,5);
  
  ExactPredicateLpSeparableMetric<Z2i::Space, 2> metric;

  trace.info()<< "a= "<<a<<std::endl;
  trace.info()<< "b= "<<b<<std::endl;
  trace.info()<< "bb= "<<bb<<std::endl;
  trace.info()<< "bbb= "<<bbb<<std::endl;
  trace.info()<< "c= "<<c<<std::endl;

  trace.info() << "distance between a and bb = "<< metric(a,bb)<< std::endl;


  DGtal::Closest closest  =metric.closest(a,d,c);
  nbok += (closest == ClosestFIRST) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "closest(a,d,c) returns d" << std::endl;
      
  bool hidden  =metric.hiddenBy(a,b,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,b,c) returns false" << std::endl;
      
  hidden  =metric.hiddenBy(a,bb,c,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bb,c) returns true" << std::endl;
  
  hidden  =metric.hiddenBy(a,bbb,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns false" << std::endl;
  
  trace.endBlock();

  trace.beginBlock ( "Testing separable metrics l_3 ..." );

   
  ExactPredicateLpSeparableMetric<Z2i::Space, 3> metric3;

  trace.info()<< "a= "<<a<<std::endl;
  trace.info()<< "b= "<<b<<std::endl;
  trace.info()<< "bb= "<<bb<<std::endl;
  trace.info()<< "bbb= "<<bbb<<std::endl;
  trace.info()<< "c= "<<c<<std::endl;


  hidden  =metric3.hiddenBy(a,b,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,b,c) returns false" << std::endl;
      
  hidden  =metric3.hiddenBy(a,bb,c,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bb,c) returns true" << std::endl;
  
  hidden  =metric3.hiddenBy(a,bbb,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns false" << std::endl;
  
  trace.endBlock();
  
  return nbok == nb;
}

template <typename Value>
bool testInexactMetrics()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing inexact predicate separable metrics l_2.1 ..." );

  Z2i::Point a( 0,0), b(5, 0), bb(5,-10), bbb(5,5),c(10,0);
  Z2i::Point starting( 0, 5), endpoint(10,5);
  
  InexactPredicateLpSeparableMetric<Z2i::Space, Value> metric (2.1);

  trace.info()<< "a= "<<a<<std::endl;
  trace.info()<< "b= "<<b<<std::endl;
  trace.info()<< "bb= "<<bb<<std::endl;
  trace.info()<< "bbb= "<<bbb<<std::endl;
  trace.info()<< "c= "<<c<<std::endl;


  bool hidden  =metric.hiddenBy(a,b,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,b,c) returns false" << std::endl;
      
  hidden  =metric.hiddenBy(a,bb,c,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bb,c) returns true" << std::endl;
  
  hidden  =metric.hiddenBy(a,bbb,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns false" << std::endl;
  
  trace.endBlock();

  trace.beginBlock ( "Testing inexact predicate separable metrics l_3.1 ..." );

   
  InexactPredicateLpSeparableMetric<Z2i::Space,Value> metric3(3.1);
 
  trace.info()<< "a= "<<a<<std::endl;
  trace.info()<< "b= "<<b<<std::endl;
  trace.info()<< "bb= "<<bb<<std::endl;
  trace.info()<< "bbb= "<<bbb<<std::endl;
  trace.info()<< "c= "<<c<<std::endl;


  hidden  =metric3.hiddenBy(a,b,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,b,c) returns false" << std::endl;
      
  hidden  =metric3.hiddenBy(a,bb,c,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bb,c) returns true" << std::endl;
  
  hidden  =metric3.hiddenBy(a,bbb,c,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns false" << std::endl;
  
  trace.endBlock();
  
  return nbok == nb;
}


bool testPowerMetrics()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing separable weighted metrics ..." );

  Z2i::Point a( 0,0), bbis(4, 1), b(5,0), bb(5,-10), bbb(5,5),c(10,0);
  Z2i::Point d(5,-6);
  Z2i::Point starting( 0, 5), endpoint(10,5);
  
  typedef ExactPredicateLpPowerSeparableMetric<Z2i::Space, 2> Metric;
  Metric metric;

  trace.info()<< "a= "<<a<<std::endl;
  trace.info()<< "b= "<<b<<std::endl;
  trace.info()<< "bb= "<<bb<<std::endl;
  trace.info()<< "bbb= "<<bbb<<std::endl;
  trace.info()<< "c= "<<c<<std::endl;
  trace.info()<< "d= "<<d<<std::endl;
  
  bool closer = (metric.closestPower(bbis,a,0,c,0) == DGtal::ClosestFIRST);  
  nbok += (closer) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "a is closer" << std::endl;

  closer = (metric.closestPower(bbis,a,10,c,35) == DGtal::ClosestFIRST);
  nbok += (!closer) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "c is closer with w_a=10 w_c=35" << std::endl;
  trace.endBlock();


  trace.beginBlock("Testing Hidden with w=0");
  bool hidden  =metric.hiddenByPower(a,0,b,0,c,0,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,b,c) returns false" << std::endl;
      
  hidden  =metric.hiddenByPower(a,0,bb,0,c,0,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bb,c) returns true" << std::endl;
  
  hidden  =metric.hiddenByPower(a,0,bbb,0,c,0,starting,endpoint,0); 
  nbok += (!hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns false" << std::endl;

  hidden  =metric.hiddenByPower(a,0,d,0,c,0,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,d,c) returns true" << std::endl;
  trace.endBlock();

  trace.beginBlock("Testing Hidden with w!=0");

  hidden  =metric.hiddenByPower(a,0,d,30,c,0,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,0,d,30,c,0) returns true" << std::endl;

  hidden  =metric.hiddenByPower(a,10,d,10,c,10,starting,endpoint,0); 
  nbok += (hidden) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,10,d,10,c,10) returns true" << std::endl;
  
  
  trace.endBlock();
  
  return nbok == nb;
}

bool testBinarySearch()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
 
  trace.beginBlock ( "Testing binary search of Voronoi abscissa..." );
  ExactPredicateLpSeparableMetric<Z2i::Space, 1>::RawValue partialA, partialB;
  ExactPredicateLpSeparableMetric<Z2i::Space, 1> metric;
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 1>::Abscissa Abscissa;
  
  trace.beginBlock("Classical case");
  Z2i::Point a(5,5), b(7,10);
  
  partialA = 5;
  partialB = 7;
  
  // (0,9) strict in B
  // distance( (0,9), (5,5) ) = 9
  // distance( (0,9), (7,10)) = 8
  //
  // (0,8) strict in A
  // distance( (0,8), (5,5) ) = 8
  // distance( (0,8), (7,10) ) = 9
  
  Abscissa res = metric.binarySearchHidden(5, 10, partialA, partialB, 0, 15);
  trace.info() << "Abscissa ="<<res<<std::endl;
  
  nbok += (res == 8) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << "last strict in A==(0,8)" << std::endl;
  trace.endBlock();
  
  trace.beginBlock("Equidistant case");
  Z2i::Point aa(5,5), bb(6,10);
  
  partialA = 5;
  partialB = 5;
  
  // (0,8)  in BB and AA
  // distance( (0,8), (5,5) ) = 8
  // distance( (0,8), (6,10)) = 8
  //
  // (0,7) strict in AA
  // distance( (0,7), (5,5) ) = 7
  // distance( (0,7), (6,10) ) = 9
  
  Abscissa res2 = metric.binarySearchHidden(5, 10, partialA, partialB, 0, 15);
  trace.info() << "Abscissa ="<<res2<<std::endl;
  
  nbok += (res2 == 7) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << "last strict in AA==(0,7) (VoroVertex)" << std::endl;
  trace.endBlock();
  
  //trace.beginBlock("Lower than lowerBound case");
  //Z2i::Point aaa(105,5), bbb(0,10); 
  //partialA = 105;
  //partialB = 0;
  // (0,0) strict in BBB
  // distance( (0,0), (105,5) ) = 120
  // distance( (0,0), (0,10)) = 10
  // Not tested since in the precondition of binarySearch
  
  trace.beginBlock("Greater than lowerBound case");
  
  partialA = 0;
  partialB = 105;
  
  // (0,15) strict in AAAA
  // distance( (0,15), (0,5) ) = 10
  // distance( (0,15), (105,10)) = 110
  
  Abscissa res4 = metric.binarySearchHidden(5, 10, partialA, partialB, 0, 15);
  trace.info() << "Abscissa ="<<res4<<std::endl;
  
  nbok += (res4 >= 15) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << "should be >= upper bound (15)" << std::endl;
  trace.endBlock();

  
  trace.endBlock();
  return nbok == nb;
}


bool testSpecialCasesLp()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing Special Cases Lp..." );
  ExactPredicateLpSeparableMetric<Z2i::Space, 1> metric;
  Z2i::Point a(5,7),b(5,8),bb(6,8),bbb(7,8),c(5,9), bbbb(105,8);
  Z2i::Point starting(4,0), endpoint(4,15);
  
  bool hidden  =metric.hiddenBy(a,b,c,starting,endpoint,1);
  nbok += (!hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "(a,b,c) returns false" << std::endl;
  trace.info() << "Distances at (4,8) "<<metric(a, Z2i::Point(4,8))<<" "
  << metric(b, Z2i::Point(4,8))<<" "
  << metric(c, Z2i::Point(4,8))<<std::endl;
  
  //(a,bb,c)
  hidden  =metric.hiddenBy(a,bb,c,starting,endpoint,1);
  nbok += (!hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "(a,bb,c) returns false" << std::endl;
  
  trace.info() << "Distances at (4,8) "<<metric(a, Z2i::Point(4,8))<<" "
  << metric(bb, Z2i::Point(4,8))<<" "
  << metric(c, Z2i::Point(4,8))<<std::endl;
  
  
  //(a,bbb,c)
  hidden  =metric.hiddenBy(a,bbb,c,starting,endpoint,1);
  nbok += (hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns true" << std::endl;
  trace.info() << "Distances at (4,8) "<<metric(a, Z2i::Point(4,8))<<" "
	       << metric(bbb, Z2i::Point(4,8))<<" "
	       << metric(c, Z2i::Point(4,8))<<std::endl;
  
  //(a,bbbb,c) x_abbbb should be > upper
  hidden  =metric.hiddenBy(a,bbbb,c,starting,endpoint,1);
  nbok += (hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "(a,bbbb,c) returns true" << std::endl;
 
  
  trace.endBlock();
  return nbok == nb;
}

bool testSpecialCasesL2()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  //Pythagorician triplet to check predicate
  trace.beginBlock ( "Testing Special Cases L2..." );
  ExactPredicateLpSeparableMetric<Z2i::Space, 2> metric;
  Z2i::Point a(8,5),b(8,8),bb(9,8),bbb(10,8),c(8,11);
  Z2i::Point starting(4,0), endpoint(4,15);
  
  bool hidden  =metric.hiddenBy(a,b,c,starting,endpoint,1);
  nbok += (!hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,b,c) returns false" << std::endl;
  trace.info() << "Distances at (4,8) "<<metric(a, Z2i::Point(4,8))<<" "
	       << metric(b, Z2i::Point(4,8))<<" "
	       << metric(c, Z2i::Point(4,8))<<std::endl;
  
  hidden  =metric.hiddenBy(a,bb,c,starting,endpoint,1);
  nbok += (!hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bb,c) returns false" << std::endl;
  
  trace.info() << "Distances at (4,8) "<<metric(a, Z2i::Point(4,8))<<" "
	       << metric(bb, Z2i::Point(4,8))<<" "
	       << metric(c, Z2i::Point(4,8))<<std::endl;
  
  
  hidden  =metric.hiddenBy(a,bbb,c,starting,endpoint,1);
  nbok += (hidden) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "(a,bbb,c) returns true" << std::endl;
  trace.info() << "Distances at (4,8) "<<metric(a, Z2i::Point(4,8))<<" "
	       << metric(bbb, Z2i::Point(4,8))<<" "
	       << metric(c, Z2i::Point(4,8))<<std::endl;
  
  trace.endBlock();
  return nbok == nb;
}


bool testConcepts()
{
  BOOST_CONCEPT_ASSERT(( concepts::CSeparableMetric<ExactPredicateLpSeparableMetric<Z2i::Space, 2> > ));
  BOOST_CONCEPT_ASSERT(( concepts::CPowerSeparableMetric<ExactPredicateLpPowerSeparableMetric<Z2i::Space, 2> > ));
  BOOST_CONCEPT_ASSERT(( concepts::CSeparableMetric<InexactPredicateLpSeparableMetric<Z2i::Space> > ));  
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class Metrics" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testMetrics()
    && testInexactMetrics<double>()
    && testInexactMetrics<float>()
    && testPowerMetrics()
    && testBinarySearch()
    && testSpecialCasesL2()
    && testSpecialCasesLp()
    && testConcepts();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
