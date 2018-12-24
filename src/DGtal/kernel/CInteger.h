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
 * @file CInteger.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/02
 *
 * Header file for concept CInteger.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CInteger_RECURSES)
#error Recursive header files inclusion detected in CInteger.h
#else // defined(CInteger_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CInteger_RECURSES

#if !defined CInteger_h
/** Prevents repeated inclusion of headers. */
#define CInteger_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/kernel/CEuclideanRing.h"
#include "DGtal/kernel/CIntegralNumber.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CInteger
  /**
Description of \b concept '\b CInteger' <p>
     @ingroup Concepts
     @brief Aim: Concept checking for Integer Numbers. More precisely,
     this concept is a refinement of both CEuclideanRing and CIntegralNumber.
     
 ### Refinement of CEuclideanRing<T> and CIntegralNumber<T>
    
 ### Associated types 
    
 ### Notation
     - \a X : A type that is a model of CInteger
     - \a x, \a y  : Object of type X
    
 ### Definitions
    
 ### Valid expressions and semantics
 
 ### Invariants

    
 ### Models
BigInteger,  short, int, long long, int16_t, int32_t, int64_t, ...

 ### Notes###

   */
  template <typename T>
  struct CInteger: CEuclideanRing<T>, CIntegralNumber<T>
  {
    

  }; // end of concept CInteger
  }  
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CInteger_h

#undef CInteger_RECURSES
#endif // else defined(CInteger_RECURSES)
