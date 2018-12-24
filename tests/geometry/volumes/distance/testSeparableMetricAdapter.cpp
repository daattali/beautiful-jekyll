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
 * @file testSeparableMetricAdapter.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/04/25
 *
 * Functions for testing class SeparableMetricAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/volumes/distance/SeparableMetricAdapter.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/helpers/StdDefs.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


struct D34 {

  typedef Z2i::Point Point;
  typedef Z2i::Vector Vector;
  typedef double Value;
  
  
};


///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SeparableMetricAdapter.
///////////////////////////////////////////////////////////////////////////////

bool testSeparableMetricAdapter()
{
  trace.beginBlock ( "Testing Type instanciation ..." );
  
  //Distance type
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 2> Distance;
  Distance l2;
  typedef SeparableMetricAdapter<Distance> AdaptedDistance;
  
  AdaptedDistance myMetric(l2);
  
  Z2i::Point a(0,0);
  Z2i::Point b(14,123);
  trace.info() << "Two point distance= "<<myMetric(a,b)<<std::endl;
  
  
  trace.endBlock();
  
  return true;
}


//From testMetrics.cpp
bool testMetrics()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing separable metrics l_2 ..." );
  
  Z2i::Point a( 0,0), b(5, 0), bb(5,-10), bbb(5,5),c(10,0), d(3,3);
  Z2i::Point starting( 0, 5), endpoint(10,5);
  
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 2> Distance;
  Distance l2;
  typedef SeparableMetricAdapter<Distance> AdaptedDistance;
  AdaptedDistance metric(l2);
  
  
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
  
  
  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 3> Distance3;
  Distance3 l3;
  typedef SeparableMetricAdapter<Distance3> AdaptedDistance3;
  AdaptedDistance3 metric3(l3);
  
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

template <typename Metric>
bool testVoronoiMap(const Metric &aMetric, string filename)
{
  typedef SeparableMetricAdapter<Metric> Adapted;
  Adapted adapted(aMetric);
  
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Checking VoronoiMap ..." );
  
  Z2i::Point a(-10,-10);
  Z2i::Point b(10,10);
  Z2i::Domain domain(a,b);
  Z2i::DigitalSet mySet(domain);
  for(Z2i::Domain::ConstIterator it = domain.begin(), itend = domain.end();
      it != itend;
      ++it)
    mySet.insertNew( *it );
  
  
  Z2i::DigitalSet sites(domain);
  sites.insertNew( Z2i::Point(0,-6));
  sites.insertNew( Z2i::Point(6,0));
  sites.insertNew( Z2i::Point(-6,0));
  for(Z2i::DigitalSet::ConstIterator it = sites.begin(), itend = sites.end();
      it != itend; ++it)
    mySet.erase (*it);

  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, Metric> VoroExact;
  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, Adapted> VoroAdapted;
  
  VoroExact voroExact(domain, mySet,aMetric);
  VoroAdapted voroAdapted(domain, mySet, adapted);
  
  
  trace.info()<<"Exporting o SVG"<<std::endl;
  Board2D board;
  for(typename VoroExact::OutputImage::Domain::ConstIterator it = voroExact.domain().begin(),
      itend = voroExact.domain().end();
      it != itend; ++it)
  {
    Z2i::Point p = voroExact(*it);
    unsigned char c = (p[1]*13 + p[0] * 7) % 256;
    board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
    << (*it);
  }
  string out = filename + "-exact.svg";
  board.saveSVG(out.c_str());
  
  board.clear();
  for(typename VoroAdapted::OutputImage::Domain::ConstIterator it = voroAdapted.domain().begin(),
      itend = voroAdapted.domain().end();
      it != itend; ++it)
  {
    Z2i::Point p = voroAdapted(*it);
    unsigned char c = (p[1]*13 + p[0] * 7) % 256;
    board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
    << (*it);
  }
  out = filename + "-adapted.svg";
  board.saveSVG(out.c_str());
  
  
  //Checking Values
  for(typename VoroExact::OutputImage::Domain::ConstIterator it = voroExact.domain().begin(),
      itend = voroExact.domain().end();
      it != itend; ++it)
  {
     if (voroExact(*it) != voroAdapted(*it))
       return false;
  }
  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
  << "Voronoi diagram is valid !" << std::endl;
  trace.endBlock();
 
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class SeparableMetricAdapter" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;
  
  bool res = testSeparableMetricAdapter() &&
             testMetrics() &&
  testVoronoiMap(Z2i::l2Metric,"voronoiadapted-l2") && // && ... other tests
  testVoronoiMap(Z2i::l1Metric,"voronoiadapted-l1") && // && ... other tests
  testVoronoiMap(InexactPredicateLpSeparableMetric<Z2i::Space>(3.444),"voronoiadapted-l3.444"); // && ... other tests
  
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
