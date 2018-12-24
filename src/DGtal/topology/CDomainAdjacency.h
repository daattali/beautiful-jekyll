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
 * @file CDomainAdjacency.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/17
 *
 * Header file for concept CDomainAdjacency.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDomainAdjacency_RECURSES)
#error Recursive header files inclusion detected in CDomainAdjacency.h
#else // defined(CDomainAdjacency_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDomainAdjacency_RECURSES

#if !defined CDomainAdjacency_h
/** Prevents repeated inclusion of headers. */
#define CDomainAdjacency_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/topology/CAdjacency.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CDomainAdjacency
  /**
  Description of \b concept '\b CDomainAdjacency' <p> 
  @ingroup Concepts 
   
  @brief Aim: Refines the concept CAdjacency by telling that the
  adjacency is specific to a given domain of the embedding digital
  space.
   
  This class is useful to define subspaces with restricted
  neighborhood relations. For instance, you can limit the adjacency
  to an object, then to its border, then to a subset of its border,
  etc.
    
  ### Refinement of 
  CAdjacency
   
  ### Associated types :
  - Domain: the domain of this adjacency.
  - Predicate: the type of the predicate "is in domain ?"
   
  ###  Notation
  - \a X : A type that is a model of CDomainAdjacency
  - \a x, \a y  : Object of type X
   
  ### Definitions
   
  ###  Valid expressions and semantics

  | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
  |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
  | embedding domain | x.domain() | | const Domain & | | return a reference to the embedding domain.| |  O(1) |
  | "is in domain ?" predicate | x.predicate() | | const Predicate & | | return a reference to the predicate object that is characteristic of the embedding domain.| |  O(1) |
   
  ### Invariants
   
  ### Models
  DomainAdjacency
   
  ### Notes
  */
  template <typename T>
  struct CDomainAdjacency : CAdjacency<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:

    typedef typename Adj::Domain Domain;
    typedef typename Adj::Predicate Predicate;

    // ------------------------- Private Datas --------------------------------
  private:
    BOOST_CONCEPT_USAGE( CDomainAdjacency )
    {
      // check domain()
      ConceptUtils::sameType( myDomain, myT.domain() );
      // check predicate()
      ConceptUtils::sameType( myPredicate, myT.predicate() );
    }

    // ------------------------- Internals ------------------------------------
  private:
    T myT;
    Domain myDomain;
    Predicate myPredicate;
    
  }; // end of concept CDomainAdjacency
  
} // namespace concepts
} // namespace DGtal

                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDomainAdjacency_h

#undef CDomainAdjacency_RECURSES
#endif // else defined(CDomainAdjacency_RECURSES)
