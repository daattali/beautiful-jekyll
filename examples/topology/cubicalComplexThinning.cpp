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
 * @file cubicalComplexThinning.cpp
 * @ingroup Examples
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, France
 *
 * @date 2016/01/16
 *
 * An example file named cubicalComplexThinning.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "ConfigExamples.h"
#include "DGtal/helpers/StdDefs.h"
// Cellular grid
#include "DGtal/topology/CubicalComplex.h"
//! [include]
#include "DGtal/topology/ParDirCollapse.h"
//! [include]
// Shape construction
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/EuclideanShapesDecorator.h"
#include "DGtal/shapes/parametric/Flower2D.h"
// Drawing
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z2i;

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

template <typename CC>
void drawComplex ( Board2D & board, CC & complex )
{
    board.clear();
    typedef typename CC::CellMapConstIterator CellMapConstIterator;
    for ( Dimension d = 0; d <= 2; ++d )
        for ( CellMapConstIterator it = complex.begin( d ), itE = complex.end( d );
                it != itE; ++it )
        {
            if ( d == 0 )
                board << CustomStyle( it->first.className(),
                        new CustomColors( Color( 0, 0, 0 ),
                            Color( 0, 0, 0 ) ) );
            else if ( d == 1 )
                board << CustomStyle( it->first.className(),
                        new CustomColors( Color( 200, 0, 0 ),
                            Color( 100, 255, 100 ) ) );
            else
                board << CustomStyle( it->first.className(),
                        new CustomColors( Color( 0, 0, 200 ),
                            Color( 100, 255, 100 ) ) );
            board << it->first;
        }
}

///////////////////////////////////////////////////////////////////////////////
//                                                                           //


int main( int, char** )
{
  typedef map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map >     CC;
  Board2D board;
  KSpace K;
  CC complex ( K );
//! [create]
  ParDirCollapse < CC > thinning ( K );
//! [create]
  trace.beginBlock ( "ParDirCollapse -- 2 iterations." );
    getComplex< CC, KSpace > ( complex, K );
    drawComplex<CC> ( board, complex );
    board.saveEPS ( "ComplexBeforeThinning.eps" );
//! [init]
    thinning.attach ( &complex );
//! [init]

//! [thinn]
    thinning.eval ( 2 );
//! [thinn]
    drawComplex<CC> ( board, complex );
    board.saveEPS ( "ParDirCollapse_2.eps" );
  trace.endBlock();

  trace.beginBlock ( "ParDirCollapse -- collapseSurface." );
    getComplex< CC, KSpace > ( complex, K );
    thinning.attach ( &complex );
//! [thinnSurface]
    thinning.collapseSurface ();
//! [thinnSurface]
    drawComplex<CC> ( board, complex );
    board.saveEPS ( "ParDirCollapse_collapseSurface.eps" );
  trace.endBlock();

  trace.beginBlock ( "ParDirCollapse -- collapseIsthmus." );
    getComplex< CC, KSpace > ( complex, K );
    thinning.attach ( &complex );
//! [thinnIsthmus]
    thinning.collapseIsthmus ();
//! [thinnIsthmus]
    drawComplex<CC> ( board, complex );
    board.saveEPS ( "ParDirCollapse_collapseIsthmus.eps" );
  trace.endBlock();
  return 0;
}
