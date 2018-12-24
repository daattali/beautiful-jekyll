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
 * @file RegularPointEmbedder.h
 * @brief Computes the Gauss digitization of some Euclidean shape.
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/06/29
 *
 * Header file for module RegularPointEmbedder.cpp
 *
 * This file is part of the DGtal library.
 *
 */

#if defined(RegularPointEmbedder_RECURSES)
#error Recursive header files inclusion detected in RegularPointEmbedder.h
#else // defined(RegularPointEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RegularPointEmbedder_RECURSES

#if !defined RegularPointEmbedder_h
/** Prevents repeated inclusion of headers. */
#define RegularPointEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class RegularPointEmbedder
  /**
     Description of template class 'RegularPointEmbedder' <p> \brief
     Aim: A simple point embedder where grid steps are given for each
     axis. Note that the real point (0,...,0) is mapped onto the
     digital point (0,...,0).
     
     RegularPointEmbedder is a model of CPointEmbedder.

     @tparam TSpace the type of digital Space where the digitized
     object lies. A model of CSpace.
   */
  template <typename TSpace>
  class RegularPointEmbedder
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));

    // ----------------------- Standard services ------------------------------
  public:
    typedef TSpace Space;
    typedef typename Space::Point Point;
    typedef typename Space::RealPoint RealPoint;
    typedef Point Argument;
    typedef RealPoint Value;

    typedef typename Space::Integer Integer;
    typedef typename Space::RealVector RealVector;

    /**
     * Destructor.
     */
    ~RegularPointEmbedder();

    /**
     * Constructor. The object is not valid.
     */
    RegularPointEmbedder();

    /**
     * Assignment. Required by concepts::CPointPredicate.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    RegularPointEmbedder & operator= ( const RegularPointEmbedder & other );

    /**
       Initializes the embedder. The real value [gridStep] specifies
       the same grid step in every direction.

       @param gridStep the grid step (distance between two embedded
       adjacent digital points) identical in every direction.
    */
    void init( typename RealVector::Component gridStep );

    /**
       Initializes the embedder. The real vector [gridSteps] specifies
       the grid steps in each direction.

       @param gridSteps the grid steps in each direction.
    */
    void init( const RealVector & gridSteps );

    /**
       @param p any point in the Euclidean space.
       @return the digital point floor( p / gridSteps ).
    */
    Point floor( const RealPoint & p ) const;

    /**
       @param p any point in the Euclidean space.
       @return the digital point ceil( p / gridSteps ).
    */
    Point ceil( const RealPoint & p ) const;

    /**
       @param p any point in the Euclidean space.

       @return the digital point round( p / gridSteps ), i.e. the
       "closest" digital point.
    */
    Point round( const RealPoint & p ) const;

    /**
     * Map a digital point to its corresponding point in the Eucldiean
     * space.
     *
     *   @param p any digital point in the digital space.
     *   @return its centroid embedding in the Euclidean space.
     */
    RealPoint embed( const Point & p ) const;

    /**
     * Map a digital point to its corresponding point in the Eucldiean
     * space.
     *
     *   @param p any digital point in the digital space.
     *   @return its centroid embedding in the Euclidean space.
     */
    RealPoint operator()( const Point & p ) const;

    
    /**
       @return the grid steps in each direction.
    */
    RealVector gridSteps() const;


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
    /// The grid steps.
    RealVector myGridSteps;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  private:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class RegularPointEmbedder


  /**
   * Overloads 'operator<<' for displaying objects of class 'RegularPointEmbedder'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'RegularPointEmbedder' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace>
  std::ostream&
  operator<< ( std::ostream & out, 
         const RegularPointEmbedder<TSpace> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/RegularPointEmbedder.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined RegularPointEmbedder_h

#undef RegularPointEmbedder_RECURSES
#endif // else defined(RegularPointEmbedder_RECURSES)
