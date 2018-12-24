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
 * @file
 * @ingroup Tests
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 *
 *
 * @date 2016/06/02
 *
 * This file is part of the DGtal library
 */

/**
 * Description of testRealFFT.cpp <p>
 * Aim: Tests of real-data in-place Fast Fourier Transform featured by RealFFT.
 */

#ifndef WITH_FFTW3
  #error You need to have activated FFTW3 (WITH_FFTW3) to include this file.
#endif

#include <cstddef>
#include <algorithm>
#include <complex>
#include <cmath>
#include <limits>
#include <string>
#include <random>

#include <boost/math/constants/constants.hpp>

#include "DGtalCatch.h"
#include "ConfigTest.h"

#include "DGtal/math/RealFFT.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/writers/PGMWriter.h"
#include "DGtal/base/BasicFunctors.h"

using namespace DGtal;

/** Tests of forward FFT followed by a backward FFT.
* @tparam  TDomain Domain type.
* @tparam  TValue  Value type.
* @param   anImage The image to transform.
*/
template <
  typename TDomain,
  typename TValue
>
void testForwardBackwardFFT( ImageContainerBySTLVector<TDomain, TValue> const & anImage )
{
  using FFT = RealFFT< TDomain, TValue >;

  INFO( "Initializing RealFFT." );
  FFT fft( anImage.domain() );

  INFO( "Copying data from the image." );
  auto spatial_image = fft.getSpatialImage();
  std::copy( anImage.cbegin(), anImage.cend(), spatial_image.begin() );

  INFO( "Forward transformation." );
  fft.forwardFFT( FFTW_ESTIMATE );

  INFO( "Checking modification of the input image." );
  REQUIRE( ! std::equal( anImage.cbegin(), anImage.cend(), spatial_image.cbegin() ) );

  INFO( "Backward transformation." );
  fft.backwardFFT( FFTW_ESTIMATE );

  INFO( "Comparing result with original image." );
  const auto eps = 100 * std::numeric_limits<TValue>::epsilon() * std::log( anImage.domain().size() );
  CAPTURE( eps );

  for ( auto it = spatial_image.cbegin(); it != spatial_image.cend(); ++it )
    {
      if ( std::abs( *it - anImage( it.getPoint() ) ) > eps * std::max( *it, TValue(1) ) )
        FAIL( "Approximation failed: " << *it << " - " << anImage( it.getPoint() ) << " = " << (*it - anImage( it.getPoint() ) ) );
    }
}

/** Find element with maximal norm in a range.
 * @tparam  TIterator   Iterator type.
 * @param   it      Iterator to the range begin.
 * @param   it_end  Iterator the the range end.
 * @return  the iterator to the maximal element.
 */
template <typename TIterator>
TIterator findMaxNorm( TIterator it, TIterator const & it_end )
{
  auto norm_max = std::norm(*it);
  auto it_max   = it;

  for ( ; it != it_end; ++it )
    if ( std::norm(*it) > norm_max )
      {
        norm_max = std::norm(*it);
        it_max   = it;
      }

  return it_max;
}

/** Tests spatial domain scaling.
* @tparam   TDomain   Domain type.
* @tparam   TValue    Value type.
* @param    anImage   The image from which to take the domain.
*/
template <
  typename TDomain,
  typename TValue
>
void testFFTScaling( ImageContainerBySTLVector<TDomain, TValue> const & anImage )
{
  typedef RealFFT< TDomain, TValue > FFT; // "typedef" instead of "using" because of g++ 4.7.4 bug.
  using RealPoint = typename FFT::RealPoint;

  const TValue pi = boost::math::constants::pi<TValue>();
  const TValue freq = 5;
  const TValue phase = pi/4;

  INFO( "Checking image size." );
  REQUIRE( anImage.extent()[ TDomain::dimension-1 ] >= 2*std::abs(freq) );

  INFO( "Initializing RealFFT." );
  FFT fft( anImage.domain(), RealPoint::zero, RealPoint::diagonal(1) );

  INFO( "Initializing spatial data." );
  auto spatial_image = fft.getSpatialImage();
  for ( auto it = spatial_image.begin(); it != spatial_image.end(); ++it )
    {
      const auto pt = fft.calcScaledSpatialCoords( it.getPoint() );
      REQUIRE( fft.calcNativeSpatialCoords( pt ) == it.getPoint() );

      *it = std::cos( 2*pi * freq * pt[ TDomain::dimension - 1 ] + phase );
    }

  INFO( "Forward transformation." );
  fft.forwardFFT( FFTW_ESTIMATE );

  INFO( "Finding maximal frequency..." );
  const auto freq_image = fft.getFreqImage();
  const auto it_max = findMaxNorm( freq_image.cbegin(), freq_image.cend() );
  const auto pt_max = it_max.getPoint();
  INFO( "\tat " << pt_max << " with value " << *it_max );

  INFO( "Checks maximal frequency on unit domain." );
    {
      auto freq_pt  = fft.calcScaledFreqCoords( it_max.getPoint() );
      auto freq_val = fft.calcScaledFreqValue( freq_pt, *it_max );

      bool applyConj;
      REQUIRE( fft.calcNativeFreqCoords( freq_pt, applyConj ) == it_max.getPoint() );
      REQUIRE( ! applyConj );
      REQUIRE( std::norm( fft.calcNativeFreqValue( freq_pt, freq_val ) - *it_max ) == Approx(0.) );
      REQUIRE( std::norm( fft.getScaledFreqValue( freq_pt ) - freq_val ) == Approx(0.) );

      if ( freq_pt[ TDomain::dimension-1 ] * freq < 0 )
        {
          freq_pt  = -freq_pt;
          freq_val = std::conj( freq_val );
        }

      REQUIRE( ( freq_pt - RealPoint::base( TDomain::dimension-1, freq ) ).norm() == Approx( 0 ) );
      REQUIRE( ( std::fmod( std::fmod( std::arg( freq_val ) - phase, 2*pi ) + 3*pi, 2*pi ) - pi ) == Approx( 0 ) );

    }

  INFO( "Checks maximal frequency on translated unit domain." );
    {
      fft.setScaledSpatialLowerBound( RealPoint::diagonal( 1. / (4*freq) ) );

      auto freq_pt  = fft.calcScaledFreqCoords( it_max.getPoint() );
      auto freq_val = fft.calcScaledFreqValue( freq_pt, *it_max );

      bool applyConj;
      REQUIRE( fft.calcNativeFreqCoords( freq_pt, applyConj ) == it_max.getPoint() );
      REQUIRE( ! applyConj );
      REQUIRE( std::norm( fft.calcNativeFreqValue( freq_pt, freq_val ) - *it_max ) == Approx(0.) );
      REQUIRE( std::norm( fft.getScaledFreqValue( freq_pt ) - freq_val ) == Approx(0.) );

      if ( freq_pt[ TDomain::dimension-1 ] * freq < 0 )
        {
          freq_pt  = -freq_pt;
          freq_val = std::conj( freq_val );
        }

      REQUIRE( ( freq_pt - RealPoint::base( TDomain::dimension-1, freq ) ).norm() == Approx( 0 ) );
      REQUIRE( ( std::fmod( std::fmod( std::arg( freq_val ) - phase + pi/2, 2*pi) + 3*pi, 2*pi ) - pi ) == Approx( 0 ) );
    }

  INFO( "Checks maximal frequency on translated initial domain." );
    {
      const RealPoint shift = RealPoint::diagonal( 3. );

      fft.setScaledSpatialExtent( anImage.extent() );
      fft.setScaledSpatialLowerBound( shift );

      auto freq_pt  = fft.calcScaledFreqCoords( it_max.getPoint() );
      auto freq_val = fft.calcScaledFreqValue( freq_pt, *it_max );

      bool applyConj;
      REQUIRE( fft.calcNativeFreqCoords( freq_pt, applyConj ) == it_max.getPoint() );
      REQUIRE( ! applyConj );
      REQUIRE( std::norm( fft.calcNativeFreqValue( freq_pt, freq_val ) - *it_max ) == Approx(0.) );
      REQUIRE( std::norm( fft.getScaledFreqValue( freq_pt ) - freq_val ) == Approx(0.) );

      if ( freq_pt[ TDomain::dimension-1 ] * freq < 0 )
        {
          freq_pt  = -freq_pt;
          freq_val = std::conj( freq_val );
        }

      const auto scaled_factor = freq/anImage.extent()[ TDomain::dimension-1 ];
      REQUIRE( ( freq_pt - RealPoint::base( TDomain::dimension-1, scaled_factor ) ).norm() == Approx( 0 ) );
      REQUIRE( ( std::fmod( std::fmod( std::arg( freq_val ) - phase + 2*pi*scaled_factor*shift[TDomain::dimension-1], 2*pi ) + 3*pi, 2*pi ) - pi ) == Approx( 0 ) );
    }
}

/** Compares the FFT of an image with the FFT of its translation.
* @tparam   TDomain   Domain type.
* @tparam   TValue    Value type.
* @param    anImage   The image from which to take the domain.
*/
template <
  typename TDomain,
  typename TValue
>
void cmpTranslatedFFT( ImageContainerBySTLVector<TDomain, TValue> const & anImage )
{
  using FFT = RealFFT< TDomain, TValue >;
  using Point = typename TDomain::Point;

  const Point shift = anImage.extent() / 3;
  const auto domain = anImage.domain();
  const TDomain shifted_domain = TDomain( domain.lowerBound() + shift, domain.upperBound() + shift );

  INFO( "Initializing RealFFT." );
  FFT fft( domain );
  //FFT shifted_fft( domain, domain.lowerBound() + shift, anImage.extent() );
  FFT shifted_fft( shifted_domain );

  INFO( "Pre-creating plan." );
  fft.createPlan( FFTW_MEASURE, FFTW_FORWARD );

  INFO( "Copying data from the image." );
  auto spatial_image = fft.getSpatialImage();
  std::copy( anImage.cbegin(), anImage.cend(), spatial_image.begin() );

  auto shifted_spatial_image = shifted_fft.getSpatialImage();
  const auto spatial_extent  = shifted_fft.getSpatialExtent();
  for ( auto it = shifted_spatial_image.begin(); it != shifted_spatial_image.end(); ++it )
    {
      // Calculating shifted coordinates with periodicity.
      Point pt = it.getPoint();
      for ( typename Point::Dimension i = 0; i < Point::dimension; ++i )
        if ( pt[ i ] > domain.upperBound()[ i ] )
          pt[ i ] -= anImage.extent()[ i ];

      *it = anImage( pt );
    }

  INFO( "Forward transformation (forcing plan re-use)." );
  fft.forwardFFT( FFTW_MEASURE | FFTW_WISDOM_ONLY );
  shifted_fft.forwardFFT( FFTW_MEASURE | FFTW_WISDOM_ONLY );

  INFO( "Comparing results." );
  auto freq_image = fft.getFreqImage();
  auto shifted_freq_image = shifted_fft.getFreqImage();
  const TValue eps = 100 * std::numeric_limits<TValue>::epsilon();

  for ( auto it = freq_image.cbegin(), shifted_it = shifted_freq_image.cbegin(); it != freq_image.cend(); ++it, ++shifted_it )
    {
      if ( std::norm(
                        fft.calcScaledFreqValue( fft.calcScaledFreqCoords( it.getPoint() ), *it )
                      - shifted_fft.calcScaledFreqValue( shifted_fft.calcScaledFreqCoords( shifted_it.getPoint() ), *shifted_it ) )
                > eps * std::max( std::norm(*it), TValue(1) ) )
        FAIL( "Approximation failed at point " << it.getPoint()
              << " between " << *it
              << " and " << shifted_fft.calcScaledFreqValue( shifted_fft.calcScaledFreqCoords( shifted_it.getPoint() ), *shifted_it )
              << " (scaled from " << *shifted_it << ")" );
    }

}
///////////////////////////////////////////////////////////////////////////////
// Test cases.

#ifdef WITH_FFTW3_FLOAT
TEST_CASE( "Checking RealFFT on a 2D image in float precision.", "[2D][float]" )
{
  constexpr typename DGtal::Dimension N = 2;
  const std::string file_name = testPath + "/samples/church-small.pgm";

  using real = float;
  using Space = SpaceND<N>;
  using Domain = HyperRectDomain<Space>;
  using Image = ImageContainerBySTLVector<Domain, real>;

  INFO( "Importing image " );
  const auto image = PGMReader< Image, functors::Cast<real> >::importPGM( file_name );

  INFO( "Testing forward and backward FFT." );
  testForwardBackwardFFT( image );

  INFO( "Testing spatial domain scaling." );
  testFFTScaling( image );

  INFO( "Testing FFT on translated image." );
  cmpTranslatedFFT( image );
}
#endif

#ifdef WITH_FFTW3_DOUBLE
TEST_CASE( "Checking RealFFT on a 2D image in double precision.", "[2D][double]" )
{
  constexpr typename DGtal::Dimension N = 2;
  const std::string file_name = testPath + "/samples/church-small.pgm";

  using real    = double;
  using Space   = SpaceND<N>;
  using Domain  = HyperRectDomain<Space>;
  using Image   = ImageContainerBySTLVector<Domain, real>;

  INFO( "Importing image " );
  const auto image = PGMReader< Image, functors::Cast<real> >::importPGM( file_name );

  INFO( "Testing forward and backward FFT." );
  testForwardBackwardFFT( image );

  INFO( "Testing spatial domain scaling." );
  testFFTScaling( image );

  INFO( "Testing FFT on translated image." );
  cmpTranslatedFFT( image );
}
#endif

#ifdef WITH_FFTW3_LONG
TEST_CASE( "Checking RealFFT on a 2D image in long double precision.", "[2D][long double]" )
{
  using namespace DGtal;

  constexpr typename DGtal::Dimension N = 2;
  const std::string file_name = testPath + "/samples/church-small.pgm";

  using real    = long double;
  using Space   = SpaceND<N>;
  using Domain  = HyperRectDomain<Space>;
  using Image   = ImageContainerBySTLVector<Domain, real>;

  INFO( "Importing image " );
  const auto image = PGMReader< Image, functors::Cast<real> >::importPGM( file_name );

  INFO( "Testing forward and backward FFT." );
  testForwardBackwardFFT( image );

  INFO( "Testing spatial domain scaling." );
  testFFTScaling( image );

  INFO( "Testing FFT on translated image." );
  cmpTranslatedFFT( image );
}
#endif

#ifdef WITH_FFTW3_DOUBLE
TEST_CASE( "Checking RealFFT on a 3D image in double precision.", "[3D][double]" )
{
  constexpr typename DGtal::Dimension N = 3;

  using real  = double;
  using Space = SpaceND<N>;
  using Point = Space::Point;
  using Domain = HyperRectDomain<Space>;
  using Image = ImageContainerBySTLVector<Domain, real>;

  const Domain domain( {0, 10, 13}, {31, 28, 45} );
  Image image( domain );
  auto const extent = image.extent();

  INFO( "Filling the image randomly." );
  const std::size_t CNT = image.size() / 100;
  std::random_device rd;
  std::mt19937 gen( rd() );
  std::uniform_real_distribution<> dis{};
  Point pt;

  for ( std::size_t i = 0; i < CNT; ++i )
    {
      for ( Dimension d = 0; d < N; ++d )
        pt[ d ] = domain.lowerBound()[ d ] + std::floor( extent[ d ] * dis(gen) );
      image.setValue( pt, 1. );
    }

  INFO( "Testing forward and backward FFT." );
  testForwardBackwardFFT( image );

  INFO( "Testing spatial domain scaling." );
  testFFTScaling( image );

  INFO( "Testing FFT on translated image." );
  cmpTranslatedFFT( image );
}
#endif

#ifdef WITH_FFTW3_DOUBLE
TEST_CASE( "Checking RealFFT on a 4D image in double precision.", "[4D][double]" )
{
  constexpr typename DGtal::Dimension N = 4;

  using real  = double;
  using Space = SpaceND<N>;
  using Point = Space::Point;
  using Domain = HyperRectDomain<Space>;
  using Image = ImageContainerBySTLVector<Domain, real>;

  const Domain domain( {0, 10, 13, 5}, {11, 28, 25, 17} );
  Image image( domain );
  auto const extent = image.extent();

  INFO( "Filling the image randomly." );
  const std::size_t CNT = image.size() / 100;
  std::random_device rd;
  std::mt19937 gen( rd() );
  std::uniform_real_distribution<> dis{};
  Point pt;

  for ( std::size_t i = 0; i < CNT; ++i )
    {
      for ( Dimension d = 0; d < N; ++d )
        pt[ d ] = domain.lowerBound()[ d ] + std::floor( extent[ d ] * dis(gen) );
      image.setValue( pt, 1. );
    }

  INFO( "Testing forward and backward FFT." );
  testForwardBackwardFFT( image );

  INFO( "Testing spatial domain scaling." );
  testFFTScaling( image );

  INFO( "Testing FFT on translated image." );
  cmpTranslatedFFT( image );
}
#endif


