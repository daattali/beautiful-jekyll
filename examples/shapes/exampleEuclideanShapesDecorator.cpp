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
 * @file shapes/exampleEuclideanShapesDecorator.cpp
 * @ingroup Examples
 * @author Jérémy Levallois (\c jeremy.levallois@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), INSA-Lyon, France
 * LAboratoire de MAthématiques - LAMA (CNRS, UMR 5127), Université de Savoie, France
 *
 * @date 2012/12/17
 *
 * An example file named exampleEuclideanShapesDecorator.
 *
 * This file is part of the DGtal library.
 */

//! [EuclideanShapesDecoratorUsageFull]

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

// Shape construction
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/images/ImageHelper.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/EuclideanShapesDecorator.h"

// Drawing
#include "DGtal/io/boards/Board2D.h"

///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    trace.beginBlock ( "Example EuclideanShapesDecorator" );
    trace.info() << "Args:";
    for ( int i = 0; i < argc; ++i )
        trace.info() << " " << argv[ i ];
    trace.info() << endl;

    /// Construction of the shape + digitalization
    double h = 1.0;

    //! [EuclideanShapesDecoratorUsage]
    typedef ImplicitBall< Z2i::Space > MyEuclideanShapeA;
    typedef ImplicitBall< Z2i::Space > MyEuclideanShapeB;
    MyEuclideanShapeA shapeA( Z2i::RealPoint( 0.0, 0.0 ), 15 );
    MyEuclideanShapeB shapeB( Z2i::RealPoint( 0.0, 0.0 ), 10 );
    MyEuclideanShapeB shapeC( Z2i::RealPoint( -5.0, 0.0 ), 5 );

    typedef EuclideanShapesCSG< MyEuclideanShapeA, MyEuclideanShapeB > Minus;
    Minus s_minus ( shapeA );
    s_minus.minus( shapeB );
    s_minus.plus( shapeC );
    //! [EuclideanShapesDecoratorUsage]

    typedef GaussDigitizer< Z2i::Space, Minus > MyGaussDigitizer;
    MyGaussDigitizer digShape;
    digShape.attach( s_minus );
    digShape.init( s_minus.getLowerBound(), s_minus.getUpperBound(), h );
    Z2i::Domain domainShape = digShape.getDomain();
    Z2i::DigitalSet aSet( domainShape );
    Shapes<Z2i::Domain>::digitalShaper( aSet, digShape );

    Board2D board;
    board << SetMode( domainShape.className(), "Paving" )
          << domainShape;

    Color dorange ( 255,  136,  0,  220 );

    board << CustomStyle( aSet.className(), new CustomFillColor( dorange ));
    board << aSet;

    board.saveSVG ( "example-EuclideanShapesDecorator.svg" );

    trace.endBlock();
    return 0;
}

//! [EuclideanShapesDecoratorUsageFull]
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
