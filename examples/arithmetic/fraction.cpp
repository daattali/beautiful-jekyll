/**
 * @file arithmetic/fraction.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named fraction.
 *
 * This file is part of the DGtal library.
 */

/**
   Computes a fraction from its quotients.

@see \ref dgtal_irrfrac_sec3_4

@verbatim
# More precise approximation of pi
$ ./examples/arithmetic/fraction 3 7 15 1 292 1 1 1 2 1 3 1 14
z = 80143857 / 25510582
@endverbatim

\example arithmetic/fraction.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [fraction-basicIncludes]
#include <iostream>
#include "DGtal/arithmetic/LighterSternBrocot.h"
//! [fraction-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <u_0> <u_1> ... <u_k>" << std::endl;
  std::cerr << "\t - computes the fraction [u_0; u_1, ..., u_k] from its partial quotients." << std::endl;
}

/**
   Main.
*/
int main( int argc, char** argv )
{
  if ( argc < 3 )
    {
      usage( argc, argv );
      return 1;
    }

  //! [fraction-types]
  typedef DGtal::int64_t Integer;
  typedef DGtal::int64_t Quotient;
  typedef LighterSternBrocot<Integer, Quotient, StdMapRebinder> SB; // the type of the Stern-Brocot tree
  typedef SB::Fraction Fraction; // the type for fractions
  typedef std::back_insert_iterator< Fraction > OutputIterator;
  //! [fraction-types]

  //! [fraction-from-quotients]
  Fraction f;
  OutputIterator itback = std::back_inserter( f );
  for ( Quotient i = 1; i < argc; ++i)
    {
      Quotient u = atoll( argv[ i ] );
      *itback++ = std::make_pair( u, i-1 );
    }
  std::cout << "z = " << f.p() << " / " << f.q() << std::endl;
  //! [fraction-from-quotients]
  return 0;
}

