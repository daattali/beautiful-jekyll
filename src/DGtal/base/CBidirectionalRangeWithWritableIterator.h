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
 * @file CBidirectionalRangeWithWritableIterator.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/27
 *
 *
 * This file is part of the DGtal library.
 */

#if defined(CBidirectionalRangeWithWritableIterator_RECURSES)
#error Recursive header files inclusion detected in CBidirectionalRangeWithWritableIterator.h
#else // defined(CBidirectionalRangeWithWritableIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBidirectionalRangeWithWritableIterator_RECURSES

#if !defined CBidirectionalRangeWithWritableIterator_h
/** Prevents repeated inclusion of headers. */
#define CBidirectionalRangeWithWritableIterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CSinglePassRangeWithWritableIterator.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CBidirectionalRangeWithWritableIterator
    /**
       Description of \b concept '\b CBidirectionalRangeWithWritableIterator'
       @ingroup Concepts
       @brief Aim: refined concept of bidirectional range which require that a reverse output iterator exists.


       ### Refinement of CSinglePassRangeWithWritableIterator

       ### Associated types :
       - OutputIterator: type of output iterator on the range.

       ### Notation
       - \a X : A type that is a model of CBidirectionalRangeWithWritableIterator
       - \a x, \a y : object of type X


       ### Definitions


       | Name| Expression       | Type requirements | Return type    | Precondition | Semantics                                          | Post condition | Complexity |
       |----------|------------------|-------------------|----------------|--------------|----------------------------------------------------|----------------|------------|
       | creation | routputIterator() |                   | ReverseOutputIterator |              | Returns a reverse output iterator on the range first element |                |            |
       |          |                  |                   |                |              |                                                    |                |            |


       ### Invariants###

       ### Models###

       ImageContainerBySTLVector::Range

       ### Notes###

       @tparam T the type that should be a model of CBidirectionalRangeWithWritableIterator.
       @tparam Value the type of object t in (*it) = t.

    */
    template <typename T, typename Value>
    struct CBidirectionalRangeWithWritableIterator : CSinglePassRangeWithWritableIterator<T, Value>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // 1. define first provided types (i.e. inner types), like
      typedef typename T::ReverseOutputIterator  ReverseOutputIterator;
      // possibly check these types so as to satisfy a concept with
      //BOOST_CONCEPT_ASSERT(( CConcept< InnerType > ));

      BOOST_CONCEPT_USAGE( CBidirectionalRangeWithWritableIterator )
      {
        concepts::ConceptUtils::sameType( myOutput, myX.routputIterator( ) );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // do not require T to be default constructible.
      ReverseOutputIterator myOutput;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CBidirectionalRangeWithWritableIterator

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBidirectionalRangeWithWritableIterator_h

#undef CBidirectionalRangeWithWritableIterator_RECURSES
#endif // else defined(CBidirectionalRangeWithWritableIterator_RECURSES)
