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
 * @file io/viewers/viewer3D-4bis-illustrationMode.cpp
 * @ingroup examples/3dViewer
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2012/09/09
 *
 * Example the "Illustration" mode with KhalimskyCell
 *
 * This file is part of the DGtal library.
 */


/**
 *   \image html  view3D-4bis-illustrationMode.png  "Illustration of the \"Illustration\" KhalimskyCell mode."
 * \example io/viewers/viewer3D-4bis-illustrationMode.cpp
 */ 

///////////////////////////////////////////////////////////////////////////////
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/viewers/Viewer3D.h"
//!  [SetKSIllustrationMode3DHeader]
#include "DGtal/io/DrawWithDisplay3DModifier.h"
//!  [SetKSIllustrationMode3DHeader]
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{

  QApplication application(argc,argv);

  KSpace K;
  Point plow(0,0,0);
  Point pup(1,1,0);
  Domain domain( plow, pup );
  K.init( plow, pup, true );

  typedef Viewer3D<Space, KSpace> MyViewer;
  MyViewer viewer(K);
  viewer.show();

  viewer << SetMode3D( domain.className(), "Paving" );
  viewer << domain;

  // drawing cells of dimension 3

  SCell v2 = K.sSpel( Point( 1, 0, 0 ), KSpace::POS ); // +v
  SCell v3 = K.sSpel( Point( 0, 1, 0 ), KSpace::POS ); // +v
  SCell v4 = K.sSpel( Point( 1, 1, 0 ), KSpace::NEG ); // +v
  //! [SetKSIllustrationMode3D]
  SCell v = K.sSpel( Point( 0, 0, 0 ), KSpace::POS ); // +v
  viewer << SetMode3D( v.className(), "Illustration" );
  //! [SetKSIllustrationMode3D]

  viewer << v << v2 << v3;


  // Surfel of Voxel (0,0)
  //! [KSIllustrationModeTransformed]
  SCell sx = K.sIncident( v, 0, true ); // surfel further along x
  DGtal::TransformedPrism tsx (sx, v);
  //! [KSIllustrationModeTransformed]

  SCell sy = K.sIncident( v, 1, true ); // surfel further along y
  SCell sz = K.sIncident( v, 2, true ); // surfel further along z
  SCell sxn = K.sIncident( v, 0, false ); // surfel further along x
  SCell syn = K.sIncident( v, 1, false ); // surfel further along y
  SCell szn = K.sIncident( v, 2, false ); // surfel further along z

  // Resizing and shifting the surfel towords its associated voxel (v).

  DGtal::TransformedPrism tsy (sy, v);
  DGtal::TransformedPrism tsz (sz, v);
  DGtal::TransformedPrism tsxn (sxn, v);
  DGtal::TransformedPrism tsyn (syn, v);
  DGtal::TransformedPrism tszn (szn, v);

  viewer << tsx << tsy << tsz << tsxn << tsyn << tszn;


  // Surfel of Voxel (1,0)
  SCell sx2 = K.sIncident( v2, 0, true ); // surfel further along x
  SCell sy2 = K.sIncident( v2, 1, true ); // surfel further along y
  SCell sz2 = K.sIncident( v2, 2, true ); // surfel further along z
  SCell sxn2 = K.sIncident( v2, 0, false ); // surfel further along x
  SCell syn2 = K.sIncident( v2, 1, false ); // surfel further along y
  SCell szn2 = K.sIncident( v2, 2, false ); // surfel further along z

  // Resizing and shifting the surfel towords its associated voxel (v2).
  DGtal::TransformedPrism tsx2 (sx2, v2);
  DGtal::TransformedPrism tsy2 (sy2, v2);
  DGtal::TransformedPrism tsz2 (sz2, v2);
  DGtal::TransformedPrism tsxn2 (sxn2, v2);
  DGtal::TransformedPrism tsyn2 (syn2, v2);
  DGtal::TransformedPrism tszn2 (szn2, v2);

  viewer << tsx2 << tsy2 << tsz2 << tsxn2 << tsyn2 << tszn2;


  // Surfel of Voxel (0,1)
  SCell sx3 = K.sIncident( v3, 0, true ); // surfel further along x
  SCell sy3 = K.sIncident( v3, 1, true ); // surfel further along y
  SCell sz3 = K.sIncident( v3, 2, true ); // surfel further along z
  SCell sxn3 = K.sIncident( v3, 0, false ); // surfel further along x
  SCell syn3 = K.sIncident( v3, 1, false ); // surfel further along y
  SCell szn3 = K.sIncident( v3, 2, false ); // surfel further along z

  // Shifting the surfel to its associated voxel (v3).
  DGtal::TransformedPrism tsx3 (sx3, v3);
  DGtal::TransformedPrism tsy3 (sy3, v3);
  DGtal::TransformedPrism tsz3 (sz3, v3);
  DGtal::TransformedPrism tsxn3 (sxn3, v3);
  DGtal::TransformedPrism tsyn3 (syn3, v3);
  DGtal::TransformedPrism tszn3 (szn3, v3);


  viewer << tsx3 << tsy3 << tsz3 << tsxn3 << tsyn3 << tszn3;
  viewer  << MyViewer::updateDisplay;

  return application.exec();
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
