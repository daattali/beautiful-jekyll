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
 * @file CConstBidirectionalRange.h
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CConstBidirectionalRange
 *
 * This file is part of the DGtal library.
 */

#if defined(CConstBidirectionalRange_RECURSES)
#error Recursive header files inclusion detected in CConstBidirectionalRange.h
#else // defined(CConstBidirectionalRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CConstBidirectionalRange_RECURSES

#if !defined CConstBidirectionalRange_h
/** Prevents repeated inclusion of headers. */
#define CConstBidirectionalRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/CConstSinglePassRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CConstBidirectionalRange
    /**
       Description of \b concept '\b CConstBidirectionalRange'
       @ingroup Concepts

       \brief Aim: Defines the concept describing a bidirectional const range.

       ###  Refinement of
       CConstSinglePassRange

       ###  Provided types :

       - ConstReverseIterator: the const reverse iterator type, a model of
       const iterator concept.

 
 
       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | rbegin of range| \e x.rbegin()|                    | \e ConstReverseIterator |             | returns a reverse forward iterator on the beginning of the range | | |
       | rend of range  | \e x.rend()|                      | \e ConstReverseIterator |             | returns a reverse forward iterator after the end of the range | | |
 
 
       ###  Invariants

       ###  Models

       ###  Notes

       @tparam T the type that is checked. T should be a model of CConstBidirectionalRange.

    */
    template <typename T>
    struct CConstBidirectionalRange: CConstSinglePassRange<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::ConstReverseIterator ConstReverseIterator;
  
      BOOST_CONCEPT_ASSERT(( boost_concepts::SinglePassIteratorConcept<ConstReverseIterator> ));
  
      BOOST_CONCEPT_USAGE(CConstBidirectionalRange)
      {
        checkConstConstraints();
      }
      void checkConstConstraints() const
      {
        concepts::ConceptUtils::sameType( it, i.rbegin() );
        concepts::ConceptUtils::sameType( it, i.rend() );
      }
  
    private:
      T i;
      ConstReverseIterator it;
    }; // end of concept CConstBidirectionalRange

  } // namespace concepts

} // namespace DGtal



////
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CConstBidirectionalRange_h

#undef CConstBidirectionalRange_RECURSES
#endif // else defined(CConstBidirectionalRange_RECURSES)
