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
 * @file SurfelAdjacency.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/03/18
 *
 * Header file for module SurfelAdjacency.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SurfelAdjacency_RECURSES)
#error Recursive header files inclusion detected in SurfelAdjacency.h
#else // defined(SurfelAdjacency_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SurfelAdjacency_RECURSES

#if !defined SurfelAdjacency_h
/** Prevents repeated inclusion of headers. */
#define SurfelAdjacency_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <boost/array.hpp>

#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class SurfelAdjacency
  /**
     Description of class 'SurfelAdjacency' <p> \brief Aim: Represent
     adjacencies between surfel elements, telling if it follows an
     interior to exterior ordering or exterior to interior ordering. It
     allows tracking of boundaries and of surfaces.
     
     @tparam dim the number of dimension of the space.

     NB: backported from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
  */
  template <Dimension dim>
  class SurfelAdjacency
  {
    // ----------------------- Standard services ------------------------------
  public:
  
    /**
     * Destructor.
     */
    ~SurfelAdjacency();
  
    /**
       Constructor.
     
       @param int2ext when 'true', the surfel adjacency is interior
       to exterior for any coordinate pair, when 'false', it is
       exterior to interior for any one.
     
       NB: @see setAdjacency to modify a specific pair or coordinates
    */
    SurfelAdjacency( bool int2ext );
  
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SurfelAdjacency ( const SurfelAdjacency & other );
  
    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SurfelAdjacency & operator= ( const SurfelAdjacency & other );
  
    /**
       Set a coordinate pair as interior to exterior or exterior to
       interior in the surfel adjacency.

       @param i first coordinate.
       @param j second coordinate (j != i).
       @param int2ext when 'true', the surfel adjacency is interior to
       exterior for the coordinate pair '(i,j)', when 'false', it is
       exterior to interior.
    */
    void setAdjacency( Dimension i, Dimension j, bool int2ext );

    /**
       Returns whether a coordinate pair is interior (true) or exterior (false) 
       in the bel adjacency.

       @param i first coordinate.
       @param j second coordinate ('j != i').

       @return 'true' if the surfel adjacency is interior to exterior
       for the coordinate pair '(i,j)', 'false' when it is exterior to
       interior.
    */
    bool getAdjacency( Dimension i, Dimension j ) const;

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

    // ------------------------- Private Datas --------------------------------
  private:

    /**
       Memorizes if the surfel adjacency is interior to exterior (true)
       or exterior to interior (false) for any pair (i,j).  The index of
       the pair (i,j) is 'i * m_ks.dim() + j'.
    */
    boost::array<bool, dim*dim> myInt2Ext;

    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class SurfelAdjacency


  /**
   * Overloads 'operator<<' for displaying objects of class 'SurfelAdjacency'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SurfelAdjacency' to write.
   * @return the output stream after the writing.
   */
  template <Dimension dim>
  std::ostream&
  operator<< ( std::ostream & out, const SurfelAdjacency<dim> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/SurfelAdjacency.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SurfelAdjacency_h

#undef SurfelAdjacency_RECURSES
#endif // else defined(SurfelAdjacency_RECURSES)
