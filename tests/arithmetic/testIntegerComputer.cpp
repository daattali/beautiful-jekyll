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
 * @file testIntegerComputer.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class IntegerComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/arithmetic/IntegerComputer.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class IntegerComputer.
///////////////////////////////////////////////////////////////////////////////

template <typename Integer>
bool testGCD( const IntegerComputer<Integer> & ic )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer a = rand();
  Integer b = rand();
  Integer g = ic.gcd( a, b );
  trace.info() << "GCD(" << a << "," << b << ")" 
               << " = " << g << std::endl;
  Integer ra = a % g;
  Integer rb = b % g;
  nbok += ic.isZero( ra ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << a << " % " << g << " == 0" << std::endl;
  nbok += ic.isZero( rb ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << b << " % " << g << " == 0" << std::endl;
  a /= g; b /= g;
  g = ic.gcd( a, b );
  nbok += g == Integer( 1 ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "GCD(" << a << "," << b << ") == 1" << std::endl;
  Integer c = rand(); 
  ++c; // avoids zero.
  a *= c; b *= c;
  ic.getGcd( g, a, b );
  nbok += g == c ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "GCD(" << a << "," << b << ") == " << c << std::endl;
  return nbok == nb;
}

template <typename Integer>
bool testCFrac( const IntegerComputer<Integer> & ic )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer a = rand();
  Integer b = rand();
  Integer g = ic.gcd( a, b );
  trace.info() << "a / b = " << a << " / " << b << std::endl;
  std::vector<Integer> quotients;
  Integer g2 = ic.getCFrac( quotients, a, b );
  nbok += g == g2 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << g << " == " << g2 << std::endl;
  trace.info() << a << " / " << b << " = ";
  for ( typename std::vector<Integer>::const_iterator it = quotients.begin(),
          it_end = quotients.end(); it != it_end; ++it )
    trace.info() << *it;
  trace.info() << std::endl;
  double da = NumberTraits<Integer>::castToDouble( a );
  double db = NumberTraits<Integer>::castToDouble( b );
  double q = floor( da / db );
  nbok += Integer( (int) q ) == quotients[ 0 ] ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << q << " == " << quotients[ 0 ] << std::endl;
  typedef typename IntegerComputer<Integer>::Point2I Point2I;
  Point2I p = ic.convergent( quotients, quotients.size() );
  nbok += p[ 0 ] == ( a / g ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "convergent p[ 0 ] " << p[ 0 ] << " == a / g " << std::endl;
  nbok += p[ 1 ] == ( b / g ) ? 1 : 0;
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "convergent p[ 1 ] " << p[ 1 ] << " == b / g " << std::endl;
  return nbok == nb;
}

template <typename Integer>
bool testCeilFloorDiv( const IntegerComputer<Integer> & ic )
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer a = rand();
  a -= rand();
  Integer b = rand();
  b -= rand(); 
  if ( ic.isZero( b ) ) ++b;
  trace.info() << "- a / b = " << a << " / " << b << std::endl;
  Integer fl = ic.floorDiv( a, b );
  Integer ce = ic.ceilDiv( a, b );
  Integer fl2, ce2;
  ic.getFloorCeilDiv( fl2, ce2, a, b );
  nbok += fl == fl2 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "fl == fl2 " << fl2 << std::endl;
  nbok += ce == ce2 ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "ce == ce2 " << ce2 << std::endl;
  Integer m = a % b;
  nbok += ( ( m == 0 ) && ( fl == ce ) ) || ( fl + 1 == ce ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "( ( m == 0 ) && ( fl == ce ) ) || ( fl+1 == ce )"
               << std::endl;
  return nbok == nb;
}

template <typename Integer>
bool testExtendedEuclid( const IntegerComputer<Integer> & ic )
{
  typedef typename IntegerComputer<Integer>::Point2I Point2I;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer a = rand();
  Integer b = rand();
  Integer g = ic.gcd( a, b );
  trace.info() << "a / b = " << a << " / " << b 
               << " gcd=" << g << std::endl;
  Point2I v = ic.extendedEuclid( a, b, g );
  trace.info() << "Bezout = " << v[ 0 ] << "," << v[ 1 ] << std::endl;
  Integer rem = a * v[ 0 ] + b * v[ 1 ];
  nbok += rem == g ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "a * v[ 0 ] + b * v[ 1 ] == g " 
               << "(" << rem << " == " << g << ")" << std::endl;
  return nbok == nb;
}

template <typename Integer>
bool testCoefficientIntersection( const IntegerComputer<Integer> & ic )
{
  typedef typename IntegerComputer<Integer>::Point2I Point2I;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Point2I p, N;
  Integer c;
  p = Point2I( rand(), rand() );
  N = Point2I( rand() , rand() );
  c = rand() * rand();
  Point2I u( rand() / 100, rand() / 100);
  trace.info() << "p = " << p << std::endl;
  trace.info() << "u = " << u << std::endl;
  trace.info() << "N = " << N << std::endl;
  trace.info() << "c = " << c << std::endl;
  Integer fl, ce;
  ic.getCoefficientIntersection( fl, ce, p, u, N, c );
  trace.info() << "fl = " << fl << ", ce = " << ce << std::endl;
  Point2I p1 = p + (u * fl);
  Point2I p2 = p + (u * ce);
  Integer c1 = ic.dotProduct( p1, N );
  Integer c2 = ic.dotProduct( p2, N );
  trace.info() << "c1 = " << c1
               << " <= c = " << c
               << " <= c2 = " << c2 << std::endl;
  nbok += ( ( c1 == c2 ) && ( c == c1 ) )
    || ( ( c1 <= c ) && ( c < c2 ) ) ? 1 : 0; 
  nb++;
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << "( ( c1 == c2 ) && ( c == c1 ) ) || ( ( c1 <= c ) && ( c < c2 ) )" << std::endl;
  return nbok == nb;
}

template <typename Integer>
bool testValidBezout( const IntegerComputer<Integer> & ic )
{
  typedef typename IntegerComputer<Integer>::Point2I Point2I;
  typedef typename IntegerComputer<Integer>::Vector2I Vector2I;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Vector2I v;
  Point2I A( rand(), rand() );
  Vector2I u( rand() / 100, rand() / 100 );
  ic.reduce( u );
  Vector2I N( rand(), rand() );
  Vector2I N2( rand(), rand() );
  Integer c = rand() * rand();
  Integer c2 = rand() * rand();
  trace.info() << "A = " << A << std::endl;
  trace.info() << "u = " << u << std::endl;
  trace.info() << "N = " << N << std::endl;
  trace.info() << "c = " << c << std::endl;
  trace.info() << "N2 = " << N2 << std::endl;
  trace.info() << "c2 = " << c2 << std::endl;
  ic.getValidBezout ( v,
                      A, u, N, c, N2, c2, true );
  trace.info() << "-> v = " << v << std::endl;
  Integer a0 = ic.crossProduct(u,v);
  nbok += ( ic.abs( a0 ) == 1 ) ? 1 : 0;
  ++nb;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << " v^u = " << a0 << " == +/- 1 " << std::endl;
  // (A+v).N    <= c , (A+v).N2   <= c2, (A+v+u).N2 >  c2.
  // Integer a1 = ic.dotProduct( A+v, N );
  Integer a2 = ic.dotProduct( A+v, N2 );
  Integer a3 = ic.dotProduct( A+v+u, N2 );
  // nbok += a1 <= c ? 1 : 0;
  // ++nb;
  // trace.info() << "(" << nbok << "/" << nb << ") "
  //              << "(A+v).N = " << a1
  //              << " <= c = " << c << std::endl;
  nbok += a2 <= c2 ? 1 : 0;
  ++nb;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "(A+v).N2 = " << a2
               << " <= c = " << c2 << std::endl;
  nbok += a3 > c2 ? 1 : 0;
  ++nb;
  trace.info() << "(" << nbok << "/" << nb << ") "
               << "(A+v+u).N2 = " << a2
               << " > c2 = " << c2 << std::endl;
  return nbok == nb;
}

/**
 * Example of a test. To be completed.
 *
 */
bool testIntegerComputer()
{
  unsigned int nbtests = 50;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef BigInteger Integer;
  IntegerComputer<Integer> ic;
  trace.beginBlock ( "Testing block: multiple random gcd." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testGCD<Integer>( ic ) ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") gcd tests." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block: multiple random cfrac." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testCFrac<Integer>( ic ) ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") cfrac tests." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block: multiple ceil floor division." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testCeilFloorDiv<Integer>( ic ) ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") ceil floor division." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block: multiple Bezout / extended euclid: ax+by= gcd(a,b)." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testExtendedEuclid<Integer>( ic ) ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") Bezout / extended euclid." << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block: multiple coefficient intersection." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testCoefficientIntersection( ic ) ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") coefficient intersection." << std::endl;
  trace.endBlock();
  
  trace.beginBlock ( "Testing block: multiple valid bezout." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testValidBezout( ic ) ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") valid bezout." << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Testing class IntegerComputer" );
  bool res = testIntegerComputer(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
