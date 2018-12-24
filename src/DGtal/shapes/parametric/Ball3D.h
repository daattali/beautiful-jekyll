/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file Ball3D.h
 * @author Anis Benyoub (\c anis.benyoub@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/05
 *
 * Header file for module Ball3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Ball3D_RECURSES)
#error Recursive header files inclusion detected in Ball3D.h
#else // defined(Ball3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Ball3D_RECURSES

#if !defined Ball3D_h
/** Prevents repeated inclusion of headers. */
#define Ball3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "StarShaped3D.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Ball3D
  /**
   * Description of template class 'Ball3D' <p>
   * \brief Aim: Model of the concept StarShaped3D
   * represents any Sphere in the space.
   *
   */
  template <typename TSpace>
  class Ball3D final: public StarShaped3D<TSpace>
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TSpace Space;
    typedef typename Space::RealPoint RealPoint;
    typedef std::pair<double,double> AngularCoordinates;
   
    /**
     * Destructor.
     */
    ~Ball3D();
    
    /**
     * Constructor.
     * @param x0 the x-coordinate of the sphere center.
     * @param y0 the y-coordinate of the sphere center.
     * @param z0 the z-coordinate of the sphere center.
     * @param r the radius of the sphere.
     */
    Ball3D( const double x0, const double y0, const double z0, const double r );

    /**
     * Constructor.
     * @param aPoint the sphere center.
     * @param r the radius of the sphere.
     */
    Ball3D(const RealPoint &aPoint, const double r);

    
    /*
     * Constructor.
     * @param aPoint the sphere center.
     * @param r the radius of the sphere.
     */
    /*
      Ball3D(const Point &aPoint, const double r);
    */
    
    // ------------- Implementation of 'StarShaped' services ------------------
  public:

    /**
     * @return the lower bound of the sphere.
     *
     */
    RealPoint getLowerBound() const
    {

      return RealPoint(myCenter[0] - myRadius,
                       myCenter[1] - myRadius ,
                       myCenter[2] - myRadius );
    }

    /**
     * @return the upper bound of the sphere.
     *
     */
    RealPoint getUpperBound() const
    {
      return RealPoint(myCenter[0] + myRadius ,
                       myCenter[1] + myRadius,
                       myCenter[2] + myRadius);
    }

    /**
     * @return the center of the sphere.
     */
    RealPoint center() const
    {
      return myCenter;
    }
   
    /**
     * @param p any point in the space.
     *
     * @return the couple of angles parameters Teta && Phi which are
     * respectivly between [-Pi/2,Pi/2) and [-Pi,Pi] corresponding to
     * this point for the shape.
     */
    AngularCoordinates parameter( const RealPoint & p ) const;


    
    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (x(t),y(t),z(t)) which is the position on the
     * shape boundary.
     */
    RealPoint x( const AngularCoordinates t ) const;




    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (gradf(M)).
     */
    virtual RealPoint gradient( const AngularCoordinates t) const ;

    
    
    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (rt(M)) wich is the partial derivative with respect to Teta.
     */
    virtual RealPoint rt( const AngularCoordinates t) const ;



    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (rp(M)) wich is the partial derivative with respect to Phi.
     */
    virtual RealPoint rp( const AngularCoordinates t) const ;


    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (rtt(M)) wich is second the partial derivative with respect to Teta (twice).
     */
    virtual RealPoint rtt( const AngularCoordinates t) const ;



    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (rpp(M)) wich is second the partial derivatif with respect to Phi (twice).
     */
    virtual RealPoint rpp( const AngularCoordinates t) const ;
    

    /**
     * @param t is a couple of Teta && Phi wich are respectivly between [-Pi/2,Pi/2) and [-Pi,Pi].
     *
     * @return the vector (rpp(M)) wich is second the partial derivative with respect to Teta then Phi.
     */
    virtual RealPoint rtp( const AngularCoordinates t) const ;
    
    
    
    
    // ------------------------- data ----------------------------
  private:

     /**
     * Radius of the sphere.
     */
    double myRadius;

    /**
     * Center of the sphere.
     */
    RealPoint myCenter;
    
   
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
    Ball3D();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    // Ball3D ( const Ball3D & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Ball3D & operator= ( const Ball3D & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Ball3D


  /**
   * Overloads 'operator<<' for displaying objects of class 'Ball3D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Ball3D' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const Ball3D<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "Ball3D.ih"

// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Ball3D_h

#undef Ball3D_RECURSES
#endif // else defined(Ball3D_RECURSES)
