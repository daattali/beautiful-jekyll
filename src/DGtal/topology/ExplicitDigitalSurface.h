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
 * @file ExplicitDigitalSurface.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/11/27
 *
 * Header file for module ExplicitDigitalSurface.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ExplicitDigitalSurface_RECURSES)
#error Recursive header files inclusion detected in ExplicitDigitalSurface.h
#else // defined(ExplicitDigitalSurface_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ExplicitDigitalSurface_RECURSES

#if !defined ExplicitDigitalSurface_h
/** Prevents repeated inclusion of headers. */
#define ExplicitDigitalSurface_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CSurfelPredicate.h"
#include "DGtal/topology/Topology.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/SurfelNeighborhood.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ExplicitDigitalSurface
  /**
     Description of template class 'ExplicitDigitalSurface' <p> \brief
     Aim: A model of CDigitalSurfaceContainer which defines the digital
     surface as connected surfels. The shape is determined by a
     predicate telling whether a given surfel belongs or not to the
     shape boundary. Compute once the boundary of the surface with a
     tracking.

     Note that in the 2D case, this object corresponds to a digital
     contour made of linels, ordered as a direct orientation
     sequence. If the contour is open, then begin() returns one
     extremity while end() is the surfel past the last extremity. If
     the contour is closed, then begin() is the surfel given at the
     instantiation of the object.
     
     @tparam TKSpace a model of CCellularGridSpaceND: the type chosen
     for the cellular grid space.
     
     @tparam TSurfelPredicate a model of CSurfelPredicate: this
     functor defines the digital surface as a characteristic function
     returning true iff the surfel belongs to it.
   */
  template <typename TKSpace, typename TSurfelPredicate>
  class ExplicitDigitalSurface
  {
  public:

    /**
       A model of CDigitalSurfaceTracker for ExplicitDigitalSurface.
    */
    class Tracker
    {
    public:
      // -------------------- associated types --------------------
      typedef Tracker Self;
      typedef ExplicitDigitalSurface<TKSpace,TSurfelPredicate>
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
    typedef ExplicitDigitalSurface<TKSpace,TSurfelPredicate> Self;
    /// Model of cellular grid space.
    typedef TKSpace KSpace;
    /// Type for surfels.
    typedef typename KSpace::SCell Surfel;
    /// Type for sizes (unsigned integral type).
    typedef typename KSpace::Size Size;
    // Model of CSurfelPredicate
    typedef TSurfelPredicate SurfelPredicate;

    // BOOST_CONCEPT_ASSERT(( CCellularGridSpaceND< KSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CSurfelPredicate< SurfelPredicate > ));

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
    ~ExplicitDigitalSurface();

    /**
       Copy constructor.
       @param other the object to clone.

       NB: O(N) computational complexity operation, where N is the
       number of surfels of the surface. This is due to the fact that
       the surface is stored explicitly.
     */
    ExplicitDigitalSurface ( const ExplicitDigitalSurface & other );

    /**
       Constructor from digital set.
       @param aKSpace a cellular grid space (referenced).
       @param aSP a surfel predicate defining the shape (referenced).
       @param adj the surfel adjacency (for instance Adjacency( true )
       is interior to exterior adjacency ).

       @param s any surfel of \a aKSpace such that \a aSP is true in
       the interior and false in the exterior.

       @param closed when 'true', the surface is known to be closed,
       hence faster extraction can be performed, default is 'false'.

       NB: O(N) computational complexity operation, where N is the
       number of surfels of the surface. This is due to the fact that,
       at construction, the surface is extracted and stored.

       @see computeSurfels
      */
    ExplicitDigitalSurface( ConstAlias<KSpace> aKSpace,
                            const SurfelPredicate & aSP,
                            const Adjacency & adj,
                            const Surfel & s,
                            bool closed = false );

    /// accessor to surfel adjacency.
    const Adjacency & surfelAdjacency() const;
    /// mutator to surfel adjacency.
    Adjacency & surfelAdjacency();
    /// accessor to point predicate.
    const SurfelPredicate & surfelPredicate() const;

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
        @return the connectedness of this surface. By construction CONNECTED.
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
    /// a reference to the surfel predicate defining the shape.
    const SurfelPredicate & mySurfelPredicate;
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
    ExplicitDigitalSurface & operator= ( const ExplicitDigitalSurface & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ExplicitDigitalSurface


  /**
     Overloads 'operator<<' for displaying objects of class 'ExplicitDigitalSurface'.
     @param out the output stream where the object is written.
     @param object the object of class 'ExplicitDigitalSurface' to write.
     @return the output stream after the writing.

     @tparam TKSpace a model of CCellularGridSpaceND: the type chosen
     for the cellular grid space.
     
     @tparam TSurfelPredicate a model of CDigitalSet: the type chosen for
     the set of digital points.
   */
  template <typename TKSpace, typename TSurfelPredicate>
  std::ostream&
  operator<< ( std::ostream & out, 
	       const ExplicitDigitalSurface<TKSpace, TSurfelPredicate> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/ExplicitDigitalSurface.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ExplicitDigitalSurface_h

#undef ExplicitDigitalSurface_RECURSES
#endif // else defined(ExplicitDigitalSurface_RECURSES)
