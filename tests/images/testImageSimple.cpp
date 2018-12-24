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
 * @file testImageSimple.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/07
 *
 * Functions for testing class ImageSimple.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/Image.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImageSimple.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testSelfCheckConcept()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Boost concept ..." );
  typedef Image<ImageContainerBySTLVector<Z2i::Domain, int> > MyImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage > ));

  nbok += true ? 1 : 0;


  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}


bool testCreate()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Image Create ..." );
  typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
  typedef Image<VImage > MyImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage > ));

  Z2i::Point a(0,0);
  Z2i::Point b(128,128);
  Z2i::Domain domain(a,b);
  MyImage image( new VImage(domain) );

  trace.info()<<image<<std::endl;
  trace.info()<<*image.getPointer()<<std::endl;

  nbok += image.isValid() ? 1 : 0;
  nb++;

  typedef HyperRectDomain<SpaceND <6> > Domain6;
  typedef ImageContainerBySTLVector<Domain6, int> VImage6;
  typedef Image<VImage6 > MyImage6;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage6 > ));

  Z2i::Integer aa[] = {0,0,0,0,0,0};
  Z2i::Integer bb[] = {2,2,2,2,2,2};
  Domain6::Point A(aa);
  Domain6::Point B(bb);

  MyImage6 imageBis( new VImage6( Domain6(A,B) ) );
  trace.warning() << "Dimension 6 image"<<std::endl;
  trace.info()<< imageBis <<std::endl;

  nbok += imageBis.isValid() ? 1 : 0;
  nb++;


  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

bool testAPI()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Image API ..." );
  typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
  typedef Image<VImage > MyImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage > ));

  Z2i::Point a(0,0);
  Z2i::Point b(32,32);
  Z2i::Point c(12, 14);

  Z2i::Domain domain(a,b);
  MyImage image( new VImage(domain) );

  trace.info()<<image<<std::endl;


  nbok += image.isValid() ? 1 : 0;
  nb++;

  image.setValue(c, 42);
  trace.info()<< "Value at "<<c<<"  = "<< image(c)<<std::endl;

  trace.warning() << "Image Iterate"<<std::endl;
  trace.info()<<std::endl;
  MyImage::ConstRange r = image.constRange();
  for(MyImage::ConstRange::ConstIterator it =r.begin(), ite=r.end();
      it != ite; ++it)
    std::cerr << (*it)<<" ";

  trace.info()<<std::endl;

  nbok += (image(c) == 42) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

bool testImageCopy()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing copy of Image..." );
  typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
  typedef Image<VImage > MyImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage > ));

  Z2i::Point a(0,0);
  Z2i::Point b(32,32);
  Z2i::Point c(12, 14);

  Z2i::Domain domain(a,b);
  MyImage image( new VImage(domain) );

  trace.info()<<image<<std::endl;

  nbok += image.isValid() ? 1 : 0;
  nb++;

  //Image pointer
  VImage  * imContainer =
    new VImage(domain);

  //Image through smart pointer
  //(that takes ownership and must free the memory)
  MyImage image2(imContainer);

  const MyImage::ImagePointer p = image2.getPointer();
  trace.info() << p << std::endl;
  trace.info() << *p << std::endl;

  nbok += (image2.isValid()) ? 1 : 0;
  nb++;

  trace.info() << p.get() << std::endl;
  trace.info() << imContainer << std::endl;
  nbok += (p.get() == imContainer) ? 1 : 0;
  nb++;

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;

  trace.endBlock();

  return nbok == nb;
}
bool testImageCopyShort()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing smart copy of Image..." );
  typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
  typedef Image<VImage > MyImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage > ));

  Z2i::Point a(0,0);
  Z2i::Point b(32,32);
  Z2i::Point c(12, 14);

  Z2i::Domain domain(a,b);

  MyImage image(  new VImage(domain) );
  trace.info() << "Image constructed: "<< image <<std::endl;

  VImage myImageC( domain );
  MyImage imageFromConstRef ( myImageC );
  trace.info() << "Image constructed (from constRef): "<< imageFromConstRef <<std::endl;
  nbok += (imageFromConstRef.getPointer().count()== 2) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "unique" << std::endl;

  MyImage image3;
  trace.info() << "Image constructed (degulat): "<< image3 <<std::endl;


  trace.info() <<  "default: "<< image3 <<std::endl;
  image3 = image;
  nbok += (image3.getPointer().count()== 3) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;
  trace.info() <<  "assignment: "<< image3 <<std::endl;
  nbok += (image3.getPointer().count()== 3) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
        << "true == true" << std::endl;

  image3.setValue(Z2i::Point(1,1), 4);
  trace.info() <<  "setValue on assigned: "<< image3 <<std::endl;
  nbok += (image3.getPointer().count()== 2) ? 1 : 0;
  nb++;

  MyImage image4(image3);
  trace.info() << "Image constructed (copy): "<< image4 <<std::endl;
  nbok += (image4.getPointer().count()== 3) ? 1 : 0;
  nb++;


  trace.info() << "(" << nbok << "/" << nb << ") "
         << "true == true" << std::endl;

  return nbok == nb;
}

bool testImageScan()
{
    unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Image scan ..." );
  typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;
  typedef Image<VImage > MyImage;
  BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImage > ));

  Z2i::Point a(0,0);
  Z2i::Point b(32,32);
  Z2i::Point c(12, 14);

  Z2i::Domain domain(a,b);
  MyImage image( new VImage(domain) );

  typedef MyImage::Range::Iterator Iterator;
  typedef MyImage::Domain::ConstIterator DomainConstIterator;

  //Setting values iterating on the domain points
  for(Iterator it = image.range().begin(), itend = image.range().end();
      it != itend; ++it)
    *it =  42 ; // (*it) is a container cell


  //Fast init of the image using container built-in iterator
  for(DomainConstIterator it = image.domain().begin(), itend = image.domain().end();
      it != itend; ++it)
      image.setValue( *it , 42 );  // (*it) is a Point


   return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ImageSimple" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testSelfCheckConcept()
    && testCreate()
    && testAPI()
    && testImageCopy() && testImageScan()
    && testImageCopyShort();// && ... other tests

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
