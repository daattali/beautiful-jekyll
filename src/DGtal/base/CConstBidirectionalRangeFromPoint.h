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
 * @file CConstBidirectionalRangeFromPoint.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/27
 *
 * Header file for concept CConstBidirectionalRangeFromPoint.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CConstBidirectionalRangeFromPoint_RECURSES)
#error Recursive header files inclusion detected in CConstBidirectionalRangeFromPoint.h
#else // defined(CConstBidirectionalRangeFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CConstBidirectionalRangeFromPoint_RECURSES

#if !defined CConstBidirectionalRangeFromPoint_h
/** Prevents repeated inclusion of headers. */
#define CConstBidirectionalRangeFromPoint_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CConstBidirectionalRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CConstBidirectionalRangeFromPoint
    /**
       DescriptionDescription of \b concept '\b CConstBidirectionalRangeFromPoint'
       @ingroup Concepts
       @brief Aim: refined concept of const bidirectional range with a begin() method from a point.

       ###  Refinement of CConstBidirectionalRange

       ###  Associated types :

       ###  Notation
       - X : A type that is a model of CConstBidirectionalRangeFromPoint
       - x,  y : object of type X
       - Point: A type of Point


       ###  Definitions

       ###  Valid expressions and semantics



       | Name  | Expression  | Type requirements    | Return type   | Precondition | Semantics   | Post condition | Complexity |
       |-------|----------------------------|----------------------|---------------|--------------|-----------------------------------------------------|----------------|------------|
       | reverse begin | rbegin(const Point &aPoint) | aPoint of type Point | ConstIterator |    | Returns a const reverse iterator on the range first element | |  |


       ###  Invariants

       ###  Models

       ImageContainerBySTLVector::Range

       ###  Notes

       @tparam T the type that should be a model of CConstBidirectionalRangeFromPoint.
    */
    template <typename T>
    struct CConstBidirectionalRangeFromPoint: CConstBidirectionalRange<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // 1. define first provided types (i.e. inner types), like
      typedef typename T::Point Point;

      // 2. then check the presence of data members, operators and methods with
      BOOST_CONCEPT_USAGE( CConstBidirectionalRangeFromPoint )
      {
        checkConstConstraints();
      }
      void checkConstConstraints() const
      {
        // const method dummyConst should take parameter myA of type A and return
        // something of type B
        concepts::ConceptUtils::sameType( myB, myX.rbegin( myPoint ) );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // do not require T to be default constructible.
      Point myPoint;
      typename T::ConstReverseIterator myB;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CConstBidirectionalRangeFromPoint

  } // namespace concepts

} // namespace DGtal

////
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CConstBidirectionalRangeFromPoint_h

#undef CConstBidirectionalRangeFromPoint_RECURSES
#endif // else defined(CConstBidirectionalRangeFromPoint_RECURSES)
