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
 * @file CBidirectionalRange.h
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CBidirectionalRange
 *
 * This file is part of the DGtal library.
 */

#if defined(CBidirectionalRange_RECURSES)
#error Recursive header files inclusion detected in CBidirectionalRange.h
#else // defined(CBidirectionalRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBidirectionalRange_RECURSES

#if !defined CBidirectionalRange_h
/** Prevents repeated inclusion of headers. */
#define CBidirectionalRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/CConstBidirectionalRange.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts
  {

    /////////////////////////////////////////////////////////////////////////////
    // class CBidirectionalRange
    /**
       Description of \b concept '\b CBidirectionalRange'
       @ingroup Concepts

       \brief Aim: Defines the concept describing a bidirectional range.

       ### Refinement of CConstBidirectionalRange

       ### Provided types :

       - ReverseIterator: the reverse iterator type, a model of
       iterator concept.

       ### Valid expressions and semantics

       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       |rbegin         |\e x.rbegin()  |                     |ReverseIterator |               |           |                |            |
       |rend           |\e x.rend()    |                     |ReverseIterator |               |           |                |            |
       |rbegin         |\e x.rbegin() const |                |ConstReverseIterator |               |           |                |            | 
       |rend         |\e x.rend() const |                |ConstReverseIterator |               |           |                |            |                 

       ### Invariants

       ### Models
       PointVector

       ### Notes

       @tparam T the type that is checked. T should be a model of CBidirectionalRange.

    */
    template <typename T>
    struct CBidirectionalRange : public CConstBidirectionalRange<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::ReverseIterator ReverseIterator;
    
      BOOST_CONCEPT_ASSERT(( boost_concepts::SinglePassIteratorConcept<ReverseIterator> ));
    
      BOOST_CONCEPT_USAGE(CBidirectionalRange)
      {
        concepts::ConceptUtils::sameType( it, i.rbegin() );
        concepts::ConceptUtils::sameType( it, i.rend() );
      };
    
    private:
      T i;
      ReverseIterator it;
    }; // end of concept CBidirectionalRange
  
  } // namespace concepts

} // namespace DGtal



//                                                                      //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBidirectionalRange_h

#undef CBidirectionalRange_RECURSES
#endif // else defined(CBidirectionalRange_RECURSES)
