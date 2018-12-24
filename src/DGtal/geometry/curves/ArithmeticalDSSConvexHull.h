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
 * @file ArithmeticalDSSConvexHull.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/02/11
 *
 * Header file for module ArithmeticalDSSConvexHull.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSSConvexHull_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSSConvexHull.h
#else // defined(ArithmeticalDSSConvexHull_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSSConvexHull_RECURSES

#if !defined ArithmeticalDSSConvexHull_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSSConvexHull_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace functors {

    /**
     * @brief Functor that returns the position of any point/vector 
     * with respect to a digital straight line of shift @a myShift. 
     * We recall that the shift vector is a vector translating a point 
     * of remainder \f$ r \f$ to a point of remainder \f$ r + \omega \f$. 
     * See @ref moduleArithDSSReco for further details.
     * @tparam Vector a model of 2d vector
     * @tparam TPosition a model of integer used to locate the 
     * points of a DSL
     */
    template <typename Vector, typename TPosition>
    struct PositionFunctorFrom2DPoint
    {
    public: 
      typedef TPosition Position; 
    private: 
      /// shift vector 
      Vector myShift; 
    public:
      /**
       * Constructor
       * @param aShift shift vector of a naive or standard DSL
       */
      PositionFunctorFrom2DPoint(const Vector& aShift): myShift(aShift) {}
      /**
       * Returns the position of a point in a digital straight line
       * @param aPointVector point/vector at which we compute the position
       * @return position of the point
       * @tparam PointVector model of 2D point/vector
       */
      template <typename PointVector>
      inline
      Position operator()(const PointVector& aPointVector) const
      {
	return ( - myShift[1] * aPointVector[0]
		 + myShift[0] * aPointVector[1] );
      }
    }; 

    /**
     * @brief Binary functor that returns the algebraic quotient i of a/b 
     * with any fractional part discarded (truncation toward zero).  
     * Note that \f$ |i| \leq |a/b| \f$. 
     *
     * (For a truncation toward negative infinity, see IntegerComputer::floorDiv)
     *
     * @tparam Integer a model of integer used to store a and b
     */
    template <typename Integer>
    struct LargeTruncationFunctor
    {
    public: 
      /**
       * @return quotient a/b with any fractional part discarded
       *
       * @param a numerator
       * @param b denominator
       * @pre b is not null
       */
      inline
      Integer operator()(const Integer& a, const Integer& b) const
      {
	ASSERT( b != NumberTraits<Integer>::ZERO );
	return a / b; 
      }
    }; 

    /**
     * @brief BinaryFunctor that computes the algebraic quotient i of a/b 
     * with any non zero fractional part discarded (truncation toward zero),
     * and that returns i+1 (resp. i-1) if a is negative (resp. positive)
     * if b divides a. 
     * Since we assume that a is not equal to 0, we have \f$ |i| < |a/b| \f$. 
     * See also LargeTruncationFunctor. 
     *
     * @tparam Integer a model of integer used to store a and b
     */
    template <typename Integer>
    struct StrictTruncationFunctor
    {
    public: 
      /**
       * @return quotient i defined above
       *
       * @param a numerator
       * @pre a is not null
       * @param b denominator
       * @pre b is not null
       */
      inline
      Integer operator()(const Integer& a, const Integer& b) const 
      {
	ASSERT( a != NumberTraits<Integer>::ZERO ); 
	ASSERT( b != NumberTraits<Integer>::ZERO );
 
	Integer i = a / b;
	if (a == i*b)
	  {
	    if (i >= NumberTraits<Integer>::ZERO) 
	      --i; 
	    else 
	      ++i;
	  }
	return i; 
      } 
    }; 

  } // namespace functors


  namespace functions {

    /**
     * @brief Procedure that computes the next (lower or upper) vertex of 
     * the left hull of a DSS.
     *
     * @param positionBound position of the last point of the DSS
     * @param remainderBound remainder of the lower leaning points contained in the DSS
     * @param X (returned) last vertex of the considered side
     * @param rX (returned) remainder of @a X
     * @param Y last vertex of the opposite side
     * @param rY remainder of @a Y
     * @param V (returned) last direction vector (unimodular with (@a X - @a Y))
     * @param rV (returned) remainder of @a V (not null)
     * @param ito output iterator used to store the new vertex 
     * lying on the same side as @a X
     * @param pos position functor, which returns the position of any given point/vector
     * @param f1 first floor function (for the vertex)
     * @param f2 second floor function (for the direction vector)
     *
     * @return 'true' if the last vertex of the left hull has been reached, 
     * 'false' otherwise. 
     *
     * @tparam Position a model of integer for locating points in the DSS
     * @tparam PointVector a model of 2d point/vector
     * @tparam Coordinate a model of integer for the coordinates of the point/vector 
     * @tparam OutputIterator a model of output iterator
     * @tparam PositionFunctor a model of unary functor that returns the position of a point/vector
     * @tparam TruncationFunctor1 a model of unary functor that implements an integer division
     * @tparam TruncationFunctor2 a model of unary functor that implements an integer division
     */
    template<typename Position, typename Coordinate, typename PointVector, 
	     typename OutputIterator,
	     typename PositionFunctor,
	     typename TruncationFunctor1, typename TruncationFunctor2>
    inline
    bool
    smartCHNextVertex(const Position& positionBound,
		      const Coordinate& remainderBound,
		      PointVector& X,
		      Coordinate& rX, 
		      const PointVector& Y,
		      const Coordinate& rY, 
		      PointVector& V, 
		      Coordinate& rV,
		      OutputIterator ito,
		      const PositionFunctor& pos, 
		      const TruncationFunctor1& f1, 
		      const TruncationFunctor2& f2); 

    /**
     * @brief Procedure that computes the lower and upper left hull of 
     * a DSS of first point @a aFirstPoint, length @a aPositionBound, 
     * contained in a digital straight line described by @a aRStep, 
     * @a aRShift and @a aRemainderBound. 
     *
     * @param aFirstPoint first point of the DSS
     * @param aRemainderBound difference between the intercept mu of the bounding DSL
     * and the remainder of the first point. 
     * @param aPositionBound (strictly positive) length of the DSS
     * @param aStep first step of the DSL
     * @param aRStep remainder of the first step, ie. parameter \f$ a \f$ of the bounding DSL
     * @param aShift shift vector of the DSL
     * @param aRShift remainder of the shift vector, ie. parameter \f$ omega \f$ of the bounding DSL. 
     * @param aPositionFunctor position functor, which returns the position of any given point/vector 
     * @param uIto output iterator used to store the vertices of the upper convex hull
     * @param lIto output iterator used to store the vertices of the lower convex hull
     *
     * @return last direction vector, 
     * ie. the rational slope of minimal denominator of the DSS
     *
     * @tparam PointVector a model of 2d point/vector
     * @tparam Coordinate a model of integer for the coordinates of the point/vector 
     * @tparam Position a model of integer for locating points in the DSS
     * @tparam PositionFunctor a model of unary functor that returns the position of a point/vector
     * @tparam OutputIterator a model of output iterator
     */
    template<typename PointVector, typename Coordinate, typename Position, 
	     typename PositionFunctor, typename OutputIterator>
    inline
    PointVector
    smartCH(const PointVector& aFirstPoint, 
	    const Coordinate& aRemainderBound, 
	    const Position& aPositionBound, 
	    const PointVector& aStep,
	    const Coordinate& aRStep, 
	    const PointVector& aShift, 
	    const Coordinate& aRShift,  
	    const PositionFunctor& aPositionFunctor, 
	    OutputIterator uIto, OutputIterator lIto); 

    /**
     * @brief Procedure that computes the lower and upper left hull of 
     * a DSS of first point @a aFirstPoint, length @a aLength, 
     * contained in a DSL @a aDSL [Roussillon 2014 : \cite RoussillonDGCI2014]. 
     *
     * @param aDSL bounding DSL
     * @param aFirstPoint first point of the DSS
     * @param aLength (strictly positive) length of the DSS
     * @param uIto output iterator used to store the vertices of the upper convex hull
     * @param lIto output iterator used to store the vertices of the lower convex hull
     *
     * @return last direction vector, 
     * ie. the rational slope of minimal denominator
     *
     * @tparam DSL a model of arithmetical DSL 
     * @tparam OutputIterator a model of output iterator
     */
    template<typename DSL, typename OutputIterator>
    inline
    typename DSL::Vector smartCH(const DSL& aDSL, 
				 const typename DSL::Point& aFirstPoint, 
				 const typename DSL::Position& aLength, 
				 OutputIterator uIto, OutputIterator lIto); 


    /**
     * @brief Procedure that computes the previous vertex of the 
     * left hull of a DSS of main direction vector @a V , 
     * first upper leaning point @a U and first positive Bezout 
     * point @a L. The computation stops as soon as a computed vertex
     * is located before @a aLastPosition.  
     *
     * @param X (returned) first vertex of the left hull on the considered side
     * @param Y first vertex of the left hull on the opposite side
     * @param V (returned) previous direction vector
     * @param aFirstPosition position of the first point of the subsegment
     * @param aLastPosition position of the last point of the subsegment
     * @param ito output iterator used to store the vertices of the left hull
     * lying on the same side as @a X
     * @param pos position functor, which returns the position of any given point/vector
     * @param f1 integer divisor for the direction vector update
     * @param f2 integer divisor for the vertex update
     *
     * @tparam PointVector a model of couple of coordinates
     * @tparam Position a model of integer for the position of the points
     * @tparam OutputIterator a model of output iterator
     * @tparam TruncationFunctor1 a model of functor for the integer division
     * @tparam TruncationFunctor2 a model of functor for the integer division
     * @tparam PositionFunctor a model of functor returning the position of a point
     *
     * @return 'true' if the last vertex has been reached, 
     * 'false' otherwise
     */
    template<typename PointVector, typename Position, 
	     typename OutputIterator, 
	     typename TruncationFunctor1, typename TruncationFunctor2, 
	     typename PositionFunctor>
    inline
    bool smartCHPreviousVertex(PointVector& X, const PointVector& Y, PointVector& V, 
			       const Position& aFirstPosition, const Position& aLastPosition, 
			       OutputIterator ito, 
			       const PositionFunctor& pos,
			       const TruncationFunctor1& f1, 
			       const TruncationFunctor2& f2); 

    /**
     * @brief Procedure that computes the lower and upper left hull of 
     * the left subsegment of a greater DSS characterized by the first 
     * upper leaning point @a U, the first positive Bezout point @a L 
     * and its direction vector @a V. Note that the so-called left 
     * subsegment is bounded on the one hand by the first point of the DSS
     * located at @a aFirstPosition and on the other hand by the point 
     * located at position @a aLastPosition. 
     *
     * @param U last upper convex hull vertex
     * @param L last lower convex hull vertex
     * @param V last valid Bezout vector (main direction vector)
     * @param aFirstPosition position of the first point of the subsegment
     * @param aLastPosition position of the last point of the subsegment
     * @param aPositionFunctor position functor, which returns the position of any given point/vector 
     * @param uIto output iterator used to store the vertices of the upper convex hull
     * @param lIto output iterator used to store the vertices of the lower convex hull
     *
     * @tparam PointVector a model of 2d point/vector
     * @tparam Position a model of integer for the position of the point in the bounding DSS
     * @tparam PositionFunctor a model of unary functor that returns the position of a point/vector
     * @tparam OutputIterator a model of output iterator
     *
     * @return last direction vector, 
     * ie. the rational slope of minimal denominator
     */
    template<typename PointVector, typename Position, typename PositionFunctor, typename OutputIterator>
    inline
    PointVector reversedSmartCH(PointVector U, PointVector L, PointVector V, 
			       const Position& aFirstPosition, const Position& aLastPosition,
			       const PositionFunctor& aPositionFunctor, 
			       OutputIterator uIto, OutputIterator lIto); 

    /**
     * @brief Procedure that computes the lower and upper left hull of 
     * the left subsegment of a greater DSS @a aDSS. Note that the so-called left 
     * subsegment is bounded on the one hand by the first point of @a aDSS and 
     * on the other hand by the point located at position @a aPositionBound
     * [Roussillon 2014 : \cite RoussillonDGCI2014]. 
     *
     * @param aDSS bounding DSS
     * @param aPositionBound position of the last point of the subsegment 
     * (should be located after the first point of @a aDSS).
     * @param uIto output iterator used to store the vertices of the upper convex hull
     * @param lIto output iterator used to store the vertices of the lower convex hull
     *
     * @tparam DSS a model of arithmetical DSS 
     * @tparam OutputIterator a model of output iterator
     *
     * @return last direction vector, 
     * ie. the rational slope of minimal denominator
     */
    template<typename DSS, typename OutputIterator>
    inline
    typename DSS::Vector reversedSmartCH(const DSS& aDSS, 
					const typename DSS::Position& aPositionBound, 
					OutputIterator uIto, OutputIterator lIto); 

  } // namespace functions


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/ArithmeticalDSSConvexHull.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArithmeticalDSSConvexHull_h

#undef ArithmeticalDSSConvexHull_RECURSES
#endif // else defined(ArithmeticalDSSConvexHull_RECURSES)
