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
 * @file CGraphVisitor.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/01/30
 *
 * Header file for concept CGraphVisitor.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CGraphVisitor_RECURSES)
#error Recursive header files inclusion detected in CGraphVisitor.h
#else // defined(CGraphVisitor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CGraphVisitor_RECURSES

#if !defined CGraphVisitor_h
/** Prevents repeated inclusion of headers. */
#define CGraphVisitor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/tuple/tuple.hpp"
#include "DGtal/base/Common.h"
#include "DGtal/graph/CVertexPredicate.h"
#include "DGtal/graph/CVertexPredicateArchetype.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal { 
  namespace concepts {

/////////////////////////////////////////////////////////////////////////////
// class CGraphVisitor
/**
Description of \b concept '\b CGraphVisitor' <p>
@ingroup Concepts

@brief Aim: Defines the concept of a visitor onto a graph, that is an
object that traverses vertices of the graph according to some
order. The user can either use the visitor as is, or even constrain
the traversal with a given predicate.

### Refinement of

- boost::CopyConstructible

### Associated types :

- \c Graph: the type of the graph that the visitor visits, must be a model of CUndirectedSimpleLocalGraph.
- \c Vertex: the type for of each vertex, must be Graph::Vertex.
- \c Size: the type used for counting vertices in the graph, must be Graph::Size.
- \c MarkSet: the type used for representing a set of marked vertices, a model of boost::SimpleAssociativeContainer and boost::UniqueAssociativeContainer, whose key type / value type is Vertex.
- \c Data: the type is associated to the current node and may be used for several purposes (like measuring the distance between the current element and the starting point/set), a model of boost::DefaultConstructible, boost::Assignable, boost::CopyConstructible.
- \c Node: either the pair<Vertex,Data> or a type convertible to the pair<Vertex,Data>, where Vertex is the current node, Data is the attached data.
 
### Notation
 - \e X : A type that is a model of CGraphVisitor
 - \e x, \e y : object of type X

### Definitions

### Valid expressions and semantics

| Name              | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------------------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Get visited graph | \a x.graph() |                 | \c Graph      |              | Return a const reference to the visited graph | | O(1) |
| Get current node  | \a x.current() |               | \c Node       | ! \a x.finished() | Return the current visited vertex and its distance | | O(1) |
| Expand to next vertex | \a x.expand() |            |               | ! \a x.finished() | Goes to the next vertex, while taking into account the current vertex for determining the future visited vertices. | | amortized logarithmic time  |
| Expand to next vertex | \a x.expand(\a p) | \a p is a model of CVertexPredicate | | ! \a x.finished() | Goes to the next vertex, while taking into account the current vertex for determining the future visited vertices (which must satisfy predicate \a p). | | amortized logarithmic time  |
| Jump to next vertex | \a x.ignore() |              |               | ! \a x.finished() | Goes to the next vertex but ignores the current vertex when determining the future visited vertices. | | amortized logarithmic time  |
| Termination test | \a x.finished() |               | \c bool       |              | Return true if and only if the visitor has traversed all autorized vertices. | | O(1) |
| Force termination | \a x.terminate() |             |               |              | Force a premature termination of the traversal. | \a x.finished() == \c true | |
| Get set of marked vertices | \a x.markedVertices() | | \c MarkSet  |              | Returns a const reference to the current set of marked vertices. It includes the visited vertices and the vertices neighbors to the current layer of vertices. | | O(1) |
| Get set of visited vertices | \a x.visitedVertices() | | \c MarkSet  |            | Returns the current set of visited vertices (equal to markedVertices() whenever \a x.finished() ). | | linear time in the number of marked vertices. | 

### Invariants

### Models

- BreadthFirstVisitor, DepthFirstVisitor, DistanceVisitor

### Notes

@tparam T the type that should be a model of CGraphVisitor.
 */
template <typename T>
struct CGraphVisitor : boost::CopyConstructible<T>
{
  // ----------------------- Concept checks ------------------------------
public:
  // 1. define first provided types (i.e. inner types), like
  typedef typename T::Graph Graph;
  typedef typename T::Vertex Vertex;
  typedef typename T::Size Size;
  typedef typename T::Data Data;
  typedef typename T::MarkSet MarkSet;
  typedef typename T::Node Node;
  typedef CVertexPredicateArchetype<Vertex> VertexPredicate;

  BOOST_CONCEPT_ASSERT(( CUndirectedSimpleLocalGraph< Graph > ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType<Vertex, typename Graph::Vertex>::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType<Size, typename Graph::Size>::value ));
  BOOST_CONCEPT_ASSERT(( boost::SimpleAssociativeContainer< MarkSet > ));
  BOOST_CONCEPT_ASSERT(( boost::UniqueAssociativeContainer< MarkSet > ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType<Vertex, typename MarkSet::key_type>::value ));
  BOOST_CONCEPT_ASSERT(( boost::DefaultConstructible< Data > ));
  BOOST_CONCEPT_ASSERT(( boost::Assignable< Data > ));
  BOOST_CONCEPT_ASSERT(( boost::CopyConstructible< Data > ));
  BOOST_STATIC_ASSERT(( boost::is_convertible<Node, std::pair<Vertex,Data> >::value ));
  
  // To test if two types A and Y are equals, use
  // 2. then check the presence of data members, operators and methods with
  BOOST_CONCEPT_USAGE( CGraphVisitor )
  {
    // check non-const methods.
    myX.expand();
    myX.expand( myVPred );
    myX.ignore();
    myX.terminate();
    // check const methods.
    checkConstConstraints();
  }
  void checkConstConstraints() const
  {
    ConceptUtils::sameType( myGraph, myX.graph() );
    ConceptUtils::sameType( myNode, myX.current() );
    ConceptUtils::sameType( myBool, myX.finished() );
    ConceptUtils::sameType( myMarkSet, myX.markedVertices() );
    ConceptUtils::sameType( myMarkSet, myX.visitedVertices() );
  }
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Graph myGraph;
  Node myNode;
  bool myBool;
  VertexPredicate myVPred;
  MarkSet myMarkSet;

}; // end of concept CGraphVisitor

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CGraphVisitor_h

#undef CGraphVisitor_RECURSES
#endif // else defined(CGraphVisitor_RECURSES)
