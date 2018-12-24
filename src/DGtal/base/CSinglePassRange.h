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
 * @file CSinglePassRange.h
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CSinglePassRange
 *
 * This file is part of the DGtal library.
 */

#if defined(CSinglePassRange_RECURSES)
#error Recursive header files inclusion detected in CSinglePassRange.h
#else // defined(CSinglePassRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSinglePassRange_RECURSES

#if !defined CSinglePassRange_h
/** Prevents repeated inclusion of headers. */
#define CSinglePassRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/CConstSinglePassRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts {
    
    /////////////////////////////////////////////////////////////////////////////
    // class CSinglePassRange
    /**
       DescriptionDescription of \b concept '\b CSinglePassRange' ###
       @ingroup Concepts

       \brief Aim: Defines the concept describing a range.

       ### Refinement of CConstSinglePassRange

       ### Provided types:

       - Iterator: the iterator type, a model of iterator concept
       (see boost concept SinglePassIteratorConcept).

       ### Notation:

       - x an object of a model of CSinglePassConstRange.

       Name | Expression | Type requirements | Return type | Precondition | Semantics | Post condition | Complexity|
       -----|------------|-------------------|-------------|--------------|-----------|----------------|-----------|
       begin| x.begin()  |                   | Iterator    |              |           |                |           |
       end  | x.end()    |                   | Iterator    |              |           |                |           |


       ### Invariants

       ### Models

       ### Notes

       @tparam T the type that is checked. T should be a model of CSinglePassRange.

    */
    template <typename T>
    struct CSinglePassRange : CConstSinglePassRange<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::Iterator Iterator;

      BOOST_CONCEPT_ASSERT(( boost_concepts::SinglePassIteratorConcept<Iterator> ));

      BOOST_CONCEPT_USAGE(CSinglePassRange)
      {
        Iterator it=i.begin();
        it=i.end();
      };

    private:
      T i;
    }; // end of concept CSinglePassRange

  } // namespace concepts

} // namespace DGtal



//                                        //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSinglePassRange_h

#undef CSinglePassRange_RECURSES
#endif // else defined(CSinglePassRange_RECURSES)
