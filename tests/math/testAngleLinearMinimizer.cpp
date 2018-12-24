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
 * @file testAngleLinearMinimizer.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/09/01
 *
 * Functions for testing class AngleLinearMinimizer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/AngleLinearMinimizer.h"
#include "DGtal/io/boards/Board2D.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class AngleLinearMinimizer.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testAngleLinearMinimizer()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing AngleLinearMinimizer ." );
   
  AngleLinearMinimizer alm;
  alm.init(10);
  alm.setIsCurveOpen(true);
  double valDec [10] = {0.8, 0.3, -0.2, -0.2, -0.1, -0.3, -3.0, -6.0,  -7.0, -8.0};
  double valDecMin [10] = {-0.5, -0.2, -0.5, -0.2, -0.1, -1.0, -1.2, -0.5,  -0.3, -0.2};
  double valDecMax [10] = {0.9, 0.3, 0.2, 1.2, 0.4, 1.0, 0.5, 0.2,  0.1, 0.3};

  for(unsigned int i=0; i<10; i++){
    AngleLinearMinimizer::ValueInfo &vi= alm.rw(i);
    double val = i + valDec[i];
    vi.value = val;
    vi.oldValue = val;
    vi.min = val + valDecMin[i];
    vi.max = val + valDecMax[i];
    vi.distToNext = 4.0;    
    alm.rw(i)=vi;
  }
  //! [optimization]
  double delta= alm.optimize();
  double aPrecision=0.00001;
  while(delta >aPrecision){
    delta= alm.optimize();
    cerr << "sum of displacements " << delta << endl; 
  }
  //! [optimization]
  cout << "# index distPos valInit valOpt valMin valMax  " << endl;
  double currentPos=0.0;
  cout << -1 << " "<< -4 << " " << 9+valDec[9]  <<  " " << alm.ro(9).value
       << " " << alm.ro(9).min << " " << alm.ro(9).max << endl ;
      
  for(unsigned int i=0; i<10; i++){
    AngleLinearMinimizer::ValueInfo vi= alm.ro(i);
    cout << i << " "<< currentPos << " " << i+ valDec[i] <<  " " << vi.value
	 << " " << vi.min << " " << vi.max << endl ;
    currentPos+=vi.distToNext;    
  }
  nbok += (abs(1.59999-alm.ro(0).value)<0.00001) && (abs(1.6-alm.ro(1).value)<0.00001) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "true == true" << std::endl;
 
  Board2D aBoard;
  aBoard << alm;
  aBoard.saveEPS("tmp.eps");
  trace.endBlock();
  return nbok == nb;
}




///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class AngleLinearMinimizer" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testAngleLinearMinimizer(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
