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
 * @file IndexedDigitalSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/05
 *
 * Header file for module IndexedDigitalSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(IndexedDigitalSurface_RECURSES)
#error Recursive header files inclusion detected in IndexedDigitalSurface.h
#else // defined(IndexedDigitalSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IndexedDigitalSurface_RECURSES

#if !defined IndexedDigitalSurface_h
/** Prevents repeated inclusion of headers. */
#define IndexedDigitalSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <map>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/OwningOrAliasingPtr.h"
#include "DGtal/base/IntegerSequenceIterator.h"
#include "DGtal/topology/HalfEdgeDataStructure.h"
#include "DGtal/topology/CDigitalSurfaceContainer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class IndexedDigitalSurface
  /**
   * Description of template class 'IndexedDigitalSurface' <p> \brief
   * Aim: Represents a digital surface with the topology of its dual
   * surface. Its aim is to mimick the standard DigitalSurface, but to
   * optimize its traversal and topology services. The idea is simply
   * to number all its vertices (ie surfels), arcs, and faces and to
   * store its topology with an half-edge data structure. It is
   * essentially a PolygonalSurface but with services specific to
   * DigitalSurface, like a tracker, a DigitalSurfaceContainer,
   * etc. In theory, it can replace a DigitalSurface in many
   * algorithms, and is more efficient if you need to do a lot of
   * traversal on it (like many k-ring operations).
   *
   * This object stores the positions of vertices in
   * space. If you need further data attached to the surface, you may
   * use property maps (see `IndexedDigitalSurface::makeVertexMap`).
   *
   * The user instantiates the object with a model of
   * concepts::CDigitalSurfaceContainer or a DigitalSurface.
   *
   * Model of concepts::CUndirectedSimpleGraph: the vertices and edges of the
   * digital surface form indeed a graph structure.
   *
   * @note Vertices, Arcs, and Faces are all integer ranging from 0 to
   * one less than the total number of the respective elements. You
   * may thus iterate on them by just looping on integers. The index
   * INVALID_FACE is an invalid element (equal to HALF_EDGE_INVALID_INDEX).
   *
   * @tparam TDigitalSurfaceContainer the type of container from which
   * the object is built (a model of
   * concepts::CDigitalSurfaceContainer), e.g. SetOfSurfels,
   * ImplicitDigitalSurface, ExplicitDigitalSurface,
   * DigitalSetBoundary, etc.
   *
   * See \ref dgtal_digsurf_sec3_2 and \ref HalfEdgeDataStructure.
   */
  template <typename TDigitalSurfaceContainer>
  class IndexedDigitalSurface
  {
  public:
    typedef IndexedDigitalSurface<TDigitalSurfaceContainer> Self;
    typedef TDigitalSurfaceContainer             DigitalSurfaceContainer;
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceContainer< DigitalSurfaceContainer > ));

    typedef typename DigitalSurfaceContainer::KSpace KSpace;
    typedef typename KSpace::Space                   Space;
    typedef typename KSpace::Surfel                  Surfel;
    typedef typename KSpace::SCell                   SCell;
    typedef typename KSpace::Cell                    Cell;
    typedef typename Space::RealPoint                RealPoint;
    typedef HalfEdgeDataStructure::Size              Size;
    typedef HalfEdgeDataStructure::Index             Index;
    typedef HalfEdgeDataStructure::VertexIndex       VertexIndex;
    typedef HalfEdgeDataStructure::EdgeIndex         EdgeIndex;
    typedef HalfEdgeDataStructure::FaceIndex         FaceIndex;
    typedef HalfEdgeDataStructure::Triangle          Triangle;
    typedef HalfEdgeDataStructure::PolygonalFace     PolygonalFace;
    typedef std::vector<RealPoint>                   PositionsStorage;
    typedef std::vector<PolygonalFace>               PolygonalFacesStorage;
    typedef std::vector<SCell>                       SCellStorage;

    // Required by CUndirectedSimpleLocalGraph
    typedef VertexIndex                              Vertex;
    typedef std::set<Vertex>                         VertexSet;
    template <typename Value> struct                 VertexMap {
      typedef typename std::map<Vertex, Value>       Type;
    };

    // Required by CUndirectedSimpleGraph
    typedef EdgeIndex                                Edge;
    typedef IntegerSequenceIterator<VertexIndex>     ConstIterator;

    // Required for CCombinatorialSurface
    typedef HalfEdgeDataStructure::HalfEdgeIndex     Arc;
    typedef HalfEdgeDataStructure::FaceIndex         Face;
    typedef std::vector<Arc>                         ArcRange;
    typedef std::vector<Face>                        FaceRange;
    typedef std::vector<Vertex>                      VertexRange;

    BOOST_STATIC_CONSTANT( Face, INVALID_FACE = HALF_EDGE_INVALID_INDEX );

    /// This structure is used to define efficient maps between
    /// vertices and any data specified by type \a TData. The
    /// indexed digital surface provides a default vertex map for vertex
    /// positions.
    /// @tparam TData the value type for the map.
    /// @see positions
    /// @see makeVertexMap
    /// @note This property map uses a vector structure as storage.
    template <typename TData>
    struct IndexedPropertyMap {
      typedef Index             Argument;
      typedef TData             Data;
      typedef std::vector<Data> Storage;

      /// Default constructor. The object is invalid.
      IndexedPropertyMap() : mySurface( 0 ), myData( 0 ) {}

      /// Creates an empty vertex property map
      /// @param aSurface the corresponding indexed digital surface.
      /// @param s one more than the maximal allowed index (i.e. nb of elements).
      /// @param def_data the default value at initialization.
      IndexedPropertyMap( const Self& aSurface, Size s, Data def_data = Data() )
        : mySurface( &aSurface ),
          myData( Storage( s, def_data ) )
      {}

      /// Creates the IndexedPropertyMap that points to one that exists already.
      ///
      /// @param aSurface the corresponding indexed digital surface.
      /// @param aStorage the map to reference in this property map.
      ///
      /// @note This method is used to give to a user the map vertex
      /// -> position that is stored within the indexed digital surface.
      IndexedPropertyMap( const Self& aSurface,
			  Storage& aStorage )
        : mySurface( &aSurface ),
          myData( &aStorage, false )
      {}

      /// @return the associated indexed digital surface.
      const Self& surface() const
      {
        ASSERT( isValid() );
        return *mySurface;
      }

      /// This object is a function : Argument -> Data
      /// @param v any index
      /// @return the associated data
      const Data& operator()( Argument v ) const
      {
        ASSERT( isValid() && v < myData->size() );
        return (*myData)[ v ];
      }

      /// Non-mutable array access.
      /// @param v any index
      /// @return the associated data
      const Data& operator[]( Argument v ) const
      {
        ASSERT( isValid() && v < myData->size() );
        return (*myData)[ v ];
      }

      /// mutable array access.
      /// @param v any index
      /// @return the associated data
      Data& operator[]( Argument v )
      {
        ASSERT( isValid() && v < myData->size() );
        return (*myData)[ v ];
      }

      /// @return if the object was properly initialized.
      bool isValid() const { return mySurface != 0; }

      /// @return the size of the indexed map (i.e., size of associated vector).
      Size size() const { return myData->size(); }

      /// @return a reference to the storage class (a vector of Data).
      Storage& storage() { return *myData; }

      /// @return a const reference to the storage class (a vector of Data).
      const Storage& storage() const { return *myData; }

    private:
      /// The associated indexed digital surface
      const Self* mySurface;
      /// An owned or aliased pointer to the vector of data.
      OwningOrAliasingPtr<Storage> myData;
    };

    typedef IndexedPropertyMap< RealPoint >          PositionsMap;

  protected:
    typedef HalfEdgeDataStructure::HalfEdge      HalfEdge;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~IndexedDigitalSurface() {}

    /**
     * Constructor.
     */
    IndexedDigitalSurface() : isHEDSValid( false ), myContainer( 0 ) {}

    /// Constructor from digital surface container.
    /// @param surfContainer any instance of digital surface
    /// container. Pass a CountedPtr or any variant if you wish to
    /// secure its aliasing.
    IndexedDigitalSurface( ConstAlias< DigitalSurfaceContainer > surfContainer )
      : isHEDSValid( false ), myContainer( 0 )
    {
      build( surfContainer );
    }
    
    /// Clears everything.
    void clear();

    /// Builds the half-edge data structure from the given digital
    /// surface container. After that, the surface is valid.
    ///
    /// @param surfContainer any instance of digital surface
    /// container. Pass a CountedPtr or any variant if you wish to
    /// secure its aliasing.
    ///
    /// @return true if everything went allright, false if it was not
    /// possible to build a consistent data structure (e.g., butterfly
    /// neighborhoods).
    bool build( ConstAlias< DigitalSurfaceContainer > surfContainer );

    /**
       @return a const reference to the stored container.
    */
    const DigitalSurfaceContainer & container() const
    { return *myContainer; }

    /// @return a const reference to the digital space containing the digital surface.
    const KSpace& space() const
    { return myContainer->space(); }

    /// @return a const reference to the half-edge data structure.
    const HalfEdgeDataStructure& heds() const
    { return myHEDS; }

    // ------------------------- standard services ------------------------------
  public:
    /// @return the number of half edges in the structure.
    Size nbArcs() const { return myHEDS.nbHalfEdges(); }

    /// @return the number of vertices in the structure.
    Size nbVertices() const { return myHEDS.nbVertices(); }

    /// @return the number of unoriented edges in the structure.
    Size nbEdges() const { return myHEDS.nbEdges(); }

    /// @return the number of faces in the structure.
    Size nbFaces() const { return myHEDS.nbFaces(); }

    /// @return the euler characteristic of the indexed digital surface
    /// (a famous topological invariant that is the number of vertices
    /// minus the number of edges plus the number of faces).
    long Euler() const { return myHEDS.Euler(); }

    /// @return the property map stored in the surface that defines vertex positions.
    /// @note The returned map only references what is stored in the surface.
    PositionsMap positions()
    {
      return PositionsMap( *this, myPositions );
    }

    /// @return the property map stored in the surface that defines the mapping vertex index -> Surfel
    /// @note The returned map only references what is stored in the surface.
    IndexedPropertyMap< SCell > surfels()
    {
      return IndexedPropertyMap< SCell >( *this, myVertexIndex2Surfel );
    }

    /// @return the property map stored in the surface that defines the mapping arc -> Linel
    /// @note The returned map only references what is stored in the surface.
    IndexedPropertyMap< SCell > linels()
    {
      return IndexedPropertyMap< SCell >( *this, myArc2Linel );
    }

    /// @return the property map stored in the surface that defines the mapping face index -> Pointel
    /// @note The returned map only references what is stored in the surface.
    IndexedPropertyMap< SCell > pointels()
    {
      return IndexedPropertyMap< SCell >( *this, myFaceIndex2Pointel );
    }

    /// @return a vertex property map that associates some data to any vertex.
    template <typename AnyData>
    IndexedPropertyMap< AnyData > makeVertexMap() const
    {
      return IndexedPropertyMap< AnyData >( *this, nbVertices() );
    }

    /// @param value the value that is given to all vertices at initialization.
    /// @return a vertex property map that associates some data to any vertex.
    template <typename AnyData>
    IndexedPropertyMap< AnyData > makeVertexMap( AnyData value ) const
    {
      return IndexedPropertyMap< AnyData >( *this, nbVertices(), value );
    }

    /// @return an edge property map that associates some data to any edge.
    template <typename AnyData>
    IndexedPropertyMap< AnyData > makeEdgeMap() const
    {
      return IndexedPropertyMap< AnyData >( *this, nbEdges() );
    }

    /// @param value the value that is given to all edges at initialization.
    /// @return an edge property map that associates some data to any edge.
    template <typename AnyData>
    IndexedPropertyMap< AnyData > makeEdgeMap( AnyData value ) const
    {
      return IndexedPropertyMap< AnyData >( *this, nbEdges(), value );
    }

    /// @return a face property map that associates some data to any face.
    template <typename AnyData>
    IndexedPropertyMap< AnyData > makeFaceMap() const
    {
      return IndexedPropertyMap< AnyData >( *this, nbFaces() );
    }

    /// @param value the value that is given to all faces at initialization.
    /// @return a face property map that associates some data to any face.
    template <typename AnyData>
    IndexedPropertyMap< AnyData > makeFaceMap( AnyData value ) const
    {
      return IndexedPropertyMap< AnyData >( *this, nbFaces(), value );
    }

    /// Mutable accessor to vertex data.
    /// @param v any vertex.
    /// @return the mutable data associated to \a v.
    RealPoint& position( Vertex v );
    /// Const accessor to vertex data.
    /// @param v any vertex.
    /// @return the non-mutable data associated to \a v.
    const RealPoint& position( Vertex v ) const;

    /// @param[in] v any vertex index.
    /// @return the corresponding surfel.
    const SCell& surfel( Vertex v ) const
    {
      ASSERT( v < nbVertices() );
      return myVertexIndex2Surfel[ v ];
    }

    /// @param[in] a any arc (index).
    /// @return the corresponding separator linel.
    const SCell& linel( Arc a ) const
    {
      ASSERT( a < nbArcs() );
      return myArc2Linel[ a ];
    }

    /// @param[in] f any face index.
    /// @return the corresponding pivot pointel.
    const SCell& pointel( Face f ) const
    {
      ASSERT( f < nbFaces() );
      return myFaceIndex2Pointel[ f ];
    }
    
    /// @param[in] aSurfel any surfel of the surface
    ///
    /// @return the vertex (ie an index) corresponding to this surfel,
    /// or INVALID_FACE if it does not exist.
    Vertex getVertex( const SCell& aSurfel ) const
    {
      auto it = mySurfel2VertexIndex.find( aSurfel );
      return it != mySurfel2VertexIndex.end() ? it->second : INVALID_FACE;
    }

    /// @param[in] aLinel any linel that is a separator on the surface (orientation is important).
    ///
    /// @return the arc (ie an index) corresponding to this separator linel,
    /// or INVALID_FACE if it does not exist.
    Arc getArc( const SCell& aLinel ) const
    {
      auto it = myLinel2Arc.find( aLinel );
      return it != myLinel2Arc.end() ? it->second : INVALID_FACE;
    }

    /// @param[in] aPointel any pointel that is a pivot on the surface (orientation is positive).
    ///
    /// @return the face (ie an index) corresponding to this pivot pointel,
    /// or INVALID_FACE if it does not exist.
    Face getFace( const SCell& aPointel ) const
    {
      auto it = myPointel2FaceIndex.find( aPointel );
      return it != myPointel2FaceIndex.end() ? it->second : INVALID_FACE;
    }
    
    // ----------------------- Undirected simple graph services -------------------------
  public:
    /**
     * @return the number of vertices of the surface.
     */
    Size size() const;

    /**
     * @return an estimate of the maximum number of neighbors for this adjacency
     *
     * @note chosen here to be 8. Number of neighbors is 6 on average
     * for planar triangulations.
     */
    Size bestCapacity() const;

    /**
     * @param v any vertex
     *
     * @return the number of neighbors of this vertex
     */
    Size degree( const Vertex & v ) const;

    /**
     * Writes the neighbors of a vertex using an output iterator
     *
     *
     * @tparam OutputIterator the type of an output iterator writing
     * in a container of vertices.
     *
     * @param it the output iterator
     *
     * @param v the vertex whose neighbors will be writen
     */
    template <typename OutputIterator>
    void
    writeNeighbors( OutputIterator &it ,
		    const Vertex & v ) const;

    /**
     * Writes the neighbors of a vertex which satisfy a predicate using an
     * output iterator
     *
     *
     * @tparam OutputIterator the type of an output iterator writing
     * in a container of vertices.
     *
     * @tparam VertexPredicate the type of the predicate
     *
     * @param it the output iterator
     *
     * @param v the vertex whose neighbors will be written
     *
     * @param pred the predicate that must be satisfied
     */
    template <typename OutputIterator, typename VertexPredicate>
    void
    writeNeighbors( OutputIterator &it ,
		    const Vertex & v,
		    const VertexPredicate & pred) const;

    /// @return a (non mutable) iterator pointing on the first vertex.
    ConstIterator begin() const
    { return ConstIterator( 0 ); }

    /// @return a (non mutable) iterator pointing after the last vertex.
    ConstIterator end() const
    { return ConstIterator( nbVertices() ); }

    // ----------------------- CombinatorialSurface --------------------------
  public:

    /**
       @param v any vertex of the surface.
       @return the outgoing arcs from [v]
    */
    ArcRange outArcs( const Vertex & v ) const;

    /**
       @param v any vertex of the surface.
       @return the ingoing arcs to [v]
    */
    ArcRange inArcs( const Vertex & v ) const;

    /**
       @param v any vertex of the surface.
       @return the faces containing this vertex [v].
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
       Constant-time access to the next arc along the face.

       @param a any arc (s,t)
       @return the next arc along the face.
    */
    Arc next( const Arc & a ) const;

    /**
       [t] and [h] should be adjacent vertices.

       @param t the vertex at the tail of the arc.
       @param h the vertex at the head of the arc.
       @return the arc (tail, head)
    */
    Arc arc( const Vertex & t, const Vertex & h ) const;

    /**
       Convenience method for computing the face incident to a given
       arc. There is at most one face that borders an arc for
       indexed digital surface since it is a combinatorial 2-manifold.

       @param a any arc on the surface.

       @return the face around the given arc or the InvalidFace if the
       arc was a boundary arc.
    */
    Face faceAroundArc( const Arc & a ) const;

    /**
       Computes the faces incident to a given arc. There is only one
       for indexed digital surface since it is a combinatorial
       2-manifold.

       @param a any arc on the surface.
       @return a vector containing the faces incident to this arc.
    */
    FaceRange facesAroundArc( const Arc & a ) const;

    /**
       If f is incident to the arcs (s,t) and (t,u) (say), then
       (s,t,u) is a subsequence of the returned sequence.

       @param f any valid face on the surface (open or closed ).

       @return the sequence of vertices that touches this face. The
       order follows the order of incident arcs (the range size is the
       number of vertices of the polygonal face).
    */
    VertexRange verticesAroundFace( const Face & f ) const;

    /**
       @param v any vertex.
       @return 'true' if and only if vertex \a v lies on a boundary.
       @note O(1) operation
    */
    bool isVertexBoundary( const Vertex& v ) const;

    /**
       @param v any arc.
       @return 'true' if and only if arc \a v lies on a boundary (note
       that the opposite arc does not lie on the boundary).
       @note O(1) operation
    */
    bool isArcBoundary( const Arc& v ) const;

    /**
       @return the range of all faces of the indexed digital surface,
       i.e. an array containing 0, 1, 2, ..., nbFaces()-1.
    */
    FaceRange allFaces() const;
    /**
       @return the range of all arcs of the indexed digital surface,
       i.e. an array containing 0, 1, 2, ..., nbArcs()-1.
    */
    ArcRange allArcs() const;
    /**
       @return the range of all vertices of the indexed digital surface,
       i.e. an array containing 0, 1, 2, ..., nbVertices()-1.
    */
    VertexRange allVertices() const;

    /**
       This set of arcs is sufficient for displaying the boundary of
       the surface.

       @return the array of all arcs (oriented edges) lying on the
       boundary of the surface (in no particular order).
    */
    ArcRange allBoundaryArcs() const;

    /**
       This set of arcs is sufficient for displaying the boundary of
       the surface.

       @return the array of vertices lying on the boundary of the
       surface (in no particular order).
    */
    VertexRange allBoundaryVertices() const;

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
  protected:
    /// Indicates if the half-edge structure has been created/updated.
    bool                  isHEDSValid;
    /// The half-edge data structure that stores the topology of the mesh
    HalfEdgeDataStructure myHEDS;
    /// The (secured or not) pointer to the associated digital surface container.
    CountedConstPtrOrConstPtr< DigitalSurfaceContainer > myContainer;

    /// Stores the information for each Vertex.
    PositionsStorage      myPositions;
    /// Stores the polygonal faces.
    PolygonalFacesStorage myPolygonalFaces;
    /// Mapping Surfel ->  VertexIndex
    std::map< SCell, VertexIndex > mySurfel2VertexIndex;
    /// Mapping Linel  -> Arc
    std::map< SCell, Arc >         myLinel2Arc;
    /// Mapping Pointel -> FaceIndex
    std::map< SCell, FaceIndex >   myPointel2FaceIndex;
    /// Mapping VertexIndex -> Surfel
    SCellStorage          myVertexIndex2Surfel;
    /// Mapping Arc         -> Linel
    SCellStorage          myArc2Linel;
    /// Mapping FaceIndex   -> Pointel
    SCellStorage          myFaceIndex2Pointel;

    
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class IndexedDigitalSurface


  /**
   * Overloads 'operator<<' for displaying objects of class 'IndexedDigitalSurface'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'IndexedDigitalSurface' to write.
   * @return the output stream after the writing.
   */
  template <typename TDigitalSurfaceContainer>
  std::ostream&
  operator<< ( std::ostream & out,
	       const IndexedDigitalSurface<TDigitalSurfaceContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/IndexedDigitalSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IndexedDigitalSurface_h

#undef IndexedDigitalSurface_RECURSES
#endif // else defined(IndexedDigitalSurface_RECURSES)
