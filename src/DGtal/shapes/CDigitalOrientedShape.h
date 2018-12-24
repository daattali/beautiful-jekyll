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
 * @file
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/10/20
 *
 * Header file for concept CDigitalOrientedShape.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalOrientedShape_RECURSES)
#error Recursive header files inclusion detected in CDigitalOrientedShape.h
#else // defined(CDigitalOrientedShape_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalOrientedShape_RECURSES

#if !defined CDigitalOrientedShape_h
/** Prevents repeated inclusion of headers. */
#define CDigitalOrientedShape_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CCommutativeRing.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CDigitalOrientedShape
  /**
Description of \b concept '\b CDigitalOrientedShape' <p>
     @ingroup Concepts

@brief Aim: characterizes models of digital oriented shapes. For example,
     models should provide an orientation method  for  points on a
     SpaceND.  Returned value type corresponds to  DGtal::Orientation.

     
 ### Refinement of
    
 ### Associated types :
     - Point: type for digital points.

 ### Notation
     - \a X : A type that is a model of CDigitalOrientedShape
     - \a x, \a y : object of type X
    
 ### Definitions
    
 ### Valid expressions and semantics 
    
| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
| Orientation method | x.orientation( aPoint) |aPoint of type const Point & | Orientation | | return the orientation of a point @c aPoint according to the shape. Orientation values can be {INSIDE,ON,OUTSIDE} | | |
    
 ### Invariants
    
 ### Models
      Parametric and implicit shapes in the DGtal shape factory, 

 ### Notes###

@tparam T the type that should be a model of CDigitalOrientedShape.
   */
  template <typename T> 
  struct CDigitalOrientedShape
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // 1. define first provided types (i.e. inner types), like
    typedef typename T::Point Point;
   
    // 2. then check the presence of data members, operators and methods with
    BOOST_CONCEPT_USAGE( CDigitalOrientedShape )
    {
      ConceptUtils::sameType( myA, myX.orientation( p ));
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // only if T is default constructible.
    Orientation myA;
    Point p;
    
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of concept CDigitalOrientedShape
  } 
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalOrientedShape_h

#undef CDigitalOrientedShape_RECURSES
#endif // else defined(CDigitalOrientedShape_RECURSES)
