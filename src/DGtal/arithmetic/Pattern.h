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

#pragma once

/**
 * @file Pattern.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/07
 *
 * Header file for module Pattern.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Pattern_RECURSES)
#error Recursive header files inclusion detected in Pattern.h
#else // defined(Pattern_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Pattern_RECURSES

#if !defined Pattern_h
/** Prevents repeated inclusion of headers. */
#define Pattern_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/arithmetic/CPositiveIrreducibleFraction.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/SternBrocot.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Pattern
  /**
     Description of template class 'Pattern' <p> \brief Aim: This
     class represents a pattern, i.e. the path between two consecutive
     upper leaning points on a digital straight line.

     A pattern is characterized by an irreducible fraction. The choice
     here is to use SternBrocot::Fraction so as to compute efficiently
     subpatterns.

     @tparam TFraction the type chosen to represent fractions, a model
     of CPositiveIrreducibleFraction. You may use
     SternBrocot::Fraction or LighterSternBrocot::Fraction for
     instance.

     @note LighterSternBrocot::Fraction takes much less memory than
     SternBrocot::Fraction and is more efficient for large
     integers. It is 10% slower than SternBrocot::Fraction for small
     integers (<1000).

     @see dgtal_digstraighness_sec2
  */
  template <typename TFraction>
  class Pattern
  {
  public:
    typedef TFraction Fraction;
    BOOST_CONCEPT_ASSERT(( concepts::CPositiveIrreducibleFraction< Fraction > ));

    typedef Pattern<TFraction> Self;
    typedef typename Fraction::Integer Integer;
    typedef typename Fraction::Quotient Quotient;
    
    // BOOST_CONCEPT_ASSERT(( CInteger< Quotient > ));

    // ----------------------- associated types ------------------------------
  public:

    typedef IntegerComputer<Integer> IC;
    typedef typename IC::Point2I Point2I;
    typedef typename IC::Vector2I Vector2I;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~Pattern();

    /**
       Constructor from fraction.
       @param f any fraction (default is null pattern).
     */
    Pattern( Fraction f = Fraction( 0 ) );

    /**
       Constructor from numerator / denominator.
       @param p the numerator.
       @param q the denominator.
     */
    Pattern( Integer p, Integer q );

    /**
       Copy constructor.
       @param other the object to clone.
     */
    Pattern ( const Pattern & other );

    /**
       Assignment.
       @param other the object to copy.
       @return a reference on 'this'.
     */
    Pattern & operator= ( const Pattern & other );

    // ----------------------- Pattern services -------------------------------
  public:

    /// The recursive mapping E, which gives the corresponding
    /// Christoffel word in {0,1}.
    std::string rE() const;

    /// The recursive mapping E, which gives the corresponding
    /// Christoffel word in {0,1}, but also shows the Berstel splits
    /// with "(|)".  @param seps the three separators.
    std::string rEs( const std::string & seps = "(|)" ) const;

    /// @return the slope of this pattern, an irreducible fraction
    Fraction slope() const;

    /// @return the digital length of the pattern, i.e. slope.p() + slope.q().
    Integer length() const;

    /// @return the position of the k-th upper leaning point, @param k
    /// its index ( posU( 0 ) == 0 ).
    Integer posU( Quotient k ) const;

    /// @return the position of the k-th lower leaning point, @param k
    /// its index ( posU( 0 ) <= posL( 0 ) < posU( 1 ) ).
    Integer posL( Quotient k ) const;

    /// @return the coordinates of the k-th upper leaning point, @param k
    /// its index ( U( 0 ) == (0,0) ).
    Point2I U( Quotient k ) const;

    /// @return the coordinates of the k-th lower leaning point, @param k
    /// its index ( L( 0 ) is between U( 0 ) and U( 1 ) ).
    Point2I L( Quotient k ) const;

    /// @return the Bezout vector for the pattern, such that bezout()
    /// is oriented in the first quadrant, slightly to the left of the
    /// slope, and shorter.
    Vector2I bezout() const;
    /// @return the vector for the pattern, ie ( slope().q(), slope().p() )
    Vector2I v() const;

    /// @return the pattern of slope z_{n-1} if z_n was the slope of 'this'.
    Pattern previousPattern() const;


    /**
       Computes the smallest subpattern that contains the segment
       [A,B] included in the pattern. Points A and B are defined by
       their position with respect to the beginning of this pattern.
       The \a subpattern has a starting position \a startPos and may
       be repeated \a nb times.

       @param subpattern (returns) the subpattern (a pattern that is
       some ascendant of 'this' in the Stern-Brocot tree).

       @param nb (returns) the number of times \a subpattern is
       repeated so as to cover [A,B]

       @param startPos (returns) the starting position of the
       subpattern in this pattern.

       @param posA the position of A (number of steps till A).
       @param posB the position of B (number of steps till B), > posA.

       @param reversed when 'false' assume a usual pattern, otherwise
       assume a reversed pattern (i.e. a path between two lower
       leaning points). In this case, all positions are relative to
       the first lower leaning point L(0). Everything returned
       correspond to reversed pattern(s).
       
       @return 'true' iff the subpattern is different from 'this'.
    */
    bool
    getSmallestCoveringSubpattern( Pattern & subpattern,
                                   Quotient & nb,
                                   Vector2I & startPos,
                                   Integer posA, Integer posB,
                                   bool reversed = false ) const;

    /**
       Computes the greatest subpattern that is included in the
       segment [A,B], a subpart of the pattern. Points A and B are
       defined by their position with respect to the beginning of this
       pattern.  The \a subpattern has a starting position \a startPos
       and may be repeated \a nb times.

       @param subpattern (returns) the subpattern (a pattern that is
       some ascendant of 'this' in the Stern-Brocot tree).

       @param nb (returns) the number of times \a subpattern is
       repeated so as to be included in [A,B]

       @param startPos (returns) the starting position of the
       subpattern in this pattern.

       @param posA the position of A (number of steps till A).
       @param posB the position of B (number of steps till B), > posA.
       
       @param reversed when 'false' assume a usual pattern, otherwise
       assume a reversed pattern (i.e. a path between two lower
       leaning points). In this case, all positions are relative to
       the first lower leaning point L(0). Everything returned
       correspond to reversed pattern(s).

       @return 'true' iff the subpattern is not null.
    */
    bool
    getGreatestIncludedSubpattern( Pattern & subpattern,
                                   Quotient & nb,
                                   Vector2I & startPos,
                                   Integer posA, Integer posB,
                                   bool reversed = false ) const;

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /// The fraction that characterizes the slope of the pattern.
    Fraction mySlope;

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Pattern


  /**
   * Overloads 'operator<<' for displaying objects of class 'Pattern'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Pattern' to write.
   * @return the output stream after the writing.
   */
  template <typename TFraction>
  std::ostream&
  operator<< ( std::ostream & out, const Pattern<TFraction> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/Pattern.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Pattern_h

#undef Pattern_RECURSES
#endif // else defined(Pattern_RECURSES)
