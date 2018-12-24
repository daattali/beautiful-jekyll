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
 * @file testParDirCollapse.cpp
 * @ingroup Tests
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2016/01/16
 *
 * Functions for testing class ParDirCollapse.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
// Cellular grid
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/topology/ParDirCollapse.h"
// Shape construction
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/EuclideanShapesDecorator.h"
#include "DGtal/shapes/parametric/Flower2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ParDirCollapse.
///////////////////////////////////////////////////////////////////////////////

template <typename CC, typename KSpace>
void getComplex ( CC & complex, KSpace & K )
{
  typedef Flower2D< Space > MyEuclideanShape;
  MyEuclideanShape shape( RealPoint( 0.0, 0.0 ), 16, 5, 5, M_PI_2/2. );

  typedef GaussDigitizer< Space, MyEuclideanShape > MyGaussDigitizer;
  MyGaussDigitizer digShape;
  digShape.attach( shape );
  digShape.init ( shape.getLowerBound(), shape.getUpperBound(), 1.0 );
  Domain domainShape = digShape.getDomain();
  DigitalSet aSet( domainShape );
  Shapes<Domain>::digitalShaper( aSet, digShape );

  K.init ( domainShape.lowerBound(), domainShape.upperBound(), true );
  complex.clear();
  complex.construct ( aSet );
}

TEST_CASE( "Testing ParDirCollapse" )
{
  typedef map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;
  KSpace K;
  CC complex ( K );
  ParDirCollapse < CC > thinning ( K );

  SECTION("Testing the basic algorithm of ParDirCollapse")
    {
      getComplex< CC, KSpace > ( complex, K );
      int eulerBefore = complex.euler();
      thinning.attach ( &complex );
      REQUIRE( ( thinning.eval ( 2 ) != 0 ) );
      REQUIRE( (eulerBefore == complex.euler()) );
    }

  SECTION("Testing ParDirCollapse::collapseSurface")
    {
      getComplex< CC, KSpace > ( complex, K );
      int eulerBefore = complex.euler();
      thinning.attach ( &complex );
      thinning.collapseSurface ();
      REQUIRE( (eulerBefore == complex.euler()) );
    }
  SECTION("Testing ParDirCollapse::collapseIsthmus")
    {
      getComplex< CC, KSpace > ( complex, K );
      int eulerBefore = complex.euler();
      thinning.attach ( &complex );
      thinning.collapseIsthmus ();
      REQUIRE( (eulerBefore == complex.euler()) );
    }
}

/** @ingroup Tests **/
