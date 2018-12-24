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
 * @file CDynamicBidirectionalSegmentComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CDynamicBidirectionalSegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDynamicBidirectionalSegmentComputer_RECURSES)
#error Recursive header files inclusion detected in CDynamicBidirectionalSegmentComputer.h
#else // defined(CDynamicBidirectionalSegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDynamicBidirectionalSegmentComputer_RECURSES

#if !defined CDynamicBidirectionalSegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define CDynamicBidirectionalSegmentComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/CBidirectionalSegmentComputer.h"
#include "DGtal/geometry/curves/CDynamicSegmentComputer.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CDynamicBidirectionalSegmentComputer
    /**
       Description of \b concept '\b CDynamicBidirectionalSegmentComputer' <p>
       @ingroup Concepts
       @brief Aim: Defines the concept describing a dynamic and bidirectional
       segment computer,  ie. a model of concepts::CSegment that can extend and retract itself
       in either direction.

       ### Refinement of concepts::CBidirectionalSegmentComputer and concepts::CDynamicSegmentComputer

       ### Valid expressions and semantics


       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | Backward retraction | x.retractFront() |      |bool         |                  | returns 'true' if --x.end() != x.begin() (and decrements the end iterator), 'false' otherwise | | |


       ### Models###

       ArithmeticalDSSComputer, OneBalancedWordComputer

       ### Notes###

       @tparam T the type that should be a model of CDynamicBidirectionalSegmentComputer.
    */
    template <typename T>
    struct CDynamicBidirectionalSegmentComputer :
      concepts::CBidirectionalSegmentComputer<T>,
      concepts::CDynamicSegmentComputer<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // Methods
      BOOST_CONCEPT_USAGE( CDynamicBidirectionalSegmentComputer )
      {
        concepts::ConceptUtils::sameType( myB, myX.retractFront() );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // only if T is default constructible.
      bool myB;

      // ------------------------- Internals ------------------------------------
    private:
    }; // end of concept CDynamicBidirectionalSegmentComputer
  }// namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDynamicBidirectionalSegmentComputer_h

#undef CDynamicBidirectionalSegmentComputer_RECURSES
#endif // else defined(CDynamicBidirectionalSegmentComputer_RECURSES)
