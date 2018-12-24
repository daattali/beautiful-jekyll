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
 * @file CircleFrom2Points.h
 * @brief Representation of a CircleFrom2Points uniquely defined by two 2D points.
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/22
 *
 * @brief Header file for module CircleFrom2Points.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CircleFrom2Points_RECURSES)
#error Recursive header files inclusion detected in CircleFrom2Points.h
#else // defined(CircleFrom2Points_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CircleFrom2Points_RECURSES

#if !defined CircleFrom2Points_h
/** Prevents repeated inclusion of headers. */
#define CircleFrom2Points_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/io/Color.h"
#include "DGtal/shapes/fromPoints/CircleFrom3Points.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // template class CircleFrom2Points
  /**
   * \brief Aim: Represents a circle that passes through a given point
   * and that is thus uniquely defined by two other points. It is able
   * to return for any given point its signed distance to itself
   *
   * @tparam TPoint  a type of points.
   */
  template <typename TPoint>
  class CircleFrom2Points
  {

    // ----------------------- associated types ------------------------------
  public:

    typedef typename TPoint::Coordinate Coordinate;
    typedef Coordinate Distance; //to promote
    typedef TPoint Point;
    typedef TPoint Vector;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     * @param aPole  a point
     */
    CircleFrom2Points(const Point& aPole);


    /**
     * Constructor with initialization.
     * @param aPole  a point
     * @param aFirstPoint  a point
     * @param aSecondPoint  a second point
     */
    CircleFrom2Points(const Point& aPole, const Point& aFirstPoint, const Point& aSecondPoint);

    /**
     * Init.
     * @param aFirstPoint  a point
     * @param aSecondPoint  a second point
     */
    void init(const Point& aFirstPoint, const Point& aSecondPoint);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    CircleFrom2Points ( const CircleFrom2Points & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    CircleFrom2Points & operator= ( const CircleFrom2Points & other );


    /**
     * Destructor. Does nothing
     */
    ~CircleFrom2Points();

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

    /**
     * Computes the signed distance of @e aP to the circle
     * @param aP the point to be tested.
     * @return the signed distance.
     */
    Distance signedDistance(const Point& aP) const;

    /**
     * Computes the parameters of the circle
     * @param cx  returned x-coordinate of the circle
     * @param cy  returned y-coordinate of the circle
     * @param r  returned radius of the circle
     */
    void getParameters(double& cx, double& cy, double& r) const;

    /**
     * @return the first (and not mutable) point through which the circle passes.
     */
    const Point & pole() const
    {
      return myPole;
    };

    /**
     * @return the second point through which the circle passes.
     */
    const Point & p() const
    {
      return myP;
    };

    /**
     * @return the third point through which the circle passes.
     */
    const Point & q() const
    {
      return myQ;
    };

    //------------------ display -------------------------------
    /**
     * Default drawing style object.
     * @return the dyn. alloc. default style for this object.
     */
    //DrawableWithBoard2D* defaultStyle( std::string mode="" ) const;

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
       First (and not mutable) point through which the circle passes
    */
    Point myPole;
    /**
       Second point through which the circle passes
    */
    Point myP;
    /**
       Third point through which the circle passes
    */
    Point myQ;
    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:




  }; // end of class CircleFrom2Points


  /**
   * Overloads 'operator<<' for displaying objects of class 'CircleFrom2Points'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'CircleFrom2Points' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint>
  inline
  std::ostream&
  operator<< ( std::ostream & out,
        const CircleFrom2Points<TPoint> & object )
  {
    object.selfDisplay( out );
    return out;
  }


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/fromPoints/CircleFrom2Points.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CircleFrom2Points_h

#undef CircleFrom2Points_RECURSES
#endif // else defined(CircleFrom2Points_RECURSES)
