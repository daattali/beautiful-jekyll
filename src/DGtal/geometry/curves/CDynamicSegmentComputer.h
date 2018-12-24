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
 * @file CDynamicSegmentComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/08/31
 *
 * Header file for concept CDynamicSegmentComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDynamicSegmentComputer_RECURSES)
#error Recursive header files inclusion detected in CDynamicSegmentComputer.h
#else // defined(CDynamicSegmentComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDynamicSegmentComputer_RECURSES

#if !defined CDynamicSegmentComputer_h
/** Prevents repeated inclusion of headers. */
#define CDynamicSegmentComputer_h

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
  // class CDynamicSegmentComputer
  /**
Description of \b concept '\b CDynamicSegmentComputer' <p>
     @ingroup Concepts
     @brief Aim: Defines the concept describing a dynamic segment computer,  
    ie. a model of CSegment that can extend and retract itself 
    (in the direction that is relative to the underlying iterator).  
     
 ### Refinement of CForwardSegmentComputer 
    
 ### Associated types : the same as CForwardSegmentComputer
  
 ### Notation
     - \a X : A type that is a model of CDynamicSegmentComputer
     - \a x : object of type X
  
 ### Definitions
    
 ### Valid expressions and 


| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
| Retraction    |x.retractBack() |              |bool         |                  | returns 'tru' if ++x.begin() != x.end() (and increments the begin iterator), 'false' otherwise ||| 


 ### Invariants###
    
 ### Models###
    
 ### Notes###

@tparam T the type that should be a model of CDynamicSegmentComputer.
   */
  template <typename T> 
  struct CDynamicSegmentComputer : concepts::CForwardSegmentComputer<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // Methods
    BOOST_CONCEPT_USAGE( CDynamicSegmentComputer )
    {
      concepts::ConceptUtils::sameType( myB, myX.retractBack() );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // only if T is default constructible.
    bool myB; 
  
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of concept CDynamicSegmentComputer
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDynamicSegmentComputer_h

#undef CDynamicSegmentComputer_RECURSES
#endif // else defined(CDynamicSegmentComputer_RECURSES)
