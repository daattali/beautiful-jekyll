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
 * @file testStandardDSLQ0-LSB-reversedSmartDSS-benchmark.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class SternBrocot.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/LightSternBrocot.h"
#include "DGtal/arithmetic/Pattern.h"
#include "DGtal/arithmetic/StandardDSLQ0.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LightSternBrocot.
///////////////////////////////////////////////////////////////////////////////

template <typename DSL>
bool checkSubStandardDSLQ0( const DSL & D,
                            const typename DSL::Point & A, 
                            const typename DSL::Point & B ) 
{
  DSL S = D.reversedSmartDSS( A, B );
  std::cout << D.a() << " " << D.b() << " " << D.mu() << " "
            << S.a() << " " << S.b() << " " << S.mu() << " "
            << A[0] << " " << A[1] << " " << B[0] << " " << B[1]
            << std::endl;
  return true;
}

template <typename Fraction>
bool testSubStandardDSLQ0( unsigned int nbtries, 
                           typename Fraction::Integer moda, 
                           typename Fraction::Integer modb, 
                           typename Fraction::Integer modx )
{
  typedef StandardDSLQ0<Fraction> DSL;
  typedef typename Fraction::Integer Integer;
  typedef typename DSL::Point Point;
  IntegerComputer<Integer> ic;

  std::cout << "# a b mu a1 b1 mu1 Ax Ay Bx By" << std::endl;
  for ( unsigned int i = 0; i < nbtries; ++i )
    {
      Integer a( rand() % moda + 1 );
      Integer b( rand() % modb + 1 );
      if ( ic.gcd( a, b ) == 1 )
        {
          for ( Integer mu = 0; mu < 5; ++mu )
            {
              DSL D( a, b, rand() % (moda+modb) );
              for ( Integer x = 0; x < 10; ++x )
                {
                  Integer x1 = rand() % modx;
                  Integer x2 = x1 + 1 + ( rand() % modx );
                  Point A = D.lowestY( x1 );
                  Point B = D.lowestY( x2 );
                  checkSubStandardDSLQ0<DSL>( D, A, B );
                }
            }
        }
    }
  return true;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv)
{
  typedef LightSternBrocot<DGtal::int64_t,DGtal::int32_t> SB;
  typedef SB::Fraction Fraction;
  typedef Fraction::Integer Integer;
  unsigned int nbtries = ( argc > 1 ) ? atoi( argv[ 1 ] ) : 10000;
  Integer moda = ( argc > 2 ) ? atoll( argv[ 2 ] ) : 12000;
  Integer modb = ( argc > 3 ) ? atoll( argv[ 3 ] ) : 12000;
  Integer modx = ( argc > 4 ) ? atoll( argv[ 4 ] ) : 1000;
  testSubStandardDSLQ0<Fraction>( nbtries, moda, modb, modx );
  return true;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
