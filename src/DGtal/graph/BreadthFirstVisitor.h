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
 * @file BreadthFirstVisitor.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/11/1
 *
 * Header file for template class BreadthFirstVisitor
 *
 * This file is part of the DGtal library.
 */

#if defined(BreadthFirstVisitor_RECURSES)
#error Recursive header files inclusion detected in BreadthFirstVisitor.h
#else // defined(BreadthFirstVisitor_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BreadthFirstVisitor_RECURSES

#if !defined BreadthFirstVisitor_h
/** Prevents repeated inclusion of headers. */
#define BreadthFirstVisitor_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <queue>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/kernel/sets/DigitalSetDomain.h"
#include "DGtal/topology/DomainAdjacency.h"
#include "DGtal/graph/CUndirectedSimpleLocalGraph.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class BreadthFirstVisitor
  /**
  Description of template class 'BreadthFirstVisitor' <p> \brief
  Aim: This class is useful to perform a breadth-first exploration
  of a graph given a starting point or set (called initial core).
 
  The expander implements a breadth-first algorithm on the graph of
  adjacencies. It can be used not only to detect connected
  component but also to identify the layers of the object located
  at a given distance of a starting set.
 
  The \b core of the expander is at the beginning the set of points
  at distance 0. Each layer is at a different distance from the
  initial core. The expander move layer by layer but the user is
  free to navigate on each layer.
 
  @tparam TGraph the type of the graph (models of CUndirectedSimpleLocalGraph).
 
  @code
     Graph g( ... );
     Graph::Vertex p( ... );
     BreadthFirstVisitor< Graph > visitor( g, p );
     while ( ! visitor.finished() )
       {
         BreadthFirstVisitor<Graph>::Node node = visitor.current();
         std::cout << "Vertex " << node.first 
                   << " at distance " << node.second << std::endl;
         visitor.expand();
       }
     @endcode
    
   @see testBreadthFirstVisitor.cpp
   @see testObject.cpp
   */
  template < typename TGraph, 
             typename TMarkSet = typename TGraph::VertexSet >
  class BreadthFirstVisitor
  {
    // ----------------------- Associated types ------------------------------
  public:
    typedef BreadthFirstVisitor<TGraph,TMarkSet> Self;
    typedef TGraph Graph;
    typedef TMarkSet MarkSet;
    typedef typename Graph::Size Size;
    typedef typename Graph::Vertex Vertex;
    typedef Size Data; ///< Data attached to each Vertex is the topological distance to the seed.

    // Cannot check this since some types using it are incomplete.
    ///FIXME
    // BOOST_CONCEPT_ASSERT(( concepts::CUndirectedSimpleLocalGraph< Graph > ));
    // BOOST_CONCEPT_ASSERT(( CSet< MarkSet, Vertex > ));

    // ----------------------- defined types ------------------------------
  public:

    /// Type stocking the vertex and its topological distance wrt the
    /// initial point or set.
    typedef std::pair< Vertex, Data > Node;
    /// Internal data structure for computing the breadth-first expansion.
    typedef std::queue< Node > NodeQueue;
    /// Internal data structure for storing vertices.
    typedef std::vector< Vertex > VertexList;


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~BreadthFirstVisitor();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    BreadthFirstVisitor ( const BreadthFirstVisitor & other );

    /**
     * Constructor from the graph only. The visitor is in the state
     * 'finished()'. Useful to create an equivalent of 'end()' iterator.
     *
     * @param graph the graph in which the breadth first traversal takes place.
     */
    BreadthFirstVisitor( ConstAlias<Graph> graph );

    /**
     * Constructor from a point. This point provides the initial core
     * of the visitor.
     *
     * @param graph the graph in which the breadth first traversal takes place.
     * @param p any vertex of the graph.
     */
    BreadthFirstVisitor( ConstAlias<Graph> graph, const Vertex & p );

    /**
       Constructor from iterators. All vertices visited between the
       iterators should be distinct two by two. The so specified set
       of vertices provides the initial core of the breadth first
       traversal. These vertices will all have a topological distance
       0.
       
       @tparam VertexIterator any type of single pass iterator on vertices.
       @param graph the graph in which the breadth first traversal takes place.
       @param b the begin iterator in a container of vertices. 
       @param e the end iterator in a container of vertices. 
    */
    template <typename VertexIterator>
    BreadthFirstVisitor( ConstAlias<Graph> graph, 
                         VertexIterator b, VertexIterator e );


    /**
       @return a const reference on the graph that is traversed.
    */
    const Graph & graph() const;

    // ----------------------- traversal services ------------------------------
  public:

    /**
       @return a const reference on the current visited vertex. The
       node is a pair <Vertex,Data> where the second term is the
       topological distance to the start vertex or set.

       NB: valid only if not 'finished()'.
     */
    const Node & current() const; 

    /**
       Goes to the next vertex but ignores the current vertex for
       determining the future visited vertices. Otherwise said, no
       future visited vertex will have this vertex as a father.

       NB: valid only if not 'finished()'.
     */
    void ignore();

    /**
       Goes to the next vertex and take into account the current
       vertex for determining the future visited vertices.
       NB: valid only if not 'finished()'.
     */
    void expand();

    /**
       Goes to the next vertex and taked into account the current
       vertex for determining the future visited vertices.

       @tparam VertexPredicate a type that satisfies CPredicate on Vertex.

       @param authorized_vtx the predicate that should satisfy the
       visited vertices.

       NB: valid only if not 'finished()'.
     */
    template <typename VertexPredicate>
    void expand( const VertexPredicate & authorized_vtx );
    
    /**
       @return 'true' if all possible elements have been visited.
     */
    bool finished() const;

    /**
       Force termination of the breadth first traversal. 'finished()'
       returns 'true' afterwards and 'current()', 'expand()',
       'ignore()' have no more meaning. Furthermore,
       'markedVertices()' and 'visitedVertices()' both represents the
       set of visited vertices.
     */
    void terminate();

    /**
       @return a const reference to the current set of marked
       vertices. It includes the visited vertices and the vertices
       neighbors to the current layer of vertices. NB: O(1) operation.
     */
    const MarkSet & markedVertices() const;

    /**
       @return the current set of visited vertices (a subset of marked
       vertices; excludes the marked vertices yet to be visited).
       Note that if 'finished()' is true, then 'markedVertices()' is
       equal to 'visitedVertices()' and should thus be preferred. 

       NB: computational cost is a copy of the set of marked vertices
       then as many deletion as the number of marked vertices yet to
       be visited.

       @see markedVertices
     */
    MarkSet visitedVertices() const;


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /**
     * The graph where the traversal takes place.
     */
    const Graph & myGraph;

    /**
     * Set representing the marked vertices: the ones that have been
     * visited and the one that are going to be visited soon (at
     * distance + 1).
     */
    MarkSet myMarkedVertices;

    /**
       Queue storing the vertices that are the next visited ones in
       the breadth-first traversal of the graph.
     */
    NodeQueue myQueue;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    BreadthFirstVisitor();

  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    BreadthFirstVisitor & operator= ( const BreadthFirstVisitor & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class BreadthFirstVisitor


  /**
   * Overloads 'operator<<' for displaying objects of class 'BreadthFirstVisitor'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'BreadthFirstVisitor' to write.
   * @return the output stream after the writing.
   */
  template <typename TGraph, typename TMarkSet >
  std::ostream&
  operator<< ( std::ostream & out, 
               const BreadthFirstVisitor<TGraph, TMarkSet > & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/graph/BreadthFirstVisitor.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BreadthFirstVisitor_h

#undef BreadthFirstVisitor_RECURSES
#endif // else defined(BreadthFirstVisitor_RECURSES)
