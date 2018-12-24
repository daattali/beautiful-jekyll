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
 * @file CVertexMap.h
 * @author Jérémy Gaillard (\c jeremy.gaillard@insa-lyon.fr )
 * Institut National des Sciences Appliquées - INSA, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/07/11
 *
 * Header file for concept CVertexMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CVertexMap_RECURSES)
#error Recursive header files inclusion detected in CVertexMap.h
#else // defined(CVertexMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CVertexMap_RECURSES

#if !defined CVertexMap_h
/** Prevents repeated inclusion of headers. */
#define CVertexMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CPredicate.h"
#include "boost/concept_check.hpp"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal { 
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CVertexMap
  /**
  Description of \b concept '\b CVertexMap' <p>
  @ingroup Concepts
  \brief Aim: models of CVertexMap concept implement mapping
  between graph vertices and values.
  
  This concept is associated with concepts related to graph  in
  DGtal (CUndirectedSimpleLocalGraph and CUndirectedSimpleGraph). Associates a value to each vertex of a graph.
  
  ### Associated types :
  - Vertex : specifies the type for an element of the domain (inner type).
  - Value : specifies the type for a value (inner type).
   
  ###  Notation
  - \a X : A type that is a model of CVertexMap
  - \a x : Object of type X
  - \a v : Object of type Vertex
  - \a val : Object of type Value
   
  ### Definitions
   
   
  ###  Valid expressions and
   
  | Name      | Expression              | Type requirements                           | Return type | Precondition | Semantics                                 | Post condition | Complexity |
  |-----------|-------------------------|---------------------------------------------|-------------|--------------|-------------------------------------------|----------------|------------|
  | Set value | x.setValue(vertex, val) | vertex of type Vertex and val of type Value | void        |              | set a given value val to a given vertex v |                |            |
  | Accessor  | x(vertex)               | vertex of type Vertex                       | Value       |              | Access to the value at vertex             |                |            |
   
   
  ###  Invariants
     
  ###  Models
  - ImageContainerBySTLVector, ImageContainerBySTLMap,
  ImageContainerByITKImage, ImageContainerByHashTree
  - Any adapted type from STLMapToVertexMapAdapter  
   
  ### Notes###
  */
  template <typename T>
  struct CVertexMap:
    boost::Assignable<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // 1. define first provided types (i.e. inner types), like
    typedef typename T::Vertex Vertex;
    typedef typename T::Value Value;
    
    // 2. then check the presence of data members, operators and methods with
    BOOST_CONCEPT_USAGE( CVertexMap )
    {
      ConceptUtils::sameType( myValue, myX.operator()(myVertex) );
      myX.setValue(myVertex, myValue);
    }
    
    // ------------------------- Private Datas --------------------------------
  private:
    T myX;
    Vertex myVertex;
    Value myValue;
    
  }; // end of concept CVertexMap
  
} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CVertexMap_h

#undef CVertexMap_RECURSES
#endif // else defined(CVertexMap_RECURSES)
