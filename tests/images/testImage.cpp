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
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 *
 * @date 2010/05/25
 *
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/13
 *
 * This file is part of the DGtal library
 */



#include <cstdio>
#include <cmath>
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ImageContainerByHashTree.h"
#include "DGtal/images/Image.h"


using namespace DGtal;
using namespace std;


/**
 * Image tests.
 *
 **/
template<typename Image>
bool testImage(const Image& aImage)
{

    BOOST_CONCEPT_ASSERT(( concepts::CImage<Image> ));

    int nb = 0;
    int nbok = 0;

    ////////////////////////////////////////////////
    trace.beginBlock ( "Main services, range" );

    Image img(aImage);
    Image img2 = img; //copy

    //fill
    typename Image::Domain::ConstIterator dit = img.domain().begin();
    typename Image::Domain::ConstIterator ditEnd = img.domain().end();
    for (int i = 0; ( (dit != ditEnd)&&(i < 5) ); ++dit, ++i)
    {
        img.setValue(*dit, i);
    }
    Image img3(img2);
    img3 = img; //assignment

    //ranges comparison
    typename Image::ConstRange rimg = img.constRange();
    typename Image::ConstRange rimg2 = img2.constRange();
    typename Image::ConstRange rimg3 = img3.constRange();

    bool flag2 = std::equal(rimg.begin(), rimg.end(), rimg2.begin());
    bool flag3 = std::equal(rimg.begin(), rimg.end(), rimg3.begin());
    bool flag23 = std::equal(rimg2.begin(), rimg2.end(), rimg3.begin());

    nbok += ( (!flag2) && flag3 && (!flag23) )?1:0;
    nb++;
    trace.info() << "(" <<nbok << "/" << nb << ")" << std::endl;
    trace.endBlock();

    ////////////////////////////////////////////////
    trace.beginBlock ( "Output iterator" );
    std::copy(rimg.begin(), rimg.end(), img2.range().outputIterator());

    //rimg2 is invalid if Image is a proxy image
    //because its iterators point to the data of aImage
    //instead of pointing to the data of img2
    rimg2 = img2.constRange();
    flag2 = std::equal(rimg.begin(), rimg.end(), rimg2.begin());
    nbok += (flag2)?1:0;
    nb++;
    trace.info() << "(" <<nbok << "/" << nb << ")" << std::endl;
    trace.endBlock();

    ////////////////////////////////////////////////
    trace.beginBlock ( " Getters / setters " );
    typename Image::Domain::Point p = img.domain().upperBound();

    //local comparison
    img.setValue( p, 128 );
    bool flag4 = ( img(p) == 128 );

    //range comparison
    rimg = img.constRange();
    rimg2 = img2.constRange();
    rimg3 = img3.constRange();
    std::copy( rimg.begin(), rimg.end(), std::ostream_iterator<int>(cout,", ") );
    cout << endl;
    flag2 = std::equal(rimg.begin(), rimg.end(), rimg2.begin());
    std::copy( rimg2.begin(), rimg2.end(), std::ostream_iterator<int>(cout,", ") );
    cout << endl;
    flag3 = std::equal(rimg.begin(), rimg.end(), rimg3.begin());
    std::copy( rimg3.begin(), rimg3.end(), std::ostream_iterator<int>(cout,", ") );
    cout << endl;

    nbok += ( flag4 && (!flag2) && (!flag3) )?1:0;
    nb++;
    trace.info() << "(" <<nbok << "/" << nb << ")" << std::endl;
    trace.endBlock();

    ////////////////////////////////////////////////
    trace.beginBlock ( " Display " );
    trace.info() << img << std::endl;
    trace.info() << img2 << std::endl;
    trace.info() << img3 << std::endl;
    trace.endBlock();

    return ( img.isValid() && img2.isValid() && img3.isValid() && (nbok == nb) );
}

int main( int argc, char** argv )
{

    trace.beginBlock ( "Testing image classes" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    /// domain
    typedef DGtal::int64_t Integer;
    typedef SpaceND<2,Integer> Space;
    typedef Space::Point Point;
    typedef HyperRectDomain<Space> Domain;

    const Integer size = 5;
    Point p = Point::diagonal(0);
    Point q = Point::diagonal(size-1);
    Domain d(p,q);

    /// image types
    typedef short Value;
    typedef ImageContainerBySTLVector<Domain,Value> VImage;
    typedef ImageContainerBySTLMap<Domain,Value> MImage;
    // TODO typedef experimental::ImageContainerByHashTree<Domain,Value> HImage;
    // TODO typedef Image<VImage > LImage;

    /// tests
    VImage vi(d);
    bool res = testImage(vi);

    MImage mi(d);
    res = res && testImage(mi);

    // TODO
    // HImage hi(3, p, q, 0);
    // res = res && testImage(hi);

    // LImage li( new VImage(d) );
    // res = res && testImage(li);

    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    return res ? 0 : 1;
}

