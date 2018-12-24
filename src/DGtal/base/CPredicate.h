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
 * @file CPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/11/26
 *
 * Defines the concept checking class CPredicate.
 *
 * This file is part of the DGtal library.
 */

#if defined(CPredicate_RECURSES)
#error Recursive header files inclusion detected in CPredicate.h
#else // defined(CPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPredicate_RECURSES

#if !defined CPredicate_h
/** Prevents repeated inclusion of headers. */
#define CPredicate_h

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
    // class CPredicate
    /**
       Description of \b concept '\b CPredicate'
       @ingroup Concepts
       \brief Aim: Defines a predicate function, ie. a functor mapping a domain into the set of booleans.

       @tparam T the type that should be a model of this predicate
       @tparam TElement the type of an element of the predicate domain.

       ###  Refinement of 

       - CUnaryFunctor

       ###  Associated types :

       ###  Notation
       - \e X : A type that is a model of CPredicate
       - \e x : Object of type \e X
       - \e p : Object of type TElement

       ###  Definitions

       ###  Valid expressions and semantics

       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | Apply predicate| \e x.( \e p )|                  | \e bool     |                  | the value of the predicate \e x at element \e p | | |

       ###  Invariants

       ###  Models

       - specializations: concepts::CPointPredicate, concepts::CVertexPredicate

       ###  Notes

       CPredicate allows to factor codes when writing concepts for new
       kinds of predicates.
    */
    template <typename T, typename TElement>
    struct CPredicate :  CUnaryFunctor<T,TElement,bool>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef TElement Element;

      // ------------------------- Private Datas --------------------------------
    private:
      T myPred;
      Element myElement;
      bool myBool;
      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CPredicate
  } // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPredicate_h

#undef CPredicate_RECURSES
#endif // else defined(CPredicate_RECURSES)
