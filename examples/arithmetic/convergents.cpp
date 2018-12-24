/**
 * @file arithmetic/convergents.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named convergents.
 *
 * This file is part of the DGtal library.
 */

/**
   Computes the quotients and the convergents of a given fraction.

@see \ref dgtal_irrfrac_sec3_2

@verbatim
# Approximations of pi
$ ./examples/arithmetic/convergents 103993 33102
z = [3,7,15,1,292]
z_0 = 3 / 1
z_1 = 22 / 7
z_2 = 333 / 106
z_3 = 355 / 113
z_4 = 103993 / 33102
@endverbatim

\example arithmetic/convergents.cpp
*/


///////////////////////////////////////////////////////////////////////////////
//! [convergents-basicIncludes]
#include <iostream>
#include "DGtal/arithmetic/LighterSternBrocot.h"
//! [convergents-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <p> <q>" << std::endl;
  std::cerr << "\t - computes the successive convergent of the fraction p / q." << std::endl;
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

  //! [convergents-types]
  typedef LighterSternBrocot<DGtal::int64_t, DGtal::int64_t, StdMapRebinder> SB; // the type of the Stern-Brocot tree
  typedef SB::Fraction Fraction; // the type for fractions
  typedef Fraction::ConstIterator ConstIterator; // the iterator type for visiting quotients
  typedef Fraction::Value Value; // the value of the iterator, a pair (quotient,depth).
  //! [convergents-types]

  //! [convergents-instantiation]
  DGtal::int64_t p = atoll( argv[ 1 ] );
  DGtal::int64_t q = atoll( argv[ 2 ] );
  Fraction f( p, q ); // fraction p/q
  //! [convergents-instantiation]

  //! [convergents-cfrac]
  // Visit quotients u_k as pair (u_k,k)
  std::cout << "z = ";
  ConstIterator itbegin = f.begin(), itend = f.end();
  for ( ConstIterator it = itbegin; it != itend; ++it )
    {
      Value u = *it;
      std::cout << ( ( it == itbegin ) ? "[" : "," )
                << u.first;
    }
  std::cout << "]" << std::endl;
  //! [convergents-cfrac]

  //! [convergents-convergents]
  Fraction g;         // fraction null, 0/0, invalid
  for ( ConstIterator it = itbegin; it != itend; ++it )
    {
      Value u = *it;
      std::cout << "z_" << u.second << " = ";
      g.push_back( u ); // add (u_i,i) to existing fractions
      std::cout << g.p() << " / " << g.q() << std::endl;
    }
  //! [convergents-convergents]
  return 0;
}

