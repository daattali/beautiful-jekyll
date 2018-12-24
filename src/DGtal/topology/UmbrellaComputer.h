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
 * @file UmbrellaComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/10/28
 *
 * Header file for module UmbrellaComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(UmbrellaComputer_RECURSES)
#error Recursive header files inclusion detected in UmbrellaComputer.h
#else // defined(UmbrellaComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define UmbrellaComputer_RECURSES

#if !defined UmbrellaComputer_h
/** Prevents repeated inclusion of headers. */
#define UmbrellaComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/CDigitalSurfaceTracker.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class UmbrellaComputer
  /**
     Description of class 'DigitalSurfaceUmbrellaComputer' <p> 

     \brief Aim: Useful for computing umbrellas on 'DigitalSurface's,
     ie set of n-1 cells around a n-3 cell.
    
     The current surfel (n-1 cell), or \a face, is denoted by \a s.
     The n-3 cell is called the \a pivot and denoted by \a +p. It is
     always a positive cell. There is also a current n-2 cell, called
     the \a separator and denoted by \a t, which is in the boundary of
     \a s and whose boundary contains \a +p.
    
     Two directions specifies the separator and the pivot, the \a
     track direction \a j and the separator direction \a k. Moreover
     an orientation \f$ \epsilon=\pm 1 \f$ specifies one which side is
     the separator wrt the face. We have \f$ t = \Delta^{\epsilon}_k
     s, +p = \Delta^{\mu}_{j} t, \f$ where \f$ \mu \f$ is the direct
     orientation of \a t along \a j.
    
     Turning around the pivot means moving the face and the separator
     once (in the track direction), such that the pivot is the same
     (ie \a +p), the track and separator directions being
     updated. Repeating this process a sufficient number of times
     brings the umbrella back in its original position, except in the
     case when the DigitalSurface has a boundary touching the pivot.
    
     Uses delegation with DigitalSurfaceTracker.

     Essentially a backport from
     [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).

     @tparam TDigitalSurfaceTracker the type of the domain in which shapes are created.
   */
  template <typename TDigitalSurfaceTracker>
  class UmbrellaComputer
  {
    // Concept checks
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceTracker<TDigitalSurfaceTracker> ) );

    // ----------------------- public types ------------------------------
  public:
    typedef TDigitalSurfaceTracker DigitalSurfaceTracker;
    typedef typename DigitalSurfaceTracker::DigitalSurfaceContainer DigitalSurfaceContainer;
    typedef typename DigitalSurfaceContainer::KSpace KSpace;
    typedef typename DigitalSurfaceContainer::Surfel Surfel;
    typedef typename DigitalSurfaceContainer::Size Size;
    typedef typename KSpace::SCell SCell;

    /**
       Stores (the main part of) the state when visiting an umbrella.
       @see UmbrellaComputer
    */
    struct State 
    {
      /// Current surfel
      Surfel surfel;
      /// Direction to find separator, k in sDirs(surfel).
      Dimension k;
      /// Orientation to find separator (true = positively along k-axis)
      bool epsilon;
      /// Track direction (j != k), j in sDirs(surfel).
      Dimension j;
      inline State(){}
      inline State( const Surfel & _surfel, 
                    Dimension _k, bool _epsilon, Dimension _j )
        : surfel( _surfel ), k( _k ), epsilon( _epsilon ), j( _j )
      {}
      inline bool operator==( const State & other ) const
      {
	return ( surfel == other.surfel ) 
	  && ( k == other.k ) 
	  && ( epsilon == other.epsilon )
	  && ( j == other.j );
      }
      inline bool operator<( const State & other ) const
      {
	return ( surfel < other.surfel ) 
	  || ( ( surfel == other.surfel ) 
	       && ( ( k < other.k ) 
		    || ( ( k == other.k ) 
			 && ( ( epsilon < other.epsilon )
			      || ( ( epsilon == other.epsilon)
				   && ( j < other.j ) ) ) ) ) );
      }
    };

    // ----------------------- Standard services ------------------------------
  public:

    /// Destructor.
    ~UmbrellaComputer();

    /// Constructor. The object is not valid.
    UmbrellaComputer();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    UmbrellaComputer( const UmbrellaComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    UmbrellaComputer & 
    operator=( const UmbrellaComputer & other );
   
    /**
       Initializes the umbrella with a 'DigitalSurfaceTracker'. Links
       the umbrella computer with a concrete surface and a surfel on
       it. Tells also where is the positive pivot to turn around.
      
       @param tracker a tracker on a digital surface with a valid
       'current()' surfel. (cloned). Specifies the initial surfel.
     
       @param k the separator direction different from [j] and the
       orthogonal direction to the surfel.
      
       @param epsilon the orientation where to find the separator
       pointing at the pivot.
      
       @param j the track direction where the next surfel of the umbrella is.
     */
    void init( const DigitalSurfaceTracker & tracker,
	       Dimension k, bool epsilon, Dimension j );

    /**
     * Puts the umbrella in the state [state]. The umbrella must have
     * been initialized with a 'DigitalSurfaceTracker' before and the
     * state must be consistent with the tracker. In particular, the
     * face of the state must lie on the same digital surface.
     *
     * @param aState a state describing the face, the separator and the pivot.
     */
    void setState( const State & aState );

    /**
     * Returns the state of the umbrella in the referenced object [state]. 
     *
     * @param aState (returns) the current umbrella state describing
     * the face, the separator and the pivot.
     */
    void getState( State & aState ) const;

    /// Accessor to current state.
    const State & state() const;

    /// Accessor to the digital space.
    const KSpace & space() const;
 
    // ----------------------- Accessor services ------------------------------
  public:

    /// @return the current surfel at which the umbrella is pointing.
    const Surfel & surfel() const;

    /// @return the separator n-2 cell.
    SCell separator() const;

    /// @return the pivot n-3 cell (always positively orientated).
    SCell pivot() const;
    
    /// @return the orthogonal direction to the current surfel.
    Dimension orthDir() const;

    /// @return the track direction (j).
    Dimension trackDir() const;

    /// @return the track orientation (mu).
    bool trackOrientation() const;

    /// @return the separator direction.
    Dimension separatorDir() const;

    /// @return the separator orientation.
    bool separatorOrientation() const;
    
    // ----------------------- Pivoting services ------------------------------
  public:

    /**
       Turns around the current pivot (positive turn).
     
       @return 0 if the move was impossible (nothing is updated)
       otherwise returns the move code of the face.
     */
    unsigned int next();
    
    /**
       Turns around the current pivot (negative turn).
       
       @return 0 if the move was impossible (nothing is updated)
       otherwise returns the move code of the face.
     */
    unsigned int previous();

    /**
       Go the adjacent umbrella, ie the one which shares the same
       faces around the separator but whose pivot is symmetric around
       the separator.
       
       @return 'true' if their was an adjacent umbrella, 'false' otherwise.
       (the umbrella is in the same state as before the call).
     */
    bool adjacent();
    


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

    /// Tracker used to move on the digital surface.
    DigitalSurfaceTracker* myTracker;
    /// Current state for the umbrella.
    State myState;

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class UmbrellaComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'UmbrellaComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'UmbrellaComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TDigitalSurfaceTracker>
  std::ostream&
  operator<< ( std::ostream & out, const UmbrellaComputer<TDigitalSurfaceTracker> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/UmbrellaComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined UmbrellaComputer_h

#undef UmbrellaComputer_RECURSES
#endif // else defined(UmbrellaComputer_RECURSES)
