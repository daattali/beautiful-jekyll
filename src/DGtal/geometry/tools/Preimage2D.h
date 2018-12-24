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
 * @file Preimage2D.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/10/26
 *
 * @brief Header file for module Preimage2D.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Preimage2D_RECURSES)
#error Recursive header files inclusion detected in Preimage2D.h
#else // defined(Preimage2D_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Preimage2D_RECURSES

#if !defined Preimage2D_h
/** Prevents repeated inclusion of headers. */
#define Preimage2D_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <list>
#include "DGtal/base/Common.h"
#include "DGtal/base/OpInSTLContainers.h"
#include "DGtal/shapes/fromPoints/Point2ShapePredicate.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Preimage2D
  /**
   * @brief Aim: Computes the preimage of the 2D Euclidean shapes 
   * crossing a sequence of n straigth segments in O(n),
   * with the algorithm of O'Rourke (1981). 
   *
   * @note Joseph O'Rourke, An on-line algorithm for fitting straight lines between data ranges,
  Communications of the ACM, Volume 24, Issue 9, September 1981, 574--578. 
   *
   * For all i from 0 to n, the straight
   * segment i is described by its two end points Pi and Qi.
   * The set of shapes considered here are those that 
   * can be uniquely defined by two points and that separate 
   * the 2D plane into two disjoint parts (e.g. straight lines, 
   * circles passing through a given point). Consequently, the 
   * points Pi and the points Qi are assumed to lie in either 
   * side of the shape.
   *
   * The user of this class has to decide from its input set 
   * of segments and the shape used whether a linear-time algorithm 
   * is possible or not. If yes (e.g. preimage of straight lines crossing a set of 
   * vertical segments of increasing x-coordinate) the algorithm of O'Rourke
   * will return the right output.
   *
   * @tparam Shape  a model of COrientableHypersurface
   *
   * You can define your preimage type from a given shape type as follows:
   * @snippet geometry/tools/examplePreimage.cpp PreimageTypedefFromStraightLine
   *
   * Here is another example:
   * @snippet geometry/tools/examplePreimage.cpp PreimageTypedefFromCircle
   *
   * Then, here is the basic usage of this class:
   * @snippet geometry/tools/examplePreimage.cpp PreimageUsageFromIncidentPointsRange
   *
   * @see examplePreimage.cpp testPreimage.cpp
   */
  template <typename Shape>
  class Preimage2D
  {


    // ----------------------- Types ------------------------------
  public:

    typedef typename Shape::Point Point;
    typedef typename Shape::Point Vector;
    //container of points
    typedef std::list<Point> Container;
    

  private:

    //Iterators on the container
    typedef typename std::list<Point>::iterator ForwardIterator;
    typedef typename std::list<Point>::reverse_iterator BackwardIterator;
    typedef typename std::list<Point>::const_iterator ConstForwardIterator;
    typedef typename std::list<Point>::const_reverse_iterator ConstBackwardIterator;

    //Predicates used to decide whether the preimage
    //has to be updated or not
    typedef functors::Point2ShapePredicate<Shape,false,true> 
      PHullBackQHullFrontPred; 
    typedef functors::Point2ShapePredicate<Shape,true,true> 
      QHullBackPHullFrontPred; 
    typedef functors::Point2ShapePredicate<Shape,true,true> 
      PHullFrontQHullBackPred; 
    typedef functors::Point2ShapePredicate<Shape,false,true> 
      QHullFrontPHullBackPred; 
    //Predicates used to update the hulls
    typedef functors::Point2ShapePredicate<Shape,true,false> 
      FrontPHullUpdatePred; 
    typedef functors::Point2ShapePredicate<Shape,false,false> 
      FrontQHullUpdatePred; 
    typedef functors::Point2ShapePredicate<Shape,false,false> 
      BackPHullUpdatePred; 
    typedef functors::Point2ShapePredicate<Shape,true,false> 
      BackQHullUpdatePred; 
    


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Constructor.
     * @param firstPoint  the end point of the first straight segment expected to lie in the interior of the separating shapes
     * @param secondPoint  the end point of the first straight segment expected to lie in the exterior of the separating shapes
     * @param aShape  any shape
     */
    Preimage2D(const Point & firstPoint, const Point & secondPoint, const Shape & aShape );

    /**
     * Destructor. Does nothing.
     */
    ~Preimage2D();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    Preimage2D ( const Preimage2D & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Preimage2D & operator= ( const Preimage2D & other );

    /**
    *  Equality operator
    * @param other the object to compare with.
    * @return 'true' if the points of @a myPHull
    * match to those of @a other.myPHull and if 
    * the points of @a myQHull match to those of 
    * @a other.myQHull, 'false' otherwise.
    *
    * NB: linear in the size of @a myPHull and @a myQHull
    */
    bool operator==( const Preimage2D & other) const;

    /**
    *  Difference operator
    * @param other the object to compare with.
    * @return 'true' if not equal, 'false' otherwise.
    */
    bool operator!=( const Preimage2D & other) const;

    /**
     * Decide whether a new constraint that is added at the front
     * (with respect to a clockwise-oriented scan)
     * makes the preimage empty because of point @a aP or not
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'true' if the new constraint makes the preimage empty
     * because of point @a aP and 'false' otherwise.
     */
    bool isLeftExteriorAtTheFront(const Point & aP, const Point & aQ);

    /**
     * Decide whether a new constraint that is added at the back
     * (with respect to a clockwise-oriented scan)
     * makes the preimage empty because of point @a aQ or not
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'true' if the new constraint makes the preimage empty
     * because of point @a aQ and 'false' otherwise.
     */
    bool isLeftExteriorAtTheBack(const Point & aP, const Point & aQ);

    /**
     * Decide whether a new constraint that is added at the front
     * (with respect to a clockwise-oriented scan)
     * makes the preimage empty because of point @a aQ or not
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'true' if the new constraint makes the preimage empty
     * because of point @a aQ and 'false' otherwise.
     */
    bool isRightExteriorAtTheFront(const Point & aP, const Point & aQ);

    /**
     * Decide whether a new constraint that is added at the front
     * (with respect to a clockwise-oriented scan)
     * makes the preimage empty because of point @a aP or not
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'true' if the new constraint makes the preimage empty
     * because of point @a aP and 'false' otherwise.
     */
    bool isRightExteriorAtTheBack(const Point & aP, const Point & aQ);

    /**
     * Decide whether a new constraint can be added at the front
     * (with respect to a clockwise-oriented scan)
     * without making the preimage empty or not
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'false' if the new constraint make the preimage empty
     * 'true' otherwise.
     */
    bool canBeAddedAtTheFront(const Point & aP, const Point & aQ);

    /**
     * Decide whether a new constraint can be added at the back
     * (with respect to a clockwise-oriented scan)
     * without making the preimage empty or not
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'false' if the new constraint make the preimage empty
     * 'true' otherwise.
     */
    bool canBeAddedAtTheBack(const Point & aP, const Point & aQ);
    
    /**
     * Updates the current preimage with 
     * the constraints involved by the two 
     * end points of a new segment
     * (adding to the front with respect to a clockwise-oriented scan)
     *
     * Nb: in O(n)
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'false' if the updated preimage is empty, 
     * 'true' otherwise.
     */
    bool addFront(const Point & aP, const Point & aQ);

    /**
     * Updates the current preimage with 
     * the constraints involved by the two 
     * end points of a new segment
     * (adding to the back with respect to a clockwise-oriented scan)
     *
     * Nb: in O(n)
     *
     * @param aP  the end point of the new straight segment expected to lie in the interior of the separating shapes
     * @param aQ  the end point of the new straight segment expected to lie in the exterior of the separating shapes
     *
     * @return 'false' if the updated preimage is empty, 
     * 'true' otherwise.
     */
    bool addBack(const Point & aP, const Point & aQ);

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
     * @return first upper leaning point.
     */
    Point Uf() const;

    /**
     * @return last upper leaning point.
     */
    Point Ul() const;

    /**
     * @return first lower leaning point.
     */
    Point Lf() const;

    /**
     * @return last lower leaning point.
     */
    Point Ll() const;
    
    /**
     * Get the parameters of one separating straight line
     * @param alpha  (returned) y-component of the normal
     * @param beta  (returned) x-component of the normal
     * @param gamma  (returned) intercept
     */
    void getSeparatingStraightLine(double& alpha, double& beta, double& gamma) const;
    
    /**
     * @return the shape used to separate the input points.
     */
    const Shape & shape() const
    {
      return myShape;
    };
    
    /**
     * @return the lower part of the preimage.
     */
    const Container & pHull() const
    {
      return myPHull;
    };
    
    /**
     * @return the upper part of the preimage.
     */
    const Container & qHull() const
    {
      return myQHull;
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

    /**
     * Shape used to separate the input points
     */
    Shape myShape;
  
    //lists of the vertices of the preimage
    /**
     * Lower part of the preimage
     * (whose vertices are Pi points)
     */
    Container myPHull;
    /**
     * Upper part of the preimage.
     * (whose vertices are Qi points)
     */
    Container myQHull;

    // ------------------------- Hidden services ------------------------------
  protected:


  private:

    /**
     * Updates the current preimage
     *
     * Nb: in O(n)
     *
     * @param aPoint  a new vertex of the preimage,
     * @param aContainer  the STL-like container to be updated,
     * @param anIterator  an iterator to its front (resp. back)
     * @param anEndIterator  an iterator pointing after its back 
     * (resp. before its front). 
     *
     * @tparam Iterator  the type of Iterator (either Container::iterator or Container::reverse_iterator)
     * @tparam Predicate  the type of Predicate
     */
    template <typename Iterator, typename Predicate>
    void update(const Point & aPoint, 
                Container & aContainer,
                Iterator & anIterator,
                const Iterator & anEndIterator);



    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Preimage2D


  /**
   * Overloads 'operator<<' for displaying objects of class 'Preimage2D'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Preimage2D' to write.
   * @return the output stream after the writing.
   */
   template <typename Shape>
  std::ostream&
  operator<< ( std::ostream & out, const Preimage2D<Shape> & object );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/tools/Preimage2D.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Preimage2D_h

#undef Preimage2D_RECURSES
#endif // else defined(Preimage2D_RECURSES)
