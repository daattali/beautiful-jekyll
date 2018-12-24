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
 * @file
 * @ingroup Tests
 * @author Kacper Pluta (\c kacper.pluta@esiee.fr )
 * Laboratoire d'Informatique Gaspard-Monge - LIGM, A3SI, France
 *
 * @date 2015/11/03
 *
 * Functions for testing class digitalSetToCubicalComplexes.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtal/helpers/StdDefs.h"
// Cellular grid converter
#include "DGtal/topology/CubicalComplex.h"
// Shape construction
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/EuclideanShapesDecorator.h"
#include "DGtal/shapes/parametric/Flower2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace functors;
using namespace Z2i;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class digitalSetToCubicalComplexes.
///////////////////////////////////////////////////////////////////////////////
class testDigitalSetToCellularGridConverter
{
  typedef Flower2D< Space > MyEuclideanShape;
  typedef map<Cell, CubicalCellData>   Map;
  typedef CubicalComplex< KSpace, Map > CC;  
  typedef GaussDigitizer< Space, MyEuclideanShape > MyGaussDigitizer;
private:
  KSpace K;
  MyGaussDigitizer digShape;
public:
  testDigitalSetToCellularGridConverter () {}
  bool extractCells()
  {
    MyEuclideanShape shape( RealPoint( 0.0, 0.0 ), 16, 5, 5, M_PI_2/2. );
    digShape.attach( shape );
    digShape.init ( shape.getLowerBound(), shape.getUpperBound(), 1.0 );
    Domain domainShape = digShape.getDomain();
    K.init (  domainShape.lowerBound(), domainShape.upperBound(), true );
    DigitalSet aSet ( domainShape );
    Shapes<Domain>::digitalShaper ( aSet, digShape );
    
    CC complex ( K );
    complex.construct < DigitalSet > ( aSet );
    return true;
  }
};
///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /* argc */, char** /* argv */ )
{
    bool res = true;
    testDigitalSetToCellularGridConverter test;
    trace.beginBlock ( "DigitalSetToCellularGridConverter" );
        trace.beginBlock ( "Testing extraction of 0D cells" );
          res &= test.extractCells();
        trace.endBlock();
    trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
    trace.endBlock();
    return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
