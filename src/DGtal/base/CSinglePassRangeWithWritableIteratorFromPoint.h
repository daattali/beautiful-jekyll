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
 * @file CSinglePassRangeWithWritableIteratorFromPoint.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/27
 *
 * Header file for concept CSinglePassRangeWithWritableIteratorFromPoint.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSinglePassRangeWithWritableIteratorFromPoint_RECURSES)
#error Recursive header files inclusion detected in CSinglePassRangeWithWritableIteratorFromPoint.h
#else // defined(CSinglePassRangeWithWritableIteratorFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSinglePassRangeWithWritableIteratorFromPoint_RECURSES

#if !defined CSinglePassRangeWithWritableIteratorFromPoint_h
/** Prevents repeated inclusion of headers. */
#define CSinglePassRangeWithWritableIteratorFromPoint_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CSinglePassRangeWithWritableIterator.h"
#include "DGtal/base/CConstSinglePassRangeFromPoint.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CSinglePassRangeWithWritableIteratorFromPoint
    /**
       Description of \b concept '\b CSinglePassRangeWithWritableIteratorFromPoint' <p>
       @ingroup Concepts
       @brief Aim: refined concept of single pass range with a outputIterator() method from a point.

       ### Refinement of CConstSinglePassRangeFromPoint and CSinglePassRangeWithWritableIterator

       ### Associated types :

       ### Notation
       - X : A type that is a model of CSinglePassRangeWithWritableIteratorFromPoint
       - x,  y : object of type X
       - Point: A type of Point

       ### Definitions

       ### Valid expressions and semantics

       | Name  | Expression                 | Type requirements    | Return type   | Precondition | Semantics                                           | Post condition | Complexity |
       |-------|----------------------------|----------------------|---------------|--------------|-----------------------------------------------------|----------------|------------|
       | output iterator | outputIterator(const Point &aPoint) | aPoint of type Point | OutputIterator |              | Returns an output iterator on the range first element |                |            |

       ### Invariants

       ### Models
       - ImageContainerBySTLVector::Range

       ### Notes

       @tparam T the type that should be a model of CSinglePassRangeWithWritableIteratorFromPoint.
       @tparam Value the type of object t in (*it) = t.

    */
    template <typename T, typename Value>
    struct CSinglePassRangeWithWritableIteratorFromPoint:
      CConstSinglePassRangeFromPoint<T,Value>,
      CSinglePassRangeWithWritableIterator<T,Value>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // 1. define first provided types (i.e. inner types), like
      typedef typename T::OutputIterator OutputIterator;
      typedef typename T::Point Point;

      // 2. then check the presence of data members, operators and methods with
      BOOST_CONCEPT_USAGE( CSinglePassRangeWithWritableIteratorFromPoint )
      {
        ConceptUtils::sameType( myIt, myX.begin( myPoint ) );
      }

      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // do not require T to be default constructible.
      Point myPoint;
      OutputIterartor myIt;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CSinglePassRangeWithWritableIteratorFromPoint

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSinglePassRangeWithWritableIteratorFromPoint_h

#undef CSinglePassRangeWithWritableIteratorFromPoint_RECURSES
#endif // else defined(CSinglePassRangeWithWritableIteratorFromPoint_RECURSES)
