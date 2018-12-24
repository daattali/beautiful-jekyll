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
 * @file testCompressedVolWriter.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2016/12/26
 *
 * Functions for testing class CompressedVolWriter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/writers/LongvolWriter.h"
#include "DGtal/io/readers/LongvolReader.h"
#include "DGtal/io/writers/VolWriter.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class CompressedVolWriter.
///////////////////////////////////////////////////////////////////////////////

template <typename Image>
bool checkImage(const Image &a, const Image &b)
{
  for(auto p: a.domain())
  {
    if (a(p) != b(p))
    {
      trace.info()<< p <<" "<< a(p) <<" "<<b(p)<<std::endl;
      return false;
    }
  }
  return true;
}

TEST_CASE( "Testing CompressedVolWriter" )
{
  Domain domain(Point(0,0,0), Point(10,10,10));
  typedef ImageContainerBySTLVector<Domain, unsigned char> Image;
  Image image(domain);
  image.setValue(Point(5,5,5), 42);
  
  SECTION("Testing API of CompressedVol")
  {
    VolWriter< ImageContainerBySTLVector<Domain, unsigned char> >::exportVol("test.vol", image, false);
    VolWriter< ImageContainerBySTLVector<Domain, unsigned char> >::exportVol("testz.vol", image);
    REQUIRE( image.isValid() );
  }
  
  SECTION("Testing write/read of CompressedVolWriter")
  {
    Image read = VolReader<Image>::importVol("test.vol");
    REQUIRE( (checkImage(image,read) == true)) ;
    
    Image readz = VolReader<Image>::importVol("testz.vol");
    REQUIRE( (checkImage(image,readz) == true)) ;
  }
}

TEST_CASE( "Testing CompressedLongvol" )
{
  Domain domain(Point(0,0,0), Point(2,2,2));
  typedef ImageContainerBySTLVector<Domain, DGtal::uint64_t> Image;
  Image image(domain);
  image.setValue(Point(1,1,1), 4222222);
  
  SECTION("Testing API of CompressedVolWriter")
    {
      LongvolWriter< ImageContainerBySTLVector<Domain, DGtal::uint64_t> >::exportLongvol("test.lvol", image, false);
      trace.info()<<std::endl;
      LongvolWriter< ImageContainerBySTLVector<Domain, DGtal::uint64_t> >::exportLongvol("testz.lvol", image);
      REQUIRE( image.isValid() );
    }
  
  SECTION("Testing write/read of CompressedVolWriter")
    {
      Image read = LongvolReader<Image>::importLongvol("test.lvol");
      REQUIRE( (checkImage(image,read) == true)) ;
 
      Image readz = LongvolReader<Image>::importLongvol("testz.lvol");
      REQUIRE( (checkImage(image,readz) == true)) ;
    }
}

/** @ingroup Tests **/
