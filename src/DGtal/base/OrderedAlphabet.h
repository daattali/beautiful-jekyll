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
 * @file OrderedAlphabet.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author Laurent Provot (\c Laurent.Provot@loria.fr )
 * LORIA (CNRS, UMR 7503), Nancy University, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/01
 *
 * Header file for module OrderedAlphabet.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(OrderedAlphabet_RECURSES)
#error Recursive header files inclusion detected in OrderedAlphabet.h
#else // defined(OrderedAlphabet_RECURSES)
/** Prevents recursive inclusion of headers. */
#define OrderedAlphabet_RECURSES

#if !defined OrderedAlphabet_h
/** Prevents repeated inclusion of headers. */
#define OrderedAlphabet_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/arithmetic/ModuloComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class OrderedAlphabet
  /**
   * Description of class 'OrderedAlphabet' <p>
   * \brief Aim: Describes an alphabet over an interval of (ascii) letters,
   * where the lexicographic order can be changed (shifted, reversed, ...).
   * Useful for the arithmetic minimum length polygon (AMLP).
   *
   * Standard operators '<' and '<=' compares letters using their ascii codes. 
   * In order to compare letters with respect to an 'OrderedAlphabet', one uses
   * the classe's functions 'less' and 'lessOrEqual'.
   */
  class OrderedAlphabet
  {
    // ----------------------- Standard types ------------------------------
  public:

    /**
     * Internal integer type to consider in the OrderdAlphabet class.
     */
    typedef int Integer;
     
    /**
     * The index datatype.
     */
    typedef unsigned int index_t;

    /**
     * The size datatype.
     */
    typedef unsigned int size_t;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~OrderedAlphabet();

    /**
     * Constructor from letters
     *
     * @param first the first letter of the alphabet.
     * @param nb the number of letters of the alphabet.
     *
     * Exemple: OrderedAlphabet( '0', 4 ) defines the alphabet for
     * 4-connected freeman chains.
     */
    OrderedAlphabet( char first, unsigned int nb );

    /**
     * @return the current ordered alphabet.
     */
    std::string orderedAlphabet() const;

    /**
     * Shift a0 < a1 < ... < an to a1 < ... < an < a0
     */
    void shiftLeft();

    /**
     * Shift a0 < a1 < ... < an to an < a0 < ... < an-1
     */
    void shiftRight();

    /**
     * Reverse the order a0 < a1 < ... < an to an < ... < a1 < a0
     */
    void reverse();

    /**
     * Reverse the order a0 < a1 < ... < an to a3 < a2 < a1 < a0 < an < ... 
     */
    void reverseAround12();
    
    /**
     * @param c any valid letter in this alphabet.
     *
     * @return the index of the letter [c] in the order relation,
     * starting from 0 to myNb-1.
     */
    unsigned int order( char c ) const;

    /**
     * @param i the index of some letter in the order relation,
     * between 0 and myNb-1.
     *
     * @return c the corresponding letter in this alphabet.
     *
     * NB: O(nb of letters in the alphabet).
     */
    char letter( unsigned int i ) const;

    /**
     * @param c1 a letter in the alphabet
     * @param c2 another letter in the same alphabet.
     * @return 'true' iff c1 < c2
     */
    bool less( char c1, char c2 ) const;

    /**
     * @param c1 a letter in the alphabet
     * @param c2 another letter in the same alphabet.
     * @return 'true' iff c1 <= c2
     */
    bool lessOrEqual( char c1, char c2 ) const;

    /**
     * @param c1 a letter in the alphabet
     * @param c2 another letter in the same alphabet.
     * @return 'true' iff c1 == c2
     */
    bool equal( char c1, char c2 ) const;

    // ----------------------- word services ------------------------------
  public:

    /**
     * Gives the first lyndon factor of the word [w] starting at
     * position [s] in this alphabet.
     *
     * @param len (returns) the length of the primitive Lyndon factor
     * (which starts at position s).
     *
     * @param nb (returns) the number of times the Lyndon factor appears.
     * 
     * @param w a word
     * @param s the starting index in [w].
     * @param e the index after the end in [w] (s<e).
     */
    void firstLyndonFactor( size_t & len, size_t & nb,
          const std::string & w, 
          index_t s, index_t e ) const;


    /**
     * Gives the first lyndon factor of the cyclic word [w]
     * starting at position [s] in this alphabet.
     *
     * @param len (returns) the length of the primitive Lyndon factor
     * (which starts at position s).
     *
     * @param nb (returns) the number of times the Lyndon factor appears.
     * 
     * @param w a word
     * @param s the starting index in [w].
     * @param e the index after the end in [w] (s and e arbitrary).
     */
    void firstLyndonFactorMod( size_t & len, size_t & nb,
             const std::string & w, 
             index_t s, index_t e ) const;


      /**
     * Adaptation of Duval's algorithm to extract the first Lyndon factor
     * (FLF). Whilst scanning the Lyndon factor, it also checks whether it
     * is a Christoffel word or not. It returns 'true' if the FLF is
     * indeed a Christoffel word, otherwise returns false. It starts the
     * extraction at position [s] in the word [w].
     *
     * The alphabet takes the form a0 < a1 < a2 < ... < an-1. [w] starts
     * with a1 or a2 at position s.
     *
     * See [Provencal, Lachaud 2009].
     *
     * @param len (returns) the length of the primitive Lyndon factor
     * (which starts at position s).
     *
     * @param nb (returns) the number of times the Lyndon factor appears.
     * 
     * @param w a word which starts with a1 or a2 at position s.
     * @param s the starting index in [w].
     * @param e the index after the end in [w] (s<e).
     */
    bool duvalPP( size_t & len, size_t & nb,
      const std::string & w, 
      index_t s, index_t e
      ) const;

    /**
     * Adaptation of Duval's algorithm to extract the first Lyndon factor
     * (FLF). Whilst scanning the Lyndon factor, it also checks whether it
     * is a Christoffel word or not. It returns 'true' if the FLF is
     * indeed a Christoffel word, otherwise returns false. It starts the
     * extraction at position [s] in the cyclic word [w].
     *
     * The alphabet takes the form a0 < a1 < a2 < ... < an-1. [w] starts
     * with a1 or a2 at position s.
     *
     * See [Provencal, Lachaud 2009].
     *
     * @param len (returns) the length of the primitive Lyndon factor
     * (which starts at position s).
     *
     * @param nb (returns) the number of times the Lyndon factor appears.
     * 
     * @param w a (cyclic) word which starts with a1 or a2 at position s.
     * @param s the starting index in [w].
     * @param e the index after the end in [w] (s and e arbitrary).
     */
    bool duvalPPMod( size_t & len, size_t & nb,
        const std::string & w, 
        index_t s, index_t e ) const;
    /**
     * Second version of the algorithm Duval++ (see OrderedAlphabet::duvalPP),
     * this one dynamically returns extra informations in order to compute
     * leanning points.
     * 
     * @param len (returns) the length of the primitive Lyndon factor
     * (which starts at position s).
     *
     * @param nb (returns) the number of times the Lyndon factor appears.
     *
     * @param n1 (returns) the number of occurrences of the letter a1
     * in the Lyndon factor
     *
     * @param n2 (returns) the number of occurrences of the letter a2
     * in the Lyndon factor
     *
     * @param Lf1 (returns) the number of occurrences of the letter a1
     * from 's' to the first lower leaning point.
     *
     * @param Lf2 (returns) the number of occurrences of the letter a2
     * from 's' to the first lower leaning point.
     * 
     * @param w a word which starts with a1 or a2 at position s.
     * @param s the starting index in [w].
     * @param e the index after the end in [w] (s<e).
     */
    bool duvalPPtoDSS( size_t & len, size_t & nb,
      unsigned int & n1,  unsigned int & n2,
      unsigned int & Lf1, unsigned int & Lf2,
      const std::string & w, 
      index_t s, index_t e
      ) const;



    // ----------------------- MLP services -----------------------------------
  public:

    /**
     * Extracts the next edge of the minimum length polygon starting from
     * position [s] on the word [w]. The alphabet may be modified
     * (reversed or shifted). The output alphabet is some a0 < a1 < a2 < ...
     *
     * @param nb_a1 (returns) the number of letters a1 in the extracted edge (a1
     * in the output alphabet)
     *
     * @param nb_a2 (returns) the number of letters a2 in the extracted edge (a2
     * in the output alphabet)
     *
     * @param w the input (cyclic) word (may be modified in the process).
     *
     * @param s the starting point in the word (updated).
     *
     * @param cvx (updates) this boolean is flipped only if a change of
     * convexity is detected.
     *
     * @return the number of letters of the extracted edge.
     */ 
    size_t nextEdge( size_t & nb_a1, size_t & nb_a2,
         std::string & w, index_t & s, bool & cvx );


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
    /**
     * the first character.
     */
    char myFirst;

    /**
     * the number of letters.
     */
    unsigned int myNb;

    /**
     * the order relation, given by the isomorphism with 0..myNb-1.
     */
    unsigned int* myOrder;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    OrderedAlphabet();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    OrderedAlphabet ( const OrderedAlphabet & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    OrderedAlphabet & operator= ( const OrderedAlphabet & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class OrderedAlphabet


  /**
   * Overloads 'operator<<' for displaying objects of class 'OrderedAlphabet'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'OrderedAlphabet' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<< ( std::ostream & out, const OrderedAlphabet & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods if necessary.
#include "DGtal/base/OrderedAlphabet.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined OrderedAlphabet_h

#undef OrderedAlphabet_RECURSES
#endif // else defined(OrderedAlphabet_RECURSES)
