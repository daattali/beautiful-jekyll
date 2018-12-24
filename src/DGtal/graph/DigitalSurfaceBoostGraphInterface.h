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
 * @file DigitalSurfaceBoostGraphInterface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/01/20
 *
 * Header file for module DigitalSurfaceBoostGraphInterface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSurfaceBoostGraphInterface_RECURSES)
#error Recursive header files inclusion detected in DigitalSurfaceBoostGraphInterface.h
#else // defined(DigitalSurfaceBoostGraphInterface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSurfaceBoostGraphInterface_RECURSES

#if !defined DigitalSurfaceBoostGraphInterface_h
/** Prevents repeated inclusion of headers. */
#define DigitalSurfaceBoostGraphInterface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include <boost/property_map/property_map.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/topology/DigitalSurface.h"
//////////////////////////////////////////////////////////////////////////////


// The interface to the Boost Graph should be defined in namespace boost.
namespace boost
{

  /**
     Defines the boost graph traits for any kind of digital surface
     (see DGtal::DigitalSurface). With these definitions, a DGtal::DigitalSurface is
     a model of VertexListGraphConcept, AdjacencyGraphConcept,
     IncidenceGraphConcept, EdgeListGraphConcept. You may use
     DGtal::DigitalSurface as is in BOOST graph algorithms (see
     http://www.boost.org/doc/libs/1_52_0/libs/graph/doc/table_of_contents.html).

     The difficult part is that models of
     DGtal::CUndirectedSimpleGraph (like DGtal::DigitalSurface) are
     only required to provide vertex iterators that are models of
     SinglePassIterator. Furthermore, no edge iterators are required,
     only the list of adjacent vertices. Therefore, most of the work
     is to create iterators over edges that are "persistent",
     i.e. models of MultiPassInputIterator (very similar to
     ForwardIterator).

     @remark Note that, for now, vertex iterators are taken as is from
     the DGtal::DigitalSurface container. Hence, they must be models of
     MultiPassInputIterator. This \b is the case for containers
     DGtal::SetOfSurfels, DGtal::DigitalSetBoundary, DGtal::ImplicitDigitalSurface,
     DGtal::ExplicitDigitalSurface. This \b is \b not the case of containers
     DGtal::LightImplicitDigitalSurface and DGtal::LightExplicitDigitalSurface.

     
     @tparam TDigitalSurfaceContainer the container chosen for the
     digital surface. Should work with DGtal::DigitalSetBoundary,
     DGtal::SetOfSurfels, DGtal::ExplicitDigitalSurface,
     DGtal::ImplicitDigitalSurface. DGtal::LightImplicitDigitalSurface
     and DGtal::LightExplicitDigitalSurface containers may not work
     since their vertex iterator is not multipass.
  */
  template < class TDigitalSurfaceContainer >
  struct graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > > 
  {
    /// the adapted DGtal graph class.
    typedef DGtal::DigitalSurface< TDigitalSurfaceContainer > Adapted;
    /// the graph is undirected.
    typedef undirected_tag directed_category;
    /// the graph satisfies AdjacencyListGraph and VertexListGraph concepts.
    typedef DigitalSurface_graph_traversal_category traversal_category;
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
    typedef typename Adapted::Arc Arc;
    /// (oriented) edge type
    typedef Arc edge_descriptor;
    /// Iterator for visiting vertices. It must be a model of
    /// MultiPassInputIterator, i.e. a kind of ForwardIterator.
    typedef typename Adapted::ConstIterator vertex_iterator;

    /// This is the intermediate data structure that is used for visiting adjacent vertices.
    typedef std::vector< vertex_descriptor > AdjacentVertexContainer;
    /// This is the intermediate data structure that is used for storing out edges.
    typedef typename Adapted::ArcRange OutEdgeContainer;


    /**
     *  @return the invalid vertex for that kind of graph (default Vertex( 0 )).
     */
    static
    inline 
    vertex_descriptor null_vertex() 
    {
      return vertex_descriptor( 0 );
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
       last iterator pointing in this structure is desallocated, the
       container is automatically desallocated. This is for instance
       used by function \ref adjacent_vertices, which returns a pair
       of adjacency_iterator, both points on the same
       container. Another problem is that the user may have called
       twice \ref adjacent_vertices on the same vertex, and may wish
       to compare iterators obtained by two different calls.

       @code
       typedef typename DigitalSurface<...> G;
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
      inline
      adjacency_iterator() 
        : myIterator(), myVertices( 0 ) {}
      inline
      adjacency_iterator( typename AdjacentVertexContainer::const_iterator it,
                          const DGtal::CountedPtr< AdjacentVertexContainer > & vertices )
        : myIterator( it ), myVertices( vertices ) {}
    private:
      inline
      const Vertex & dereference() const 
      {
        ASSERT( myIterator != myVertices->end() );
        return *myIterator; 
      }

      inline
      bool equal(const adjacency_iterator& other) const
      {
        bool thisAtEnd = ( myIterator == myVertices->end() );
        bool otherAtEnd = ( other.myIterator == other.myVertices->end() );
        if ( thisAtEnd || otherAtEnd ) return thisAtEnd && otherAtEnd;
        else return *myIterator == *other.myIterator; 
      }

      inline
      void increment() { ++myIterator; }
      inline
      void decrement() { --myIterator; }

      /// The iterator pointing in the container of adjacent vertices.
      typename AdjacentVertexContainer::const_iterator myIterator;
      /// A counted pointer to the dynamically allocated container of
      /// vertices. Will be automatically deallocated when there is no
      /// more iterators pointing on it.
      DGtal::CountedPtr< AdjacentVertexContainer > myVertices;

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
       iterator pointing in this structure is desallocated, the
       container is automatically desallocated. This is for instance
       used by function \ref out_edges, which returns a pair of
       out_edge_iterator, both points on the same container. Another
       problem is that the user may have called twice \ref out_edges
       on the same vertex, and may wish to compare iterators obtained
       by two different calls..

       @code
       typedef typename DigitalSurface<...> G;
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
                                Arc,
                                bidirectional_traversal_tag,
                                const Arc & >
    {
    public:
      inline
      out_edge_iterator() 
        : myIterator(), myOutEdges( 0 ) {}
      inline
      out_edge_iterator( typename OutEdgeContainer::const_iterator it,
                         const DGtal::CountedPtr< OutEdgeContainer > & out_edges )
        : myIterator( it ), myOutEdges( out_edges ) {}
    private:
      inline
      const Arc & dereference() const
      { 
        ASSERT( myIterator != myOutEdges->end() );
        return *myIterator; 
      }

      inline
      bool equal(const out_edge_iterator & other) const
      {
        bool thisAtEnd = ( myIterator == myOutEdges->end() );
        bool otherAtEnd = ( other.myIterator == other.myOutEdges->end() );
        if ( thisAtEnd || otherAtEnd ) return thisAtEnd && otherAtEnd;
        else return *myIterator == *other.myIterator; 
      }

      inline
      void increment() { ++myIterator; }
      inline
      void decrement() { --myIterator; }

      /// The iterator pointing in the container of out edges.
      typename OutEdgeContainer::const_iterator myIterator;
      /// A counted pointer to the dynamically allocated container of
      /// out edges. Will be automatically deallocated when there is no
      /// more iterators pointing on it.
      DGtal::CountedPtr< OutEdgeContainer > myOutEdges;

      friend class iterator_core_access;
    }; // end class out_edge_iterator

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
       typedef typename DigitalSurface<...> G;
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
                                Arc,
                                forward_traversal_tag,
                                const Arc & >
    {
    public:
      edge_iterator();
      edge_iterator( ConstAlias<Adapted> graph,
                     const vertex_iterator & itB, const vertex_iterator & itE );

    private:
      const Arc & dereference() const;
      bool equal(const edge_iterator & other) const;
      void increment();

      const Adapted* myGraph;
      std::pair< vertex_iterator, vertex_iterator > myVertexRange;
      std::pair< out_edge_iterator, out_edge_iterator > myOutEdgeRange;

      friend class iterator_core_access;
    }; // end class out_edge_iterator

  }; // end struct graph_traits< >

  /**
     Defines the property map traits for any kind of digital surface.
     
     @tparam TDigitalSurfaceContainer the container chosen for the
     digital surface. 
  */
  // template < class TDigitalSurfaceContainer, typename TPropertyTag >
  // struct property_map< DGtal::DigitalSurface< TDigitalSurfaceContainer >, TPropertyTag >
  // {
    
  // }; 


  /////////////////////////////////////////////////////////////////////////////
  // Functions for the boost graph interface to DigitalSurface<TDigitalSurfaceContainer>.

  /**
     @param edge an arc (s,t) on \a digSurf.
     @param digSurf a valid digital surface.
     @return the vertex s.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_descriptor
  source( typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edge_descriptor edge,
          const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    return digSurf.tail( edge );
  }
  /**
     @param edge an arc (s,t) on \a digSurf.
     @param digSurf a valid digital surface.
     @return the vertex t.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_descriptor
  target( typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edge_descriptor edge,
          const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    return digSurf.head( edge );
  }
  
  /**
     @param digSurf a valid digital surface.
     @return a pair< vertex_iterator, vertex_iterator > that
     represents a range to visit all the vertices of \a digSurf.
  */
  template < class TDigitalSurfaceContainer >
  std::pair<
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_iterator,
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_iterator 
    >
  vertices( const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf );

  /**
     @param digSurf a valid digital surface.
     @return the number of vertices of \a digSurf.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertices_size_type
  num_vertices( const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    return digSurf.size();
  }
  
  /**
     @param u a vertex belonging to \a digSurf.
     @param digSurf a valid digital surface.
     @return a pair< adjacency_iterator, adjacency_iterator > that
     represents a range to visit the adjacent vertices of vertex \a
     u.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  std::pair<
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::adjacency_iterator,
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::adjacency_iterator 
    >
  adjacent_vertices( typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_descriptor u,
                     const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >
      ::adjacency_iterator Iterator;
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >
      ::AdjacentVertexContainer Container;
    DGtal::CountedPtr<Container> ptrAdjVertices( new Container );
    std::back_insert_iterator< Container > outIt = std::back_inserter( *ptrAdjVertices );
    digSurf.writeNeighbors( outIt, u );
    return std::make_pair( Iterator( ptrAdjVertices->begin(), ptrAdjVertices ),
                           Iterator( ptrAdjVertices->end(), ptrAdjVertices ) );
  }


  /**
     @param u a vertex belonging to \a digSurf.
     @param digSurf a valid digital surface.

     @return a pair< out_edge_iterator, out_edge_iterator > that
     represents a range to visit the out edges of vertex \a u. Each
     out edge is a tuple (u,t) of vertices, where t != u.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  std::pair<
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::out_edge_iterator,
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::out_edge_iterator 
    >
  out_edges( typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_descriptor u,
             const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >
      ::out_edge_iterator Iterator;
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >
      ::OutEdgeContainer Container;
    DGtal::CountedPtr<Container> ptrOutEdges( new Container( digSurf.outArcs( u ) ) );
    return std::make_pair( Iterator( ptrOutEdges->begin(), ptrOutEdges ),
                           Iterator( ptrOutEdges->end(), ptrOutEdges ) );
  }

  /**
     @param u a vertex belonging to \a digSurf.
     @param digSurf a valid digital surface.

     @return the number of out edges at vertex \a u. Each out edge is
     a tuple (u,t) of vertices, where t != u.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::degree_size_type
  out_degree( typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::vertex_descriptor u,
              const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    return digSurf.degree( u );
  }

  /**
     @param digSurf a valid digital surface.
     @return a pair< out_edge_iterator, out_edge_iterator > that
     represents a range to visit the out edges of vertex \a u. Each
     out edge is a tuple (u,t) of vertices, where t != u.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  std::pair<
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edge_iterator,
    typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edge_iterator 
    >
  edges( const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edge_iterator
      edge_iterator;
    return std::make_pair( edge_iterator( digSurf, digSurf.begin(), digSurf.end() ),
                           edge_iterator( digSurf, digSurf.end(), digSurf.end() ) );
  }

  /**
     @param digSurf a valid digital surface.
     @return the number of vertices of \a digSurf.
  */
  template < class TDigitalSurfaceContainer >
  inline 
  typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edges_size_type
  num_edges( const DGtal::DigitalSurface< TDigitalSurfaceContainer > & digSurf )
  {
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edge_iterator
      edge_iterator;
    typedef typename graph_traits< DGtal::DigitalSurface< TDigitalSurfaceContainer > >::edges_size_type
      edges_size_type;
    edges_size_type nbEdges = 0;
    for ( std::pair< edge_iterator, edge_iterator > ve = boost::edges( digSurf );
          ve.first != ve.second; ++ve.first ) 
      ++nbEdges;
    return nbEdges;
  }

  
} // namespace Boost


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/graph/DigitalSurfaceBoostGraphInterface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSurfaceBoostGraphInterface_h

#undef DigitalSurfaceBoostGraphInterface_RECURSES
#endif // else defined(DigitalSurfaceBoostGraphInterface_RECURSES)
