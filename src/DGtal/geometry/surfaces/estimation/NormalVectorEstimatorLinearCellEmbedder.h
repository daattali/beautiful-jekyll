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
 * @file NormalVectorEstimatorLinearCellEmbedder.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/14
 *
 * Header file for module NormalVectorEstimatorLinearCellEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(NormalVectorEstimatorLinearCellEmbedder_RECURSES)
#error Recursive header files inclusion detected in NormalVectorEstimatorLinearCellEmbedder.h
#else // defined(NormalVectorEstimatorLinearCellEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define NormalVectorEstimatorLinearCellEmbedder_RECURSES

#if !defined NormalVectorEstimatorLinearCellEmbedder_h
/** Prevents repeated inclusion of headers. */
#define NormalVectorEstimatorLinearCellEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/shapes/implicit/CImplicitFunction.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
    Description of template class 'NormalVectorEstimatorLinearCellEmbedder' <p>
    \brief Aim: model of cellular embedder for normal vector
    estimators on digital surface,
    (default constructible, copy constructible, assignable).
   
    @tparam TDigitalSurface the digital surface definition
    @tparam TNormalVectorEstimator the type of normal vector estimator.
    @tparam TEmbedder the type of digital embedder.

    @todo assert dimensions of space, embedder and implicit function.
   */
  
  template < typename TDigitalSurface,
             typename TNormalVectorEstimator,
             typename TEmbedder >
  class NormalVectorEstimatorLinearCellEmbedder
  {

  public:
    typedef TDigitalSurface DigitalSurface;
    typedef TNormalVectorEstimator NormalVectorEstimator;
    typedef TEmbedder Embedder;
    typedef typename DigitalSurface::ConstIterator ConstIterator;
    typedef typename DigitalSurface::KSpace::Point Point;
    typedef typename DigitalSurface::KSpace::Space::RealPoint RealPoint;
    typedef typename DigitalSurface::KSpace::Space::RealVector RealVector;
    typedef typename NormalVectorEstimator::Quantity Quantity;
    
    /** 
        Constructor.
        
       @param digSurf  any digital surface.
       @param estimator an normal vector estimator
       @param e a digital embedder (like a GaussDigitizer).
    */
    NormalVectorEstimatorLinearCellEmbedder( ConstAlias<DigitalSurface> digSurf,
                                             ConstAlias<NormalVectorEstimator> estimator, 
                                             ConstAlias<Embedder> e );
    
    /** 
     * Destructor.
     */    
    ~NormalVectorEstimatorLinearCellEmbedder();

    // ----------------------- Interface --------------------------------------
  public:


    /**
       Maps a digital point to its corresponding point in the Euclidean
       space.
       
       @param p any digital point in the digital space.
       @return its embedding by the current embedder in the Euclidean space.
     */
    RealPoint embed( const Point & p ) const;

    /**
       Maps a digital surface surfel defined by an iterator into its
       corresponding point in the Euclidean space.
       
       @param it any iterator on surface surfel.
       @return its embedding in the Euclidean space.
     */
    RealPoint embedSurfel( const ConstIterator & it ) const;

    /**
       Maps a digital point to its corresponding embedding position
       and gradient vector in the Euclidean space.
       
       @param surfelIt any digital surface surfel given by a ConstIterator.
       @param x its embedding in the Euclidean space.
       @param grad (returns) its gradient vector at the point given by
       the current embedder in the Euclidean space.
     */
    void embedSurfel( const ConstIterator & surfelIt, RealPoint & x, RealVector & grad ) const;

   
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
   
    ///A pointer on the digital surface
    const DigitalSurface& mySurface;
    /// A pointer on the normal vector estimator.
    const NormalVectorEstimator& myPtrFct;
    /// A pointer on the digital embedder.
    const Embedder& myPtrEmbedder;
   
    // ------------------------- Hidden services ------------------------------
  protected:
    NormalVectorEstimatorLinearCellEmbedder();

  private:    
    
  }; // end of class NormalVectorEstimatorLinearCellEmbedder


  /**
   * Overloads 'operator<<' for displaying objects of class 'NormalVectorEstimatorLinearCellEmbedder'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'NormalVectorEstimatorLinearCellEmbedder' to write.
   * @return the output stream after the writing.
   */
  template < typename TDigitalSurface, typename TNormalVectorEstimator, typename TEmbedder >
  std::ostream&
  operator<< ( std::ostream & out, 
               const NormalVectorEstimatorLinearCellEmbedder<TDigitalSurface, TNormalVectorEstimator, TEmbedder> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/estimation/NormalVectorEstimatorLinearCellEmbedder.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined NormalVectorEstimatorLinearCellEmbedder_h

#undef NormalVectorEstimatorLinearCellEmbedder_RECURSES
#endif // else defined(NormalVectorEstimatorLinearCellEmbedder_RECURSES)
