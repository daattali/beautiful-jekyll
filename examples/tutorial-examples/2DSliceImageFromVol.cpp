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
 * @file 2DSliceImageFromVol.cpp
 * @ingroup tutorial-examples
 * @author Bertrand Kerautret (\c bertrand.kerautret@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Lorraine, France
 * 
 *
 * @date 2016/05/09
 *
 * @brief Example associated to the tutorial 5 on Image adapter
 *
 * This file is part of the DGtal library.
 */

#include <iostream>
#include <DGtal/base/Common.h>
#include "DGtal/io/readers/GenericReader.h"
#include "DGtal/io/writers/GenericWriter.h"

#include <DGtal/helpers/StdDefs.h>
#include <DGtal/images/ImageContainerBySTLVector.h>
#include <DGtal/images/ConstImageAdapter.h>


#include "DGtal/kernel/BasicPointFunctors.h"

using namespace std;
using namespace DGtal;
using namespace Z2i;



int main(int argc, char ** argv)
{
    
  typedef ImageContainerBySTLVector<Z2i::Domain, unsigned char>  Image2D;
  typedef ImageContainerBySTLVector<Z3i::Domain, unsigned char>  Image3D;

  if(argc < 3)
    {
      trace.error() << "You need to indicate the volumetric image name and slice number as parameters." << std::endl;
      trace.error() << std::endl;
      return 1;
    }
  std::string filename(argv[1]);  
  std::string outputFileName = "sliceImage.pgm";

  unsigned int numSlice = atoi(argv[2]);

  trace.beginBlock("Loading file");
  Image3D  image3d = GenericReader< Image3D >::import ( filename );
  
   
  functors::Identity id;  
  typedef ConstImageAdapter<Image3D, Image2D::Domain, functors::Projector<Z3i::Space>,
                            Image3D::Value,  functors::Identity >  SliceImageAdapter;
  functors::Projector<Z2i::Space >  proj(2);
  Z2i::Domain domain2D(proj(image3d.domain().lowerBound()),
                              proj(image3d.domain().upperBound()));

  DGtal::functors::Projector<Z3i::Space> aSliceFunctor(numSlice); 
  aSliceFunctor.initAddOneDim(2);
  SliceImageAdapter sliceImageZ(image3d, domain2D, aSliceFunctor, id);
  
  trace.endBlock();

  trace.beginBlock("Exporting...");
  sliceImageZ >> outputFileName; 
  trace.endBlock();
  return 0;
}
