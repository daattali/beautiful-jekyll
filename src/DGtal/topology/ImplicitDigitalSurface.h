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
 * @file ImplicitDigitalSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/11/18
 *
 * Header file for module ImplicitDigitalSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImplicitDigitalSurface_RECURSES)
#error Recursive header files inclusion detected in ImplicitDigitalSurface.h
#else // defined(ImplicitDigitalSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImplicitDigitalSurface_RECURSES

#if !defined ImplicitDigitalSurface_h
/** Prevents repeated inclusion of headers. */
#define ImplicitDigitalSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/topology/Topology.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ImplicitDigitalSurface
  /**
     Description of template class 'ImplicitDigitalSurface' <p> \brief
     Aim: A model of CDigitalSurfaceContainer which defines the digital
     surface as the boundary of an implicitly define shape. Compute
     once the boundary of the surface with a tracking.
     
     @tparam TKSpace a model of CCellularGridSpaceND: the type chosen
     for the cellular grid space.
     
     @tparam TPointPredicate a model of concepts::CPointPredicate: this functor
     defines the inside of a shape on points where it is true.
   */
  template <typename TKSpace, typename TPointPredicate>
  class ImplicitDigitalSurface
  {
  public:

    /**
       A model of CDigitalSurfaceTracker for ImplicitDigitalSurface.
    */
    class Tracker
    {
    public:
      // -------------------- associated types --------------------
      typedef Tracker Self;
      typedef ImplicitDigitalSurface<TKSpace,TPointPredicate>
      DigitalSurfaceContainer;
      typedef typename TKSpace::SCell Surfel;

      // -------------------- inner types --------------------
      typedef TKSpace KSpace;
      typedef SurfelNeighborhood<KSpace> Neighborhood;

    public:
      /**
	 Constructor from surface container and surfel.
	 @param aSurface the container describing the surface.
	 @param s the surfel on which the tracker is initialized.
      */
      Tracker( ConstAlias<DigitalSurfaceContainer> aSurface, 
               const Surfel & s );

      /**
	 Copy constructor.
	 @param other the object to clone.
      */
      Tracker( const Tracker & other );

      /**
       * Destructor.
       */
      ~Tracker();

      /// @return the surface container that the Tracker is tracking.
      const DigitalSurfaceContainer & surface() const;
      /// @return the current surfel on which the tracker is.
      const Surfel & current() const;
      /// @return the orthogonal direction to the current surfel.
      Dimension orthDir() const;

      /**
	 Moves the tracker to the given valid surfel.
	 @pre 'surface().isInside( s )'
	 @param s the surfel on which the tracker is moved.
      */
      void move( const Surfel & s );
      
      /**
	 Computes the surfel adjacent to 'current()' in the direction
	 [d] along orientation [pos]. 
	 
	 @param s (modified) set to the adjacent surfel in the specified
	 direction @a d and orientation @a pos if it exists. Otherwise
	 unchanged (method returns 0 in this case).
	 
	 @param d any direction different from 'orthDir()'.
	 
	 @param pos when 'true' look in positive direction along
	 [track_dir] axis, 'false' look in negative direction.
	 
	 @return the move code (n=0-3). When 0: no adjacent surfel,
	 otherwise 1-3: adjacent surfel is n-th follower.
      */
      uint8_t adjacent( Surfel & s, Dimension d, bool pos ) const;
      
    private:
      /// a reference to the digital surface container on which is the
      /// tracker.
      const DigitalSurfaceContainer & mySurface;
      /// the current surfel neighborhood, the object that holds the
      /// necessary information for determining neighbors.
      Neighborhood myNeighborhood;

    };

    // ----------------------- associated types ------------------------------
  public:
    typedef ImplicitDigitalSurface<TKSpace,TPointPredicate> Self;
    /// Model of cellular grid space.
    typedef TKSpace KSpace;
    /// Type for surfels.
    typedef typename KSpace::SCell Surfel;
    /// Type for sizes (unsigned integral type).
    typedef typename KSpace::Size Size;
    // Model of concepts::CPointPredicate
    typedef TPointPredicate PointPredicate;
    
    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND< KSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate< PointPredicate > ));

    // -------------------- specific types ------------------------------
    typedef typename std::vector<Surfel> SurfelStorage;
    typedef typename SurfelStorage::const_iterator SurfelConstIterator;
    typedef typename KSpace::Space Space;
    typedef typename KSpace::Point Point;
    typedef Tracker DigitalSurfaceTracker;

    // ----------------------- other types ------------------------------
  public:
    typedef SurfelAdjacency<KSpace::dimension> Adjacency;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::SCell SCell;
    typedef typename KSpace::CellSet CellSet;
    typedef typename KSpace::SCellSet SCellSet;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~ImplicitDigitalSurface();

    /**
       Copy constructor.
       @param other the object to clone.

       NB: O(N) computational complexity operation, where N is the
       number of surfels of the surface. This is due to the fact that
       the surface is stored explicitly.
     */
    ImplicitDigitalSurface ( const ImplicitDigitalSurface & other );

    /**
       Constructor from digital set.
       @param aKSpace a cellular grid space (referenced).
       @param aPP a point predicate defining implicitly the shape (referenced).
       @param adj the surfel adjacency (for instance Adjacency( true )
       is interior to exterior adjacency ).

       @param s any surfel of \a aKSpace such that \a aPP is true in
       the interior and false in the exterior.

       @param closed when 'true', the surface is known to be closed,
       hence faster extraction can be performed, default is 'false'.

       NB: O(N) computational complexity operation, where N is the
       number of surfels of the surface. This is due to the fact that,
       at construction, the surface is extracted and stored.

       @see computeSurfels
      */
    ImplicitDigitalSurface( ConstAlias<KSpace> aKSpace,
                            ConstAlias<PointPredicate> aPP,
                            const Adjacency & adj,
                            const Surfel & s,
                            bool closed = false );

    /// accessor to surfel adjacency.
    const Adjacency & surfelAdjacency() const;
    /// mutator to surfel adjacency.
    Adjacency & surfelAdjacency();
    /// accessor to point predicate.
    const PointPredicate & pointPredicate() const;

    // --------- CDigitalSurfaceContainer realization -------------------------
  public:

    /// @return the cellular space in which lives the surface.
    const KSpace & space() const;
    /**
       @param s any surfel of the space.
       @return 'true' if @a s belongs to this digital surface.
    */
    bool isInside( const Surfel & s ) const;

    /// @return an iterator pointing on the first surfel of the digital surface
    /// (unspecified order).
    SurfelConstIterator begin() const;

    /// @return an iterator after the last surfel of the digital surface
    /// (unspecified order).
    SurfelConstIterator end() const;

    /// @return the number of surfels of this digital surface. NB:
    /// O(1)
    Size nbSurfels() const;

    /// @return 'true' is the surface has no surfels, 'false'
    /// otherwise. NB: O(1) operation.
    bool empty() const;

    /**
       @param s any surfel of the space.
       @pre 'isInside( s )'
       @return a dyn. alloc. pointer on a tracker positionned at @a s.
    */
    DigitalSurfaceTracker* newTracker( const Surfel & s ) const;

     /**
        @return the connectedness of this surface. Either CONNECTED,
        DISCONNECTED, or UNKNOWN.
       */
    Connectedness connectedness() const;

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
    /// a reference to the cellular space.
    const KSpace & myKSpace;
    /// a reference to the point predicate defining the shape.
    const PointPredicate & myPointPredicate;
    /// the surfel adjacency used to determine neighbors. 
    Adjacency mySurfelAdjacency;
    /// a vector storing all the surfels of the boundary.
    SurfelStorage mySurfels;

    // ------------------------- Hidden services ------------------------------
  protected:
    /**
       Recomputes the set of boundary surfels from the point predicate
       and some initial surfel.

       @param p any surfel of the surface

       @param closed when 'true', the surface is known to be closed,
       hence faster extraction can be performed.

    */
    void computeSurfels( const Surfel & p,
                         bool closed );


  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    ImplicitDigitalSurface & operator= ( const ImplicitDigitalSurface & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ImplicitDigitalSurface


  /**
     Overloads 'operator<<' for displaying objects of class 'ImplicitDigitalSurface'.
     @param out the output stream where the object is written.
     @param object the object of class 'ImplicitDigitalSurface' to write.
     @return the output stream after the writing.

     @tparam TKSpace a model of CCellularGridSpaceND: the type chosen
     for the cellular grid space.
     
     @tparam TPointPredicate a model of CDigitalSet: the type chosen for
     the set of digital points.
   */
  template <typename TKSpace, typename TPointPredicate>
  std::ostream&
  operator<< ( std::ostream & out, 
	       const ImplicitDigitalSurface<TKSpace, TPointPredicate> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/ImplicitDigitalSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImplicitDigitalSurface_h

#undef ImplicitDigitalSurface_RECURSES
#endif // else defined(ImplicitDigitalSurface_RECURSES)
