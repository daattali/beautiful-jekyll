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
 * @file CEuclideanRing.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/05
 *
 * This file is part of the DGtal library.
 */

#if defined(CEuclideanRing_RECURSES)
#error Recursive header files inclusion detected in CEuclideanRing.h
#else // defined(CEuclideanRing_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CEuclideanRing_RECURSES

#if !defined CEuclideanRing_h
/** Prevents repeated inclusion of headers. */
#define CEuclideanRing_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CCommutativeRing.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CEuclideanRing
  /**
Description of \b concept '\b CEuclideanRing' <p>
     @ingroup Concepts
    
     @brief Aim: Defines the mathematical concept equivalent to a
     unitary commutative ring with a division operator. 
     
 ### Refinement of CCommutativeRing
 ### Associated types :
    
 ### Notation
     - \a X : A type that is a model of CEuclideanRing
     - \a x, \a y  : Object of type Integer
    
 ### Definitions
    
 ### Valid expressions and semantics



|Name | Expression |  Type requirements | Return type| Precondition | Semantics | Postcondition | Complexity| 
-----|------------|--------------------|------------|--------------|-----------|---------------|-----------
| Division|   \a x / \a y   | @a X| object of type @a X|       Euclidean division of two numbers | | | |   


 ### Invariants###
    
 ### Models###
DGtal::int32_t, DGtal::int64_t, DGtal::int8_t, float, double, long double, DGtal::BigInteger
    
 ### Notes###
   
@tparam T the type that should be a model of commutative ring.
   */
  template <typename T>
  struct CEuclideanRing : CCommutativeRing<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:

    BOOST_CONCEPT_USAGE( CEuclideanRing )
    {
      ConceptUtils::sameType( c, T( a/b ) );
    }   
    // ------------------------- Internals ------------------------------------
  private:
    T a,b,c;
  
  };
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CEuclideanRing_h

#undef CEuclideanRing_RECURSES
#endif // else defined(CEuclideanRing_RECURSES)
