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
 * @file CanonicEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/28
 *
 * Header file for module CanonicEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CanonicEmbedder_RECURSES)
#error Recursive header files inclusion detected in CanonicEmbedder.h
#else // defined(CanonicEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CanonicEmbedder_RECURSES

#if !defined CanonicEmbedder_h
/** Prevents repeated inclusion of headers. */
#define CanonicEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class CanonicEmbedder
/**
   Description of class 'CanonicEmbedder' <p>

   \brief Aim: A trivial embedder for digital points, which
   corresponds to the canonic injection of Zn into Rn.

   Model of CPointEmbedder.

   @tparam TSpace the type of digital Space where the embedder works.
 */
  template <typename TSpace>
  struct CanonicEmbedder
  {
  public:
    typedef CanonicEmbedder<TSpace> Self;
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));

    typedef TSpace Space;
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    typedef typename Space::RealPoint RealPoint;
    typedef Point Argument;
    typedef RealPoint Value;

    // ----------------------- Standard services ------------------------------
  public:
    
    /**
     * Destructor.
     */
    virtual ~CanonicEmbedder(){};


    /**
       @param p any point in the Euclidean space.
       @return the digital point floor( p ).
    */
    Point floor( const RealPoint & p ) const;

    /**
       @param p any point in the Euclidean space.
       @return the digital point ceil( p ).
    */
    Point ceil( const RealPoint & p ) const;

    /**
       @param p any point in the Euclidean space.

       @return the digital point round( p ), i.e. the
       "closest" digital point.
    */
    Point round( const RealPoint & p ) const;

    /**
       Map a digital point to its corresponding point in the Euclidean
       space.
       
       @param dp any digital point in the digital space.
       @return its canconical embedding in the Euclidean space.
    */
    virtual RealPoint embed( const Point & dp ) const;

    /**
       Map a digital point to its corresponding point in the Euclidean
       space.
       
       @param dp any digital point in the digital space.
       @return its canconical embedding in the Euclidean space.
    */
    virtual RealPoint operator()( const Point & dp ) const;



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

    // ------------------------- Hidden services ------------------------------
protected:


    // ------------------------- Internals ------------------------------------
private:

}; // end of class CanonicEmbedder


/**
 * Overloads 'operator<<' for displaying objects of class 'CanonicEmbedder'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'CanonicEmbedder' to write.
 * @return the output stream after the writing.
 */
  template <typename TSpace>
  std::ostream&
  operator<< ( std::ostream & out, const CanonicEmbedder<TSpace> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/CanonicEmbedder.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CanonicEmbedder_h

#undef CanonicEmbedder_RECURSES
#endif // else defined(CanonicEmbedder_RECURSES)
