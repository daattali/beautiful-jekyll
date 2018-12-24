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
 * @file io/display3DToOFF.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/03/25
 *
 * An example file named display3DToOFF.
 *
 * This file is part of the DGtal library.
 */

/**
 *  Example of OFF generation from a Display3D object.
 *
 * @see @ref exportMesh3D
 * @image html visuDisplay3DToOFF.png   "Visualisation of the Display3D mesh export using MeshLab software (http://meshlab.sourceforge.net). "
 *
 * @example io/display3DToOFF.cpp
 */

#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/Display3D.h"

#include "DGtal/io/DrawWithDisplay3DModifier.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"


using namespace std;
using namespace DGtal;
using namespace Z3i;


int main( int /*argc*/, char** /*argv*/ )
{
  std::string inputFilename = examplesPath + "samples/Al.100.vol";
  //! [ExampleDisplay3DToOFF]
  Display3D<Space, KSpace> viewer;
  typedef ImageSelector < Z3i::Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  Z3i::DigitalSet set3d (image.domain());
  SetFromImage<Z3i::DigitalSet>::append<Image>(set3d, image, 0,255);

  viewer << set3d ;
  viewer >> "exportMeshToOFF.off";
 //! [ExampleDisplay3DToOFF]

  return 0;
}
