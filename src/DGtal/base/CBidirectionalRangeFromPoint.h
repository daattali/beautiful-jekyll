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
 * @file CBidirectionalRangeFromPoint.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/27
 *
 * Header file for concept CBidirectionalRangeFromPoint.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CBidirectionalRangeFromPoint_RECURSES)
#error Recursive header files inclusion detected in CBidirectionalRangeFromPoint.h
#else // defined(CBidirectionalRangeFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBidirectionalRangeFromPoint_RECURSES

#if !defined CBidirectionalRangeFromPoint_h
/** Prevents repeated inclusion of headers. */
#define CBidirectionalRangeFromPoint_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CBidirectionalRange.h"
#include "DGtal/base/CConstBidirectionalRangeFromPoint.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CBidirectionalRangeFromPoint
    /**
       DescriptionDescription of \b concept '\b CBidirectionalRangeFromPoint'
       @ingroup Concepts
       @brief Aim: refined concept of  single pass range with a begin() method from a point.

       ### Refinement of CBidirectionalRange

       ### Associated types :

       - ReverseIterator

       ### Notation
       - X : A type that is a model of CBidirectionalRangeFromPoint
       - x,  y : object of type X
       - Point: A type of Point


       ### Definitions

       ### Valid expressions and



       | Name  | Expression       | Type requirements    | Return type   | Precondition | Semantics                                           | Post condition | Complexity |
       |-------|----------------------------|----------------------|---------------|--------------|-----------------------------------------------------|----------------|------------|
       | reverse begin | rbegin(const Point &aPoint) | aPoint of type Point | ReverseIterator |              | Returns a reverse iterator on the range at point \a aPoint |                |            |

       ### Invariants

       ### Models

       ImageContainerBySTLVector::Range

       ### Notes

       @tparam T the type that should be a model of CBidirectionalRangeFromPoint.
    */
    template <typename T>

    struct CBidirectionalRangeFromPoint:
      CBidirectionalRange<T>,
      CConstBidirectionalRangeFromPoint<T>
    {
      // ----------------------- Concept checks ------------------------------

    public:
      // 1. define first provided types (i.e. inner types), like
      typedef typename T::Point Point;
      typedef typename T::ReverseIterator ReverseIterator;


      // 2. then check the presence of data members, operators and methods with
      BOOST_CONCEPT_USAGE ( CBidirectionalRangeFromPoint )
      {
        concepts::ConceptUtils::sameType ( myIt, myX.rbegin ( myPoint ) );
      }

      // ------------------------- Private Datas --------------------------------

    private:
      T myX; // do not require T to be default constructible.
      Point myPoint;
      ReverseIterator myIt;

      // ------------------------- Internals ------------------------------------

    private:

    }; // end of concept CBidirectionalRangeFromPoint

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBidirectionalRangeFromPoint_h

#undef CBidirectionalRangeFromPoint_RECURSES
#endif // else defined(CBidirectionalRangeFromPoint_RECURSES)
