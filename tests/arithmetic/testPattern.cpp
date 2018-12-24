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
 * @file testPattern.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class LightSternBrocot.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/SternBrocot.h"
#include "DGtal/arithmetic/LightSternBrocot.h"
#include "DGtal/arithmetic/LighterSternBrocot.h"
#include "DGtal/arithmetic/Pattern.h"

#include <boost/version.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_smallint.hpp>
#include <boost/random/variate_generator.hpp>
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class LightSternBrocot.
///////////////////////////////////////////////////////////////////////////////

template <typename Fraction1, typename Fraction2>
bool
testPattern( Fraction1 f1 )
{
  typedef Pattern<Fraction1> Pattern1;
  typedef Pattern<Fraction2> Pattern2;
  Fraction2 f2( f1.p(), f1.q() );

  std::cerr << " f1 =";
  f1.selfDisplay( std::cerr );
  std::cerr << std::endl;
  std::cerr << "r(1)=";
  f1.reduced(1).selfDisplay( std::cerr );
  std::cerr << std::endl;
  std::cerr << "r(2)=";
  f1.reduced(2).selfDisplay( std::cerr );
  std::cerr << std::endl;
 
  Pattern1 p1( f1 );
  Pattern2 p2( f2 );
  std::cerr << "p1=" << p1.rE() << std::endl;
  std::cerr << "p2=" << p2.rE() << std::endl;
  std::cerr << "p1=" << p1.rEs( "(|)" ) << std::endl;
  std::cerr << "p2=" << p2.rEs( "(|)" ) << std::endl;
  return p1.rE() == p2.rE();
}

template <typename Fraction1, typename Fraction2>
bool
testPatterns()
{
  unsigned int nbtests = 100;
  unsigned int nb = 0;
  unsigned int nbok = 0;
  Fraction1 f1;
  f1 = Fraction1( 5, 8 );
  ++nb;
  nbok += testPattern<Fraction1,Fraction2>( f1 ) ? 1 : 0;
  std::cerr << "(" << nbok << "/" << nb << ") f1=";
  f1.selfDisplay( std::cerr );
  std::cerr << endl;
  f1 = Fraction1( 31, 24 );
  ++nb;
  nbok += testPattern<Fraction1,Fraction2>( f1 ) ? 1 : 0;
  std::cerr << "(" << nbok << "/" << nb << ") f1=";
  f1.selfDisplay( std::cerr );
  std::cerr << endl;
  f1 = Fraction1( 5, 13 );
  ++nb;
  nbok += testPattern<Fraction1,Fraction2>( f1 ) ? 1 : 0;
  std::cerr << "(" << nbok << "/" << nb << ") f1=";
  f1.selfDisplay( std::cerr );
  std::cerr << endl;
  IntegerComputer<unsigned  int > ic;

  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      unsigned int p = std::rand() % 999+1;
      unsigned int q = std::rand() % 999+1;
      unsigned int g = ic.gcd( p, q );
      p /= g; q /= g;
      std::cerr << "*- p / q = " << p << "/" << q << std::endl;
      f1 = Fraction1( p, q );
      ++nb;
	  nbok += testPattern<Fraction1,Fraction2>( f1 ) ? 1 : 0;
      std::cerr << "(" << nbok << "/" << nb << ") f1=";
      f1.selfDisplay( std::cerr );
      std::cerr << endl;
    }
  return nbok == nb;
}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :
int main( int , char** )
{
  typedef SternBrocot<DGtal::int64_t, DGtal::int32_t> SB;
  typedef LightSternBrocot<DGtal::int64_t,DGtal::int32_t> LSB;
  typedef LighterSternBrocot<DGtal::int64_t,DGtal::int32_t> LLSB;
  typedef SB::Fraction Fraction;
  typedef LSB::Fraction LFraction;
  typedef LLSB::Fraction LLFraction;
  trace.beginBlock ( "Testing class Pattern" );
  bool res = testPatterns<Fraction, LFraction>()
    && testPatterns<Fraction, LLFraction>()
    && testPatterns<LLFraction, LFraction>();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();

  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

