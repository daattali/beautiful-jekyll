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
 * @file testImplicitShape.cpp
 * @ingroup Tests
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/22
 *
 * Functions for testing class ImplicitShape.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/GrayscaleColorMap.h"
#include "DGtal/io/writers/VolWriter.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImplicitShape.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testImplicitShape()
{
  trace.beginBlock ( "Testing implicit shaper ..." );
  Z2i::Point a(0,0);
  Z2i::Point b(64,64);
  Z2i::Point c(32,32);
  
  Board2D board;
  
  Z2i::Domain domain(a,b);
  Z2i::DigitalSet set(domain);
  
  Shapes<Z2i::Domain>::euclideanShaper( set,
             ImplicitBall<Z2i::Space>( c, 10));
  board << set;
  board.saveSVG("implicitball.svg");

  set.clear();
  board.clear();
  Shapes<Z2i::Domain>::euclideanShaper( set,
             ImplicitHyperCube<Z2i::Space>( c, 10));
  board << set;
  board.saveSVG("implicitcube.svg");
  

  set.clear();
  board.clear();
  Shapes<Z2i::Domain>::euclideanShaper( set,
             ImplicitNorm1Ball<Z2i::Space>( c, 10));
  board << set;
  board.saveSVG("implicitlosange.svg");
  
  set.clear();
  board.clear();
  Shapes<Z2i::Domain>::euclideanShaper( set,
             ImplicitRoundedHyperCube<Z2i::Space>( c, 10, 1));
  board << set;
  board.saveSVG("implicitrounded-1.svg");
  

  set.clear();
  board.clear();
  Shapes<Z2i::Domain>::euclideanShaper( set,
             ImplicitRoundedHyperCube<Z2i::Space>( c, 10, 2.5));
  board << set;
  board.saveSVG("implicitrounded-2.5.svg");
  

  return true;
}
/**
 * Example of a test. To be completed.
 *
 */
bool testImplicitShape3D()
{
  trace.beginBlock ( "Testing implicit shaper in 3D..." );
  Z3i::Point a(0,0);
  Z3i::Point b(64,64,64);
  Z3i::Point c(32,32,32);
  
  Z3i::Domain domain(a,b);

  typedef ImageContainerBySTLVector<Z3i::Domain, DGtal::uint8_t> Image;

  Image image(domain);
  Z3i::DigitalSet set(domain);

  Shapes<Z3i::Domain>::euclideanShaper( set,
             ImplicitRoundedHyperCube<Z3i::Space>( c, 10, 2.5));

  for(Z3i::DigitalSet::ConstIterator it=set.begin(), itend=set.end();
      it != itend;
      ++it)
    {
      image.setValue((*it), 128);
    }

  VolWriter<Image>::exportVol("implicitrounded.vol",image);
  
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ImplicitShape" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testImplicitShape() && testImplicitShape3D(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
