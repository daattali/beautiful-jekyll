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
 * @file ReverseDistanceTransformation.h
 * @brief Linear in time distance transformation
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/09
 *
 * Header file for module ReverseDistanceTransformation.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testReverseDistanceTransformation.cpp, testReverseDistanceTransformationND.cpp, testReverseDT.cpp
 */

#if defined(ReverseDistanceTransformation_RECURSES)
#error Recursive header files inclusion detected in ReverseDistanceTransformation.h
#else // defined(ReverseDistanceTransformation_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ReverseDistanceTransformation_RECURSES

#if !defined ReverseDistanceTransformation_h
/** Prevents repeated inclusion of headers. */
#define ReverseDistanceTransformation_h

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
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/CImage.h"
#include "DGtal/base/ConstAlias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ReverseDistanceTransformation
  /**
   * Description of template class 'ReverseDistanceTransformation' <p>
   * \brief Aim: Implementation of the linear in time reverse distance
   * transformation for separable metrics.
   *
   * This class is a wrapper around a power map construction (see
   * PowerMap). More precisely, at a point p, since the PowerMap at p
   * returns a vector to the closest power site, this class adapts
   * the operator() in order to returns the power distance to the
   * closest weighted site for the considered metric.
   *
   * Please refer to PowerMap documentation for details on the
   * computational cost and parameter description.
   *
   * This class is a model of CConstImage.
   *
   * @tparam TWeightImage model of CConstImage
   * @tparam TPSeparableMetric model of CPowerSeparableMetric
   * @tparam TImageContainer any model of CImage to store the
   * PowerMap (default: ImageContainerBySTLVector). The space of the
   * image container and the TSpace should match. Furthermore the
   * container value type must be TSpace::Vector.
   */
  template < typename TWeightImage,
             typename TPSeparableMetric,
             typename TImageContainer =
               ImageContainerBySTLVector<HyperRectDomain<typename TWeightImage::Domain::Space>,
             typename TWeightImage::Domain::Space::Vector>
           >
  class ReverseDistanceTransformation
    : public PowerMap<TWeightImage, TPSeparableMetric, TImageContainer>
  {

  public:

    ///Separable Metric type
    typedef TWeightImage WeightImage;

    ///Separable Metric type
    typedef TPSeparableMetric PowerSeparableMetric;

    ///Image Container type
    typedef TImageContainer ImageContainer;
    BOOST_CONCEPT_ASSERT(( concepts::CImage<ImageContainer> ));

    ///Separable Metric type value type
    typedef typename PowerSeparableMetric::Value Value;

    ///Point type
    typedef typename TWeightImage::Domain::Space::Point Point;

    ///Vector type
    typedef typename TWeightImage::Domain::Space::Vector Vector;

    ///Separable Metric type weight type
    typedef typename PowerSeparableMetric::Weight Weight;

    ///Definition of the image.
    typedef  ReverseDistanceTransformation<TWeightImage,
                                           TPSeparableMetric,
                                           TImageContainer> Self;

    typedef PowerMap<TWeightImage,TPSeparableMetric> Parent;

    ///Definition of the image constRange
    typedef  DefaultConstImageRange<Self> ConstRange;


    ///Definition of the image value type.
    typedef typename PowerMap< TWeightImage,TPSeparableMetric,
                               TImageContainer >::Domain  Domain;


    /**
     *  Constructor in the non-periodic case.
     *
     * See documentation of PowerMap constructor.
     */
    ReverseDistanceTransformation(ConstAlias<Domain> aDomain,
                                  ConstAlias<WeightImage> aWeightImage,
                                  ConstAlias<PowerSeparableMetric> aMetric):
      PowerMap<TWeightImage,TPSeparableMetric,TImageContainer>(aDomain,
                                                               aWeightImage,
                                                               aMetric)
    {}

    /**
     *  Constructor with periodicity specification.
     *
     * See documentation of PowerMap constructor.
     */
    ReverseDistanceTransformation(ConstAlias<Domain> aDomain,
                                  ConstAlias<WeightImage> aWeightImage,
                                  ConstAlias<PowerSeparableMetric> aMetric,
                                  typename Parent::PeriodicitySpec const & aPeriodicitySpec)
      : PowerMap<TWeightImage,TPSeparableMetric,TImageContainer>(aDomain,
                                                                 aWeightImage,
                                                                 aMetric,
                                                                 aPeriodicitySpec)
    {}

    /**
     * Default destructor
     */
    ~ReverseDistanceTransformation() {};

    // ------------------- Private functions ------------------------
  public:

     /**
     * Returns a const range on the ReverseDistanceMap values.
     *  @return a const range
     */
    const Domain & domain() const
    {
      return Parent::domain();
    }

     /**
     * Returns a const range on the ReverseDistanceMap values.
     *  @return a const range
     */
    ConstRange constRange() const
    {
      return ConstRange(*this);
    }

    /**
     * Access to a ReverseDistanceMap value (a.k.a. the norm of the
     * associated Power vector) at a point.
     *
     * @param aPoint the point to probe.
     */
    Value operator()(const Point &aPoint) const
    {
      return this->myMetricPtr->powerDistance(aPoint,
                                              this->myImagePtr->operator()(aPoint),
                                              this->myWeightImagePtr->operator()( this->myImagePtr->operator()(aPoint)));
    }

    /**
     * Access to a ReverseDistanceMap value (a.k.a. the norm of the
     * associated Voronoi vector) at a point.
     *
     * @param aPoint the point to probe.
     */
    Vector getPowerVector(const Point &aPoint) const
    {
      return this->myImagePtr->operator()(aPoint);
    }

    /**
     * @return  Returns the underlying metric.
     */
    const PowerSeparableMetric* metricPtr() const
    {
      return Parent::metricPtr();
    }

    /**
     * Self Display method.
     *
     * @param out output stream
     */
    void selfDisplay ( std::ostream & out ) const
    {
      out << "[ReverseDistanceTransformation] underlying PowerMap={";
      Parent::selfDisplay(out);
      out << "}";
    }

    // ------------------- protected methods ------------------------
  protected:

    /**
     * Default Constructor.
     *
     */
    ReverseDistanceTransformation();


    // ------------------- Private members ------------------------
  private:

  }; // end of class ReverseDistanceTransformation


// //                                                                           //
// ///////////////////////////////////////////////////////////////////////////////

  template <typename W,typename TSep>
  inline
  std::ostream&
  operator<< ( std::ostream & out,
               const ReverseDistanceTransformation<W,TSep> & object )
  {
    object.selfDisplay( out );
    return out;
  }



} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ReverseDistanceTransformation_h

#undef ReverseDistanceTransformation_RECURSES
#endif // else defined(ReverseDistanceTransformation_RECURSES)
