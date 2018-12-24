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
 * @file testOrderedAlphabet.cpp
 * @ingroup Tests
 * @author Laurent Provot (\c Laurent.Provot@loria.fr )
 * LORIA (CNRS, UMR 7503), Nancy University, France
 *
 * @date 2010/07/04
 *
 * Functions for testing class OrderedAlphabet.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include "DGtal/base/Common.h"
#include "DGtal/base/OrderedAlphabet.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class OrderedAlphabet.
///////////////////////////////////////////////////////////////////////////////
/**
 * Checks if the Lyndon factorization works.
 *
 * @param alphabet an alphabet.
 * @param input the input word.
 * @param output the expected output word as (w1)^l1...(wn)^ln.
 * @return 'true' if the test was ok, 'false' otherwise.
 */
bool testFLF( const OrderedAlphabet & alphabet,
              const string & output,
              const string & input)
{
  string w1 = input;
  string a1 = output;
  stringstream s1;
  unsigned int len;
  unsigned int nb;
  unsigned int s = 0;
  unsigned int e = (unsigned int)w1.size();
  do 
    {
      alphabet.firstLyndonFactor( len, nb, w1, s, e );
      s1 << "(" << w1.substr( s, len ) << ")^" << nb;
      s += len*nb;
    }
  while ( s < e );

  trace.beginBlock ( "Test Lyndon factorization" );
  trace.info() << "   input = " << input << endl;
  trace.info() << "expected = " << output << endl;
  trace.info() << "computed = " << s1.str() << endl;
  trace.endBlock();

  return s1.str() == a1;
}


/**
 * Checks if Duval++ works.
 *
 * @param alphabet an alphabet.
 * @param input the input word.
 * @param output the expected output word as "NC" or "C(w1)^l1"
 * @return 'true' if the test was ok, 'false' otherwise.
 */
bool testDuvalPP( const OrderedAlphabet & alphabet,
                  const string & output, 
                  const string & input)
{
  OrderedAlphabet::size_t len;
  OrderedAlphabet::size_t nb;
  bool christoffel = alphabet.duvalPP( len, nb, input, 0, (DGtal::OrderedAlphabet::index_t)input.size() );
  stringstream s1;
  if ( christoffel ) 
    s1 << "C(" << input.substr( 0, len ) << ")^" << nb;
  else s1 << "NC(" << len << ")";

  trace.beginBlock ( "Test Duval++" );
  trace.info() << "   input = " << input << endl;
  trace.info() << "expected = " << output << endl;
  trace.info() << "computed = " << s1.str() << endl;
  trace.endBlock();

  return s1.str() == output;
}


/**
 * Checks if Duval++ modulo works.
 *
 * @param alphabet an alphabet.
 * @param input the input word.
 * @param output the expected output word as "NC" or "C(w1)^l1"
 * @param s starting index.
 * @return 'true' if the test was ok, 'false' otherwise.
 */
bool testDuvalPPMod( const OrderedAlphabet & alphabet,
                     const string & output,
                     const string & input,
                     OrderedAlphabet::index_t s)
{
  OrderedAlphabet::size_t len;
  OrderedAlphabet::size_t nb;
  bool christoffel = alphabet.duvalPPMod( len, nb, input, s, s );
  stringstream s1;
  if ( christoffel ) 
    {
      s1 << "C(";
      for ( unsigned int i = 0; i < len; ++i )
  {
    s1 << input[ s ];
    s = s + 1 % input.size();
  }
      s1  << ")^" << nb;
    }
  else s1 << "NC(" << len << ")";

  trace.beginBlock ( "Test Duval++ modulo" );
  trace.info() << "   input = " << input << endl;
  trace.info() << "expected = " << output << endl;
  trace.info() << "computed = " << s1.str() << endl;
  trace.endBlock();

  return s1.str() == output;
}


/**
 * Test the class OrderedAlphabet.
 *
 */
bool testOrderedAlphabet()
{
  unsigned int nb_ok = 0;
  unsigned int nb_ko = 0;
  OrderedAlphabet A( '0', 4 );
  string w1 = "01101010100101001010001";
  string a1= "(011)^1(01)^3(00101)^2(0001)^1";
  if ( testFLF( A, a1, w1 ) ) nb_ok++;
  else                        nb_ko++;
  w1 = "01232112232232103220123210120";
  a1 = "(0123211223223210322)^1(012321)^1(012)^1(0)^1";
  if ( testFLF( A, a1, w1 ) ) nb_ok++;
  else                        nb_ko++;
  w1 = "1112111211211121121112111211211121121111";
  a1 = "C(111211121121112112)^2";
  if ( testDuvalPP( A, a1, w1 ) ) nb_ok++;
  else                            nb_ko++;
  w1 = "1112111211211121121121111211211121121111";
  a1 = "NC(20)";
  if ( testDuvalPP( A, a1, w1 ) ) nb_ok++;
  else                            nb_ko++;
  w1 = "2111211211121121111111211121121112112111";
  a1 = "C(111211121121112112)^2";
  if ( testDuvalPPMod( A, a1, w1, 19 ) ) nb_ok++;
  else                                   nb_ko++;

  trace.info() << "Tests passed: " << nb_ok << "/" 
               << ( nb_ok + nb_ko ) << endl;

  return !nb_ko;
}


///////////////////////////////////////////////////////////////////////////////
int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class OrderedAlphabet" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = testOrderedAlphabet(); // && ... other tests
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;
}
