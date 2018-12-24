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
 * @file ElementaryConvolutionNormalVectorEstimator.h
 * @brief Computes the true quantity to each element of a range associated to a parametric shape.
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/31
 *
 * Header file for module ElementaryConvolutionNormalVectorEstimator.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testLengthEstimators.cpp, testTrueLocalEstimator.cpp
 */

#if defined(ElementaryConvolutionNormalVectorEstimator_RECURSES)
#error Recursive header files inclusion detected in ElementaryConvolutionNormalVectorEstimator.h
#else // defined(ElementaryConvolutionNormalVectorEstimator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ElementaryConvolutionNormalVectorEstimator_RECURSES

#if !defined ElementaryConvolutionNormalVectorEstimator_h
/** Prevents repeated inclusion of headers. */
#define ElementaryConvolutionNormalVectorEstimator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/topology/SCellsFunctors.h>
#include <vector>

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
  /////////////////////////////////////////////////////////////////////////////
  // template class ElementaryConvolutionNormalVectorEstimator
  /**
   * Description of template class 'ElementaryConvolutionNormalVectorEstimator' <p>
   * \brief Aim: Estimates normal vector  by
   * convolution of elementary normal vector to adjacent surfel.
   *
   * To each @f$n-1@f$ signed surfel, an elementary inward normal vector
   * can be defined. At a given surfel, this functor will compute the
   * weighted average of elementary normal vectors in the
   * neighborihood.
   *
   * Model of CLocalEstimatorFromSurfelFunctor.
   *
   * @tparam TSurfel type of surfels
   * @tparam TEmbedder type of functors which embed surfel to @f$ \mathbb{R}^3@f$
   */
  template <typename TSurfel, typename TEmbedder>
  class ElementaryConvolutionNormalVectorEstimator
  {
  public:

    typedef TSurfel Surfel;
    typedef TEmbedder SCellEmbedder;
    typedef typename SCellEmbedder::RealPoint RealPoint;
    typedef RealPoint Quantity;

    /**
     * Constructor.
     *
     * @param anEmbedder embedder to map surfel to R^n.
     * @param h grid step
     */
    ElementaryConvolutionNormalVectorEstimator(ConstAlias<SCellEmbedder> anEmbedder,
                                               const double h):
      myEmbedder(&anEmbedder), myH(h)
    {
    }

    /**
     * Add the geometrical embedding of a surfel to the point list
     *
     * @param aSurf a surfel to add
     * @param aDistance  distance of aSurf to the neighborhood boundary
     */
    void pushSurfel(const Surfel & aSurf,
                    const double aDistance)
    {
      RealPoint elementary;
      Dimension i = myEmbedder->space().sOrthDir ( aSurf );
      elementary[ i ] = myEmbedder->space().sDirect ( aSurf, i ) ? 1 : -1;

      myWeightedVector += aDistance *elementary;
    }

    /**
     * Evaluate the normal vector from Monge form.
     *
     * @return the mean curvature
     */
    Quantity eval( )
    {
      return myWeightedVector.getNormalized();
    }

    /**
     * Reset the point list.
     *
     */
    void reset()
    {
      myWeightedVector = RealPoint().diagonal(0.0);
    }


  private:

    ///Alias of the geometrical embedder
    const SCellEmbedder * myEmbedder;

    ///Array of CGAL points
    RealPoint myWeightedVector;

    //Grid step
    double myH;

  }; // end of class ElementaryConvolutionNormalVectorEstimator
  } //namespace functors
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ElementaryConvolutionNormalVectorEstimator_h

#undef ElementaryConvolutionNormalVectorEstimator_RECURSES
#endif // else defined(ElementaryConvolutionNormalVectorEstimator_RECURSES)
