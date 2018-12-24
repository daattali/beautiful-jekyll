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
 * @file CDigitalBoundedShape.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/22
 *
 * Header file for concept CDigitalBoundedShape.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalBoundedShape_RECURSES)
#error Recursive header files inclusion detected in CDigitalBoundedShape.h
#else // defined(CDigitalBoundedShape_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalBoundedShape_RECURSES

#if !defined CDigitalBoundedShape_h
/** Prevents repeated inclusion of headers. */
#define CDigitalBoundedShape_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"

#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/kernel/CSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CDigitalBoundedShape
  /**
DescriptionDescription of \b concept '\b CDigitalBoundedShape' <p>
@ingroup Concepts
@brief Aim: designs the concept of bounded shapes in DGtal (shape for
    which upper and lower bounding bounds are available).
    
### Refinement of 
   
### Associated types :
    - Point: type for points (to characterize upper/lower bounds).
   
### Notation
    - \a X : A type that is a model of CDigitalBoundedShape
    - \a x, \a y  : Object of type X
   
### Definitions
   
### Valid expressions and semantics
   
| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|Lower bound    | x.getLowerBound()| |             |Point        |                  |compute and return the lower bound of the shape bounding box | | |
|Upper bound    | x.getUpperBound()| |             |Point        |                  |compute and return the upper bound of the shape bounding box | | |
   
### Invariants
   
### Models
      Implicit and Parametric shapes of the shape factory.
   
   
### Notes
   */
  template <typename TShape>
  struct CDigitalBoundedShape
  {
    // ----------------------- Concept checks ------------------------------
  public:
    
    typedef typename TShape::Point Point;
    
     BOOST_CONCEPT_USAGE( CDigitalBoundedShape )
    {
      // Shape should have a getUpperBound() returning a Point.
      ConceptUtils::sameType( myP, myT.getUpperBound() );
      // Shape should have a getLowerBound() returning a Point.
      ConceptUtils::sameType( myP, myT.getLowerBound() );    
    }

    // ------------------------- Private Datas --------------------------------
  private:
    TShape myT;
    Point myP;
    
  }; // end of concept CDigitalBoundedShape
  }
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalBoundedShape_h

#undef CDigitalBoundedShape_RECURSES
#endif // else defined(CDigitalBoundedShape_RECURSES)
