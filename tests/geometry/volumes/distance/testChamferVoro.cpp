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
 * @file testChamferDT.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/16
 *
 * Functions for testing class ChamferDT.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <set>
#include <algorithm>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/volumes/distance/ChamferNorm2D.h"
#include "DGtal/geometry/volumes/distance/CMetricSpace.h"
#include "DGtal/geometry/volumes/distance/CSeparableMetric.h"

#include "DGtal/geometry/volumes/distance/VoronoiMap.h"

#include "DGtal/io/colormaps/HueShadeColorMap.h"
#include "DGtal/io/colormaps/RandomColorMap.h"

#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ChamferDT.
///////////////////////////////////////////////////////////////////////////////
template <typename VoroMap>
void saveVoroMap(const std::string &filename,const VoroMap &output)
{
  typedef HueShadeColorMap<double,2> Hue;
  double maxdt=0.0;
  
  for ( typename VoroMap::Domain::ConstIterator it = output.domain().begin(), itend = output.domain().end();
       it != itend; ++it)
    if ( output(*it) > maxdt)
      maxdt = output(*it);
    

  Board2D board;
  Hue hue(0,maxdt);
  
  for(typename VoroMap::Domain::ConstIterator it = output.domain().begin(),
      itend = output.domain().end();
      it != itend; ++it)
  {
    typename VoroMap::Value point = output(*it);
    board << (*it);
  }
  
  board.saveSVG(filename.c_str());
}




bool testChamferVoro()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing VoronoiMap with chamfer norm...");
  
  //5-7-11 metic
  typedef experimental::ChamferNorm2D<Z2i::Space> Metric;
  Metric::Directions dirs5711;
  Metric::Directions normals5711;
  //5-7-11 mask
  dirs5711.push_back(Z2i::Vector(0,-1));
  dirs5711.push_back(Z2i::Vector(1,-2));
  dirs5711.push_back(Z2i::Vector(1,-1));
  dirs5711.push_back(Z2i::Vector(2,-1));
  dirs5711.push_back(Z2i::Vector(1,0));
  dirs5711.push_back(Z2i::Vector(2,1));
  dirs5711.push_back(Z2i::Vector(1,1));
  dirs5711.push_back(Z2i::Vector(1,2));
  
  normals5711.push_back(Z2i::Vector(1,-5));
  normals5711.push_back(Z2i::Vector(3,-4));
  normals5711.push_back(Z2i::Vector(4,-3));
  normals5711.push_back(Z2i::Vector(5,-1));
  normals5711.push_back(Z2i::Vector(5,1));
  normals5711.push_back(Z2i::Vector(4,3));
  normals5711.push_back(Z2i::Vector(3,4));
  normals5711.push_back(Z2i::Vector(1,5));
  
  Metric mask5711(dirs5711,normals5711);
  
  
  Z2i::Point a(-20,-20);
  Z2i::Point b(20,20);
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
  sites.insertNew( Z2i::Point(0,4));
  sites.insertNew( Z2i::Point(0,0));
  sites.insertNew( Z2i::Point(-12,-12));
  sites.insertNew( Z2i::Point(0,-12));

  sites.insertNew( Z2i::Point(12,-12));
  sites.insertNew( Z2i::Point(3,4));
  sites.insertNew( Z2i::Point(-3,7));
  
  sites.insertNew( Z2i::Point(-16,16));
  sites.insertNew( Z2i::Point(-15,15));
  sites.insertNew( Z2i::Point(-13,13));
  
  
  sites.insertNew( Z2i::Point(15,16));
  sites.insertNew (Z2i::Point(-16, 3));
  
  
  
  sites.insertNew( Z2i::Point(2,16));
  sites.insertNew( Z2i::Point(3,16));
  sites.insertNew (Z2i::Point(4,16));
  sites.insertNew (Z2i::Point(5,17));
  
  
  for(Z2i::DigitalSet::ConstIterator it = sites.begin(), itend = sites.end();
      it != itend; ++it)
    mySet.erase (*it);
  
  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, Metric> VoroChamf;
  VoroChamf voro(&domain, &mySet,&mask5711);

  Board2D board;
  HueShadeColorMap< int> map(0, 256,2);
  RandomColorMap map2(0,256);
  
  for(VoroChamf::OutputImage::Domain::ConstIterator it = voro.domain().begin(),
      itend = voro.domain().end();
      it != itend; ++it)
  {
    Z2i::Point p = voro(*it);
    int c = abs(p[1]*11+ p[0]*17);
    if (p == *it)
     board << CustomStyle( (*it).className(), new CustomColors(Color::Black,Color::Black));
    else
     if ((*it)[0]==-16 )
      board << CustomStyle( (*it).className(), new CustomColors(Color(c%256,0,0),Color(c%256,0,0)));
    else
      board << CustomStyle( (*it).className(), new CustomColors(map(c%256),map(c%256)));
    
    board << (*it);
  }
  
  board.saveSVG("Voromap.svg");

  
  for(int j= -20; j <= 20 ; j++)
    trace.info()<< "  Reading "<< voro(Point(-16,j))<<std::endl;
  
  
  return nbok == nb;
}



bool testChamferVoroLarge()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing VoronoiMap...");
  
  //5-7-11 metic
  typedef experimental::ChamferNorm2D<Z2i::Space> Metric;
  Metric::Directions dirs5711;
  Metric::Directions normals5711;
  //5-7-11 mask
  dirs5711.push_back(Z2i::Vector(0,-1));
  dirs5711.push_back(Z2i::Vector(1,-2));
  dirs5711.push_back(Z2i::Vector(1,-1));
  dirs5711.push_back(Z2i::Vector(2,-1));
  dirs5711.push_back(Z2i::Vector(1,0));
  dirs5711.push_back(Z2i::Vector(2,1));
  dirs5711.push_back(Z2i::Vector(1,1));
  dirs5711.push_back(Z2i::Vector(1,2));
  
  normals5711.push_back(Z2i::Vector(1,-5));
  normals5711.push_back(Z2i::Vector(3,-4));
  normals5711.push_back(Z2i::Vector(4,-3));
  normals5711.push_back(Z2i::Vector(5,-1));
  normals5711.push_back(Z2i::Vector(5,1));
  normals5711.push_back(Z2i::Vector(4,3));
  normals5711.push_back(Z2i::Vector(3,4));
  normals5711.push_back(Z2i::Vector(1,5));
  
  Metric mask5711(dirs5711,normals5711);
  
  unsigned int N = 64;
  
  Z2i::Point a(0,0);
  Z2i::Point b(N,N);
  Z2i::Domain domain(a,b);
  Z2i::DigitalSet mySet(domain);
  
  for(Z2i::Domain::ConstIterator it = domain.begin(), itend = domain.end();
      it != itend;
      ++it)
    mySet.insertNew( *it );
  
  
  Z2i::DigitalSet sites(domain);
  for(unsigned int i = 0; i < N; i++)
    sites.insert(Z2i::Point( rand() % N , rand()% N ));

  std::copy(sites.begin(), sites.end() , std::ostream_iterator<Z2i::Point>(std::cout,", "));
  
  for(Z2i::DigitalSet::ConstIterator it = sites.begin(), itend = sites.end();
      it != itend; ++it)
    mySet.erase (*it);
  
  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, Metric> VoroChamf;
  VoroChamf voro(&domain, &mySet,&mask5711);
  
  Board2D board;
  HueShadeColorMap< int> map(0, 256,2);
  for(VoroChamf::OutputImage::Domain::ConstIterator it = voro.domain().begin(),
      itend = voro.domain().end();
      it != itend; ++it)
  {
    Z2i::Point p = voro(*it);
    int c = abs(p[1]*11+ p[0]*17);
    if (p == *it)
      board << CustomStyle( (*it).className(), new CustomColors(Color::Black,Color::Black));
   /* else
      if ((*it)[0]==1 )
        board << CustomStyle( (*it).className(), new CustomColors(Color(c%256,0,0),Color(c%256,0,0)));
     */ else
        board << CustomStyle( (*it).className(), new CustomColors(map(c),map(c)));
    
    board << (*it);
  }
  

  
  board.saveSVG("Voromap-large.svg");
  
  return nbok == nb;
}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ChamferDT" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testChamferVoro()&& testChamferVoroLarge(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
