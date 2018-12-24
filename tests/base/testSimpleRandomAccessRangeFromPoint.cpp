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
 * @file testSimpleRandomAccessRangeFromPoint.cpp
 * @ingroup Tests
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 *
 * @date 2015/10/21
 *
 * This file is part of the DGtal library
 */

#include "DGtalCatch.h"

#include <DGtal/kernel/SpaceND.h>
#include <DGtal/kernel/domains/HyperRectDomain.h>
#include <DGtal/kernel/domains/Linearizer.h>
#include <DGtal/images/ImageContainerBySTLVector.h>

#include <algorithm>
#include <cstddef>

TEST_CASE( "Testing SimpleRandomAccess(Const)RangeFromPoint from ImageContainerBySTLVector", "" )
{
  using namespace DGtal;

  typedef double Value;
  typedef SpaceND<2> Space;
  typedef Space::Point Point;
  typedef HyperRectDomain<Space> Domain;
  typedef ImageContainerBySTLVector<Domain, Value> Image;
  typedef Image::Range Range;
  typedef Image::ConstRange ConstRange;
  typedef Linearizer<Domain, ColMajorStorage> Linearizer;

  const Domain domain( Point(1,2), Point(6,5) );
  const Point aPoint(3,4);
  REQUIRE( domain.isInside(aPoint) );

  Image image(domain);
  Image refImage(domain);

  // Initialization
  const double hour = 4.29; // Oups
  std::size_t cnt = 0;
  for ( Domain::ConstIterator it = domain.begin(), it_end = domain.end(); it != it_end; ++it, ++cnt )
    {
      image.setValue(*it, cnt*hour);
      refImage.setValue(*it, cnt*hour);
    }

  SECTION( "Testing constant forward iterators" )
    {
      const Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.end() - range.begin()) == domain.size() );
      REQUIRE( std::equal(range.begin(), range.end(), refImage.begin())  );

      ConstRange crange = image.constRange();
      REQUIRE( static_cast<Domain::Size>(crange.end() - crange.begin()) == domain.size() );
      REQUIRE( std::equal(crange.begin(), crange.end(), refImage.begin()) );
    }

  SECTION( "Testing constant forward iterators from a point" )
    {
      const Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.end() - range.begin(aPoint)) == domain.size() - Linearizer::getIndex(aPoint, domain) );
      REQUIRE( std::equal( range.begin(aPoint), range.end(), refImage.begin() + Linearizer::getIndex(aPoint, domain) ) );

      ConstRange crange = image.constRange();
      REQUIRE( static_cast<Domain::Size>(crange.end() - crange.begin(aPoint)) == domain.size() - Linearizer::getIndex(aPoint, domain) );
      REQUIRE( std::equal( crange.begin(aPoint), crange.end(), refImage.begin() + Linearizer::getIndex(aPoint, domain) ) );
    }

  SECTION( "Testing mutable forward iterators" )
    {
      Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.end() - range.begin()) == domain.size() );

      cnt = 1;
      for ( Range::Iterator it = range.begin(), it_end = range.end(); it != it_end; ++it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstIterator it = domain.begin(), it_end = domain.end(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      REQUIRE( std::equal(range.begin(), range.end(), refImage.begin()) );
    }

  SECTION( "Testing mutable forward iterators from a point" )
    {
      Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.end() - range.begin(aPoint)) == domain.size() - Linearizer::getIndex(aPoint, domain) );

      cnt = 1;
      for ( Range::Iterator it = range.begin(aPoint), it_end = range.end(); it != it_end; ++it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstIterator it = domain.begin(aPoint), it_end = domain.end(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      REQUIRE( std::equal(range.begin(), range.end(), refImage.begin()) );
    }

  SECTION( "Testing constant reverse iterators" )
    {
      const Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.rend() - range.rbegin()) == domain.size() );
      REQUIRE( std::equal(range.rbegin(), range.rend(), refImage.rbegin()) );

      ConstRange crange = image.constRange();
      REQUIRE( static_cast<Domain::Size>(crange.rend() - crange.rbegin()) == domain.size() );
      REQUIRE( std::equal(crange.rbegin(), crange.rend(), refImage.rbegin()) );
    }

  SECTION( "Testing constant reverse iterators from a point" )
    {
      const Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.rend() - range.rbegin(aPoint)) == Linearizer::getIndex(aPoint, domain) + 1 );
      REQUIRE( std::equal( range.rbegin(aPoint), range.rend(), refImage.rbegin() + (domain.size() - Linearizer::getIndex(aPoint, domain) - 1) ) );

      ConstRange crange = image.constRange();
      REQUIRE( static_cast<Domain::Size>(crange.rend() - crange.rbegin(aPoint)) == Linearizer::getIndex(aPoint, domain) + 1 );
      REQUIRE( std::equal( crange.rbegin(aPoint), crange.rend(), refImage.rbegin() + (domain.size() - Linearizer::getIndex(aPoint, domain) - 1) ) );
    }

  SECTION( "Testing mutable reverse iterators" )
    {
      Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.rend() - range.rbegin()) == domain.size() );

      cnt = 1;
      for ( Range::ReverseIterator it = range.rbegin(), it_end = range.rend(); it != it_end; ++it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstReverseIterator it = domain.rbegin(), it_end = domain.rend(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      REQUIRE( std::equal(range.rbegin(), range.rend(), refImage.rbegin()) );
    }

  SECTION( "Testing mutable reverse iterators from a point" )
    {
      Range range = image.range();
      REQUIRE( static_cast<Domain::Size>(range.rend() - range.rbegin(aPoint)) == Linearizer::getIndex(aPoint, domain) + 1 );

      cnt = 1;
      for ( Range::ReverseIterator it = range.rbegin(aPoint), it_end = range.rend(); it != it_end; ++it )
        {
          *it += cnt++;
        }


      cnt = 1;
      for ( Domain::ConstReverseIterator it = domain.rbegin(aPoint), it_end = domain.rend(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      REQUIRE( std::equal(range.rbegin(), range.rend(), refImage.rbegin()) );
    }

  SECTION( "Testing forward output iterators" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Domain::ConstIterator it = domain.begin(), it_end = domain.end(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      std::copy( refImage.begin(), refImage.end(), range.outputIterator() );

      REQUIRE( std::equal(range.begin(), range.end(), refImage.begin()) );
    }

  SECTION( "Testing forward output iterators from a point" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Domain::ConstIterator it = domain.begin(aPoint), it_end = domain.end(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      std::copy( refImage.begin() + Linearizer::getIndex(aPoint, domain), refImage.end(), range.outputIterator(aPoint) );

      REQUIRE( std::equal(range.begin(), range.end(), refImage.begin()) );
    }

  SECTION( "Testing reverse output iterators" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Domain::ConstReverseIterator it = domain.rbegin(), it_end = domain.rend(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      std::copy( refImage.rbegin(), refImage.rend(), range.routputIterator() );

      REQUIRE( std::equal(range.rbegin(), range.rend(), refImage.rbegin()) );
    }

  SECTION( "Testing reverse output iterators from a point" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Domain::ConstReverseIterator it = domain.rbegin(aPoint), it_end = domain.rend(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it)+cnt );
          ++cnt;
        }

      std::copy( refImage.rbegin() + (domain.size() - Linearizer::getIndex(aPoint, domain) - 1), refImage.rend(), range.routputIterator(aPoint) );

      REQUIRE( std::equal(range.rbegin(), range.rend(), refImage.rbegin()) );
    }

  SECTION( "Testing constant forward circulators" )
    {
      // Reference sum
      Value refSum = 0;
      for ( Image::ConstIterator it = refImage.begin(), it_end = refImage.end(); it != it_end; ++it )
        {
          refSum += 2 * (*it);
        }

      // Sum in forward way
      const Range range = image.range();
      Value sum = 0;
      cnt = 1;
      for ( Range::ConstCirculator it = range.c(); cnt <= 2*domain.size(); ++it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );
      REQUIRE( std::equal( refImage.begin(), refImage.end(), range.c() ) );

      // Sum in backward way
      sum = 0;
      cnt = 1;
      for ( Range::ConstCirculator it = range.c(); cnt <= 2*domain.size(); --it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );

      // Sum in forward way
      ConstRange crange = image.constRange();
      sum = 0;
      cnt = 1;
      for ( Range::ConstCirculator it = crange.c(); cnt <= 2*domain.size(); ++it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );
      REQUIRE( std::equal( refImage.begin(), refImage.end(), crange.c() ) );

      // Sum in backward way
      sum = 0;
      cnt = 1;
      for ( Range::ConstCirculator it = crange.c(); cnt <= 2*domain.size(); --it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );
    }

  SECTION( "Testing constant reverse circulators" )
    {
      // Reference sum
      Value refSum = 0;
      for ( Image::ConstIterator it = refImage.begin(), it_end = refImage.end(); it != it_end; ++it )
        {
          refSum += 2 * (*it);
        }

      // Sum in forward way
      const Range range = image.range();
      Value sum = 0;
      cnt = 1;
      for ( Range::ConstReverseCirculator it = range.rc(); cnt <= 2*domain.size(); ++it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );
      REQUIRE( std::equal( refImage.rbegin(), refImage.rend(), range.rc() ) );

      // Sum in backward way
      sum = 0;
      cnt = 1;
      for ( Range::ConstReverseCirculator it = range.rc(); cnt <= 2*domain.size(); --it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );

      // Sum in forward way
      ConstRange crange = image.constRange();
      sum = 0;
      cnt = 1;
      for ( Range::ConstReverseCirculator it = crange.rc(); cnt <= 2*domain.size(); ++it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );
      REQUIRE( std::equal( refImage.rbegin(), refImage.rend(), crange.rc() ) );

      // Sum in backward way
      sum = 0;
      cnt = 1;
      for ( Range::ConstReverseCirculator it = crange.rc(); cnt <= 2*domain.size(); --it )
        {
          sum += *it;
          ++cnt;
        }
      REQUIRE( sum == Approx(refSum) );
    }

  SECTION( "Testing mutable circulators in forward way" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Range::Circulator it = range.c(); cnt <= 2*domain.size(); ++it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstIterator it = domain.begin(), it_end = domain.end(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it) + 2*cnt + domain.size());
          ++cnt;
        }

      REQUIRE( std::equal( range.begin(), range.end(), refImage.begin() ) );
    }

  SECTION( "Testing mutable circulators in backward way" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Range::Circulator it = --range.c(); cnt <= 2*domain.size(); --it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstReverseIterator it = domain.rbegin(), it_end = domain.rend(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it) + 2*cnt + domain.size());
          ++cnt;
        }

      REQUIRE( std::equal( range.begin(), range.end(), refImage.begin() ) );
    }

  SECTION( "Testing mutable reverse circulators in forward way" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Range::ReverseCirculator it = range.rc(); cnt <= 2*domain.size(); ++it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstReverseIterator it = domain.rbegin(), it_end = domain.rend(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it) + 2*cnt + domain.size());
          ++cnt;
        }

      REQUIRE( std::equal( range.begin(), range.end(), refImage.begin() ) );
    }

  SECTION( "Testing mutable reverse circulators in backward way" )
    {
      Range range = image.range();

      cnt = 1;
      for ( Range::ReverseCirculator it = --range.rc(); cnt <= 2*domain.size(); --it )
        {
          *it += cnt++;
        }

      cnt = 1;
      for ( Domain::ConstIterator it = domain.begin(), it_end = domain.end(); it != it_end; ++it )
        {
          refImage.setValue( *it, refImage(*it) + 2*cnt + domain.size());
          ++cnt;
        }

      REQUIRE( std::equal( range.begin(), range.end(), refImage.begin() ) );
    }
}

