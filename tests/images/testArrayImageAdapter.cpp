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
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/07/16
 *
 * This file is part of the DGtal library
 */

#include <cstddef>
#include <iostream>
#include <new>
#include <cmath>

#include <DGtal/kernel/SpaceND.h>
#include <DGtal/kernel/domains/HyperRectDomain.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include <DGtal/images/CConstImage.h>
#include <DGtal/images/CImage.h>

#include <DGtal/images/ArrayImageAdapter.h>

#include "DGtalCatch.h"

using namespace DGtal;
using namespace std;

template < typename TImage, typename TDomain >
void fillImageWithCounter ( TImage& anImage, TDomain const& aDomain )
{
  size_t cnt = 0;
  for ( auto const& point : aDomain )
    anImage.setValue( point, cnt++ );
}

template < typename TImage >
void fillImageWithCounter ( TImage& anImage )
{
  fillImageWithCounter( anImage, anImage.domain() );
}

template < typename TImage, typename TFunction, typename TDomain >
void fillImageWithPointFn ( TImage& anImage, TFunction const& aFunction, TDomain const& domain )
{
  using Image = TImage;
  using Value = typename Image::Value;
  for ( auto const& point : domain )
    {
      Value value = 0;
      for ( Dimension i = 0; i < Image::dimension; ++i )
        value += aFunction( i, point[i] );

      anImage.setValue(point, value);
    }
}

template < typename TImage, typename TFunction >
void fillImageWithPointFn ( TImage& anImage, TFunction const& aFunction )
{
  fillImageWithPointFn ( anImage, aFunction, anImage.domain() );
}

template < typename TImage, typename TFunction, typename TDomain >
void incrementImageWithPointFn ( TImage& anImage, TFunction const& aFunction, TDomain const& domain )
{
  using Image = TImage;
  using Value = typename Image::Value;
  for ( auto const& point : domain )
    {
      Value value = anImage(point);
      for ( Dimension i = 0; i < Image::dimension; ++i )
        value += aFunction( i, point[i] );

      anImage.setValue(point, value);
    }
}

template < typename TImage, typename TFunction >
void incrementImageWithPointFn ( TImage& anImage, TFunction const& aFunction )
{
  incrementImageWithPointFn ( anImage, aFunction, anImage.domain() );
}

template < typename TDomain, typename TValue, typename TFunction >
void fastFillImageWithPointFn ( ImageContainerBySTLVector<TDomain, TValue>& anImage, TFunction const& aFunction )
{
  typedef ImageContainerBySTLVector<TDomain, TValue> Image; // 'typedef' instead of 'using' because of g++ 4.7.4 bug.
  using Value = typename Image::Value;
  auto imgit = anImage.begin();
  for ( auto const& point : anImage.domain() )
    {
      Value value = 0;
      for ( Dimension i = 0; i < Image::dimension; ++i )
        value += aFunction( i, point[i] );

      *(imgit++) = value;
    }
}

template < typename TIterator, typename TDomain, typename TFunction >
void fastFillImageWithPointFn ( ArrayImageAdapter<TIterator, TDomain>& anImage, TFunction const& aFunction )
{
  typedef ArrayImageAdapter<TIterator, TDomain> Image; // 'typedef' instead of 'using' because of g++ 4.7.4 bug.
  using Value = typename Image::Value;
  for ( auto imgit = anImage.begin(); imgit != anImage.end(); ++imgit )
    {
      Value value = 0;
      auto const point = imgit.getPoint();

      for ( Dimension i = 0; i < Image::dimension; ++i )
        value += aFunction( i, point[i] );

      *imgit = value;
    }
}

template < typename TImage >
void checkImage( TImage& anImage )
{
  using Image = TImage;
  using Value = typename Image::Value;
  using Domain = typename Image::Domain;
  using Point = typename Image::Point;
  using Dimension = typename Point::Dimension;
  using Coordinate = typename Point::Coordinate;
  using RefImage = ImageContainerBySTLVector<Domain, Value>;

  // Checks CImage concept.
  BOOST_CONCEPT_ASSERT( (DGtal::concepts::CImage<TImage>) );

  size_t nb = 0;
  size_t nbok = 0;

  // Full domain
  auto const domain = anImage.domain();

  // Sub domain
  Point lowerPt = domain.lowerBound();
  Point upperPt = domain.upperBound();
  for ( Dimension i = 0; i < Domain::dimension; ++i )
    {
      lowerPt[i] = std::min( upperPt[i]-1, lowerPt[i] + 1 + static_cast<Coordinate>(i) );
      upperPt[i] = std::max( lowerPt[i]+1, upperPt[i] - static_cast<Coordinate>(Domain::dimension - i) );
    }
  auto const sub_domain = Domain( lowerPt, upperPt );

  // Checks that sub domain is not empty and different of full domain
  REQUIRE( (!sub_domain.isEmpty() && sub_domain.size() != domain.size()) );

  // Reference image
  RefImage ref_image( domain );

  // The filling function
  auto const fn = [] (size_t i, Coordinate x) { return cos( static_cast<Value>(pow(100, i)*x ) ); };

  // Fill with function
  SECTION( "Filling with point dependant function" )
    {
      fillImageWithPointFn( ref_image, fn );
      fillImageWithPointFn( anImage, fn );
      REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
    }

  // Fill with counter
  SECTION( "Filling with counter" )
    {
      fillImageWithCounter( ref_image );
      fillImageWithCounter( anImage );
      REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
    }

  // Fast filling with function
  SECTION( "Fast filling with point dependant function" )
    {
      fastFillImageWithPointFn( ref_image, fn );
      fastFillImageWithPointFn( anImage, fn );
      REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
    }

  // Tests that need images to be initialized.
  SECTION( "Tests on initialized images" )
    {
      fastFillImageWithPointFn( ref_image, fn );
      fastFillImageWithPointFn( anImage, fn );
      REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );

      // Increment with function
      SECTION( "Incrementing with point dependant function" )
        {
          incrementImageWithPointFn( ref_image, fn );
          incrementImageWithPointFn( anImage, fn );
          REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
        }

      // Partial fill with counter
      SECTION( "Partial filling with counter" )
        {
          auto sub_image = makeArrayImageAdapterFromImage( anImage, sub_domain );
          fillImageWithCounter( ref_image, sub_domain );
          fillImageWithCounter( sub_image );
          REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
        }

      // Partial increment with function
      SECTION( "Partial increment with point dependant function" )
        {
          auto sub_image = makeArrayImageAdapterFromImage( anImage, sub_domain );
          incrementImageWithPointFn( ref_image, fn, sub_domain );
          incrementImageWithPointFn( sub_image, fn );
          REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
        }

      // Fast partial fill with function
      SECTION( "Fast partial filling with point dependand function" )
        {
          auto sub_image = makeArrayImageAdapterFromImage( anImage, sub_domain );
          fillImageWithPointFn( ref_image, fn,  sub_domain );
          fastFillImageWithPointFn( sub_image, fn );
          REQUIRE( std::equal( ref_image.begin(), ref_image.end(), anImage.begin() ) );
        }
    }
}

// Context for each image test
template < DGtal::Dimension N >
struct TestImage
{
  using Space = SpaceND<N>;
  using Domain = HyperRectDomain<Space>;
  using Value = double;

  template < typename TImage >
  static 
  void checkThat( TImage & anImage )
    {
      checkImage(anImage);
    }

  static const Domain domain;
  static const Domain subDomain;
};

// Context data for 3D image tests
using TestImage3D = TestImage<3>;
template <> const TestImage3D::Domain TestImage3D::domain{ {0, 1, 2}, {12, 8, 11} };
template <> const TestImage3D::Domain TestImage3D::subDomain{ {0, 2, 4}, {8, 7, 10} };

// Test cases
TEST_CASE_METHOD( TestImage3D, "Checking ArrayImageAdapter with C-style array", "[CArray][FullDomain]" )
{
  Value* data = new Value[domain.size()];
  auto image = makeArrayImageAdapterFromIterator( data, domain );
  checkThat(image);
  delete[] data;
}

TEST_CASE_METHOD( TestImage3D, "Checking ArrayImageAdapter with C-style array on sub-domain", "[CArray][SubDomain]" )
{
  Value* data = new Value[domain.size()];
  auto image = makeArrayImageAdapterFromIterator( data, domain, subDomain );
  checkThat(image);
  delete[] data;
}

TEST_CASE_METHOD( TestImage3D, "Checking ArrayImageAdapter with ImageContainerBySTLVector", "[ImageSTL][FullDomain]" )
{
  ImageContainerBySTLVector<Domain, Value> image(domain);
  auto image_view = makeArrayImageAdapterFromImage( image );
  checkThat(image_view);
}

TEST_CASE_METHOD( TestImage3D, "Checking ArrayImageAdapter with ImageContainerBySTLVector on sub-domain", "[ImageSTL][SubDomain]" )
{
  ImageContainerBySTLVector<Domain, Value> image(domain);
  auto image_view = makeArrayImageAdapterFromImage( image, subDomain );
  checkThat(image_view);
}

