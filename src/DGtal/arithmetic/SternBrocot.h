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
 * @file SternBrocot.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Xavier Provençal (\c xavier.provencal@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/07
 *
 * Header file for module SternBrocot.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SternBrocot_RECURSES)
#error Recursive header files inclusion detected in SternBrocot.h
#else // defined(SternBrocot_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SternBrocot_RECURSES

#if !defined SternBrocot_h
/** Prevents repeated inclusion of headers. */
#define SternBrocot_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/InputIteratorWithRankOnSequence.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SternBrocot
  /**
   Description of template class 'SternBrocot' <p> \brief Aim: The
   Stern-Brocot tree is the tree of irreducible fractions. This class
   allows to construct it progressively and to navigate within
   fractions in O(1) time for most operations. It is well known that
   the structure of this tree is a coding of the continued fraction
   representation of fractions.

   This class is not to be instantiated, since it is useless to
   duplicate it. Use static method SternBrocot::fraction to obtain
   your fractions.

   @tparam TInteger the integral type chosen for the fractions.

   @tparam TQuotient the integral type chosen for the
   quotients/coefficients or depth (may be "smaller" than TInteger,
   since they are generally much smaller than the fraction itself).
  */
  template <typename TInteger, typename TQuotient = int32_t>
  class SternBrocot
  {
  public:
    typedef TInteger Integer;
    typedef TQuotient Quotient;
    typedef SternBrocot<Integer,Quotient> Self;
    
    BOOST_CONCEPT_ASSERT(( concepts::CInteger< Integer > ));

  public:

    /**
       Represents a node in the Stern-Brocot. The node stores
       information on the irreducible fraction itself (p/q, the
       partial quotient u, the depth k), but also pointers to
       ascendants, descendants and inverse in the Stern-Brocot tree.
       Nodes are constructed on demand, when the user ask for
       descendant or for a specific fraction.

       @see SternBrocot::fraction

       Essentially a backport from <a
       href="https://gforge.liris.cnrs.fr/projects/imagene">ImaGene</a>.
    */
    struct Node {

      /**
         Constructor for node.

         @param p1 the numerator.
         @param q1 the denominator.
         @param u1 the quotient (last coefficient of its continued fraction).
         @param k1 the depth (1+number of coefficients of its continued fraction).
         @param ascendant_left1 the node that is the left ascendant.
         @param ascendant_right1 the node that is the right ascendant.
         @param descendant_left1 the node that is the left descendant or 0 (if none exist).
         @param descendant_right1 the node that is the right descendant or 0 (if none exist).
         @param inverse1 the node that is its inverse.
       */
      Node( Integer p1, Integer q1, Quotient u1, Quotient k1, 
	    Node* ascendant_left1, Node* ascendant_right1, 
	    Node* descendant_left1, Node* descendant_right1,
	    Node* inverse1 );

      /// the numerator;
      Integer p;
      /// the denominator;
      Integer q;
      /// the quotient (last coefficient of its continued fraction).
      Quotient u;
      /// the depth (1+number of coefficients of its continued fraction).
      Quotient k;
      /// the node that is the left ascendant.
      Node* ascendantLeft;
      /// the node that is the right ascendant.
      Node* ascendantRight;
      /// the node that is the left descendant or 0 (if none exist).
      Node* descendantLeft;
      /// the node that is the right descendant or 0 (if none exist).
      Node* descendantRight;
      /// the node that is its inverse.
      Node* inverse;
    };

    /**
       @brief This fraction is a model of CPositiveIrreducibleFraction.

       It represents a positive irreducible fraction, i.e. some p/q
       qith gcd(p,q)=1. It is an inner class of SternBrocot. This
       representation of a fraction is simply a pointer to the
       corresponding node in this tree.
    */
    class Fraction {
    public:
      typedef TInteger Integer;
      typedef TQuotient Quotient;
      typedef SternBrocot<TInteger,TQuotient> SternBrocotTree;
      typedef typename SternBrocotTree::Fraction Self;
      typedef typename NumberTraits<Integer>::UnsignedVersion UnsignedInteger;
      typedef std::pair<Quotient, Quotient> Value;
      typedef std::vector<Quotient> CFracSequence;
      typedef InputIteratorWithRankOnSequence<CFracSequence,Quotient> ConstIterator;

      // --------------------- std types ------------------------------
      typedef Value value_type;
      typedef ConstIterator const_iterator;
      typedef const value_type & const_reference;

    private:
      Node* myNode; 

    public:
      /** 
          Any fraction p/q. Complexity is in \f$ \sum_i
          u_i \f$, where u_i are the partial quotients of p/q.
          
          @param aP the numerator (>=0)
          @param aQ the denominator (>=0)
          
          @param ancestor (optional) any ancestor of aP/aQ in the tree
          (for speed-up).
          
          Construct the corresponding fraction in the Stern-Brocot tree.
          
          NB: Complexity is bounded by \f$ 2 \sum_i u_i \f$, where u_i
          are the partial quotients of aP/aQ.
      */
      Fraction( Integer aP, Integer aQ,
                Fraction ancestor = SternBrocotTree::zeroOverOne() );

      /**
	 Default constructor.
         @param sb_node the associated node (or 0 for null fraction).
      */
      Fraction( Node* sb_node = 0 );

      /**
         Copy constructor.
         @param other the object to clone.
      */
      Fraction( const Self & other );

      /**
         Assignment
         @param other the object to clone.
         @return a reference to 'this'.
      */
      Self& operator=( const Self & other );

      /// @return 'true' iff it is the null fraction 0/0.
      bool null() const;
      /// @return its numerator;
      Integer p() const;
      /// @return its denominator;
      Integer q() const;
      /// @return its quotient (last coefficient of its continued fraction).
      Quotient u() const;
      /// @return its depth (1+number of coefficients of its continued fraction).
      Quotient k() const;
      /// @return its left descendant (construct it if it does not exist yet).
      Fraction left() const;
      /// @return its right descendant (construct it if it does not exist yet).
      Fraction right() const;
      /// @return 'true' if it is an even fraction, i.e. its depth k() is even.
      bool even() const; 
      /// @return 'true' if it is an odd fraction, i.e. its depth k() is odd.
      bool odd() const; 
      /**
	 @return the father of this fraction in O(1), ie [u0,...,uk]
	 => [u0,...,uk - 1]
      */
      Fraction father() const;
      /**
         @param m a quotient between 1 and uk-1.
	 @return a given father of this fraction in O(uk - m), ie [u0,...,uk]
	 => [u0,...,m]

         @todo Do it in O(1)... but require to change the data structure.
      */
      Fraction father( Quotient m ) const;
      /**
	 @return the previous partial of this fraction in O(1), ie
	 [u0,...,u{k-1},uk] => [u0,...,u{k-1}]. Otherwise said, it is
	 its ascendant with a smaller depth.
      */
      Fraction previousPartial() const;
      /**
	 @return the inverse of this fraction in O(1), ie [u0,...,uk]
	 => [0,u0,...,uk] or [0,u0,...,uk] => [u0,...,uk].
      */
      Fraction inverse() const;
      /**
	 @param kp the chosen depth of the partial fraction (kp <= k()).

	 @return the partial fraction of depth kp, ie. [u0,...,uk] =>
	 [u0,...,ukp]
      */
      Fraction partial( Quotient kp ) const;
      /**
	 @param i a positive integer smaller or equal to k()+2.

	 @return the partial fraction of depth k()-i, ie. [u0,...,uk] =>
	 [u0,...,u{k-i}]
      */
      Fraction reduced( Quotient i ) const;

      /**
         Modifies this fraction \f$[u_0,...,u_k]\f$ to obtain the
         fraction \f$[u_0,...,u_k,m]\f$. The depth of the quotient
         must be given, since continued fractions have two writings
         \f$[u_0,...,u_k]\f$ and \f$[u_0,...,u_k - 1, 1]\f$.

         Useful to create output iterators, for instance with

         @code
         typedef ... Fraction; 
         Fraction f;
         std::back_insert_iterator<Fraction> itout = std::back_inserter( f );
         @endcode

         @param quotient the pair \f$(m,k+1)\f$.
      */
      void push_back( const std::pair<Quotient, Quotient> & quotient );

      /**
         Modifies this fraction \f$[u_0,...,u_k]\f$ to obtain the
         fraction \f$[u_0,...,u_k,m]\f$. The depth of the quotient
         must be given, since continued fractions have two writings
         \f$[u_0,...,u_k]\f$ and \f$[u_0,...,u_k - 1, 1]\f$.

         See push_back for creating output iterators.

         @param quotient the pair \f$(m,k+1)\f$.
      */         
      void pushBack( const std::pair<Quotient, Quotient> & quotient );

      /**
	 Splitting formula, O(1) time complexity. This fraction should
	 not be 0/1 or 1/0. NB: 'this' = [f1] @f$\oplus@f$ [f2].

	 @param f1 (returns) the left part of the split.
	 @param f2 (returns) the right part of the split.
      */
      void getSplit( Fraction & f1, Fraction & f2 ) const; 

      /**
	 Berstel splitting formula, O(1) time complexity. This
	 fraction should not be 0/1 or 1/0. NB: 'this' = nb1*[f1]
	 @f$\oplus@f$ nb2*[f2]. Also, if 'this->k' is even then nb1=1,
	 otherwise nb2=1.

	 @param f1 (returns) the left part of the split (left pattern).
	 @param nb1 (returns) the number of repetition of the left pattern
	 @param f2 (returns) the right part of the split (right pattern).
	 @param nb2 (returns) the number of repetition of the right pattern
      */
      void getSplitBerstel( Fraction & f1, Quotient & nb1, 
			    Fraction & f2, Quotient & nb2 ) const; 

      /**
	 @param quotients (returns) the coefficients of the continued
	 fraction of 'this'.
      */
      void getCFrac( std::vector<Quotient> & quotients ) const;

      /**
         @param p1 a numerator.
         @param q1 a denominator.
         @return 'true' if this is the fraction p1/q1.
      */
      bool equals( Integer p1, Integer q1 ) const;

      /**
         @param p1 a numerator.
         @param q1 a denominator.
         @return 'true' if this is < to the fraction p/q.
      */
      bool lessThan( Integer p1, Integer q1 ) const;

      /**
         @param p1 a numerator.
         @param q1 a denominator.
         @return 'true' if this is > to the fraction p1/q1.
      */
      bool moreThan( Integer p1, Integer q1 ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is equal to other.
      */
      bool operator==( const Fraction & other ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is different from other.
      */
      bool operator!=( const Fraction & other ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is < to other.
      */
      bool operator<( const Fraction & other ) const;

      /**
         @param other any fraction.
         @return 'true' iff this is > to other.
      */
      bool operator>( const Fraction & other ) const;

      /**
       * Writes/Displays the fraction on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const;

      /**
         @return a const iterator pointing on the beginning of the sequence of quotients of this fraction.
         NB: \f$ O(\sum_i u_i) \f$ operation. 
      */
      ConstIterator begin() const;

      /**
         @return a const iterator pointing after the end of the sequence of quotients of this fraction.
         NB: O(1) operation.
      */
      ConstIterator end() const;
      
      /**
	 @param g any fraction
	 @return the median of 'this' and g
       */

      Fraction median(const Fraction & g) const;
      

      /** 
       * Compute the fraction of smallest denominator strictly between
       * this fraction and other fraction. Assumes that "this" fraction is
       * smaller than "other" fraction.
       * @param other any fraction
       * @return a fraction
       * NB: \f$ O(k) \f$ where \f$ k \f$ is the depth of the output fraction.
       */
      Fraction simplestFractionInBetween(const Fraction & other) const;
	
    };

  

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~SternBrocot();

    /**
       @return the (only) instance of SternBrocot.
    */
    static SternBrocot & instance();

    /** The fraction 0/1 */
    static Fraction zeroOverOne();

    /** The fraction 1/0 */
    static Fraction oneOverZero();

    /** 
	Any fraction p/q. Complexity is in \f$ \sum_i
	u_i \f$, where u_i are the partial quotients of p/q.

	@param p the numerator (>=0)
	@param q the denominator (>=0)

	@param ancestor (optional) any ancestor of p/q in the tree
	(for speed-up).
	
	@return the corresponding fraction in the Stern-Brocot tree.

        NB: Complexity is bounded by \f$ 2 \sum_i u_i \f$, where u_i
        are the partial quotients of p/q.
    */
    static Fraction fraction( Integer p, Integer q,
                              Fraction ancestor = zeroOverOne() );

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the fraction on an output stream.
     * @param out the output stream where the object is written.
     * @param f the fraction to display.
     */
    static void display ( std::ostream & out, const Fraction & f );

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /// The total number of fractions in the current tree.
    Quotient nbFractions;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    /// Singleton class.
    static SternBrocot* singleton;

    Node* myZeroOverOne;
    Node* myOneOverZero;
    Node* myOneOverOne;

    // ------------------------- Hidden services ------------------------------
  private:

    /**
     * Constructor. Hidden since singleton class.
     */
    SternBrocot();

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    SternBrocot ( const SternBrocot & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    SternBrocot & operator= ( const SternBrocot & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class SternBrocot


  /**
   * Overloads 'operator<<' for displaying objects of class 'SternBrocot'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SternBrocot' to write.
   * @return the output stream after the writing.
   */
  // template <typename TInteger, typename TQuotient>
  // std::ostream&
  // operator<< ( std::ostream & out, 
  //              const typename SternBrocot<TInteger, TQuotient>::Fraction & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/SternBrocot.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SternBrocot_h

#undef SternBrocot_RECURSES
#endif // else defined(SternBrocot_RECURSES)
