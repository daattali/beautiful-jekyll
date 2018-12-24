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
 * @file testEmbedder.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/16
 *
 * Functions for testing class Embedder.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/kernel/CPointEmbedder.h"
#include "DGtal/kernel/CWithGradientMap.h"
#include "DGtal/kernel/CanonicEmbedder.h"
#include "DGtal/topology/CanonicCellEmbedder.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/topology/CanonicDigitalSurfaceEmbedder.h"
#include "DGtal/kernel/RegularPointEmbedder.h"
#include "DGtal/topology/CCellEmbedder.h"
#include "DGtal/topology/CSCellEmbedder.h"
#include "DGtal/topology/CDigitalSurfaceEmbedder.h"
#include "DGtal/topology/DigitalSetBoundary.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/shapes/implicit/ImplicitPolynomial3Shape.h"
#include "DGtal/shapes/implicit/ImplicitFunctionLinearCellEmbedder.h"
#include "DGtal/shapes/implicit/ImplicitFunctionDiff1LinearCellEmbedder.h"
#include "DGtal/geometry/surfaces/estimation/BasicConvolutionWeights.h"
#include "DGtal/geometry/surfaces/estimation/LocalConvolutionNormalVectorEstimator.h"
#include "DGtal/geometry/surfaces/estimation/DigitalSurfaceEmbedderWithNormalVectorEstimator.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace DGtal::concepts;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Embedder.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testEmbedder()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  using Z3i::Point;
  using Z3i::Vector;
  using Z3i::Domain;
  using Z3i::Space;
  using Z3i::KSpace;
  using Z3i::DigitalSet;

  typedef CanonicEmbedder<Space> MyEmbedder1;
  BOOST_CONCEPT_ASSERT(( CPointEmbedder< MyEmbedder1 > ));
  typedef RegularPointEmbedder<Space> MyEmbedder2;
  BOOST_CONCEPT_ASSERT(( CPointEmbedder< MyEmbedder2 > ));
  typedef ImplicitPolynomial3Shape<Space> ImplicitShape;
  typedef ImplicitFunctionLinearCellEmbedder
    < KSpace, ImplicitShape, MyEmbedder1 > MyCellEmbedder1;
  BOOST_CONCEPT_ASSERT(( CCellEmbedder< MyCellEmbedder1 > ));
  typedef ImplicitFunctionDiff1LinearCellEmbedder
    < KSpace, ImplicitShape, MyEmbedder2 > MyCellEmbedder2;
  BOOST_CONCEPT_ASSERT(( CCellEmbedder< MyCellEmbedder2 > ));
  BOOST_CONCEPT_ASSERT(( CWithGradientMap< MyCellEmbedder2 > ));
  typedef CanonicCellEmbedder<KSpace> MyCellEmbedder3;
  BOOST_CONCEPT_ASSERT(( CCellEmbedder< MyCellEmbedder3 > ));
  typedef CanonicSCellEmbedder<KSpace> MySCellEmbedder1;
  BOOST_CONCEPT_ASSERT(( CSCellEmbedder< MySCellEmbedder1 > ));
  typedef DigitalSetBoundary<KSpace, DigitalSet> DigitalSurfaceContainer;
  typedef DigitalSurface<DigitalSurfaceContainer> MyDigitalSurface;
  typedef CanonicDigitalSurfaceEmbedder<MyDigitalSurface> MyDSEmbedder1;
  BOOST_CONCEPT_ASSERT(( CDigitalSurfaceEmbedder< MyDSEmbedder1 > ));
  typedef deprecated::ConstantConvolutionWeights< MyDigitalSurface::Size > Kernel;
  typedef deprecated::LocalConvolutionNormalVectorEstimator
    < MyDigitalSurface, Kernel > MyEstimator;
  typedef DigitalSurfaceEmbedderWithNormalVectorEstimator
    < MyDSEmbedder1, MyEstimator > MyDSEmbedder2;
  BOOST_CONCEPT_ASSERT(( CDigitalSurfaceEmbedder< MyDSEmbedder2 > ));
  BOOST_CONCEPT_ASSERT(( CWithGradientMap< MyDSEmbedder2 > ));

  trace.beginBlock ( "Testing block ..." );
  KSpace K;
  MyCellEmbedder3 cemb3( K );
  MySCellEmbedder1 scemb1( K );
  Domain domain( Point( 0, 0, 0 ), Point( 10, 10, 10 ) );
  K.init( Point( 0, 0, 0 ), Point( 10, 10, 10 ), true );
  DigitalSet dset( domain );
  //dset.insert( Point( 3,3,2) );
  DigitalSurfaceContainer dsc( K, dset );
  MyDigitalSurface ds( dsc );
  MyDSEmbedder1 dsemb1( ds );
  nbok += true ? 1 : 0;
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
  trace.beginBlock ( "Testing class Embedder" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testEmbedder(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
