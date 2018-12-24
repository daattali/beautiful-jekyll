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
 * @file shapes/exampleParametricShapes.cpp
 * @ingroup Examples
 * @author Adrien Krähenbühl (\c krahenbuhl@unistra.fr )
 * Laboratoire des sciences de l'ingénieur, de l'informatique et de l'imagerie - ICube (UMR 7357), France
 *
 * @date 2018/08/14
 *
 * An example file named exampleParametricShapes.
 *
 * This file is part of the DGtal library.
 */

//! [ParametricShapesUsageFull]

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <DGtal/base/Common.h>

// Shape construction
#include <DGtal/shapes/Shapes.h>
#include <DGtal/shapes/GaussDigitizer.h>
#include <DGtal/shapes/parametric/Astroid2D.h>

// Drawing
#include <DGtal/io/boards/Board2D.h>

using namespace DGtal;
///////////////////////////////////////////////////////////////////////////////

int main( int argc, char** argv )
{
    trace.beginBlock ( "Example Parametric Shapes" );

    typedef Z2i::Space Space;

    /* This example consider the Lemniscate shape.
     *
     * To test other shapes, replace Astroid2D by the desirated shape
     * and adapt parameters of the shape constructor.
     */
    typedef Astroid2D<Space> MyShape;
    MyShape shape( 0, 0, 10, 5 );

    // Grid step parameter for the Gauzz digitization
    double h = 1;

    // Gauss digitization
    typedef GaussDigitizer< Z2i::Space, MyShape > MyGaussDigitizer;
    MyGaussDigitizer dig;
    dig.attach( shape );
    dig.init( shape.getLowerBound(), shape.getUpperBound(), h );

    // Create the digital point set from the digitizer
    Z2i::DigitalSet aSet( dig.getDomain() );
    Shapes<Z2i::Domain>::digitalShaper( aSet, dig );

    // Draw the digitized shape in a file named "shape.svg"
    Board2D board;
    board << aSet;
    board << CustomStyle( aSet.className(), new CustomFillColor(Color::Black));
    board.saveSVG( "shape.svg" );

    trace.endBlock();
    return 0;
}

//! [ParametricShapesUsageFull]
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
