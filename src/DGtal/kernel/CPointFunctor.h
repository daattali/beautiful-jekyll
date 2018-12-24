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
 * @file CPointFunctor.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/02
 *
 * Header file for concept CPointFunctor.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPointFunctor_RECURSES)
#error Recursive header files inclusion detected in CPointFunctor.h
#else // defined(CPointFunctor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPointFunctor_RECURSES

#if !defined CPointFunctor_h
/** Prevents repeated inclusion of headers. */
#define CPointFunctor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CPointFunctor
  /**
Description of \b concept '\b CPointFunctor' <p>
     @ingroup Concepts

@brief Aim: Defines a functor on points.

 Associates values to points.

 ### Refinement of CUnaryFunctor

 ### Associated types
 - Point : specifies the type for a point (inner type).
 - Value : specifies the type for a value (inner type).

 ### Notation
     - \a X : A type that is a model of CPointFunctor
     - \a x : Object of type \a X
     - \a p : Object of type Point
     - \a v : Object of type Value

 ### Definitions

 ### Valid expressions and semantics

| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|Apply function | \a x( \a p)|                     | \c v        |                  |the value of the function \a x at point \a p | | |

 ### Invariants

 - Shapes and images are models of (refinements of) this concept

 ### Notes###
   */
  template <typename T>
  struct CPointFunctor : CUnaryFunctor<T, typename T::Point, typename T::Value>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::Point Point;
    typedef typename T::Value Value;

    // ------------------------- Private Datas --------------------------------
  private:
    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CPointFunctor
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPointFunctor_h

#undef CPointFunctor_RECURSES
#endif // else defined(CPointFunctor_RECURSES)
