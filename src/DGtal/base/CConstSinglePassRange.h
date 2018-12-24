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
 * @file CConstSinglePassRange.h
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CConstSinglePassRange
 *
 * This file is part of the DGtal library.
 */

#if defined(CConstSinglePassRange_RECURSES)
#error Recursive header files inclusion detected in CConstSinglePassRange.h
#else // defined(CConstSinglePassRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CConstSinglePassRange_RECURSES

#if !defined CConstSinglePassRange_h
/** Prevents repeated inclusion of headers. */
#define CConstSinglePassRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace concepts {
    
    /////////////////////////////////////////////////////////////////////////////
    // class CConstSinglePassRange
    /**
       Description of \b concept '\b CConstSinglePassRange' <p>
       @ingroup Concepts
    
       \brief Aim: Defines the concept describing a const single pass range.
     
       \tparam T the type that should be a model of CConstSinglePassRange.

       ### Refinement of
    
       ### Associated types :

       - \e ConstIterator: the const iterator type, a model of const iterator
       concept (see boost_concepts::SinglePassIteratorConcept).

       ### Notation
       - \e T : A type that is a model of CConstSinglePassRange
       - \e x : object of type \e T

       ### Valid expressions and semantics

       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | begin of range| \e x.begin()|                    | \e ConstIterator |             | returns a forward iterator on the beginning of the range | | |
       | end of range  | \e x.end()|                      | \e ConstIterator |             | returns a forward iterator after the end of the range | | |
    
       ### Invariants
    
       - Valid range. For any Range x, [\e x.begin(), \e x.end()) is a
       valid range, that is, \e x.end() is reachable from \e x.begin()
       in a finite number of increments.
       - Completeness. An algorithm that iterates through the range [\e x.begin(), \e x.end()) will pass through every element of \e x.

       ### Models

    */
    template <typename T>
    struct CConstSinglePassRange
    {
      // ----------------------- Concept checks ------------------------------
    public:
      typedef typename T::ConstIterator ConstIterator;
    
      BOOST_CONCEPT_ASSERT(( boost_concepts::SinglePassIteratorConcept<ConstIterator> ));
    
      BOOST_CONCEPT_USAGE(CConstSinglePassRange)
      {
        checkConstConstraints();
      }
      void checkConstConstraints() const
      {
        concepts::ConceptUtils::sameType( it, i.begin() );
        concepts::ConceptUtils::sameType( it, i.end() );
      }
    
    private:
      T i;
      ConstIterator it;
    }; // end of concept CConstSinglePassRange

  } // namespace concepts
    
} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CConstSinglePassRange_h

#undef CConstSinglePassRange_RECURSES
#endif // else defined(CConstSinglePassRange_RECURSES)
