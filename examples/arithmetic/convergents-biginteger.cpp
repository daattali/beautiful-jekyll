/**
 * @file arithmetic/convergents-biginteger.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named convergents-biginteger.
 *
 * This file is part of the DGtal library.
 */
/**

   Computes the quotients and the convergents of a given fraction,
   which may be arbitrarily large.

@see \ref dgtal_irrfrac_sec3_2

@verbatim
# A huge fraction
$ ./examples/arithmetic/convergents-biginteger 243224233245235253407096734543059 4324213412343432913758138673203834
z = [0,17,1,3,1,1,12,1,2,33,2,1,1,1,1,49,1,1,1,1,17,34,1,1,304,1,2,1,1,1,2,1,48,1,20,2,3,5,1,1,16,9,1,1,5,1,2,2,7,4,3,1,7,1,1,17,1,1,29,1,12,2,5]
z_0 = 0 / 1
z_1 = 1 / 17
z_2 = 1 / 18
z_3 = 4 / 71
z_4 = 5 / 89
...
z_18 = 23610961 / 419772458
...
z_40 = 832739221613445323225 / 14805030169237188131024
...
z_62 = 243224233245235253407096734543059 / 4324213412343432913758138673203834
@endverbatim

\example arithmetic/convergents-biginteger.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [convergents-biginteger-basicIncludes]
#include <iostream>
#include "DGtal/arithmetic/LighterSternBrocot.h"
//! [convergents-biginteger-basicIncludes]

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
  std::string inputP = argv[ 1 ];
  std::string inputQ = argv[ 2 ];

  //! [convergents-biginteger-types]
  typedef BigInteger Integer;
  typedef DGtal::int64_t Quotient;
  typedef LighterSternBrocot<Integer, Quotient, StdMapRebinder> SB; // the type of the Stern-Brocot tree
  typedef SB::Fraction Fraction; // the type for fractions
  typedef Fraction::ConstIterator ConstIterator; // the iterator type for visiting quotients
  typedef Fraction::Value Value; // the value of the iterator, a pair (quotient,depth).
  //! [convergents-biginteger-types]

  //! [convergents-biginteger-instantiation]
  Integer p( inputP );
  Integer q( inputQ );
  Fraction f( p, q ); // fraction p/q
  //! [convergents-biginteger-instantiation]

  //! [convergents-biginteger-cfrac]
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
  //! [convergents-biginteger-cfrac]

  //! [convergents-biginteger-convergents]
  Fraction g;         // fraction null, 0/0, invalid
  for ( ConstIterator it = itbegin; it != itend; ++it )
    {
      Value u = *it;
      std::cout << "z_" << u.second << " = ";
      g.push_back( u ); // add (u_i,i) to existing fractions
      std::cout << g.p() << " / " << g.q() << std::endl;
    }
  //! [convergents-biginteger-convergents]
  return 0;
}

