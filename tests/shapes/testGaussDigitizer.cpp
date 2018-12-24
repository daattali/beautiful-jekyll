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
 * @file testGaussDigitizer.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/07/01
 *
 * Functions for testing class GaussDigitizer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/parametric/Ellipse2D.h"
#include "DGtal/shapes/parametric/Flower2D.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/shapes/CDigitalOrientedShape.h"
#include "DGtal/shapes/CDigitalBoundedShape.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class GaussDigitizer.
///////////////////////////////////////////////////////////////////////////////


/** 
 * 
 * Gaussdigitizer is a model of CDigitalBoundedShape and
 * CDigitalOrientedShape.
 * 
 */
bool testConcept()
{
  typedef GaussDigitizer<Z2i::Space,Ellipse2D< Z2i::Space > > Dig; 
  BOOST_CONCEPT_ASSERT((concepts::CDigitalBoundedShape<Dig>));
  BOOST_CONCEPT_ASSERT((concepts::CDigitalOrientedShape<Dig>));
  return true;
}


template <typename Space, typename Shape>
bool
testDigitization( const Shape & aShape, double h,
      const string & fileName )
{
  typedef typename Space::Point Point;
  typedef typename Space::RealPoint RealPoint;
  typedef HyperRectDomain<Space> Domain;
  typedef typename DigitalSetSelector
    < Domain, BIG_DS + HIGH_ITER_DS + HIGH_BEL_DS >::Type MySet;

  // Creates a digitizer on the window (xLow, xUp).
  RealPoint xLow( -5.3, -4.3 );
  RealPoint xUp( 7.4, 4.7 );
  GaussDigitizer<Space,Shape> dig;  
  dig.attach( aShape ); // attaches the shape.
  dig.init( xLow, xUp, h ); 
  
  // The domain size is given by the digitizer according to the window
  // and the step.
  Domain domain = dig.getDomain();
  MySet aSet( domain );
  // Creates a set from the digitizer.
  Shapes<Domain>::digitalShaper( aSet, dig );
  
  // Create cellular space
  typedef Z2i::KSpace KSpace;
  typedef Z2i::SCell SCell;
  KSpace K;
  bool ok = K.init( dig.getLowerBound(), dig.getUpperBound(), true );
 
  if (!ok)
    return false;
  

  SurfelAdjacency<KSpace::dimension> SAdj( true );

 

  // Extracts shape boundary
  SCell bel = Surfaces<KSpace>::findABel( K, dig, 10000 );
  // Getting the consecutive surfels of the 2D boundary
  std::vector<Point> points;
  Surfaces<KSpace>::track2DBoundaryPoints( points, K, SAdj, dig, bel );
  GridCurve<KSpace> gridcurve;
  gridcurve.initFromVector( points );

  // Display all
  Board2D board;
  board.setUnit( LibBoard::Board::UCentimeter );
  board << SetMode( domain.className(), "Paving" )
    << domain << aSet;

  board << SetMode( gridcurve.className(), "Edges" )
  << CustomStyle( bel.className(), 
      new CustomColors( DGtal::Color( 0, 0, 0 ),
            DGtal::Color( 0, 192, 0 ) ) )
  << gridcurve;
  board << SetMode( gridcurve.className(), "Points" )
  << CustomStyle( bel.className(), 
      new CustomColors( DGtal::Color( 255, 0, 0 ),
            DGtal::Color( 200, 0, 0 ) ) )
  << gridcurve;

  board.saveEPS( ( fileName + ".eps" ).c_str() );
  board.saveSVG( ( fileName + ".svg" ).c_str() );
  
  return true;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testGaussDigitizer()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing GaussDigitizer as a Digital Shape functor." );

  typedef Ellipse2D< Z2i::Space > MyEllipse;
  MyEllipse ellipse( 1.2, 0.1, 4.0, 3.0, 0.3 );
  nbok += testDigitization<Z2i::Space,MyEllipse>
    ( ellipse, 1.0, "gauss-ellipse-1" ) ? 1 : 0; 
  nb++;
  nbok += testDigitization<Z2i::Space,MyEllipse>
    ( ellipse, 0.5, "gauss-ellipse-0_5" ) ? 1 : 0; 
  nb++;
  nbok += testDigitization<Z2i::Space,MyEllipse>
    ( ellipse, 0.25, "gauss-ellipse-0_25" ) ? 1 : 0; 
  nb++;

  typedef Flower2D< Z2i::Space > MyFlower;
  MyFlower flower( 0.5, -2.3, 5.0, 0.7, 6, 0.3 );
  nbok += testDigitization<Z2i::Space,MyFlower>
    ( flower, 1.0, "gauss-flower-1" ) ? 1 : 0; 
  nb++;
  nbok += testDigitization<Z2i::Space,MyFlower>
    ( flower, 0.5, "gauss-flower-0_5" ) ? 1 : 0; 
  nb++;
  nbok += testDigitization<Z2i::Space,MyFlower>
    ( flower, 0.25, "gauss-flower-0_25" ) ? 1 : 0; 
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
  trace.beginBlock ( "Testing class GaussDigitizer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testConcept() && testGaussDigitizer(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
