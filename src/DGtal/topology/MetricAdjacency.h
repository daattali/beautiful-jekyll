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
 * @file MetricAdjacency.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/04
 *
 * Header file for module MetricAdjacency.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MetricAdjacency_RECURSES)
#error Recursive header files inclusion detected in MetricAdjacency.h
#else // defined(MetricAdjacency_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MetricAdjacency_RECURSES

#if !defined MetricAdjacency_h
/** Prevents repeated inclusion of headers. */
#define MetricAdjacency_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/BasicPointPredicates.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class MetricAdjacency
  /**
   * Description of template class 'MetricAdjacency' <p> \brief Aim:
   * Describes digital adjacencies in digital spaces that are defined
   * with the 1-norm and the infinity-norm.
   *
   * It induces the classical 4 and 8 adjacencies in 2D, the 6, 18 and
   * 26 adjacencies in 3D, and the \f$ \omega \f$ and \f$ \alpha \f$
   * adjacencies in nD.
   *
   * \b Model of concepts::CAdjacency.
   *
   * @tparam TSpace any digital space (see concept CSpace).
   *
   * @tparam maxNorm1 defines which points are adjacent. More
   * precisely, two points are adjacent iff their norm-infinity is
   * less or equal than 1 and if their norm-1 is less or equal than
   * maxNorm1.
   *
   * @see testAdjacency.cpp
   */
  template <typename TSpace, Dimension maxNorm1, 
	    Dimension dimension = TSpace::dimension >
  class MetricAdjacency
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    // ----------------------- public types ------------------------------
  public:
    // Required by CAdjacency
    typedef TSpace Space;
    typedef typename Space::Point Point;
    typedef MetricAdjacency<Space, maxNorm1, dimension> Adjacency;

    // Others
    typedef typename Space::Vector Vector;
    
    // Required by CUndirectedSimpleLocalGraph
    typedef Point Vertex;
    typedef typename Space::Size Size;
    typedef std::set<Vertex> VertexSet; // DigitalSet doesn't fit since MetricAdjacency has no domain
    template <typename Value> struct VertexMap {
      typedef typename std::map<Vertex, Value> Type;
    };

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor. Does nothing. Due to the symmetry and translation
     * invariance of this digital topology, all methods are static.
     */
    MetricAdjacency();

    /**
     * Destructor.
     */
    ~MetricAdjacency();

    // ----------------------- Adjacency services -----------------------------
  public:

    /**
     * @param p1 any point in this space.
     * @param p2 any point in this space.
     *
     * @return 'true' iff p1 is adjacent to p2 according to this
     * adjacency relation.
     */
    static
    bool isAdjacentTo( const Point & p1, const Point & p2 ); 

    /**
     * @param p1 any point in this space.
     * @param p2 any point in this space.
     *
     * @return 'true' iff p1 is adjacent to p2 according to this
     * adjacency relation and p1 != p2.
     */
    static
    bool isProperlyAdjacentTo( const Point & p1, const Point & p2 ); 

    
    // ----------------------- Local graph services --------------------------
    
    /**
     * @return maximum number of neighbors for this adjacency
     */
    static
    Size bestCapacity();
    
    /**
     * @param v any vertex
     * 
     * @return the number of neighbors of this vertex
     */
    static
    Size degree( const Vertex & v );
    
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
    static
    void  
    writeNeighbors( OutputIterator &it ,
		    const Vertex & v );
    
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
    static
    void
    writeNeighbors( OutputIterator &it ,
		    const Vertex & v,
		    const VertexPredicate & pred);
    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    static
    void selfDisplay ( std::ostream & out );

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    static
    bool isValid();

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    
    // ------------------------- Hidden services ------------------------------
  protected:
    static Size computeCapacity();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    MetricAdjacency ( const MetricAdjacency & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    MetricAdjacency & operator= ( const MetricAdjacency & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class MetricAdjacency

  /**
   * Overloads 'operator<<' for displaying objects of class 'MetricAdjacency'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'MetricAdjacency' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, Dimension maxNorm1>
  std::ostream&
  operator<< ( std::ostream & out, 
         const MetricAdjacency< TSpace,maxNorm1,
         TSpace::dimension > & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/MetricAdjacency.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MetricAdjacency_h

#undef MetricAdjacency_RECURSES
#endif // else defined(MetricAdjacency_RECURSES)
