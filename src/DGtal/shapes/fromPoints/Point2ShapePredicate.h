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
 * @file Point2ShapePredicate.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/10/27
 *
 * @brief Header file for module Point2ShapePredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Point2ShapePredicate_RECURSES)
#error Recursive header files inclusion detected in Point2ShapePredicate.h
#else // defined(Point2ShapePredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Point2ShapePredicate_RECURSES

#if !defined Point2ShapePredicate_h
/** Prevents repeated inclusion of headers. */
#define Point2ShapePredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <functional>

#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

  /////////////////////////////////////////////////////////////////////////////
  // template class Point2ShapePredicate
  /**
   * \brief Aim: Predicate returning 'true' iff a given point is in 
   * the 'interior' of a given shape, 'false' otherwise
   *
   * @tparam TSurface  a type that is a model of COrientableHypersurface.
   * Must separate the space in two disjoints parts (the 'interior' and the 'exterior')
   * and must be able to return for any given point (of type TSurface::Point) 
   * the signed distance to itself (of type TSurface::Distance) by a method called signedDistance() 
   * @tparam isUpward  a bool for the orientation ('true' means that the interior 
   * is the set of points of positive distance)
   * @tparam isClosed  a bool for the closure ('true' means that the surface is included)
   *
   * For instance, in 2d, you can define four shapes from one straight line of equation @f$ y = ax + b @f$:
   - the set @f$ \{(x,y) | y > ax + b \} @f$  
   -  @f$ \{(x,y) | y \geq ax + b \} @f$ 
   -  @f$ \{(x,y) | y < ax + b \} @f$ 
   -  @f$ \{(x,y) | y \leq ax + b \} @f$
   *
   * The second set can be defined as follows: 
   * @snippet shapes/testHalfPlane.cpp HalfPlaneTypedefUpClosed
   *
   * Then, you can create and use your half-plane as shown below:
   * @snippet shapes/testHalfPlane.cpp HalfPlaneUsage
   * 
   * You should get: 
   @code
  [Point2ShapePredicate] :
[StraightLine] passing through:
[PointVector] {0, 0}[PointVector] {5, 2}
(upward oriented, closed)

  Does [PointVector] {2, 0} belongs to hp (no)?
  no
   @endcode
   *
   * This class is a model of concepts::CPointPredicate.
   *
   * @see testHalfPlane.cpp
   */
  template <typename TSurface, bool isUpward, bool isClosed>
  class Point2ShapePredicate
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef typename TSurface::Point Point;
    typedef typename TSurface::Distance Distance; 
  
  /**
     * Constructor.
     * @param aSurface any Surface
     */
    Point2ShapePredicate(const TSurface& aSurface);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Point2ShapePredicate ( const Point2ShapePredicate & other );

   /**
     * @param p any point.
     * @return true iff @a p is in the interior of the shape.
     */
    bool operator()( const Point & p ) const;

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;


    /**
     * Destructor. Does nothing
     */
    ~Point2ShapePredicate();


    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * The surface with respect to the points have to be located
     */
    TSurface myS;
    // ------------------------- Hidden services ------------------------------
  protected:


  private:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Point2ShapePredicate

//////////////////////////////////////////////////////////////////////////////
// policy classes for Point2ShapePredicate
/////////////////////////////////////////////////////////////////////////////
// template class Point2ShapePredicateComparator
/**
 * \brief Aim: A small struct with an operator 
 * that compares two values according to two 
 * bool template parameters.
 *
 * @tparam T  type for a signed quantity that is comparable
 * @tparam b1  a bool for the comparison sign ('true' for >, 'false' for <)
 * @tparam b2  a bool for the equality ('true' for a large inequality, 'false' for a strict inequality)
 *
 * NB: only specialized versions should be used.
 * 
 * @see Point2ShapePredicate
 */
template <typename T, bool b1, bool b2>
struct Point2ShapePredicateComparator {
  /**
  * Compares two values.
  * @param q  left value.
  * @param t  right value.
  * @return 'true' if @a q < @a t, 'false' otherwise
  */
  bool operator()(const T& q, 
                   const T& t) const {
    std::less<T> c;
    return c(q,t);
  }
};

/**
 * \brief Aim: A small struct with an operator 
 * that compares two values (<).
 *
 * @tparam T  type for a signed quantity that is comparable
 *  
 * @see Point2ShapePredicate
 */
template <typename T>
struct Point2ShapePredicateComparator<T,false,false> {
  /**
  * Compares two values.
  * @param q  left value.
  * @param t  right value.
  * @return 'true' if @a q < @a t, 'false' otherwise
  */
  bool operator()(const T& q, 
                   const T& t) const {
    std::less<T> c;
    return c(q,t);
  }
};
/**
 * \brief Aim: A small struct with an operator 
 * that compares two values (<=).
 *
 * @tparam T  type for a signed quantity that is comparable
 *  
 * @see Point2ShapePredicate
 */
template <typename T>
struct Point2ShapePredicateComparator<T,false,true> {
  /**
  * Compares two values.
  * @param q  left value.
  * @param t  right value.
  * @return 'true' if @a q <= @a t, 'false' otherwise
  */
  bool operator()(const T& q, 
                   const T& t) const {
    std::less_equal<T> c;
    return c(q,t);
  }
};
/**
 * \brief Aim: A small struct with an operator 
 * that compares two values (>).
 *
 * @tparam T  type for a signed quantity that is comparable
 *  
 * @see Point2ShapePredicate
 */
template <typename T>
struct Point2ShapePredicateComparator<T,true,false> {
  /**
  * Compares two values.
  * @param q  left value.
  * @param t  right value.
  * @return 'true' if @a q > @a t, 'false' otherwise
  */
  bool operator()(const T& q, 
                   const T& t) const {
    std::greater<T> c;
    return c(q,t);
  }
};
/**
 * \brief Aim: A small struct with an operator 
 * that compares two values (>=).
 *
 * @tparam T  type for a signed quantity that is comparable
 *  
 * @see Point2ShapePredicate
 */
template <typename T>
struct Point2ShapePredicateComparator<T,true,true> {
  /**
  * Compares two values.
  * @param q  left value.
  * @param t  right value.
  * @return 'true' if @a q >= @a t, 'false' otherwise
  */
  bool operator()(const T& q, 
                   const T& t) const {
    std::greater_equal<T> c;
    return c(q,t);
  }
};

} // namespace functors

/**
 * Overloads 'operator<<' for displaying objects of class 'Point2ShapePredicate'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'Point2ShapePredicate' to write.
 * @return the output stream after the writing.
 */
template <typename TSurface, bool isUpward, bool isClosed>
inline
std::ostream&
operator<< ( std::ostream & out, 
             const DGtal::functors::Point2ShapePredicate<TSurface,isUpward,isClosed> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/fromPoints/Point2ShapePredicate.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Point2ShapePredicate_h

#undef Point2ShapePredicate_RECURSES
#endif // else defined(Point2ShapePredicate_RECURSES)
