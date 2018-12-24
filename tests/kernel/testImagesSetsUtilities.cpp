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
 * @file testImagesSetsUtilities.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/26
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/15
 *
 * Functions for testing ImageHelper functions.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/images/imagesSetsUtils/ImageFromSet.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"

#include "DGtal/kernel/sets/DigitalSetInserter.h"
#include "DGtal/images/ImageHelper.h"

#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageSelector.h"

#include "DGtal/helpers/StdDefs.h"

#include "ConfigTest.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing ImageHelper functions.
///////////////////////////////////////////////////////////////////////////////

template <typename P>
struct Norm1
{
  typedef P Point;
  typedef typename P::Coordinate Value;

  Value operator()(const Point& p)
  {
    return p.norm1();
  }
};

/**
 * Example of a test. To be completed.
 *
 */
bool testImageFromSet()
{

  typedef ImageContainerBySTLVector<Domain,int> Image;

  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing ImageFromSet ..." );

  Point a(0,0);
  Point b(23,435);
  Point c(12,12);

  Domain d(a,b);
  DigitalSet aSet(d);
  aSet.insert(c);

  Image image(d);
  //assign to the points belonging to aSet the value 128
  imageFromRangeAndValue(aSet, image, 128);
  //ie. the value of c is 128 but the value of a remains 0
  nbok += ( (image(c) == 128)&&(image(a) == 0) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  Image image2(d);
  Norm1<Point> n;
  //fill image2 from n
  imageFromFunctor(image2, n);
  nbok += ( (image2(c) == (int)c.norm1())
	    &&(image2(a) == (int)a.norm1())
	    &&(image2(b) == (int)b.norm1()) )? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  Image image3 = image;
  //fill image3 from image2
  imageFromImage(image3, const_cast<Image const&>(image2));
  //image2 and image3 should be equal,
  //but both different from image
  Image::ConstRange rimg = image.constRange();
  Image::ConstRange rimg2 = image2.constRange();
  Image::ConstRange rimg3 = image3.constRange();
  bool flag2 = std::equal(rimg.begin(), rimg.end(), rimg2.begin());
  bool flag3 = std::equal(rimg.begin(), rimg.end(), rimg3.begin());
  bool flag23 = std::equal(rimg2.begin(), rimg2.end(), rimg3.begin());
  nbok += ( (!flag2) && (!flag3) && flag23 )?1:0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  trace.endBlock();

  return nbok == nb;
}

bool testSetFromImage()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing SetFromImage ..." );

  //some points
  Point a(0,0);
  Point b(3,3);
  Point p(1,1);
  Point q(2,2);
  Point r(1,2);

  //image construction
  typedef ImageContainerBySTLMap<Domain,int> Image;
  Domain d(a,b);
  Image image(d,1);
  image.setValue(p,127);
  image.setValue(q,128);
  image.setValue(r,10);

  //image content
  Image::ConstRange range = image.constRange();
  std::copy(range.begin(), range.end(), ostream_iterator<Image::Value>(cout, " ") );
  cout << endl;

  //set tests

  DigitalSet aSet(d);
  DigitalSetInserter<DigitalSet> inserter(aSet);
  //all points whose value <= 126
  setFromImage( image, inserter, 126 );
  //ie, all points except p and q
  nbok += ( (aSet.find(p) == aSet.end())
	    &&(aSet.find(q) == aSet.end())
	    &&(aSet.size()==(d.size()-2)) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  DigitalSet aSet2(d);
  DigitalSetInserter<DigitalSet> inserter2(aSet2);
  //all points whose value <= 127
  setFromImage( image, inserter2, 127 );
  //ie, all points except q
  nbok += ( (aSet2.find(q) == aSet2.end())
	    &&(aSet2.size()==(d.size()-1)) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  DigitalSet aSet3(d);
  DigitalSetInserter<DigitalSet> inserter3(aSet3);
  //all points whose value <= 128
  setFromImage( image, inserter3, 128 );
  //ie, all points
  nbok += ( aSet3.size()==d.size() ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  DigitalSet aSet4(d);
  DigitalSetInserter<DigitalSet> inserter4(aSet4);
  //all points whose value is between 2 and 100
  setFromImage( image, inserter4, 2, 100 );
  //ie, only point r
  nbok += ( (aSet4.find(r)!=aSet4.end())&&(aSet4.size()==1) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;

  DigitalSet aSet5(d);
  DigitalSetInserter<DigitalSet> inserter5(aSet5);
  //predicate construction
  using ValuePredicate = std::function<bool(const Image::Value &)>;
  ValuePredicate equalTo1 = [](const Image::Value & v)
    {
      return v == 1;
    };
  functors::PointFunctorPredicate<Image, ValuePredicate> pred(image, equalTo1);
  //all points whose value is 1
  setFromPointsRangeAndPredicate( d.begin(), d.end(), inserter5, pred );
  //ie all points except p, q, and r
  nbok += ( (aSet5.find(p) == aSet5.end())
	    &&(aSet5.find(q) == aSet5.end())
	    &&(aSet5.find(r) == aSet5.end())
	    &&(aSet5.size()==(d.size()-3)) ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") " << std::endl;


  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ImageHelper functions" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testImageFromSet() && testSetFromImage();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
