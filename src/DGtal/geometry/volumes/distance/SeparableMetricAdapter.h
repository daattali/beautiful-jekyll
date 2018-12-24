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
 * @file SeparableMetricAdapter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/21/04
 *
 * Header file for module SeparableMetricAdapter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SeparableMetricAdapter_RECURSES)
#error Recursive header files inclusion detected in SeparableMetricAdapter.h
#else // defined(SeparableMetricAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SeparableMetricAdapter_RECURSES

#if !defined SeparableMetricAdapter_h
/** Prevents repeated inclusion of headers. */
#define SeparableMetricAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <cmath>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/volumes/distance/CMetricSpace.h"
#include "DGtal/base/ConstAlias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class SeparableMetricAdapter
  /**
   * Description of template class 'SeparableMetricAdapter' <p>
   * \brief Aim: Adapts any model of CMetric to construct a separable metric
   * (model of CSeparableMetric).
   *
   * The adapted metric can thus be used in separable algorithms such as
   * VoronoiMap or PowerMap. The adapted metric makes sense only if the input
   * metric as the @e monotinicity propertery (see  @cite Hirata1996  or @cite Maurer2003PAMI): In
   * dimension 2, consider two points @f$ p(x,y)@f$,
   * @f$q(x',y')@f$ with @f$x<x'@f$. Let @f$r( x'',0)@f$ be a point on the
   * x-axis such that @f$d(p,r) = d(q,r)@f$ and @f$ s(u,0)@f$ be another
   * point on the x-axis. A metric @f$ d@f$ is @e monotonic if
   *
   * @f[     u < x'' \implies d(p,s) \leq d(q,s) @f]
   * and
   * @f[    u > x'' \implies d(p,s) \geq d(q,s) @f]
   *
   * If the metric distance evaluation is in @f$O(m)@f$, the hiddenBy()
   * method is in @f$O(m\log n)@f$.
   *
   * @tparam TMetric the type of input metric (model of CMetric)
   *
   */
  template <typename TMetric>
  class SeparableMetricAdapter
  {
    // ----------------------- Standard services ------------------------------
  public:


    ///Copy the space type
    typedef TMetric Metric;
    BOOST_CONCEPT_ASSERT(( concepts::CMetricSpace<TMetric> ));

    ///Type for points
    typedef typename Metric::Point Point;
    ///Type for point abscissa
    typedef typename Point::Coordinate Abscissa;
    ///Type for values
    typedef typename Metric::Value Value;
    ///Type for raw values
    typedef typename Metric::RawValue RawValue;
    ///Type for vectors
    typedef typename Metric::Vector Vector;
    ///Type for Space
    typedef typename Metric::Space Space;

    /**
     * Constructor from a CMetric model instance.
     * The metric is aliased in this class.
     *
     * @param [in] aMetric any model of CMetric which is monotonic.
     */
    SeparableMetricAdapter(ConstAlias<Metric> aMetric): myMetric(&aMetric)
    {}

    /**
     * Destructor.
     */
    ~SeparableMetricAdapter() {};

    /**
     * Copy constructor. (CopyConstruticle concept)
     * @param other the object to clone.
     */
    SeparableMetricAdapter ( const SeparableMetricAdapter &other ) : myMetric(other.myMetric) {}

    /**
     * Assignment. (Assignable concept)
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SeparableMetricAdapter & operator= ( const SeparableMetricAdapter & other )
    {
      myMetric = other.myMetric;
      return *this;
    }

    // ----------------------- Interface --------------------------------------
  public:

    // ----------------------- CMetric --------------------------------------
    /**
     * Compute the distance between @a aP and @a aQ.
     *
     * @param aP a first point.
     * @param aQ a second point.
     *
     * @return the distance between aP and aQ.
     */
    Value operator()(const Point & aP, const Point &aQ) const
    {
      return myMetric->operator()(aP,aQ);
    }

    /**
     * Compute the raw distance between @a aP and @a aQ.
     *
     * @param aP a first point.
     * @param aQ a second point.
     *
     * @return the distance between aP and aQ.
     */
    RawValue rawDistance(const Point & aP, const Point &aQ) const
    {
      return myMetric->rawDistance(aP,aQ);
    }
    /**
     * Given an origin and two points, this method decides which one
     * is closest to the origin. This method should be faster than
     * comparing distance values.
     *
     * @param origin the origin
     * @param first  the first point
     * @param second the second point
     *
     * @return a Closest enum: ClosestFIRST, ClosestSECOND or ClosestBOTH.
     */
    Closest closest(const Point &origin,
                    const Point &first,
                    const Point &second) const
    {
      return myMetric->closest(origin,first,second);
    }

    // ----------------------- CSeparableMetric --------------------------------------
    /**
     * Given three sites (u,v,w) and a straight segment
     * [startingPoint,endPoint] along dimension dim, we detect if the
     * voronoi cells of @a u and @a w strictly hide the voronoi cell of @a v on the
     * straight line.
     *
     * If operator()(p,q) of the underlying metric is in @f$ O(m)@f$, the cost of this
     * method is @f$ O(mlog(n))@f$ (b being the number of points in [startingPoint,endPoint]).
     *
     * @pre u,v and w must be such that u[dim] < v[dim] < w[dim]
     *
     * @param u a site
     * @param v a site
     * @param w a site
     * @param startingPoint starting point of the segment
     * @param endPoint end point of the segment
     * @param dim direction of the straight line
     *
     * @return true if (u,w) hides v (strictly).
     */
    bool hiddenBy(const Point &u,
                  const Point &v,
                  const Point &w,
                  const Point &startingPoint,
                  const Point &endPoint,
                  const typename Point::UnsignedComponent dim) const;


    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const
    {
      return myMetric->isValid();
    }


    /**
     * Perform a binary search on the interval [lower,upper] to
     * detect the mid-point between u and v .
     *
     * @pre udim < vdim
     *
     * @param u a point
     * @param v a point
     * @param dim direction of the straight line
     * @param lower starting point of the segment
     * @param upper end point of the segment
     *
     * @return the u Voronoi cell greatest point coordinates along dimension dim.
     */
    Abscissa binarySearchHidden(const Point &u,
                                const Point &v,
                                const typename Point::UnsignedComponent dim,
                                const Point &lower,
                                const Point &upper) const;

    // ------------------------- Private methods ------------------------------
  private:

    // ------------------------- Private members ------------------------------
  private:
    const Metric *myMetric;

  }; // end of class SeparableMetricAdapter



  /**
   * Overloads 'operator<<' for displaying objects of class 'SeparableMetricAdapter'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'SeparableMetricAdapter' to write.
   * @return the output stream after the writing.
   */
  template <typename TM>
  std::ostream&
  operator<< ( std::ostream & out, const SeparableMetricAdapter<TM> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/distance/SeparableMetricAdapter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SeparableMetricAdapter_h

#undef SeparableMetricAdapter_RECURSES
#endif // else defined(SeparableMetricAdapter_RECURSES)
