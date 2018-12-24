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
 * @file testVoronoiMap.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/08/14
 *
 * Functions for testing class VoronoiMap.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <array>
#include <algorithm>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/DistanceTransformation.h"
#include "DGtal/kernel/BasicPointPredicates.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
///////////////////////////////////////////////////////////////////////////////
// Functions for testing class VoronoiMap.
///////////////////////////////////////////////////////////////////////////////


template<typename Point>
double mynorm(const Point &point, const double p)
{
  double res=0.0;
  for(unsigned int i=0; i< Point::dimension; i++)
    res +=  std::pow ( (double)abs(point[i]) , p);

  return std::pow(res, 1.0/p);
}

template <typename VoroMap>
void saveVoroMap(const std::string &filename,const VoroMap &output,const double p)
{
  typedef HueShadeColorMap<double,2> Hue;

  const double maxdt = mynorm( output.domain().upperBound() - output.domain().lowerBound(), p );

  Board2D board;
  Hue hue(0, maxdt);

  for(typename VoroMap::Domain::ConstIterator it = output.domain().begin(),
        itend = output.domain().end();
      it != itend; ++it)
    {
      typename VoroMap::Value point = output(*it);
      board << CustomStyle( (*it).className(), new CustomColors( hue(mynorm(point- (*it),p)),
                                                                 hue(mynorm(point- (*it),p))))
            << (*it);
    }

  board.saveSVG(filename.c_str());
}

/** Modify a point coordinates as if the given domain is periodic
 * and so that the coordinates are between the lower and upper bounds
 * of the domain.
 *
 * @param aPoint  the point.
 * @param aDomain the periodic domain.
 * @return the same point with coordinates between domain's lower and upper bounds.
 */
template < typename Point, typename Domain >
Point calcPointModuloDomain( Point aPoint, Domain const & aDomain )
{
  auto const & lowerBound = aDomain.lowerBound();
  auto const & upperBound = aDomain.upperBound();

  for ( std::size_t i = 0; i < Domain::dimension; ++i )
    aPoint[i] = ( aPoint[i] - 2*lowerBound[i] + upperBound[i] + 1 ) % ( upperBound[i] - lowerBound[i] + 1 ) + lowerBound[i];

  return aPoint;
}

/** Returns periodicity specification from an integer between 0 and 2^n - 1.
 *
 * From an integer between 0 and 2^n-1, it returns a boolean array of size n
 * whith value true at position i if the ith bit of the integer is set,
 * false otherwise.
 *
 * @tparam N          size of the periodicity specification array.
 * @param  anInteger  an integer between 0 and 2^N-1.
 * @return a periodicity specification array.
 */
template < std::size_t N >
std::array<bool, N> getPeriodicityFromInteger( std::size_t anInteger )
{
  std::array<bool, N> periodicity;
  for ( std::size_t i = 0, mask = 1 ; i < N ; ++i, mask *= 2 )
    periodicity[i] = anInteger & mask;

  return periodicity;
}

/** Format a periodicity specification array as a string.
 *
 * @param aPeriodicity the periodicity specification array.
 * @return a string which ith character is '0' if the ith dimension is
 *         non-periodic, '1' otherwise.
 */
template < std::size_t N >
std::string formatPeriodicity( std::array<bool, N> const& aPeriodicity )
{
  std::string str;
  for ( std::size_t i = 0; i < N; ++i )
    str += aPeriodicity[i] ? '1' : '0';

  return str;
}

/** Validates the VoronoiMap
 */
template < typename Set, typename Voro>
bool checkVoronoi(const Set &aSet, const Voro & voro)
{
  typedef typename Voro::Point Point;

  // Domain extent
  Point const extent = voro.domain().upperBound() - voro.domain().lowerBound() + Point::diagonal();

  // Site shifting depending on the periodicity.
  std::vector< typename Voro::PeriodicitySpec > periodicShift;
  for ( std::size_t i = 0; i < ( 1u << Voro::Space::dimension ); ++i )
    {
      const auto periodicity = getPeriodicityFromInteger< Voro::Space::dimension >( i );

      // Checking if this periodicity possibility is valid.
      bool isValid = true;
      for ( size_t j = 0; j < periodicity.size(); ++j )
        if ( periodicity[j] && ! voro.isPeriodic(j) )
          {
            isValid = false;
            break;
          }

      if ( isValid )
        periodicShift.push_back( periodicity );
    }

  // Checking site for all domain points.
  for ( auto const& pt : voro.domain() )
    {
      // Calculating reference (raw-)distance.
      const Point psite  = voro(pt);
      const auto dist = voro.metric()->rawDistance( pt, psite );

      // Checking that the reference site is actually a given site.
      // Also testing projectPoint method.
      if ( std::find( aSet.begin(), aSet.end(), voro.projectPoint( psite ) ) == aSet.end() )
        {
          trace.error() << "The Voro point " << psite
                        << " projected to " << voro.projectPoint( psite )
                        << " is not a valid site." << std::endl;
          return false;
        }

      // Checking if we can found a better site.
      for ( auto site : aSet )
        {
          // Trying all shifting possibilities of the site depending on the domain periodicity.
          for ( auto const & periodicity : periodicShift )
            {
              auto currSite = site;

              // Shifting site.
              for ( std::size_t dim = 0; dim < Voro::Space::dimension ; ++dim )
                if ( periodicity[dim] )
                  currSite[dim] += ( pt[dim] < currSite[dim] ? -1 : 1 ) * extent[dim];

              // Checking raw-distance.
              const auto dbis = voro.metric()->rawDistance( pt, currSite );
              if ( dbis < dist )
                {
                  trace.error() << "DT Error at " << pt
                                << "  Voro:" << psite << " (" << dist << ")"
                                << "  from set:" << site << "(" << dbis << ")"
                                << " projected from " << currSite << "." << std::endl;
                  return false;
                }
            }
        }
    }

  return true;
}


bool testCheckConcept()
{
  typedef ExactPredicateLpSeparableMetric<Z3i::Space,2> L2Metric;
  BOOST_CONCEPT_ASSERT(( concepts::CConstImage< VoronoiMap<Z3i::Space, Z3i::DigitalSet, L2Metric> >));

  return true;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testVoronoiMap( std::array<bool, 2> const& periodicity = { {false, false} } )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing VoronoiMap2D with periodicity " + formatPeriodicity(periodicity) );

  Z2i::Point a(-10,-10);
  Z2i::Point b(10,10);
  Z2i::Domain domain(a,b);

  Z2i::DigitalSet mySet(domain);

  for(Z2i::Domain::ConstIterator it = domain.begin(), itend = domain.end();
      it != itend;
      ++it)
    mySet.insertNew( *it );


  Z2i::DigitalSet sites(domain);

  sites.insertNew( Z2i::Point(3,-6));
  sites.insertNew( Z2i::Point(9,0));
  sites.insertNew( Z2i::Point(-2,0));

  for(Z2i::DigitalSet::ConstIterator it = sites.begin(), itend = sites.end();
      it != itend; ++it)
    mySet.erase (*it);



  typedef ExactPredicateLpSeparableMetric<Z2i::Space, 2> L2Metric;
  typedef VoronoiMap<Z2i::Space, Z2i::DigitalSet, L2Metric> Voro2;
  L2Metric l2;
  Voro2 voro(&domain, &mySet, &l2, periodicity);

  for(int j=-10; j <= 10; j++)
    {
      for(int i=-10; i<=10; i++)
        trace.info() << "("<<voro( Z2i::Point(i,j))[0]<<","<< voro( Z2i::Point(i,j))[1]<<") ";
      trace.info()<<std::endl;
    }

  trace.info()<<"Exporting to SVG"<<std::endl;

  Board2D board;
  for(Voro2::OutputImage::Domain::ConstIterator it = voro.domain().begin(),
        itend = voro.domain().end();
      it != itend; ++it)
    {
      const auto p = calcPointModuloDomain( voro(*it), voro.domain() );
      const unsigned char c = ( p[1]*13 + p[0] * 7) % 256;
      board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
            << (*it);
    }

  board.saveSVG( ( "Voromap." + formatPeriodicity(periodicity) + ".svg" ).c_str() );

  trace.beginBlock("Validating the Voronoi Map");
  nbok += checkVoronoi(sites,voro) ? 1 : 0;
  nb++;
  trace.endBlock();

  trace.endBlock();

  return nbok == nb;
}



/**
 * Example of a test. To be completed.
 *
 */
template<typename Set>
bool testVoronoiMapFromSites2D( const Set &aSet,
                                const std::string &name,
                                std::array<bool, 2> const& periodicity = { {false, false} } )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  Set mySet(aSet.domain());

  for(typename Set::Domain::ConstIterator it = aSet.domain().begin(), itend = aSet.domain().end();
      it != itend;
      ++it)
    mySet.insertNew( *it );


  for(typename Set::ConstIterator it = aSet.begin(), itend = aSet.end();
      it != itend; ++it)
    mySet.erase (*it);


  trace.beginBlock(" Voro computation");
  typedef ExactPredicateLpSeparableMetric<typename Set::Space,2> L2Metric;
  typedef VoronoiMap<typename Set::Space, Set, L2Metric> Voro2;
  L2Metric l2;
  Voro2 voro(aSet.domain(), mySet, l2, periodicity );

  trace.endBlock();

  trace.beginBlock(" Voronoi computation l_6");
  typedef ExactPredicateLpSeparableMetric<typename Set::Space,6> L6Metric;
  L6Metric l6;
  typedef VoronoiMap<typename Set::Space, Set, L6Metric> Voro6;
  Voro6 voro6( aSet.domain(), mySet, l6, periodicity );
  trace.endBlock();



  trace.beginBlock(" DT computation");
  typedef DistanceTransformation<typename Set::Space, Set, L2Metric> DT;
  DT dt( aSet.domain(), mySet, l2, periodicity );
  trace.endBlock();


  if ( (aSet.domain().upperBound()[1] - aSet.domain().lowerBound()[1]) <20)
    {
      for(int j= aSet.domain().lowerBound()[1]; j <= aSet.domain().upperBound()[1]; j++)
        {
          for(int i=aSet.domain().lowerBound()[0]; i<=aSet.domain().upperBound()[0]; i++)
            if ( aSet.find( Z2i::Point(i,j) ) != aSet.end() )
              std::cout <<"X ";
            else
              std::cout<<"0 ";
          trace.info()<<std::endl;
        }

      trace.info() << std::endl;

      for(int j= aSet.domain().lowerBound()[1]; j <= aSet.domain().upperBound()[1]; j++)
        {
          for(int i=aSet.domain().lowerBound()[0]; i<=aSet.domain().upperBound()[0]; i++)
            trace.info() << "("<<voro( Z2i::Point(i,j))[0]<<","<< voro( Z2i::Point(i,j))[1]<<") ";
          trace.info()<<std::endl;
        }
    }

  Board2D board;
  board << voro.domain();
  for(typename Voro2::OutputImage::Domain::ConstIterator it = voro.domain().begin(), itend = voro.domain().end();
      it != itend; ++it)
    {
      if (!mySet(*it))
        board  << (*it);
    }
  std::string filename = "Voromap-" + name + "-orig." + formatPeriodicity(periodicity) + ".svg";
  board.saveSVG(filename.c_str());

  board.clear();
  board << voro.domain();
  board.setPenColor(Color(0,0,0));
  for(typename Voro2::OutputImage::Domain::ConstIterator it = voro.domain().begin(), itend = voro.domain().end();
      it != itend; ++it)
    {
      Z2i::Point p = voro(*it);
      if ((p != (*it)) && (p != voro.domain().upperBound() + Z2i::Point::diagonal(1))
          &&  (p != voro.domain().lowerBound()))
        Display2DFactory::draw( board,   p - (*it), (*it));
    }

  filename = "Voromap-" + name + "-diag." + formatPeriodicity(periodicity) + ".svg";
  board.saveSVG(filename.c_str());


  board.clear();
  board << voro.domain();
  for(typename Voro2::OutputImage::Domain::ConstIterator it = voro.domain().begin(), itend = voro.domain().end();
      it != itend; ++it)
    {
      const auto p = calcPointModuloDomain( voro(*it), voro.domain() );
      unsigned char c = (p[1]*13 + p[0] * 7) % 256;
      board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
            << (*it);
    }

  filename = "Voromap-" + name + "." + formatPeriodicity(periodicity) + ".svg";
  board.saveSVG(filename.c_str());

  filename = "Voromap-" + name + "-hue." + formatPeriodicity(periodicity) + ".svg";
  saveVoroMap(filename.c_str(),voro,2);


  board.clear();
  for(typename Voro6::OutputImage::Domain::ConstIterator it = voro6.domain().begin(),
      itend = voro6.domain().end();
      it != itend; ++it)
    {
      Z2i::Point p = voro6(*it);
      if (p != (*it))
        Display2DFactory::draw( board,   p - (*it), (*it));
    }

  filename = "Voromap-diag-l6-" + name + "." + formatPeriodicity(periodicity) + ".svg";
  board.saveSVG(filename.c_str());

  board.clear();
  for(typename Voro6::OutputImage::Domain::ConstIterator it = voro6.domain().begin(), itend = voro6.domain().end();
      it != itend; ++it)
    {
      const auto p = calcPointModuloDomain( voro6(*it), voro6.domain() );
      unsigned char c = (p[1]*13 + p[0] * 7) % 256;
      board << CustomStyle( (*it).className(), new CustomColors(Color(c,c,c),Color(c,c,c)))
            << (*it);;
    }

  filename = "Voromap-l6" + name + "." + formatPeriodicity(periodicity) + ".svg";
  board.saveSVG(filename.c_str());

  filename = "Voromap-hue-l6-" + name + "." + formatPeriodicity(periodicity) + ".svg";
  saveVoroMap(filename.c_str(),voro6,3);


  trace.beginBlock("Validating the Voronoi Map");
  nbok += checkVoronoi(aSet, voro) ? 1 : 0;
  nb++;
  trace.endBlock();

  trace.beginBlock("Validating the Voronoi Map l_6");
  nbok += checkVoronoi(aSet, voro6) ? 1 : 0;
  nb++;
  trace.endBlock();

  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
template<typename Set>
bool testVoronoiMapFromSites( const Set &aSet )
{
  std::array<bool, Set::dimension> periodicity;
  periodicity.fill( false );
  return testVoronoiMapFromSites( aSet, periodicity );
}

template<typename Set>
bool testVoronoiMapFromSites( const Set &aSet, std::array<bool, Set::Space::dimension> const & periodicity )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  Set mySet(aSet.domain());

  for(typename Set::Domain::ConstIterator it = aSet.domain().begin(),
      itend = aSet.domain().end();
      it != itend;
      ++it)
    mySet.insertNew( *it );


  for(typename Set::ConstIterator it = aSet.begin(), itend = aSet.end();
      it != itend; ++it)
    mySet.erase (*it);



  trace.beginBlock(" Voronoi computation l_2");
  typedef ExactPredicateLpSeparableMetric<typename Set::Space,2> L2Metric;
  typedef VoronoiMap<typename Set::Space, Set, L2Metric> Voro2;
  L2Metric l2;
  Voro2 voro(aSet.domain(), mySet, l2, periodicity);
  trace.endBlock();

  trace.beginBlock("Validating the Voronoi Map");
  nbok += checkVoronoi(aSet, voro) ? 1 : 0;
  nb++;
  trace.endBlock();

  trace.beginBlock(" Voronoi computation l_3");
  typedef ExactPredicateLpSeparableMetric<typename Set::Space,3> L3Metric;
  typedef VoronoiMap<typename Set::Space, Set, L3Metric> Voro3;
  L3Metric l3;
  Voro3 voro3(aSet.domain(), mySet, l3, periodicity);
  trace.endBlock();

  trace.beginBlock("Validating the Voronoi Map l_3");
  nbok += checkVoronoi(aSet, voro3) ? 1 : 0;
  nb++;
  trace.endBlock();

  trace.beginBlock(" DT computation");
  typedef DistanceTransformation<typename Set::Space, Set, L2Metric> DT;
  DT dt(aSet.domain(), mySet, l2, periodicity);
  trace.endBlock();

  return nbok == nb;
}


bool testSimple2D()
{

  Z2i::Point a(-10,-10);
  Z2i::Point b(10,10);
  Z2i::Domain domain(a,b);

  Z2i::DigitalSet sites(domain);
  bool ok = true;

  sites.insertNew( Z2i::Point(3,-6));
  sites.insertNew( Z2i::Point(9,0));
  sites.insertNew( Z2i::Point(-3,0));

  for ( std::size_t i = 0; i < 4; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<2>(i);
      trace.beginBlock( "Simple2D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testVoronoiMapFromSites2D( sites, "simple", periodicity );
      trace.endBlock();
    }

  return ok;

}

bool testSimpleRandom2D()
{
  unsigned size=16;
  Z2i::Point a(0,0);
  Z2i::Point b(size,size);
  Z2i::Domain domain(a,b);

  Z2i::DigitalSet sites(domain);
  bool ok = true;

  for(unsigned int i = 0 ; i < size; ++i)
    {
      Z2i::Point p(  rand() % (b[0]) -  a[0],  rand() % (b[1]) +  a[1]  );
      sites.insert( p );
    }

  for ( std::size_t i = 0; i < 4; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<2>(i);
      trace.beginBlock( "Random 2D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testVoronoiMapFromSites2D( sites, "random", periodicity );
      trace.endBlock();
    }

  for(unsigned int i = 0 ; i < size*size-size; ++i)
    {
      Z2i::Point p(  rand() % (b[0]) -  a[0],  rand() % (b[1]) +  a[1]  );
      sites.insert( p );
    }

  for ( std::size_t i = 0; i < 4; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<2>(i);
      trace.beginBlock( "Random 2D (dense) with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testVoronoiMapFromSites2D( sites, "random-dense", periodicity );
      trace.endBlock();
    }

  return ok;
}


bool testSimple3D()
{

  Z3i::Point a(-10,-10,-10);
  Z3i::Point b(10,10,10);
  Z3i::Domain domain(a,b);

  Z3i::DigitalSet sites(domain);
  bool ok = true;

  sites.insertNew( Z3i::Point(0,0,-6));
  sites.insertNew( Z3i::Point(6,0,0));
  sites.insertNew( Z3i::Point(-6,0,3));

  for ( auto i = 0; i < 8; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<3>(i);
      trace.beginBlock( "Simple3D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testVoronoiMapFromSites( sites, periodicity );
      trace.endBlock();
    }

  return ok;
}

bool testSimpleRandom3D()
{
  std::size_t const N = 16;

  Z3i::Point a(0, 0, 0);
  Z3i::Point b(N, N, N);
  Z3i::Domain domain(a,b);

  Z3i::DigitalSet sites(domain);
  bool ok = true;

  for(unsigned int i = 0 ; i < N; ++i)
    {
      Z3i::Point p(  rand() % (b[0]) -  a[0],
                     rand() % (b[1]) +  a[1],
                     rand() % (b[2]) +  a[2]  );
      sites.insert( p );
    }

  for ( std::size_t i = 0; i < 8; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<3>(i);
      trace.beginBlock( "Random 3D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testVoronoiMapFromSites( sites, periodicity );
      trace.endBlock();
    }

  return ok;
}



bool testSimple4D()
{

  typedef SpaceND<4> Space4;
  Space4::Point a(0,0,0,0);
  Space4::Point b(5,5,5,5);
  HyperRectDomain<Space4> domain(a,b);

  DigitalSetBySTLSet< HyperRectDomain<Space4> > sites(domain);
  bool ok = true;

  sites.insertNew( Space4::Point(1,4,1,1));
  sites.insertNew( Space4::Point(3,1,3,1));
  sites.insertNew( Space4::Point(0,0,0,0));

  for ( std::size_t i = 0; i < 16; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<4>(i);
      trace.beginBlock( "Simple4D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testVoronoiMapFromSites( sites, periodicity );
      trace.endBlock();
    }

  return ok;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class VoronoiMap" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testCheckConcept()
    && testVoronoiMap()
    && testVoronoiMap( { {true, false} } )
    && testVoronoiMap( { {false, true} } )
    && testVoronoiMap( { {true, true} } )
    && testSimple2D()
    && testSimpleRandom2D()
    && testSimple3D()
    && testSimpleRandom3D()
    && testSimple4D()
    ; // && ... other tests

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
