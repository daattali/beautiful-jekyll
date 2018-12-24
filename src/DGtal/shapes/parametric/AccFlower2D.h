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
 * @file AccFlower2D.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/04/12
 *
 * Header file for module AccFlower2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(AccFlower2D_RECURSES)
#error Recursive header files inclusion detected in AccFlower2D.h
#else // defined(AccFlower2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define AccFlower2D_RECURSES

#if !defined AccFlower2D_h
/** Prevents repeated inclusion of headers. */
#define AccFlower2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/shapes/parametric/StarShaped2D.h"
#include <cmath>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class AccFlower2D
  /**
   * Description of template class 'AccFlower2D' <p>
   * \brief Aim: Model of the concept StarShaped
   * represents any accelerated flower in the plane.
   *
   * NB: A backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   */
  template <typename TSpace>
  class AccFlower2D final:  public StarShaped2D<TSpace>
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TSpace Space;
    typedef typename Space::Point Point;
    typedef typename Space::RealPoint RealPoint2D;
    typedef typename Space::RealVector RealVector2D;
    
    /**
     * Destructor.
     */
    ~AccFlower2D();
    
    /**
     * Constructor. 
     * @param x0 the x-coordinate of the flower center.
     * @param y0 the y-coordinate of the flower center.
     * @param r the radius of the flower.
     * @param smallr the variable small radius of the flower.
     * @param k the number of flower extremeties.
     * @param phi the phase of the flower (in radian).
     */
    AccFlower2D( const double x0, const double y0, 
        const double r,
        const double smallr,
        const unsigned int k,
        const double phi);

    /**
     * Constructor. 
     * @param aPoint the flower center.
     * @param r the radius of the flower.
     * @param smallr the variable small radius of the flower.
     * @param k the number of flower extremeties.
     * @param phi the phase of the flower (in radian).
     */
    AccFlower2D(const RealPoint2D &aPoint, 
       const double r,
       const double smallr,
       const unsigned int k,
       const double phi);

    /**
     * Constructor. 
     * @param aPoint the flower center.
     * @param r the radius of the flower.
     * @param smallr the variable small radius of the flower.
     * @param k the number of flower extremeties.
     * @param phi the phase of the flower (in radian).
     */
    AccFlower2D(const Point &aPoint, 
       const double r,
       const double smallr,
       const unsigned int k,
       const double phi);

    
    // ------------- Implementation of 'StarShaped' services ------------------
  public:

    /**
     * @return the lower bound of the shape bounding box.
     *
     */
    RealPoint2D getLowerBound() const
    {
      return RealPoint2D(myCenter[0] - myRadius - myVarRadius, 
                         myCenter[1] - myRadius - myVarRadius);
    }

    /**
     * @return the upper bound of the shape bounding box.
     *
     */
    RealPoint2D getUpperBound() const
    {
      return RealPoint2D(myCenter[0] + myRadius + myVarRadius,
                         myCenter[1] + myRadius + myVarRadius);
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
    

    // ------------------------- data ----------------------------
  private:

    /**
     * Center of the flower.
     */
    RealPoint2D myCenter;
    
    /**
     * Radius of the flower.
     */
    double myRadius;
    
    /**
     * the variable small radius of the flower.
     */
    double myVarRadius;
    
    /**
     * the number of flower extremeties.
     */
    unsigned int myK;
    
    /**
     * The value 2*myK*Pi/(Pi^3)
     */
    double myKp;
    
    /**
     * the phase of the flower (in radian).
     */
    double myPhi;

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
    AccFlower2D();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    //  AccFlower2D ( const AccFlower2D & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    AccFlower2D & operator= ( const AccFlower2D & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class AccFlower2D


  /**
   * Overloads 'operator<<' for displaying objects of class 'AccFlower2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'AccFlower2D' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const AccFlower2D<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/parametric/AccFlower2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined AccFlower2D_h

#undef AccFlower2D_RECURSES
#endif // else defined(AccFlower2D_RECURSES)
