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
 * @file SimpleIncremental2x2DetComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/18
 *
 * Header file for module SimpleIncremental2x2DetComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SimpleIncremental2x2DetComputer_RECURSES)
#error Recursive header files inclusion detected in SimpleIncremental2x2DetComputer.h
#else // defined(SimpleIncremental2x2DetComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SimpleIncremental2x2DetComputer_RECURSES

#if !defined SimpleIncremental2x2DetComputer_h
/** Prevents repeated inclusion of headers. */
#define SimpleIncremental2x2DetComputer_h

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
  // template class SimpleIncremental2x2DetComputer
  /**
   * \brief Aim: Small class useful to compute, in an incremental way, 
   * the determinant of a 2x2 matrix from its four coefficients, ie. 
   \f$ 
   \begin{vmatrix}
   a & x \\
   b & y
   \end{vmatrix} 
   \f$
   *
   * This class is a model of C2x2DetComputer.  
   *
   * It should be used to compute the determinant \f$ ay - bx \f$, for various 
   * \f$ x, y \f$ and given \f$ a \f$ and \f$ b \f$. 
   * Let us assume that the determinant \f$ \delta_i = ay_i - bx_i \f$ is computed. 
   * The determinant \f$ \delta_j = ay_j - bx_j \f$ is then computed incrementally 
   * as follows: \f$ \delta_j = a(y_j - y_i) - b(x_j - x_i) \f$. The computation 
   * is simplified if the differences \f$ (x_j - x_i) \f$ and \f$ (y_j - y_i) \f$
   * are equal to 0 or 1, as it may occur in digital geometry. 
   * 
   * In order to use SimpleIncremental2x2DetComputer 
   * - first, you must set the first column vector, ie. \f$ a \f$ and \f$ b \f$, using method 
   * SimpleIncremental2x2DetComputer::init(). 
   * - then, you must call method SimpleIncremental2x2DetComputer::operator() on the 
   * second column vector, ie. \f$ x \f$ and \f$ y \f$. 
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
   * @see Simple2x2DetComputer
   */
  template <typename TArgumentInteger, typename TResultInteger = TArgumentInteger>
  class SimpleIncremental2x2DetComputer
  {
    // ----------------------- Types ----------------------------------------
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
    SimpleIncremental2x2DetComputer();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SimpleIncremental2x2DetComputer ( const SimpleIncremental2x2DetComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SimpleIncremental2x2DetComputer & operator= ( const SimpleIncremental2x2DetComputer & other );

    /**
     * Destructor.
     */
    ~SimpleIncremental2x2DetComputer();

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
     * @a myAY . @a aY - @a myBX . @a aX
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
     * Data member used to store the product a.y
     */
    mutable ResultInteger myAY; 
    /**
     * Data member used to store the product b.x
     */
    mutable ResultInteger myBX; 
    /**
     * Data member used to store the determinant, ie. ay - bx
     */
    mutable ResultInteger myDet; 
    /**
     * Data member used to store 
     * the 0-component of the second column vector, ie. x.
     */
    mutable ResultInteger myX; 
    /**
     * Data member used to store
     * the 1-component of the second column vector, ie. y.
     */
    mutable ResultInteger myY; 
    /**
     * Data member used to store the difference between the last
     * 0-component of the second column vector and a new one. 
     */
    mutable ResultInteger myDX; 
    /**
     * Data member used to store the difference between the last
     * 1-component of the second column vector and a new one. 
     */
    mutable ResultInteger myDY; 
    /**
     * Data member used to store the product a.dy. 
     */
    mutable ResultInteger myADY; 
    /**
     * Data member used to store the product b.dx. 
     */
    mutable ResultInteger myBDX; 
    /**
     * Data member used to store the partial determinant, ie. a.dy - b.dx
     */
    mutable ResultInteger myDDet; 

    const ResultInteger myZero; 
    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Update @a myDet with respect to the new value of @a myDY.
     * @pre @a myDY should be updated first
     * @see operator()
     */
    void partialComputation() const;

  }; // end of class SimpleIncremental2x2DetComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'SimpleIncremental2x2DetComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SimpleIncremental2x2DetComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TI, typename TO>
  std::ostream&
  operator<< ( std::ostream & out, const SimpleIncremental2x2DetComputer<TI,TO> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/determinant/SimpleIncremental2x2DetComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SimpleIncremental2x2DetComputer_h

#undef SimpleIncremental2x2DetComputer_RECURSES
#endif // else defined(SimpleIncremental2x2DetComputer_RECURSES)
