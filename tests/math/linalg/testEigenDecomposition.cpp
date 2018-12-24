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
 * @file testEigenDecomposition.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2014/04/02
 *
 * Functions for testing class testEigenDecomposition.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/linalg/EigenDecomposition.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class testEigenDecomposition.
///////////////////////////////////////////////////////////////////////////////
/**
 * Example of a test. To be completed.
 *
 */
bool testEigenDecomposition()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  typedef EigenDecomposition<2,double> Eigen2;
  typedef Eigen2::Vector Vector2;
  typedef Eigen2::Matrix Matrix2;
  
  trace.beginBlock ( "Testing block ..." );
  // [4 1]
  // [1 2]
  Matrix2 A;
  A.setComponent( 0, 0, 4 );
  A.setComponent( 0, 1, 1 );
  A.setComponent( 1, 0, 1 );
  A.setComponent( 1, 1, 2 );
  Matrix2 P;
  Vector2 v;
  Eigen2::getEigenDecomposition( A, P, v );
  trace.info() << "Input matrix: " << A << std::endl;
  trace.info() << "Eigenvectors: " << P << std::endl;
  trace.info() << "Eigenvalues: " << v << std::endl;
  Vector2 V0 = P.column( 0 );
  Vector2 V1 = P.column( 1 );
  Vector2 V0_exp( 0.3826834323650898, -0.9238795325112868 );
  Vector2 V1_exp( 0.9238795325112868, 0.3826834323650898);
  double v0_exp = 1.585786437626905;
  double v1_exp = 4.414213562373095;
  double error_V0 = (V0-V0_exp).norm();
  double error_V1 = (V1-V1_exp).norm();
  double error_v0 = fabs( v[0] - v0_exp );
  double error_v1 = fabs( v[1] - v1_exp );
  trace.info() << "error_V0 = " << error_V0 << std::endl;
  trace.info() << "error_V1 = " << error_V1 << std::endl;
  trace.info() << "error_v0 = " << error_v0 << std::endl;
  trace.info() << "error_v1 = " << error_v1 << std::endl;
  double epsilon = 1e-10;
  ++nb; nbok += error_V0 < epsilon ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "error_V0 < epsilon, i.e. " <<  error_V0 << " < " << epsilon << std::endl;
  ++nb; nbok += error_V1 < epsilon ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "error_V1 < epsilon, i.e. " <<  error_V1 << " < " << epsilon << std::endl;
  ++nb; nbok += error_v0 < epsilon ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "error_v0 < epsilon, i.e. " <<  error_v0 << " < " << epsilon << std::endl;
  ++nb; nbok += error_v1 < epsilon ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "error_v1 < epsilon, i.e. " <<  error_v1 << " < " << epsilon << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class testEigenDecomposition" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testEigenDecomposition(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
