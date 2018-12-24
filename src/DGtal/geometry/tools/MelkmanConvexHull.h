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
 * @file MelkmanConvexHull.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/12/20
 *
 * Header file for module MelkmanConvexHull.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MelkmanConvexHull_RECURSES)
#error Recursive header files inclusion detected in MelkmanConvexHull.h
#else // defined(MelkmanConvexHull_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MelkmanConvexHull_RECURSES

#if !defined MelkmanConvexHull_h
/** Prevents repeated inclusion of headers. */
#define MelkmanConvexHull_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/CountedConstPtrOrConstPtr.h"
#include "DGtal/base/IteratorCirculatorTraits.h"
#include "DGtal/base/FrontInsertionSequenceToStackAdapter.h"
#include "DGtal/base/BackInsertionSequenceToStackAdapter.h"

#include "DGtal/geometry/tools/determinant/COrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/PredicateFromOrientationFunctor2.h"

#include "DGtal/geometry/tools/Hull2DHelpers.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class MelkmanConvexHull
  /**
   * \brief Aim: This class implements the on-line algorithm
   * of Melkman for the computation of the convex hull of 
   * a simple polygonal line (without self-intersection) 
   * [Melkman, 1987: \cite Melkman1987].
   *
   * This algorithm is based on a deque, which stores the vertices 
   * of the convex hull (for convenience, the first and last vertex 
   * contained in the deque are the same point). Since we assume 
   * that the input points form a simple polygonal line, a new point
   * cannot be located in the cone formed by the first and last edges
   * of the current convex hull. As a consequence, it is enough to update
   * the convex hull by a Graham scan from the front and/or from the back 
   * of the deque; it is never required to remove/insert points in the middle 
   * of the container. See \ref moduleHull2D for more details. 
   *
   * @see functions::Hull2D::updateHullWithAdaptedStack
   * 
   * Note that if the input points do not form a simple polygonal line, 
   * the behavior is not defined. 
   *
   * @tparam TPoint a model of point
   * @tparam TOrientationFunctor a model of COrientationFunctor2
   * (whose inner type 'Point' match to 'TPoint')
   */
  template <typename TPoint, 
	    typename TOrientationFunctor >
  class MelkmanConvexHull
  {
    // ----------------------- Types ------------------------------------------
  public:

    /**
     * Self type
     */
    typedef MelkmanConvexHull<TPoint, TOrientationFunctor> Self;

    /**
     * Type of point
     */
    typedef TPoint Point; 
    /**
     * Type of orientation functor
     */
    typedef TOrientationFunctor Functor;
    BOOST_CONCEPT_ASSERT(( concepts::COrientationFunctor2<Functor> )); 
    //the two types of points must be the same
    BOOST_STATIC_ASSERT (( boost::is_same< Point, typename Functor::Point >::value )); 

    /**
     * Type of predicate devoted to the backward scan
     */
    typedef PredicateFromOrientationFunctor2<Functor,false,false> BackwardPredicate; 
    /**
     * Type of predicate devoted to the forward scan
     */
    typedef PredicateFromOrientationFunctor2<Functor,true,false> ForwardPredicate; 

    /**
     * Type of iterator on the convex hull vertices
     */
    typedef typename std::deque<Point>::const_iterator ConstIterator; 

    // ----------------------- Standard services ------------------------------
  public:

    MelkmanConvexHull( Alias<Functor> aFunctor); 
    MelkmanConvexHull(); 
    
    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Consider a new point and possibly update the convex hull. 
     * @param aPoint an extra point
     * @post if @a aPoint lies outside the current convex hull, 
     * this hull is then updated with @a aPoint as a vertex. 
     */
    void add ( const Point& aPoint );

    /**
     * Begin iterator
     * @return either a const iterator pointing past-the-end
     * if the container is empty or a const iterator pointing
     * after the first point otherwise. 
     * Rationale: we do not want to iterate over the same point, 
     * duplicated at the begin and at the end of the container.  
     */
    ConstIterator begin() const;

    /**
     * End iterator 
     * @return a const iterator to the end of the container
     */
    ConstIterator end() const;

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
     * Assignement Operator
     *
     * @param mch the object to copy.
     * @return a reference on 'this'.
     */
    Self & operator= ( const Self & mch );

    /**
     * @return the @a i-th point of the convex hull queue. 
     * @param i the index of the considered point.
     */
    const Point & operator[](unsigned int i) const;
    
    /**
     * @return the nomber of points constituing the convex hull.
     **/
    unsigned int size() const;
    
    /**
     * clear the current content of the convex hull.
     **/
    void clear();
    
    /**
     * Reverse the convex hull container allowing to change the order
     * of adding points from the front or from the back in reference
     * to an input contour. Such a reverse is important to avoid wrong
     * convexhull and to allow convex hull extension from two directions.
     **/
    void reverse();


    // ------------------------- Private Datas --------------------------------
  private:
    /**
     * Deque container, which stores the vertices of the convex hull
     * NB: the first and last point is the same. 
     */
    std::deque<Point> myContainer; 
    /**
     * Predicate devoted to the backward scan
     */
    BackwardPredicate myBackwardPredicate; 
    /**
     * Predicate devoted to the forward scan
     */
    ForwardPredicate myForwardPredicate; 
    /**
     * Used to define a default functor to allow default constructor
     **/
    Functor myDefaultFunctor;
    /**
     * first point used to reverse the convexhull container.
     **/
    Point myFirstPoint; 

    // ------------------------- Internals ------------------------------------
  private:
    
  }; // end of class MelkmanConvexHull

  /**
   * Overloads 'operator<<' for displaying objects of class 'MelkmanConvexHull'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'MelkmanConvexHull' to write.
   * @return the output stream after the writing.
   */
  template <typename TPoint, typename TOrientationFunctor>
  std::ostream&
  operator<< ( std::ostream & out, const MelkmanConvexHull<TPoint, TOrientationFunctor> & object );

  namespace functions
  {
  namespace Hull2D
  {
    /**
     * @brief Procedure that retrieves the vertices
     * of the hull of a set of 2D points given by 
     * the range [ @a itb , @a ite ). 
     * This procedure follows the well-known Melkman algorithm
     * [Melkman, 1979 : \cite Melkman1987]
     *
     * @see MelkmanConvexHull
     *
     * @param itb begin iterator
     * @param ite end iterator 
     * @param res output iterator used to export the retrieved points
     * @param aFunctor aFunctor  
     * 
     * @tparam ForwardIterator a model of forward and readable iterator
     * @tparam OutputIterator a model of incrementable and writable iterator   
     * @tparam Functor a model of COrientationFunctor2
     */
    template <typename ForwardIterator, 
	      typename OutputIterator, 
	      typename Functor >
    void melkmanConvexHullAlgorithm(const ForwardIterator& itb, 
				    const ForwardIterator& ite,  
				    OutputIterator res, 
				    Functor& aFunctor ); 
  } //namespace Hull2D
  } //namespace functions

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/MelkmanConvexHull.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MelkmanConvexHull_h

#undef MelkmanConvexHull_RECURSES
#endif // else defined(MelkmanConvexHull_RECURSES)
