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
 * @file CVertexPredicateArchetype.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2013/01/29
 *
 * Header file for concept CVertexPredicateArchetype.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CVertexPredicateArchetype_RECURSES)
#error Recursive header files inclusion detected in CVertexPredicateArchetype.h
#else // defined(CVertexPredicateArchetype_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CVertexPredicateArchetype_RECURSES

#if !defined CVertexPredicateArchetype_h
/** Prevents repeated inclusion of headers. */
#define CVertexPredicateArchetype_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CVertexPredicateArchetype
  /**
  Description of \b class '\b CVertexPredicateArchetype' <p>

  @brief Aim: Defines a an archetype for concept CVertexPredicate.
  @tparam TVertex the type chosen for vertices.
  */
  template <typename TVertex>
  struct CVertexPredicateArchetype
  {
    typedef CVertexPredicateArchetype<TVertex> Self;
    typedef TVertex Vertex;
    bool operator()( const Vertex & /* p */ ) const
    { return true; }
    Self & operator=( const Self & /* other */ )
    {
      return *this;
    }
  }; // end of concept CVertexPredicateArchetype
  
} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CVertexPredicateArchetype_h

#undef CVertexPredicateArchetype_RECURSES
#endif // else defined(CVertexPredicateArchetype_RECURSES)
