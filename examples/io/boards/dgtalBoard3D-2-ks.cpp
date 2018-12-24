
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
 * @file io/boards/dgtalBoard3D-2-ks.cpp
 * @ingroup Examples
 * @author Aline MARTIN (\c aline.martin@insa-lyon.fr )
 *
 * @date 2013/06/16
 *
 * An example file named dgtalBoard3D-2-ks.
 *
 */


/**
 *   Example of Khalimsky Signed Cell export with Display3D.
 *  @see \ref DGtalGLV_OBJExport
 *  \image html  dgtalBoard3D-2-ks.png  "Illustration of the resulting exported file (OBJ format visualized with blender)."
 *  \example io/boards/dgtalBoard3D-2-ks.cpp
 *
 */


#include <iostream>
#include "DGtal/io/boards/Board3D.h"
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"

using namespace std;
using namespace DGtal;
using namespace Z3i;


// Standard services - public :

int main( )
{

  KSpace K;
  Point plow(0,0,0);
  Point pup(1,1,0);
  Domain domain( plow, pup );
  K.init( plow, pup, true );

  Board3D<Space, KSpace> board(K);

  // drawing cells of dimension 3

  SCell v2 = K.sSpel( Point( 1, 0, 0 ), KSpace::POS ); // +v
  SCell v3 = K.sSpel( Point( 0, 1, 0 ), KSpace::POS ); // +v
  SCell v4 = K.sSpel( Point( 1, 1, 0 ), KSpace::NEG ); // +v
  //! [SetKSIllustrationMode3D]
  SCell v = K.sSpel( Point( 0, 0, 0 ), KSpace::POS ); // +v
  board << SetMode3D( v.className(), "Illustration" );
  //! [SetKSIllustrationMode3D]

  board << v << v2 << v3;
  board.saveOBJ("board3D-2-ks.obj");

  Board3D<Space, KSpace> board2(K);

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

  board2 << tsx << tsy << tsz << tsxn << tsyn << tszn;


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

  board2 << tsx2 << tsy2 << tsz2 << tsxn2 << tsyn2 << tszn2;


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


  board2 << tsx3 << tsy3 << tsz3 << tsxn3 << tsyn3 << tszn3;

  std::cout << "save obj" << std::endl;
  board2.saveOBJ("board3D-2bis-ks.obj");


}
