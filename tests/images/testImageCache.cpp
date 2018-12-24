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
 * @file testImageCache.cpp
 * @ingroup Tests
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/23
 *
 * @brief A test file for ImageCache.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageContainerBySTLVector.h"

//#define DEBUG_VERBOSE

#include "DGtal/images/ImageFactoryFromImage.h"
#include "DGtal/images/ImageCache.h"

#include "ConfigTest.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImageCache.
///////////////////////////////////////////////////////////////////////////////
bool testSimple()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing simple ImageCache");
    
    typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;

    VImage image(Z2i::Domain(Z2i::Point(0,0), Z2i::Point(3,3)));
    int i = 1;
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = i++;

    trace.info() << "ORIGINAL image: " << image << endl;

    // 1) ImageFactoryFromImage
    typedef ImageFactoryFromImage<VImage > MyImageFactoryFromImage;
    MyImageFactoryFromImage factImage(image);
    
    typedef MyImageFactoryFromImage::OutputImage OutputImage;
    
    Z2i::Domain domain1(Z2i::Point(0,0), Z2i::Point(1,1));
    OutputImage *image1 = factImage.requestImage(domain1);
    OutputImage::ConstRange r1 = image1->constRange();
    cout << "image1: "; std::copy( r1.begin(), r1.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;
    
    Z2i::Domain domain1b(Z2i::Point(0,0), Z2i::Point(1,2));
    OutputImage *image1b = factImage.requestImage(domain1b);
    OutputImage::ConstRange r1b = image1b->constRange();
    cout << "image1b: "; std::copy( r1b.begin(), r1b.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;
    
    Z2i::Domain domain2(Z2i::Point(2,0), Z2i::Point(3,1));
    OutputImage *image2 = factImage.requestImage(domain2);
    OutputImage::ConstRange r2 = image2->constRange();
    cout << "image2: "; std::copy( r2.begin(), r2.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;
        
    Z2i::Domain domain3(Z2i::Point(0,2), Z2i::Point(1,3));
    OutputImage *image3 = factImage.requestImage(domain3);
    OutputImage::ConstRange r3 = image3->constRange();
    cout << "image3: "; std::copy( r3.begin(), r3.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;
        
    Z2i::Domain domain4(Z2i::Point(2,2), Z2i::Point(3,3));
    OutputImage *image4 = factImage.requestImage(domain4);
    OutputImage::ConstRange r4 = image4->constRange();
    cout << "image4: "; std::copy( r4.begin(), r4.end(), std::ostream_iterator<int>(cout,", ") ); cout << endl;
    
    // 2) ImageCache with DGtal::CACHE_READ_POLICY_LAST, DGtal::CACHE_WRITE_POLICY_WT
    trace.info() << endl << "ImageCache with DGtal::CACHE_READ_POLICY_LAST, DGtal::CACHE_WRITE_POLICY_WT" << endl;
    
    typedef ImageCacheReadPolicyLAST<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyLAST;
    typedef ImageCacheWritePolicyWT<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWT;
    MyImageCacheReadPolicyLAST imageCacheReadPolicyLAST(factImage);
    MyImageCacheWritePolicyWT imageCacheWritePolicyWT(factImage);
    
    typedef ImageCache<OutputImage, MyImageFactoryFromImage, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWT> MyImageCache;
    MyImageCache imageCache(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWT);
    OutputImage::Value aValue;
    
    trace.info() << "READING from cache (empty cache): " << imageCache << endl;
    if (imageCache.read(Z2i::Point(2,2), aValue)) 
      trace.info() << "READ: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "READ: Point 2,2 is not in an image from cache." << endl;
    nbok += (imageCache.read(Z2i::Point(2,2), aValue) == false) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache.update(domain1); // image1
    
    trace.info() << "READING from cache (not empty but wrong domain): " << imageCache << endl;
    if (imageCache.read(Z2i::Point(2,2), aValue)) 
      trace.info() << "READ: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "READ: Point 2,2 is not in an image from cache." << endl;
    nbok += (imageCache.read(Z2i::Point(2,2), aValue) == false) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache.update(domain4); // image4
    
    trace.info() << "READING from cache (not empty but good domain): " << imageCache << endl;
    if (imageCache.read(Z2i::Point(2,2), aValue)) 
      trace.info() << "READ: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "READ: Point 2,2 is not in an image from cache." << endl; 
    nbok += ( (imageCache.read(Z2i::Point(2,2), aValue) && (aValue == 11)) == true ) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    trace.info() << "WRITING from cache (not empty but good domain): " << imageCache << endl;
    aValue = 22;
    if (imageCache.write(Z2i::Point(2,2), aValue)) 
      trace.info() << "WRITE: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "WRITE: Point 2,2 is not in an image from cache." << endl; 
    nbok += ( (imageCache.read(Z2i::Point(2,2), aValue) && (aValue == 22)) == true ) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    trace.info() << "  AFTER WRITING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 22) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache.update(domain3); // image3
    
    trace.info() << "WRITING from cache (not empty but wrong domain): " << imageCache << endl;
    aValue = 22;
    if (imageCache.write(Z2i::Point(2,2), aValue)) 
      trace.info() << "WRITE: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "WRITE: Point 2,2 is not in an image from cache." << endl; 
    nbok += (imageCache.read(Z2i::Point(2,2), aValue) == false) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;

    imageCache.update(domain1); // image1
    
    trace.info() << "WRITING from cache (not empty but good domain): " << imageCache << endl;
    aValue = 7;
    if (imageCache.write(Z2i::Point(0,0), aValue)) 
      trace.info() << "WRITE: Point 0,0 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "WRITE: Point 0,0 is not in an image from cache." << endl; 
    nbok += ( (imageCache.read(Z2i::Point(0,0), aValue) && (aValue == 7)) == true ) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    trace.info() << "  AFTER WRITING: Point 0,0 on ORIGINAL image, value: " << image(Z2i::Point(0,0)) << endl;
    nbok += (image(Z2i::Point(0,0)) == 7) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    // 3) ImageCache with DGtal::CACHE_READ_POLICY_LAST, DGtal::CACHE_WRITE_POLICY_WB
    i = 1; // reinit image
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = i++;
    
    trace.info() << endl << "ImageCache with DGtal::CACHE_READ_POLICY_LAST, DGtal::CACHE_WRITE_POLICY_WB" << endl;
    
    typedef ImageCacheWritePolicyWB<OutputImage, MyImageFactoryFromImage> MyImageCacheWritePolicyWB;
    MyImageCacheWritePolicyWB imageCacheWritePolicyWB(factImage);
    
    typedef ImageCache<OutputImage, MyImageFactoryFromImage, MyImageCacheReadPolicyLAST, MyImageCacheWritePolicyWB > MyImageCache2;
    MyImageCache2 imageCache2(factImage, imageCacheReadPolicyLAST, imageCacheWritePolicyWB);
    
    imageCache2.update(domain4); // image4
    
    trace.info() << "WRITING from cache (not empty but good domain): " << imageCache2 << endl;
    aValue = 22;
    if (imageCache2.write(Z2i::Point(2,2), aValue)) 
      trace.info() << "WRITE: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "WRITE: Point 2,2 is not in an image from cache." << endl; 
    nbok += ( (imageCache2.read(Z2i::Point(2,2), aValue) && (aValue == 22)) == true ) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    trace.info() << "  AFTER WRITING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 11) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache2.update(domain3); // image3 - so flush domain4 (image4)
    
    trace.info() << "  AFTER FLUSHING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 22) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    // 4) ImageCache with DGtal::CACHE_READ_POLICY_FIFO, DGtal::CACHE_WRITE_POLICY_WB
    i = 1; // reinit image
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = i++;
    
    trace.info() << endl << "ImageCache with DGtal::CACHE_READ_POLICY_FIFO, DGtal::CACHE_WRITE_POLICY_WB" << endl;
    
    typedef ImageCacheReadPolicyFIFO<OutputImage, MyImageFactoryFromImage> MyImageCacheReadPolicyFIFO;
    MyImageCacheReadPolicyFIFO imageCacheReadPolicyFIFO(factImage, 3);
    
    typedef ImageCache<OutputImage, MyImageFactoryFromImage, MyImageCacheReadPolicyFIFO, MyImageCacheWritePolicyWB > MyImageCache3;
    MyImageCache3 imageCache3(factImage, imageCacheReadPolicyFIFO, imageCacheWritePolicyWB);
    
    imageCache3.update(domain4); // image4
    
    trace.info() << "WRITING from cache (not empty but good domain): " << imageCache3 << endl;
    aValue = 22;
    if (imageCache3.write(Z2i::Point(2,2), aValue)) 
      trace.info() << "WRITE: Point 2,2 is in an image from cache, value: " << aValue << endl;
    else
      trace.info() << "WRITE: Point 2,2 is not in an image from cache." << endl; 
    nbok += ( (imageCache3.read(Z2i::Point(2,2), aValue) && (aValue == 22)) == true ) ? 1 : 0; 
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    trace.info() << "  AFTER WRITING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 11) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache3.update(domain3); // image3
    
    trace.info() << "  AFTER FLUSHING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 11) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache3.update(domain2); // image2
    
    trace.info() << "  AFTER FLUSHING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 11) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    imageCache3.update(domain1); // image1 - so flush domain4 (image4)
    
    trace.info() << "  AFTER FLUSHING: Point 2,2 on ORIGINAL image, value: " << image(Z2i::Point(2,2)) << endl;
    nbok += (image(Z2i::Point(2,2)) == 22) ? 1 : 0;
    nb++;
    
    trace.info() << "(" << nbok << "/" << nb << ") " << endl;
    
    trace.endBlock();
    
    return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
    trace.beginBlock ( "Testing class ImageCache" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    bool res = testSimple(); // && ... other tests

    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
