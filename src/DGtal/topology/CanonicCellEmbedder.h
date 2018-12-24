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
 * @file CanonicCellEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/28
 *
 * Header file for module CanonicCellEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CanonicCellEmbedder_RECURSES)
#error Recursive header files inclusion detected in CanonicCellEmbedder.h
#else // defined(CanonicCellEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CanonicCellEmbedder_RECURSES

#if !defined CanonicCellEmbedder_h
/** Prevents repeated inclusion of headers. */
#define CanonicCellEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/topology/CPreCellularGridSpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class CanonicCellEmbedder
/**
   Description of class 'CanonicCellEmbedder' <p>

   \brief Aim: A trivial embedder for signed and unsigned cell, which
   corresponds to the canonic injection of cell centroids into Rn.

   Model of CCellEmbedder.

   @tparam TKSpace the type of cellular grid space where the embedder works, a model of CPreCellularGridSpaceND.
 */
  template <typename TKSpace>
  struct CanonicCellEmbedder
  {
  public:
    typedef CanonicCellEmbedder<TKSpace> Self;
    BOOST_CONCEPT_ASSERT(( concepts::CPreCellularGridSpaceND<TKSpace> ));

    typedef TKSpace KSpace;
    typedef typename KSpace::Cell Cell;
    typedef typename KSpace::Space Space;
    typedef typename Space::RealPoint RealPoint;
    typedef Cell Argument;
    typedef RealPoint Value;

    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;

    // ----------------------- Standard services ------------------------------
  public:
    /**
       Destructor. Nothing special.
    */
    ~CanonicCellEmbedder();

    /**
       Default constructor. The object is not valid.
    */
    CanonicCellEmbedder();

    /**
       Constructor from space.
    */
    CanonicCellEmbedder( ConstAlias<KSpace> aKSpace );

    /**
       Copy constructor.
       @param other the object to clone.
    */
    CanonicCellEmbedder( const Self & other );

    /**
       Assignment.
       @param other the object to clone.
       @return a reference to 'this'.
    */
    Self & operator=( const Self & other );

    /**
       @return the cellular grid space.
    */
    const KSpace & space() const;

    /**
       Map a unsigned cell to its corresponding point in the Euclidean
       space.

       @param cell any unsigned cell in the digital space.
       @return its canonical embedding in the Euclidean space.
    */
    RealPoint embed( const Cell & cell ) const;

    /**
       Map a unsigned cell to its corresponding point in the Euclidean
       space.

       @param cell any unsigned cell in the digital space.
       @return its canonical embedding in the Euclidean space.
    */
    RealPoint operator()( const Cell & cell ) const;

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
    const KSpace* myKSpace;

    // ------------------------- Private Datas --------------------------------
private:

    // ------------------------- Hidden services ------------------------------
protected:


    // ------------------------- Internals ------------------------------------
private:

}; // end of class CanonicCellEmbedder


/**
 * Overloads 'operator<<' for displaying objects of class 'CanonicCellEmbedder'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'CanonicCellEmbedder' to write.
 * @return the output stream after the writing.
 */
  template <typename TKSpace>
  std::ostream&
  operator<< ( std::ostream & out, const CanonicCellEmbedder<TKSpace> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/CanonicCellEmbedder.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CanonicCellEmbedder_h

#undef CanonicCellEmbedder_RECURSES
#endif // else defined(CanonicCellEmbedder_RECURSES)
