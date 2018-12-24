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
 * @file testRawReader.cpp
 * @ingroup Tests
 *
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @autor Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 10/12/2015
 *
 * Functions for testing class RawReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtalCatch.h"
#include <DGtal/base/Common.h>
#include <DGtal/kernel/SpaceND.h>
#include <DGtal/kernel/domains/HyperRectDomain.h>
#include <DGtal/images/ImageSelector.h>
#include <DGtal/io/readers/RawReader.h>
#include <DGtal/io/writers/RawWriter.h>
#include <DGtal/kernel/domains/Linearizer.h>

#include <ConfigTest.h>

#include <string>

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

/** Compares an image to the reference data.
 * @tparam  Image   Image type.
 * @param   anImage The image to test.
 */
template <
  typename Image
>
void testImageOnRef( Image const& anImage )
{
  typedef typename Image::Domain  Domain;
  typedef typename Domain::Point  Point;
  
  // Checking domain
  INFO( "Checking domain" )
  REQUIRE( anImage.domain().lowerBound() == Point::diagonal(0) );
  REQUIRE( anImage.domain().upperBound() == Point::diagonal(4) );

  // Checking values
  INFO( "Checking values" )
  const Domain domain = anImage.domain();
  for ( typename Domain::ConstIterator it = domain.begin(), itEnd = domain.end(); it != itEnd; ++it )
    {
      const Point pt = *it;
      const unsigned int refValue =   anImage.dimension  == 2 ?
            1000000 * pt[0] * pt[1]
          : 250000  * pt[0] * pt[1] * pt[2];

      INFO( "At point " << pt );
      REQUIRE( anImage( pt ) == refValue );
    }
}

/** Reads and compares a raw file to the reference data.
 * @tparam N  Dimension of the image.
 */
template < 
  DGtal::Dimension N
>
void testRawReaderOnRef()
{
  REQUIRE( N >= 2 );
  REQUIRE( N <= 3 );

  typedef SpaceND<N> Space;
  typedef HyperRectDomain<Space> Domain;
  typedef typename ImageSelector<Domain, unsigned int>::Type Image;
  typedef typename Domain::Vector  Vector;

  // Generating file name
  std::string fileName = testPath + "samples/";
  if ( N == 2)
    fileName += "raw32bits5x5.raw";
  else
    fileName += "raw32bits5x5x5.raw";

  // Reading file
  const Vector extent = Vector::diagonal(5);
  
  INFO( "Reading file with importRaw32" << fileName );
  Image imageRaw32 = RawReader<Image>::importRaw32( fileName, extent );
  testImageOnRef( imageRaw32 );

  INFO( "Reading file with importRaw" << fileName );
  Image imageRaw = RawReader<Image>::template importRaw< unsigned int >( fileName, extent );
  testImageOnRef( imageRaw );
}

/** Compares an image to a generated data.
 * @tparam  Image  Image type.
 * @param[out]  anImage The image.
 * @param       aSeed   Seed for the generator.
 */
template <
  typename Image
>
void generateRefImage( Image & anImage, typename Image::Value aSeed )
{
  typedef typename Image::Domain  Domain;
  typedef typename Domain::Point  Point;

  const Domain  domain = anImage.domain();
  
  for ( typename Domain::ConstIterator it = domain.begin(), itEnd = domain.end(); it != itEnd; ++it )
    {
      const Point pt = *it;
      const typename Image::Value refValue = aSeed * Linearizer<Domain, RowMajorStorage>::getIndex( pt, domain );
      anImage.setValue( pt, refValue );
    }
}

/** Checks reading a previously writed file.
 * @tparam  N  Dimension of the image.
 * @tparam  T  Value type.
 * @tparam  RawIO Class with writer and reader, templated by the image type.
 * @param   aSeed Seed to generate image values.
 */
template <
  DGtal::Dimension N,
  typename T,
  template<typename> class RawIO
>
void testWriteAndRead( T aSeed )
{
  typedef SpaceND<N> Space;
  typedef HyperRectDomain<Space> Domain;
  typedef typename ImageSelector<Domain, T>::Type Image;
  typedef typename Domain::Point  Point;  

  Point upperPt;
  upperPt[ 0 ] = 8;
  for ( Dimension i = 1; i < N; ++i )
    upperPt[ i ] = upperPt[ i-1 ] * ( i == 1 ? 4 : 2 );

  const Domain domain( Point::diagonal(0), upperPt );
  Image refImage( domain );
  generateRefImage( refImage, aSeed );

  INFO( "Writing image" );
  RawIO<Image>::write( "export-raw-writer.raw", refImage );

  INFO( "Reading image" );
  Image image = RawIO<Image>::read( "export-raw-writer.raw", upperPt + Point::diagonal(1) );

  INFO( "Comparing image values" );
  for ( typename Domain::ConstIterator it = domain.begin(), itEnd = domain.end(); it != itEnd; ++it )
    {
      const Point pt = *it;
      INFO( "At point " << pt );
      REQUIRE( image( pt ) == refImage( pt ) );
    }
}

// Some RawIO classes
template < typename Image >
struct RawIO8
{
  static inline Image read( std::string const& filename, typename Image::Domain::Vector const& extent )
    {
      return DGtal::RawReader<Image>::importRaw8( filename, extent );
    }

  static inline bool write( std::string const& filename, Image const& anImage )
    {
      return DGtal::RawWriter<Image>::exportRaw8( filename, anImage );
    }
};

template < typename Image >
struct RawIO16
{
  static inline Image read( std::string const& filename, typename Image::Domain::Vector const& extent )
    {
      return DGtal::RawReader<Image>::importRaw16( filename, extent );
    }

  static inline bool write( std::string const& filename, Image const& anImage )
    {
      return DGtal::RawWriter<Image>::exportRaw16( filename, anImage );
    }
};

template < typename Image >
struct RawIO32
{
  static inline Image read( std::string const& filename, typename Image::Domain::Vector const& extent )
    {
      return DGtal::RawReader<Image>::importRaw32( filename, extent );
    }

  static inline bool write( std::string const& filename, Image const& anImage )
    {
      return DGtal::RawWriter<Image>::exportRaw32( filename, anImage );
    }
};

template < typename Image >
struct RawIO
{
  static inline Image read( std::string const& filename, typename Image::Domain::Vector const& extent )
    {
      return DGtal::RawReader<Image>::template importRaw< typename Image::Value>( filename, extent );
    }

  static inline bool write( std::string const& filename, Image const& anImage )
    {
      return DGtal::RawWriter<Image>::template exportRaw< typename Image::Value>( filename, anImage );
    }
};

///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Checking RawReader with reference files in 2D", "[reader][2D][raw][raw32][uint32]" )
{
  testRawReaderOnRef<2>();
}

TEST_CASE( "Checking RawReader with reference files in 3D", "[reader][3D][raw][raw32][uint32]" )
{
  testRawReaderOnRef<3>();
}

// Signed and unsigned char
TEST_CASE( "Checking writing & reading uint8 in 2D with generic IO", "[reader][writer][2D][raw][uint8]" )
{
  testWriteAndRead<2, DGtal::uint8_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading uint8 in 2D with 8bits IO", "[reader][writer][2D][raw8][uint8]" )
{
  testWriteAndRead<2, DGtal::uint8_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading int8 in 2D with generic IO", "[reader][writer][2D][raw][int8]" )
{
  testWriteAndRead<2, DGtal::int8_t, RawIO>( 1 );
}

// Signed and unsigned short
TEST_CASE( "Checking writing & reading uint16 in 2D with generic IO", "[reader][writer][2D][raw][uint16]" )
{
  testWriteAndRead<2, DGtal::uint16_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading uint16 in 2D with 16bits IO", "[reader][writer][2D][raw16][uint16]" )
{
  testWriteAndRead<2, DGtal::uint16_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading int16 in 2D with generic IO", "[reader][writer][2D][raw][int16]" )
{
  testWriteAndRead<2, DGtal::int16_t, RawIO>( 1 );
}

// Signed and unsigned int
TEST_CASE( "Checking writing & reading uint32 in 2D with generic IO", "[reader][writer][2D][raw][uint32]" )
{
  testWriteAndRead<2, DGtal::uint32_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading uint32 in 2D with 32bits IO", "[reader][writer][2D][raw32][uint32]" )
{
  testWriteAndRead<2, DGtal::uint32_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading int32 in 2D with generic IO", "[reader][writer][2D][raw][int32]" )
{
  testWriteAndRead<2, DGtal::int32_t, RawIO>( 1 );
}

// Signed and unsigned long int
TEST_CASE( "Checking writing & reading uint64 in 2D with generic IO", "[reader][writer][2D][raw][uint64]" )
{
  testWriteAndRead<2, DGtal::uint64_t, RawIO>( 1 );
}

TEST_CASE( "Checking writing & reading int64 in 2D with generic IO", "[reader][writer][2D][raw][int64]" )
{
  testWriteAndRead<2, DGtal::int64_t, RawIO>( 1 );
}

// Double
TEST_CASE( "Checking writing & reading double in 1D with generic IO", "[reader][writer][1D][raw][double]" )
{
  testWriteAndRead<1, double, RawIO>( 1.23456789 );
}

TEST_CASE( "Checking writing & reading double in 2D with generic IO", "[reader][writer][2D][raw][double]" )
{
  testWriteAndRead<2, double, RawIO>( 1.23456789 );
}

TEST_CASE( "Checking writing & reading double in 3D with generic IO", "[reader][writer][3D][raw][double]" )
{
  testWriteAndRead<3, double, RawIO>( 1.23456789 );
}

