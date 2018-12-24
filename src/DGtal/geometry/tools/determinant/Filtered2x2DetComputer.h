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
 * @file Filtered2x2DetComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/20
 *
 * Header file for module Filtered2x2DetComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Filtered2x2DetComputer_RECURSES)
#error Recursive header files inclusion detected in Filtered2x2DetComputer.h
#else // defined(Filtered2x2DetComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Filtered2x2DetComputer_RECURSES

#if !defined Filtered2x2DetComputer_h
/** Prevents repeated inclusion of headers. */
#define Filtered2x2DetComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/tools/determinant/C2x2DetComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Filtered2x2DetComputer
  /**
   * \brief Aim: Class that provides a way of computing the sign of the 
   * determinant of a 2x2 matrix from its four coefficients, ie. 
   * 
   \f$ 
   \begin{vmatrix}
   a & x \\
   b & y
   \end{vmatrix} 
   \f$
   *
   * The coefficients must be integers, with an absolute value less than
   * 2^53, of type 'double'. 
   * 
   * It returns: 
   * - a strictly positive value if \f$ ay - bx > 0\f$, 
   * - a strictly negative value if \f$ ay - bx < 0 \f$,
   * - 0 if \f$ ay - bx = 0 \f$.
   *
   * If the result of \f$ ay - bx \f$ is not null,
   * the IEC-559 / IEEE-754 standard guarantees that 
   * the result is not zero (filtering step). Otherwise, 
   * we use another method to conclude. 
   *
   * This class is a model of C2x2DetComputer. 
   *
   * @tparam TDetComputer any model of C2x2DetComputer
   */
  template <typename TDetComputer>
  class Filtered2x2DetComputer
  {
    // ----------------------- Types  ------------------------------------
  public:
    BOOST_CONCEPT_ASSERT(( C2x2DetComputer<TDetComputer> )); 

    /**
     * Type of integer for the input coefficients of the 2x2 matrix
     */
    typedef typename TDetComputer::ArgumentInteger ArgumentInteger; 
    //NB. TDetComputer should take input coefficients of type float, double or long double
    //this type must adhere to IEC-559 / IEEE-754 standard.
    BOOST_STATIC_ASSERT(( std::numeric_limits<ArgumentInteger>::is_iec559 )); 

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
    typedef typename TDetComputer::ResultInteger ResultInteger; 
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
     * Data member used to store 
     * the 0-component of the first column vector, ie. a.
     */
    ArgumentInteger myA; 
    /**
     * Data member used to store
     * the 1-component of the first column vector, ie. b.
     */
    ArgumentInteger myB; 
    /**
     * Object that can return (the sign of) the determinant, 
     * after the filtering. 
     */
    mutable TDetComputer myDetComputer; 

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Filtered2x2DetComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'Filtered2x2DetComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Filtered2x2DetComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const Filtered2x2DetComputer<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/determinant/Filtered2x2DetComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Filtered2x2DetComputer_h

#undef Filtered2x2DetComputer_RECURSES
#endif // else defined(Filtered2x2DetComputer_RECURSES)
