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
 * @file testImplicitFunctionModels.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/28
 *
 * Functions for testing class ImplicitFunctionModels.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/implicit/ImplicitNorm1Ball.h"
#include "DGtal/shapes/implicit/ImplicitHyperCube.h"
#include "DGtal/shapes/implicit/ImplicitRoundedHyperCube.h"
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/shapes/implicit/CImplicitFunction.h"
#include "DGtal/shapes/implicit/CImplicitFunctionDiff1.h"
#include "DGtal/helpers/StdDefs.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ImplicitFunctionModels.
///////////////////////////////////////////////////////////////////////////////



/**
 * Tests models of CImplicitFunction.
 */
bool testImplicitFunctionModels()
{
  typedef ImplicitBall<Z2i::Space> _ImplicitBall2D;
  typedef ImplicitBall<Z3i::Space> _ImplicitBall3D;
  typedef ImplicitNorm1Ball<Z2i::Space> _ImplicitNorm1Ball2D;
  typedef ImplicitNorm1Ball<Z3i::Space> _ImplicitNorm1Ball3D;
  typedef ImplicitHyperCube<Z2i::Space> _ImplicitHyperCube2D;
  typedef ImplicitHyperCube<Z3i::Space> _ImplicitHyperCube3D;
  typedef ImplicitRoundedHyperCube<Z2i::Space> _ImplicitRoundedHyperCube2D;
  typedef ImplicitRoundedHyperCube<Z3i::Space> _ImplicitRoundedHyperCube3D;
  typedef ImplicitPolynomial3Shape<Z3i::Space> _ImplicitPolynomial3Shape;
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitBall2D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitBall3D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitNorm1Ball2D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitNorm1Ball3D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitHyperCube2D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitHyperCube3D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitRoundedHyperCube2D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitRoundedHyperCube3D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunction< _ImplicitPolynomial3Shape > ));
  //BOOST_CONCEPT_ASSERT(( CImplicitFunctionDiff1< _ImplicitBall2D > ));
  BOOST_CONCEPT_ASSERT(( concepts::CImplicitFunctionDiff1< _ImplicitPolynomial3Shape > ));
  return true;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Testing class ImplicitFunctionModels" );
  bool res = testImplicitFunctionModels(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
