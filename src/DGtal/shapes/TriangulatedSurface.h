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
 * @file TriangulatedSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2017/02/05
 *
 * Header file for module TriangulatedSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TriangulatedSurface_RECURSES)
#error Recursive header files inclusion detected in TriangulatedSurface.h
#else // defined(TriangulatedSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TriangulatedSurface_RECURSES

#if !defined TriangulatedSurface_h
/** Prevents repeated inclusion of headers. */
#define TriangulatedSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/base/OwningOrAliasingPtr.h"
#include "DGtal/base/IntegerSequenceIterator.h"
#include "DGtal/topology/HalfEdgeDataStructure.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class TriangulatedSurface
  /**
   * Description of template class 'TriangulatedSurface' <p> \brief
   * Aim: Represents a triangulated surface. The topology is stored
   * with a half-edge data structure. This object stored the positions
   * of vertices in space. If you need further data attached to the
   * surface, you may use property maps (see
   * `TriangulatedSurface::makeVertexMap`).
   *
   * For now, the user must add vertices and triangles, and when
   * finished, call 'build()'.
   *
   * Model of CUndirectedSimpleGraph: the vertices and edges of the
   * triangulated surface form indeed a graph structure.
   *
   * @note Vertices, Arcs, and Faces are all integer ranging from 0 to
   * one less than the total number of the respective elements. You
   * may thus iterate on them by just looping on integers. The index
   * INVALID_FACE is an invalid element (equal to HALF_EDGE_INVALID_INDEX).
   *
   * @tparam TPoint a type defining the position in space of vertices.
   *
   * @see HalfEdgeDataStructure
   *
   * @note You may access the underlying half-edge data structure
   * through PolygonalSurface::heds method.
   */
  template <typename TPoint>
  class TriangulatedSurface
  {
  public:
    typedef TPoint                             Point;
    typedef TriangulatedSurface<TPoint>        Self;
    typedef HalfEdgeDataStructure::Size        Size;
    typedef HalfEdgeDataStructure::Index       Index;
    typedef HalfEdgeDataStructure::VertexIndex VertexIndex;
    typedef HalfEdgeDataStructure::EdgeIndex   EdgeIndex;
    typedef HalfEdgeDataStructure::FaceIndex   FaceIndex;
    typedef HalfEdgeDataStructure::Triangle    Triangle;
    typedef std::vector<Point>                 PositionsStorage;
    typedef std::vector<Triangle>              TriangleStorage;

    // Required by CUndirectedSimpleLocalGraph
    typedef VertexIndex                        Vertex;
    typedef std::set<Vertex>                   VertexSet;
    template <typename Value> struct           VertexMap {
      typedef typename std::map<Vertex, Value> Type;
    };

    // Required by CUndirectedSimpleGraph
    typedef EdgeIndex                          Edge;
    typedef IntegerSequenceIterator< VertexIndex > ConstIterator;

    // Required for CCombinatorialSurface
    typedef HalfEdgeDataStructure::HalfEdgeIndex Arc;
    typedef HalfEdgeDataStructure::FaceIndex     Face;
    typedef std::vector<Arc>                     ArcRange;
    typedef std::vector<Face>                    FaceRange;
    typedef std::vector<Vertex>                  VertexRange;

    BOOST_STATIC_CONSTANT( Face, INVALID_FACE = HALF_EDGE_INVALID_INDEX );

    /// This structure is used to define efficient maps between
    /// vertices and any data specified by type \a TData. The
    /// triangulated surface provides a default vertex map for vertex
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
      /// @param aSurface the corresponding triangulated surface.
      /// @param s one more than the maximal allowed index (i.e. nb of elements).
      /// @param def_data the default value at initialization.
      IndexedPropertyMap( const Self& aSurface, Size s, Data def_data = Data() )
        : mySurface( &aSurface ),
          myData( Storage( s, def_data ) )
      {}

      /// Creates the IndexedPropertyMap that points to one that exists already.
      ///
      /// @param aSurface the corresponding triangulated surface.
      /// @param aStorage the map to reference in this property map.
      ///
      /// @note This method is used to give to a user the map vertex
      /// -> position that is stored within the triangulated surface.
      IndexedPropertyMap( const Self& aSurface,
			  Storage& aStorage )
        : mySurface( &aSurface ),
          myData( &aStorage, false )
      {}

      /// @return the associated triangulated surface.
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
      /// The associated polygonal surface
      const Self* mySurface;
      /// An owned or aliased pointer to the vector of data.
      OwningOrAliasingPtr<Storage> myData;
    };

    typedef IndexedPropertyMap< Point >          PositionsMap;

  protected:
    typedef HalfEdgeDataStructure::HalfEdge      HalfEdge;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~TriangulatedSurface() {}

    /**
     * Constructor.
     */
    TriangulatedSurface() : isHEDSValid( false ) {}

    /// Clears everything.
    void clear();

    /// Builds the half-edge data structure from the given triangles
    /// and vertices. After that, the surface is valid.
    ///
    /// @return true if everything went allright, false if it was not
    /// possible to build a consistent data structure (e.g., butterfly
    /// neighborhoods).
    bool build();

    /// Adds a new vertex to the surface with data \a vdata.
    /// @param vdata the data associated to this new vertex.
    /// @return the new index given to this vertex.
    VertexIndex addVertex( const Point& vdata );

    /// Adds a new triangle of vertices \a v0, \a v1, \a v2 to the surface.
    /// @return the corresponding index of the triangle.
    FaceIndex addTriangle( VertexIndex v0, VertexIndex v1, VertexIndex v2 );

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

    /// @return the euler characteristic of the triangulated surface
    /// (a famous topological invariant that is the number of vertices
    /// minus the number of edges plus the number of faces).
    long Euler() const { return myHEDS.Euler(); }

    /// @return the property map stored in the surface that defines vertex positions.
    /// @note The returned map only references what is stored in the surface.
    PositionsMap positions()
    {
      return PositionsMap( *this, myPositions );
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
    Point& position( Vertex v );
    /// Const accessor to vertex data.
    /// @param v any vertex.
    /// @return the non-mutable data associated to \a v.
    const Point& position( Vertex v ) const;

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
       Constant-time access to the next arc

       @param a any arc (s,t)
       @return the next arc
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
       triangulated surface since it is a combinatorial 2-manifold.

       @param a any arc on the surface.

       @return the face around the given arc or the InvalidFace if the
       arc was a boundary arc.
    */
    Face faceAroundArc( const Arc & a ) const;

    /**
       Computes the faces incident to a given arc. There is only one
       for triangulated surface since it is a combinatorial
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
       order follows the order of incident arcs (the range size should be 3).
    */
    VertexRange verticesAroundFace( const Face & f ) const;

    /**
       @param f any valid face on the surface. (open or closed ).

       @note By construction, each @e anArc returned by the method on
       a face @a f is such that `this->faceAroundArc(anArc) == f`.

       @return the sequence of arcs that touches this face in their
       natural order (the range size should be 3).
    */
    ArcRange arcsAroundFace( const Face & f ) const;

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
       @return the range of all faces of the triangulated surface,
       i.e. an array containing 0, 1, 2, ..., nbVertices()-1.
    */
    FaceRange allFaces() const;
    /**
       @return the range of all arcs of the triangulated surface,
       i.e. an array containing 0, 1, 2, ..., nbArcs()-1.
    */
    ArcRange allArcs() const;
    /**
       @return the range of all vertices of the triangulated surface,
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
    bool isHEDSValid;
    /// The half-edge data structure that stores the topology of the mesh
    HalfEdgeDataStructure myHEDS;
    /// Stores the information for each Vertex.
    PositionsStorage myPositions;
    /// Stores the triangles.
    TriangleStorage myTriangles;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class TriangulatedSurface


  /**
   * Overloads 'operator<<' for displaying objects of class 'TriangulatedSurface'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'TriangulatedSurface' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint>
  std::ostream&
  operator<< ( std::ostream & out, const TriangulatedSurface<TPoint> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/TriangulatedSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TriangulatedSurface_h

#undef TriangulatedSurface_RECURSES
#endif // else defined(TriangulatedSurface_RECURSES)
