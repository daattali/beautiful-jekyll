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
 * @file topology/3dBorderExtractionImg.cpp
 * @ingroup Examples
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/03/25
 *
 * An example file named 3dBorderExtraction.
 *
 * This file is part of the DGtal library.
 */


/**
 *  Objects have a border, which are the points which touch the
 *  complement in the sense of background adjacency. A border of an
 *  object is itself an object, with the same topology as the object.
 *    
 *   @see \ref dgtal_topology_sec3_3
 *   @image html visuBorderExtraction2.png  "Border extraction visualisation from imported volume " 
 * 
 *    \example topology/3dBorderExtractionImg.cpp
 */


///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"

#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/images/ImageSelector.h"
#include "DGtal/images/imagesSetsUtils/SetFromImage.h"
#include "DGtal/io/viewers/Viewer3D.h"

#include "DGtal/helpers/StdDefs.h"
#include "ConfigExamples.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{

  std::string inputFilename = examplesPath + "samples/Al.100.vol";
  QApplication application(argc,argv);
  Viewer3D<> viewer;
  viewer.show();

  typedef ImageSelector < Z3i::Domain, int>::Type Image;
  Image image = VolReader<Image>::importVol(inputFilename);
  Z3i::DigitalSet set3d (image.domain());
  SetFromImage<Z3i::DigitalSet>::append<Image>(set3d, image, 0,255);
  Z3i::Object18_6 obj3d (Z3i::dt18_6, set3d);
  Z3i::Object18_6 border = obj3d.border();
  viewer << border;
  viewer << ClippingPlane(0,1,0, -40) << Viewer3D<>::updateDisplay;

  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
