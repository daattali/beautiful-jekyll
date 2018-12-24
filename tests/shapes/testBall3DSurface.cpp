/**
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as
* published by the Free Software Foundation, either version 3 of the
* License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**/

/**
 * @file testBall3DSurface.cpp
 * @ingroup Tests
 * @author Anis Benyoub (\c anis.benyoub@insa-lyon.fr )
 *
 * @date 2012/°6/05
 *
 * Functions for testing class Ball3D.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "DGtal/shapes/parametric/Ball3D.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/io/Color.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;
using namespace Z3i;

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :


int main(int /*argc*/, char** /*argv*/)
{

     
   
  // -------------------------------------------------------------------------- Type declaring
  typedef Space::RealPoint RealPoint;
  typedef Ball3D<Space> EuclideanShape;

  bool test = true;
   
  // -------------------------------------------------------------------------- Creating the shape
  double  radius = 10;
  RealPoint c1(0, 0, 0 );
  EuclideanShape ball1( c1, radius );	

  trace.beginBlock("Arc length computing");
  double arcExp = ball1.arclength( make_pair(0.0,0.0), make_pair(0.0,M_PI) ,500 );
  double arcTheo = M_PI*radius;
  trace.info() <<"Computed arc length: "<< arcExp <<endl;
  trace.info() << "Theoric arc length: "<< arcTheo << endl;
  if(fabs(arcTheo- arcExp) < 0.1)
    {
      trace.info() <<"The arc length has a good value"<<endl;	
    }
  else
    {
      test=false;
    }
  trace.endBlock();
  
  trace.beginBlock("Surface length computing");
  double surfaceExp = ball1.surfacelength( make_pair(0.0,0.0), make_pair(M_PI*2,M_PI) ,500 );
  double surfaceTheo = 4.0*M_PI*radius*radius;
  trace.info() <<"Computed surface length: "<< surfaceExp <<endl;
  trace.info() << "Theoric surface length: "<< surfaceTheo << endl;
  if(fabs(surfaceExp- surfaceTheo) < 0.1)
    {
      trace.info() <<"The surface has a good value"<<endl;	
    }
  else
    {
      test=false;
    }
  trace.endBlock();

    
  if (test)
    return 0;
  else
    return -1;
}
// //
///////////////////////////////////////////////////////////////////////////////


