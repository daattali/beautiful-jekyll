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
 * @file BasicConvolutionWeights.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/03/06
 *
 * Header file for module BasicConvolutionWeightss.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicConvolutionWeights_RECURSES)
#error Recursive header files inclusion detected in BasicConvolutionWeights.h
#else // defined(BasicConvolutionWeights_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicConvolutionWeights_RECURSES

#if !defined BasicConvolutionWeights_h
/** Prevents repeated inclusion of headers. */
#define BasicConvolutionWeights_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace deprecated
  {
    /////////////////////////////////////////////////////////////////////////////
    // template class ConstantConvolutionWeight
    /**
     * Description of template class 'ConstantConvolutionWeights' <p>
     * \brief Aim: implement a trivial constant convolution kernel which
     * returns 1 to each distance.
     *
     *
     * @warning moved to deprecated since 0.7. Please consider using
     * LocalEstimatorFromFunctorAdapter.
     *
     *
     *   @tparam TDistance type for topological distances.
     */
    template <typename TDistance>
    class ConstantConvolutionWeights
    {
      // ----------------------- Standard services ------------------------------
    public:

      ///Inner type
      typedef TDistance Distance;


      /**
       * @return 1.0 whatever the distance is.
       */
      inline
      double operator()(const Distance &/*aDisplacement*/) const
      {
        return 1.0;
      }
    };

    /////////////////////////////////////////////////////////////////////////////
    // template class ConstantConvolutionWeight
    /**
     * Description of template class 'GaussianConvolutionWeights' <p>
     * \brief Aim: implement a Gaussian centered convolution kernel.
     *
     * @warning moved to deprecated since 0.7. Please consider using
     * LocalEstimatorFromFunctorAdapter.
     *
     *
     *   @tparam TDistance type for  topological distances.
     */
    template <typename TDistance>
    class GaussianConvolutionWeights
    {
      // ----------------------- Standard services ------------------------------
    public:

      ///Inner type for the topological distance.
      typedef TDistance Distance;

      /**
       * Constructor
       *
       * @param sigma Gaussian sigma parameter.
       */
      GaussianConvolutionWeights(const double sigma): mySigma(sigma)
      {
        myCoef = 1.0/(mySigma * sqrt(2.0*M_PI));
        myCoef2 = 1.0/(2.0*M_PI);
      }

      /**
       * Return a Gaussian weight from a distance to the gaussian
       * function center.
       *
       * @param aDisplacment distance to the center
       * @return the weight
       */
      inline
      double operator()(const Distance &aDisplacment) const
      {
        return myCoef*exp(-NumberTraits<Distance>::castToDouble(aDisplacment)*
                          NumberTraits<Distance>::castToDouble(aDisplacment)*myCoef2);
      }

      ///Internal Sigma value;
      double mySigma;

      ///Precomputed constant coefs.
      double myCoef;
      double myCoef2;
    };

  }


} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicConvolutionWeights_h

#undef BasicConvolutionWeights_RECURSES
#endif // else defined(BasicConvolutionWeights_RECURSES)
