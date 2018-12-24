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
 * @file ImplicitHyperCube.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/03/22
 *
 * Header file for module ImplicitHyperCube.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImplicitHyperCube_RECURSES)
#error Recursive header files inclusion detected in ImplicitHyperCube.h
#else // defined(ImplicitHyperCube_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImplicitHyperCube_RECURSES

#if !defined ImplicitHyperCube_h
/** Prevents repeated inclusion of headers. */
#define ImplicitHyperCube_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   * Description of template class 'ImplicitHyperCube' <p> \brief Aim:
   * model of CEuclideanOrientedShape and CEuclideanBoundedShape
   * concepts to create an hypercube in nD..
   *
   * @tparam TSpace the Digital space definition.
   */
  template <typename TSpace>
  class ImplicitHyperCube
  {

  public:
    typedef ImplicitHyperCube<TSpace> Self;
    typedef TSpace Space;
    typedef typename Space::RealPoint RealPoint;
    typedef double Value;

    /** 
     * Constructor. Contructs a ball with center aCenter and width
     * aWidth.
     * 
     * @param aCenter the cube center. 
     * @param aHalfWidth the cube half-width.
     */
    ImplicitHyperCube(const RealPoint &aCenter, const double &aHalfWidth): 
      myCenter(aCenter),
      myHalfWidth(aHalfWidth)
    {};
    
    /** 
     * Destructor.
     * 
     */    
    ~ImplicitHyperCube();


    // ----------------------- Interface --------------------------------------
  public:
    
    /** 
     * Operator() of the implicit function. Given a point, it returns
     * the function value at p. In Shapes, positive values are used to
     * construct a set.
     * 
     * @param aPoint the point to evalute the function at.
     * @return the distance of aPoint to the ball center.
     */
    inline
    double operator()(const RealPoint &aPoint) const
    {
      return  myHalfWidth - (aPoint - myCenter ).norm(RealPoint::L_infty);
    }


    /** 
     * Return true if the given point belongs to the shape.
     * 
     * @param aPoint the point to evalute the function at.
     * @return the distance of aPoint to the ball center.
     */
    inline
    bool isInside(const RealPoint &aPoint) const
    {
      return this->operator()(aPoint) >0.0;
    }


    inline
    Orientation orientation(const RealPoint &aPoint) const
    {
      if (this->operator()(aPoint) > 0.0)
        return INSIDE;
      else
        if (this->operator()(aPoint) < 0.0)
          return OUTSIDE;
        else
          return ON;
    }

    /** 
     * Returns the lower bound of the Shape bounding box.
     * 
     * 
     * @return the lower bound point.
     */
    inline
    RealPoint getLowerBound() const
    {
      return (myCenter - RealPoint::diagonal(myHalfWidth));
    }
    
    /** 
     * Returns the upper bound of the Shape bounding box.
     * 
     * 
     * @return the upper bound point.
     */
    inline
    RealPoint getUpperBound() const
    {
      return (myCenter + RealPoint::diagonal(myHalfWidth)); 
    }
    

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
   
    ///Ball center
    RealPoint myCenter;

    ///Ball HalfWidth
    double myHalfWidth;
   
    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    ImplicitHyperCube();

  private:

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    ImplicitHyperCube & operator= ( const ImplicitHyperCube & other );
    
    
  }; // end of class ImplicitHyperCube


  /**
   * Overloads 'operator<<' for displaying objects of class 'ImplicitHyperCube'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImplicitHyperCube' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const ImplicitHyperCube<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/implicit/ImplicitHyperCube.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImplicitHyperCube_h

#undef ImplicitHyperCube_RECURSES
#endif // else defined(ImplicitHyperCube_RECURSES)
