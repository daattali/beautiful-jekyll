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
 * @file CForwardSegmentComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CForwardSegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CForwardSegmentComputer_RECURSES)
#error Recursive header files inclusion detected in CForwardSegmentComputer.h
#else // defined(CForwardSegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CForwardSegmentComputer_RECURSES

#if !defined CForwardSegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define CForwardSegmentComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/CIncrementalSegmentComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CForwardSegmentComputer
    /**
       Description of \b concept '\b CForwardSegmentComputer' <p>
       @ingroup Concepts
       @brief Aim: Defines the concept describing a forward segment computer.
       Like any model of CIncrementalSegmentComputer, it can control its own extension
       (in the direction that is relative to the underlying iterator)
       so that an implicit predicate P remains true. However, contrary to models
       of CIncrementalSegmentComputer, it garantees that P is also true for any
       subrange of the whole segment at any time. This extra constraint is necessary
       to be able to incrementally check whether or not the segment is maximal.

       ### Refinement of CIncrementalSegmentComputer

       ### Associated types :
       - same as CIncrementalSegmentComputer

       ### Notation
       - \a X : A type that is a model of CForwardSegmentComputer
       - \a x : object of type X
       - \a r : object of type X::Reverse

       ### Invariants###

       Contrary to models of CIncrementalSegmentComputer,
       models of CForwardSegmentComputer also garantee that
       for each iterator it from s.begin() to s.end(),
       the range [it, s.end()) is a segment such that P is true.

       @code
       for ( ConstIterator it = s.begin(),
             ConstIterator itEnd = s.end();
             it != itEnd; ++it)
       { 
         // [it, itEnd) is a segment:
         bool flag = true;
         while ( (s.end() != itEnd)&&(flag) ) { flag = s.extend(); }
         ASSERT( flag );
       }
       @endcode

       ### Models###

       ### Notes###

       @tparam T the type that should be a model of CForwardSegmentComputer.
    */
    template <typename T>
    struct CForwardSegmentComputer : concepts::CIncrementalSegmentComputer<T>
    {
      //no new syntactic constraints to check
      // ----------------------- Concept checks ------------------------------
    public:

      // ------------------------- Private Datas --------------------------------
    private:

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CForwardSegmentComputer
  } //namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CForwardSegmentComputer_h

#undef CForwardSegmentComputer_RECURSES
#endif // else defined(CForwardSegmentComputer_RECURSES)
