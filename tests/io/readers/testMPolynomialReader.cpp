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
 * @file testMPolynomialReader.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/12
 *
 * Functions for testing class Signal.
 *
 * This file is part of the DGtal library.
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
// Functions for testing class MPolynomialReader.
///////////////////////////////////////////////////////////////////////////////

bool testMPolynomialReader()
{

  MPolynomial<2,double,std::allocator<double> > Q1;
  MPolynomial<2,double,std::allocator<double> > Q2;
  MPolynomial<2,double,std::allocator<double> > Q = Q1 * Q2;

  typedef int Ring;
  MPolynomial<3,Ring,std::allocator<Ring> > P;
  MPolynomialReader<3,Ring> reader;
  string s1 = "1.5 X_0^2 X_2^3 X_1^5 * (4 X_0^3 + X_1^2)^2";
  //string s1 = "1.5 X_0^2 X_2^3 X_1^5";
  string s2 = "2 X_0^2 X_2 X_1^5";
  string s3 = s1 + " * " + s2;
  string s4 = "(" + s2 + ")^4 * (" + s1 + ")^1 - 3 X_2^3";
  string s5 = "x^3y+xz^3+y^3z+z^3+5z"; // Durchblick
  string s6 = "(y^2+z^2-1)^2 +(x^2+y^2-1)^3"; // Crixxi 
  string s7 = "(y^2+z^2-1)^2 Abrahamovitch"; 
  bool ok1 = reader.read( P, s1.begin(), s1.end() ) == s1.end();
  trace.info() << "- Parsing " << s1 << " : " << ok1 << " " << P << std::endl;
  bool ok2 = reader.read( P, s2.begin(), s2.end() ) == s2.end();
  trace.info() << "- Parsing " << s2 << " : " << ok2 << " " << P << std::endl;
  bool ok3 = reader.read( P, s3.begin(), s3.end() ) == s3.end();
  trace.info() << "- Parsing " << s3 << " : " << ok3 << " " << P << std::endl;
  bool ok4 = reader.read( P, s4.begin(), s4.end() ) == s4.end();
  trace.info() << "- Parsing " << s4 << " : " << ok4 << " " << P << std::endl;
  bool ok5 = reader.read( P, s5.begin(), s5.end() ) == s5.end();
  trace.info() << "- Parsing " << s5 << " : " << ok5 << " " << P << std::endl;
  bool ok6 = reader.read( P, s6.begin(), s6.end() ) == s6.end();
  trace.info() << "- Parsing " << s6 << " : " << ok6 << " " << P << std::endl;
  bool ok7 = reader.read( P, s7.begin(), s7.end() ) == s7.end();
  trace.info() << "- Parsing " << s7 << " : " << ok7 << " " << P << std::endl;

  string s8 = "(zyx^2+x^2-1)^2 + xy AVERTY"; 
  std::istringstream sin( s8 );
  std::string other;
  sin >> P >> other;
  trace.info() << "- Read " << P << " and " << other << std::endl;

  return ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && (!ok7);
}

bool testMPolynomialReader2()
{

  typedef double Ring;
  MPolynomial<3,Ring,std::allocator<Ring> > P1, P2, Q1, Q2, Q3, Q4;
  MPolynomialReader<3,Ring> reader;
  string s1 = "  x^4";
  string s2 = "1*y^4";
  string s3 = s1 + "+" + s2 + "-2";
  string s4 = "(" + s1 + ")+(" + s2 + ")-2";
  string s5 = "(" + s1 + ")+ " + s2 + " -2";
  bool ok1 = reader.read( P1, s1.begin(), s1.end() ) == s1.end();
  bool ok2 = reader.read( P2, s2.begin(), s2.end() ) == s2.end();
  Q1 = P1 + P2 - 2;
  bool ok3 = reader.read( Q2, s3.begin(), s3.end() ) == s3.end();
  bool ok4 = reader.read( Q3, s4.begin(), s4.end() ) == s4.end();
  bool ok4b= reader.read( Q4, s5.begin(), s5.end() ) == s5.end();

  trace.info() << "- Read Q1=" << Q1 << " from addition of monomials. " << std::endl;
  trace.info() << "- Read Q2=" << Q2 << " from string: " << s3 << std::endl;
  trace.info() << "- Read Q3=" << Q3 << " from string: " << s4 << std::endl;
  trace.info() << "- Read Q4=" << Q4 << " from string: " << s5 << std::endl;
  bool ok5 = Q1 == Q2;
  bool ok6 = Q1 == Q3;
  return ok1 && ok2 && ok3 && ok4 && ok5 && ok6 && ok4b;
}
///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int /*argc*/, char** /*argv*/ )
{
  trace.beginBlock ( "Testing class MPolynomialReader" );

  bool res = testMPolynomialReader()
    && testMPolynomialReader2();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
