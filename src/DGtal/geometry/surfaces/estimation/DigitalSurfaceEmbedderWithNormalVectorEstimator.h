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
 * @file DigitalSurfaceEmbedderWithNormalVectorEstimator.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/14
 *
 * Header file for module DigitalSurfaceEmbedderWithNormalVectorEstimator.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSurfaceEmbedderWithNormalVectorEstimator_RECURSES)
#error Recursive header files inclusion detected in DigitalSurfaceEmbedderWithNormalVectorEstimator.h
#else // defined(DigitalSurfaceEmbedderWithNormalVectorEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSurfaceEmbedderWithNormalVectorEstimator_RECURSES

#if !defined DigitalSurfaceEmbedderWithNormalVectorEstimator_h
/** Prevents repeated inclusion of headers. */
#define DigitalSurfaceEmbedderWithNormalVectorEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/topology/CDigitalSurfaceEmbedder.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  // Forward declaration.
  template < typename TDigitalSurfaceEmbedder,
             typename TNormalVectorEstimator >
  class DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap;

  /////////////////////////////////////////////////////////////////////////////
  /**
    Description of template class
    'DigitalSurfaceEmbedderWithNormalVectorEstimator' <p> \brief Aim:
    Combines a digital surface embedder with a normal vector estimator
    to get a model of CDigitalSurfaceEmbedder and CWithGradientMap.
    (also default constructible, copy constructible, assignable).

    @tparam TDigitalSurfaceEmbedder a model of digital surface embedder.
    @tparam TNormalVectorEstimator the type of normal vector estimator.

    @todo assert dimensions of space, embedder and implicit function.
   */

  template < typename TDigitalSurfaceEmbedder,
             typename TNormalVectorEstimator >
  class DigitalSurfaceEmbedderWithNormalVectorEstimator
  {
  public:
    typedef DigitalSurfaceEmbedderWithNormalVectorEstimator
    < TDigitalSurfaceEmbedder, TNormalVectorEstimator > Self;
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceEmbedder<TDigitalSurfaceEmbedder> ));

    typedef TDigitalSurfaceEmbedder DigitalSurfaceEmbedder;
    typedef TNormalVectorEstimator NormalVectorEstimator;

    typedef typename DigitalSurfaceEmbedder::KSpace KSpace;
    typedef typename DigitalSurfaceEmbedder::Surface Surface;
    typedef typename DigitalSurfaceEmbedder::SCell SCell;
    typedef typename DigitalSurfaceEmbedder::RealPoint RealPoint;
    typedef typename DigitalSurfaceEmbedder::Argument Argument;
    typedef typename DigitalSurfaceEmbedder::Value Value;

    typedef typename KSpace::Space Space;
    typedef typename Space::RealVector RealVector;
    typedef typename NormalVectorEstimator::Quantity Quantity;
    typedef typename NormalVectorEstimator::DigitalSurface NVESurface;

    BOOST_STATIC_ASSERT(( concepts::ConceptUtils::SameType< RealVector, Quantity >::value ));
    BOOST_STATIC_ASSERT(( concepts::ConceptUtils::SameType< Surface, NVESurface >::value ));

    typedef DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap<DigitalSurfaceEmbedder,NormalVectorEstimator> GradientMap;


    /**
       Default constructor. The object is not valid.
    */
    DigitalSurfaceEmbedderWithNormalVectorEstimator();

    /**
       Assignment.
       @param other the object to clone.
       @return a reference to 'this'.
    */
    Self & operator=( const Self & other );

    /**
        Constructor.
        @param aDSEmbedder any digital surface embedder.
        @param anEstimator a normal vector estimator
    */
    DigitalSurfaceEmbedderWithNormalVectorEstimator
    ( ConstAlias<DigitalSurfaceEmbedder> aDSEmbedder,
      ConstAlias<NormalVectorEstimator> anEstimator );

    /**
       Copy Constructor.
       @param other the object to clone.
    */
    DigitalSurfaceEmbedderWithNormalVectorEstimator
    ( const Self & other );

    /**
     * Destructor.
     */
    ~DigitalSurfaceEmbedderWithNormalVectorEstimator();

    // ----------------------- Interface --------------------------------------
  public:

    /**
       Maps a signed cell to its corresponding point in the Euclidean
       space. Uses the given embedder.

       @param scell any signed cell in the cellular grid space.
       @return its embedding in the Euclidean space.
     */
    RealPoint operator()( const SCell & scell ) const;

    /**
       @return the associated digital surface.
     */
    const Surface & surface() const;

    /**
       @return the associated khalimsky space.
    */
    const KSpace & space() const
    {
      return myDSEmbedder->space();
    }

    /**
       @return the gradient map associated to this embedder, i.e. a
       functor SCell -> RealVector. Uses the given NormalVectorEstimator.
    */
    GradientMap gradientMap() const;

    /**
       @param scell any signed cell in the cellular grid space.
       @return the gradient vector at this surfel. Uses the given
       NormalVectorEstimator.
     */
    RealVector gradient( const SCell & scell ) const;

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
    const DigitalSurfaceEmbedder* myDSEmbedder;
    /// A pointer on the normal vector estimator.
    const NormalVectorEstimator* myEstimator;

    // ------------------------- Hidden services ------------------------------
  protected:

  }; // end of class DigitalSurfaceEmbedderWithNormalVectorEstimator

  /**
     Functor object to associate a normal vector to any surfel of a
     digital surface. It is constructed from an object combining
     digital surface embedder and a normal vector estimator. Generally
     not instantiated directly by the user.

    @tparam TDigitalSurfaceEmbedder a model of digital surface embedder.
    @tparam TNormalVectorEstimator the type of normal vector estimator.

     @see DigitalSurfaceEmbedderWithNormalVectorEstimator::gradientMap
  */
  template < typename TDigitalSurfaceEmbedder,
             typename TNormalVectorEstimator >
  class DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap
  {
  public:
    typedef DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap<TDigitalSurfaceEmbedder,TNormalVectorEstimator> Self;
    BOOST_CONCEPT_ASSERT(( concepts::CDigitalSurfaceEmbedder<TDigitalSurfaceEmbedder> ));

    typedef TDigitalSurfaceEmbedder DigitalSurfaceEmbedder;
    typedef TNormalVectorEstimator NormalVectorEstimator;

    typedef DigitalSurfaceEmbedderWithNormalVectorEstimator< DigitalSurfaceEmbedder, NormalVectorEstimator > Embedder;
    typedef typename Embedder::SCell Argument;
    typedef typename Embedder::RealVector Value;

    /// Destructor. Does nothing.
    ~DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap();

    /// Default constructor. The object is not valid.
    DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap();

    /// Assignment.
    Self & operator=( const Self & other );

    /**
       Copy constructor.
       @param other the object to clone.
    */
    DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap
    ( const Self & other );

    /**
       Constructor from embedder.
       @param embedder any instance of DigitalSurfaceEmbedderWithNormalVectorEstimator.
    */
    DigitalSurfaceEmbedderWithNormalVectorEstimatorGradientMap
    ( ConstAlias<Embedder> embedder );

    /**
       Functor operator : SCell (surfel) -> RealVector (gradient vector).
       @param arg any signed cell.
       @return a real-value vector.
    */
    Value operator()( const Argument & arg ) const;

  protected:
    /// The digital surface embedder with normal vector estimator.
    const Embedder* myEmbedder;

  private:

  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'DigitalSurfaceEmbedderWithNormalVectorEstimator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'DigitalSurfaceEmbedderWithNormalVectorEstimator' to write.
   * @return the output stream after the writing.
   */
  template < typename TDigitalSurfaceEmbedder, typename TNormalVectorEstimator >
  std::ostream&
  operator<< ( std::ostream & out,
               const DigitalSurfaceEmbedderWithNormalVectorEstimator<TDigitalSurfaceEmbedder, TNormalVectorEstimator> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/estimation/DigitalSurfaceEmbedderWithNormalVectorEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSurfaceEmbedderWithNormalVectorEstimator_h

#undef DigitalSurfaceEmbedderWithNormalVectorEstimator_RECURSES
#endif // else defined(DigitalSurfaceEmbedderWithNormalVectorEstimator_RECURSES)
