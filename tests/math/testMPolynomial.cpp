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
 * @file testMPolynomial.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/12
 *
 * Functions for testing class Signal.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/math/MPolynomial.h"
#include "DGtal/io/readers/MPolynomialReader.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class Signal.
///////////////////////////////////////////////////////////////////////////////

/**
   Durchblick polynomial: x3y+xz3+y3z+z3+5z
*/
template <typename Ring>
MPolynomial<3, Ring, std::allocator<Ring> >
durchblick()
{
  MPolynomial<3, Ring, std::allocator<Ring> > p
    = mmonomial<Ring>( 3, 1, 0 )
    + mmonomial<Ring>( 1, 0, 3 )
    + mmonomial<Ring>( 0, 3, 1 )
    + mmonomial<Ring>( 0, 0, 3 )
    + ((Ring)5) * mmonomial<Ring>( 0, 0, 1 );
  return p;
}

double
durchblickC( const double & x, const double & y, const double  z )
{
  return x*x*x*y + x*z*z*z + y*y*y*z + z*z*z + 5.0 * z;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testMPolynomialSpeed( double step = 0.01 )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock ( "Testing block ... Evaluation speed of mpolynomials (naive)" );
  trace.info() << setprecision( 15 ) <<  "step is " << step << std::endl;
  trace.info() << "approximately " << 8.0/(step*step*step) << " computations." << std::endl;
  MPolynomial<3, double> P = durchblick<double>();
  double total = 0.0;
  for ( double x = -1.0; x < 1.0; x += step )
    {
      for ( double y = -1.0; y < 1.0; y += step )
        {
          for ( double z = -1.0; z < 1.0; z += step )
            total += P(x)(y)(z);
        }
    }
  trace.info() << "Total = " << total << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block ... Evaluation speed of mpolynomials" );
  //MPolynomial<3, double> P = durchblick<double>();
  double total1 = 0.0;
  for ( double x = -1.0; x < 1.0; x += step )
    {
      MPolynomial<2, double> PX = P( x );
      for ( double y = -1.0; y < 1.0; y += step )
        {
          MPolynomial<1, double> PXY = PX( y );
          for ( double z = -1.0; z < 1.0; z += step )
            total1 += PXY( z );
        }
    }
  trace.info() << "Total1 = " << total1 << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block ... Same computation in C." );
  double total2 = 0.0;
  for ( double x = -1.0; x < 1.0; x += step )
    {
      for ( double y = -1.0; y < 1.0; y += step )
        {
          for ( double z = -1.0; z < 1.0; z += step )
            total2 += durchblickC( x, y, z );
        }
    }
  trace.info() << "Total2 = " << total2 << std::endl;
  trace.endBlock();
  nbok += fabs( total1 - total ) < 1e-8 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "fabs( total1 - total ) < 1e-8" << std::endl;
  nbok += fabs( total2 - total ) < 1e-8 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "fabs( total2 - total ) < 1e-8" << std::endl;

  trace.info() << "For information, ImaGene::Polynomial3 takes 164ms for step=0.01 and 1604ms for step = 0.005." << std::endl;
  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testMPolynomial()
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );

  MPolynomial<2, int> f = mmonomial<int>(1, 2) + 3 * mmonomial<int>(4, 5);
  trace.info() << f << std::endl;
  int e = f(4)(2);
  trace.info() << e << std::endl;
  nbok += e == 24592 ? 1 : 0; 
  nb++;
  trace.info() << derivative<1>(f) << std::endl;
  MPolynomial<1, int> g = f(2), h = f(3);
  trace.info() << g << " and " << h << std::endl;
  trace.info() << gcd<double>(g, h) << std::endl; // cast polynomials to MPolynomial<1, double> first; otherwise,
  // result will be incorrect since int is not a field
  trace.info() << gcd(g, h) << std::endl; // to prove our point, check for yourself that the result is
  // X_0^5 instead of X_0^2
  nbok += gcd<double>(g,h) == mmonomial<double>(2) ? 1 : 0; 
  nb++;
  MPolynomial<1, double> l = f(mmonomial<double>(1) - 1)(mmonomial<double>(1) - 2);
  trace.info() << l << std::endl;
  trace.info() << derivative<0>(l) << std::endl;
  trace.info() << gcd(l, derivative<0>(l)) << " (gcd of two previous polys is 1)" << std::endl;
  nbok += gcd(l, derivative<0>(l)) == 1.0 * mmonomial<double>(0) ? 1 : 0; 
  nb++;
  trace.info() << "Durchblick (x3y+xz3+y3z+z3+5z)= " << durchblick<double>() << std::endl;
  trace.endBlock();
  MPolynomial<3, double> Q = mmonomial<double>( 0, 0, 0 )
    + mmonomial<double>( 1, 2, 0 ) + mmonomial<double>( 4, 1, 1 );
  std::cout << "Q(x,y,z)=1+xy^2+x^4yz = " << Q << std::endl;
  std::cout << "         degree       = " << Q.degree() << std::endl;
  std::cout << "         leading      = " << Q.leading() << std::endl;
  std::cout << "         Q[0]         = " << Q[ 0 ] << std::endl;
  std::cout << "         Q[1]         = " << Q[ 1 ] << std::endl;
  std::cout << "         Q[2]         = " << Q[ 2 ] << std::endl;
  std::cout << "         Q[3]         = " << Q[ 3 ] << std::endl;
  std::cout << "         Q[4]         = " << Q[ 4 ] << std::endl;
  std::cout << "         dQ/dx        = " << derivative<0>(Q) << std::endl;
  std::cout << "         dQ/dy        = " << derivative<1>(Q) << std::endl;
  std::cout << "         dQ/dz        = " << derivative<2>(Q) << std::endl;
  MPolynomial<3,double> P;
  P = Xe_k<3,double>( 2, 7 ) + Xe_k<3,double>( 1, 3 );
  trace.info() << "P=" << P << std::endl;
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Testing class MPolynomial" );

  bool res = testMPolynomial()
    && testMPolynomialSpeed( 0.05 );
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
