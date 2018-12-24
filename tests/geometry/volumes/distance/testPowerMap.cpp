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
 * @file testPowerMap.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/25
 *
 * Functions for testing class PowerMap.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <array>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/volumes/distance/PowerMap.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpPowerSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/ReverseDistanceTransformation.h"
#include "DGtal/kernel/sets/DigitalSetDomain.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class PowerMap.
///////////////////////////////////////////////////////////////////////////////

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

/** Validates the PowerMap
 */
template < typename PowerMap>
bool checkPowerMap( const PowerMap & aPowerMap)
{
  using Point = typename PowerMap::Point;

  // Domain extent
  Point const extent = aPowerMap.domain().upperBound() - aPowerMap.domain().lowerBound() + Point::diagonal();

  // Site shifting depending on the periodicity.
  std::vector< typename PowerMap::PeriodicitySpec > periodicShift;
  for ( std::size_t i = 0; i < ( 1u << PowerMap::Space::dimension ); ++i )
    {
      const auto periodicity = getPeriodicityFromInteger< PowerMap::Space::dimension >( i );

      // Checking if this periodicity possibility is valid.
      bool isValid = true;
      for ( std::size_t j = 0; j < periodicity.size(); ++j )
        if ( periodicity[j] && ! aPowerMap.isPeriodic(j) )
          {
            isValid = false;
            break;
          }

      if ( isValid )
        periodicShift.push_back( periodicity );
    }

  // Weight image
  auto const& image = *(aPowerMap.weightImagePtr());

  // Power metric
  auto const& metric = *(aPowerMap.metricPtr());

  // Pruning sites.
  DigitalSetBySTLSet< typename PowerMap::Domain > aSet( aPowerMap.domain() );
  for ( auto const& pt : image.domain() )
    if ( image(pt) > 0 )
      aSet.insertNew( pt );

  // Checking site for all domain points.
  for ( auto const& pt : aPowerMap.domain() )
    {
      // Getting reference size.
      const Point psite  = aPowerMap(pt);
      const Point boundedPSite  = aPowerMap.projectPoint( psite );

      // Checking that the reference site is actually a given site.
      // Also testing projectPoint method.
      if ( std::find( aSet.begin(), aSet.end(), boundedPSite ) == aSet.end() )
        {
          trace.error() << "The PowerMap point " << psite
                        << " projected to " << aPowerMap.projectPoint( psite )
                        << " is not a valid site." << std::endl;
          return false;
        }

      // Calculating reference power distance.
      const auto dist = metric.powerDistance( pt, psite, image( boundedPSite ) );

      // Checking if we can found a better site.
      for ( auto site : aSet )
        {
          // Trying all shifting possibilities of the site depending on the domain periodicity.
          for ( auto const & periodicity : periodicShift )
            {
              auto currSite = site;

              // Shifting site.
              for ( std::size_t dim = 0; dim < PowerMap::Space::dimension ; ++dim )
                if ( periodicity[dim] )
                  currSite[dim] += ( pt[dim] < currSite[dim] ? -1 : 1 ) * extent[dim];

              // Checking raw-distance.
              const auto dbis = metric.powerDistance( pt, currSite, image( site ) );
              if ( dbis < dist )
                {
                  trace.error() << "DT Error at " << pt
                                << "  PowerMap:" << psite << "@" << image(boundedPSite) << " (" << dist << ")"
                                << "  from set:" << site << "@" << image(site) << " (" << dbis << ")"
                                << " projected from " << currSite << "." << std::endl;
                  return false;
                }
            }
        }
    }

  return true;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testPowerMap( std::array<bool, 2> const& aPeriodicity = {{ false, false }} )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing PowerMap2D with periodicity " + formatPeriodicity(aPeriodicity) );

  Z2i::Domain domain(Z2i::Point(0,0),Z2i::Point(10,10));
  Z2i::Domain domainLarge(Z2i::Point(0,0),Z2i::Point(10,10));

  DigitalSetBySTLSet<Z2i::Domain > set(domain);
  set.insertNew(Z2i::Point(3,3));
  //set.insertNew(Z2i::Point(3,7));
  set.insertNew(Z2i::Point(7,7));

  using SetDomain = DigitalSetDomain< DigitalSetBySTLSet<Z2i::Domain > >;
  using Image = ImageContainerBySTLMap< SetDomain , DGtal::int64_t>;

  Image image( new SetDomain( set ) );

  //Setting some values
  image.setValue(Z2i::Point(3,3), 9);
  //  image.setValue(Z2i::Point(3,7), 0);
  image.setValue(Z2i::Point(7,7), 16);

  Z2i::L2PowerMetric l2power;
  PowerMap<Image, Z2i::L2PowerMetric> power(&domainLarge, &image, &l2power, aPeriodicity);
  for(unsigned int i=0; i<11; i++)
    {
      for(unsigned int j=0; j<11; j++)
        if (image.domain().isInside(Z2i::Point(i,j)))
          trace.info()<< image(Z2i::Point(i,j))<<" ";
        else
          trace.info()<< "0 ";
      trace.info()<<std::endl;
    }
  trace.info()<<std::endl;

  //Power Map
  for(unsigned int i=0; i<11; i++)
    {
      for(unsigned int j=0; j<11; j++)
        trace.info()<< power(Z2i::Point(i,j))[0]<<","<<power(Z2i::Point(i,j))[1]<<" ";
      trace.info()<<std::endl;
    }
  trace.info() << "REDT" << std::endl;
  trace.info() << std::endl;

  // Checking PowerMap validity.
  trace.beginBlock("Validating the Power Map");
  nbok += checkPowerMap( power ) ? 1 : 0;
  nb++;
  trace.endBlock();
  trace.info() << std::endl;

  //Reconstruction
  for(unsigned int i=0; i<11; i++)
    {
      for(unsigned int j=0; j<11; j++)
        {
          Z2i::Point p(i,j);
          DGtal::int64_t dist = (i-power(p)[0])*(i-power(p)[0]) +
            ( j-power(p)[1])*(j-power(p)[1])  - image( power.projectPoint(power(p)) );
          trace.info()<< dist;
        }
      std::cerr<<std::endl;
    }
  trace.info()<<std::endl;

  //Reconstruction
  for(unsigned int i=0; i<11; i++)
    {
      for(unsigned int j=0; j<11; j++)
        {
          Z2i::Point p(i,j);
          DGtal::int32_t dist = (i-power(p)[0])*(i-power(p)[0]) +
            ( j-power(p)[1])*(j-power(p)[1])  - image( power.projectPoint(power(p)) );
          if (dist>=0)
            std::cerr<< "0 ";
          else
            std::cerr<< "X ";
        }
      std::cerr<<std::endl;
    }

  nbok += true ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
    << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

bool testCheckConcept()
{
  using SetDomain   = DigitalSetDomain< DigitalSetBySTLSet<Z2i::Domain > >;
  using Image       = ImageContainerBySTLMap< SetDomain , DGtal::int64_t>;
  using PowerMetric = Z2i::L2PowerMetric;

  BOOST_CONCEPT_ASSERT(( concepts::CConstImage< PowerMap< Image, PowerMetric > >));

  return true;
}

template < typename Set >
bool testPowerMapFromSites( const Set &aSet )
{
  std::array<bool, Set::dimension> periodicity;
  periodicity.fill( false );
  return testPowerMapFromSites( aSet, periodicity );
}

template < typename Set >
bool testPowerMapFromSites( const Set &aSet, std::array<bool, Set::Space::dimension> const & periodicity )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  using SetDomain = DigitalSetDomain< Set >;
  using Image = ImageContainerBySTLMap< SetDomain , DGtal::int64_t>;

  // Weight image.
  Image image( new SetDomain( aSet ) );

  // Setting weights
  typename Image::Value weight = 2;
  for ( auto const & pt : image.domain() )
    {
      image.setValue( pt, weight );
      weight *= 2;
    }

  trace.beginBlock(" Power Map computation l_2");
  typedef ExactPredicateLpPowerSeparableMetric<typename Set::Space, 2> L2PowerMetric;
  typedef PowerMap< Image, L2PowerMetric > Power2;
  L2PowerMetric l2;
  Power2 power2( aSet.domain(), image, l2, periodicity);
  trace.endBlock();

  trace.beginBlock("Validating the Power Map");
  nbok += checkPowerMap( power2 ) ? 1 : 0;
  nb++;
  trace.endBlock();

  trace.beginBlock(" Power Map computation l_3");
  typedef ExactPredicateLpPowerSeparableMetric<typename Set::Space, 3> L3PowerMetric;
  typedef PowerMap< Image, L3PowerMetric > Power3;
  L3PowerMetric l3;
  Power3 power3( aSet.domain(), image, l3, periodicity);
  trace.endBlock();

  trace.beginBlock("Validating the Power Map l_3");
  nbok += checkPowerMap( power3 ) ? 1 : 0;
  nb++;
  trace.endBlock();

  trace.beginBlock("Reverse DT computation");
  typedef ReverseDistanceTransformation<typename Power2::WeightImage, L2PowerMetric> RDT;
  RDT rdt(aSet.domain(), power2.weightImagePtr(), l2, periodicity);
  trace.endBlock();

  return nbok == nb;
}

bool testSimple2D()
{

  Z2i::Point a(-10,-10);
  Z2i::Point b(10,10);
  Z2i::Domain domain(a,b);

  DigitalSetBySTLSet<Z2i::Domain> sites(domain);
  bool ok = true;

  sites.insertNew( Z2i::Point(3,-6));
  sites.insertNew( Z2i::Point(9,0));
  sites.insertNew( Z2i::Point(-3,0));

  for ( std::size_t i = 0; i < 4; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<2>(i);
      trace.beginBlock( "Simple2D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testPowerMapFromSites( sites, periodicity );
      trace.endBlock();
    }

  return ok;

}

bool testSimple3D()
{

  Z3i::Point a(-10,-10,-10);
  Z3i::Point b(10,10,10);
  Z3i::Domain domain(a,b);

  DigitalSetBySTLSet<Z3i::Domain> sites(domain);
  bool ok = true;

  sites.insertNew( Z3i::Point(0,0,-6));
  sites.insertNew( Z3i::Point(6,0,0));
  sites.insertNew( Z3i::Point(-6,0,3));

  for ( std::size_t i = 0; i < 8; ++i )
    {
      auto const periodicity = getPeriodicityFromInteger<3>(i);
      trace.beginBlock( "Simple3D with periodicity " + formatPeriodicity(periodicity) );
      ok = ok && testPowerMapFromSites( sites, periodicity );
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
      ok = ok && testPowerMapFromSites( sites, periodicity );
      trace.endBlock();
    }

  return ok;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class PowerMap" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testCheckConcept()
    && testPowerMap()
    && testPowerMap( {{ true,  false }} )
    && testPowerMap( {{ false, true }} )
    && testPowerMap( {{ true,  true }} )
    && testSimple2D()
    && testSimple3D()
    && testSimple4D()
    ; // && ... other tests

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
