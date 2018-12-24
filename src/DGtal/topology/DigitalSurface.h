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
 * @file DigitalSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/09/01
 *
 * Header file for module DigitalSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSurface_RECURSES)
#error Recursive header files inclusion detected in DigitalSurface.h
#else // defined(DigitalSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSurface_RECURSES

#if !defined DigitalSurface_h
/** Prevents repeated inclusion of headers. */
#define DigitalSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <set>
// JOL (2013/02/01): required to define internal tags (boost/graph/copy.hpp, l. 251 error ?).
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/properties.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/kernel/CWithGradientMap.h"
#include "DGtal/topology/CCellEmbedder.h"
#include "DGtal/topology/CSCellEmbedder.h"
#include "DGtal/topology/CDigitalSurfaceContainer.h"
#include "DGtal/topology/CDigitalSurfaceTracker.h"
#include "DGtal/topology/UmbrellaComputer.h"
//////////////////////////////////////////////////////////////////////////////
namespace boost
{
  /**
     This is the kind of boost graph that a digital surface (see DGtal::DigitalSurface) can mimick.
  */
  struct DigitalSurface_graph_traversal_category 
    : public virtual adjacency_graph_tag,
      public virtual vertex_list_graph_tag,
      public virtual incidence_graph_tag,
      public virtual edge_list_graph_tag { };
}

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalSurface
  /**
  Description of template class 'DigitalSurface' <p>

  \brief Aim: Represents a set of n-1-cells in a nD space, together
  with adjacency relation between these cells. Therefore, a digital
  surface is a pure cubical complex (model of CCubicalComplex),
  made of k-cells, 0 <= k < n. This complex is generally not a
  manifold (i.e. a kind of surface), except when it has the
  property of being well-composed.

  For geometric analysis or visualization, it is often interesting
  to look at the "dual" of the digital surface. n-1-cells form now
  vertices, n-2-cells are edges, n-3-cells are faces, and so on.  A
  digital surface is thus a model of CUndirectedSimpleGraph,
  henceforth of CUndirectedSimpleLocalGraph. The n-1-cells are then
  seen as the vertices of the graph, while their adjacencies
  constitutes the edges of the graph.

  Furthermore, starting from 3D, a digital surface is in some sense
  a model of combinatorial surface (closed or open). You may obtain
  arcs (which are oriented edges) and faces (which are sequences of
  oriented arcs turning around some pivot cell). In 3D, this dual
  digital surface is a combinatorial 2-manifold, open or not
  depending whether the digital surface is open or closed. For
  instance, arcs may have 0 or 1 incident face. 

  We construct this dual digital surface with umbrellas, which are
  sequences of adjacent n-1-cells turning around a n-3-cell, called
  the pivot of the umbrella. Faces or umbrellas are computed with
  UmbrellaComputer class.

  Proxy class to a DigitalSurfaceContainer.

  DigitalSurface is a model of the concept CUndirectedSimpleGraph,
  CUndirectedSimpleLocalGraph, CConstSinglePassRange,
  boost::CopyConstructible, boost::Assignable.

  @todo Should be a model of CCubicalComplex

  @tparam TDigitalSurfaceContainer any model of
  CDigitalSurfaceContainer: the concrete representation chosen for
  the digital surface.

  ee \ref moduleDigitalSurfaces
   */
  template <typename TDigitalSurfaceContainer>
  class DigitalSurface
  {
  public:
    typedef TDigitalSurfaceContainer DigitalSurfaceContainer;
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceContainer<DigitalSurfaceContainer> ));

    // ----------------------- boost graph tags ------------------------------
    // JOL (2013/02/01): required to define internal tags (boost/graph/copy.hpp, l. 251 error ?).
  public:
    /// the graph is undirected.
    typedef boost::undirected_tag directed_category;
    /// the graph satisfies AdjacencyListGraph and VertexListGraph concepts.
    typedef boost::DigitalSurface_graph_traversal_category traversal_category;
    /// the graph does not allow parallel edges.
    typedef boost::disallow_parallel_edge_tag edge_parallel_category;


    // ----------------------- types ------------------------------
  public:
    typedef DigitalSurface<DigitalSurfaceContainer> Self;
    typedef typename DigitalSurfaceContainer::KSpace KSpace;
    typedef typename DigitalSurfaceContainer::Cell Cell;
    typedef typename DigitalSurfaceContainer::SCell SCell;
    typedef typename DigitalSurfaceContainer::Surfel Surfel;
    typedef typename DigitalSurfaceContainer::SurfelConstIterator ConstIterator;
    typedef typename DigitalSurfaceContainer::DigitalSurfaceTracker DigitalSurfaceTracker; 
    typedef typename KSpace::Point Point;
    typedef typename KSpace::SurfelSet SurfelSet;
    /// Template rebinding for defining the type that is a mapping
    /// SCell -> Value.
    template <typename Value> struct SurfelMap {
      typedef typename KSpace::template SurfelMap<Value>::Type Type;
    };

    // ----------------------- UndirectedSimpleGraph --------------------------
  public:
    /// Defines the type for a vertex.
    typedef Surfel Vertex;
    /// Defines how to represent a size (unsigned integral type).
    typedef typename KSpace::Size Size;
    /// Defines how to represent a set of vertex.
    typedef typename KSpace::SurfelSet VertexSet;
    /// Template rebinding for defining the type that is a mapping
    /// SCell -> Value.
    template <typename Value> struct VertexMap {
      typedef typename KSpace::template SurfelMap<Value>::Type Type;
    };
    /**
       An edge is a unordered pair of vertices. To make comparisons
       easier, the smallest vertex is stored before the greatest
       vertex. Note that loops are legal.
    */ 
    struct Edge {
      /// The two vertices.
      Vertex vertices[ 2 ];
      /** 
          Constructor from vertices.
          @param v1 the first vertex.
          @param v2 the second vertex.
      */
      Edge( const Vertex & v1, const Vertex & v2 )
      {
        if ( v1 <= v2 ) 
          {
            vertices[ 0 ] = v1;
            vertices[ 1 ] = v2;
          }
        else
          {
            vertices[ 0 ] = v2;
            vertices[ 1 ] = v1;
          }
      }
      bool operator==( const Edge & other ) const
      {
        return ( vertices[ 0 ] == other.vertices[ 0 ] )
          && ( vertices[ 1 ] == other.vertices[ 1 ] );
      }
      bool operator<( const Edge & other ) const
      {
        return ( vertices[ 0 ] < other.vertices[ 0 ] )
          || ( ( vertices[ 0 ] == other.vertices[ 0 ] )
               && ( vertices[ 1 ] < other.vertices[ 1 ] ) );
      }

    };

    // ----------------------- CombinatorialSurface --------------------------
  public:
    
    /// This define a utility class for computing umbrellas.
    typedef UmbrellaComputer<DigitalSurfaceTracker> Umbrella;
    /// The state of an umbrella is a triplet (surfel, separator,
    /// pivot). Given a state, the whole umbrella can be computed.
    typedef typename Umbrella::State UmbrellaState;

    /// Defines an arc on the digital surface, i.e. an arrow between
    /// two adjacent surfels.
    struct Arc {
      Vertex base;  ///< base surfel 
      Dimension k;  ///< direction toward the head surfel
      bool epsilon; ///< orientation toward the head surfel
      /**
         Default constructor. The arc is invalid.
      */
      inline Arc()
        : base(), k( 0 ), epsilon( false ) {}
      inline Arc( const Vertex & theTail, Dimension aK, bool aEpsilon )
	: base( theTail ), k( aK ), epsilon( aEpsilon ) {}
      inline bool operator==( const Arc & other ) const
      {
	return ( base == other.base ) 
	  && ( k == other.k ) && ( epsilon == other.epsilon );
      }
      inline bool operator<( const Arc & other ) const
      {
	return ( base < other.base ) 
	  || ( ( base == other.base ) 
	       && ( ( k < other.k ) 
		    || ( ( k == other.k ) 
			 && ( epsilon < other.epsilon ) ) ) );
      }
      inline bool operator!=( const Arc & other ) const
      {
	return ( base != other.base ) 
	  || ( k != other.k ) || ( epsilon != other.epsilon );
      }
    };

    /** 
        Defines a face on the digital surface, i.e. an umbrella (open
        or closed) around a pivot cell (n-3-cell). To be able to
        compare faces, the face is characterized by one of its
        possible states. If the face is closed, the representative
        state is the smallest one. If the face is open, the
        representative state is the first (applying previous() does
        not move). 
    */
    struct Face {
      UmbrellaState state; ///< stores a state from which the whole
			   ///< umbrella can be recomputed.
      unsigned int nbVertices; ///< number of vertices incident to face.
      bool closed;         ///< tells if the face is closed or open.
      inline Face( const UmbrellaState & aState, 
                   unsigned int nb, bool aIsClosed )
        : state( aState ), nbVertices( nb ), closed( aIsClosed )
      {}
      inline bool isClosed() const 
      { return closed; }
      inline bool operator==( const Face & other ) const
      {
	return state == other.state;
      }
      inline bool operator<( const Face & other ) const
      {
	return state < other.state;
      }
 
    };
    
    /// The range of arcs is defined as a vector.
    typedef std::vector<Arc> ArcRange;
    /// The range of faces is defined as a vector.
    typedef std::vector<Face> FaceRange;
    /// The range of vertices is defined as a vector.
    typedef std::vector<Vertex> VertexRange;
    /// The set of faces is defined as set.
    typedef std::set<Face> FaceSet;


    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Destructor.
     */
    ~DigitalSurface();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    DigitalSurface ( const DigitalSurface & other );

    /**
       Copy constructor from container.
       @param container the container to copy.
    */
    DigitalSurface( const DigitalSurfaceContainer & container );

    /**
       Constructor from pointer on a dynamically allocated container.
       @param containerPtr the pointer to acquire.
    */
    DigitalSurface( DigitalSurfaceContainer* containerPtr );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    DigitalSurface & operator= ( const DigitalSurface & other );

    // ----------------------- Services --------------------------------------
  public:

    /**
       @return a const reference to the stored container.
    */
    const DigitalSurfaceContainer & container() const;

    /**
       @return a reference to the container (may be duplicated if
       several DigitalSurface points on the same).
    */
    DigitalSurfaceContainer & container();

    // ----------------- UndirectedSimpleGraph realization --------------------
  public:
    
    /**
       @return a ConstIterator on the first surfel in the container.

     @remark The digital surface delegates operations to some model of
     CDigitalSurfaceContainer. Therefore, ranges have only the
     guarantee to be a model CConstSinglePassRange, but \b not
     necessarily a model of CConstBidirectionalRange. For instance, if
     you wish to do an algorithm like: for all vertex x, for all
     vertex y, compute something, then the following code may not
     work depending on the container:

     @code
     // This snippet may NOT work.
     const ConstIterator itb = mySurface.begin(); 
     const ConstIterator ite = mySurface.end();
     for ( ConstIterator itX = itb; itX != ite; ++itX ) 
     { 
       for ( ConstIterator itY = itb; itY != ite; ++itY ) 
       { // compute something with *itX and *itY.
         // But itX == itY at each step ! }
       // now itX == itY == ite !
       }
     @endcode
     
     You may use this range only once ! This is because the iterators
     are only single pass. If you wish to visit twice the range, you
     must indeed creates two ranges by calling begin() twice (end() is
     not compulsory here, but advised).

     @code
     // This snippet does ALWAYS work.
     for ( ConstIterator itX = mySurface.begin(), 
                         itXEnd = mySurface.end();
           itX != itXEnd; ++itX ) 
     {
       for ( ConstIterator itY = mySurface.begin(), 
                           itYEnd = mySurface.end();
             itY != itYEnd; ++itY ) 
         { // compute something with *itX and *itY. }
     }
     @endcode
    */
    ConstIterator begin() const;

    /**
       @return a ConstIterator after the last surfel in the container.
    */
    ConstIterator end() const;

    /// @return the number of vertices of the graph.
    Size size() const;

    /**
       @param v any vertex of this graph
       @return the number of neighbors of this Vertex/Surfel.a
       @pre container().isInside( v )
    */
    Size degree( const Vertex & v ) const;

    /**
       Should return a reasonable estimation of the number of
       neighbors for all vertices. For instance a planar triangulation
       should return 6-8, a quad-mesh should return 4, digital surface
       is 2*(K::dimension-1).

       @return 2*(K::dimension-1)
    */
    Size bestCapacity() const;

    /**
       Writes the neighbors of [v] in the output iterator
       [it]. Neighbors are given in no specific order.

       @tparam OutputIterator the type for the output iterator
       (e.g. back_insert_iterator<std::vector<Vertex> >).

       @param[in,out] it any output iterator on Vertex (*it++ should
       be allowed), which specifies where neighbors are written.

       @param[in] v any vertex of this graph

       @pre container().isInside( v )
    */
    template <typename OutputIterator>
    void writeNeighbors( OutputIterator & it,
                         const Vertex & v ) const;

    /**
       Writes the neighbors of [v], verifying the predicate [pred] in
       the output iterator [it]. Neighbors are given in no specific
       order.

       @tparam OutputIterator the type for the output iterator
       (e.g. back_insert_iterator<std::vector<Vertex> >).

       @tparam VertexPredicate any type of predicate taking a Vertex as input.
  
       @param[in,out] it any output iterator on Vertex (*it++ should
       be allowed), which specifies where neighbors are written.

       @param[in] v any vertex of this graph
       
       @param[in] pred the predicate for selecting neighbors.

       @pre container().isInside( v )
    */
    template <typename OutputIterator, typename VertexPredicate>
    void writeNeighbors( OutputIterator & it,
                         const Vertex & v,
                         const VertexPredicate & pred ) const;


    // ----------------------- CombinatorialSurface --------------------------
  public:

    /**
       @param v any vertex (surfel) of the surface.
       @return the outgoing arcs from [v]
    */
    ArcRange outArcs( const Vertex & v ) const;

    /**
       @param v any vertex (surfel) of the surface.
       @return the ingoing arcs to [v]
    */
    ArcRange inArcs( const Vertex & v ) const;

    /**
       @param v any vertex (surfel) of the surface.
       @return the faces containing this vertex [v]: 0 in 2D, 4 in 3D,
       12 in 4D, 2(n-1)(n-2) in nD.
    */
    FaceRange facesAroundVertex( const Vertex & v ) const;

    /**
      @param a any arc (s,t)
      @return the vertex t
    */
    Vertex head( const Arc & a ) const;

    /**
      @param a any arc (s,t)
      @return the vertex s
    */
    Vertex tail( const Arc & a ) const;

    /**
       @param a any arc (s,t)
       @return the arc (t,s)
    */
    Arc opposite( const Arc & a ) const;

    /**
       [tail] and [head] should be adjacent surfel.
       
       @param tail the vertex at the tail of the arc.
       @param head the vertex at the head of the arc.
       @return the arc (tail, head)
    */
    Arc arc( const Vertex & tail, const Vertex & head ) const;

    /**
       Computes the faces incident to a given arc. Empty in 2D. 1 face
       in 3D, 2 in 4D and so one, n-2 in nD. Returned faces may be open.

       @param a any arc on the surface.
       @return a vector containing the faces incident to this arc.
    */
    FaceRange facesAroundArc( const Arc & a ) const;

    /**
       If f is incident to the arcs (s,t) and (t,u) (say), then
       (s,t,u) is a subsequence of the returned sequence.

       @param f any valid face on the digital surface (open or closed ).

       @return the sequence of vertices that touches this face. The
       order follows the order of incident arcs
    */
    VertexRange verticesAroundFace( const Face & f ) const;

    /**
       @return the set of all faces of the digital surface (open and
       closed faces).
    */
    FaceSet allFaces() const;

    /**
       This set of faces is sufficient for displaying the surface.
       @return the set of all closed faces of the digital surface.
    */
    FaceSet allClosedFaces() const;

    /**
       This set of faces is sufficient for displaying the boundary of
       the surface.
       @return the set of all closed faces of the digital surface.
    */
    FaceSet allOpenFaces() const;

    /**
       @param state any valid state (i.e. some pivot cell) on the surface.
       @return the face that contains the given [state].
    */
    Face computeFace( UmbrellaState state ) const;

    /**
       NB: there may be two arcs with the same separator.
       @param a any arc.
       @return the n-2-cell between the two surfels forming the arc.
    */
    SCell separator( const Arc & a ) const;

    /**
       NB: there may be different faces with the same pivot (except on
       the boundary of well-composed pictures).

       @param f any face.
       @return the positively oriented n-3-cell that is the pivot of the face.
    */
    SCell pivot( const Face & f ) const;


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

    /**
       Writes/Displays the object on an output stream in OFF file
       format. Cells are embbeded onto their default centroid.

       @param out the output stream where the object is written.
     */
    void exportSurfaceAs3DOFF ( std::ostream & out ) const;

    /**
       Writes/Displays the object on an output stream in OFF file
       format. Cells are embedded by [cembedder]. Normals are not
       computed.

       @param out the output stream where the object is written.
       @param cembedder any embedder of cellular grid elements.

       @tparam CellEmbedder any model of CCellEmbedder.
     */
    template <typename CellEmbedder>
    void exportEmbeddedSurfaceAs3DOFF ( std::ostream & out,
                                        const CellEmbedder & cembedder ) const;

    /**
       Writes/Displays the object on an output stream in NOFF file
       format. Cells are embedded by [cembedder]. Normals are also
       computed by the embedder.

       @param out the output stream where the object is written.
       @param cembedder any embedder of cellular grid elements.

       @tparam CellEmbedder any model of CCellEmbedder and CWithGradientMap.
     */
    template <typename CellEmbedder>
    void exportEmbeddedSurfaceAs3DNOFF ( std::ostream & out,
                                        const CellEmbedder & cembedder ) const;

    /**
       Writes/Displays the object on an output stream in NOFF file
       format. Cells are embedded by [scembedder]. Normals are also
       computed by the embedder.

       @param out the output stream where the object is written.
       @param scembedder any embedder of signed cellular grid elements.

       @tparam SCellEmbedderWithGradientMap any model of
       CSCellEmbedder and CWithGradientMap.
     */
    template <typename SCellEmbedderWithGradientMap>
    void exportAs3DNOFF( std::ostream & out,
                         const SCellEmbedderWithGradientMap & scembedder ) const;
 
    /**
       Writes/Displays the object on an output stream in NOFF file
       format. Surface spels are embedded by [cembedder]. Normals are also
       computed by the embedder.

       @param out the output stream where the object is written.
       @param cembedder any embedder of digital surface spels.
     */
    template <typename CellEmbedder>
    void exportEmbeddedIteratedSurfaceAs3DNOFF ( std::ostream & out,
                                                 const CellEmbedder & cembedder ) const;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    /// a smart pointer on the container.
    CountedPtr<DigitalSurfaceContainer> myContainer;
    /// a pointer on a tracker.
    mutable DigitalSurfaceTracker* myTracker;
    /// This object is used to compute umbrellas over the surface.
    mutable UmbrellaComputer<DigitalSurfaceTracker> myUmbrellaComputer;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    DigitalSurface();

  private:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class DigitalSurface


  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalSurface'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalSurface' to write.
   * @return the output stream after the writing.
   */
  template <typename TDigitalSurfaceContainer>
  std::ostream&
  operator<< ( std::ostream & out, 
	       const DigitalSurface<TDigitalSurfaceContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/DigitalSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSurface_h

#undef DigitalSurface_RECURSES
#endif // else defined(DigitalSurface_RECURSES)
