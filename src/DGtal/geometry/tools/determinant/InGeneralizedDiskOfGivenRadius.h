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
 * @file InGeneralizedDiskOfGivenRadius.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/10
 *
 * Header file for module InGeneralizedDiskOfGivenRadius.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(InGeneralizedDiskOfGivenRadius_RECURSES)
#error Recursive header files inclusion detected in InGeneralizedDiskOfGivenRadius.h
#else // defined(InGeneralizedDiskOfGivenRadius_RECURSES)
/** Prevents recursive inclusion of headers. */
#define InGeneralizedDiskOfGivenRadius_RECURSES

#if !defined InGeneralizedDiskOfGivenRadius_h
/** Prevents repeated inclusion of headers. */
#define InGeneralizedDiskOfGivenRadius_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <array>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/tools/determinant/C2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class InGeneralizedDiskOfGivenRadius 
  /**
   * \brief Aim: This class implements an orientation functor that  
   * provides a way to determine the position of a given point with 
   * respect to the unique circle passing by the same two given points 
   * and whose radius and orientation is given. 
   *
   * This class is useful for some geometric algorithm involving disks of 
   * given radius, such as alpha-hull and alpha-shape computations. 
   *
   * The radius is given at construction. It is described by a pair
   * of integers @a myNum2 and @a myDen2 that stands for the numerator 
   * and denominator of the squared radius. 
   * The orientation is also given at construction. 
   * It is described by a boolean equal to 'true' (resp. 'false') if the 
   * center C of the circle of squared radius @a myNum2 / @a myDen2 
   * and passing by @a myP and @a myQ is located on the left side 
   * (resp. right side) of the oriented line @a myP @a myQ, ie. if 
   * @a myP , @a myQ , C are counter-clockwise oriented (resp. 
   * clockwise oriented). 
   * 
   * The test is done in two steps. After an initialization step that 
   * memorizes the two points that uniquely defines the circle whose
   * radius and orientation is given, we can test the position of a third 
   * point @a myR with respect to this circle. Note that the distance between 
   * @a myP and @a myR is assumed to be greater than the distance between 
   * @a myP and @a myQ and between @a myQ and @a myR.  
   * - If the third point lies on the same side of the oriented line 
   * passing by @a myP @a myQ than the circle center, the return value is: 
   *   - zero if the third point belongs to the circle  
   *   - strictly positive if it does not lie in the interior or on the boundary 
   *   of the circle 
   *   - strictly negative if it lies in the interior of the circle
   * - otherwise, the return value is strictly negative. This case is discarded
   * because segment @a myP @a myR is assumed to be the longest side of the triangle
   * @a myP ,  @a myQ , @a myR. 
   *
   * The test is reduced to the computation of the determinant of a 2x2 matrix
   * of integral entries, the implementation of which is delegated to a determinant 
   * computer. The reduction involves many multiplications and additions 
   * so that temporary integers must be coded with at least \f$ 6b + 9 \f$ bits 
   * for point coordinates coded with \f$ b \f$ bits. That's why it is a best 
   * practice to use BigInteger to avoid any overflows. You can use however 
   * 64 bits integers together with a smart determinant computer, like 
   * AvnaimEtAl2x2DetSignComputer, for small domains where point coordinates range 
   * within ]-2^9; 2^9[. 
   *
   * Basic usage: 
   @code
   ...
   typedef Z2i::Point Point; 
   typedef Simple2x2DetComputer<Z2i::BigInteger> DeterminantComputer; 
   typedef InGeneralizedDiskOfGivenRadius<Point, DeterminantComputer> Functor; 

   Functor functor(true, 25, 1); //circles of radius 5, directly oriented 
   functor.init( Point(5,0), Point(0,5) ); 
   return functor( Point(-4,1) ); 
   //a strictly positive value is returned because (-4,1) lies in the interior
   //of the circle of center (0,0) and radius 5. 
   @endcode
   * 
   * Note that since a substantial part of the execution time comes from 
   * the allocation/desallocation of integers, we follow the same strategy 
   * used in IntegerComputer: the user instantiates once this object and 
   * performs several tests with it. 
   *
   * @tparam TPoint a model of point
   * @tparam TDetComputer a model of C2x2DetComputer
   */
  template <typename TPoint, typename TDetComputer>
  class InGeneralizedDiskOfGivenRadius
  {
    // ----------------------- Inner types ------------------------------------
  public:
    /**
     * Type of input points
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
     * Type of integers used during the computation
     */
    typedef typename DetComputer::ArgumentInteger Integer; 
    /**
     * Type of returned value
     */
    typedef typename DetComputer::ResultInteger Value; 
    /**
     * Type of functor returning the area of a parallelogram 
     * based on two vectors. Used to compute the radius of 
     * a circle passing by 3 points.
     */
    typedef Simple2x2DetComputer<Integer> AreaFunctor; 

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor of the functor from a given radius. 
     *
     * @param isPositive bool equal to 'true' (resp. 'false') if the 
     * center C of the circle of squared radius @a myNum2 / @a myDen2 
     * and passing by @a myP and @a myQ is located on the left side 
     * (resp. right side) of the oriented line @a myP @a myQ, ie. 
     * @a myP , @a myQ , C are counter-clockwise oriented (resp. 
     * clockwise oriented). 
     * @param aNum2 squared numerator of the radius (0 by default)
     * @param aDen2 squared denominator of the radius (1 by default)
     * @pre aNum2 should be not zero; the object is not valid. 
     * @warning @a aNum2 and @a aDen2 should be both positive. If they are 
     * negative, we take their opposite. It @a aDen2 is zero, the 
     * radius is assumed to tend to infinite. 
     */
    InGeneralizedDiskOfGivenRadius(bool isPositive = true, 
		  const Integer& aNum2 = NumberTraits<Integer>::ONE, 
		  const Integer& aDen2 = NumberTraits<Integer>::ZERO);

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    InGeneralizedDiskOfGivenRadius ( const InGeneralizedDiskOfGivenRadius & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    InGeneralizedDiskOfGivenRadius & operator= ( const InGeneralizedDiskOfGivenRadius & other );

    // ----------------------- Interface --------------------------------------
  public:
    /**
     * Initialization from two points.
     * @param aP a first point
     * @param aQ a second point
     *
     * @pre the distance between @a aP and @a aQ must be greater than the circle diameter
     */
    void init( const Point& aP, const Point& aQ ); 

    /**
     * Initialisation from two points. 
     * @param aA array of two points
     * @see InGeneralizedDiskOfGivenRadiusBy2x2DetComputer::init()
     */
    void init(const PointArray& aA);

    /**
     * Main operator.
     *
     * @warning InGeneralizedDiskOfGivenRadiusBy2x2DetComputer::init() should be called before
     *
     * @param aR any point to test
     * @return orientation of the third point @a myR with respect to the 
     * circle of squared radius @a myNum2 / @a myDen2 and oriented by @a myPositive
     * passing by @a myP and @a myQ. 
     * - if the third point lies on the same side of the oriented line 
     * passing by @a myP @a myQ than the circle center, the return value is: 
     *   - zero if the third point belongs to the circle  
     *   - strictly positive if it does not lie in the interior or on the boundary 
     *   of the circle 
     *   - strictly negative if it lies in the interior of the circle
     * - otherwise, the return value is strictly negative.  
     *
     * @pre the distance between @a myQ and @a aR must be greater than the circle diameter
     * and segment @a myP @a aR is assumed to be the longest side of the triangle
     * @a myP ,  @a myQ , @a aR. 
     */
    Value operator()( const Point& aR ) const; 

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Compares the length of two consecutive input points
     * to the diameter of the circle.
     * @param aL2 any squared length between two points 
     * @return 'true' if either @a myDen2 equals zero or
     * the given (squared) length is shorter than the (squared) 
     * diameter of the circle
     */
    bool lengthIsValid(const Integer& aL2) const;

    /**
     * Checks the validity/consistency of the object.
     * More precisely, @a myNum2 and @a myDen2 must 
     * be positive, @a myNum2 must not be zero 
     * (only strictly positive radius are valid)
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    // ----------------------- Internals --------------------------------------
  public:
    /**
     * Update @a myComputedNum2 and @a myComputedDen2 from other private datas. 
     */
    void finalizeComputation() const; 

    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Numerator of the given squared radius 
     */
    Integer myNum2; 
    /**
     * Denominator of the given squared radius 
     */
    Integer myDen2; 
    /**
     * boolean equal to 'true' (resp. 'false') if the 
     * center C of the circle of squared radius @a myNum2 / @a myDen2 
     * and passing by @a myP and @a myQ is located on the left side 
     * (resp. right side) of the oriented line @a myP @a myQ, ie. if 
     * @a myP , @a myQ , C are counter-clockwise oriented (resp. 
     * clockwise oriented). 
     */
    bool myIsPositive; 
    /**
     * Determinant computer used to compare the given (squared) radius 
     * @a myNum2 / @a myDen2 to the (squared) radius of the circle 
     * passing by @a myP , @a myQ , @a myR , ie. 
     * @a myComputedNum2 / @a myComputedDen2
     */
    DetComputer myDetComputer; 

    /**
     * First point  
     */
    mutable Point myP;     
    /**
     * Second point  
     */
    mutable Point myQ;     
    /**
     * Third point  
     */
    mutable Point myR;     
    /**
     * Numerator of the squared radius of the circle @a myP , @a myQ , @a myR  
     */
    mutable Integer myComputedNum2; 
    /**
     * Denominator of the squared radius of the circle @a myP , @a myQ , @a myR  
     */
    mutable Integer myComputedDen2; 
    /**
     * x-coordinate of @a myQ - @a myP
     */
    mutable Integer myPQ0; 
    /**
     * y-coordinate of @a myQ - @a myP
     */
    mutable Integer myPQ1; 
    /**
     * Squared length of @a myQ - @a myP
     */
    mutable Integer myPQnorm; 
    /**
     * x-coordinate of @a myR - @a myQ
     */
    mutable Integer myQR0; 
    /**
     * y-coordinate of @a myR - @a myQ
     */
    mutable Integer myQR1; 
    /**
     * Squared length of @a myR - @a myQ
     */
    mutable Integer myQRnorm; 
    /**
     * x-coordinate of @a myP - @a myR
     */
    mutable Integer myRP0; 
    /**
     * y-coordinate of @a myP - @a myR
     */
    mutable Integer myRP1; 
    /**
     * Squared length of @a myP - @a myR
     */
    mutable Integer myRPnorm; 
    /**
     * area of triangle @a myP @a myQ @a myR
     */
    mutable Integer myArea; 
    /**
     * Functor returning the area of a parallelogram 
     * based on two vectors. 
     */
    mutable AreaFunctor myAreaFunctor; 

  }; // end of class InGeneralizedDiskOfGivenRadius


  /**
   * Overloads 'operator<<' for displaying objects of class 'InGeneralizedDiskOfGivenRadius'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'InGeneralizedDiskOfGivenRadius' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint, typename TDetComputer>
  std::ostream&
  operator<< ( std::ostream & out, const InGeneralizedDiskOfGivenRadius<TPoint, TDetComputer> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/determinant/InGeneralizedDiskOfGivenRadius.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined InGeneralizedDiskOfGivenRadius_h

#undef InGeneralizedDiskOfGivenRadius_RECURSES
#endif // else defined(InGeneralizedDiskOfGivenRadius_RECURSES)
