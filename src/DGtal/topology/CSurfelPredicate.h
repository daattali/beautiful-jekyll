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
 * @file CSurfelPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Header file for concept CSurfelPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSurfelPredicate_RECURSES)
#error Recursive header files inclusion detected in CSurfelPredicate.h
#else // defined(CSurfelPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSurfelPredicate_RECURSES

#if !defined CSurfelPredicate_h
/** Prevents repeated inclusion of headers. */
#define CSurfelPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CPredicate.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CSurfelPredicate
  /**
  Description of \b concept '\b CSurfelPredicate' <p>
  @ingroup Concepts
  @brief Aim: Defines a predicate on a surfel.
     
  Associates a boolean to surfels.

  ### Refinement of 
  CPredicate< T, T::Surfel >.
    
  ### Associated types:
  - Surfel: specifies the type for an element of the domain (inner
  type).

  @see CPredicate

  ### Models###
  BoundaryPredicate, FrontierPredicate, SurfelSetPredicate

  ### Notes###
  */
  template <typename T>
  struct CSurfelPredicate : CPredicate< T, typename T::Surfel> 
  {
  }; // end of concept CSurfelPredicate
  
} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSurfelPredicate_h

#undef CSurfelPredicate_RECURSES
#endif // else defined(CSurfelPredicate_RECURSES)
