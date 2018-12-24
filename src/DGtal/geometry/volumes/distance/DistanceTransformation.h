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
 * @file DistanceTransformation.h
 * @brief Linear in time distance transformation
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/09
 *
 * Header file for module DistanceTransformation.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testDistanceTransformation.cpp, testDistanceTransformationND.cpp, testReverseDT.cpp
 */

#if defined(DistanceTransformation_RECURSES)
#error Recursive header files inclusion detected in DistanceTransformation.h
#else // defined(DistanceTransformation_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DistanceTransformation_RECURSES

#if !defined DistanceTransformation_h
/** Prevents repeated inclusion of headers. */
#define DistanceTransformation_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/geometry/volumes/distance/CSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/VoronoiMap.h"
#include "DGtal/images/DefaultConstImageRange.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/base/ConstAlias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DistanceTransformation
  /**
   * Description of template class 'DistanceTransformation' <p>
   * \brief Aim: Implementation of the linear in time distance
   * transformation for separable metrics.
   *
   * This class is a wrapper around a Voronoi map construction (see
   * VoronoiMap). More precisely, at a point p, since the VoronoiMap
   * at p returns a vector to the closest site, this class adapts the
   * operator() in order to returns the distance to the closest site
   * for the considered metric.
   *
   * Please refer to VoronoiMap documentation for details on the
   * computational cost and parameter description.
   *
   * This class is a model of concepts::CConstImage.
   *
   * @tparam TSpace type of Digital Space (model of concepts::CSpace).
   * @tparam TPointPredicate point predicate returning false for points
   * from which we compute the distance (model of concepts::CPointPredicate)
   * @tparam TSeparableMetric a model of concepts::CSeparableMetric
   * @tparam TImageContainer any model of concepts::CImage to store the
   * VoronoiMap (default: ImageContainerBySTLVector). The space of the
   * image container and the TSpace should match. Furthermore the
   * container value type must be TSpace::Vector.
    *
   * @see distancetransform2D.cpp
   * @see distancetransform3D.cpp
   */
  template < typename TSpace,
             typename TPointPredicate,
             typename TSeparableMetric,
             typename TImageContainer =
               ImageContainerBySTLVector< HyperRectDomain<TSpace>,
                                          typename TSpace::Vector >
           >
  class DistanceTransformation
    : public VoronoiMap<TSpace,TPointPredicate, TSeparableMetric, TImageContainer>
  {

  public:
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate<TPointPredicate> ));
    BOOST_CONCEPT_ASSERT(( concepts::CSeparableMetric<TSeparableMetric> ));

    ///Separable Metric type
    typedef TSeparableMetric SeparableMetric;

    ///Separable Metric type
    typedef TSpace  Space;

    ///Separable Metric type
    typedef typename TSpace::Vector  Vector;

    ///Point Predicate  type
    typedef TPointPredicate PointPredicate;

    ///Definition of the image value type.
    typedef  typename SeparableMetric::Value Value;

    ///Definition of the image value type.
    typedef  typename SeparableMetric::Point Point;
    BOOST_STATIC_ASSERT((boost::is_same< typename Space::Point,
                         typename SeparableMetric::Point>::value));

    ///Definition of the image.
    typedef  DistanceTransformation<TSpace,TPointPredicate,TSeparableMetric> Self;

    typedef VoronoiMap<TSpace,TPointPredicate,TSeparableMetric> Parent;

    ///Definition of the image constRange
    typedef  DefaultConstImageRange<Self> ConstRange;


    ///Definition of the image value type.
    typedef typename VoronoiMap<TSpace,TPointPredicate,
            TSeparableMetric,TImageContainer>::Domain  Domain;

    /**
     *  Constructor in the non-periodic case.
     *
     * See documentation of VoronoiMap constructor.
     */
    DistanceTransformation(ConstAlias<Domain> aDomain,
                           ConstAlias<PointPredicate> predicate,
                           ConstAlias<SeparableMetric> aMetric):
      VoronoiMap<TSpace,TPointPredicate,TSeparableMetric,TImageContainer>(aDomain,
                                                                          predicate,
                                                                          aMetric)
    {}

    /**
     *  Constructor with periodicity specification.
     *
     * See documentation of VoronoiMap constructor.
     */
    DistanceTransformation(ConstAlias<Domain> aDomain,
                           ConstAlias<PointPredicate> predicate,
                           ConstAlias<SeparableMetric> aMetric,
                           typename Parent::PeriodicitySpec const & aPeriodicitySpec)
      : VoronoiMap<TSpace,TPointPredicate,TSeparableMetric,TImageContainer>(aDomain,
                                                                            predicate,
                                                                            aMetric,
                                                                            aPeriodicitySpec)
    {}

    /**
     * Default destructor
     */
    ~DistanceTransformation() {};

    // ------------------- Private functions ------------------------
  public:

     /**
     * Returns a const range on the DistanceMap values.
     *  @return a const range
     */
    const Domain & domain() const
    {
      return Parent::domain();
    }

     /**
     * Returns a const range on the DistanceMap values.
     *  @return a const range
     */
    ConstRange constRange() const
    {
      return ConstRange(*this);
    }

    /**
     * Access to a DistanceMap value (a.k.a. the norm of the
     * associated Voronoi vector) at a point.
     *
     * @param aPoint the point to probe.
     */
    Value operator()(const Point &aPoint) const
    {
      return this->myMetricPtr->operator()(aPoint,
                                           this->myImagePtr->operator()(aPoint));
    }

    /**
     * Access to a Voronoi vector inducing the DistanceMap value
     * (a.k.a. the  vector such that its norm is the DT value) at a point.
     *
     * @param [in] aPoint the point to probe.
     */
    Vector getVoronoiVector(const Point &aPoint) const
    {
      return this->myImagePtr->operator()(aPoint);
    }

    /**
     * @return  Returns the underlying metric.
     */
    const SeparableMetric* metric() const
    {
      return Parent::metric();
    }

    /**
     * Self Display method.
     *
     * @param [out] out output stream
     */
    void selfDisplay ( std::ostream & out ) const
    {
      out << "[DistanceTransformation] underlying VoronoiMap={";
      Parent::selfDisplay(out);
      out << "}";
    }

    // ------------------- protected methods ------------------------
  protected:

    /**
     * Default Constructor.
     *
     */
    DistanceTransformation();


    // ------------------- Private members ------------------------
  private:

  }; // end of class DistanceTransformation


// //                                                                           //
// ///////////////////////////////////////////////////////////////////////////////

  template <typename S,typename P,typename TSep>
  inline
  std::ostream&
  operator<< ( std::ostream & out,
               const DistanceTransformation<S,P,TSep> & object )
  {
    object.selfDisplay( out );
    return out;
  }



} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DistanceTransformation_h

#undef DistanceTransformation_RECURSES
#endif // else defined(DistanceTransformation_RECURSES)
