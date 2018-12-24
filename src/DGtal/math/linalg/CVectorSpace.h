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
 * @file CVectorSpace.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CVectorSpace.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CVectorSpace_RECURSES)
#error Recursive header files inclusion detected in CVectorSpace.h
#else // defined(CVectorSpace_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CVectorSpace_RECURSES

#if !defined CVectorSpace_h
/** Prevents repeated inclusion of headers. */
#define CVectorSpace_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CEuclideanRing.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CVectorSpace
    /**
       Description of \b concept '\b CVectorSpace' <p>
       @ingroup Concepts
       @brief Aim:
       Base concept for vector space structure.

       ### Refinement of
       - boost::Assignable

       ### Associated types
       - \c Scalar: Scalar type used for external multiplication and internal type representation.
       - \c Index: Random access index type.

       ### Notation
       - \c VectorSpace : A type that is a model of concepts::CVectorSpace
       - \e x, \e y : const object of type \c VectorSpace
       - \e z : object of type \c VectorSpace
       - \e a : object of type \c VectorSpace::Scalar

       ### Definitions

       ### Valid expressions and semantics

       | Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
       |-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
       | Reset container content      |  \a z.clear()         |                   |               |              |           |                |            |
       | Addition      | \a z = \a x + \a y           |                  | \c VectorSpace              |              |           |                |            |
       | Substraction      | \a z = \a x - \a y           |                   | \c VectorSpace              |              |           |                |            |
       | External multiplication      | \a z = \a a * \a x           |                   |  \c VectorSpace               |              |           |                |            |

       ### Invariants

       ### Models

       ### Notes

       @tparam T the type that should be a model of CVectorSpace.
    */
    template <typename T>
    struct CVectorSpace : boost::Assignable<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::Scalar Scalar;

      BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<Scalar> ));

      BOOST_CONCEPT_USAGE( CVectorSpace )
      {
        z.clear();
        z = x + y;
        z = x - y;
        z = a * x;
      }
      // ------------------------- Private Datas --------------------------------
    private:
      const T x,y;
      T z;
      Scalar a;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CVectorSpace
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CVectorSpace_h

#undef CVectorSpace_RECURSES
#endif // else defined(CVectorSpace_RECURSES)
