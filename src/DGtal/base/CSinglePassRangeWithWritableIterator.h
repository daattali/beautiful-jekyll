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
 * @file CSinglePassRangeWithWritableIterator.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/27
 *
 *
 * This file is part of the DGtal library.
 */

#if defined(CSinglePassRangeWithWritableIterator_RECURSES)
#error Recursive header files inclusion detected in CSinglePassRangeWithWritableIterator.h
#else // defined(CSinglePassRangeWithWritableIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSinglePassRangeWithWritableIterator_RECURSES

#if !defined CSinglePassRangeWithWritableIterator_h
/** Prevents repeated inclusion of headers. */
#define CSinglePassRangeWithWritableIterator_h

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
    // class CSinglePassRangeWithWritableIterator
    /**
       Description of \b concept '\b CSinglePassRangeWithWritableIterator' <p>
       @ingroup Concepts
       @brief Aim: refined concept of const single pass range which require that an output iterator exists.

       ###  Refinement of CSinglePassRange

       ###  Associated types :
       - OutputIterator: type of output iterator on the range.

       ###  Notation
       - \a X : A type that is a model of CSinglePassRangeWithWritableIterator
       - \a x, \a y : object of type X

       ###  Definitions

       | Name     | Expression       | Type requirements | Return type    | Precondition | Semantics                                          | Post condition | Complexity |
       |----------|------------------|-------------------|----------------|--------------|----------------------------------------------------|----------------|------------|
       | creation | \e x.\c outputIterator() |                   | OutputIterator |              | Returns an output iterator on the range first element |                |            |
     

       ###  Invariants

       ###  Models
       - ImageContainerBySTLVector::Range

       ###  Notes

       @tparam T the type that should be a model of CSinglePassRangeWithWritableIterator.
       @tparam Value the type of object t in (*it) = t.
    */
    template <typename T, typename Value>
    struct CSinglePassRangeWithWritableIterator : CConstSinglePassRange<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // 1. define first provided types (i.e. inner types), like
      typedef typename T::OutputIterator  OutputIterator;

      // possibly check these types so as to satisfy a concept with
      BOOST_CONCEPT_ASSERT(( boost::OutputIterator<OutputIterator,Value> ));

      BOOST_CONCEPT_USAGE( CSinglePassRangeWithWritableIterator )
      {
        concepts::ConceptUtils::sameType( myOutput, myX.outputIterator( ) );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // do not require T to be default constructible.
      OutputIterator myOutput;

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CSinglePassRangeWithWritableIterator

  } // namespace concepts

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSinglePassRangeWithWritableIterator_h

#undef CSinglePassRangeWithWritableIterator_RECURSES
#endif // else defined(CSinglePassRangeWithWritableIterator_RECURSES)
