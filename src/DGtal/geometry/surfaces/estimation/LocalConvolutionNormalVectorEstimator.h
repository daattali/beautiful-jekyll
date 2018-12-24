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
 * @file LocalConvolutionNormalVectorEstimator.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/03
 *
 * This file is part of the DGtal library.
 *
 * @see  testLocalConvolutionNormalVectorEstimator.cpp
 */

#if defined(LocalConvolutionNormalVectorEstimator_RECURSES)
#error Recursive header files inclusion detected in LocalConvolutionNormalVectorEstimator.h
#else // defined(LocalConvolutionNormalVectorEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LocalConvolutionNormalVectorEstimator_RECURSES

#if !defined LocalConvolutionNormalVectorEstimator_h
/** Prevents repeated inclusion of headers. */
#define LocalConvolutionNormalVectorEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/graph/BreadthFirstVisitor.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/geometry/surfaces/estimation/CConvolutionWeights.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace deprecated
  {

  /////////////////////////////////////////////////////////////////////////////
  // template class LocalConvolutionNormalVectorEstimator
  /**
   * Description of template class 'LocalConvolutionNormalVectorEstimator' <p>
   * \brief Aim: Computes the normal vector at a surface element by
   * convolution of elementary normal vector to adjacent surfel.
   *
   * A model of CNormalVectorEstimator.
   *
   * To each $n-1$ signed surfel, an elementary inward normal vector can be
   * defined. At a given surfel, this estimator will compute the
   * convolution of elementary normal vector of neighboring surfels
   * using a breadth-first propagation around the given surfel.
   *
   * The neighboring is parametrized by a given topological radius @e R.
   * The weight kernel function maps displacment vectors  to a
   * continuous weights.
   *
   * @warning moved to deprecated since 0.7. Please consider using
   * LocalEstimatorFromFunctorAdapter.
   *
   * @tparam TDigitalSurface type of digital surface on which we would
   * like to compute vector field..
   * @tparam TKernelFunctor type of Functor used to represent
   * convolution kernel functor (see BasicConvolutionKernels.h).
   */
  template <typename TDigitalSurface, typename TKernelFunctor>
  class LocalConvolutionNormalVectorEstimator
  {

    // ----------------------- Types ------------------------------
  public:

    typedef TDigitalSurface DigitalSurface;
    typedef TKernelFunctor KernelFunctor;
    typedef DigitalSurface Surface;
    typedef typename Surface::ConstIterator ConstIterator;
    typedef typename Surface::KSpace::Space::RealVector Quantity;
    typedef typename Surface::SCell SCell;

    BOOST_CONCEPT_ASSERT(( concepts::CConvolutionWeights<TKernelFunctor>));

    // ----------------------- Standard services ------------------------------
  public:

     /**
     * Constructor.
     * @param aSurface surface  for which the normal vector are estimated.
     * @param aFunctor convolution kernel functor.
     */
    LocalConvolutionNormalVectorEstimator(ConstAlias<DigitalSurface> aSurface,
                                          ConstAlias<KernelFunctor> aFunctor);

    /**
     * Destructor.
     */
    ~LocalConvolutionNormalVectorEstimator() {};

    // ----------------------- Interface --------------------------------------
  public:

    /// @return a reference to the associated digital surface.
    const Surface & surface() const;

    /**
     * Initialisation.
     * @param h grid size (must be >0).
     * @param radius topological radius used to specify the size of
     * the convolution.
     */
    void init(const double h,
              const unsigned int radius);

    /**
       @param scell any signed cell.
       @return the estimated quantity at cell \e scell.
     */
    Quantity eval(const SCell & scell) const;

    /**
     * @return the estimated quantity at *it
     */
    Quantity eval(const ConstIterator& it) const;

    /**
     * @return the estimated quantity
     * from itb till ite (exculded)
     */
    template <typename OutputIterator>
    OutputIterator eval(const ConstIterator& itb,
                        const ConstIterator& ite,
                        OutputIterator result) const;

    /**
       Writes on \e result the estimated quantity at all surfels of the digital surface.
       @param result any model of boost::OutputIterator on Quantity.
       @return the output iterator after the last write.
     */
    template <typename OutputIterator>
    OutputIterator evalAll( OutputIterator result ) const;


    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ------------------------- Protected Datas ------------------------------
  protected:
    /**
     * Default constructor.
     */
    LocalConvolutionNormalVectorEstimator()
    {
      myFlagIsInit = false;
    }


    // ------------------------- Private Datas --------------------------------
  private:

    /// Grid size
    double myH;

    /// True if the init() has been called.
    bool myFlagIsInit;

    /// Radius of the convolution.
    unsigned int myRadius;

    /// Reference to the digital surface
    const DigitalSurface & mySurface;

    /// Reference of the kernel convolution functor.
    const KernelFunctor & myKernelFunctor;

    // ------------------------- Hidden services ------------------------------
  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    LocalConvolutionNormalVectorEstimator ( const LocalConvolutionNormalVectorEstimator & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    LocalConvolutionNormalVectorEstimator & operator= ( const LocalConvolutionNormalVectorEstimator & other );


  }; // end of class LocalConvolutionNormalVectorEstimator
  }
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/estimation/LocalConvolutionNormalVectorEstimator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LocalConvolutionNormalVectorEstimator_h

#undef LocalConvolutionNormalVectorEstimator_RECURSES
#endif // else defined(LocalConvolutionNormalVectorEstimator_RECURSES)
