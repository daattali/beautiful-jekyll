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
 * @file SurfelNeighborhood.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/03/18
 *
 * Header file for module SurfelNeighborhood.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SurfelNeighborhood_RECURSES)
#error Recursive header files inclusion detected in SurfelNeighborhood.h
#else // defined(SurfelNeighborhood_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SurfelNeighborhood_RECURSES

#if !defined SurfelNeighborhood_h
/** Prevents repeated inclusion of headers. */
#define SurfelNeighborhood_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/SurfelAdjacency.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SurfelNeighborhood
  /**
   * Description of template class 'SurfelNeighborhood' <p> \brief
   * Aim: This helper class is useful to compute the neighboring
   * surfels of a given surfel, especially over a digital surface or
   * over an object boundary. Two signed surfels are incident if they
   * share a common n-2 cell. This class uses a SurfelAdjacency so as
   * to determine adjacent surfels (either looking for them from
   * interior to exterior or inversely).
   *
   * @tparam TKSpace the type of celluler grid space (for instance, a
   * KhalimskySpaceND).
   *
   * Essentially a backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   */
  template <typename TKSpace>
  class SurfelNeighborhood
  {
    // ----------------------- Types ------------------------------
  public:

    typedef TKSpace KSpace;
    typedef typename KSpace::Point Point;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::SCell SCell;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~SurfelNeighborhood();

    /**
     * Constructor. The object is not valid.
     */
    SurfelNeighborhood();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SurfelNeighborhood ( const SurfelNeighborhood & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SurfelNeighborhood & operator= ( const SurfelNeighborhood & other );

    /**
       Initializes space, adjacency, surfel.
       
       @param space the cellular grid space (only referenced).
       @param adj the chosen surfel adjacency (only referenced).
       @param aSurfel any signed surfel of [space] ((n-1)-cell).
    */
    void init( const KSpace* space, 
         const SurfelAdjacency<KSpace::dimension>* adj,
         const SCell & aSurfel );

    /**
       Sets the neighborhood to the given [surfel].
       @param aSurfel any signed surfel of this space ((n-1)-cell).
    */
    void setSurfel( const SCell & aSurfel );

    /** @return the current surfel. */
    const SCell & surfel() const;

    /** @return the orthogonal direction to the current surfel. */
    Dimension orthDir() const;

   //----------------------- spel services -------------------------
  public:
    /** @return the positively oriented spel touching the surfel 'surfel()'. */
    SCell innerSpel() const;

    /** @return the negatively oriented spel touching the surfel 'surfel()'. */
    SCell outerSpel() const;

    /**
       @param track_dir the direction where to look for the spel.

       @param pos when 'true', looks along the positive direction of
       the tracking axis, otherwise along the negative direction.

       @return the (positively oriented) spel adjacent to
       'innerSpel()' in the direction [track_dir] and orientation
       [pos].
     */
    SCell innerAdjacentSpel( Dimension track_dir, bool pos ) const;

    /**
       @param track_dir the direction where to look for the spel.

       @param pos when 'true', looks along the positive direction of
       the tracking axis, otherwise along the negative direction.

       @return the (negatively oriented) spel adjacent to
       'outerSpel()' in the direction [track_dir] and orientation
       [pos].
     */
    SCell outerAdjacentSpel( Dimension track_dir, bool pos ) const;
 
    //----------------------- follower services -------------------------
  public:
    /**
       @param track_dir the direction where to look for the follower
       (different from 'orthDir()'.
       @param pos when 'true', indicates to look for the follower
       along the positive direction of the tracking axis, otherwise
       along the negative direction.
       @return the first follower of 'surfel()'.
     */ 
    SCell follower1( Dimension track_dir, bool pos ) const;

    /**
       @param track_dir the direction where to look for the follower
       (different from 'orthDir()'.
       @param pos when 'true', indicates to look for the follower
       along the positive direction of the tracking axis, otherwise
       along the negative direction.
       @return the second follower of 'surfel()'.
     */ 
    SCell follower2( Dimension track_dir, bool pos ) const;

    /**
       @param track_dir the direction where to look for the follower
       (different from 'orthDir()'.
       @param pos when 'true', indicates to look for the follower
       along the positive direction of the tracking axis, otherwise
       along the negative direction.
       @return the third follower of 'surfel()'.
     */ 
    SCell follower3( Dimension track_dir, bool pos ) const;


    // ----------------------- Surfel adjacency services --------------------
  public:

    /**
       Go to the next direct or indirect adjacent bel on the boundary of
       some set of unsigned spels [obj].  The boundary may be open (it
       touches the space borders).

       @tparam SpelSet any model of a set of unsigned spels, having
       'find( const Spel & ) : const_iterator'.

       @param adj_surfel (returns) the signed adjacent surfel in direction
       [track_dir] if there is one.
       @param obj any set of unsigned spels (n-cells). 
       @param track_dir the direction where to look for the spel.
       @param pos when 'true' look in positive direction along
       [track_dir] axis, 'false' look in negative direction.

       @return 0 if the move was impossible (no bels in this direction),
       1 if it was the first interior, 2 if it was the second interior,
       3 if it was the third interior.
    */
    template <typename SpelSet>
    unsigned int getAdjacentOnSpelSet( SCell & adj_surfel,
               const SpelSet & obj, 
               Dimension track_dir,
               bool pos ) const;

    /**
       Go to the next direct or indirect adjacent bel on the boundary
       of some digital [obj].  The boundary may be open (it touches
       the space borders).

       @tparam DigitalSet any model of digital set, i.e. a set of
       digital points, having 'find( const Point & ) : const_iterator'.

       @param adj_surfel (returns) the signed adjacent surfel in direction
       [track_dir] if there is one.
       @param obj any set of unsigned spels (n-cells). 
       @param track_dir the direction where to look for the spel.
       @param pos when 'true' look in positive direction along
       [track_dir] axis, 'false' look in negative direction.

       @return 0 if the move was impossible (no bels in this direction),
       1 if it was the first interior, 2 if it was the second interior,
       3 if it was the third interior.
    */
    template <typename DigitalSet>
    unsigned int getAdjacentOnDigitalSet( SCell & adj_surfel,
            const DigitalSet & obj, 
            Dimension track_dir,
            bool pos ) const;

    /**
       Go to the next direct or indirect adjacent bel on the boundary
       of some digital set defined by a PointPredicate [pp].  The
       boundary may be open (it touches the space borders).

       @tparam PointPredicate any model of predicate on point, i.e. a
       boolean functor returning 'true' when the point belongs to the
       object. It is a model of concepts::CPointPredicate. The type
       SurfelNeighborhood::Point should be the same as
       PointPredicate::Point.

       @param adj_surfel (returns) the signed adjacent surfel in direction
       [track_dir] if there is one.

       @param pp any predicate taking a Point and returning 'true'
       whenever the point belongs to the object.

       @param track_dir the direction where to look for the spel.
       @param pos when 'true' look in positive direction along
       [track_dir] axis, 'false' look in negative direction.

       @return 0 if the move was impossible (no bels in this direction),
       1 if it was the first interior, 2 if it was the second interior,
       3 if it was the third interior.
    */
    template <typename PointPredicate>
    unsigned int getAdjacentOnPointPredicate( SCell & adj_surfel,
                const PointPredicate & pp, 
                Dimension track_dir,
                bool pos ) const;

    /**
       Go to the next direct or indirect adjacent bel on some set of
       surfels defined by a SurfelPredicate [sp].  The digital surface may be
       open (for instance, it may touch the space borders or may be open).

       @tparam SurfelPredicate any model of predicate on surfel, i.e. a
       boolean functor returning 'true' when the surfel belongs to the
       digital surface. It is a model of CSurfelPredicate. 

       @param adj_surfel (returns) the signed adjacent surfel in direction
       [track_dir] if there is one.

       @param sp any predicate taking a Surfel and returning 'true'
       whenever the surfel belongs to the surface.

       @param track_dir the direction where to look for the spel.
       @param pos when 'true' look in positive direction along
       [track_dir] axis, 'false' look in negative direction.

       @return 0 if the move was impossible (no bels in this direction),
       1 if it was the first interior, 2 if it was the second interior,
       3 if it was the third interior.
    */
    template <typename SurfelPredicate>
    unsigned int getAdjacentOnSurfelPredicate( SCell & adj_surfel,
                                               const SurfelPredicate & sp, 
                                               Dimension track_dir,
                                               bool pos ) const;

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

    /** A pointer to the digital space. */
    const KSpace* mySpace;
    /** A pointer to the bel adjacency.  */
    const SurfelAdjacency<KSpace::dimension>* mySurfelAdj;
    /** The current surfel. */
    SCell mySurfel;
    /** The orthogonal direction to [mySurfel]. @see mySurfel */
    Dimension myOrthDir;
    /** The direct orientation in the orthogonal direction wrt [mySurfel].
  @see m_surfel */
    bool myOrthDirect;
 
    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class SurfelNeighborhood


  /**
   * Overloads 'operator<<' for displaying objects of class 'SurfelNeighborhood'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SurfelNeighborhood' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const SurfelNeighborhood<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/SurfelNeighborhood.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SurfelNeighborhood_h

#undef SurfelNeighborhood_RECURSES
#endif // else defined(SurfelNeighborhood_RECURSES)
