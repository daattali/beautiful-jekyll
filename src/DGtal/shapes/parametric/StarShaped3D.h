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
 * along with this program. If not, see <http:/www.gnu.org/licenses/>.
 *
 **/

#pragma once

/**
 * @file StarShaped3D.h
 * @author Anis Benyoub (\c anis.benyoub@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/06/05
 *
 * Header file for module StarShaped3D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(StarShaped3D_RECURSES)
#error Recursive header files inclusion detected in StarShaped3D.h
#else // defined(StarShaped3D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define StarShaped3D_RECURSES

#if !defined StarShaped3D_h
/** Prevents repeated inclusion of headers. */
#define StarShaped3D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class StarShaped3D
  /**
   * Description of template class 'StarShaped3D' <p>
   *
   * Aim: Abstract class that represents any star-shaped object in
   * dimension 3. Such a shape as a center and any segment from this
   * center to the shape boundary is included in the shape. These
   * shapes can thus be parameterized by a couple of angles 'Teta,Phi' turning around
   * the center.
   *
   * StarShaped3D and its derived classes are models of
   * CEuclideanBoundedShape and CEuclideanOrientedShape.
   *
   * NB: A backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   *
   *
   * @tparam TSpace space in which the shape is defined.
   */
  template <typename TSpace>
  class StarShaped3D
  {
   
  public:
    typedef TSpace Space;
    typedef typename Space::RealPoint RealPoint;
    typedef std::pair<double,double> AngularCoordinates;
     
    /**
     * Constructor.
     */
    StarShaped3D()
    {}

    /**
     * Destructor.
     */
    ~StarShaped3D();
    
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
     * @param p any point in the sapce.
     *
     * @return the angles parameters (Teta, Phi) corresponding to
     * this point for the shape.
     */
    virtual AngularCoordinates parameter( const RealPoint & p ) const = 0;

    /**
     * @param t is a couple of Theta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (x(t),y(t),z(t)) which is the position on the
     * shape boundary.
     */
    virtual RealPoint x( const AngularCoordinates t ) const = 0;

    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (gradf(M).
     */
    virtual RealPoint gradient( const AngularCoordinates t) const = 0;

    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (rt(M)) wich is the partial derivative with respect to Teta.
     */
    virtual RealPoint rt( const AngularCoordinates t) const = 0;



    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (rp(M)) wich is the first partial derivative with respect to Phi.
     */
    virtual RealPoint rp( const AngularCoordinates t) const = 0;


    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (rtt(M)) wich is second the partial
     * derivative with respect to Teta(twice).
     */
    virtual RealPoint rtt( const AngularCoordinates t) const = 0;



    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (rpp(M)) wich is second the partial
     * derivative with respect to Phi.
     */
    virtual RealPoint rpp( const AngularCoordinates t) const = 0;

    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (rpp(M)) wich is second the partial
     * derivative with respect to Teta then Phi.
     */
    virtual RealPoint rtp( const AngularCoordinates t) const = 0;




    // ------------------------- star-shaped services -------------------------
  public:

    /**
     * Return the orienatation of a point with respect to a shape.
     *
     * @param p input point
     *
     * @return the orientation of the point (<0 means inside, ...)
     */
    virtual Orientation orientation( const RealPoint &p) const;
    
    
    /*
     * @param t is a couple of Teta && Phi wich are 2 angles
     respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector (x'(t),y'(t),z'(t)) made unitary which is
     * the unit tangent to the shape boundary.
     */
    /*
      virtual RealPoint tangent( AngularCoordinates t ) const;
    */
   
   


    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the vector normal made unitary which is the unit
     * normal to the shape boundary looking inside the shape.
     */
    virtual RealPoint normal( AngularCoordinates t ) const;

    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     *
     * @return the gaussian curvature at point (x(t),y(t)), positive
     * is convex, negative is concave when shape is to the left and
     * the shape boundary is followed counterclockwise.
     */
    virtual double gaussianCurvature( AngularCoordinates t) const;


    /**
     * @param t is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi]
     *
     * @return the mean curvature at point (x(t),y(t)), positive
     * is convex, negative is concave when shape is to the left and
     * the shape boundary is followed counterclockwise.
     */
    virtual double meanCurvature( AngularCoordinates t) const;


    /**
     * @param t1 is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     * @param t2 is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi]. further from
     * [t1].
     * @param nb the number of points used to estimate the arclength
     * between x(Teta1,Phi1) and x(Teta2,Phi2).
     * @return the estimated arclength.
     */
    virtual double arclength( AngularCoordinates t1,
                              AngularCoordinates t2,
                              unsigned int nb ) const;


    /**
     * @param t1 is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi].
     * @param t2 is a couple of Teta && Phi wich are 2 angles
     * respectivly between [0,2PI] and [0,Pi]. further from
     * [t1].
     * @param nb the number of points used to estimate the surface
     * between x(Teta1,Phi1) and x(Teta2,Phi2).
     * @return the estimated surfacelength.
     */
    virtual double surfacelength( AngularCoordinates t1,
                                  AngularCoordinates t2,
                                  unsigned int nb ) const;



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
    //StarShaped3D();

  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    StarShaped3D & operator= ( const StarShaped3D & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class StarShaped3D


  /**
   * Overloads 'operator<<' for displaying objects of class 'StarShaped3D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'StarShaped2D' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const StarShaped3D<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "StarShaped3D.ih"

// //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined StarShaped3D_h

#undef StarShaped3D_RECURSES
#endif // else defined(StarShaped3D_RECURSES)
