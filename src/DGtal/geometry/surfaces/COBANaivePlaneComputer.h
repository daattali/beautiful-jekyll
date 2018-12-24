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
 * @file COBANaivePlaneComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Emilie Charrier
 * @author Lilian Buzer
 *
 * @date 2012/09/20
 *
 * Header file for module COBANaivePlaneComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(COBANaivePlaneComputer_RECURSES)
#error Recursive header files inclusion detected in COBANaivePlaneComputer.h
#else // defined(COBANaivePlaneComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define COBANaivePlaneComputer_RECURSES

#if !defined COBANaivePlaneComputer_h
/** Prevents repeated inclusion of headers. */
#define COBANaivePlaneComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CSpace.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/arithmetic/IntegerComputer.h"
#include "DGtal/arithmetic/LatticePolytope2D.h"
#include "DGtal/geometry/surfaces/ParallelStrip.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class COBANaivePlaneComputer
  /**
   * Description of template class 'COBANaivePlaneComputer' <p> \brief Aim: A
   * class that contains the COBA algorithm (Emilie Charrier, Lilian
   * Buzer, DGCI2008) for recognizing pieces of digital planes of given axis
   * width. When the width is 1, it corresponds to naive planes. The
   * axis is specified at initialization of the object.
   *
   * As a (3D) geometric primitive, it obeys to a subset of the
   * concept CSegmentComputer. It is copy constructible,
   * assignable. It is iterable (inner type ConstIterator, begin(),
   * end()). It has methods \ref extend(), extend( InputIterator,
   * InputIterator) and \ref isExtendable(),
   * isExtendable(InputIterator, InputIterator).  The object stores
   * all the distinct points \c p such that 'extend( \c p )' was
   * successful. It is thus a model of boost::ForwardContainer (non
   * mutable).
   *
   * It is also a model of concepts::CPointPredicate (returns 'true' iff a point
   * is within the current bounds).
   *
   * Note on complexity: The complexity is highly dependent on the way
   * points are added to the object. Let \a D be the diameter and \a n
   * be the number of points already added. Assume small
   * integers. Complexity of adding a point that do not change the
   * normal of the plane is \f$ O(\log(n)) \f$. When it changes the
   * normal, the number of cuts is upper bounded by some \f$
   * O(\log(D)) \f$, each cut costs \f$ O(n+m\log(D) ) \f$, where \a m
   * is the number of sides of the convex polygon of
   * constraints. However, when recognizing a piece of naive plane,
   * the number of times \a K where the normal should be updated is
   * rather limited to some \f$ O(\log(D)) \f$.
   *
   * Note on execution times: The user should favor int64_t instead of
   * BigInteger whenever possible (diameter smaller than 500). The
   * speed-up is between 10 and 20 for these diameters. For greater
   * diameters, it is necessary to use BigInteger (see below).
   *
   * @tparam TSpace specifies the type of digital space in which lies
   * input digital points. A model of CSpace.
   *
   * @tparam TInternalInteger specifies the type of integer used in
   * internal computations. The type should be able to hold integers
   * of order (2*D^3)^2 if D is the diameter of the set of digital
   * points. In practice, diameter is limited to 20 for int32_t,
   * diameter is approximately 500 for int64_t, and whatever with
   * BigInteger/GMP integers. For huge diameters, the slow-down is
   * polylogarithmic with respect to the diameter.
   *
   * Essentially a backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   *
   @code
   typedef SpaceND<3,int> Z3;
   typedef COBANaivePlaneComputer< Z3, int64_t > NaivePlaneComputer;
   NaivePlaneComputer plane;
   plane.init( 2, 100, 1, 1 ); // axis is z, diameter is 100, width is 1/1 => naive 
   plane.extend( Point( 10, 0, 0 ) ); // return 'true'
   plane.extend( Point( 0, 8, 0 ) );  // return 'true'
   plane.extend( Point( 0, 0, 6 ) );  // return 'true'
   plane.extend( Point( 5, 5, 5 ) );  // return 'false'
   // There is no naive plane going through the 3 first points and the last one.
   @endcode
   *
   * Model of boost::DefaultConstructible, boost::CopyConstructible,
   * boost::Assignable, boost::ForwardContainer, concepts::CAdditivePrimitiveComputer, concepts::CPointPredicate.
   */
  template < typename TSpace, 
             typename TInternalInteger >
  class COBANaivePlaneComputer
  {

    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
    BOOST_CONCEPT_ASSERT(( concepts::CInteger< TInternalInteger > ));
    BOOST_STATIC_ASSERT(( TSpace::dimension == 3 ));

    // ----------------------- public types ------------------------------
  public:
    typedef TSpace Space;
    typedef typename Space::Point Point;
    typedef std::set< Point > PointSet;
    typedef typename PointSet::size_type Size;
    typedef typename PointSet::const_iterator ConstIterator;
    typedef typename PointSet::iterator Iterator;
    typedef TInternalInteger InternalInteger;
    typedef IntegerComputer< InternalInteger > MyIntegerComputer;
    typedef ParallelStrip<Space, true, true> Primitive;
    typedef PointVector< 3, InternalInteger > IntegerVector3;

    // ----------------------- std public types ------------------------------
  public:
    typedef typename PointSet::const_iterator const_iterator;
    typedef typename PointSet::const_pointer const_pointer;
    typedef typename PointSet::const_reference const_reference;
    typedef typename PointSet::value_type value_type;
    typedef typename PointSet::difference_type difference_type;
    typedef typename PointSet::size_type size_type;

    // ----------------------- internal types ------------------------------
  private:
    typedef PointVector< 3, InternalInteger > InternalPoint3;
    typedef SpaceND< 2, InternalInteger > InternalSpace2;
    typedef typename InternalSpace2::Point InternalPoint2;
    typedef LatticePolytope2D< InternalSpace2 > ConvexPolygonZ2;
    typedef typename ConvexPolygonZ2::HalfSpace HalfSpace;

    /**
       Defines the state of the algorithm, the part of the data that
       may change after initialization of the COBANaivePlaneComputer
       object. Only the set of points is not stored here.
    */
    struct State {
      InternalInteger max;     /**< current max dot product. */
      InternalInteger min;     /**< current min dot product. */
      Point ptMax;             /**< 3D point giving the max dot product. */
      Point ptMin;             /**< 3D point giving the min dot product. */
      ConvexPolygonZ2 cip;     /**< current constraint integer polygon. */
      InternalPoint3 centroid; /**< current centroid of cip. */
      InternalPoint3 N;        /**< current normal vector. */
    };

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~COBANaivePlaneComputer();

    /**
     * Constructor. The object is not valid and should be initialized.
     * @see init
     */
    COBANaivePlaneComputer();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    COBANaivePlaneComputer ( const COBANaivePlaneComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    COBANaivePlaneComputer & operator= ( const COBANaivePlaneComputer & other );

    /**
       @return the object that performs integer calculation.
    */
    MyIntegerComputer & ic() const;

    /**
     * Clear the object, free memory. The plane keeps its main axis,
     * diameter and width, but contains no point.
     */
    void clear();

    /**
     * All these parameters cannot be changed during the process.
     * After this call, the object is in a consistent state and can
     * accept new points for recognition. Calls clear so that the
     * object is ready to be extended.
     *
     * @param axis the main axis (0,1,2) for x, y or z.
     *
     * @param diameter the diameter for the set of points (maximum
     * distance between the given points)
     *
     * @param widthNumerator the maximal axis-width (x,y,or z) for the
     * plane is defined as the rational number \a widthNumerator / \a
     * widthDenominator (default is 1/1, i.e. naive plane).
     *
     * @param widthDenominator the maximal axis-width (x,y,or z) for
     * the plane is defined as the rational number \a widthNumerator /
     * \a widthDenominator (default is 1/1, i.e. naive plane).
     */
    void init( Dimension axis, InternalInteger diameter, 
               InternalInteger widthNumerator = NumberTraits< InternalInteger >::ONE, 
               InternalInteger widthDenominator = NumberTraits< InternalInteger >::ONE );

    /**
     * @return the number of vertices/edges of the convex integer polygon of solutions.
     */
    Size complexity() const;

    //-------------------- model of ForwardContainer -----------------------------
  public:

    /**
     * @return the number of distinct points in the current naive plane.
     */
    Size size() const;

    /**
     * @return 'true' if and only if this object contains no point.
     */
    bool empty() const;

    /**
     * @return a const iterator pointing on the first point stored in the current naive plane.
     */
    ConstIterator begin() const;

    /**
     * @return a const iterator pointing after the last point stored in the current naive plane.
     */
    ConstIterator end() const;

    /**
     * NB: std version.
     * @return the maximal allowed number of points in the current naive plane.
     * @see maxSize
     */
    Size max_size() const;

    /**
     * same as max_size
     * @return the maximal allowed number of points in the current naive plane.
     */
    Size maxSize() const;


    //-------------------- model of concepts::CPointPredicate -----------------------------
  public:

    /**
     * Checks if the point \a p is in the current digital
     * plane. Therefore, a COBANaivePlaneComputer is a model of
     * concepts::CPointPredicate.
     *
     * @param p any 3D point.
     *
     * @return 'true' if it is in the current plane, false otherwise.
     */
    bool operator()( const Point & p ) const;

    //-------------------- model of CIncrementalPrimitiveComputer -----------------------------
  public:

    /**
     * Adds the point \a p to this plane if it is within the current
     * bounds. The plane parameters are not updated.
     *
     * @param p any 3D point (in the specified diameter).
     *
     * @return 'true' if \a p is in the plane, 'false' otherwise (the
     * object is then in its original state).
     */
    bool extendAsIs( const Point & p );

    /**
     * Adds the point \a p and checks if we have still a digital plane
     * of specified width. The plane parameters may be updated so as
     * to include the new point.
     *
     * @param p any 3D point (in the specified diameter).
     *
     * @return 'true' if it is still a plane, 'false' otherwise (the
     * object is then in its original state).
     */
    bool extend( const Point & p );

    /**
     * Checks if we have still a digital plane of specified width when
     * adding point \a p. The object is left unchanged whatever the
     * returned value. The invariant is 'this->isExtendable( p ) ==
     * true <=> this->extend( p ) == true'.
     *
     * @param p any 3D point (in the specified diameter).
     *
     * @return 'true' if this is still a plane, 'false' otherwise.
     */
    bool isExtendable( const Point & p ) const;

    //-------------------- model of CAdditivePrimitiveComputer -----------------------------
  public:

    /**
     * Adds the range of points [\a it, \a itE) and checks if we have
     * still a digital plane of specified width. The plane parameters
     * may be updated so as to include all the new points. All points
     * pointed by iterators should be in the diameter of this object.
     *
     * @tparam TInputIterator any model of InputIterator on Point.
     * @param it an iterator on the first element of the range of 3D points.
     * @param itE an iterator after the last element of the range of 3D points.
     *
     * @return 'true' if it is still a plane, 'false' otherwise (the
     * object is then in its original state).
     */
    template <typename TInputIterator>
    bool extend( TInputIterator it, TInputIterator itE );

    /**
     * Checks if we have still a digital plane of specified width when
     * adding the range of points [\a it, \a itE). The object is left
     * unchanged whatever the returned value.  All points pointed by
     * iterators should be in the diameter of this object. The
     * invariant is 'this->isExtendable( it, itE ) == true <=>
     * this->extend( it, itE ) == true'.
     *
     * @tparam TInputIterator any model of InputIterator on Point.
     * @param it an iterator on the first element of the range of 3D points.
     * @param itE an iterator after the last element of the range of 3D points.
     *
     * @return 'true' if this is still a plane, 'false' otherwise.
     */
    template <typename TInputIterator>
    bool isExtendable( TInputIterator it, TInputIterator itE ) const;

    //-------------------- Primitive services -----------------------------
  public:

    /**
       @return the current primitive recognized by this computer,
       which is a ParallelStrip of axis width smaller than the one
       specified at instanciation. 

       @note The returned primitive has the form \f$\mu \le \vec{N}
       \cdot \vec{X} \le \mu + \epsilon\f$. It is guaranteed that its axis
       width is strictly less than the value \a widthNumerator / \a
       widthDenominator specified with method \ref init.
    */
    Primitive primitive() const;

    //-------------------- Parameters services -----------------------------
  public:

    /**
     * @tparam Vector3D any type T such that T.operator[](int i)
     * returns a reference to a double. i ranges in 0,1,2.
     *
     * @param [in,out] normal  the current normal vector 
     */
    template <typename Vector3D>
    void getNormal( Vector3D & normal ) const;

    /**
     * @return a reference to the current normal vector (exact form).
     */
    const IntegerVector3 & exactNormal() const;

    /**
     * @tparam Vector3D any type T such that T.operator[](int i)
     * returns a reference to a double. i ranges in 0,1,2.
     *
     * @param [in,out] normal (updates) the current unit normal vector 
     */
    template <typename Vector3D>
    void getUnitNormal( Vector3D & normal ) const;

    /**
     * If n is the unit normal to the current plane, then n.x >= min
     * and n.x <= max are the two half-planes defining it.
     *
     * @param min the lower bound (corresponding to the unit vector).
     * @param max the upper bound (corresponding to the unit vector).
     */
    void getBounds( double & min, double & max ) const;

    /**
     * @pre ! empty()
     * @return the current minimal point of the plane, i.e. the one
     * with the smallest scalar product with the current normal
     * vector. Note that other points may also have a minimum value.
     */
    const Point & minimalPoint() const;

    /**
     * @pre ! empty()
     * @return the current maximal point of the plane, i.e. the one
     * with the highest scalar product with the current normal
     * vector. Note that other points may also have a maximum value.
     */
    const Point & maximalPoint() const;

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

    // ------------------------- Private Datas --------------------------------
  private:
    Dimension myAxis;          /**< the main axis used in all subsequent computations. */
    InternalInteger myG;       /**< the grid step used in all subsequent computations. */
    InternalPoint2 myWidth;    /**< the plane width as a positive rational number myWidth[0]/myWidth[1] */
    PointSet myPointSet;       /**< the set of points within the plane. */ 
    State myState;             /**< the current state that defines the plane being recognized. */
    InternalInteger myCst1;    /**<  ( (int) ceil( get_si( myG ) * myWidth ) + 1 ). */
    InternalInteger myCst2;    /**<  ( (int) floor( get_si( myG ) * myWidth ) - 1 ). */
    mutable InternalInteger _v;/**< temporary variable used in computations. */
    mutable State _state;      /**< Temporary state used in computations. */
    mutable InternalPoint2 _grad; /**< temporary variable to store the current gradient. */
    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:

    /**
     * Recompute centroid of polygon of solution and deduce the
     * current normal vector.  It is called after any modification of
     * the convex polygon representing the set of solution.
     *
     * @param state (modified) the state where the fields state.cip are used in computation and where
     * fields state.centroid and state.N are updated.
     */
    void computeCentroidAndNormal( State & state ) const;

    /**
     * Performs the double cut in parameter space according to the
     * current gradient and width. The centroid and normals are no
     * more valid (computeCentroidAndNormal should be called
     * afterwards).
     *
     * @param grad (altered, but not modified) the gradient used to
     * update the polygon of solutions state.cip.
     *
     * @param state (modified) the state where the fields
     * state.ptMin, state.ptMax, state.cip are used in computation
     * and where field state.cip is updated.
     */
    void doubleCut( InternalPoint2 & grad, State & state ) const;

    /**
     * Computes the min and max values/arguments of the scalar product
     * between the normal state.N and the points in the range
     * [itB,itE). Overwrites state.min, state.max at the start.
     *
     * @tparam TInputIterator any model of InputIterator.
     * @param state (modified) the state where the normal N is used in
     * computation and where fields state.min, state.max,
     * state.ptMin, state.ptMax are updated.
     *
     * @param itB an input iterator on the first point of the range.
     * @param itE an input iterator after the last point of the range.
     */
    template <typename TInputIterator>
    void computeMinMax( State & state, TInputIterator itB, TInputIterator itE ) const;

    /**
     * Updates the min and max values/arguments of the scalar product
     * between the normal state.N and the points in the range
     * [itB,itE). Do not overwrite state.min, state.max at the start.
     *
     * @tparam TInputIterator any model of InputIterator.
     *
     * @param state (modified) the state where the normal N is used in
     * computation and where fields state.min, state.max,
     * state.ptMin, state.ptMax are updated.
     *
     * @param itB an input iterator on the first point of the range.
     * @param itE an input iterator after the last point of the range.
     * @return 'true' if any of the fields state.min, state.max,
     * state.ptMin, state.ptMax have been updated, 'false'
     * otherwise.
     */
    template <typename TInputIterator>
    bool updateMinMax( State & state, TInputIterator itB, TInputIterator itE ) const;

    /**
     * @param state the state where the normal state.N, the scalars state.min and state.max are used in
     * computations.
     *
     * @return 'true' if the current width along state.N (computed
     * from the difference of state.max and state.min) is strictly
     * inferior to the maximal specified width (in myWidth), 'false'
     * otherwise.
     */
    bool checkPlaneWidth( const State & state ) const;

    /**
     * @param grad (updated) the value of a gradient used to cut the
     * polygon of solutions.
     *
     * @param state the state where the iterators state.ptMin and
     * state.ptMax are used in computations.
     */
    void computeGradient( InternalPoint2 & grad, const State & state ) const;

  }; // end of class COBANaivePlaneComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'COBANaivePlaneComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'COBANaivePlaneComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, typename TInternalInteger>
  std::ostream&
  operator<< ( std::ostream & out, const COBANaivePlaneComputer<TSpace, TInternalInteger> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/COBANaivePlaneComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined COBANaivePlaneComputer_h

#undef COBANaivePlaneComputer_RECURSES
#endif // else defined(COBANaivePlaneComputer_RECURSES)
