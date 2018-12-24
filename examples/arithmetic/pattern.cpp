/**
 * @file arithmetic/pattern.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named pattern.
 *
 * This file is part of the DGtal library.
 */

/**
   Computes a pattern from a given slope p / q.

@see \ref dgtal_digstraighness_sec2

@verbatim
# Pattern 5 / 12
$ ./examples/arithmetic/pattern 5 12
00010010001001001

# Pattern 5 / 12 with its recursive subdivision
$ ./examples/arithmetic/pattern 5 12 SUB
((0|(00|1)(00|1))(0|(00|1)(00|1))|(00|1))
@endverbatim

\example arithmetic/pattern.cpp
*/

///////////////////////////////////////////////////////////////////////////////
//! [pattern-basicIncludes]
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include "DGtal/arithmetic/LighterSternBrocot.h"
#include "DGtal/arithmetic/Pattern.h"
//! [pattern-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <p> <q> [SUB]" << std::endl;
  std::cerr << "\t - computes the pattern of slope p / q and displays it." << std::endl;
  std::cerr << "\t - the optional [SUB] parameter displays the pattern with its recursive Berstel decomposition." << std::endl;
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

  //! [pattern-types]
  typedef DGtal::int32_t Integer;
  typedef DGtal::int32_t Quotient;
  typedef LighterSternBrocot<Integer, Quotient, StdMapRebinder> SB; // the type of the Stern-Brocot tree
  typedef SB::Fraction Fraction; // the type for fractions
  typedef Pattern<Fraction> MyPattern; // the type for patterns
  //! [pattern-types]

  //! [pattern-instantiation]
  DGtal::int32_t p = atoi( argv[ 1 ] );
  DGtal::int32_t q = atoi( argv[ 2 ] );
  MyPattern pattern( p, q );
  //! [pattern-instantiation]

  //! [pattern-process]
  bool sub = ( argc > 3 ) && ( std::string( argv[ 3 ] ) == "SUB" );
  std::cout << ( ! sub ? pattern.rE() : pattern.rEs( "(|)" ) ) << std::endl;
  //! [pattern-process]
  return 0;
}

