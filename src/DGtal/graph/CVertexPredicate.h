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
 * @file CVertexPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Header file for concept CVertexPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CVertexPredicate_RECURSES)
#error Recursive header files inclusion detected in CVertexPredicate.h
#else // defined(CVertexPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CVertexPredicate_RECURSES

#if !defined CVertexPredicate_h
/** Prevents repeated inclusion of headers. */
#define CVertexPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CPredicate.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CVertexPredicate
  /**
  Description of \b concept '\b CVertexPredicate' <p>
  @ingroup Concepts
  @brief Aim: Defines a predicate on a vertex.

  Associates a boolean to vertices.

  ### Refinement of CPredicate< T, T::Vertex >.
    
  ### Associated types:
  - Vertex : specifies the type for an element of the domain (inner
  type).

  @see CPredicate

  ### Models###
        
  ### Notes###
  */
  template <typename T>
  struct CVertexPredicate : CPredicate< T, typename T::Vertex> 
  {
  }; // end of concept CVertexPredicate
  
} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CVertexPredicate_h

#undef CVertexPredicate_RECURSES
#endif // else defined(CVertexPredicate_RECURSES)
