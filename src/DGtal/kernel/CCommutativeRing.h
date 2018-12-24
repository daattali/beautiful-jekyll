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
 * @file CCommutativeRing.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/08/26
 *
 * Header file for concept CCommutativeRing.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CCommutativeRing_RECURSES)
#error Recursive header files inclusion detected in CCommutativeRing.h
#else // defined(CCommutativeRing_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CCommutativeRing_RECURSES

#if !defined CCommutativeRing_h
/** Prevents repeated inclusion of headers. */
#define CCommutativeRing_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSignedNumber.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CCommutativeRing
  /**
Description of \b concept '\b CCommutativeRing' <p>
     @ingroup Concepts

     @brief Aim: Defines the mathematical concept equivalent to a
     unitary commutative ring.

 ### Refinement of 
  - CSignedNumber<T>

 ### Associated types :

 ### Notation
     - \e X : A type that is a model of CCommutativeRing
     - \e x, \e y  : Object of type @e X

 ### Definitions

 ### Valid expressions and semantics


Name                                 | Expression |  Type requirements | Return type| Precondition | Semantics                             | Postcondition | Complexity|
-------------------------------------|------------|--------------------|------------|--------------|--------------------------------------|---------------|-----------|
Construction from basic integer type | @e X( i )  |                    |            |              | \e X represents the integer \e i     |               |           |
Should have a 0                      |   @e X(0)  |                    |            |              | Neutral element for addition         |               |           |
Should have a 1                      |   @e X(1)  |                    |            |              | Neutral element for multiplication   |               |           |
Addition                             | @e x + @e y|                    | @a X       |              | addition of two numbers              |               |           |
Substraction                         | @e x - @e y|                    | @a X       |              | substraction of two numbers          |               |           |
Multiplication                       | @e x * @e y|                    | @a X       |              | multiplication of two numbers        |               |           |
Addition                             | @e x + @e y|                    | @a X       |              | addition of two numbers              |               |           |
Opposite operator                    | - @e x     |                    | @a X       |              | opposite of a number                 |               |           |


 ### Invariants###

 ### Models###
       DGtal::int32_t, DGtal::int64_t, DGtal::int8_t, float, double, long double, DGtal::BigInteger

 ### Notes###

@tparam T the type that should be a model of commutative ring.
   */
  template <typename T>
  struct CCommutativeRing : concepts::CSignedNumber<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:

    BOOST_CONCEPT_USAGE( CCommutativeRing )
    {
      ConceptUtils::sameType( c, T( 25 ) );
      ConceptUtils::sameType( c, T( -25 ) );
      ConceptUtils::sameType( c, T( a+b ) );
      ConceptUtils::sameType( c, T( -a ) );
      ConceptUtils::sameType( c, T( a-b ) );
      ConceptUtils::sameType( c, T( a*b ) );
      ConceptUtils::sameType( c, T( 0 ) );
      ConceptUtils::sameType( c, T( 1 ) );

      ///The 0 and 1 neutral elements should be tested.
    }
    // ------------------------- Internals ------------------------------------
  private:
    T a,b,c;

  };
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CCommutativeRing_h

#undef CCommutativeRing_RECURSES
#endif // else defined(CCommutativeRing_RECURSES)
