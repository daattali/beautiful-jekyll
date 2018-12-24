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
 * @file CBidirectionalSegmentComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CBidirectionalSegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CBidirectionalSegmentComputer_RECURSES)
#error Recursive header files inclusion detected in CBidirectionalSegmentComputer.h
#else // defined(CBidirectionalSegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBidirectionalSegmentComputer_RECURSES

#if !defined CBidirectionalSegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define CBidirectionalSegmentComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/CForwardSegmentComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CBidirectionalSegmentComputer
    /**
       Description of \b concept '\b CBidirectionalSegmentComputer' <p>
       @ingroup Concepts
       @brief Aim: Defines the concept describing a bidirectional segment computer,  
       ie. a model of concepts::CSegment that can extend itself in the two possible directions. 
     
       ### Refinement of CForwardSegmentComputer 
    
       ### Associated types : the same as concepts::CForwardSegmentComputer
  
       ### Notation
       - \a X : A type that is a model of CBidirectionalSegmentComputer
       - \a x : object of type X
  
       ### Definitions
    
       ### Valid expressions and 


       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | Extension test | x.isExtendableBack() |      |bool         |                  | check whether x can be extended to - -x.begin() or not | | |
       | Extension      | x.extendBack()       |      |bool         |                  | check whether x can be extended to - -x.begin() or not, extend if true | | |
     
    
       ### Invariants###
    
       ### Models###

       StandardDSS6Computer, StabbingLineComputer, StabbingCircleComputer    

       ### Notes###

       @tparam T the type that should be a model of CBidirectionalSegmentComputer.
    */
    template <typename T> 
    struct CBidirectionalSegmentComputer : concepts::CForwardSegmentComputer<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:
      // Methods
      BOOST_CONCEPT_USAGE( CBidirectionalSegmentComputer )
      {
        concepts::ConceptUtils::sameType( myB, myX.isExtendableBack() );
        concepts::ConceptUtils::sameType( myB, myX.extendBack() );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // only if T is default constructible.
      bool myB; 
  
      // ------------------------- Internals ------------------------------------
    private:
    
    }; // end of concept CBidirectionalSegmentComputer
  } //namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBidirectionalSegmentComputer_h

#undef CBidirectionalSegmentComputer_RECURSES
#endif // else defined(CBidirectionalSegmentComputer_RECURSES)
