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
 * @file InexactPredicateLpSeparableMetric.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/11/02
 *
 * Header file for module InexactPredicateLpSeparableMetric.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(InexactPredicateLpSeparableMetric_RECURSES)
#error Recursive header files inclusion detected in InexactPredicateLpSeparableMetric.h
#else // defined(InexactPredicateLpSeparableMetric_RECURSES)
/** Prevents recursive inclusion of headers. */
#define InexactPredicateLpSeparableMetric_RECURSES

#if !defined InexactPredicateLpSeparableMetric_h
/** Prevents repeated inclusion of headers. */
#define InexactPredicateLpSeparableMetric_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <cmath>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/CEuclideanRing.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// template class InexactPredicateLpSeparableMetric
/**
 * Description of template class 'InexactPredicateLpSeparableMetric' <p>
 * \brief Aim: implements separable l_p metrics with  approximated
 * predicates.
 *
 * Given a parameter p, the class implement classical l_p
 * metric as a model of CSeparableMetric. Hence, given two points
 * @f$ x=(x_0...x_{n-1})@f$, @f$ y=(y_0...y_{n-1})@f$ in the given digital space (see
 * below), we define a metric such that:
 *
 * @f$ distance(x,y)= \left(
 * \sum_{i=0}^{n-1} |x_i-y_i|^p\right)^{1/p}@f$
 *
 * This class is said to be inexact in the sense that the power @a p a
 * real number (of type TValue, e.g. @a double or @a float) and the power is given by std::pow on
 * double numbers. As a consequence, @a hiddenBy and @a closest
 * methods may be inexact (numerical issues).
 *
 * The exponent @a p is specifed at the constructor.
 *
 * @tparam TSpace the model of CSpace on which the metric is
 * defined.
 * @tparam TValue value type of the distance computation (e.g. float
 * or double --defaut--). Model of CEuclideanRing.
 */
  template <typename TSpace, typename TValue = double>
  class InexactPredicateLpSeparableMetric
  {
    // ----------------------- Standard services ------------------------------
  public:

    ///Copy the space type
    typedef TSpace Space;

    BOOST_CONCEPT_ASSERT(( concepts::CSpace<TSpace> ));
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<TValue> ));

    ///Type for points
    typedef typename Space::Point Point;
    ///Type for points
    typedef typename Point::Coordinate Abscissa;
    ///Type for vectors
    typedef typename Space::Vector Vector;
    ///Type for distance values
    typedef TValue Value;
    ///Type for raw distance values
    typedef TValue RawValue;
    
    /**
     * Constructor.
     */
    InexactPredicateLpSeparableMetric( const double anExponent );


    /**
     * Destructor.
     */
    ~InexactPredicateLpSeparableMetric();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    InexactPredicateLpSeparableMetric ( const InexactPredicateLpSeparableMetric & other )
    {
      myExponent = other.myExponent;
    }

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    InexactPredicateLpSeparableMetric & operator= ( const InexactPredicateLpSeparableMetric & other )
    {
      myExponent = other.myExponent;
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
    Value operator()(const Point & aP, const Point &aQ) const;

    /**
     * Compute the raw distance between @a aP and @a aQ.
     *
     * @param aP a first point.
     * @param aQ a second point.
     *
     * @return the distance between aP and aQ.
     */
    RawValue rawDistance(const Point & aP, const Point &aQ) const;

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

      // ----------------------- CSeparableMetric --------------------------------------
    /**
     * Given three sites (u,v,w) and a straight segment
     * [startingPoint,endPoint] along dimension dim, we detect if the
     * voronoi cells of @a u and @a w strictly hide the voronoi cell of @a v on the
     * straight line.
     *
     * This method is in @f$ O(log(n))@f$ if @a n is the size of the
     * straight segment.
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

    // ------------------------- Protected Datas ------------------------------
  private:

    /**
     * Compute the Lp distance without the computation of the power
     * 1/p. I.e. only @f$ \sum |p_i- q_i|^p@f$ is given.
     *
     * @param aP a first point
     * @param aQ a second point
     *
     * @return the power p of the l_p distance between aP and aQ.
     */
    Value distanceLp(const Point &aP, const Point &aQ) const;


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
                                const Value &nu,
                                const Value &nv,
                                const Abscissa &lower,
                                const Abscissa &upper) const;


    // ------------------------- Private Datas --------------------------------
  private:

    ///Exponent value
    Value myExponent;

  }; // end of class InexactPredicateLpSeparableMetric

  /**
   * Overloads 'operator<<' for displaying objects of class 'InexactPredicateLpSeparableMetric'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'InexactPredicateLpSeparableMetric' to write.
   * @return the output stream after the writing.
   */
  template <typename T, typename V>
  std::ostream&
  operator<< ( std::ostream & out, const InexactPredicateLpSeparableMetric<T,V> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/volumes/distance/InexactPredicateLpSeparableMetric.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined InexactPredicateLpSeparableMetric_h

#undef InexactPredicateLpSeparableMetric_RECURSES
#endif // else defined(InexactPredicateLpSeparableMetric_RECURSES)
