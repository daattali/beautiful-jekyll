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
 * @file InHalfPlaneBy2x2DetComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/22
 *
 * Header file for module InHalfPlaneBy2x2DetComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(InHalfPlaneBy2x2DetComputer_RECURSES)
#error Recursive header files inclusion detected in InHalfPlaneBy2x2DetComputer.h
#else // defined(InHalfPlaneBy2x2DetComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define InHalfPlaneBy2x2DetComputer_RECURSES

#if !defined InHalfPlaneBy2x2DetComputer_h
/** Prevents repeated inclusion of headers. */
#define InHalfPlaneBy2x2DetComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <array>
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/tools/determinant/C2x2DetComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class InHalfPlaneBy2x2DetComputer
  /**
   * \brief Aim: Class that implements an orientation functor, ie. 
   * it provides a way to compute the orientation of three given 2d points. 
   * More precisely, it returns: 
   * - zero if the three points belong to the same line
   * - strictly positive if the three points are counter-clockwise oriented
   * - striclty negative if the three points are clockwise oriented. 
   * The orientation test is reduced to the computation of the determinant of
   * a 2x2 matrix, the implementation of which is delegated to a determinant 
   * computer. 
   *
   * Basic usage: 
   @code
   ...
   typedef Z2i::Point Point; 
   typedef Simple2x2DetComputer<Z2i::Integer> DeterminantComputer; 
   typedef InHalfPlaneBy2x2DetComputer<Point, DeterminantComputer> MyType; 

   MyType orientationTest; 
   orientationTest.init( Point(0,0), Point(5,2) ); 
   return orientationTest( Point(2,1) ); 
   //a strictly positive value is returned because (0,0) (5,2) (2,1) are CCW oriented
   @endcode
   *
   * @tparam TPoint a model of point
   * @tparam TDetComputer a model of C2x2DetComputer
   *
   * NB: The robustness of the computation depends on the robustness of the determinant 
   * computer. 
   * However, in order to be sure that the result will be exact, you should be sure that 
   * the chosen determinant computer can safely deal with integers coded with b+1 bits 
   * if the points coordinates are coded with b bits. 
   * 
   * @see Simple2x2DetComputer SimpleIncremental2x2DetComputer 
   * AvnaimEtAl2x2DetComputer FilteredDetComputer
   */
  template <typename TPoint, typename TDetComputer>
  class InHalfPlaneBy2x2DetComputer
  {
    // ----------------------- Types  ------------------------------------
  public:

    /**
     * Type of points 
     */
    typedef TPoint Point; 

    /**
     * Type of point array
     */
    typedef std::array<Point,2> PointArray;
    /**
     * Type used to represent the size of the array
     */
    typedef typename PointArray::size_type SizeArray; 
    /**
     * static size of the array, ie. 2
     */
    static const SizeArray size = 2;

    /**
     * Type of determinant computer
     */
    typedef TDetComputer DetComputer; 
    BOOST_CONCEPT_ASSERT(( C2x2DetComputer<DetComputer> )); 

    /**
     * Type of input integers for the determinant computer
     *
     * NB: the type of the points coordinates are casted into ArgumentInteger
     * before being passed to the determinant computer. 
     */
    typedef typename TDetComputer::ArgumentInteger ArgumentInteger;

    /**
     * Type of integer for the result
     */
    typedef typename TDetComputer::ResultInteger Value; 

    // ----------------------- Standard services ------------------------------
  public:


    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Initialisation.
     * @param aP first point
     * @param aQ second point
     */
    void init(const Point& aP, const Point& aQ);

    /**
     * Initialisation. 
     * @param aA array of two points
     */
    void init(const PointArray& aA);

    /**
     * Main operator.
     * @warning InHalfPlaneBy2x2DetComputer::init() should be called before
     * @param aR any point to test
     * @return orientation of the three points @a aP @a aQ @a aR : 
     * - zero if the three points belong to the same line
     * - strictly positive if the three points are counter-clockwise oriented
     * - striclty negative if the three points are clockwise oriented
     * @see InHalfPlaneBy2x2DetComputer::init()
     */
    Value operator()(const Point& aR) const;

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


    // ------------------------- Internals ------------------------------------
  private:
    /**
     * Coordinates of the first point.
     */
    ArgumentInteger myA, myB; 
    /**
     * A 2x2 determinant computer
     */
    mutable DetComputer myDetComputer; 

  }; // end of class InHalfPlaneBy2x2DetComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'InHalfPlaneBy2x2DetComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'InHalfPlaneBy2x2DetComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint, typename TDetComputer>
  std::ostream&
  operator<< ( std::ostream & out, const InHalfPlaneBy2x2DetComputer<TPoint, TDetComputer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/determinant/InHalfPlaneBy2x2DetComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined InHalfPlaneBy2x2DetComputer_h

#undef InHalfPlaneBy2x2DetComputer_RECURSES
#endif // else defined(InHalfPlaneBy2x2DetComputer_RECURSES)
