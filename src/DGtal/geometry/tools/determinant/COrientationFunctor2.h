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
 * @file COrientationFunctor2.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/22
 *
 * Header file for concept COrientationFunctor2.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(COrientationFunctor2_RECURSES)
#error Recursive header files inclusion detected in COrientationFunctor2.h
#else // defined(COrientationFunctor2_RECURSES)
/** Prevents recursive inclusion of headers. */
#define COrientationFunctor2_RECURSES

#if !defined COrientationFunctor2_h
/** Prevents repeated inclusion of headers. */
#define COrientationFunctor2_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/tools/determinant/COrientationFunctor.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
 namespace concepts
 {
  /////////////////////////////////////////////////////////////////////////////
  // class COrientationFunctor2
  /**
     Description of \b concept '\b COrientationFunctor2' <p>
     @ingroup Concepts
     @brief Aim: This concept is a refinement of COrientationFunctor, 
     useful for simple algebraic curves that can be uniquely defined 
     by only two points.  
     
     ### Refinement of COrientationFunctor

     ### Associated types

     ### Notation
     - \e X : A type that is a model of COrientationFunctor2
     - \e x : object of type X
     - \e a , \e b : objects of type Point

     ### Valid expressions and semantics

     | Name           | Expression  | Type requirements  | Return type | Precondition | Semantics   | Post condition | Complexity |
     |----------------|-------------|--------------------|-------------|--------------|-------------|----------------|------------|
     | initialization | x.init(a,b) | a and b are points |             |              |             |                | constant   |

     ### Models
  
     InHalfPlaneBy2x2DetComputer InHalfPlaneBySimpleMatrix InGeneralizedDiskOfGivenRadius

     @tparam T the type that should be a model of COrientationFunctor2.
  */
  template <typename T>
  struct COrientationFunctor2 : concepts::COrientationFunctor<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:

    BOOST_CONCEPT_USAGE( COrientationFunctor2 )
    {
      myX.init( myA, myB );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; 
    typename T::Point myA, myB;

  }; // end of concept COrientationFunctor2
 }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined COrientationFunctor2_h

#undef COrientationFunctor2_RECURSES
#endif // else defined(COrientationFunctor2_RECURSES)
