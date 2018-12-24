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
 * @file testSliceImageFromFunctor.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/04/24
 *
 * Functions for testing class ImageHelper.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/PGMWriter.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ConstImageAdapter.h"

#include "ConfigTest.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImageHelper.
///////////////////////////////////////////////////////////////////////////////
/**
 * Test of the function extractLowerDimImage for the extraction of 2D images from 3D image.
 *
 */

bool testSliceImageFromFunctor()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  std::string filename = testPath + "samples/cat10.vol";
  trace.beginBlock ( "Testing block ..." );
  typedef  DGtal::ImageContainerBySTLVector<DGtal::Z3i::Domain, unsigned char>  Image3D;

  typedef DGtal::ConstImageAdapter<Image3D, DGtal::Z2i::Domain, functors::Projector< DGtal::Z3i::Space>,
				   Image3D::Value,  DGtal::functors::Identity >  MySliceImageAdapter;

  typedef DGtal::ConstImageAdapter<Image3D, DGtal::Z2i::Domain, functors::SliceRotator2D< HyperRectDomain< DGtal::Z3i::Space >, DGtal::Z3i::Integer>,
				   Image3D::Value,  DGtal::functors::Identity >  MyRotatorSliceImageAdapter;

  bool res= true;
  Image3D image = VolReader<Image3D>::importVol( filename );
  DGtal::functors::Projector<DGtal::Z2i::Space>  projX(0); projX.initRemoveOneDim(0);
  DGtal::Z2i::Domain domainX(projX(image.domain().lowerBound()),
			     projX(image.domain().upperBound()));


  DGtal::functors::Projector<DGtal::Z3i::Space> aSliceFunctor(0); aSliceFunctor.initAddOneDim(0);
  const auto identityFunctor = DGtal::functors::Identity();
  MySliceImageAdapter sliceImageX(image, domainX, aSliceFunctor, identityFunctor);
  res &= PGMWriter<MySliceImageAdapter>::exportPGM("exportedSlice2DDimX.pgm",sliceImageX);

   DGtal::functors::Projector<DGtal::Z2i::Space>  projY(0); projY.initRemoveOneDim(1);
  DGtal::Z2i::Domain domainY(projY(image.domain().lowerBound()),
			     projY(image.domain().upperBound()));

  DGtal::functors::Projector<DGtal::Z3i::Space> aSliceFunctor2(0); aSliceFunctor2.initAddOneDim(1);
   MySliceImageAdapter sliceImageY(image, domainY, aSliceFunctor2, identityFunctor);
  res &= PGMWriter<MySliceImageAdapter>::exportPGM("exportedSlice2DDimY.pgm",sliceImageY);


  DGtal::functors::Projector<DGtal::Z2i::Space>  projZ(0); projZ.initRemoveOneDim(2);
  DGtal::Z2i::Domain domainZ(projZ(image.domain().lowerBound()),
			     projZ(image.domain().upperBound()));


  DGtal::functors::Projector<DGtal::Z3i::Space> aSliceFunctor3(0); aSliceFunctor3.initAddOneDim(2);
  MySliceImageAdapter sliceImageZ(image, domainZ, aSliceFunctor3, identityFunctor);
  res &= PGMWriter<MySliceImageAdapter>::exportPGM("exportedSlice2DDimZ.pgm",sliceImageZ);


  PointVector<3, DGtal::Z3i::Integer> center(0,0,0);
  DGtal::functors::SliceRotator2D< HyperRectDomain< DGtal::Z3i::Space >, DGtal::Z3i::Integer> sliceRot(2, image.domain(), 0, 2, M_PI/4.0, center);


  MyRotatorSliceImageAdapter sliceRotImageZ(image, domainZ, sliceRot, identityFunctor);
  res &= PGMWriter<MyRotatorSliceImageAdapter>::exportPGM("exportedRotSliceZ.pgm",sliceRotImageZ);





  nbok += res ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
  trace.endBlock();

  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ImageHelper" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testSliceImageFromFunctor(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
