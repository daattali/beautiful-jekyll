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
 * @file ReducedMedialAxis.h
 * @brief Linear in time distance transformation
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/12/08
 *
 * Header file for module ReducedMedialAxis.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testReducedMedialAxis.cpp, testReducedMedialAxisND.cpp, testReverseDT.cpp
 */

#if defined(ReducedMedialAxis_RECURSES)
#error Recursive header files inclusion detected in ReducedMedialAxis.h
#else // defined(ReducedMedialAxis_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ReducedMedialAxis_RECURSES

#if !defined ReducedMedialAxis_h
/** Prevents repeated inclusion of headers. */
#define ReducedMedialAxis_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/geometry/volumes/distance/CPowerSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/PowerMap.h"
#include "DGtal/images/DefaultConstImageRange.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/Image.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ReducedMedialAxis
  /**
   * Description of template class 'ReducedMedialAxis' <p>
   * \brief Aim: Implementation of the separable medial axis
   * extraction.
   *
   * This utility struct extract medial axis balls from a
   * PowerMap. Basically, each (weighted) site of the PowerMap defines
   * a digital maximal ball if its digital power cell restricted to
   * the input shape is not empty @cite dcoeurjo_pami_RDMA .
   *
   *        Optimal Separable Algorithms to Compute the Reverse
   *        Euclidean Distance Transformation and Discrete Medial Axis in
   *        Arbitrary Dimension, D. Coeurjolly and A. Montanvert, IEEE
   *        Transactions on Pattern Analysis and Machine Intelligence,
   *        29(3):437-448, 2007.
   *
   * The output is an image associating ball radii (weight of the
   * power map site) to maximal ball centers. Most methods output a
   * lightweight proxy to an image container (of type ImageContainer,
   * see below).
   *
   * @note Following ReverseDistanceTransformation, the input shape is
   * defined as points with negative power distance.
   *
   * @tparam TPowerMap any specialized PowerMap type @tparam
   * TImageContainer any model of CImage to store the medial axis
   * points (default: ImageContainerBySTLVector).
   *
   * @see testReducedMedialAxis.cpp
   */
  template <typename TPowerMap,
            typename TImageContainer =  ImageContainerBySTLMap<typename TPowerMap::Domain,
                                                               typename TPowerMap::PowerSeparableMetric::Value> >
  struct ReducedMedialAxis
  {
    //MA Container
    typedef Image<TImageContainer> Type;

    /**
     * Extract reduced medial axis from a power map.
     * This methods is in @f$ O(|powerMap|)@f$.
     *
     * @param aPowerMap the input powerMap
     *
     * @return a lightweight proxy to the ImageContainer specified in
     * template arguments.
     */
    static
    Type getReducedMedialAxisFromPowerMap(const TPowerMap &aPowerMap)
    {
      TImageContainer *computedMA = new TImageContainer( aPowerMap.domain() );

      for (typename TPowerMap::Domain::ConstIterator it = aPowerMap.domain().begin(),
             itend = aPowerMap.domain().end(); it != itend; ++it)
        {
          const auto v  = aPowerMap( *it );
          const auto pv = aPowerMap.projectPoint( v );

          if ( aPowerMap.metricPtr()->powerDistance( *it, v, aPowerMap.weightImagePtr()->operator()( pv ) )
                      < NumberTraits<typename TPowerMap::PowerSeparableMetric::Value>::ZERO )
            computedMA->setValue( v, aPowerMap.weightImagePtr()->operator()( pv ) );
        }

      return Type( computedMA );
    }
  }; // end of class ReducedMedialAxis



} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ReducedMedialAxis_h

#undef ReducedMedialAxis_RECURSES
#endif // else defined(ReducedMedialAxisdesign pa_RECURSES)
