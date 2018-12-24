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
 * @file Simple2x2DetComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/18
 *
 * Header file for module Simple2x2DetComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Simple2x2DetComputer_RECURSES)
#error Recursive header files inclusion detected in Simple2x2DetComputer.h
#else // defined(Simple2x2DetComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Simple2x2DetComputer_RECURSES

#if !defined Simple2x2DetComputer_h
/** Prevents repeated inclusion of headers. */
#define Simple2x2DetComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CEuclideanRing.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Simple2x2DetComputer
  /**
   * \brief Aim: Small class useful to compute the determinant of a 2x2 matrix 
   * from its four coefficients, ie. 
   \f$ 
   \begin{vmatrix}
   a & x \\
   b & y
   \end{vmatrix} 
   \f$
   *
   * This class, which is a model of C2x2DetComputer, 
   * just computes the quantity \f$ ay - bx \f$.
   *
   * In order to use Simple2x2DetComputer in its incremental form: 
   * - first, you must set the first column vector, 
   * ie. \f$ a \f$ and \f$ b \f$, using method 
   * Simple2x2DetComputer::init(). 
   * - then, you must call method Simple2x2DetComputer::operator() on the 
   * second column vector, ie. \f$ x \f$ and \f$ y \f$. 
   *
   * Note that since a substantial part of the execution time comes from 
   * the allocation/desallocation of integers, we follow the same strategy 
   * used in IntegerComputer: the user instantiates once this object and 
   * computes the determinant several times with it. 
   *
   * @tparam TArgumentInteger a model of CEuclideanRing for the input coefficients of the 
   * 2x2 matrix
   * @tparam TResultInteger a model of CEuclideanRing for the result. It must be 
   * either unbounded or twice as big as TArgumentInteger, ie. if TArgumentInteger is 
   * a type coded on b bits, TResultInteger must be coded on 2b+1 bits
   * 
   * Note that if you use the same type for the arguments and the result, 
   * the code may fail to provide the exact result because of a possible overflow. 
   *
   * @see AvnaimEtAl2x2DetSignComputer
   */
  template <typename TArgumentInteger, typename TResultInteger = TArgumentInteger>
  class Simple2x2DetComputer
  {
    // ----------------------- Types  ------------------------------------
  public:
    /**
     * Type of integer for the input coefficients of the 2x2 matrix
     */
    typedef TArgumentInteger ArgumentInteger; 
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<ArgumentInteger> )); 
    /**
     * DGtal alias of type ArgumentInteger
     */
    typedef ArgumentInteger Integer; 
    /**
     * STL alias of type ArgumentInteger
     */
    typedef ArgumentInteger argument_type; 

    /**
     * Type of integer for the returned determinant
     */
    typedef TResultInteger ResultInteger; 
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<ArgumentInteger> )); 

    /**
     * DGtal alias type of ResultInteger
     */
    typedef ResultInteger Value; 
    /**
     * STL alias of type ResultInteger
     */
    typedef ResultInteger result_type;
 
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     */
    Simple2x2DetComputer();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Simple2x2DetComputer ( const Simple2x2DetComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Simple2x2DetComputer & operator= ( const Simple2x2DetComputer & other );

    /**
     * Destructor.
     */
    ~Simple2x2DetComputer();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Initialisation.
     * @param aA 0-component of the first column vector
     * @param aB 1-component of the first column vector
     * @see operator()
     */
    void init(const ArgumentInteger& aA, const ArgumentInteger& aB);

    /**
     * Incremental operator.
     * @pre init must be called before
     * @param aX 0-component of the second column vector
     * @param aY 1-component of the second column vector
     * @return the 2x2 matrix determinant, ie. 
     * @a myAX . @a aY - @a myBY . @a aX
     */
    ResultInteger operator()(const ArgumentInteger& aX, const ArgumentInteger& aY) const;

    /**
     * Operator.
     * @param aA 0-component of the first column vector
     * @param aB 1-component of the first column vector
     * @param aX 0-component of the second column vector
     * @param aY 1-component of the second column vector
     * @return determinant of the 2x2 matrix that consists
     * of the two above column vectors, ie. @a aA . @a aY - @a aB . @a aX
     */
    ResultInteger operator()(const ArgumentInteger& aA, const ArgumentInteger& aB, 
			     const ArgumentInteger& aX, const ArgumentInteger& aY);

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

    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Data member used to store 
     * the 0-component of the first column vector, ie. a.
     */
    ResultInteger myA; 
    /**
     * Data member used to store
     * the 1-component of the first column vector, ie. b.
     */
    ResultInteger myB; 
    /**
     * Data member used to store the product ay
     */
    mutable ResultInteger myAY; 
    /**
     * Data member used to store the product bx
     */
    mutable ResultInteger myBX; 

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Simple2x2DetComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'Simple2x2DetComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Simple2x2DetComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TI, typename TO>
  std::ostream&
  operator<< ( std::ostream & out, const Simple2x2DetComputer<TI,TO> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Simple2x2DetComputer_h

#undef Simple2x2DetComputer_RECURSES
#endif // else defined(Simple2x2DetComputer_RECURSES)
