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
 * @file CUndirectedSimpleGraph.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/03/01
 *
 * Header file for concept CUndirectedSimpleGraph.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CUndirectedSimpleGraph_RECURSES)
#error Recursive header files inclusion detected in CUndirectedSimpleGraph.h
#else // defined(CUndirectedSimpleGraph_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CUndirectedSimpleGraph_RECURSES

#if !defined CUndirectedSimpleGraph_h
/** Prevents repeated inclusion of headers. */
#define CUndirectedSimpleGraph_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CConstSinglePassRange.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal { 
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CUndirectedSimpleGraph
  /**
  Description of \b concept '\b CUndirectedSimpleGraph' <p>
  @ingroup Concepts
  @brief Aim: Represents the concept of local graph: each vertex has neighboring vertices, but we do not necessarily know all the vertices.
     
  ### Refinement of 
  CUndirectedSimpleLocalGraph, CSinglePassConstRange
    
  ### Associated types :
  - Edge: the type for the edges of the graph.

  The following types are defined in CSinglePassConstRange 
  - ConstIterator: const iterator on Vertex

  The following types are defined in CUndirectedSimpleLocalGraph
  - Size: an integral type to count the number of vertices.
  - Vertex: the type for the vertices of the graph.
  - VertexSet: the type for storing a set of vertices.
  - VertexMap: a rebinding structure to associate Value to vertices of model CVertexMap.
    
  ### Notation
  - \c X : A type that is a model of CUndirectedSimpleGraph
  - \c x : object of type X
  - \c v : object of type Vertex
  - \c out : an output iterator of type OutputIterator (model of boost::OutputIterator).
  - \c p : a predicate on vertex of type VertexPredicate (model of CVertexPredicate).
    
  ### Definitions
    
  ### Valid expressions and 


  | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
  |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
  |Size           | x.size()   |                     | Size        |                  | Returns  the number of vertices of this graph | | | 
       
    
  ### Invariants###
    
  ### Models###
  DigitalSurface, Object, IndexedDigitalSurface

  ### Notes###

  @tparam T the type that should be a model of CUndirectedSimpleGraph.
  */
  template <typename T> 
  struct CUndirectedSimpleGraph : 
    CUndirectedSimpleLocalGraph<T>, 
    CConstSinglePassRange<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // 1. define first provided types (i.e. inner types), like
    typedef typename T::Edge Edge;
    typedef typename T::Size Size;

    // 2. then check the presence of data members, operators and methods with
    BOOST_CONCEPT_USAGE( CUndirectedSimpleGraph )
    {
      // check const methods.
      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
      ConceptUtils::sameType( mySize, myX.size() );
    }

    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // do not require T to be default constructible.
    Size mySize;
    
    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of concept CUndirectedSimpleGraph

  } // namespace concepts  
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CUndirectedSimpleGraph_h

#undef CUndirectedSimpleGraph_RECURSES
#endif // else defined(CUndirectedSimpleGraph_RECURSES)
