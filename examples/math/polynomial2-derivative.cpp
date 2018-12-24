/**
 * @file math/polynomial2-derivative.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/06
 *
 * An example file named polynomial2-derivative.
 *
 * This file is part of the DGtal library.
 */

/**
 *   computes the first and second derivatives of the given polynomial P (in two variables).
 *
 * @see \ref dgtal_mpolynomial_sec1_5 and \ref dgtal_mpolynomial_sec3 
 *
 * @verbatim
 * $ ./examples/math/polynomial2-derivative "(x-3)^2 + (y-2)^2 - 4"
 * P(X_0,X_1)        = ((9 + -4 X_1 + 1 X_1^2) + -6 X_0 + 1 X_0^2)
 * dP/dX_0(X_0,X_1)  = (-6 + 2 X_0)
 * dP/dX_1(X_0,X_1)  = (-4 + 2 X_1)
 * d/dX_1 dP/dX_0(X_0,X_1) = 0
 * d/dX_0 dP/dX_1(X_0,X_1) = 0
 * d/dX_0 dP/dX_0(X_0,X_1) = 2
 * d/dX_1 dP/dX_1(X_0,X_1) = 2
 * @endverbatim
 *
 * \example math/polynomial2-derivative.cpp
 */

///////////////////////////////////////////////////////////////////////////////
//! [polynomial2-derivative-basicIncludes]
#include <iostream>
#include <string>
#include <sstream>
#include "DGtal/math/MPolynomial.h"
#include "DGtal/io/readers/MPolynomialReader.h"
//! [polynomial2-derivative-basicIncludes]

///////////////////////////////////////////////////////////////////////////////

using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////

void usage( int, char** argv )
{
  std::cerr << "Usage: " << argv[ 0 ] << " <P(x,y)>" << std::endl;
  std::cerr << "\t - computes the first and second derivatives of the given polynomial P (in two variables)." << std::endl;
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

  //! [polynomial2-derivative-types]
  typedef double Ring;
  typedef MPolynomial<2, Ring> MyPolynomial;
  //! [polynomial2-derivative-types]

  //! [polynomial2-derivative-process]
  std::string polynomialString( argv[ 1 ] );
  std::istringstream polynomialIStream( polynomialString );
  MyPolynomial P;
  polynomialIStream >> P;
  MyPolynomial P1_0 = derivative<0>( P );
  MyPolynomial P2_0 = derivative<0>( P1_0 );
  MyPolynomial P0_1 = derivative<1>( P );
  MyPolynomial P0_2 = derivative<1>( P0_1 );
  MyPolynomial P1_1 = derivative<1>( P1_0 );
  MyPolynomial P1_1b= derivative<0>( P0_1 );
  std::cout << "P(X_0,X_1)        = " << P << std::endl;
  std::cout << "dP/dX_0(X_0,X_1)  = " << P1_0 << std::endl;
  std::cout << "dP/dX_1(X_0,X_1)  = " << P0_1 << std::endl;
  std::cout << "d/dX_1 dP/dX_0(X_0,X_1) = " << P1_1 << std::endl;
  std::cout << "d/dX_0 dP/dX_1(X_0,X_1) = " << P1_1b << std::endl;
  std::cout << "d/dX_0 dP/dX_0(X_0,X_1) = " << P2_0 << std::endl;
  std::cout << "d/dX_1 dP/dX_1(X_0,X_1) = " << P0_2 << std::endl;
  //! [polynomial2-derivative-process]
  return 0;
}

