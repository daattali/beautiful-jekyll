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
 * @file ExactPredicateLpSeparableMetric.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/02
 *
 * Header file for module ExactPredicateLpSeparableMetric.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ExactPredicateLpSeparableMetric_RECURSES)
#error Recursive header files inclusion detected in ExactPredicateLpSeparableMetric.h
#else // defined(ExactPredicateLpSeparableMetric_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ExactPredicateLpSeparableMetric_RECURSES

#if !defined ExactPredicateLpSeparableMetric_h
/** Prevents repeated inclusion of headers. */
#define ExactPredicateLpSeparableMetric_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <cmath>
#include "DGtal/base/Common.h"
#include "DGtal/math/BasicMathFunctions.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/CInteger.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// template class ExactPredicateLpSeparableMetric
/**
 * Description of template class 'ExactPredicateLpSeparableMetric' <p>
   * \brief Aim: implements separable l_p metrics with  exact
   * predicates.
   *
   * Given a template parameter p, the class implement classical l_p
   * metric as a model of CSeparableMetric. Hence, given two points
   * @f$ x=(x_0...x_{n-1})@f$, @f$ y=(y_0...y_{n-1})@f$ in the given
   * digital space (see below), we define a metric such that:
   *
   * @f$ distance(x,y)= \left(
   * \sum_{i=0}^{n-1} |x_i-y_i|^p\right)^{1/p}@f$
   *
   * This class is said to be exact in the sense that the power @a p
   * is computed without approximation (exponentiation by squaring in
   * @f$ O(log(p))@f$ per computation, see
   * functions::power). As a consequence, @a hiddenBy and
   * @a closest methods are error free if the capacity of the template
   * type @a TPromoted allows to store sums of @f$ |x_i-y_i|^p@f$
   * quantities.
   *
   * @tparam TSpace the model of CSpace on which the metric is
   * defined.
   * @tparam p the exponent of the metric (static DGtal::uint32_t)
   * @tparam TRawValue model of CSignedInteger used to store power @a
   * p sums (default: DGtal::int64_t)
   *
   */
  template <typename TSpace, DGtal::uint32_t p,
            typename TRawValue=DGtal::int64_t>
  class ExactPredicateLpSeparableMetric
  {
    // ----------------------- Standard services ------------------------------
  public:
    ///Copy the space type
    typedef TSpace Space;
    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));

    ///Type for points
    typedef typename Space::Point Point;
    ///Type for points
    typedef typename Point::Coordinate Abscissa;
    ///Type for vectors
    typedef typename Space::Vector Vector;

    ///Type for internal distance values
    typedef TRawValue RawValue;
    BOOST_CONCEPT_ASSERT(( concepts::CInteger<RawValue> ));

    ///Type for distance values
    typedef double Value;

    ///Self type
    typedef ExactPredicateLpSeparableMetric<TSpace,p,RawValue> Self;

    /**
     * Constructor.
     */
    ExactPredicateLpSeparableMetric();


    /**
     * Destructor.
     */
    ~ExactPredicateLpSeparableMetric();

    /**
     * Copy constructor.
     * @param other the object to clone (not used).
     */
    ExactPredicateLpSeparableMetric ( const Self & other )
    {
      boost::ignore_unused_variable_warning( other );
    }

    /**
     * Assignment.
     * @param other other the object to copy (not used).
     * @return a reference on 'this'.
     */
    Self & operator= ( const Self & other )
    {
      boost::ignore_unused_variable_warning( other );
      return *this;
    }

    // ----------------------- Interface --------------------------------------
  public:

    // ----------------------- CMetricSpace --------------------------------------
    /**
     * Compute the distance between @a aP and @a aQ.
     *
     * @param aP a first point.
     * @param aQ a second point.
     *
     * @return the distance between aP and aQ.
     */
    Value operator()(const Point & aP, const Point &aQ) const;

    /**
     * Given an origin and two points, this method decides which one
     * is closest to the origin. This method should be faster than
     * comparing distance values.
     *
     * @param origin the origin
     * @param first  the first point
     * @param second the second point
     *
     * @return a Closest enum: FIRST, SECOND or BOTH.
     */
    Closest closest(const Point &origin,
		    const Point &first,
		    const Point &second) const;

    /**
     * Compute the raw distance between @a aP and @a aQ.
     * (i.e. @f$ \sum_{i=1}^n |x_i-y_i |^p\f$).
     * @param aP a first point.
     * @param aQ a second point.
     *
     * @return the distance between aP and aQ.
     */
    RawValue rawDistance(const Point & aP, const Point &aQ) const;

      // ----------------------- CSeparableMetric --------------------------------------
    /**
     * Given three sites (u,v,w) and a straight segment
     * [startingPoint,endPoint] along dimension dim, we detect if the
     * voronoi cells of @a u and @a w strictly hide the voronoi cell of @a v on the
     * straight line.
     *
     * This method is in @f$ O(log(n))@f$ if @a n is the size of the
     * straight segment. For @f$ l_2@f$ metric (p=2), the method is in
     * @f$ O(1)@f$.
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
    bool isValid() const;


    /**
     * Perform a binary search on the interval [lower,upper] to
     * detect the mid-point between u and v according to the l_p
     * distance. It returns the abscissa @a q such that q belongs to
     * the power cell of u (strictly) but not @a q-1.
     *
     * @pre udim < vdim
     *
     * @param udim coordinate of u along dimension dim
     * @param vdim coordinate of v along dimension dim
     * @param nu  partial distance of u (sum of |xj-x_i|^p) discarding
     * the term along the dimension dim
     * @param nv partial distance of v (sum of |xj-x_i|^p) discarding
     * the term along the dimension dim
     * @param lower interval lower bound
     * @param upper interval upper bound
     *
     * @return the u Voronoi cell greatest point coordinates along dimension dim.
     */
    Abscissa binarySearchHidden(const Abscissa &udim,
                                const Abscissa &vdim,
                                const RawValue &nu,
                                const RawValue &nv,
                                const Abscissa &lower,
                                const Abscissa &upper) const;

  }; // end of class ExactPredicateLpSeparableMetric


///////////////////////////////////////////////////////////////////////////////
//            L_2 specialization                                             //
///////////////////////////////////////////////////////////////////////////////


 template <typename TSpace,
           typename TRawValue>
 class ExactPredicateLpSeparableMetric<TSpace, 2, TRawValue>
  {
    // ----------------------- Standard services ------------------------------
  public:

    ///Copy the space type
    typedef TSpace Space;
    ///Type for points
    typedef typename Space::Point Point;
    ///Type for points
    typedef typename Point::Coordinate Abscissa;
    ///Type for vectors
    typedef typename Space::Vector Vector;

    ///Type for internal distance values
    typedef TRawValue RawValue;

    ///Type for distance values
    typedef double Value;

    ///Self type
    typedef ExactPredicateLpSeparableMetric<TSpace,2,TRawValue> Self;

    /**
     * Constructor.
     */
    ExactPredicateLpSeparableMetric();


    /**
     * Destructor.
     */
    ~ExactPredicateLpSeparableMetric();


    /**
     * Copy constructor.
     * @param  other the object to clone (not used).
     */
    ExactPredicateLpSeparableMetric ( const Self & other )
    {
      boost::ignore_unused_variable_warning( other );
    }

    /**
     * Assignment.
     * @param other the object to copy (unused).
     * @return a reference on 'this'.
     */
    Self & operator= ( const Self & other )
    {  
      boost::ignore_unused_variable_warning( other );
      return *this;
    }


    // ----------------------- Interface --------------------------------------
  public:

    // ----------------------- CLocalMetric --------------------------------------
    /**
     * Compute the local distance between @a aP and its displacement
     * along the direction @a aDir.
     *
     * @param aP a point.
     * @param aDir a direction.
     *
     * @return the distance between @a aP and @a aP+@a aDir.
     */
    Value local(const Point & aP, const Vector &aDir) const;


    // ----------------------- CMetric --------------------------------------
    /**
     * Compute the distance between @a aP and @a aQ.
     *
     * @param aP a first point.
     * @param aQ a second point.
     *
     * @return the distance between aP and aQ.
     */
    Value operator()(const Point & aP, const Point &aQ) const;

    /**
     * Given an origin and two points, this method decides which one
     * is closest to the origin. This method should be faster than
     * comparing distance values.
     *
     * @param origin the origin
     * @param first  the first point
     * @param second the second point
     *
     * @return a Closest enum: FIRST, SECOND or BOTH.
     */
    Closest closest(const Point &origin,
		    const Point &first,
		    const Point &second) const;


    /**
     * Compute an exact representation of  Lp distances. We just
     *  return the sum of powers without computing the last 1/p power.
     *  I.e. only @f$ \sum |p_i- q_i|^p@f$ is given.
     *
     * @param aP a first point
     * @param aQ a second point
     *
     * @return the power p of the l_p distance between aP and aQ.
     */
    RawValue rawDistance(const Point &aP, const Point &aQ) const;

    // ----------------------- CSeparableMetric --------------------------------------
    /**
     * Given three sites (a,b,c) and a straight segment
     * [startingPoint,endPoint] along dimension dim, we detect if the
     * voronoi cells of a and c @e hide the voronoi cell of c on the
     * straight line.
     *
     * @pre both voronoi cells associated with @a a and @a b must
     * intersect the straight line.
     *
     * @param u a site
     * @param v a site
     * @param w a site
     * @param startingPoint starting point of the segment
     * @param endPoint end point of the segment
     * @param dim direction of the straight line
     *
     * @return true if (a,c) hides b.
     */
    bool hiddenBy(const Point &u,
                  const Point &v,
                  const Point &w,
                  const Point &startingPoint,
                  const Point &endPoint,
                  const typename Point::UnsignedComponent dim) const;

   // ----------------------- Other services --------------------------------------
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


     /**
     * Perform a binary search on the interval [lower,upper] to
     * detect the mid-point between u and v according to the l_p
     * distance.
     *
     * @param udim coordinate of u along dimension dim
     * @param vdim coordinate of v along dimension dim
     * @param nu  partial distance of u (sum of |xj-x_i|^p) discarding
     * the term along the dimension dim
     * @param nv partial distance of v (sum of |xj-x_i|^p) discarding
     * the term along the dimension dim
     * @param lower interval lower bound
     * @param upper interval upper bound
     *
     * @return the Voronoi boundary point coordinates along dimension dim.
     */
    Abscissa binarySearchHidden(const Abscissa &udim,
                                const Abscissa &vdim,
                                const RawValue &nu,
                                const RawValue &nv,
                                const Abscissa &lower,
                                const Abscissa &upper) const;


  }; // end of class ExactPredicateLpSeparableMetric

  /**
   * Overloads 'operator<<' for displaying objects of class 'ExactPredicateLpSeparableMetric'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ExactPredicateLpSeparableMetric' to write.
   * @return the output stream after the writing.
   */
  template <typename T, DGtal::uint32_t p, typename P>
  std::ostream&
  operator<< ( std::ostream & out, const ExactPredicateLpSeparableMetric<T,p,P> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ExactPredicateLpSeparableMetric_h

#undef ExactPredicateLpSeparableMetric_RECURSES
#endif // else defined(ExactPredicateLpSeparableMetric_RECURSES)
