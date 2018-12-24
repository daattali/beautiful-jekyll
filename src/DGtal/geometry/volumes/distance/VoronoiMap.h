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
 * @file VoronoiMap.h
 * @brief Linear in time distance transformation
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/08/14
 *
 * Header file for module VoronoiMap.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testVoronoiMap.cpp
 */

#if defined(VoronoiMap_RECURSES)
#error Recursive header files inclusion detected in VoronoiMap.h
#else // defined(VoronoiMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VoronoiMap_RECURSES

#if !defined VoronoiMap_h
/** Prevents repeated inclusion of headers. */
#define VoronoiMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include <array>
#include "DGtal/base/Common.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/CImage.h"
#include "DGtal/kernel/CPointPredicate.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/geometry/volumes/distance/CSeparableMetric.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/base/ConstAlias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class VoronoiMap
  /**
   * Description of template class 'VoronoiMap' <p>
   * \brief Aim: Implementation of the linear in time Voronoi map
   * construction.

   * The algorithm uses a seperable process to construct Voronoi maps
   * which has been described in @cite Maurer2003PAMI @cite dcoeurjo_these.
   * Along periodic dimensions, the algorithm is adapted following @cite Coeurjo2008.
   *
   * Given a domain and a point predicate, an instance returns, for
   * each point in the domain, the closest point for which the
   * predicate if false. Following Computational Geometry
   * terminoliogy, points for which the predicate is false are "sites"
   * for the Voronoi map construction. If a point is equi-distant to
   * two sites (e.g. if the digital point belong to a Voronoi cell
   * boundary in the Euclidean space), this Voronoi map construction
   * will only keep one of them.
   *
   * By default, the domain is considered non-periodic but per-dimension
   * periodicity can be specified in the constructor.
   * When the domain has periodic dimensions, the closest point
   * coordinates \c B to a given point \c A may not be between the lower
   * and upper bounds of the domain, in such a way that the non-periodic
   * distance between \c A and \c B is equal to their distance considering
   * the periodicity.
   *
   * The metric is specified by a model of concepts::CSeparableMetric (for
   * instance, any instance of ExactPredicateLpSeparableMetric or
   * InexactPredicateLpSeparableMetric).  If the separable metric has
   * a complexity of O(h) for its "hiddenBy" predicate, the overall
   * Voronoi construction algorithm is in @f$ O(h.d.n^d)@f$ for @f$
   * n^d@f$ domains (see class constructor). For Euclidean the @f$
   * l_2@f$ metric, the overall computation is in @f$ O(d.n^d)@f$,
   * which is optimal.
   *
   * If DGtal has been built with OpenMP support (WITH_OPENMP flag set
   * to "true"), the computation is done in parallel (multithreaded)
   * in an optimal way: on @a p processors, expected runtime is in
   * @f$ O(h.d.n^d / p)@f$.
   *
   * This class is a model of concepts::CConstImage.
   *
   * @see &nbsp; \ref toricVol
   *
   * @tparam TSpace type of Digital Space (model of concepts::CSpace).
   * @tparam TPointPredicate point predicate returning true for points
   * from which we compute the distance (model of concepts::CPointPredicate)
   * @tparam TSeparableMetric a model of concepts::CSeparableMetric
   * @tparam TImageContainer any model of concepts::CImage to store the
   * VoronoiMap (default: ImageContainerBySTLVector). The space of the
   * image container and the TSpace should match. Furthermore the
   * container value type must be TSpace::Vector. Lastly, the domain
   * of the container must be HyperRectDomain.
   */
  template < typename TSpace,
             typename TPointPredicate,
             typename TSeparableMetric,
             typename TImageContainer =
             ImageContainerBySTLVector<HyperRectDomain<TSpace>,
                                       typename TSpace::Vector>
             >
  class VoronoiMap
  {

  public:
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CPointPredicate<TPointPredicate> ));
    BOOST_CONCEPT_ASSERT(( concepts::CSeparableMetric<TSeparableMetric> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImage< TImageContainer > ));

    ///Both Space points and PointPredicate points must be the same.
    BOOST_STATIC_ASSERT ((boost::is_same< typename TSpace::Point,
                          typename TPointPredicate::Point >::value ));

    //ImageContainer::Domain::Space must match with TSpace
    BOOST_STATIC_ASSERT ((boost::is_same< TSpace,
                          typename TImageContainer::Domain::Space >::value ));

    //ImageContainer value type must be  TSpace::Vector
    BOOST_STATIC_ASSERT ((boost::is_same< typename TSpace::Vector,
                          typename TImageContainer::Value >::value ));

    //ImageContainer domain type must be  HyperRectangular
    BOOST_STATIC_ASSERT ((boost::is_same< HyperRectDomain<TSpace>,
                          typename TImageContainer::Domain >::value ));

    ///Copy of the space type.
    typedef TSpace Space;

    ///Copy of the point predicate type.
    typedef TPointPredicate PointPredicate;

    ///Definition of the underlying domain type.
    typedef typename TImageContainer::Domain Domain;

    ///Definition of the separable metric type
    typedef TSeparableMetric SeparableMetric;

    ///Large integer type for SeparableMetricHelper construction.
    typedef DGtal::int64_t IntegerLong;

    typedef typename Space::Vector Vector;
    typedef typename Space::Point Point;
    typedef typename Space::Dimension Dimension;
    typedef typename Space::Size Size;
    typedef typename Space::Point::Coordinate Abscissa;

    ///Type of resulting image
    typedef TImageContainer OutputImage;

    ///Definition of the image value type.
    typedef Vector Value;

    ///Definition of the image value type.
    typedef typename OutputImage::ConstRange  ConstRange;

    ///Self type
    typedef VoronoiMap< TSpace, TPointPredicate,
                        TSeparableMetric,TImageContainer > Self;


    /// Periodicity specification type.
    typedef std::array< bool, Space::dimension > PeriodicitySpec;

    /**
     * Constructor in the non-periodic case.
     *
     * This constructor computes the Voronoi Map of a set of point
     * sites using a SeparableMetric metric, on a non-periodic domain.
     *
     * The method associates to each point satisfying the foreground predicate,
     * the closest site for which the predicate is false. This algorithm is
     * @f$ O(h.d.|domain size|)@f$ if the separable metric "hiddenBy"
     * predicate is in @f$ O(h)@f$.
     *
     * @param aDomain a pointer to the (hyper-rectangular) domain on
     * which the computation is performed.
     *
     * @param predicate a pointer to the point predicate to define the
     * Voronoi sites (false points).
     *
     * @param aMetric a pointer to the separable metric instance.
     */
    VoronoiMap(ConstAlias<Domain> aDomain,
               ConstAlias<PointPredicate> predicate,
               ConstAlias<SeparableMetric> aMetric);

    /**
     * Constructor with periodicity specification.
     *
     * This constructor computes the Voronoi Map of a set of point
     * sites using a SeparableMetric metric, on a domain with specified
     * periodicity.
     *
     * The method associates to each point satisfying the foreground predicate,
     * the closest site for which the predicate is false. This algorithm is
     * @f$ O(h.d.|domain size|)@f$ if the separable metric "hiddenBy"
     * predicate is in @f$ O(h)@f$.
     *
     * @param aDomain a pointer to the (hyper-rectangular) domain on
     * which the computation is performed.
     *
     * @param predicate a pointer to the point predicate to define the
     * Voronoi sites (false points).
     *
     * @param aMetric a pointer to the separable metric instance.
     *
     * @param aPeriodicitySpec an array of size equal to the space dimension
     *        where the i-th value is \c true if the i-th dimension of the
     *        space is periodic, \c false otherwise.
     */
    VoronoiMap(ConstAlias<Domain> aDomain,
               ConstAlias<PointPredicate> predicate,
               ConstAlias<SeparableMetric> aMetric,
               PeriodicitySpec const & aPeriodicitySpec);
    /**
     * Default destructor
     */
    ~VoronoiMap() = default;

    /**
     * Disabling default constructor.
     */
     VoronoiMap() = delete;

  public:
    // ------------------- ConstImage model ------------------------

    /**
     * Assignment operator from another Voronoi map.
     *
     *  @param aOtherVoronoiMap another instance of Self
     *  @return a reference to Self
     */
    Self &  operator=(const Self &aOtherVoronoiMap ) = default;

    /**
     * Returns a reference (const) to the Voronoi map domain.
     * @return a domain
     */
    const Domain &  domain() const
    {
      return *myDomainPtr;
    }

    /**
     * Returns a const range on the Voronoi map values.
     *  @return a const range
     */
    ConstRange constRange() const
    {
      return myImagePtr->constRange();
    }

    /**
     * Access to a Voronoi value (a.k.a. vector to the closest site)
     * at a point.
     *
     * @param aPoint the point to probe.
     */
    Value operator()(const Point &aPoint) const
    {
      return myImagePtr->operator()(aPoint);
    }

    /**
     * @return Returns an alias to the underlying metric.
     */
    const SeparableMetric* metric() const
    {
      return myMetricPtr;
    }

    /** Periodicity specification.
     *
     * @returns the periodicity specification array.
     */
    PeriodicitySpec const & getPeriodicitySpec() const
      {
        return myPeriodicitySpec;
      }

    /** Periodicity specification along one dimensions.
     *
     * @param [in] n the dimension index.
     * @return \c true if the n-th dimension is periodic, \c false otherwise.
     */
    bool isPeriodic( const Dimension n ) const
      {
        return myPeriodicitySpec[ n ];
      }

    /**
     * Project point coordinates into the domain, taking into account
     * the periodicity.
     *
     * @pre The given point must come from operator()(const Point &) const (for performance reasons).
     *
     * @param aPoint the point to project
     * @return the coordinates projected into the domain bounds accordingly
     *         to the periodicity specification.
     */
    Point projectPoint( Point aPoint ) const;

    /**
     * Self Display method.
     *
     * @param out output stream
     */
    void selfDisplay ( std::ostream & out ) const;

    // ------------------- Private functions ------------------------
  private:

    /**
     * Compute the Voronoi Map of a set of point sites using a
     * SeparableMetric metric.  The method associates to each point
     * satisfying the foreground predicate, the closest site for which
     * the predicate is false. This algorithm is O(h.d.|domain size|).
     */
    void compute ( ) ;


    /**
     *  Compute the other steps of the separable Voronoi map.
     *
     * @param [in] dim the dimension to process
     */
    void computeOtherSteps(const Dimension dim) const;
    /**
     * Given  a voronoi map valid at dimension @a dim-1, this method
     * updates the map to make it consistent at dimension @a dim along
     * the 1D span starting at @a row along the dimension @a
     * dim.
     *
     * @param [in] row starting point of the 1D process.
     * @param [in] dim dimension of the update.
     */
    void computeOtherStep1D (const Point &row,
                             const Dimension dim) const;

    /**
     * Project a coordinate into the domain, taking into account
     * the periodicity.
     *
     * @pre The given coordinate must come from operator()(const Point &) const (for performance reasons).
     *
     * @param aCoordinate the coordinate.
     * @param aDim  dimension of the coordinate.
     * @return the coordinates projected into the domain bounds accordingly
     *         to the periodicity specification.
     */
    typename Point::Coordinate projectCoordinate( typename Point::Coordinate aCoordinate, const Dimension aDim ) const;

    // ------------------- Private members ------------------------
  private:

    ///Pointer to the computation domain
    const Domain * myDomainPtr;

    ///Pointer to the point predicate
    const PointPredicate * myPointPredicatePtr;

    ///Copy of the image lower bound
    Point myLowerBoundCopy;

    ///Copy of the image lower bound
    Point myUpperBoundCopy;

    ///Value to act as a +infinity value
    Point myInfinity;

    /// Index of the periodic dimensions
    std::vector< Dimension > myPeriodicityIndex; // Could be boost::static_vector but it needs Boost >= 1.54.

    /// Domain extent.
    Point myDomainExtent;

  protected:

    ///Pointer to the separable metric instance
    const SeparableMetric * myMetricPtr;

    ///Voronoi map image
    CountedPtr<OutputImage> myImagePtr;

    /// Periodicity along each dimension.
    PeriodicitySpec myPeriodicitySpec;

  }; // end of class VoronoiMap

  /**
   * Overloads 'operator<<' for displaying objects of class 'ExactPredicateLpSeparableMetric'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ExactPredicateLpSeparableMetric' to write.
   * @return the output stream after the writing.
   */
  template <typename S, typename P,
            typename Sep, typename TI>
  std::ostream&
  operator<< ( std::ostream & out, const VoronoiMap<S,P,Sep,TI> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/distance/VoronoiMap.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VoronoiMap_h

#undef VoronoiMap_RECURSES
#endif // else defined(VoronoiMap_RECURSES)
