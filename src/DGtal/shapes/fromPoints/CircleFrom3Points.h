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
 * @file CircleFrom3Points.h
 * @brief Representation of a CircleFrom3Points uniquely defined by two 2D points.
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/22
 *
 * @brief Header file for module CircleFrom3Points.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CircleFrom3Points_RECURSES)
#error Recursive header files inclusion detected in CircleFrom3Points.h
#else // defined(CircleFrom3Points_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CircleFrom3Points_RECURSES

#if !defined CircleFrom3Points_h
/** Prevents repeated inclusion of headers. */
#define CircleFrom3Points_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // template class CircleFrom3Points
  /**
   * \brief Aim: Represents a circle uniquely
   * defined by three 2D points and that is able
   * to return for any given 2D point its signed distance to itself
   *
   * @tparam TPoint  a type of points.
   */
  template <typename TPoint>
  class CircleFrom3Points
  {

    BOOST_STATIC_ASSERT(( TPoint::dimension == 2 ));

    // ----------------------- associated types ------------------------------
  public:

    typedef typename TPoint::Coordinate Coordinate;
    typedef Coordinate Distance; //to promote
    typedef TPoint Point;
    typedef TPoint Vector;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     */
    CircleFrom3Points();


    /**
     * Constructor.
     * @param aFirstPoint  a point
     * @param aSecondPoint  a second point
     * @param aThirdPoint  a third point
     */
    CircleFrom3Points(const Point& aFirstPoint, const Point& aSecondPoint, const Point& aThirdPoint);

    /**
     * Init.
     * @param aFirstPoint  a point
     * @param aSecondPoint  a second point
     * @param aThirdPoint  a third point
     */
    void init(const Point& aFirstPoint, const Point& aSecondPoint, const Point& aThirdPoint);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CircleFrom3Points ( const CircleFrom3Points & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    CircleFrom3Points & operator= ( const CircleFrom3Points & other );


    /**
     * Destructor. Does nothing
     */
    ~CircleFrom3Points();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Computes the signed distance of @e aP to the circle
     * @param aP the point to be tested.
     * @return the signed distance.
     */
    Distance signedDistance(const Point& aP) const;

    //------------------ accessors -------------------------------
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /**
     * Computes the parameters of the circle
     * @param cx  returned x-coordinate of the circle
     * @param cy  returned y-coordinate of the circle
     * @param rr  returned radius of the circle
     */

    void getParameters(double& cx, double& cy, double& rr) const;

    /**
     * @return circle curvature
     */
    double getCurvature() const;

    /**
     * @return the first point through which the circle passes.
     */
    const Point & p() const
    {
      return myP;
    };

    /**
     * @return the second point through which the circle passes.
     */
    const Point & q() const
    {
      return myQ;
    };

    /**
     * @return the third point through which the circle passes.
     */
    const Point & r() const
    {
      return myR;
    };


    //------------------ display -------------------------------

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;


    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    //the three points that uniquely define the circle
    /**
       First point through which the circle passes
    */
    Point myP;
    /**
       Second point through which the circle passes
    */
    Point myQ;
    /**
       Third point through which the circle passes
    */
    Point myR;
    // ------------------------- Hidden services ------------------------------
  protected:


  private:



    // ------------------------- Internals ------------------------------------
  private:




  }; // end of class CircleFrom3Points


  /**
   * Overloads 'operator<<' for displaying objects of class 'CircleFrom3Points'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CircleFrom3Points' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint>
  inline
  std::ostream&
  operator<< ( std::ostream & out,
        const CircleFrom3Points<TPoint> & object )
  {
    object.selfDisplay( out );
    return out;
  }


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/fromPoints/CircleFrom3Points.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CircleFrom3Points_h

#undef CircleFrom3Points_RECURSES
#endif // else defined(CircleFrom3Points_RECURSES)
