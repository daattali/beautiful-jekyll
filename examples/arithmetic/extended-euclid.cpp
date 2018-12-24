/**
 * @file arithmetic/extended-euclid.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named extended-euclid.
 *
 * This file is part of the DGtal library.
 */

/**
   Computes a solution to the diophantine equation \f$ ax+by=c \f$, where the
   integers \a a, \a b, \a c are given and \a x, \a y are the unknowns
   (integers). Note that \a c must be a multiple of gcd( \a a, \a b ).

@see \ref dgtal_integer_computations_sec2

@verbatim
$ ./examples/arithmetic/extended-euclid 5 7 1
x=3 y=-2
$ ./examples/arithmetic/extended-euclid 12 32 4
x=3 y=-1
@endverbatim

\example arithmetic/extended-euclid.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [extended-euclid-basicIncludes]
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "DGtal/arithmetic/IntegerComputer.h"
//! [extended-euclid-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <a> <b> <c>" << std::endl;
  std::cerr << "\t - solves the diophantine equation ax+by=c by the extended Euclid algorithm." << std::endl;
  std::cerr << "\t - note: c should be a multiple of gcd(a,b)." << std::endl;
}

/**
   Main.
*/
int main( int argc, char** argv )
{
  if ( argc < 4 )
    {
      usage( argc, argv );
      return 0;
    }

  //! [extended-euclid-types]
  typedef BigInteger Integer;
  typedef IntegerComputer<Integer> IC;
  //! [extended-euclid-types]

  //! [extended-euclid-instantiation]
  Integer a( argv[ 1 ] );
  Integer b( argv[ 2 ] );
  Integer c( argv[ 3 ] );
  IC ic;
  Integer g = ic.gcd( a, b );
  if ( ic.isZero( a ) || ic.isZero( b ) )
    {
      std::cerr << "[Error] parameters a and b should be non-null." << std::endl;
      return 1;
    }
  if ( ic.isNotZero( c % g ) )
    {
      std::cerr << "[Error] parameter c should be a multiple of gcd(a,b)." << std::endl;
      return 2;
    }
  //! [extended-euclid-instantiation]

  //! [extended-euclid-process]
  IC::Vector2I X = ic.extendedEuclid( a, b, c );
  std::cout << "x=" << X[ 0 ] << " y=" << X[ 1 ] << std::endl;
  Integer d = a*X[ 0 ] + b*X[ 1 ];
  if ( c != d )
    {
      std::cerr << "[Internal Error] Output of extended Euclid algorithm is incorrect: " << d << " != " << c 
                << ". This should not happen." << std::endl;
      return 3;
    }
  //! [extended-euclid-process]
  return 0;
}

