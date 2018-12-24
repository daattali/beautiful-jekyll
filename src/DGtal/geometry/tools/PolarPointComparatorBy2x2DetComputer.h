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
 * @file PolarPointComparatorBy2x2DetComputer.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/04
 *
 * Header file for module PolarPointComparatorBy2x2DetComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(PolarPointComparatorBy2x2DetComputer_RECURSES)
#error Recursive header files inclusion detected in PolarPointComparatorBy2x2DetComputer.h
#else // defined(PolarPointComparatorBy2x2DetComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PolarPointComparatorBy2x2DetComputer_RECURSES

#if !defined PolarPointComparatorBy2x2DetComputer_h
/** Prevents repeated inclusion of headers. */
#define PolarPointComparatorBy2x2DetComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/tools/determinant/C2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace functors {

  /////////////////////////////////////////////////////////////////////////////
  // template class PolarPointComparatorBy2x2DetComputer
  /**
   * \brief Aim: Class that implements a binary point predicate, which is able to 
   * compare the position of two given points \f$ P, Q \f$ around a pole \f$ O \f$. 
   * More precisely, it compares the oriented angles lying between the horizontal line
   * passing by \f$ O \f$ and the rays \f$ [OP) \f$ and \f$ [OQ) \f$ 
   * (in a counter-clockwise orientation). 
   *
   * See PolarPointComparatorBy2x2DetComputer::operator() and PolarPointComparatorBy2x2DetComputer::isBefore
   * for more details about the comparison (especially in degenerate cases).  
   *
   * \note We do not use any approximating function like atan, but only exact computations
   * involving the evaluation of determinants of 2x2 matrices. With the default
   * template parameters, the result is guaranteed to be exact for integral point coordinates
   * lying whithin the range ]-2^30,2^30[. 
   *
   * @tparam TPoint type of points to compare
   * @tparam TDetComputer a model of C2x2DetComputer. 
   * By default, Simple2x2DetComputer is chosen. 
   *
   */
  template <typename TPoint, 
	    typename TDetComputer = Simple2x2DetComputer<typename TPoint::Coordinate, DGtal::int64_t > >
  class PolarPointComparatorBy2x2DetComputer
  {
    // ----------------------- Inner types ------------------------------------
  public: 

    /**
     * Type of 2D points to compare
     */
    typedef TPoint Point; 
    /**
     * Type of point coordinates
     */
    typedef typename Point::Coordinate Coordinate; 
    /**
     * Type of 2D vectors
     */
    typedef Point Vector; 

    /**
     * Type of the object that computes the determinant of 2x2 matrix in order to 
     * determine the orientation of three points or compare the norm of two vectors. 
     */
    typedef TDetComputer DetComputer; 
    BOOST_CONCEPT_ASSERT(( C2x2DetComputer<DetComputer> )); 

    /**
     * Type of integer returned by the determinant computer
     */    
    typedef typename DetComputer::ResultInteger ResultInteger; 

    /**
     * Type of the object that returns a bool from the determinant returned 
     * by @a myDetComputer.   
     */
    typedef functors::Thresholder<ResultInteger, false, false> CustomThresholder; 


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Default constructor.
     * @a myPole is set to (0,0). 
     */
    PolarPointComparatorBy2x2DetComputer();

    /**
     * Constructor.
     * @param aPoint pole used for the polar comparison
     */
    PolarPointComparatorBy2x2DetComputer(const Point& aPoint);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    PolarPointComparatorBy2x2DetComputer ( const PolarPointComparatorBy2x2DetComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    PolarPointComparatorBy2x2DetComputer & operator= ( const PolarPointComparatorBy2x2DetComputer & other );

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
     * Sets the pole.
     * @param aPole new pole for the polar comparison.
     */
    void setPole ( const Point& aPole );

    /**
     * Main operator, which compares two given points
     * @a aPoint1 and @a aPoint2.
     *
     * This method first checks whether the two points 
     * are located on the same side of the horizontal 
     * line passing by @a myPole or not. If so, it calls
     * PolarPointComparatorBy2x2DetComputer::isBefore. Otherwise it
     * concludes. 
     *
     * @param aPoint1 first point
     * @param aPoint2 second point
     * @return 'true' if aPoint1 lies before aPoint2, 'false' otherwise
     * @see PolarPointComparatorBy2x2DetComputer::isBefore
     */
    bool operator()(const Point& aPoint1, const Point& aPoint2) const;

    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Method that compares two given points both belonging 
     * to the upward (positive y-coordinates) or downward 
     * (negative y-coordinates) half-plane. 
     *
     * The first argument @a aU lies @e before 
     * the second one @a aV iff the triple
     * @a myPole , @a aU , @a aV are counter-clockwise oriented. 
     *
     * If @a myPole , @a aU , @a aV are aligned
     * @a aU lies @e before @a aV iff its (L2) norm is shorter. 
     *
     * Note that if @a aU or @a aV are equal to @a myPole, 
     * its norm is the shortest possible. 
     *
     * If @a aU and @a aV are equal, this methods returns 'false', 
     * because no point is strictly located before the other. 
     *
     * @param aU first point 
     * @param aV second point
     * @return 'true' if @a aU lies before @a aV, 
     * 'false' otherwise
     */
    bool isBefore(const Point& aU, const Point& aV) const;

    // ------------------------- Private Datas --------------------------------
  private:

    /**
     * Point used as the origin for the polar comparison of two given points
     */
    Point myPole; 

    /**
     * Object that computes the determinant of 2x2 matrix in order to 
     * determine the orientation of three points or compare the norm of two vectors
     */
    mutable DetComputer myDetComputer; 

    /**
     * Object that returns a bool from the determinant returned by @a myDetComputer
     */
    CustomThresholder myThresholder; 

    // ------------------------- Hidden services ------------------------------
  protected:


  private:


  }; // end of class PolarPointComparatorBy2x2DetComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'PolarPointComparatorBy2x2DetComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'PolarPointComparatorBy2x2DetComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint, typename TDetComputer>
  std::ostream&
  operator<< ( std::ostream & out, const PolarPointComparatorBy2x2DetComputer<TPoint,TDetComputer> & object );

  } //namespace functors

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/PolarPointComparatorBy2x2DetComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PolarPointComparatorBy2x2DetComputer_h

#undef PolarPointComparatorBy2x2DetComputer_RECURSES
#endif // else defined(PolarPointComparatorBy2x2DetComputer_RECURSES)
