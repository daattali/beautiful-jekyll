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
 * @file testImageAdapter.cpp
 * @ingroup Tests
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/12
 *
 * Functions for testing class ImageAdapter.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageContainerBySTLVector.h"

//#define DEBUG_VERBOSE

#include "DGtal/images/ImageAdapter.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/boards/Board2D.h"

#include "ConfigTest.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImageAdapter.
///////////////////////////////////////////////////////////////////////////////
bool testSimple()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing simple ImageAdapter");
    
    typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;

    VImage image(Z2i::Domain(Z2i::Point(0,0), Z2i::Point(10,10)));
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = 10;

    trace.info() << "Original image: " << image << endl;

    Z2i::Domain domain(Z2i::Point(2,2), Z2i::Point(4,4));
    typedef ImageAdapter<VImage, Z2i::Domain, functors::Identity, VImage::Value, functors::Identity, functors::Identity > MyImageAdapter;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImageAdapter > ));
    
    functors::Identity idD;
    functors::Identity idV;
    functors::Identity idVm1;
    
    MyImageAdapter restimage(image, domain, idD, idV, idVm1);
    trace.info() << "Restricted Image: " << restimage << "  " << restimage.domain() << std::endl;

    nbok += (restimage(Z2i::Point(3,3)) == 10) ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " read access on restricted Image" << endl;

    restimage.setValue(Z2i::Point(3,3), 5);
    nbok += (restimage(Z2i::Point(3,3)) == 5) ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " write on restricted Image"  << endl;

    nbok += (image(Z2i::Point(3,3)) == 5) ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " written on original image" << endl;

    trace.warning()<< "Original image at (3,3) = "<< (image)(Z2i::Point(3,3)) << std::endl;
    
    trace.endBlock();
    
    return nbok == nb;
}

  /**
   * Description of template class 'MyTransValueFunctor' <p>
   * \brief Aim: Define a simple functor that returns 
   * a 'trans' value. 
   *
   * @tparam TValue type of the value
   */
  template <typename TValue>
  class MyTransValueFunctor
  {
  public:
    typedef TValue Value;

    /** 
     * Constructor.
     * @param aValue the 'trans' value.
     */
    MyTransValueFunctor(const Value& aValue = 0)
      :myValue(aValue) {};
    
    /** 
     * Operator
     *
     * @tparam TInput type of the input object
     * @param aInput input object
     *
     * @return the constant value.
     */
    template <typename TInput>
    inline
    Value operator()(const TInput& aInput) const
    {
      return aInput+myValue;
    }

  private:
    /** 
     * value
     */
    Value myValue;
    
  };
  
bool test_g_f_fm1()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing g, f and fm1 with ImageAdapter");
    
    typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;

    VImage image(Z2i::Domain(Z2i::Point(0,0), Z2i::Point(10,10)));
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = 10;

    trace.info() << "Original image: " << image << endl;

    //ConstAdapter
    Z2i::Domain domain(Z2i::Point(2,2), Z2i::Point(4,4));
    typedef ConstImageAdapter<VImage, Z2i::Domain, functors::Identity, VImage::Value, DGtal::functors::ConstValue<VImage::Value> > MyImageAdapter;
    BOOST_CONCEPT_ASSERT(( concepts::CConstImage< MyImageAdapter > ));
    functors::Identity idD;
    DGtal::functors::ConstValue<VImage::Value> idV(3);
    MyImageAdapter restimage(image, domain, idD, idV);
    trace.info() << "Restricted Image: " << restimage << "  " << restimage.domain() << std::endl;
    nbok += (restimage(Z2i::Point(3,3)) == 3) ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " read access on restricted Image" << endl;
    
    //! [ImageAdapterConstruction]
  typedef ImageAdapter<VImage, Z2i::Domain, functors::Identity, bool, functors::Thresholder<VImage::Value>, functors::Cast<VImage::Value>  > MyImageAdapter2;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImageAdapter2 > ));
    
    functors::Identity idD_2;
    DGtal::functors::Thresholder<VImage::Value>  idV_2(4);
    functors::Cast<VImage::Value>  idVm1_2;
    
    MyImageAdapter2 restimage2(image, domain, idD_2, idV_2, idVm1_2);
    //! [ImageAdapterConstruction]

    restimage2.setValue(Z2i::Point(2,2), true);
    nbok += (restimage2(Z2i::Point(2,2)) == true) ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " write on restricted Image 2"  << endl;
    
    trace.warning()<< "Restricted image 2 at (2,2) = "<< (int)(restimage2)(Z2i::Point(2,2)) << std::endl;
    trace.warning()<< "Original image at (2,2) = "<< (image)(Z2i::Point(2,2)) << std::endl;
    trace.warning()<< "Original image at (3,3) = "<< (image)(Z2i::Point(3,3)) << std::endl;
    
    restimage2.setValue(Z2i::Point(2,2), false);
    trace.warning()<< "Restricted image with false at (2,2) = "<< (int)(restimage2)(Z2i::Point(2,2)) << std::endl;
    nbok += (restimage2(Z2i::Point(2,2)) == true) ? 1 : 0;
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " write on restricted Image 2"  << endl;
    
    trace.warning()<< "Restricted image 2 at (2,2) = "<< (restimage2)(Z2i::Point(2,2)) << std::endl;
    trace.warning()<< "Original image at (2,2) = "<< (image)(Z2i::Point(2,2)) << std::endl;
    
    typedef ImageAdapter<VImage, Z2i::Domain, MyTransValueFunctor<Z2i::Point>, VImage::Value, functors::Identity, functors::Identity > MyImageAdapter3;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImageAdapter3 > ));
    
    MyTransValueFunctor<Z2i::Point> idD_3(Z2i::Point(2,2));
    functors::Identity idV_3;
    functors::Identity idVm1_3;
    
    MyImageAdapter3 restimage3(image, domain, idD_3, idV_3, idVm1_3);
    
    restimage3.setValue(Z2i::Point(2,2), 5);
    nbok += (image(Z2i::Point(4,4)) == 5) ? 1 : 0; 
    nb++;
    trace.info() << "(" << nbok << "/" << nb << ") "
    << " write on restricted Image 3"  << endl;
    
    trace.warning()<< "Original image at (2,2) = "<< (image)(Z2i::Point(2,2)) << std::endl;
    trace.warning()<< "Original image at (4,4) = "<< (image)(Z2i::Point(4,4)) << std::endl;
    trace.warning()<< "Original image at (5,5) = "<< (image)(Z2i::Point(5,5)) << std::endl;
    
    trace.endBlock();
    
    return nbok == nb;
}

bool test_range_constRange()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock("Testing range/constRange with ImageAdapter");
    
    typedef ImageContainerBySTLVector<Z2i::Domain, int> VImage;

    VImage image(Z2i::Domain(Z2i::Point(0,0), Z2i::Point(10,10)));
    for (VImage::Iterator it = image.begin(); it != image.end(); ++it)
        *it = 10;

    trace.info() << "Original image: " << image << endl;

    Z2i::Domain domain(Z2i::Point(2,2), Z2i::Point(4,4));
    typedef ImageAdapter<VImage, Z2i::Domain, functors::Identity, VImage::Value, functors::Identity, functors::Identity > MyImageAdapter;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImageAdapter > ));
    
    functors::Identity idD;
    functors::Identity idV;
    functors::Identity idVm1;
    
    MyImageAdapter restimage(image, domain, idD, idV, idVm1);
    trace.info() << "Restricted Image: " << restimage << "  " << restimage.domain() << std::endl;

    // writing values
    const int maximalValue = domain.size(); 
    MyImageAdapter::Range::OutputIterator it = restimage.range().outputIterator(); 
    for (int i = 0; i < maximalValue; ++i)
      *it++ = i;

    // reading values 
    MyImageAdapter::ConstRange r = restimage.constRange(); 
    std::copy( r.begin(), r.end(), std::ostream_iterator<int>(cout,", ") ); 
    cout << endl;
    
    std::vector<int> to_vector(9);
    std::copy(r.begin(), r.end(), to_vector.begin());
    for (int i = 0; i < 9; i++)
    {
      if (to_vector[i]==i)
      {
        cout << "ok, ";
        nbok += 1 ;
        nb++;
      }
      else
      {
        cout << "!ok, ";
        nb++;
      }
    }
    
    cout << endl; 
    
    trace.endBlock();
    
    return nbok == nb;
}

bool testImageAdapter()
{
    unsigned int nbok = 0;
    unsigned int nb = 0;

    trace.beginBlock ("Testing ImageAdapter");

    typedef ImageContainerBySTLVector< Z2i::Domain, unsigned char> VImage;
    typedef GrayscaleColorMap<unsigned char> Gray;

    string filename = testPath + "samples/church-small.pgm";
    VImage image = PGMReader<VImage>::importPGM(filename);
    trace.info() << "Imported image: " << image << endl;

    Board2D aBoard;

    Display2DFactory::drawImage<Gray>(aBoard, image, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("church.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("church.png", Board2D::CairoPNG);
#endif

    typedef ImageAdapter<VImage, Z2i::Domain, functors::Identity, VImage::Value, functors::Identity, functors::Identity> MyImageAdapter;
    BOOST_CONCEPT_ASSERT(( concepts::CImage< MyImageAdapter > ));

    // 1) bell_tower
    //! [ImageAdapterWithSubdomain]
    Z2i::Point p1( 43, 107 );
    Z2i::Point p2( 73, 177 );
    Z2i::Domain domain_bell_tower( p1, p2 );

    functors::Identity idbtD, idbtV, idbtVm1;
    MyImageAdapter bell_tower(image, domain_bell_tower, idbtD, idbtV, idbtVm1);
    //! [ImageAdapterWithSubdomain]

    trace.info() << "ImageAdapter: " << bell_tower << "  " << bell_tower.domain() << std::endl;

    nbok += bell_tower.isValid() ? 1 : 0;
    nb++;

    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, bell_tower, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("bell_tower.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("bell_tower.png", Board2D::CairoPNG);
#endif

    // 2) cars
    Z2i::Point p3( 0, 49 );
    Z2i::Point p4( 58, 72 );
    Z2i::Domain domain_cars( p3, p4 );
    
    functors::Identity idcD;
    functors::Identity idcV;
    functors::Identity idcVm1;
    MyImageAdapter cars(image, domain_cars, idcD, idcV, idcVm1);

    trace.info() << "ImageAdapter: " << cars << "  " << cars.domain() << std::endl;

    nbok += cars.isValid() ? 1 : 0;
    nb++;

    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, cars, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("cars.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("cars.png", Board2D::CairoPNG);
#endif

    // 3) fill 255 for 'bell_tower' image
    MyImageAdapter::Domain::ConstIterator bt_it = bell_tower.domain().begin();
    MyImageAdapter::Domain::ConstIterator bt_itEnd = bell_tower.domain().end();
    for (; bt_it != bt_itEnd; ++bt_it)
    {
        bell_tower.setValue(*bt_it, 255);
    }

    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, bell_tower, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("bell_tower_after_filling.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("bell_tower_after_filling.png", Board2D::CairoPNG);
#endif

    // 4) fill 55 for 'cars' image
    MyImageAdapter::Domain::ConstIterator c_it = cars.domain().begin();
    MyImageAdapter::Domain::ConstIterator c_itEnd = cars.domain().end();
    for (; c_it != c_itEnd; ++c_it)
    {
        cars.setValue(*c_it, 55);
    }
    
    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, cars, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("cars_after_filling.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("cars_after_filling.png", Board2D::CairoPNG);
#endif
    
    // 5) fill 0 (only for one pixel on two) for 'floor_lamp' image
    //! [ImageAdapterWithSpecificDomain]
    Z2i::Point p5( 56, 33 );
    Z2i::Point p6( 68, 79 );
    Z2i::Domain domain_floor_lamp( p5, p6 );

    // --- DigitalSetDomain
    Z2i::DigitalSet mySet( domain_floor_lamp );

    unsigned int i = 0;
    for ( Z2i::Domain::ConstIterator it = domain_floor_lamp.begin() ; 
      it != domain_floor_lamp.end();
      ++it, ++i )
    {
      if (i%2)
        mySet.insertNew( *it );
    }
    
    DigitalSetDomain<Z2i::DigitalSet> my_specific_domain_floor_lamp(mySet);
    // --- DigitalSetDomain
    

    typedef ImageAdapter<VImage, DigitalSetDomain<Z2i::DigitalSet>, functors::Identity, VImage::Value, functors::Identity, functors::Identity> MyImageAdapter2;
    // BOOST_CONCEPT_ASSERT(( CImage< MyImageAdapter2 > )); // pb here

    functors::Identity idflD, idflV, idflVm1;
    MyImageAdapter2 floor_lamp(image, my_specific_domain_floor_lamp, idflD, idflV, idflVm1);
    //! [ImageAdapterWithSpecificDomain]

    trace.info() << "ImageAdapter: " << floor_lamp << "  " << floor_lamp.domain() << std::endl;

    nbok += floor_lamp.isValid() ? 1 : 0;
    nb++;
    
    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, floor_lamp, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("floor_lamp.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("floor_lamp.png", Board2D::CairoPNG);
#endif
    
    MyImageAdapter2::Domain::ConstIterator f_it = floor_lamp.domain().begin();
    MyImageAdapter2::Domain::ConstIterator f_itEnd = floor_lamp.domain().end();
    for (; f_it != f_itEnd; ++f_it)
    {
        floor_lamp.setValue(*f_it, 0);
    }
    
    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, floor_lamp, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("floor_lamp_after_filling.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("floor_lamp_after_filling.png", Board2D::CairoPNG);
#endif

    aBoard.clear();
    Display2DFactory::drawImage<Gray>(aBoard, image, (unsigned char)0, (unsigned char)255);
    aBoard.saveSVG("church_after_filling.svg");
#ifdef WITH_CAIRO
    aBoard.saveCairo("church_after_filling.png", Board2D::CairoPNG);
#endif

    trace.info() << "(" << nbok << "/" << nb << ") "
    << "true == true" << endl;
    trace.endBlock();

    return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
    trace.beginBlock ( "Testing class ImageAdapter" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    bool res = testSimple() && test_g_f_fm1() && test_range_constRange() && testImageAdapter(); // && ... other tests

    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
