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
 * @file CAdjacency.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/04
 *
 * Header file for concept CAdjacency.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CAdjacency_RECURSES)
#error Recursive header files inclusion detected in CAdjacency.h
#else // defined(CAdjacency_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CAdjacency_RECURSES

#if !defined CAdjacency_h
/** Prevents repeated inclusion of headers. */
#define CAdjacency_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CAdjacency
  /**
  DescriptionDescription of \b concept '\b CAdjacency' <p>
  @ingroup Concepts
   
  @brief Aim: The concept CAdjacency defines an elementary
  adjacency relation between points of a digital space.
    
  It thus distinguishes which points are close and which points are
  further away in this space. Adjacency relations are used to
  define a digital topology, in the sense of Rosenfeld or in the
  sense of Herman. In other words, and adjacency relation define a
  neighborhood graph on the points of a digital domain.
   
  ### Refinement of 
  - CUndirectedSimpleLocalGraph
   
  ### Associated types (must be defined in the model):
  - \c Space: the space of the adjacency.
  - \c Point: the digital point type.
  - \c Adjacency: the type of the adjacency itself.
   
  ###  Notations
  - \c Adj : A type that is a model of CAdjacency
  - \c adj  : Object of type Adj.
  - \c p1, \c p2 : an object of type \ref Point.
    
  ### Definitions
   
  ### Valid expressions and semantics

  | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
  |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
  | adjacency test | adj.isAdjacentTo( p1, p2 ) | \c p1 and \c p2 of same type Point. | \c bool | | Return 'true' when the two points are adjacent according to the adjacency relation \c adj | | |
  | proper adjacency test | adj.isProperlyAdjacentTo( p1, p2 ) | \c p1 and \c p2 of same type Point. | \c bool | | Return 'true' when the two points are adjacent according to the adjacency relation \c adj and if \c p1 different from \c p2 | | | 
    
  ### Invariants
   
  ### Models
  - MetricAdjacency, DomainAdjacency
   
  ### Notes
  */
  template <typename Adj>
  struct CAdjacency : CUndirectedSimpleLocalGraph<Adj>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    
    typedef typename Adj::Space Space;
    typedef typename Adj::Point Point;
    typedef typename Adj::Adjacency Adjacency;

    BOOST_CONCEPT_USAGE( CAdjacency )
    {
      // check isAdjacentTo
      ConceptUtils::sameType( myBool, myAdj.isAdjacentTo( myP1, myP2 ) );
      // check isProperlyAdjacentTo
      ConceptUtils::sameType( myBool, 
            myAdj.isProperlyAdjacentTo( myP1, myP2 ) );
    }

    // ------------------------- Private Datas --------------------------------
  private:
    Adj myAdj;
    Point myP1;
    Point myP2;
    bool myBool;
    std::back_insert_iterator< std::vector<Point> > myInserter;

    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of concept CAdjacency
  
} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CAdjacency_h

#undef CAdjacency_RECURSES
#endif // else defined(CAdjacency_RECURSES)
