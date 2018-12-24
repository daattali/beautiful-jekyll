/**
 * @file arithmetic/approximation.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named approximation.
 *
 * This file is part of the DGtal library.
 */
/**
   Computes a fraction from a floating-point number

@see \ref dgtal_irrfrac_sec3_8

@verbatim
$ ./examples/arithmetic/approximation 1.33333333333333
z = 1 / 1 =~ 1
z = 4 / 3 =~ 1.333333333333333
z = 4 / 3

$./examples/arithmetic/approximation 1.33333333333338
z = 1 / 1 =~ 1
z = 3 / 2 =~ 1.5
z = 4 / 3 =~ 1.333333333333333
z = 9523805234895 / 7142853926171 =~ 1.33333333333338
z = 9523805234895 / 7142853926171

$ ./examples/arithmetic/approximation 3.141592654 
z = 3 / 1 =~ 3
z = 22 / 7 =~ 3.142857142857143
z = 333 / 106 =~ 3.141509433962264
z = 355 / 113 =~ 3.141592920353982
z = 104348 / 33215 =~ 3.141592653921421
z = 1148183 / 365478 =~ 3.141592654003798
z = 1252531 / 398693 =~ 3.141592653996935
z = 2400714 / 764171 =~ 3.141592654000217
z = 18057529 / 5747890 =~ 3.14159265399999
z = 38515772 / 12259951 =~ 3.141592654000004
z = 38515772 / 12259951
@endverbatim

\example arithmetic/approximation.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [approximation-basicIncludes]
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "DGtal/arithmetic/LighterSternBrocot.h"
#include "DGtal/base/StdRebinders.h"
//! [approximation-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <floating point number>" << std::endl;
  std::cerr << "\t - computes the successive rational approximation of this number, up to a precision of 1e-14." << std::endl;
}

/**
   Main.
*/
int main( int argc, char** argv )
{
  if ( argc < 2 )
    {
      usage( argc, argv );
      return 1;
    }

  //! [approximation-types]
  typedef DGtal::int64_t Integer;
  typedef DGtal::int64_t Quotient;
  typedef LighterSternBrocot<Integer, Quotient, StdMapRebinder> SB; // the type of the Stern-Brocot tree
  typedef SB::Fraction Fraction; // the type for fractions
  typedef std::back_insert_iterator< Fraction > OutputIterator;
  //! [approximation-types]

  //! [approximation-process]
  long double epsilon = 1e-14;
  long double number0 = strtold( argv[ 1 ], 0 );
  long double number = number0;
  ASSERT( number >= 0.0 );
  Fraction f;
  OutputIterator itback = std::back_inserter( f );
  Quotient i = 0;
  while ( true )
    {
      long double int_part = floorl( number );
      Quotient u = NumberTraits<long double>::castToInt64_t( int_part );
      *itback++ = std::make_pair( u, i++ );
      long double approx =
        ( (long double) NumberTraits<Integer>::castToDouble( f.p() ) )
        / ( (long double) NumberTraits<Integer>::castToDouble( f.q() ) );
      std::cout << "z = " << f.p() << " / " << f.q()
                << " =~ " << std::setprecision( 16 ) << approx << std::endl;
      number -= int_part;
      if ( ( (number0 - epsilon ) < approx )
           && ( approx < (number0 + epsilon ) ) ) break;
      number = 1.0 / number;
    }
  std::cout << "z = " << f.p() << " / " << f.q() << std::endl;
  //! [approximation-process]
  return 0;
}

