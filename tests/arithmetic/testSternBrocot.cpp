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
 * @file testSternBrocot.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Functions for testing class SternBrocot.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <cstdlib>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/arithmetic/CPositiveIrreducibleFraction.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/SternBrocot.h"
#include "DGtal/arithmetic/Pattern.h"
#include "DGtal/arithmetic/StandardDSLQ0.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class SternBrocot.
///////////////////////////////////////////////////////////////////////////////

template <typename Quotient>
bool
equalCFrac( const std::vector<Quotient> & c1, const std::vector<Quotient> & c2 )
{
  unsigned int s = c1.size() < c2.size() ? c1.size() : c2.size();
  if ( ( s != c1.size() ) && ( c1.back() != NumberTraits<Quotient>::ONE ) )
    return false;
  if ( ( s != c2.size() ) && ( c2.back() != NumberTraits<Quotient>::ONE ) )
    return false;
  for ( unsigned int i = 0; i < s; ++i )
    {
      Quotient q1 = c1[ i ];
      if ( ( s != c1.size() ) && ( i == s - 1 ) ) q1 += c1.back();
      Quotient q2 = c2[ i ];
      if ( ( s != c2.size() ) && ( i == s - 1 ) ) q2 += c2.back();
      if ( q1 != q2 ) return false;
    }
  return true;
}

template <typename SB>
bool testReducedFraction()
{
  typedef typename SB::Integer Integer;
  typedef typename SB::Quotient Quotient;
  typedef typename SB::Fraction Fraction;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer p = rand() / 10000;
  Integer q = rand() / 10000;
  trace.beginBlock ( "Testing block: reduced fraction." );
  IntegerComputer<Integer> ic;
  Integer g = ic.gcd( p, q );
  p /= g;
  q /= g;
  IntegerComputer<Quotient> ics;
  Quotient sp = NumberTraits<Integer>::castToInt64_t( p );
  Quotient sq = NumberTraits<Integer>::castToInt64_t( q );
  std::vector<Quotient> cf1;
  ics.getCFrac( cf1, sp, sq );
  Fraction f1 = SB::fraction( p, q );
  std::vector<Quotient> cf1_bis;
  f1.getCFrac( cf1_bis );
  bool ok = equalCFrac<Quotient>( cf1, cf1_bis );
  trace.info() << "  - p / q = " << p << " / " << q << std::endl;
  trace.info() << "  - f1 = ";
  SB::display( trace.info(), f1 );
  trace.info() << std::endl;
  ++nb, nbok += ok ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") " 
               << " cfrac"
               << std::endl;
  unsigned int depth = cf1.size();
  for ( unsigned int k = 1; k < depth; ++k )
    {
      std::vector<Quotient> cf1_red;
      Fraction fr = f1.reduced( k );
      fr.getCFrac( cf1_red );
      cf1.resize( depth - k );
      ok = equalCFrac<Quotient>( cf1, cf1_red );
      ++nb, nbok += ok ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") " 
                   << "reduced(" << k << ")=";
      SB::display( trace.info(), fr );
      std::cerr << std::endl;
    }

  //trace.info() << "- nbFractions = " << SB::instance().nbFractions << std::endl;
  trace.endBlock();
  return nbok == nb;
}

template <typename SB>
bool testInitFraction()
{
  typedef typename SB::Integer Integer;
  typedef typename SB::Fraction Fraction;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer p = rand() / 10000;
  Integer q = rand() / 10000;
  trace.beginBlock ( "Testing block: init fraction." );
  IntegerComputer<Integer> ic;
  Integer g = ic.gcd( p, q );
  p /= g;
  q /= g;
  Fraction f1 = SB::fraction( p, q );
  trace.info() << "p / q = " << p << " / " << q << std::endl;
  trace.info() << "f1 = ";
  SB::display( trace.info(), f1 );
  trace.info() << std::endl;
  nbok += ( ( p == f1.p() ) && ( q == f1.q() ) ) ? 1 : 0;
  ++nb;
  trace.info() << "(" << nbok << "/" << nb << ") " 
               << "( ( p == f1.p() ) && ( q == f1.q() ) )"
               << std::endl;
  trace.info() << "- nbFractions = " << SB::instance().nbFractions << std::endl;
  trace.endBlock();

  return nbok == nb;
}

template <typename SB>
bool testPattern()
{
  typedef typename SB::Integer Integer;
  typedef typename SB::Quotient Quotient;
  typedef typename SB::Fraction Fraction;
  typedef Pattern<Fraction> MyPattern;
  typedef typename MyPattern::Vector2I Vector2I;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  Integer p = rand() / 10000;
  Integer q = rand() / 10000;
  MyPattern pattern( p*6, q*6 );
  trace.info() << pattern << endl;

  // ODD PATTERN
  trace.beginBlock ( "Testing block: Smallest covering subpatterns of ODD pattern." );
  MyPattern pat_odd( 5, 12 );
  trace.info() << "ODD  " << pat_odd << " " << pat_odd.rE() << endl;
  MyPattern sp;
  Quotient np;
  Vector2I start;

  // Left Subpatterns
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 17 );
  trace.info() << "sub(0,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 12 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         1, 17 );
  trace.info() << "sub(1,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 12 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         7, 17 );
  trace.info() << "sub(7,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 3, 7 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         8, 17 );
  trace.info() << "sub(8,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 3, 7 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         13, 17 );
  trace.info() << "sub(13,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 3, 7 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         14, 17 );
  trace.info() << "sub(14,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 1, 2 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         15, 17 );
  trace.info() << "sub(15,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 1, 2 ) ? 1 : 0;

  trace.info() << "(" << nbok << "/" << nb << ") covering left Subpatterns." << endl;

  // Right Subpatterns
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 16 );
  trace.info() << "sub(0,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 12 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 15 );
  trace.info() << "sub(0,15) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 12 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 14 );
  trace.info() << "sub(0,14) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 2 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 8 );
  trace.info() << "sub(0,8) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 2 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 7 );
  trace.info() << "sub(0,7) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         0, 1 );
  trace.info() << "sub(0,1) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;

  trace.info() << "(" << nbok << "/" << nb << ") covering right Subpatterns." << endl;

  // Middle Subpatterns
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         1, 16 );
  trace.info() << "sub(1,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 12 ) ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         2, 14 );
  trace.info() << "sub(2,14) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 2 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         7, 15 );
  trace.info() << "sub(7,15) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 3, 7 ) && np == 1 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         7, 14 );
  trace.info() << "sub(7,14) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         3, 6 );
  trace.info() << "sub(3,6) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         6, 8 );
  trace.info() << "sub(6,8) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 2 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         8, 12 );
  trace.info() << "sub(8,12) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getSmallestCoveringSubpattern( sp, np, start,
                                         15, 16 );
  trace.info() << "sub(15,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 1, 2 ) && np == 1 ? 1 : 0;

  trace.info() << "(" << nbok << "/" << nb << ") covering middle Subpatterns." << endl;
  trace.endBlock();

  // EVEN PATTERN
  trace.beginBlock ( "Testing block: Smallest covering subpatterns of EVEN pattern." );
  MyPattern pat_even( 12, 17 );
  trace.info() << "EVEN " << pat_even << " " << pat_even.rE() << endl;

  // Left Subpatterns
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          0, 29 );
  trace.info() << "sub(0,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 12, 17 ) ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          0, 25 );
  trace.info() << "sub(0,25) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 12, 17 ) ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          0, 17 );
  trace.info() << "sub(0,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 7, 10 ) ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          0, 6 );
  trace.info() << "sub(0,6) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 7, 10 ) ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          0, 5 );
  trace.info() << "sub(0,5) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 3 ) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") covering left Subpatterns." << endl;

  // Right Subpatterns
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          4, 29 );
  trace.info() << "sub(4,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 12, 17 ) ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          5, 29 );
  trace.info() << "sub(5,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 2 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          16, 29 );
  trace.info() << "sub(16,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 2 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          17, 29 );
  trace.info() << "sub(17,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") covering right Subpatterns." << endl;

  // Middle Subpatterns
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          1, 27 );
  trace.info() << "sub(1,27) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 12, 17 ) ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          5, 24 );
  trace.info() << "sub(5,24) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 2 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          4, 17 );
  trace.info() << "sub(4,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 7, 10 ) && np == 1 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          5, 17 );
  trace.info() << "sub(5,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          7, 12 );
  trace.info() << "sub(7,12) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          1, 4 );
  trace.info() << "sub(1,4) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 3 ) && np == 1 ? 1 : 0;
  pat_even.getSmallestCoveringSubpattern( sp, np, start,
                                          18, 25 );
  trace.info() << "sub(18,20) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") covering middle Subpatterns." << endl;
  trace.endBlock();

  
  // GREATEST INCLUDED SUBPATTERN
  // ODD PATTERN
  trace.beginBlock ( "Testing block: greatest included subpatterns of ODD pattern." );
  trace.info() << "ODD  " << pat_odd << " " << pat_odd.rE() << endl;

  // Left Subpatterns
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 17 );
  trace.info() << "sub(0,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 12 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         1, 17 );
  trace.info() << "sub(1,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 3, 7 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         7, 17 );
  trace.info() << "sub(7,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 3, 7 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         8, 17 );
  trace.info() << "sub(8,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 1, 2 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         13, 17 );
  trace.info() << "sub(13,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 1, 2 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         14, 17 );
  trace.info() << "sub(14,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 1, 2 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         15, 17 );
  trace.info() << "sub(15,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;

  trace.info() << "(" << nbok << "/" << nb << ") covering left Subpatterns." << endl;

  // Right Subpatterns
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 15 );
  trace.info() << "sub(0,15) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 2 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 14 );
  trace.info() << "sub(0,14) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 2 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 13 );
  trace.info() << "sub(0,13) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 7 );
  trace.info() << "sub(0,7) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 6 );
  trace.info() << "sub(0,6) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         0, 1 );
  trace.info() << "sub(0,1) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;

  trace.info() << "(" << nbok << "/" << nb << ") covering right Subpatterns." << endl;

  // Middle Subpatterns
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         1, 16 );
  trace.info() << "sub(1,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         2, 14 );
  trace.info() << "sub(2,14) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         7, 15 );
  trace.info() << "sub(7,15) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         7, 14 );
  trace.info() << "sub(7,14) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 5 ) && np == 1 ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         3, 6 );
  trace.info() << "sub(3,6) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         6, 8 );
  trace.info() << "sub(6,8) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         8, 12 );
  trace.info() << "sub(8,12) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  pat_odd.getGreatestIncludedSubpattern( sp, np, start,
                                         15, 16 );
  trace.info() << "sub(15,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;

  trace.info() << "(" << nbok << "/" << nb << ") covering middle Subpatterns." << endl;
  trace.endBlock();

  // EVEN PATTERN
  trace.beginBlock ( "Testing block: Greatest included subpatterns of EVEN pattern." );
  trace.info() << "EVEN " << pat_even << " " << pat_even.rE() << endl;

  // Left Subpatterns
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 29 );
  trace.info() << "sub(0,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 12, 17 ) ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 25 );
  trace.info() << "sub(0,25) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 7, 10 ) ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 17 );
  trace.info() << "sub(0,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 7, 10 ) ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 16 );
  trace.info() << "sub(0,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 3 ) ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 6 );
  trace.info() << "sub(0,6) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 3 ) ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 5 );
  trace.info() << "sub(0,5) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 2, 3 ) ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          0, 4 );
  trace.info() << "sub(0,4) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") covering left Subpatterns." << endl;

  // Right Subpatterns
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          4, 29 );
  trace.info() << "sub(4,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 2 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          5, 29 );
  trace.info() << "sub(5,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 2 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          16, 29 );
  trace.info() << "sub(16,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          17, 29 );
  trace.info() << "sub(17,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          18, 29 );
  trace.info() << "sub(18,29) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") covering right Subpatterns." << endl;

  // Middle Subpatterns
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          1, 27 );
  trace.info() << "sub(1,27) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          5, 24 );
  trace.info() << "sub(5,24) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          4, 17 );
  trace.info() << "sub(4,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          5, 17 );
  trace.info() << "sub(5,17) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == SB::fraction( 5, 7 ) && np == 1 ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          7, 16 );
  trace.info() << "sub(5,16) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          1, 4 );
  trace.info() << "sub(1,4) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  pat_even.getGreatestIncludedSubpattern( sp, np, start,
                                          18, 25 );
  trace.info() << "sub(18,20) = " << sp << " " << sp.rE() << "^" << np << endl;
  ++nb, nbok += sp.slope() == Fraction() ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ") covering middle Subpatterns." << endl;
  trace.endBlock();

  trace.info() << "Odd pattern " << pat_odd << endl;
  trace.info() << " U(0)=" << pat_odd.U( 0 )
               << " L(0)=" << pat_odd.L( 0 )
               << " U(1)=" << pat_odd.U( 1 )
               << " L(1)=" << pat_odd.L( 1 ) << endl;

  trace.info() << "Even pattern " << pat_even << endl;
  trace.info() << " U(0)=" << pat_even.U( 0 )
               << " L(0)=" << pat_even.L( 0 )
               << " U(1)=" << pat_even.U( 1 )
               << " L(1)=" << pat_even.L( 1 ) << endl;
                                        
  return nbok == nb;
}

template <typename Fraction>
bool testStandardDSLQ0()
{
  typedef StandardDSLQ0<Fraction> DSL;
  typedef typename Fraction::Integer Integer;
  typedef typename DSL::Point Point;
  typedef typename DSL::Vector2I Vector2I;

  BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< DSL > ));
  unsigned int nbok = 0;
  unsigned int nb = 0;

  for ( Integer mu = -5; mu < 30; ++mu )
    {
      DSL D1( 5, 12, mu );
      trace.info() << "DSL D1=" << D1 << endl;
      Point U = D1.U();
      Point L = D1.L();
      trace.info() << "- U=" << U << " r(U)=" << D1.r( U )
                   << ", L=" << L << " r(L)=" << D1.r( L ) << endl;
      ++nb, nbok += D1.r( U ) == D1.mu() ? 1 : 0;
      ++nb, nbok += D1.r( L ) == D1.mup() ? 1 : 0;
    }

  DSL D2( 12, 17, 5 );
  for ( Integer x = -5; x < 30; ++x )
    {
      Point P = D2.lowestY( x );
      ++nb, nbok += D2( P ) && ( ! D2( P - Vector2I(0,1) ) ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "D2(P) && ! D2(P-y) P=" << P << " r(P)=" << D2.r( P ) 
                   << endl;
      P = D2.uppermostY( x );
      ++nb, nbok += D2( P ) && ( ! D2( P + Vector2I(0,1) ) ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "D2(P) && ! D2(P+y) P=" << P << " r(P)=" << D2.r( P ) 
                   << endl;
    }
  for ( Integer y = -5; y < 30; ++y )
    {
      Point P = D2.lowestX( y );
      ++nb, nbok += D2( P ) && ( ! D2( P - Vector2I(1,0) ) ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "D2(P) && ! D2(P-x) P=" << P << " r(P)=" << D2.r( P ) 
                   << endl;
      P = D2.uppermostX( y );
      ++nb, nbok += D2( P ) && ( ! D2( P + Vector2I(1,0) ) ) ? 1 : 0;
      trace.info() << "(" << nbok << "/" << nb << ") "
                   << "D2(P) && ! D2(P+x) P=" << P << " r(P)=" << D2.r( P ) 
                   << endl;
    }

  return nbok == nb;
}

template <typename DSL>
bool checkSubStandardDSLQ0( const DSL & D,
                            const typename DSL::Point & A, 
                            const typename DSL::Point & B ) 
{
  typedef typename DSL::Integer Integer;
  typedef typename DSL::ConstIterator ConstIterator;
  typedef ArithmeticalDSSComputer<ConstIterator, Integer, 4> ADSS;

  DSL S = D.reversedSmartDSS( A, B );
  ConstIterator it = D.begin( A );
  ConstIterator it_end = D.end( B );
  ADSS dss;
  dss.init( it );
  while ( ( dss.end() != it_end )
          && ( dss.extendFront() ) ) {}
  bool ok = S.a() == dss.a() 
    &&  S.b() == dss.b() 
    &&  S.mu() == dss.mu(); 
  if ( ! ok )
    {
      trace.info() << "-------------------------------------------------------"
                   << std::endl;
      trace.info() << "D = " << D // << " U1=" << U1 << " U2=" << U2
                   << " " << D.pattern().rE() << endl;
      trace.info() << "S(" << A << "," << B << ") = "
                   << S << " " << S.pattern() << endl;
      trace.info() << "ArithDSS = " << dss << std::endl;
    }
  // if ( ok )
  //   trace.info() << "========================== OK =========================";
  // else
  //   trace.info() << "eeeeeeeeeeeeeeeeeeeeeeeeee KO eeeeeeeeeeeeeeeeeeeeeeeee";
  // std::cerr << std::endl;
  return ok;
}

template <typename Fraction>
bool testSubStandardDSLQ0()
{
  typedef StandardDSLQ0<Fraction> DSL;
  typedef typename Fraction::Integer Integer;
  typedef typename DSL::Point Point;
  IntegerComputer<Integer> ic;
  unsigned int nbok = 0;
  unsigned int nb = 0;

  trace.beginBlock( "Check ReversedSmartDSS == ArithmeticDSS" );
  for ( unsigned int i = 0; i < 100; ++i )
    {
      Integer a( rand() % 12000 + 1 );
      Integer b( rand() % 12000 + 1 );
      if ( ic.gcd( a, b ) == 1 )
        {
          trace.info() << "(" << i << ")"
                       << " Test DSL has slope " << a << "/" << b << std::endl;
          for ( Integer mu = 0; mu < 5; ++mu )
            {
              DSL D( a, b, rand() % 10000 );
              for ( Integer x = 0; x < 10; ++x )
                {
                  Integer x1 = rand() % 1000;
                  Integer x2 = x1 + 1 + ( rand() % 1000 );
                  Point A = D.lowestY( x1 );
                  Point B = D.lowestY( x2 );
                  ++nb, nbok += checkSubStandardDSLQ0<DSL>( D, A, B ) ? 1 : 0;
                  if ( nb != nbok )
                    trace.info() << "(" << nbok << "/" << nb << ") correct reversedSmartDSS."
                                 << std::endl;
                  if ( nbok != nb ) assert(false);
                }
            }
        }
    }
  trace.info() << "(" << nbok << "/" << nb << ") correct reversedSmartDSS."
               << std::endl;
  trace.endBlock();
  return nbok == nb;
}


/**
 * Example of a test. To be completed.
 *
 */
bool testSternBrocot()
{
  unsigned int nbtests = 10;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  typedef DGtal::BigInteger Integer;
  typedef SternBrocot<Integer, DGtal::int32_t> SB;
  trace.beginBlock ( "Testing block: init fractions." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testInitFraction<SB>() ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") init fractions." << endl;
  trace.endBlock();
  trace.beginBlock ( "Testing block: reduced fractions." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      nbok += testReducedFraction<SB>() ? 1 : 0;
      nb++;
    }
  trace.info() << "(" << nbok << "/" << nb << ") reduced fractions." << endl;
  trace.endBlock();

  trace.beginBlock ( "Testing block: number of fractions." );
  trace.info() << "- nbFractions = " << SB::instance().nbFractions << endl;
  trace.endBlock();

  return nbok == nb;
}

template <typename SB>
bool testContinuedFraction()
{
  typedef typename SB::Quotient Quotient;
  typedef typename SB::Fraction Fraction;
  typedef typename SB::Fraction::ConstIterator ConstIterator;

  Fraction f;
  std::vector<Quotient> quotients;
  std::vector<Quotient> qcfrac;
  std::back_insert_iterator< Fraction > itout = 
    std::back_inserter( f );
  unsigned int size = ( rand() % 20 ) + 10;
  for ( unsigned int i = 0; i < size; ++i )
    {
      Quotient q = ( i == 0 )
        ? ( rand() % 5 )
        : ( rand() % 5 ) + 1;
      *itout++ = std::make_pair( q, (Quotient) i );
      quotients.push_back( q );
    }
  for ( ConstIterator it = f.begin(), it_end = f.end();
        it != it_end; ++it )
    qcfrac.push_back( (*it).first );
  // f.getCFrac( qcfrac );
  bool ok = equalCFrac( quotients, qcfrac );
  
  trace.info() << ( ok ? "(OK)" : "(ERR)" );
  for ( unsigned int i = 0; i < quotients.size(); ++i )
    std::cerr << " " << quotients[ i ];
  trace.info() << std::endl;
  trace.info() << "     f=";
  f.selfDisplay( std::cerr );
  trace.info() << std::endl;
  return ok;
}

template <typename SB>
bool testContinuedFractions()
{
  unsigned int nbtests = 1000;
  unsigned int nbok = 0;
  unsigned int nb = 0;
  trace.beginBlock ( "Testing block: continued fraction." );
  for ( unsigned int i = 0; i < nbtests; ++i )
    {
      ++nb, nbok += testContinuedFraction<SB>() ? 1 : 0; 
      trace.info() << "(" << nbok << "/" << nb << ")"
                   << " continued fractions." << std::endl;
    }
  trace.endBlock();
  return nbok == nb;
}

/**
   Bug report of I. Sivignon.
*/
template <typename SB>
bool 
testAncestors()
{
  typedef typename SB::Fraction Fraction; 
  typedef StandardDSLQ0<Fraction> DSL;
  typedef typename DSL::Point Point;

  // Instanciation d'un DSL
  DSL D(1077,1495,6081);
  
  // Definition du sous-segment [AB] et calcul des caractéristiques
  Point A(3,-3);
  Point B(4,-2);
  ASSERT( D( A ) && "Point A belongs to D." );
  ASSERT( D( B ) && "Point A belongs to D." );
  DSL D1 = D.reversedSmartDSS(A,B); // may raise an assert.
  std::cerr << D1 << std::endl;
  return D1.slope() == Fraction( 1, 1 );
}


//-------------------------------------------
template <typename SB>
bool
testSimplestFractionInBetween()
{
  typedef typename SB::Fraction Fraction;
  Fraction f,g;
  unsigned int nb = 0;
  unsigned int nbok = 0;
  
  trace.beginBlock("Testing block: simplest fraction between two fractions");
  // When the two fractions are not ancestors of one other
  f = Fraction(1,5); g = Fraction(3,4);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(1,2) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;
  
  f = Fraction(4,7); g = Fraction(5,7);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(2,3) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;

  f = Fraction(3,8); g = Fraction(7,4);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(1,1) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;

  f = Fraction(11,7); g = Fraction(7,4);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(5,3) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;
  
  f = Fraction(8,13); g = Fraction(7,11);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(5,8) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;

  // When f is an ancestor of g or conversely
  f = Fraction(2,5); g = Fraction(4,9);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(3,7) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;
  
  f = Fraction(2,3); g = Fraction(8,11);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(5,7) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;

  f = Fraction(1,2); g = Fraction(5,9);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(6,11) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;

  f = Fraction(5,9); g = Fraction(2,3);
  ++nb, nbok += f.simplestFractionInBetween(g) == Fraction(3,5) ? 1 : 0;
  trace.info() << "(" << nbok << "/" << nb << ")" << std::endl;

  trace.endBlock();
  return nbok == nb;
}



///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int , char** )
{
  typedef SternBrocot<DGtal::int64_t,DGtal::int32_t> SB;
  typedef SB::Fraction Fraction;
  typedef Fraction::ConstIterator ConstIterator;

  BOOST_CONCEPT_ASSERT(( concepts::CPositiveIrreducibleFraction< Fraction > ));
  BOOST_CONCEPT_ASSERT(( boost::InputIterator< ConstIterator > ));

  trace.beginBlock ( "Testing class SternBrocot" );
  bool res = testSternBrocot()
    && testPattern<SB>()
    && testSubStandardDSLQ0<Fraction>()
    && testContinuedFractions<SB>()
    && testAncestors<SB>()
    && testSimplestFractionInBetween<SB>();
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
