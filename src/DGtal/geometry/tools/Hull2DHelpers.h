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
 * @file Hull2DHelpers.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @author Bertrand Kerautret (\c bertrand.kerautret@univ-lorraine.fr)
 * LORIA (CNRS, UMR 7503), University of Lorraine, France
 * @date 2015/12/10
 *
 * Header file for module Hull2DHelpers.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Hull2DHelpers_RECURSES)
#error Recursive header files inclusion detected in Hull2DHelpers.h
#else // defined(Hull2DHelpers_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Hull2DHelpers_RECURSES

#if !defined Hull2DHelpers_h
/** Prevents repeated inclusion of headers. */
#define Hull2DHelpers_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>
#include <vector>
#include "boost/utility.hpp"

#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include "DGtal/base/FrontInsertionSequenceToStackAdapter.h"
#include "DGtal/base/BackInsertionSequenceToStackAdapter.h"
#include "DGtal/base/CStack.h"
#include "DGtal/geometry/tools/CPolarPointComparator2D.h"
#include "DGtal/geometry/tools/PolarPointComparatorBy2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/COrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"
#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  namespace functions
  {
  /**
   * @brief Hull2D namespace gathers useful functions to compute 
   * and return the convex hull or the alpha-shape of a range 
   * of 2D points. 
   */
  namespace Hull2D
  {

    
    /// The 2 thickness definitions.
    enum ThicknessDefinition {HorizontalVerticalThickness, EuclideanThickness};


    /**
     * @brief Procedure that updates the hull when
     * an extra point @a aNewPoint is considered: 
     * while the last three consecutive points, ie. @a aNewPoint
     * and the last two points of the container are not oriented 
     * such that the predicate @a aPredicate returns 'true',  
     * the last point of the container is removed. 
     * @see Hull2D::buildHullWithStack
     * 
     * @param aStack reference to the stack of retrieved vertices
     * @param aNewPoint new point
     * @param aPredicate point predicate  
     * 
     * @tparam Stack a model of CStack 
     * @tparam Point a model of point    
     * @tparam Predicate a model of ternary predicate 
     */
    template <typename Stack, 
	      typename Point, 
	      typename Predicate>
    void updateHullWithStack(Stack& aStack, 
			     const Point& aNewPoint, 
			     const Predicate& aPredicate); 

    /**
     * @brief Procedure that calls Hull2D::updateHullWithStack
     * on a copy of the stack object used to retrieved the hull
     * vertices. Useful when the first argument is a stack adapter
     * returned by a function: it must be copied before being
     * passed by reference in Hull2D::updateHullWithStack. 
     * 
     * @param aStack stack copy
     * @param aNewPoint new point
     * @param aPredicate point predicate  
     * 
     * @tparam Stack a model of CStack 
     * @tparam Point a model of point    
     * @tparam Predicate a model of ternary predicate 
     */
    template <typename Stack, 
	      typename Point, 
	      typename Predicate>
    void updateHullWithAdaptedStack(Stack aStack, 
				    const Point& aNewPoint, 
				    const Predicate& aPredicate); 

    /**
     * @brief Procedure that retrieves the vertices of the convex hull 
     * of a weakly externally visible polygon (WEVP) in linear-time. 
     * This technique is called Sklansky's scan, Graham's scan or 3-coins algorithm.  
     * It works for all WEVP [Toussaint and Avis, 1982 : \cite ToussaintAvis1982].  
     *
     * @param aStack reference to the stack of retrieved vertices
     * @param itb begin iterator
     * @param ite end iterator 
     * @param aPredicate predicate  
     * 
     * @tparam Stack a model of CStack
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam Predicate a model of ternary predicate
     *
     * @see Hull2D::updateHullWithStack
     */
    template <typename Stack, 
	      typename ForwardIterator, 
	      typename Predicate>
    void buildHullWithStack(Stack& aStack, 
			    const ForwardIterator& itb, 
			    const ForwardIterator& ite,
			    const Predicate& aPredicate); 

    /**
     * @brief Procedure that calls Hull2D::buildHullWithStack
     * on a copy of the stack object used to retrieved the hull
     * vertices. Useful when the first argument is a stack adapter
     * returned by a function: it must be copied before being
     * passed by reference in Hull2D::buildHullWithStack. 
     *
     * @param aStack stack copy
     * @param itb begin iterator
     * @param ite end iterator 
     * @param aPredicate predicate  
     * 
     * @tparam Stack a model of CStack 
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam Predicate a model of ternary predicate
     *
     * @see Hull2D::buildHullWithStack
     */
    template <typename Stack, 
	      typename ForwardIterator, 
	      typename Predicate>
    void buildHullWithAdaptedStack(Stack aStack, 
				   const ForwardIterator& itb, 
				   const ForwardIterator& ite,
				   const Predicate& aPredicate); 

    /**
     * @brief Procedure that retrieves the vertices of the convex hull 
     * of a weakly externally visible polygon (WEVP) in linear-time. 
     * @see Hull2D::buildHullWithStack
     * 
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aPredicate any ternary predicate  
     * 
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incremental and writable iterator   
     * @tparam Predicate a model of ternary predicate
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Predicate>
    void openGrahamScan(const ForwardIterator& itb, 
			const ForwardIterator& ite,  
			OutputIterator res, 
			const Predicate& aPredicate); 

    /**
     * @brief Procedure that retrieves the vertices of the convex hull 
     * of a weakly externally visible polygon (WEVP) in linear-time. 
     * @see Hull2D::buildHullWithStack
     * 
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aPredicate any ternary predicate  
     *
     * @pre we assume that the starting point of the polygon 
     * is an extremal point. 
     *
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incremental and writable iterator   
     * @tparam Predicate a model of ternary predicate
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Predicate>
    void closedGrahamScanFromVertex(const ForwardIterator& itb, 
				    const ForwardIterator& ite,  
				    OutputIterator res, 
				    const Predicate& aPredicate); 

    /**
     * @brief Procedure that retrieves the vertices of the convex hull 
     * of a weakly externally visible polygon (WEVP) in linear-time. 
     * @see Hull2D::buildHullWithStack Hull2D::closedGrahamScanFromVertex
     *
     * NB: We do not assume that the starting point of the polygon 
     * is an extremal point like in Hull2D::closedGrahamScanFromVertex
     * 
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aPredicate  any ternary predicate
     *
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incremental and writable iterator   
     * @tparam Predicate a model of ternary predicate
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Predicate>
    void closedGrahamScanFromAnyPoint(const ForwardIterator& itb, 
				      const ForwardIterator& ite,  
				      OutputIterator res, 
				      const Predicate& aPredicate); 

    /**
     * @brief Procedure that retrieves the vertices
     * of the convex hull of a set of 2D points given by 
     * the range [ @a itb , @a ite ). 
     * This procedure follows the well-known Graham's algorithm
     * [Graham, 1972 : \cite Graham1972]
     * - choose a pole and sort the points in order of increasing angle about the pole
     * with the given comparator. 
     * - scan the sorted list of points and remove some points so that the given 
     * predicate returns 'true' for all sets of three consecutive points. 
     * @see Hull2D::closedGrahamScanFromVertex
     *
     * @post The first point of the resulting list of extremal points is 
     * guaranteed to be the one with maximal x-coordinate and y-coordinate. 
     *
     * @warning The orientation of the predicate and of the polar comparator 
     * should be the same. Otherwise, the procedure only returns the last convex hull edge. 
     * For instance, you may use a predicate that returns 'true' for three points 
     * counter-clockwise oriented together with PolarPointComparatorBy2x2DetComputer.    
     *
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aPredicate any ternary predicate  
     * @param aPolarComparator any polar comparator 
     * 
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incremental and writable iterator   
     * @tparam Predicate a model of ternary predicate
     * @tparam PolarComparator a model of CPolarPointComparator2D. 
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Predicate, 
	      typename PolarComparator >
    void grahamConvexHullAlgorithm(const ForwardIterator& itb, 
				   const ForwardIterator& ite,  
				   OutputIterator res, 
				   const Predicate& aPredicate, 
				   PolarComparator& aPolarComparator); 

    /**
     * @brief Procedure that retrieves the vertices
     * of the convex hull of a set of 2D points given by 
     * the range [ @a itb , @a ite ). 
     * This procedure follows the well-known Graham's algorithm
     * [Graham, 1972 : \cite Graham1972]
     * - choose a pole and sort the points in order of increasing angle about the pole
     * (with a counter-clockwise orientation). 
     * - scan the sorted list of points and remove some points so that the given 
     * predicate returns 'true' for all sets of three consecutive points. 
     * @see Hull2D::closedGrahamScanFromVertex
     *
     * @post The first point of the resulting list of extremal points is 
     * guaranteed to be the one with maximal x-coordinate and y-coordinate. 
     *
     * @warning The predicate must be chosen so that is returns 'true' 
     * for counter-clockwise oriented 3-point sets. Otherwise, the procedure
     * only returns the last convex hull edge.   
     *
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aPredicate any ternary predicate  
     * 
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incremental and writable iterator   
     * @tparam Predicate a model of ternary predicate
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Predicate, 
	      typename PolarComparator >
    void grahamConvexHullAlgorithm(const ForwardIterator& itb, 
				   const ForwardIterator& ite,  
				   OutputIterator res, 
				   const Predicate& aPredicate); 

    /**
     * @brief Procedure that retrieves the vertices
     * of the hull of a set of 2D points given by 
     * the range [ @a itb , @a ite ). 
     * This procedure follows the well-known monotone-chain algorithm
     * due to [Andrew, 1979 : \cite Andrew1979]
     * - first, points are sorted along the horizontal axis. 
     * - then, the lower and upper convex hull are computed by a simple
     * Graham scan. 
     * @see Hull2D::openGrahamScan
     * 
     * @post The first point of the resulting list of extremal points 
     * follows the one with minimal x-coordinate and y-coordinate. 
     * Orientation depends on the predicate. 
     *
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aPredicate any ternary predicate  
     * 
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incrementable and writable iterator   
     * @tparam Predicate a model of ternary predicate
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Predicate >
    void andrewConvexHullAlgorithm(const ForwardIterator& itb, 
				   const ForwardIterator& ite,  
				   OutputIterator res, 
				   const Predicate& aPredicate ); 


    /**
     *  @brief Procedure to compute the convex hull thickness given
     *  from different definitions (Horizontal/vertical or Euclidean
     *  distances). It takes as input the vertices of the hull given
     *  by the range [@a itbn, @a ite).  The procedure applies the
     *  classic rotating caliper to recover all anti-podal pairs.
     *
     * Typical use:
     * @code 
     *  typedef PointVector<2,DGtal::int32_t> Point;
     *  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int32_t> Functor;  
     *  DGtal::MelkmanConvexHull<Point, Functor> ch; 
     *  ch.add(Point(0,0));
     *  ch.add(Point(11,1));
     *  ch.add(Point(12,3));
     *  ch.add(Point(8,3));
     *  ch.add(Point(4,5));
     *  ch.add(Point(2,6));
     *  ch.add(Point(1,4));
     *  double th = computeHullThickness(ch.begin(), ch.end(), 
     *                                   DGtal::functions::Hull2D::EuclideanThickness);
     * @endcode  
     * @param[in] itb begin iterator on the convex hull points.
     * @param[in] ite end iterator on the convex hull points.
     * @param[in] def definition of the thickness used in the estimation (i.e HorizontalVerticalThickness or EuclideanThickness)
     *
     * @note If the convex hull contains 0, 1 or 2 points the thickness of 0 is returned.
     * @warning The convex hull should be oriented in counter clockwise else it will return wrong result.
     **/
    template <typename ForwardIterator >
    double computeHullThickness(const ForwardIterator& itb, 
                                const ForwardIterator& ite,
                                const ThicknessDefinition& def);


    /**
     *  @brief Procedure to compute the convex hull thickness given
     *  from different definitions (Horizontal/vertical or Euclidean
     *  distances). It takes as input the vertices of the hull given
     *  by the range [@a itbn, @a ite).  The procedure applies the
     *  classic rotating caliper to recover all anti-podal pairs.
     *
     * Typical use:
     * @code 
     *  typedef PointVector<2,DGtal::int32_t> Point;
     *  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int32_t> Functor;  
     *  DGtal::MelkmanConvexHull<Point, Functor> ch; 
     *  ch.add(Point(0,0));
     *  ch.add(Point(11,1));
     *  ch.add(Point(12,3));
     *  ch.add(Point(8,3));
     *  ch.add(Point(4,5));
     *  ch.add(Point(2,6));
     *  ch.add(Point(1,4));
     *  Point p, q, s;
     *  double th = computeHullThickness(ch.begin(), ch.end(), 
     *                                   DGtal::functions::Hull2D::EuclideanThickness, p, q, s);
     * @endcode       
     * @param[in] itb begin iterator on the convex hull points.
     * @param[in] ite end iterator on the convex hull points.
     * @param[in] def definition of the thickness used in the estimation (i.e HorizontalVerticalThickness or EuclideanThickness)
     * @param[out] antipodalEdgeP one point of the antipodal edge associated to the minimal value of convex hull thickness. 
     * @param[out] antipodalEdgeQ one point of the antipodal edge associated to the minimal value of convex hull thickness. 
     * @param[out] antipodalVertexR the vertex of the antipodal pair associated to the minimal value of convex hull thickness. 
     * @note If the convex hull contains 0, 1 or 2 points the thickness of 0 is returned and the antipodal points are updated with the first points (if they exist).
     * @warning The convex hull should be oriented in counter clockwise else it will return wrong result.
     **/
    template <typename ForwardIterator, 
              typename TInputPoint >
    double computeHullThickness(const ForwardIterator& itb, 
                                const ForwardIterator& ite,
                                const ThicknessDefinition& def,
                                TInputPoint& antipodalEdgeP,
                                TInputPoint& antipodalEdgeQ,
                                TInputPoint& antipodalVertexR);


    /**
     * Computes the angle between the line (@a a,@a b) and (@a c,@a d)
     * @param[in] a one of point defining the first line. 
     * @param[in] b a second point defining the first line. 
     * @param[in] c a third point defining the second line. 
     * @param[in] d a third point defining the second line. 
     
     **/
    template<typename TInputPoint>
    inline
    double getAngle(const TInputPoint& a, const TInputPoint& b,const TInputPoint& c,const  TInputPoint& d);
    
    /**
     * Computes the thickness of an anti podal pair (represented by
     * the segment [ @a p , @a q ] and vertex @a r) according to the given
     * distance @a def definition.  
     *
     * If the distance definition is @a HorizontalVerticalThickness, it
     * returns the minimal distance between the vertical/horizontal
     * projection of @a r on ( @a p , @a q ).
     *
     * If the distance definition is @a EuclideanThickness, it returns
     * the distance between r and its projection on the line ( @a p ,@a q ).
     *
     * @param[in] p the first point of the edge anti podal pair.
     * @param[in] q the second point of the edge anti podal pair.
     * @param[in] r the vertex of the anti podal pair.
     * @param[in] def definition of the thickness used in the estimation (i.e HorizontalVerticalThickness or EuclideanThickness).
     *
     **/
    template<typename TInputPoint>
    double getThicknessAntipodalPair(const TInputPoint& p, const TInputPoint& q, 
                                     const TInputPoint& r, const ThicknessDefinition& def);

    /**
     * Computes the horizontal distance a point @c according to the segment [ @a a , @a b ].
     * (i.e the horizontal projection distance of @c on [ @a a , @a b ]). 
     * @note if the segment [@a a, @a b] is horizontal (i.e @a a [1]==@a b[1]) then an infinite value (std::numerics<double>::max()) is returned. 
     *
     *  @param[in] a one point of the segment.
     *  @param[in] b a second point of the segment.
     *  @param[in] c the point for which the horizontal distance is computed.
     *  @param[out] isInside indicates if the projected point is inside the segment or not.
     **/    
    template< typename TInputPoint>
    double
    computeHProjDistance(const TInputPoint& a, const TInputPoint& b, const TInputPoint& c, bool& isInside );


    /**
     * Computes the vertical distance a point @c according to the segment [@a a, @a b].
     * (i.e the vertical projection distance of @c on [@a a,@a b]. 
     * @note if the segment [@a a, @a b] is vertical (i.e @a a [0]== @a b [0]) then an infinite value (std::numerics<double>::max()) is returned. 
     *
     *  @param[in] a one point of the segment.
     *  @param[in] b a second point of the segment.
     *  @param[in] c the point for which the vertical distance is computed.
     *  @param[out] isInside indicates if the projected point is inside the segment or not.
     **/    
    template< typename TInputPoint>
    double
    computeVProjDistance(const TInputPoint& a, const TInputPoint& b, const TInputPoint& c, bool& isInside );


    /**
     * Computes the euclidean distance a point @a c according to the segment [@a a, @a b].
     * (i.e the distance between @a c and its projected point on [@a a,@a b]. 
     *
     *  @param[in] a one point of the segment.
     *  @param[in] b a second point of the segment.
     *  @param[in] c the point for which the vertical distance is computed.
     *  @param[out] isInside indicates if the projected point is inside the segment or not.
     **/
    template< typename TInputPoint>
    double
    computeEuclideanDistance(const TInputPoint& a, const TInputPoint& b, const TInputPoint& c, bool& isInside );
    
      

  } // namespace convexHull2D

  } // namespace functions

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes friend functions.
#include "DGtal/geometry/tools/MelkmanConvexHull.h"

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/Hull2DHelpers.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Hull2DHelpers_h

#undef Hull2DHelpers_RECURSES
#endif // else defined(Hull2DHelpers_RECURSES)
