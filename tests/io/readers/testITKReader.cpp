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
 * @file testITKReader.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Lorraine, France
 *
 * @date 2017/04/02
 *
 * Functions for testing class ITKReader.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/io/readers/ITKReader.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ITKReader.
///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing ITKReader" )
{
  // Default image selector = STLVector
  typedef ImageContainerBySTLVector<Z3i::Domain, unsigned char> Image3DUC;
  typedef ImageContainerBySTLVector<Z3i::Domain, uint16_t> Image3D16b;

  SECTION(
  "Testing feature io/readers of ITKReader with  16 bits (unit16) images" )
  {
    Image3D16b im = ITKReader<Image3D16b>::importITK(
    testPath + "samples/lobsterCroped16b.mhd" );
    REQUIRE( ( im( Z3i::Point( 35, 29, 3 ) ) == 60400 ) );
  }

  SECTION(
  "Testing feature io/readers of ITKReader with rescaled 16 bits (unit16) "
  "images" )
  {
    typedef DGtal::functors::Rescaling<uint16_t, unsigned char> RescalFCT;
    RescalFCT resc = RescalFCT( 0, 65535, 0, 255 );
    Image3DUC im   = ITKReader<Image3DUC>::importITK(
    testPath + "samples/lobsterCroped16b.mhd", resc );
    REQUIRE( ( im( Z3i::Point( 35, 29, 3 ) ) == resc( 60400 ) ) );
  }
}

/** @ingroup Tests **/
