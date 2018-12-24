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
 * @file CImplicitFunction.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/28
 *
 * Header file for concept CImplicitFunction.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CImplicitFunction_RECURSES)
#error Recursive header files inclusion detected in CImplicitFunction.h
#else // defined(CImplicitFunction_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CImplicitFunction_RECURSES

#if !defined CImplicitFunction_h
/** Prevents repeated inclusion of headers. */
#define CImplicitFunction_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CImplicitFunction
  /**
Description of \b concept '\b CImplicitFunction' <p>
     @ingroup Concepts

@brief Aim: Describes any function of the form f(x), where x is
     some real point in the given space, and f(x) is some value.
     
 ### Associated types :
     - RealPoint: the type for the domain
     - Value: the type for the range

 ### Notation
     - \c X : A type that is a model of CImplicitFunction
     - \c f : objet of type X
     - \c a : objet of type RealPoint
    
 ### Definitions
    
 ### Valid expressions and semantics
     
| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|Function call  | \c f( \c a )|                    | Value       |                  | Evaluates the function \c f at point \c a | | |


 ### Invariants
    
 ### Models
     ImplicitBall, ImplicitPolynomial3Shape, ImplicitHyperCube, ImplicitRoundedHyperCube, ImplicitNorm1Ball

 ### Notes


@tparam T the type that should be a model of CImplicitFunction.
   */
  template <typename T> 
  struct CImplicitFunction 
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // 1. define first provided types (i.e. inner types), like
    typedef typename T::RealPoint RealPoint;
    typedef typename T::Value Value;
    // possibly check these types so as to satisfy a concept with
    BOOST_CONCEPT_ASSERT(( boost::UnaryFunction< T, Value, RealPoint > ));
    
  }; // end of concept CImplicitFunction
  } 
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CImplicitFunction_h

#undef CImplicitFunction_RECURSES
#endif // else defined(CImplicitFunction_RECURSES)
