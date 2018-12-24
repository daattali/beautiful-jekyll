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
 * @file AvnaimEtAl2x2DetSignComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/19
 *
 * Header file for module AvnaimEtAl2x2DetSignComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(AvnaimEtAl2x2DetSignComputer_RECURSES)
#error Recursive header files inclusion detected in AvnaimEtAl2x2DetSignComputer.h
#else // defined(AvnaimEtAl2x2DetSignComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define AvnaimEtAl2x2DetSignComputer_RECURSES

#if !defined AvnaimEtAl2x2DetSignComputer_h
/** Prevents repeated inclusion of headers. */
#define AvnaimEtAl2x2DetSignComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ExpressionTemplates.h"

#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CEuclideanRing.h"
#include "DGtal/kernel/CBoundedNumber.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace detail
  {

    /**
     * \brief Aim: Small stucture that provides
     * a static method returning the Euclidean division
     * of two integers. 
     * @tparam TNumber type of number. 
     * If TNumber is a model of CInteger (default), 
     * the method EuclideanDivisionHelper::compute(a,b)
     * returns a / b.
     * If TNumber is float or double, the same method
     * returns std::floor( a / b ). 
     */
    template <typename TNumber>
    struct EuclideanDivisionHelper
    {
      /**
       * Computes the Euclidean division @a a / @a b
       * @param a numerator
       * @param b denominator
       * @return Euclidean division @a a / @a b
       */
      static TNumber compute(const TNumber& a, const TNumber& b)
      {
	BOOST_CONCEPT_ASSERT(( concepts::CInteger<TNumber> )); 
	return a / b; 
      }
    }; 
    //specialization for float and double
    template < >
    struct EuclideanDivisionHelper<float>
    {
      static float compute(const float& a, const float& b)
      {
    	return std::floor(a / b); 
      }
    }; 
    template < >
    struct EuclideanDivisionHelper<double>
    {
      static double compute(const double& a, const double& b)
      {
	return std::floor(a / b); 
      }
    }; 
    template < >
    struct EuclideanDivisionHelper<long double>
    {
      static double compute(const double& a, const double& b)
      {
	return std::floor(a / b); 
      }
    }; 
  }

  /////////////////////////////////////////////////////////////////////////////
  // template class AvnaimEtAl2x2DetSignComputer
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
   * It returns: 
   * - 1 if \f$ ay - bx > 0\f$, 
   * - -1 if \f$ ay - bx < 0 \f$,
   * - 0 if \f$ ay - bx = 0 \f$.
   *
   * If the coefficients are coded with b bits, the computation only uses 
   * numbers coded with b bits too without any overflows 
   * [Avnaim et.al., 1997 : \cite AvnaimEtAlAlgorithmica1997]. 
   *
   * This class is a model of C2x2DetComputer. 
   *
   * @tparam TInteger both a model of CEuclideanRing (it has the usual 
   * arithmetic operators) and a model of CBoundedNumber. 
   * It can be DGtal::int8_t, DGtal::int16_t, DGtal::int32_t, DGtal::int64_t
   * as well as float and double.
   *
   * @see Simple2x2DetComputer
   */
  template <typename TInteger>
  class AvnaimEtAl2x2DetSignComputer
  {
    // ----------------------- Types  ------------------------------------
  public:
    /**
     * Type of integer for the input coefficients of the 2x2 matrix
     */
    typedef TInteger ArgumentInteger; 
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<ArgumentInteger> )); 
    BOOST_CONCEPT_ASSERT(( concepts::CBoundedNumber<ArgumentInteger> )); 

    /**
     * DGtal alias of type ArgumentInteger
     */
    typedef ArgumentInteger Integer; 
    /**
     * STL alias of type ArgumentInteger
     */
    typedef ArgumentInteger argument_type; 

    /**
     * Type of integer for the returned determinant, 
     *  which is an alias of type ArgumentInteger
     */
    typedef Integer ResultInteger; 
    /**
     * DGtal alias type of ResultInteger
     */
    typedef ResultInteger Value; 
    /**
     * STL alias of type ResultInteger
     */
    typedef ResultInteger result_type;

    // ----------------------- Static members ---------------------------------
  public:
    /**
     * Data member storing the number of the base (radix) of the representation, 
     * 2 usually
     */
    BOOST_STATIC_CONSTANT( unsigned int, base = std::numeric_limits<Integer>::radix ); 
    /**
     * Data member storing the number of non-sign bits in the representation, 
     * eg. b-1 for signed integer coded with b bits. 
     */
    BOOST_STATIC_CONSTANT( unsigned int, exponent = std::numeric_limits<Integer>::digits ); 

    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Default constructor
     */
    AvnaimEtAl2x2DetSignComputer(); 


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
     * @param aU 0-component of the second column vector
     * @param aV 1-component of the second column vector
     * @return the sign of the determinant of the 2x2 matrix, ie. 
     * 1 if @a myA . @a aV - @a myB . @a aU is strictly positive, 
     * -1 if it is strictly negative, 0 otherwise
     */
    ResultInteger operator()(const ArgumentInteger& aU, const ArgumentInteger& aV) const;

    /**
     * Operator.
     * @param aA 0-component of the first column vector
     * @param aB 1-component of the first column vector
     * @param aX 0-component of the second column vector
     * @param aY 1-component of the second column vector
     * @return the sign of the determinant of the 2x2 matrix, ie. 
     * 1 if @a aA . @a aY - @a aB . @a aX is strictly positive, 
     * -1 if it is strictly negative, 0 otherwise
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

    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Returns the quadrant where a given vector lies
     * @param aX x-component of the vector
     * @param aY y-component of the vector
     * @pre aX and aY must not be null
     * @return the quadrant where the vector of 
     * components @a aX , @a aY lies, ie. 
     * 0, 1, 2, or 3 in a counter-clockwise order 
     * with 0 if aX and aY are both positive. 
     */
    int quadrant(const Integer& aX, const Integer& aY) const;  

    /**
     * Method that computes the sign of the determinant
     * for strictly positive coefficients. 
     * @param aA 0-component of the first column vector
     * @param aB 1-component of the first column vector
     * @param aX 0-component of the second column vector
     * @param aY 1-component of the second column vector
     * @pre aA, aB, aX, aY are strictly positive. 
     * @return the sign of the determinant of the 2x2 matrix, ie. 
     * 1 if @a aA . @a aY - @a aB . @a aX is strictly positive, 
     * -1 if it is strictly negative, 0 otherwise
     * @see recursiveComputation
     */
    Integer computation(const Integer& aA, const Integer& aB, 
			const Integer& aX, const Integer& aY) const;

    /**
     * Method that computes the sign of the determinant
     * for strictly positive coefficients  
     * aA, aB, aX, aY such that aB < aY.
     * @param aA 0-component of the first column vector
     * @param aB 1-component of the first column vector
     * @param aX 0-component of the second column vector
     * @param aY 1-component of the second column vector
     * @pre aA, aB, aX, aY are strictly positive and such 
     * that aB < aY
     * @return the sign of the determinant of the 2x2 matrix, ie. 
     * 1 if @a aA . @a aY - @a aB . @a aX is strictly positive, 
     * -1 if it is strictly negative, 0 otherwise
     */
    Integer recursiveComputation(const Integer& aA, const Integer& aB, 
				 const Integer& aX, const Integer& aY) const;

    // ------------------------- Private Datas --------------------------------
  private:

    /**
     * Data member used to store 
     * the 0-component of the first column vector, ie. a.
     */
    Integer myA; 
    /**
     * Data member used to store
     * the 1-component of the first column vector, ie. b.
     */
    Integer myB; 
    /**
     * Data member storing the maximal representable integer, ie. 
     * 2 ^ b if the type of integer that is used is coded with b bits. 
     */
    Integer myMax; 

  }; // end of class AvnaimEtAl2x2DetSignComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'AvnaimEtAl2x2DetSignComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'AvnaimEtAl2x2DetSignComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TInteger>
  std::ostream&
  operator<< ( std::ostream & out, const AvnaimEtAl2x2DetSignComputer<TInteger> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined AvnaimEtAl2x2DetSignComputer_h

#undef AvnaimEtAl2x2DetSignComputer_RECURSES
#endif // else defined(AvnaimEtAl2x2DetSignComputer_RECURSES)
