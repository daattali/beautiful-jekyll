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
 * @file testDigitalShapesDecorator.cpp
 * @ingroup Tests
 * @author Jérémy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2012/12/07
 *
 * Functions for testing class DigitalShapesDecorator.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/shapes/GaussDigitizer.h"

/////// UnaryOperators
#include "DGtal/shapes/DigitalShapesDecorator.h"

/////// Shapes 2D
#include "DGtal/shapes/parametric/Ball2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class DigitalShapesDecorator.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testDigitalShapesDecorator()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing Unary operation on digital shapes ..." );

  typedef Ball2D< Z2i::Space > ShapeA;
  typedef GaussDigitizer< Z2i::Space, ShapeA > MyGaussDigitizerA;

  typedef ShapeA::Point Point;

  double h = 0.5;

  ShapeA shapeA(-2.501, 0.0, 2.5013);
  ShapeA shapeB(2, 0.0, 2.5013);
  ShapeA shapeC(0.0, 0.0, 2.5);

  MyGaussDigitizerA digShapeA;
  digShapeA.attach( shapeA );
  digShapeA.init( shapeA.getLowerBound(), shapeA.getUpperBound(), h );

  MyGaussDigitizerA digShapeB;
  digShapeB.attach( shapeB );
  digShapeB.init( shapeB.getLowerBound(), shapeB.getUpperBound(), h );

  MyGaussDigitizerA digShapeC;
  digShapeC.attach( shapeC );
  digShapeC.init( shapeC.getLowerBound(), shapeC.getUpperBound(), h );


  typedef DigitalShapesCSG< MyGaussDigitizerA, MyGaussDigitizerA > CSG;
  CSG s_union ( digShapeA );
  s_union.plus( digShapeB );

  CSG s_intersec ( digShapeA );
  s_intersec.plus( digShapeB );
  s_intersec.intersection( digShapeC );

  CSG s_minus ( digShapeA );
  s_minus.minus( digShapeC );


  nbok += (( s_union.orientation( Point( -12, 0 )) == INSIDE )
          || ( s_union.orientation( Point( -12, 0 )) == ON  ))? 0 : 1;
  nbok += (( s_union.orientation( Point( 0, 0 )) == INSIDE )
          || ( s_union.orientation( Point( 0, 0 )) == ON  ))? 1 : 0;
  nbok += (( s_union.orientation( Point( 10, 0 )) == INSIDE )
          || ( s_union.orientation( Point( 10, 0 )) == ON  ))? 0 : 1;
  nbok += (( s_union.orientation( Point( 9, 0 )) == INSIDE )
          || ( s_union.orientation( Point( 9, 0 )) == ON  ))? 1 : 0;
  nbok += (( s_union.orientation( Point( -10, 0 )) == INSIDE )
          || ( s_union.orientation( Point( -10, 0 )) == ON  ))? 1 : 0;


  nbok += (( s_intersec.orientation( Point( -6, 0 )) == INSIDE )
          || ( s_intersec.orientation( Point( -6, 0 )) == ON  ))? 0 : 1;
  nbok += (( s_intersec.orientation( Point( 4, 0 )) == INSIDE )
          || ( s_intersec.orientation( Point( 4, 0 )) == ON  ))? 1 : 0;
  nbok += (( s_intersec.orientation( Point( 6, 0 )) == INSIDE )
          || ( s_intersec.orientation( Point( 6, 0 )) == ON  ))? 0 : 1;
  nbok += (( s_intersec.orientation( Point( 0, 5 )) == INSIDE )
          || ( s_intersec.orientation( Point( 0, 5 )) == ON  ))? 0 : 1;


  nbok += (( s_minus.orientation( Point( -9, 0 )) == INSIDE )
          || ( s_minus.orientation( Point( -9, 0 )) == ON  ))? 1 : 0;
  nbok += (( s_minus.orientation( Point( -2, 0 )) == INSIDE )
          || ( s_minus.orientation( Point( -2, 0 )) == ON  ))? 0 : 1;
  nbok += (( s_minus.orientation( Point( 0, 2 )) == INSIDE )
          || ( s_minus.orientation( Point( 0, 2 )) == ON  ))? 0 : 1;
  nbok += (( s_minus.orientation( Point( -8, 0 )) == INSIDE )
          || ( s_minus.orientation( Point( -8, 0 )) == ON  ))? 1 : 0;

  nb = 13;


  trace.info() << "(" << nbok << "/" << nb << ") "
               << "true == true" << std::endl;
  trace.endBlock();
  return  nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class DigitalShapesDecorator" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << std::endl;

  bool res = testDigitalShapesDecorator(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << std::endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
