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
 * @file StarShaped2D.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/04/12
 *
 * Header file for module StarShaped2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(StarShaped2D_RECURSES)
#error Recursive header files inclusion detected in StarShaped2D.h
#else // defined(StarShaped2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define StarShaped2D_RECURSES

#if !defined StarShaped2D_h
/** Prevents repeated inclusion of headers. */
#define StarShaped2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class StarShaped2D
  /**
   * Description of template class 'StarShaped2D' <p>
   *
   * Aim: Abstract class that represents any star-shaped object in
   * dimension 2. Such a shape as a center and any segment from this
   * center to the shape boundary is included in the shape. These
   * shapes can thus be parameterized by an angle 't' turning around
   * the center.
   *
   * StarShaped2D and its derived classes are models of
   * CEuclideanBoundedShape and CEuclideanOrientedShape.
   *
   * NB: A backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   *
   *
   * @tparam TSpace space in which the shape is defined.
   */
  template <typename TSpace>
  class StarShaped2D
  {

  public:
    typedef TSpace Space;
    typedef typename Space::Point Point;
    typedef typename Space::RealPoint RealPoint;

   /**
     * Constructor.
     */
    StarShaped2D()
    {}

    /**
     * Destructor.
     */
    ~StarShaped2D();

    // ------------------------- Implemented services -------------------------
  public:
    /**
     * @return a point p such that 'isInside(p)' returns 'true'.
     */
    virtual RealPoint interiorPoint() const
    {
      return center();
    }

    // ------------------------- Abstract services ----------------------------
  public:

    /**
     * @return the lower bound of the shape bounding box.
     *
     */
    virtual RealPoint getLowerBound() const = 0;

    /**
     * @return the upper bound of the shape bounding box.
     *
     */
    virtual RealPoint getUpperBound() const = 0;


    /**
     * @return the center of the star-shaped object.
     */
    virtual RealPoint center() const = 0;

    /**
     * @param p any point in the plane.
     *
     * @return the angle parameter between 0 and 2*Pi corresponding to
     * this point for the shape.
     */
    virtual double parameter( const RealPoint & p ) const = 0;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x(t),y(t)) which is the position on the
     * shape boundary.
     */
    virtual RealPoint x( const double t ) const = 0;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x'(t),y'(t)) which is the tangent to the
     * shape boundary.
     */
    virtual RealPoint xp( const double t ) const = 0;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x''(t),y''(t)).
     */
    virtual RealPoint xpp( const double t ) const = 0;


    // ------------------------- star-shaped services -------------------------
  public:

    /**
     * Return the orienatation of a point with respect to a shape.
     *
     * @param p input point
     *
     * @return the orientation of the point (INSIDE ON or OUTSIDE).
     */
    Orientation orientation( const RealPoint &p) const;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x'(t),y'(t)) made unitary which is the unit
     * tangent to the shape boundary.
     */
    RealPoint tangent( double t ) const;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x''(t),y''(t)) made unitary which is the unit
     * normal to the shape boundary looking inside the shape.
     */
    RealPoint normal( double t ) const;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the algebraic curvature at point (x(t),y(t)), positive
     * is convex, negative is concave when shape is to the left and
     * the shape boundary is followed counterclockwise.
     */
    double curvature( double t ) const;

    /**
     * @param t1 any angle between 0 and 2*Pi.
     * @param t2 any angle between 0 and 2*Pi, further from [t1].
     * @param nb the number of points used to estimate the arclength between x(t1) and x(t2).
     *
     * @return the estimated arclength.
     */
    double arclength( double t1, double t2, unsigned int nb ) const;

    /**
     * Return a point on the segment [inner;outer] that is at most \f$\epsilon\f$ from the shape in \f$L_2\f$ norm.
     *
     * @param inner a point that is inside the shape
     * @param outer a point that is outside the shape
     * @param epsilon error parameter
     *
     * @return the intersected point.
     */
    RealPoint findIntersection( const RealPoint& inner, const RealPoint& outer, const double epsilon ) const;

    /**
     * Return a point that lies between the projection of left and right and that is the closest regarding the \f$L_2\f$ norm
     *
     * @param p the point to be projected
     * @param left a point that is supposed to be projected left of p (regarding the angle)
     * @param right a point that is supposed to be projected right of p (regarding the angle)
     * @param step precision of the approximation
     *
     * @return a point.
     * */
    RealPoint closestPointWithWitnesses( const RealPoint& p, const RealPoint& left, const RealPoint& right, const int step) const;

    // ----------------------- Interface --------------------------------------
  public:

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
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    //StarShaped2D();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    //StarShaped2D ( const StarShaped2D & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    StarShaped2D & operator= ( const StarShaped2D & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class StarShaped2D


  /**
   * Overloads 'operator<<' for displaying objects of class 'StarShaped2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'StarShaped2D' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const StarShaped2D<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/parametric/StarShaped2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined StarShaped2D_h

#undef StarShaped2D_RECURSES
#endif // else defined(StarShaped2D_RECURSES)
