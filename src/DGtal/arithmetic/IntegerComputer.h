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
 * @file IntegerComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/05
 *
 * Header file for module IntegerComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IntegerComputer_RECURSES)
#error Recursive header files inclusion detected in IntegerComputer.h
#else // defined(IntegerComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IntegerComputer_RECURSES

#if !defined IntegerComputer_h
/** Prevents repeated inclusion of headers. */
#define IntegerComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CUnsignedNumber.h"
#include "DGtal/kernel/CIntegralNumber.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/SpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class IntegerComputer
  /**
Description of template class 'IntegerComputer' <p> \brief Aim:
This class gathers several types and methods to make computation
with integers.

This class is especially useful with using big integers (like
GMP), since a substantial part of the execution time cames from
the allocation/desallocation of integers. The idea is that the
user instantiate once this object and computes gcd, bezout,
continued fractions with it.

To be thread-safe, each thread \b must instantiate an
IntegerComputer.

It is a model of boost::CopyConstructible,
boost::DefaultConstructible, boost::Assignable. All its member data are
\b mutable.

It is a backport of <a
href="https://gforge.liris.cnrs.fr/projects/imagene">ImaGene</a>.

@tparam TInteger any model of integer (CInteger), like \c int, \c long int,
\c int64_t, \c BigInteger (when GMP is installed).
   
   */
  template <typename TInteger>
  class IntegerComputer
  {
    // ----------------------- Associated types ------------------------------
  public:
    typedef IntegerComputer<TInteger> Self;
    typedef typename NumberTraits<TInteger>::SignedVersion Integer;
    typedef typename NumberTraits<Integer>::ParamType IntegerParamType;

    typedef typename NumberTraits<TInteger>::UnsignedVersion UnsignedInteger;
    typedef typename NumberTraits<UnsignedInteger>::ParamType UnsignedIntegerParamType;

    typedef typename SpaceND<2,Integer>::Point Point2I;
    typedef typename SpaceND<2,Integer>::Vector Vector2I;
    typedef typename SpaceND<3,Integer>::Point Point3I;
    typedef typename SpaceND<3,Integer>::Vector Vector3I;

    BOOST_CONCEPT_ASSERT((concepts::CInteger<Integer>));
    BOOST_CONCEPT_ASSERT((concepts::CUnsignedNumber<UnsignedInteger>));
    BOOST_CONCEPT_ASSERT((concepts::CIntegralNumber<UnsignedInteger>));

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~IntegerComputer();

    /**
       Constructor.  Each thread must have its own instance for all
       computations. Such object stores several local variables to
       limit the number of memory allocations.
     
       Does nothing (member data are allocated, but their values are
       not used except during the execution of methods).
     */
    IntegerComputer();

    /**
       Copy constructor.
       
       Does nothing (member data are allocated, but their values are
       not used except during the execution of methods).

       @param other the object to clone.
     */
    IntegerComputer ( const Self & other );

    /**
       Assignment.

       Does nothing (member data are allocated, but their values are
       not used except during the execution of methods).

       @param other the object to copy.
       @return a reference on 'this'.
     */
    Self & operator= ( const Self & other );


    // ----------------------- Integer services ------------------------------
  public:

    /**
       @param a any integer.
       @return true if a == 0.
     */
    static bool isZero( IntegerParamType a );

    /**
       @param a any integer.
       @return true if a != 0.
     */
    static bool isNotZero( IntegerParamType a );

    /**
       @param a any integer.
       @return true if a > 0.
     */
    static bool isPositive( IntegerParamType a );

    /**
       @param a any integer.
       @return true if a < 0.
     */
    static bool isNegative( IntegerParamType a );

    /**
       @param a any integer.
       @return true if a >= 0.
     */
    static bool isPositiveOrZero( IntegerParamType a );

    /**
       @param a any integer.
       @return true if a <= 0.
     */
    static bool isNegativeOrZero( IntegerParamType a );

    /**
       @param a any integer.
       @return its absolute value.
     */
    static Integer abs( IntegerParamType a );

    /**
       @param a any integer.
       @param b any integer.
       @return the maximum value of \a a and \a b.
     */
    static Integer max( IntegerParamType a, IntegerParamType b );

    /**
       @param a any integer.
       @param b any integer.
       @param c any integer.
       @return the maximum value of \a a, \a b and \a c.
     */
    static Integer max( IntegerParamType a, IntegerParamType b, IntegerParamType c );

    /**
       @param a any integer.
       @param b any integer.
       @return the minimum value of \a a and \a b.
     */
    static Integer min( IntegerParamType a, IntegerParamType b );

    /**
       @param a any integer.
       @param b any integer.
       @param c any integer.
       @return the minimum value of \a a, \a b and \a c.
     */
    static Integer min( IntegerParamType a, IntegerParamType b, IntegerParamType c );

    /**
       Computes the euclidean division of a/b, returning quotient and
       remainder. May be faster than computing separately quotient and
       remainder, depending on the integral type in use.

       @todo Specialize it for GMP as mpz_fdiv_qr (q.get_mpz_t(),
       r.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());

       @param q (returns) the quotient of a/b.
       @param r (returns) the remainder of a/b.
       @param a any integer.
       @param b any integer.
     */
    void getEuclideanDiv( Integer & q, Integer & r,
                       IntegerParamType a, IntegerParamType b ) const;

    /**
       Computes the floor value of na/nb.

       @param na any integer.
       @param nb any integer.
     */
    Integer floorDiv( IntegerParamType na, IntegerParamType nb ) const;

    /**
       Computes the ceil value of na/nb.

       @param na any integer.
       @param nb any integer.
     */
    Integer ceilDiv( IntegerParamType na, IntegerParamType nb ) const;

    /**
       Computes the floor and ceil value of na/nb.

       @param fl (returns) the floor value of na/nb.
       @param ce (returns) the ceil value of na/nb.
       @param na any integer.
       @param nb any integer.
     */
    void getFloorCeilDiv( Integer & fl, Integer & ce,
                          IntegerParamType na, IntegerParamType nb ) const;

    /**
       Returns the greatest common divisor of \a a and \a b (\a a and \a b may be
       either positive or negative).

       @param a any integer.
       @param b any integer.
       @return the gcd of \a a and \a b.
     */
    static Integer staticGcd( IntegerParamType a, IntegerParamType b );

    /**
       Returns the greatest common divisor of \a a and \a b (\a a and \a b may be
       either positive or negative).

       @param a any integer.
       @param b any integer.
       @return the gcd of \a a and \a b.
     */
    Integer gcd( IntegerParamType a, IntegerParamType b ) const;

    /**
       Returns the greatest common divisor of \a a and \a b (\a a and \a b may be
       either positive or negative).

       @param g (returns) the gcd of \a a and \a b.
       @param a any integer.
       @param b any integer.
    */
    void getGcd( Integer & g, IntegerParamType a, IntegerParamType b ) const;

    /**
       Computes and push_backs the simple continued fraction of a / b.
       (positive) and b (positive). For instance, 5/13=[0;2,1,1,2],
       which is exactly what is pushed at the back of \a quotients.
 
       @param quotients (modifies) adds to the back of the vector the quotients of the continued fraction of a/b.
       @param a any positive integer.
       @param b any positive integer.
       @return the gcd of \a a and \a b.
    */
    Integer getCFrac( std::vector<Integer> & quotients,
                   IntegerParamType a, IntegerParamType b ) const;
    /**
       Computes and outputs the quotients of the simple continued
       fraction of a / b.  (positive) and b (positive). For instance,
       5/13=[0;2,1,1,2], which is exactly what is outputed with the
       OutputIterator outIt.
 
       @tparam OutputIterator a model of boost::OutputIterator

       @param outIt an instance of output iterator that is used to
       write the successive quotients of the continued fraction of
       a/b.
       @param a any positive integer.
       @param b any positive integer.
       @return the gcd of \a a and \a b.
    */
    template <typename OutputIterator>
    Integer getCFrac( OutputIterator outIt,
                      IntegerParamType a, IntegerParamType b ) const;

    /**
       Returns the fraction corresponding to the given quotients, more
       precisely its k-th principal convergent. When k >=
       quotients.size() - 1, it is the inverse of the function
       getCFrac.

       @param quotients the sequence of partial quotients.
       @param k the desired partial convergent.
       @return the corresponding fraction p_k / q_k as a point (p_k, q_k).
    */
    Point2I convergent( const std::vector<Integer> & quotients,
                        unsigned int k ) const;

    // ----------------------- Point2I services ------------------------------
  public:
    /**
       Makes \a p irreducible.
       
       @param p any vector in Z2.
     */
    void reduce( Vector2I & p ) const ;


    /**
       Computes and returns the cross product of \a u and \a v.

       @param u any vector in Z2.
       @param v any vector in Z2. 
       @return the cross product of \a u and \a v.
    */
    Integer crossProduct( const Vector2I & u, const Vector2I & v) const;

    /**
       Computes the cross product of \a u and \a v.

       @param cp (returns) the cross product of \a u and \a v.
       @param u any vector in Z2.
       @param v any vector in Z2.
     */
    void getCrossProduct( Integer & cp, 
                          const Vector2I & u, const Vector2I & v) const;

    /**
       Computes and returns the dot product of \a u and \a v.

       @param u any vector in Z2.
       @param v any vector in Z2.
       @return the dot product of \a u and \a v.
     */
    Integer dotProduct( const Vector2I & u, const Vector2I & v ) const;

    /**
       Computes and returns the dot product of \a u and \a v.

       @param dp (returns) the dot product of \a u and \a v.
       @param u any vector in Z2.
       @param v any vector in Z2.
     */
    void getDotProduct( Integer & dp, 
                        const Vector2I & u, const Vector2I & v) const;

    /**
       Returns a solution of the Diophantine equation: a x + b y =
       c. The integer \a c should be a multiple of the gcd of \a a and
       \a b. Uses the extended Euclid algorithm to do it, whose
       complexity is bounded by max(log(a),log(b)).

       The solution is chosen such that:
       - when \a c > 0, 
         - \a a > 0 implies \a x >= 0, thus sgn(\a y)=-sgn(\a b)
         - \a a < 0 implies \a x <= 0, thus sgn(\a y)=-sgn(\a b)
       - when \a c < 0, 
         - \a a > 0 implies \a x <= 0, thus sgn(\a y)=sgn(\a b)
         - \a a < 0 implies \a x >= 0, thus sgn(\a y)=sgn(\a b)
       - abs(\a x) <= abs(\a b * \a c )
       - abs(\a y) < abs(\a a * \a c )

       @param a any non-null integer.
       @param b any non-null integer.
       @param c any integer multiple of gcd(|a|,|b|).
       @return a vector (x,y) solution to a x + b y = c.
     */
    Vector2I extendedEuclid( IntegerParamType a, IntegerParamType b, 
                             IntegerParamType c ) const;

    /**
       Computes the floor (fl) and the ceiling (ce) value of the real
       number k such that p + k u lies on the supporting line of the
       linear constraint N.p <= c. 

       Otherwise said: (u.N) fl <= c - p.N < (u.N) ce

       @param fl the greatest integer such that (u.N) fl <= c - p.N
       @param ce the smallest integer such that c - p.N  < (u.N) ce
       @param p any vector in Z2
       @param u any vector in Z2 in the same quadrant as N.
       @param N any vector in Z2 in the same quadrant as u.
       @param c any integer.
     */
    void getCoefficientIntersection( Integer & fl, Integer & ce,
                                     const Vector2I & p, 
                                     const Vector2I & u, 
                                     const Vector2I & N, 
                                     IntegerParamType c ) const;
				  
    /**
       Compute the valid bezout vector v of u such that A+v satifies
       the constraints C2 and such that A+v+u doesn't satify the
       constraint C2. 
       
       (A+v).N2   <= c2,
       (A+v+u).N2 >  c2.

       The constraint (N,c) is used like this: if the Bezout is such
       that (A+v).N > c, then v <- -v. Thus v is oriented toward the
       constraint.

       If ! compute_v, v is used as is. The constraint N.(A+v) <= c
       should be satisfied.

       @param v (modifies) a Bezout vector for u, with the constraints above.
       @param A any point in Z2.
       @param u any vector in Z2.
       @param N any vector in Z2, defining the first constraint.
       @param c the integer for the first constraint.
       @param N2 any vector in Z2, defining the second constraint.
       @param c2 the integer for the second constraint.
       @param compute_v tells if v should be recomputed (true) or is
       already given (false), default to true.
     */
    void getValidBezout ( Vector2I & v, 
                          const Point2I & A, const Vector2I & u,
                          const Vector2I & N, IntegerParamType c, 
                          const Vector2I & N2, IntegerParamType c2, 
                          bool compute_v = true ) const;

    // ----------------------- Point3I services ------------------------------
  public:

    /**
       Makes \a p irreducible.
       
       @param p any vector in Z3.
     */
    void reduce( Vector3I & p ) const;

    /**
       Computes and returns the dot product of \a u and \a v.

       @param u any vector in Z2.
       @param v any vector in Z2.
       @return the dot product of \a u and \a v.
     */
    Integer dotProduct( const Vector3I & u, const Vector3I & v) const;

    /**
       Computes and returns the dot product of \a u and \a v.

       @param dp (returns) the dot product of \a u and \a v.
       @param u any vector in Z3.
       @param v any vector in Z3.
     */
    void getDotProduct( Integer & dp, 
                        const Vector3I & u, const Vector3I & v) const;


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

    /// Used to store parameter a.
    mutable Integer _m_a;
    /// Used to store parameter b.
    mutable Integer _m_b;
    /// Used to for successive computation in gcd
    mutable Integer _m_a0;
    /// Used to for successive computation in gcd
    mutable Integer _m_a1;
    /// Used to represent a quotient
    mutable Integer _m_q;
    /// Used to represent a remainder.
    mutable Integer _m_r;
    /// Used to represent the variables during an extended Euclid
    /// computation, [0] are remainders, [1] are quotients, [2] are
    /// successive a, [3] are successive b.
    mutable std::vector<Integer> _m_bezout[ 4 ];
    /// Used to represent the Bezout vector.
    mutable Vector2I _m_v;
    /// Used to represent vectors.
    mutable Vector2I _m_v0;
    /// Used to represent vectors.
    mutable Vector2I _m_v1;
    /// Used to represent scalar products.
    mutable Integer _m_c0;
    /// Used to represent scalar products.
    mutable Integer _m_c1;
    /// Used to represent scalar products.
    mutable Integer _m_c2;

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class IntegerComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'IntegerComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'IntegerComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TInteger>
  std::ostream&
  operator<< ( std::ostream & out, const IntegerComputer<TInteger> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/IntegerComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IntegerComputer_h

#undef IntegerComputer_RECURSES
#endif // else defined(IntegerComputer_RECURSES)
