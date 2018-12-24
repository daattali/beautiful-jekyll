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
 * @file CSegmentFactory.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/06
 *
 * Header file for concept CSegmentFactory.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSegmentFactory_RECURSES)
#error Recursive header files inclusion detected in CSegmentFactory.h
#else // defined(CSegmentFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSegmentFactory_RECURSES

#if !defined CSegmentFactory_h
/** Prevents repeated inclusion of headers. */
#define CSegmentFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/CSegment.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CSegmentFactory
    /**
       Description of \b concept '\b CSegmentFactory' <p>
       @ingroup Concepts
       @brief Aim: Defines the concept describing a segment 
       ie. a valid and not empty subrange, which can construct
       instances of its own type or of derived type. 

       ### Refinement of CSegment

       ### Associated types :
       - Self, its own type
       - Reverse, same as Self but using std::reverse_iterator<Self::ConstIterator>
       instead of Self::ConstIterator as the underlying iterator

       ### Notation
       - \a X : A type that is a model of CSegmentFactory
       - \a x : object of type X

       ### Definitions

       ### Valid expressions and semantics


       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | getSelf method| x.getSelf()|                     |X::Self      |                  |returns an instance of Self, which is constructed from the same input parameters used to construct x (if any) | | depends on the internal structures defined in x |
       | conversion    | x.getReverse() |                 |X::Reverse   |                  |returns an instance of Reverse, which is constructed from the same input parameters used to construct x (if any) | | depends on the internal structures defined in x |


       ### Invariants###

       ### Models###

       ### Notes###

       @tparam T the type that should be a model of CSegmentFactory.
    */
    template <typename T>
    struct CSegmentFactory : concepts::CSegment<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // Inner types
      typedef typename T::Self Self;
      BOOST_STATIC_ASSERT(( boost::is_same< T, Self >::value ));
      typedef typename T::Reverse Reverse;
      // Methods
      BOOST_CONCEPT_USAGE( CSegmentFactory )
      {
        concepts::ConceptUtils::sameType( myT, myT.getSelf() );
        concepts::ConceptUtils::sameType( myRT, myT.getReverse() );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myT; // only if T is default constructible.
      Reverse myRT; 

      // ------------------------- Internals ------------------------------------
    private:

    }; // end of concept CSegmentFactory
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSegmentFactory_h

#undef CSegmentFactory_RECURSES
#endif // else defined(CSegmentFactory_RECURSES)
