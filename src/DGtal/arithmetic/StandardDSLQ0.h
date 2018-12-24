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
 * @file StandardDSLQ0.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Mouhammad Said (\c mouhammad.said@liris.cnrs.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France, and LIRIS (CNRS), University of Lyon 2.
 *
 * @date 2012/03/08
 *
 * Header file for module StandardDSLQ0.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(StandardDSLQ0_RECURSES)
#error Recursive header files inclusion detected in StandardDSLQ0.h
#else // defined(StandardDSLQ0_RECURSES)
/** Prevents recursive inclusion of headers. */
#define StandardDSLQ0_RECURSES

#if !defined StandardDSLQ0_h
/** Prevents repeated inclusion of headers. */
#define StandardDSLQ0_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/Pattern.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class StandardDSLQ0
  /**
  Description of template class 'StandardDSLQ0' <p> \brief Aim:
  Represents a digital straight line with slope in the first quadrant (Q0: x >= 0,
  y >= 0 ).

  It is the 4-connected set of points (x,y) of Z2 satisfying:

  \f$ mu <= ax - by < mu + a + b \f$

  You may move on it point by point with iterators ConstIterator.
  You can find upper and lower leaning points, find points on the
  DSL given one coordinate.  You may extract subsegment with smartDSS() and
  reversedSmartDSS() algorithms.

  @tparam TFraction the type chosen to represent fractions, a model
  of CFraction. You may use SternBrocot::Fraction for instance.

  Model of boost::CopyConstructible, boost::Assignable, concepts::CPointPredicate

  @see The documentation about @ref dgtal_digstraighness_sec3
  */
  template <typename TFraction>
  class StandardDSLQ0
  {
    // ----------------------- Standard types ------------------------------
  public:
    typedef TFraction Fraction;
    typedef StandardDSLQ0<TFraction> Self;
    typedef typename Fraction::Integer Integer;
    typedef typename Fraction::UnsignedInteger UnsignedInteger;
    typedef typename Fraction::Quotient Quotient;

    // BOOST_CONCEPT_ASSERT(( CFraction<Fraction> ));

    typedef IntegerComputer<Integer> IC;
    typedef typename IC::IntegerParamType IntegerParamType;
    typedef typename IC::Vector2I Vector2I;
    typedef typename IC::Point2I Point2I;

    // Model of concepts::CPointPredicate
    typedef typename IC::Point2I Point;

    /**
       The iterator to move in the standard digital straight line,
       point by point. To move from A to B on the DSL D, visiting
       [A,B], write:

       @code
       for ( ConstIterator it = D.begin( A ), it_end = D.end( B );
             it != it_end; ++it )
         Point P = *it;
       @endcode
    */
    struct ConstIterator {
      typedef ConstIterator Self;
      typedef Point Value;

      // stl iterator types.
      typedef std::forward_iterator_tag iterator_category;
      typedef Point value_type;
      typedef std::ptrdiff_t difference_type; 
      typedef const Point* pointer;
      typedef const Point& reference;

      inline ConstIterator()
        : myPtrDSL( 0 )
      {}
      inline ConstIterator( ConstAlias< StandardDSLQ0<TFraction> > myDSL,
                            const Point & p )
        : myPtrDSL( & myDSL ), myP( p )
      {}
      inline ConstIterator( const Self & other )
        : myPtrDSL( other.myPtrDSL ), myP( other.myP )
      {}
      inline Self& operator=( const Self & other )
      {
        if ( this != &other )
          {
            myPtrDSL = other.myPtrDSL;
            myP = other.myP;
          }
        return *this;
      }

      inline reference operator*() const
      {
        ASSERT( myPtrDSL != 0 );
        return myP;
      }

      inline pointer operator->() const
      { 
        ASSERT( myPtrDSL != 0 );
        return &myP;
      }

      inline Self& operator++()
      {
        Integer rem = myPtrDSL->r( myP );
        if ( rem - myPtrDSL->b() >= myPtrDSL->mu() )
          ++myP[ 1 ]; // +y;
        else
          ++myP[ 0 ]; // +x;
	return *this;
      }

      inline
      Self
      operator++(int)
      {
	Self __tmp = *this;
        this->operator++();
	return __tmp;
      }
      
      inline
      bool operator==( const Self & other ) const
      {
        ASSERT( myPtrDSL == other.myPtrDSL );
        return myP == other.myP;
      }

      inline
      bool operator!=( const Self & other ) const
      {
        return ! ( this->operator==( other ) );
      }


    private:
      const StandardDSLQ0<TFraction>* myPtrDSL;
      Point myP;
      
    };
    // ----------------------- Standard services ------------------------------
  public:

    /**
       Destructor.
     */
    ~StandardDSLQ0();

    /**
       Constructor. Null DSL.
     */
    StandardDSLQ0();

    /**
       Copy constructor.
       @param other the object to clone.
     */
    StandardDSLQ0 ( const StandardDSLQ0 & other );

    /**
       Assignment.
       @param other the object to copy.
       @return a reference on 'this'.
    */
    StandardDSLQ0 & operator= ( const StandardDSLQ0 & other );

    /**
       Creates the DSL(a,b,mu).
       @param aSlope the slope a/b, where gcd(a,b)=1
       @param aMu the shift to origin.
    */
    StandardDSLQ0( Fraction aSlope, IntegerParamType aMu );

    /**
       Creates the DSL(a/g,b/g,mu), where g = gcd( a, b).
       @param a1 any integer
       @param b1 any integer 
       @param mu1 the shift to origin.
    */
    StandardDSLQ0( IntegerParamType a1, IntegerParamType b1, 
                   IntegerParamType mu1 );

    /// @param p any point in Z2.
    /// @return 'true' iff the point \a p belongs to this.
    bool operator()( const Point & p ) const;

    /// @return the slope of this DSL, an irreducible fraction
    Fraction slope() const;

    /// @return the shift to origin, which is also the lower
    /// diopantine constraint.
    const Integer & mu() const;

    /// @return the upper diopantine constraint, ie. mu + a + b - 1
    Integer mup() const;

    /// @return a the numerator of the slope.
    Integer a() const;
    /// @return b the denominator of the slope.
    Integer b() const;
    /// @return the vector for the pattern, ie ( slope().q(), slope().p() )
    Vector2I v() const;

    /// @param p a point in the DSL.
    /// @return an iterator on the DSL pointing on \a p.
    ConstIterator begin( Point p ) const;

    /// @param p a point in the DSL.
    /// @return an iterator on the DSL pointing after \a p.
    ConstIterator end( Point p ) const;

    /// @return the pattern of this DSL
    const Pattern<Fraction> & pattern() const;

    /// Remainder a p.x - b p.y of point \a p in this DSL.
    /// @param p any point in Z2
    /// @return a p.x - b p.y
    Integer r( const Point & p ) const;

    /// @return the first upper leaning point of the DSL in the first
    /// quadrant (x >= 0).
    Point U() const;
    /// @return the first lower leaning point of the DSL with greater
    /// x than U().
    Point L() const;

    /// @return the point on this DSL with this \a x coordinate and
    /// lowest y coordinate.
    Point lowestY( IntegerParamType x ) const;
    /// @return the point on this DSL with this \a x coordinate and
    /// uppermost y coordinate.
    Point uppermostY( IntegerParamType x ) const;
    /// @return the point on this DSL with this \a y coordinate and
    /// lowest x coordinate.
    Point lowestX( IntegerParamType y ) const;
    /// @return the point on this DSL with this \a y coordinate and
    /// uppermost x coordinate.
    Point uppermostX( IntegerParamType y ) const;

    /// @return true if p1 is before p2 in the DSL.
    bool before( const Point & p1, const Point & p2 ) const;
    /// @return true if p1 is before or equal to p2 in the DSL.
    bool beforeOrEqual( const Point & p1, const Point & p2 ) const;
    

    /**
       Algorithm ReversedSmartDSS. See M. Said and J.-O. Lachaud,
       DGCI2010.

       Computes the exact characteristics of the subsegment [A,B] of
       this DSL in time O(log(|B-A|)). An even better bound in the
       output is achieved.
       
       @param A any point belonging to this DSL, A < B.
       @param B any point belonging to this DSL, A < B.

       @return the minimal DSL containing [A,B].
    */
    Self reversedSmartDSS( const Point & A, const Point & B ) const;

    /**
       Algorithm ReversedSmartDSS. See M. Said and J.-O. Lachaud,
       DGCI2010.

       Computes the exact characteristics of the subsegment [A,B] of
       this DSL in time O(log(|B-A|)). An even better bound in the
       output is achieved.
       
       @param A any point belonging to this DSL, A < B.
       @param B any point belonging to this DSL, A < B.
       @param U1 the first upper leaning point such that U1 <= A.
       @param U2 the second upper leaning point such that B <= U2.

       @return the minimal DSL containing [A,B].
       @see reversedSmartDSS( const Point & A, const Point & B )
    */
    Self reversedSmartDSS( Point U1, Point U2,
                           const Point & A, const Point & B ) const;

    /**
       Used by reversedSmartDSS.
       Computes the exact characteristics of the subsegment [A,B] of
       this DSL. Note that |U2-U1| = 2 * length().
       
       @param A any point belonging to this DSL, A < B.
       @param B any point belonging to this DSL, A < B.
       @param U1 the first upper leaning point such that U1 <= A.
       @param U2 the second upper leaning point such that B <= U2.

       @return the minimal DSL containing [A,B].
    */
    Self DSSWithinTwoPatterns( Point U1, Point U2,
                               const Point & A, const Point & B ) const;


    /**
       Algorithm SmartDSS. See M. Said and J.-O. Lachaud,
       DGCI2009.

       Computes the exact characteristics of the subsegment [A,B] of
       this DSL in time O(sum_k u_k), where the continued fraction of
       this DSL slope a/b is [u_0; u_1, u_2, ... ]
       
       @param A any point belonging to this DSL, A < B.
       @param B any point belonging to this DSL, A < B.

       @return the minimal DSL containing [A,B].
    */
    Self smartDSS( const Point & A, const Point & B ) const;

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
  protected:
    /// the characteristic pattern of this DSL.
    Pattern<Fraction> myPattern;
    /// the shift to origin.
    Integer myMu;

    // ------------------------- Private Datas --------------------------------
  private:
    /// Used in some computations.
    IC ic;

    // ------------------------- Hidden services ------------------------------
  protected:
    
    // ------------------------- Internals ------------------------------------
  private:
    static Fraction deepest( Fraction f1, Fraction f2, Fraction f3 );
    static Fraction deepest( Fraction f1, Fraction f2 );
  }; // end of class StandardDSLQ0


  /**
   * Overloads 'operator<<' for displaying objects of class 'StandardDSLQ0'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'StandardDSLQ0' to write.
   * @return the output stream after the writing.
   */
  template <typename TFraction>
  std::ostream&
  operator<< ( std::ostream & out, const StandardDSLQ0<TFraction> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/StandardDSLQ0.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined StandardDSLQ0_h

#undef StandardDSLQ0_RECURSES
#endif // else defined(StandardDSLQ0_RECURSES)
