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
 * @file images/extract2DSlicesImagesFrom3D.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/04/24
 *
 * An example file named extract2DImagesFrom3D.
 *
 * This file is part of the DGtal library.
 */


/**
 *  Example of 2D slice images extraction from 3D images.
 *
 *  \image html lobsterSliceZ_20.png   "Example of resulting 2D slices images of the sample/lobster.vol file."
 *
 * \example images/extract2DSlicesImagesFrom3D.cpp
 **/


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/kernel/BasicPointFunctors.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/writers/PGMWriter.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/ConstImageAdapter.h"
#include "ConfigExamples.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( )
{
   typedef ImageSelector < Z3i::Domain, unsigned char>::Type Image3D;
   typedef ImageSelector < Z2i::Domain, unsigned char>::Type Image2D;
   typedef DGtal::ConstImageAdapter<Image3D, Image2D::Domain, DGtal::functors::Projector<Z3i::Space>,
                                    Image3D::Value,  DGtal::functors::Identity >  SliceImageAdapter;
   

   DGtal::functors::Projector<Z2i::Space >  proj(2);

   // Importing a 3D image
   std::string filename = examplesPath + "samples/lobster.vol";
   Image3D image = VolReader<Image3D>::importVol( filename );
   DGtal::Z2i::Domain domain(proj(image.domain().lowerBound()),
			     proj(image.domain().upperBound()));
   DGtal::functors::Identity idV;

   trace.beginBlock ( "Example extract2DImagesFrom3D" );

   // Extracting 2D slices ... and export them in the pgm format.
   for (unsigned int i=0; i<30; i+=10){
     std::stringstream name;
     name << "lobsterSliceZ_"  << i << ".pgm";
     DGtal::functors::Projector<Z3i::Space> aSliceFunctor(i); aSliceFunctor.initAddOneDim(2);
     SliceImageAdapter sliceImageZ(image, domain, aSliceFunctor, idV);
     PGMWriter<SliceImageAdapter>::exportPGM(name.str(), sliceImageZ);
   }

   // trace.endBlock();
   return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
