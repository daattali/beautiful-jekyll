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
 * @file StraightLineFrom2Points.h
 * @brief Representation of a StraightLineFrom2Points uniquely defined by two 2D points.
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/10/27
 *
 * Header file for module StraightLineFrom2Points.cpp
 *
 * This file is part of the DGtal library.
 *
 * @see testHalfPlane.cpp
 */

#if defined(StraightLineFrom2Points_RECURSES)
#error Recursive header files inclusion detected in StraightLineFrom2Points.h
#else // defined(StraightLineFrom2Points_RECURSES)
/** Prevents recursive inclusion of headers. */
#define StraightLineFrom2Points_RECURSES

#if !defined StraightLineFrom2Points_h
/** Prevents repeated inclusion of headers. */
#define StraightLineFrom2Points_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>

#include "DGtal/base/Common.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  /////////////////////////////////////////////////////////////////////////////
  // template class StraightLineFrom2Points
  /**
   * \brief Aim: Represents a straight line uniquely
   * defined by two 2D points and that is able
   * to return for any given 2D point its signed distance to itself
   *
   * @tparam TPoint  a type of points.
   */
  template <typename TPoint>
  class StraightLineFrom2Points
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
     * Default constructor.
     */
    StraightLineFrom2Points();


    /**
     * Constructor.
     * @param aFirstPoint  a point
     * @param aSecondPoint  another point
     */
    StraightLineFrom2Points(const Point& aFirstPoint, const Point& aSecondPoint);

    /**
     * Init.
     * @param aFirstPoint  a point
     * @param aSecondPoint  another point
     */
    void init(const Point& aFirstPoint, const Point& aSecondPoint);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    StraightLineFrom2Points ( const StraightLineFrom2Points & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    StraightLineFrom2Points & operator= ( const StraightLineFrom2Points & other );


    /**
     * Destructor. Does nothing
     */
    ~StraightLineFrom2Points();

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
     * Computes the signed distance of @e aP to the straight line
     * @param aP the point to be tested.
     * @return the signed distance.
     */
    Distance signedDistance(const Point& aP) const;

    /**
     * @return the first point through which the straight line passes.
     */
    const Point & p() const
    {
      return myP;
    };

    /**
     * @return the second point through which the straight line passes.
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
    //the two points that uniquely define the straight line
    /**
       First point through which the straight line passes
    */
    Point myP;
    /**
       Second point through which the straight line passes
    */
    Point myQ;
    // ------------------------- Hidden services ------------------------------
  protected:


  private:



    // ------------------------- Internals ------------------------------------
  private:




  }; // end of class StraightLineFrom2Points


  /**
   * Overloads 'operator<<' for displaying objects of class 'StraightLineFrom2Points'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'StraightLineFrom2Points' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint>
  inline
  std::ostream&
  operator<< ( std::ostream & out,
        const StraightLineFrom2Points<TPoint> & object )
  {
    object.selfDisplay( out );
    return out;
  }


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/fromPoints/StraightLineFrom2Points.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined StraightLineFrom2Points_h

#undef StraightLineFrom2Points_RECURSES
#endif // else defined(StraightLineFrom2Points_RECURSES)
