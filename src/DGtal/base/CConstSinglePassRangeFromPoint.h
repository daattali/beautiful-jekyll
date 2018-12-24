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
 * @file CConstSinglePassRangeFromPoint.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/27
 *
 * Header file for concept CConstSinglePassRangeFromPoint.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CConstSinglePassRangeFromPoint_RECURSES)
#error Recursive header files inclusion detected in CConstSinglePassRangeFromPoint.h
#else // defined(CConstSinglePassRangeFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CConstSinglePassRangeFromPoint_RECURSES

#if !defined CConstSinglePassRangeFromPoint_h
/** Prevents repeated inclusion of headers. */
#define CConstSinglePassRangeFromPoint_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CConstSinglePassRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CConstSinglePassRangeFromPoint
    /**
       Description of \b concept '\b CConstSinglePassRangeFromPoint' <p>
       @ingroup Concepts
       @brief Aim: refined concept of const single pass range with a begin() method from a point.

       ###  Refinement of CConstSinglePassRange

       ###  Associated types :

       ###  Notation
       - X : A type that is a model of CConstSinglePassRangeFromPoint
       - x,  y : object of type X
       - Point: A type of Point

       ###  Definitions

       ###  Valid expressions and semantics

       | Name  | Expression                 | Type requirements    | Return type   | Precondition | Semantics                                           | Post condition | Complexity |
       |-------|----------------------------|----------------------|---------------|--------------|-----------------------------------------------------|----------------|------------|
       | begin | begin(const Point &aPoint) | aPoint of type Point | ConstIterator |              | Returns a const iterator on the range first element |                |            |
       ###  Invariants

       ###  Models
       - ImageContainerBySTLVector::Range

       ###  Notes
       @tparam T the type that should be a model of CConstSinglePassRangeFromPoint.
    */
    template <typename T>
      struct CConstSinglePassRangeFromPoint: CConstSinglePassRange<T>
      {
        // ----------------------- Concept checks ------------------------------
      public:
        // 1. define first provided types (i.e. inner types), like
        typedef typename T::Point Point;

        // 2. then check the presence of data members, operators and methods with
        BOOST_CONCEPT_USAGE( CConstSinglePassRangeFromPoint )
        {
          checkConstConstraints();
        }
        void checkConstConstraints() const
        {
          // const method dummyConst should take parameter myA of type A and return
          // something of type B
          ConceptUtils::sameType( myB, myX.begin( myPoint ) );
        }
        // ------------------------- Private Datas --------------------------------
      private:
        T myX; // do not require T to be default constructible.
        Point myPoint;
        ConstIterartor myB;

        // ------------------------- Internals ------------------------------------
      private:

      }; // end of concept CConstSinglePassRangeFromPoint

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CConstSinglePassRangeFromPoint_h

#undef CConstSinglePassRangeFromPoint_RECURSES
#endif // else defined(CConstSinglePassRangeFromPoint_RECURSES)
