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
 * @file testITKio.cpp
 * @ingroup Tests
 * @author Pierre Gueth (\c pierre.gueth@gmail.com )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/28
 *
 * Functions for testing class ITKio.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "ConfigTest.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/CImage.h"
#include "DGtal/io/writers/ITKWriter.h"
#include "DGtal/io/readers/ITKReader.h"
using namespace DGtal;

#include <string>
using std::endl;
using std::string;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing ITK io
///////////////////////////////////////////////////////////////////////////////
template <typename Image>
bool
test_image(const string& filename)
{
    BOOST_CONCEPT_ASSERT(( concepts::CImage<Image> ));

    typedef typename Image::Domain::Point Point;
    Point point0;
    Point point1;
    for (typename Image::Domain::Dimension kk=0; kk<Image::Domain::dimension; kk++)
    {
        point0[kk] = 5;
        point1[kk] = 10;
    }

    typedef typename Image::Domain Domain;
    const Domain domain(point0, point1);
    Image image(domain);

    typedef typename std::vector<typename Image::Value> Values;
    Values values;
    for (typename Domain::Size kk=0; kk<domain.size(); kk++)
        values.push_back(rand());

    std::copy(values.begin(), values.end(), image.range().outputIterator());

    trace.info() << image << endl;
    trace.info() << "writing " << filename << endl;
    if (!ITKWriter<Image>::exportITK(filename, image)) return false;

    trace.info() << "reading " << filename << endl;
    Image image_read = ITKReader<Image>::importITK(filename);
    trace.info() << image_read << endl;

    if (image_read.domain().lowerBound() !=  image.domain().lowerBound()) trace.warning() << "lowerBound mismatch!!" << endl;
    if (image_read.domain().upperBound() !=  image.domain().upperBound()) trace.warning() << "upperBound mismatch!!" << endl;

    typename Image::ConstRange::ConstIterator iter_read = image_read.constRange().begin();
    typename Image::ConstRange::ConstIterator iter_read_end = image_read.constRange().end();
    typename Values::const_iterator iter_value = values.begin();
    typename Values::const_iterator iter_value_end = values.end();
    while (iter_value!=iter_value_end && iter_read!=iter_read_end)
    {
        if ((*iter_read)!=(*iter_value)) {
            trace.error() << "values mismatch" << endl;
            return false;
        }
        iter_value++;
        iter_read++;
    }

    return true;
}

bool testITKio()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  nbok += 6;
  trace.beginBlock ( "Testing 2D ITK image value types ..." );
  nb += test_image<ImageSelector<Z2i::Domain, int>::Type>("image_2d_int.mha");
  nb += test_image<ImageSelector<Z2i::Domain, bool>::Type>("image_2d_bool.mha");
  nb += test_image<ImageSelector<Z2i::Domain, unsigned int>::Type>("image_2d_unsigned_int.mha");
  nb += test_image<ImageSelector<Z2i::Domain, unsigned char>::Type>("image_2d_unsigned_char.mha");
  nb += test_image<ImageSelector<Z2i::Domain, float>::Type>("image_2d_float.mha");
  nb += test_image<ImageSelector<Z2i::Domain, double>::Type>("image_2d_double.mha");
  trace.endBlock();

  nbok += 6;
  trace.beginBlock ( "Testing 3D ITK image value types ..." );
  nb += test_image<ImageSelector<Z3i::Domain, int>::Type>("image_3d_int.mha");
  nb += test_image<ImageSelector<Z3i::Domain, bool>::Type>("image_3d_bool.mha");
  nb += test_image<ImageSelector<Z3i::Domain, unsigned int>::Type>("image_3d_unsigned_int.mha");
  nb += test_image<ImageSelector<Z3i::Domain, unsigned char>::Type>("image_3d_unsigned_char.mha");
  nb += test_image<ImageSelector<Z3i::Domain, float>::Type>("image_3d_float.mha");
  nb += test_image<ImageSelector<Z3i::Domain, double>::Type>("image_3d_double.mha");
  trace.endBlock();

  nbok += 3;
  trace.beginBlock ( "Testing 2D ITK image formats ..." );
  nb += test_image<ImageSelector<Z2i::Domain, unsigned char>::Type>("image_unsigned_char.jpg"); nbok--; // jpg is lossy
  nb += test_image<ImageSelector<Z2i::Domain, unsigned char>::Type>("image_unsigned_char.png");
  nb += test_image<ImageSelector<Z2i::Domain, unsigned char>::Type>("image_unsigned_char.bmp");
  trace.endBlock();

  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  bool res = testITKio(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
