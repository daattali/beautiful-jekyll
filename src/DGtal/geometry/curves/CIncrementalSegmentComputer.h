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
 * @file CIncrementalSegmentComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CIncrementalSegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CIncrementalSegmentComputer_RECURSES)
#error Recursive header files inclusion detected in CIncrementalSegmentComputer.h
#else // defined(CIncrementalSegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CIncrementalSegmentComputer_RECURSES

#if !defined CIncrementalSegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define CIncrementalSegmentComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/CSegmentFactory.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
    /////////////////////////////////////////////////////////////////////////////
    // class CIncrementalSegmentComputer
    /**
       Description of \b concept '\b CIncrementalSegmentComputer' <p>
       @ingroup Concepts
       @brief Aim: Defines the concept describing an incremental segment computer,  
       ie. a model of CSegmentFactory that can, in addition, incrementally check 
       whether or not an implicit predicate P is true. 
       In other words, it can control its own extension from a range of one element
       (in the direction that is relative to the underlying iterator)
       so that an implicit predicate P remains true.  
     
       ### Refinement of CSegmentFactory
    
       ### Associated types : 
       the same as CSegmentFactory
  
       ### Notation
       - \a X : A type that is a model of CIncrementalSegmentComputer
       - \a x, \a y : object of type X
       - \a i : object of type X::ConstIterator
  
       ### Definitions
    
       ### Valid expressions and 


       | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
       |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
       | Initialization| x.init(i)  |                     |void         |                  |set a segment to i |x is valid and P is true | O(1) |
       | Extension test| x.isExtendableFront()|         |bool         | x is valid and P is true | check whether x can be extended to x.end() or not | x is valid and P is true | |
       | Extension     | x.extendFront()|               |bool         | x is valid and P is true | check whether x can be extended to x.end() or not, extend only if true | x is valid and P is true | |
    
       ### Invariants###

       Models of CIncrementalSegmentComputer garantee that 
       for each iterator it from s.begin() to s.end(), the range [s.begin(), it) is 
       a segment such that P is true. 
    
       @code
       for ( ConstIterator it = s.begin(), 
             ConstIterator itEnd = s.end();
             it != itEnd; ++it)
       { 
          // [s.begin(), it) is a segment:
          s.init( s.begin() ); 
          bool flag = true; 
          while ( (s.end() != it)&&(flag) ) { flag = s.extend(); }
          ASSERT( flag ); 
       }
       @endcode

    
       ### Models###
    
       ### Notes###

       @tparam T the type that should be a model of CIncrementalSegmentComputer.
    */
    template <typename T> 
    struct CIncrementalSegmentComputer : concepts::CSegmentFactory<T>
    {
      // ----------------------- Concept checks ------------------------------
    public:

      // Methods
      BOOST_CONCEPT_USAGE( CIncrementalSegmentComputer )
      {
        myX.init(myI);     

        concepts::ConceptUtils::sameType( myB, myX.isExtendableFront() );
        concepts::ConceptUtils::sameType( myB, myX.extendFront() );
      }
      // ------------------------- Private Datas --------------------------------
    private:
      T myX; // only if T is default constructible.
      typename T::ConstIterator myI;
      bool myB; 
    
      // ------------------------- Internals ------------------------------------
    private:
    
    }; // end of concept CIncrementalSegmentComputer
  } //namespace concepts 
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CIncrementalSegmentComputer_h

#undef CIncrementalSegmentComputer_RECURSES
#endif // else defined(CIncrementalSegmentComputer_RECURSES)
