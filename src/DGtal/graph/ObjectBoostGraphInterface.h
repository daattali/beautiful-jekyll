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
 * @file ObjectBoostGraphInterface.h
 * @author Pablo Hernandez-Cerdan. Institute of Fundamental Sciences.
 * Massey University. Palmerston North, New Zealand
 *
 * @date 2016/02/01
 *
 * Header file for module ObjectBoostGraphInterface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ObjectBoostGraphInterface_RECURSES)
#error Recursive header files inclusion detected in ObjectBoostGraphInterface.h
#else // defined(ObjectBoostGraphInterface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ObjectBoostGraphInterface_RECURSES

#if !defined ObjectBoostGraphInterface_h
/** Prevents repeated inclusion of headers. */
#define ObjectBoostGraphInterface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/topology/Object.h"
//////////////////////////////////////////////////////////////////////////////


// The interface to the Boost Graph should be defined in namespace boost.
namespace boost
{

  /**
     Defines the boost graph traits for any kind of object
     (see DGtal::Object). With these definitions, a DGtal::Object is
     a model of VertexListGraphConcept, AdjacencyGraphConcept,
     IncidenceGraphConcept, EdgeListGraphConcept. You may use
     DGtal::Object as is in BOOST graph algorithms (see
     http://www.boost.org/doc/libs/1_60_0/libs/graph/doc/table_of_contents.html).

     The difficult part is that models of
     DGtal::CUndirectedSimpleGraph (like DGtal::Object) are
     only required to provide vertex iterators that are models of
     SinglePassIterator. Furthermore, no edge iterators are required,
     only the list of adjacent vertices. Therefore, most of the work
     is to create iterators over edges that are "persistent",
     i.e. models of MultiPassInputIterator (very similar to
     ForwardIterator).

     @remark Note that, for now, vertex iterators are taken as is from
     the DGtal::Object container. Hence, they must be models of
     MultiPassInputIterator.

     @tparam TDigitalTopology Topology of the set.

     @tparam TDigitalSet the container chosen for the
     digital set.
  */
  template < class TDigitalTopology, class TDigitalSet >
  struct graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >
  {
    /// the adapted DGtal graph class.
    typedef DGtal::Object< TDigitalTopology, TDigitalSet > Adapted;
    /// the graph is undirected.
    typedef undirected_tag directed_category;
    /// the graph satisfies AdjacencyListGraph and VertexListGraph concepts.
    typedef Object_graph_traversal_category traversal_category;
    /// the graph does not allow parallel edges.
    typedef disallow_parallel_edge_tag edge_parallel_category;

    /// the type for counting vertices
    typedef typename Adapted::Size vertices_size_type;
    /// the type for counting edges
    typedef typename Adapted::Size edges_size_type;
    /// the type for counting out or in edges
    typedef typename Adapted::Size degree_size_type;

    /// Vertex type
    typedef typename Adapted::Vertex Vertex;
    /// Vertex type
    typedef Vertex vertex_descriptor;
    /// (oriented) edge type
    typedef typename Adapted::Edge Edge;
    /// (oriented) edge type
    typedef Edge edge_descriptor;
    /// Iterator for visiting vertices. It must be a model of
    /// MultiPassInputIterator, i.e. a kind of ForwardIterator.
    typedef typename Adapted::ConstIterator vertex_iterator;

    /// This is the intermediate data structure that is used for visiting adjacent vertices.
    typedef std::vector< vertex_descriptor > AdjacentVertexContainer;
    /// This is the intermediate data structure that is used for storing out edges.
    typedef typename Adapted::EdgeRange OutEdgeContainer;


    /**
     *  @return the invalid vertex for that kind of graph (default Vertex()).
     */
    static
    inline
    vertex_descriptor null_vertex()
    {
      return vertex_descriptor();
    }

    /**
       Iterator for visiting adjacent vertices.  We use an iterator
       facade to create a STL-compliant iterator with as little effort
       as possible.

       \note The difficulty is that DGtal graphs do not provide
       iterators for visiting edges or adjacent vertices, but merely
       provide a method that outputs them. Therefore, this iterator \b
       shares the container of adjacent vertices (a std::vector) with
       other (potentially) iterators, through a DGtal::CountedPtr. When the
       last iterator pointing in this structure is deallocated, the
       container is automatically deallocated. This is for instance
       used by function \ref adjacent_vertices, which returns a pair
       of adjacency_iterator, both points on the same
       container. Another problem is that the user may have called
       twice \ref adjacent_vertices on the same vertex, and may wish
       to compare iterators obtained by two different calls.

       @code
       typedef typename Object<...> G;
       typedef typename graph_traits<G>::adjacency_iterator adjacency_iterator;
       G g(...);
       std::pair<adjacency_iterator,adjacency_iterator> vp1 = boost::adjacent_vertices( vertex, g );
       std::pair<adjacency_iterator,adjacency_iterator> vp2 = boost::adjacent_vertices( vertex, g );
       @endcode

       In this case, \a vp1 and \a vp2 are not pointing on the same
       structure, hence the address pointed by \a vp1 is different
       from the address pointed by \a vp2. They are then not
       comparable a priori. The adjacency_iterator is written so that
       vp1 (.first or .second) and vp2 (.first or .second) \b are
       comparable, using value comparison and out-of-range check.
    */
    class adjacency_iterator
      : public iterator_facade< adjacency_iterator,
                                Vertex,
                                bidirectional_traversal_tag,
                                const Vertex & >
    {
    public:
      /// Default, invalid, constructor.
      inline
      adjacency_iterator()
        : myIterator(), myVertices( 0 ) {}

      /**
       * Valid constructor from instance of AdjacentVertexContainer.
       * The iterator shares the container of adjacent vertices
       * (a std::vector) with other (potentially) iterators,
       * through a DGtal::CountedPtr.
       *
       * @param it const_iterator of AdjacentVertexContainer.
       * @param vertices CountedPtr of an AdjacentVertexContainer
       */
      inline
      adjacency_iterator( typename AdjacentVertexContainer::const_iterator it,
                          const DGtal::CountedPtr< AdjacentVertexContainer > & vertices )
        : myIterator( it ), myVertices( vertices ) {}

    private:
      /**
       * @return const reference to the Vertex the iterator is pointing to.
       * Required for Readable Iterator, Writable Iterator Concepts
       */
      inline
      const Vertex & dereference() const
      {
        ASSERT( myIterator != myVertices->end() );
        return *myIterator;
      }

      /**
       * Predicate to compare equal value of iterators.
       * Required to implement Single Pass Iterator Concept.
       *
       * @param other adjacency_iterator to compare with.
       *
       * @return true iff other and this refer to the same Vertex.
       */
      inline
      bool equal(const adjacency_iterator& other) const
      {
        bool thisAtEnd = ( myIterator == myVertices->end() );
        bool otherAtEnd = ( other.myIterator == other.myVertices->end() );
        if ( thisAtEnd || otherAtEnd ) return thisAtEnd && otherAtEnd;
        else return *myIterator == *other.myIterator;
      }

      /**
       * Increment iterator.
       * Required to implement Incrementable Iterator Concept.
       */
      inline
      void increment() { ++myIterator; }

      /**
       * Decrement iterator.
       * Required to implement Bidirectional Traversal Iterator Concept.
       */
      inline
      void decrement() { --myIterator; }

      // ///////////// Data Members ////////////////

      /// The iterator pointing in the container of adjacent vertices.
      typename AdjacentVertexContainer::const_iterator myIterator;
      /**
       * A counted pointer to the dynamically allocated container of
       * vertices. Will be automatically deallocated when there is no
       * more iterators pointing on it.
       */
      DGtal::CountedPtr< AdjacentVertexContainer > myVertices;

      /// Requirement for boost::iterator_facade
      friend class iterator_core_access;
    }; // end class adjacency_iterator

    /**
       Iterator for visiting out edges.  We use an iterator
       facade to create a STL-compliant iterator with as little effort
       as possible.

       \note The difficulty is that DGtal graphs do not provide
       iterators for visiting edges or adjacent vertices, but merely
       provide a method that outputs them. Therefore, this iterator \b
       shares the container of out edges (a std::vector) with other
       (potentially) iterators, through a DGtal::CountedPtr. When the last
       iterator pointing in this structure is deallocated, the
       container is automatically deallocated. This is for instance
       used by function \ref out_edges, which returns a pair of
       out_edge_iterator, both points on the same container. Another
       problem is that the user may have called twice \ref out_edges
       on the same vertex, and may wish to compare iterators obtained
       by two different calls..

       @code
       typedef typename Object<...> G;
       typedef typename graph_traits<G>::out_edge_iterator out_edge_iterator;
       G g(...);
       std::pair<out_edge_iterator,out_edge_iterator> vp1 = boost::out_edges( vertex, g );
       std::pair<out_edge_iterator,out_edge_iterator> vp2 = boost::out_edges( vertex, g );
       @endcode

       In this case, \a vp1 and \a vp2 are not pointing on the same
       structure, hence the address pointed by \a vp1 is different
       from the address pointed by \a vp2. They are then not
       comparable a priori. The out_edge_iterator is written so that
       vp1 (.first or .second) and vp2 (.first or .second) \b are
       comparable, using value comparison and out-of-range check.
    */
    class out_edge_iterator
      : public iterator_facade< out_edge_iterator,
                                Edge,
                                bidirectional_traversal_tag,
                                const Edge & >
    {
    public:
      /// Default, invalid, constructor.
      inline
      out_edge_iterator()
        : myIterator(), myOutEdges( 0 ) {}
      /**
       * Valid constructor from instance of OutEdgeContainer.
       * The iterator shares the container of out edges
       * (a std::vector) with other (potentially) iterators,
       * through a DGtal::CountedPtr.
       *
       * @param it const_iterator of OutEdgeContainer.
       * @param out_edges CountedPtr of an OutEdgeContainer
       */
      inline
      out_edge_iterator( typename OutEdgeContainer::const_iterator it,
                         const DGtal::CountedPtr< OutEdgeContainer > & out_edges )
        : myIterator( it ), myOutEdges( out_edges ) {}
    private:
      /**
       * @return const reference to the Edge the iterator is pointing to.
       * Required for Readable Iterator, Writable Iterator Concepts
       */
      inline
      const Edge & dereference() const
      {
        ASSERT( myIterator != myOutEdges->end() );
        return *myIterator;
      }

      /**
       * Predicate to compare equal value of iterators.
       * Required to implement Single Pass Iterator Concept.
       *
       * @param other out_edge_iterator to compare with.
       *
       * @return true iff other and this refer to the same Edge.
       */
      inline
      bool equal(const out_edge_iterator & other) const
      {
        bool thisAtEnd = ( myIterator == myOutEdges->end() );
        bool otherAtEnd = ( other.myIterator == other.myOutEdges->end() );
        if ( thisAtEnd || otherAtEnd ) return thisAtEnd && otherAtEnd;
        else return *myIterator == *other.myIterator;
      }

      /**
       * Increment iterator.
       * Required to implement Incrementable Iterator Concept.
       */
      inline
      void increment() { ++myIterator; }
      /**
       * Decrement iterator.
       * Required to implement Bidirectional Traversal Iterator Concept.
       */
      inline
      void decrement() { --myIterator; }

      /// The iterator pointing in the container of out edges.
      typename OutEdgeContainer::const_iterator myIterator;
      /** A counted pointer to the dynamically allocated container of
       *  out edges. Will be automatically deallocated when there is no
       *  more iterators pointing on it.
       */
      DGtal::CountedPtr< OutEdgeContainer > myOutEdges;

      /// Requirement for boost::iterator_facade
      friend class iterator_core_access;
    }; // end class out_edge_iterator

    /**
     * Alias to use in_edge_iterator as out_edge_iterator.
     * Required by filtered_graph algorithm.
     */
    using in_edge_iterator = out_edge_iterator ;

    /**
       Iterator for visiting all edges of the graph.  We use an iterator
       facade to create a STL-compliant iterator with as little effort
       as possible.

       \note The difficulty is that DGtal graphs do not provide
       iterators for visiting edges or adjacent vertices, but merely
       provide a method that outputs them. Therefore, this iterator
       mixes a vertex_iterator (to visit all vertices) and a local
       out_edge_iterator (to visit all out edges of each vertex). This
       is for instance used by function \ref edges, which returns a
       pair of edge_iterator. A potential problem is that the user may
       have called twice \ref edges, and may wish to compare iterators
       obtained by two different calls. Here, edges are constructed on
       the fly, hence iterators may not point on the same container
       even if the values are the same.

       @code
       typedef typename Object<...> G;
       typedef typename graph_traits<G>::edge_iterator edge_iterator;
       G g(...);
       std::pair<edge_iterator,edge_iterator> vp1 = boost::edges( g );
       std::pair<edge_iterator,edge_iterator> vp2 = boost::edges( g );
       @endcode

       In this case, \a vp1 and \a vp2 are not pointing on the same
       structure, hence the address pointed by \a vp1 is different
       from the address pointed by \a vp2. They are then not
       comparable a priori. The edge_iterator is written so that
       vp1 (.first or .second) and vp2 (.first or .second) \b are
       comparable, using value comparison and out-of-range check.
    */
    class edge_iterator
      : public iterator_facade< edge_iterator,
                                Edge,
                                forward_traversal_tag,
                                const Edge & >
    {
    public:
      /// Default, invalid, constructor.
      edge_iterator();
      /**
       * Valid constructor from instance of an Object (Graph),
       * and begin/end vertex_iterators.
       * This iterator mixes a vertex_iterator (to visit all vertices)
       * and a local out_edge_iterator (to visit all out edges
       * of each vertex).
       *
       * @param graph valid Object.
       * @param itB begin vertex_iterator of \b graph.
       * @param itE end vertex_iterator of \b graph.
       */
      edge_iterator( const Adapted & graph,
                     const vertex_iterator & itB, const vertex_iterator & itE );

    private:
      /**
       * @return const reference to the Edge the iterator is pointing to.
       * Required for Readable Iterator, Writable Iterator Concepts
       */
      const Edge & dereference() const;
      /**
       * Predicate to compare equal value of iterators.
       * Required to implement Single Pass Iterator Concept.
       *
       * @param other edge_iterator to compare with.
       *
       * @return true iff other and this refer to the same Edge.
       */
      bool equal(const edge_iterator & other) const;
      /**
       * Increment iterator.
       * Required to implement Incrementable Iterator Concept.
       */
      void increment();

      // /////////// Data Members //////////////
      /// Graph to iterate from.
      const Adapted* myGraph;
      /// Vertex Range to iterator from. Set at constructor.
      std::pair< vertex_iterator, vertex_iterator > myVertexRange;
      /// Local pair of out_edge_iterator. Created within this iterator.
      std::pair< out_edge_iterator, out_edge_iterator > myOutEdgeRange;

      /// Requirement for boost::iterator_facade
      friend class iterator_core_access;
    }; // end class out_edge_iterator

  }; // end struct graph_traits< >


  /////////////////////////////////////////////////////////////////////////////
  // Functions for the boost graph interface to Object<TDigitalTopology, TDigitalSet>.

  /**
     @param edge an edge (s,t) on \a obj.
     @param obj a valid object.
     @return the vertex s.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_descriptor
  source( typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edge_descriptor edge,
          const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    return obj.tail( edge );
  }
  /**
     @param edge an edge (s,t) on \a obj.
     @param obj a valid object.
     @return the vertex t.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_descriptor
  target( typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edge_descriptor edge,
          const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    return obj.head( edge );
  }

  /**
     @param obj a valid object.
     @return a pair< vertex_iterator, vertex_iterator > that
     represents a range to visit all the vertices of \a obj.
  */
  template < class TDigitalTopology, class TDigitalSet >
  std::pair<
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_iterator,
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_iterator
    >
  vertices( const DGtal::Object< TDigitalTopology, TDigitalSet > & obj );

  /**
     @param obj a valid object.
     @return the number of vertices of \a obj.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertices_size_type
  num_vertices( const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    return obj.size();
  }

  /**
     @param u a vertex belonging to \a obj.
     @param obj a valid object.
     @return a pair< adjacency_iterator, adjacency_iterator > that
     represents a range to visit the adjacent vertices of vertex \a
     u.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  std::pair<
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::adjacency_iterator,
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::adjacency_iterator
    >
  adjacent_vertices( typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_descriptor u,
                     const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >
      ::adjacency_iterator Iterator;
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >
      ::AdjacentVertexContainer Container;
    DGtal::CountedPtr<Container> ptrAdjVertices( new Container );
    std::back_insert_iterator< Container > outIt = std::back_inserter( *ptrAdjVertices );
    obj.writeNeighbors( outIt, u );
    return std::make_pair( Iterator( ptrAdjVertices->begin(), ptrAdjVertices ),
                           Iterator( ptrAdjVertices->end(), ptrAdjVertices ) );
  }


  /**
     @param u a vertex belonging to \a obj.
     @param obj a valid object.

     @return a pair< out_edge_iterator, out_edge_iterator > that
     represents a range to visit the out edges of vertex \a u. Each
     out edge is a tuple (u,t) of vertices, where t != u.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  std::pair<
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::out_edge_iterator,
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::out_edge_iterator
    >
  out_edges( typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_descriptor u,
             const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >
      ::out_edge_iterator Iterator;
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >
      ::OutEdgeContainer Container;
    DGtal::CountedPtr<Container> ptrEdges( new Container( obj.outEdges( u ) ) );
    return std::make_pair( Iterator( ptrEdges->begin(), ptrEdges ),
                           Iterator( ptrEdges->end(), ptrEdges ) );
  }


  /**
     @param u a vertex belonging to \a obj
     @param obj a valid Object.

     @return the number of out edges at vertex \a u.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::degree_size_type
  out_degree( typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::vertex_descriptor u,
              const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    return obj.degree( u );
  }

  /**
     @param obj a valid Object.
     @return a pair< edge_iterator, edge_iterator > that
     represents a range to visit all the edges of \a obj . Each
     edge is a tuple (u,t) of vertices, where t != u.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  std::pair<
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edge_iterator,
    typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edge_iterator
    >
  edges( const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edge_iterator
      edge_iterator;
    return std::make_pair( edge_iterator( obj, obj.begin(), obj.end() ),
                           edge_iterator( obj, obj.end(), obj.end() ) );
  }

  /**
     @param obj a valid object.
     @return the number of edges of \a obj.
  */
  template < class TDigitalTopology, class TDigitalSet >
  inline
  typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edges_size_type
  num_edges( const DGtal::Object< TDigitalTopology, TDigitalSet > & obj )
  {
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edge_iterator
      edge_iterator;
    typedef typename graph_traits< DGtal::Object< TDigitalTopology, TDigitalSet > >::edges_size_type
      edges_size_type;
    edges_size_type nbEdges = 0;
    for ( std::pair< edge_iterator, edge_iterator > ve = boost::edges( obj );
          ve.first != ve.second; ++ve.first )
      ++nbEdges;
    return nbEdges;
  }

} // namespace Boost


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/graph/ObjectBoostGraphInterface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ObjectBoostGraphInterface_h

#undef ObjectBoostGraphInterface_RECURSES
#endif // else defined(ObjectBoostGraphInterface_RECURSES)
