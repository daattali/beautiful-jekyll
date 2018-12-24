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
 * @file CanonicDigitalSurfaceEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/28
 *
 * Header file for module CanonicDigitalSurfaceEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CanonicDigitalSurfaceEmbedder_RECURSES)
#error Recursive header files inclusion detected in CanonicDigitalSurfaceEmbedder.h
#else // defined(CanonicDigitalSurfaceEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CanonicDigitalSurfaceEmbedder_RECURSES

#if !defined CanonicDigitalSurfaceEmbedder_h
/** Prevents repeated inclusion of headers. */
#define CanonicDigitalSurfaceEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class CanonicDigitalSurfaceEmbedder
/**
   Description of class 'CanonicDigitalSurfaceEmbedder' <p>

   \brief Aim: A trivial embedder for digital surfaces, which
   corresponds to the canonic injection of cell centroids into Rn.

   Model of CCanonicDigitalSurfaceEmbedder (and thus of CSCellEmbedder).

   @tparam TDigitalSurface the type of digital surface where the embedder works.
 */
  template <typename TDigitalSurface>
  struct CanonicDigitalSurfaceEmbedder
  {
  public:
    typedef CanonicDigitalSurfaceEmbedder<TDigitalSurface> Self;

    typedef TDigitalSurface Surface;
    typedef typename Surface::KSpace KSpace;
    BOOST_CONCEPT_ASSERT(( concepts::CCellularGridSpaceND<KSpace> ));
    typedef typename KSpace::SCell SCell;
    typedef typename KSpace::Space Space;
    typedef typename Space::RealPoint RealPoint;
    typedef SCell Argument;
    typedef RealPoint Value;

    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;

    // ----------------------- Standard services ------------------------------
  public:
    /**
       Destructor. Nothing special.
    */
    ~CanonicDigitalSurfaceEmbedder();

    /**
       Default constructor. The object is not valid.
    */
    CanonicDigitalSurfaceEmbedder();

    /**
       Constructor from surface.
    */
    CanonicDigitalSurfaceEmbedder( ConstAlias<Surface> aSurface );

    /**
       Copy constructor.
       @param other the object to clone.
    */
    CanonicDigitalSurfaceEmbedder( const Self & other );

    /**
       Assignment.
       @param other the object to clone.
       @return a reference to 'this'.
    */
    Self & operator=( const Self & other );

    /**
       @return the Khalimsky space.
    */
    const KSpace & space() const
    {
      return mySurface->container().space();
    }


    /**
       @return the digital surface.
    */
    const Surface & surface() const;


    /**
       Map a signed cell to its corresponding point in the Euclidean
       space.

       @param cell any signed cell in the digital space.
       @return its canconical embedding in the Euclidean space.
    */
    RealPoint embed( const SCell & cell ) const;

    /**
       Map a signed cell to its corresponding point in the Euclidean
       space.

       @param cell any signed cell in the digital space.
       @return its canconical embedding in the Euclidean space.
    */
    RealPoint operator()( const SCell & cell ) const;

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
    const Surface* mySurface;

    // ------------------------- Private Datas --------------------------------
private:

    // ------------------------- Hidden services ------------------------------
protected:


    // ------------------------- Internals ------------------------------------
private:

}; // end of class CanonicDigitalSurfaceEmbedder


/**
 * Overloads 'operator<<' for displaying objects of class 'CanonicDigitalSurfaceEmbedder'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'CanonicDigitalSurfaceEmbedder' to write.
 * @return the output stream after the writing.
 */
  template <typename TDigitalSurface>
  std::ostream&
  operator<< ( std::ostream & out, const CanonicDigitalSurfaceEmbedder<TDigitalSurface> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/CanonicDigitalSurfaceEmbedder.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CanonicDigitalSurfaceEmbedder_h

#undef CanonicDigitalSurfaceEmbedder_RECURSES
#endif // else defined(CanonicDigitalSurfaceEmbedder_RECURSES)
