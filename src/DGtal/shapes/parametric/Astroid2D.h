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
 * @file Astroid2D.h
 * @author Chouaib Fellah, Adrien Krähenbühl (\c krahenbuhl@unistra.fr )
 * Laboratoire des sciences de l'ingénieur, de l'informatique et de l'imagerie - ICube (UMR 7357), France
 *
 * @date 2018/06/12
 *
 * Header file for module Astroid2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Astroid2D_RECURSES)
#error Recursive header files inclusion detected in Astroid2D.h
#else // defined(Astroid2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Astroid2D_RECURSES

#if !defined Astroid2D_h
/** Prevents repeated inclusion of headers. */
#define Astroid2D_h

///////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <DGtal/base/Common.h>
#include <DGtal/shapes/parametric/StarShaped2D.h>
#include <cmath>
///////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Astroid2D
  /**
   * Description of template class 'Astroid2D' <p>
   * \brief Aim: Model of the concept StarShaped
   * represents an astroid.
   *
   */
  template <typename TSpace>
  class Astroid2D : public StarShaped2D<TSpace>
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TSpace Space;
    typedef typename Space::Point Point2D;
    typedef typename Space::RealPoint RealPoint2D;
    typedef typename Space::RealVector RealVector2D;

    /**
     * Destructor.
     */
    ~Astroid2D();

    /**
     * Constructor.
     * @param x0 the x-coordinate of the astroid center.
     * @param y0 the y-coordinate of the astroid center.
     * @param a  coefficient along x-axis
     * @param b  coefficient along y-axis
     */
   Astroid2D( const double x0, const double y0,
              const double a, const double b );

    /**
     * Constructor.
     * @param aPoint the astroid center
     * @param a      coefficient along x-axis
     * @param b      coefficient along y-axis
     */
    Astroid2D( const RealPoint2D &aPoint, const double a, const double b );

     /**
      * Constructor.
      * @param aPoint the astroid center
      * @param a      coefficient along x-axis
      * @param b      coefficient along y-axis
      */
    Astroid2D( const Point2D &aPoint, const double a, const double b );


   // ------------- Implementation of 'StarShaped' services -------------------
    public:

    /**
     * @return the lower bound of the shape bounding box.
     *
     */
    RealPoint2D getLowerBound() const
    {
      return RealPoint2D(-myA - myCenter[0] , -myB - myCenter[1] );
    }

    /**
     * @return the upper bound of the shape bounding box.
     *
     */
    RealPoint2D getUpperBound() const
    {
      return RealPoint2D(myA - myCenter[0] , myB - myCenter[1]);
    }

    /**
     * @return the center of the star-shaped object.
     */
    RealPoint2D center() const
    {
      return myCenter;
    }

    /**
     * @param p any point in the plane.
     *
     * @return the angle parameter between 0 and 2*Pi corresponding to
     * this point for the shape.
     */
    double parameter( const RealPoint2D & p ) const;


    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x(t),y(t)) which is the position on the
     * shape boundary.
     */
    RealPoint2D x( const double t ) const;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x'(t),y'(t)) which is the tangent to the
     * shape boundary.
     */
    RealVector2D xp( const double t ) const;

    /**
     * @param t any angle between 0 and 2*Pi.
     *
     * @return the vector (x''(t),y''(t)).
     */
    RealVector2D xpp( const double t ) const;


    // ------------------------- data -----------------------------------------
  private:

    /**
     * Center of the circle.
     */
    RealPoint2D myCenter;

    /**
     * Coefficient along x-axis
     */
    double myA;

    /**
     * Coefficient along y-axis
     */
    double myB;

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


    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    Astroid2D();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    //  Astroid2D ( const Astroid2D & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Astroid2D & operator= ( const Astroid2D & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Astroid2D



  /**
   * Overloads 'operator<<' for displaying objects of class 'Astroid2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Astroid2D' to write.
   * @return the output stream after the writing.
   */
   template <typename T>
   std::ostream&
   operator<< ( std::ostream & out, const Astroid2D<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/parametric/Astroid2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Astroid2D_h

#undef Astroid2D_RECURSES
#endif // else defined(Astroid2D_RECURSES)
