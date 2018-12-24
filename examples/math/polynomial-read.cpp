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
 * @file math/polynomial-read.cpp
 * @ingroup Examples
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/12
 *
 * Functions for testing class Signal.
 *
 * This file is part of the DGtal library.
 */

/**
 *   Example of polynom read from user input.
 *
 * @see \ref modulePolynomial  
 *
 * @verbatim
 * $ ./examples/math/polynomial-read               
 * Type any multi-variate polynomial, then press return.
 * Examples: xyz^3-4yz, (x+y+z)*(x-y-z)^2.
 * (x-3)^2 + (y-2)^2 - 4
 * Ok : ((9 + -4 X_1 + 1 X_1^2) + -6 X_0 + 1 X_0^2)
 * @endverbatim
 *
 * \example math/polynomial-read.cpp
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
// Standard services - public :

/**
   A simple example to show how to read a multivariate-polynomial from stdin.
*/
int main( int /*argc*/, char** /*argv*/ )
{
  typedef double Ring;
  MPolynomial<3,Ring,std::allocator<Ring> > P;
  MPolynomialReader<3,Ring> reader;
  string str;

  std::cout << "Type any multi-variate polynomial, then press return." << std::endl
	    << "Examples: xyz^3-4yz, (x+y+z)*(x-y-z)^2." << std::endl;
  do {
    getline( cin, str );
    if ( cin.good() && ( ! str.empty() ) )
      {
	std::string::const_iterator iter 
	  = reader.read( P, str.begin(), str.end() );
	bool ok = iter == str.end();
	if ( ! ok )
	  {
	    std::cerr << "ERROR: I read only <" 
		      << str.substr( 0, iter - str.begin() )
		      << ">, and I built P=" << P << std::endl;
	  }
	std::cout << (ok ? "Ok : " : "Err: ") << P << std::endl;
      }
  } while ( ! str.empty() );
  return 0;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
