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
 * @file BasicMathFunctions.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/05/06
 *
 * Header file for module BasicMathFunctions.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicMathFunctions_RECURSES)
#error Recursive header files inclusion detected in BasicMathFunctions.h
#else // defined(BasicMathFunctions_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicMathFunctions_RECURSES

#if !defined BasicMathFunctions_h
/** Prevents repeated inclusion of headers. */
#define BasicMathFunctions_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <algorithm>
#include <functional>
#include "DGtal/base/Common.h"
#include "DGtal/base/Bits.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{
  namespace functions
  {

    /** 
     * Compute exponentiation by squaring of a scalar @a aVal of type
     * @a T by the exponent @a exponent (unsigned int). The
     * computation is done in @f$ O(\log(exponent))@f$ multiplications.
     * @note This function is better than std::pow on unsigned int
     * exponents and integer value type  since it performs  exact
     * computations (no cast to float or doubles).
     *
     * @param aVal the value
     * @param exponent the exponent
     * @tparam T scalar value type (must have '*' operator).
     * @return aVal^exponent
     *
     * @see square, cube
     */
    template<typename T>
    T power(const T&aVal, const unsigned int exponent)
    {
      unsigned int q=exponent;
      T p(aVal);
      
      if (exponent == 0) { return 1;    }
      
      T result = NumberTraits<T>::ONE;
      while (q != 0) 
	{
	  if (q % 2 == 1) {    // q is odd
	    result *= p;
	    q--;
	  }
	  p *= p;
	  q /= 2;
	}
      return result;
    }


    /**
     * Compute the next higher power of two of the given argument n of type T. 
     * 
     * @tparam T the type of the element T
     * @param n an element of type T (casted to unsigned integer).
     * @return the next higher power of two.
     **/
    template<typename T> 
    T roundToUpperPowerOfTwo(const  T &n){
      return (T)  1 << (1+DGtal::Bits::mostSignificantBit( (unsigned int) n-1 ) );
    }

    /** 
     * Return the absolute value of an instance of type T.
     *
     * @tparam T the type of elements to compare (model of
     * boost::LessThanComparable).
     * @param a first value
     *
     * @return the absolute value |a|.
     */
    template<typename T>
    T abs(const T & a)
    {
      BOOST_CONCEPT_ASSERT((boost::LessThanComparable<T>));
      if (a<0) 
	return -a;
      else
	return a;
    }

    /**
       Returns the value x * x
       @tparam T a type with the multiply operator.
       @param x any value
       @return the value x * x
    */
    template <typename T>
    inline
    T square( T x )
    { return x * x; }

    /**
       Returns the value x * x * x
       @tparam T a type with the multiply operator.
       @param x any value
       @return the value x * x * x
    */
    template <typename T>
    inline
    T cube( T x )
    { return x * x * x; }

  }  // namespace functions
} // namespace DGTal



///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicMathFunctions_h

#undef BasicMathFunctions_RECURSES
#endif // else defined(BasicMathFunctions_RECURSES)
