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
 * @file testTiledImage.cpp
 * @ingroup Tests
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/23
 *
 * @brief A test file for TiledImage.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"

#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageFactoryFromImage.h"
#include "DGtal/images/TiledImage.h"

#include "ConfigTest.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class TiledImage.
///////////////////////////////////////////////////////////////////////////////
bool testSimple()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing simple TiledImage");

    typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
    VImage image(Z2i::Domain(Z2i::Point(1,1), Z2i::Point(16,16)));

    int i = 1;
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = i++;

    trace.info() << "ORIGINAL image: " << image << endl;

    typedef ImageFactoryFromImage<VImage> MyImageFactoryFromImage;
    typedef MyImageFactoryFromImage::OutputImage OutputImage;
    MyImageFactoryFromImage imageFactoryFromImage(image);

    typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
    typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
    MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(imageFactoryFromImage, 2);
    MyImageCacheWritePolicyWT imageCacheWritePolicyWT(imageFactoryFromImage);

    typedef TiledImage<VImage, MyImageFactoryFromImage, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImage;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
    MyTiledImage tiledImage(imageFactoryFromImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWT, 4);

    typedef MyTiledImage::OutputImage OutputImage;
    OutputImage::Value aValue;

    trace.info() << "Read value for Point 4,2: " << tiledImage(Z2i::Point(4,2)) << endl;
    nbok += (tiledImage(Z2i::Point(4,2)) == 20) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 10,6: " << tiledImage(Z2i::Point(10,6)) << endl;
    nbok += (tiledImage(Z2i::Point(10,6)) == 90) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    aValue = 1; tiledImage.setValue(Z2i::Point(11,7), aValue);
    trace.info() << "Write value for Point 11,7: " << aValue << endl;
    nbok += (tiledImage(Z2i::Point(11,7)) == 1) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 2,3: " << tiledImage(Z2i::Point(2,3)) << endl;
    nbok += (tiledImage(Z2i::Point(2,3)) == 34) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 16,1: " << tiledImage(Z2i::Point(16,1)) << endl;
    nbok += (tiledImage(Z2i::Point(16,1)) == 16) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    aValue = 128; tiledImage.setValue(Z2i::Point(16,1), aValue);
    trace.info() << "Write value for Point 16,1: " << aValue << endl;
    nbok += (tiledImage(Z2i::Point(16,1)) == 128) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "  Point 16,1 on ORIGINAL image, value: " << image(Z2i::Point(16,1)) << endl;
    nbok += (image(Z2i::Point(16,1)) == 128) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.endBlock();

    return nbok == nb;
}

bool test3d()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing 3d TiledImage");

    typedef ImageContainerBySTLVector<Z3i::Domain, int> VImage;
    VImage image(Z3i::Domain(Z3i::Point(1,1,1), Z3i::Point(4,4,4)));

    int i = 1;
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = i++;

    trace.info() << "ORIGINAL image: " << image << endl;

    typedef ImageFactoryFromImage<VImage> MyImageFactoryFromImage;
    typedef MyImageFactoryFromImage::OutputImage OutputImage;
    MyImageFactoryFromImage imageFactoryFromImage(image);

    typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
    typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
    MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(imageFactoryFromImage, 2);
    MyImageCacheWritePolicyWT imageCacheWritePolicyWT(imageFactoryFromImage);

    typedef TiledImage<VImage, MyImageFactoryFromImage, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImage;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
    MyTiledImage tiledImage(imageFactoryFromImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWT, 4);

    typedef MyTiledImage::OutputImage OutputImage;

    trace.info() << "Read value for Point 1,1,1: " << tiledImage(Z3i::Point(1,1,1)) << endl;
    nbok += (tiledImage(Z3i::Point(1,1,1)) == 1) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 4,4,4: " << tiledImage(Z3i::Point(4,4,4)) << endl;
    nbok += (tiledImage(Z3i::Point(4,4,4)) == 64) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.info() << "Read value for Point 4,3,2: " << tiledImage(Z3i::Point(4,3,2)) << endl;
    nbok += (tiledImage(Z3i::Point(4,3,2)) == 28) ? 1 : 0;
    nb++;

    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    trace.endBlock();

    return nbok == nb;
}

bool testIterators()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock("Testing iterators with TiledImage");

  typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
  VImage image(Z2i::Domain(Z2i::Point(1,1), Z2i::Point(10,10)));
  for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
    *it = 10;
  trace.info() << "ORIGINAL image: " << image << endl;
  typedef ImageFactoryFromImage<VImage> MyImageFactoryFromImage;
  typedef MyImageFactoryFromImage::OutputImage OutputImage;
  MyImageFactoryFromImage imageFactoryFromImage(image);

  typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
  typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
  MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(imageFactoryFromImage, 2);
  MyImageCacheWritePolicyWT imageCacheWritePolicyWT(imageFactoryFromImage);

  typedef TiledImage<VImage, MyImageFactoryFromImage, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWT> MyTiledImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
  MyTiledImage tiledImage(imageFactoryFromImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWT, 4);

  tiledImage.setValue( Z2i::Point(5,5), 42 );
  tiledImage.setValue( Z2i::Point(1,1), 1 );

  // typedefs
  typedef MyTiledImage::ConstIterator ConstIterator;
  typedef MyTiledImage::OutputIterator OutputIterator;

  ConstIterator itbegin = tiledImage.constRange().begin();
  trace.info() << "Value at range begin (1) = "<< *itbegin << std::endl;
  nbok += (*itbegin == 1) ? 1 : 0; nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  ConstIterator itbegin2 = tiledImage.constRange().begin(Z2i::Point(5,5));
  trace.info() << "Value at range begin from point (42) = "<< *itbegin2 << std::endl;
  nbok += (*itbegin2 == 42) ? 1 : 0; nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  OutputIterator itbegino = tiledImage.range().begin();
  trace.info() << "Value at range begin (1) = "<< *itbegino << std::endl;
  nbok += (*itbegino == 1) ? 1 : 0; nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  *itbegino = 5;
  trace.info() << "Value at range begin after writing (5) = "<< *itbegino << std::endl;
  nbok += (*itbegino == 5) ? 1 : 0; nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();
  
  return nbok == nb;
}

bool test_range_constRange()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing range/constRange with TiledImage");

    typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;

    VImage image(Z2i::Domain(Z2i::Point(1,1), Z2i::Point(10,10)));
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = 10;

    trace.info() << "ORIGINAL image: " << image << endl;

    typedef ImageFactoryFromImage<VImage> MyImageFactoryFromImage;
    typedef MyImageFactoryFromImage::OutputImage OutputImage;
    MyImageFactoryFromImage imageFactoryFromImage(image);

    typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
    //typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
    typedef ImageCacheWritePolicyWB<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWB;
    MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(imageFactoryFromImage, 2);
    //MyImageCacheWritePolicyWT imageCacheWritePolicyWT(imageFactoryFromImage);
    MyImageCacheWritePolicyWB imageCacheWritePolicyWB(imageFactoryFromImage);

    typedef TiledImage<VImage, MyImageFactoryFromImage, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWB> MyTiledImage;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyTiledImage > ));
    MyTiledImage tiledImage(imageFactoryFromImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWB, 4);

    // writing values
    const int maximalValue = tiledImage.domain().size();
    MyTiledImage::Range::OutputIterator it = tiledImage.range().outputIterator();
    for (int i = 0; i < maximalValue; ++i)
    {
      *it++ = i;
    }

    // reading values
    MyTiledImage::ConstRange r = tiledImage.constRange();
    std::copy( r.begin(), r.end(), std::ostream_iterator<int>(cout,", ") );
    cout << endl;

    std::vector<int> to_vector(100);
    std::copy(r.begin(), r.end(), to_vector.begin());
    for (int i = 0; i < 100; i++)
    {
      if (to_vector[i]==i)
      {
        cout << "ok, ";
        nbok += 1;
        nb++;
      }
      else
      {
        cout << "!ok -> " << to_vector[i] << ", "; 
        nb++;
      }
    }
    cout << endl;
    
    cout << endl;
    
    // reading values
    std::copy( r.begin(Z2i::Point(7,7)), r.end(), std::ostream_iterator<int>(cout,", ") );
    cout << endl;

    std::vector<int> to_vector2(28);
    std::copy(r.begin(Z2i::Point(7,7)), r.end(), to_vector2.begin());
    for (int i = 0; i < 28; i++)
    {
      if (to_vector2[i]==i+72)
      {
        cout << "ok, ";
        nbok += 1 ;
        nb++;
      }
      else
      {
        cout << "!ok -> " << to_vector2[i] << ", "; 
        nb++;
      }
    }
    cout << endl;

    trace.endBlock();

    return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
    trace.beginBlock ( "Testing class TiledImage" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    bool res = testSimple() && test3d() && testIterators() && test_range_constRange(); // && ... other tests

    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
