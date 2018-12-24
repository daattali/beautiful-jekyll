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
 * @file COBAGenericNaivePlaneComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 * @author Emilie Charrier
 * @author Lilian Buzer
 *
 * @date 2012/09/20
 *
 * Header file for module COBAGenericNaivePlaneComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(COBAGenericNaivePlaneComputer_RECURSES)
#error Recursive header files inclusion detected in COBAGenericNaivePlaneComputer.h
#else // defined(COBAGenericNaivePlaneComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define COBAGenericNaivePlaneComputer_RECURSES

#if !defined COBAGenericNaivePlaneComputer_h
/** Prevents repeated inclusion of headers. */
#define COBAGenericNaivePlaneComputer_h

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
#include "DGtal/geometry/surfaces/COBANaivePlaneComputer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class COBAGenericNaivePlaneComputer
  /**
   * Description of template class 'COBAGenericNaivePlaneComputer' <p> \brief
   * Aim: A class that recognizes pieces of digital planes of given
   * axis width. When the width is 1, it corresponds to naive
   * planes. Contrary to COBANaivePlaneComputer, the axis is \b not specified
   * at initialization of the object. This class uses three instances
   * of COBANaivePlaneComputer, one per axis.
   *
   * As a (3D) geometric primitive, it obeys to a subset of the
   * concept CSegmentComputer. It is copy constructible,
   * assignable. It is iterable (inner type ConstIterator, begin(),
   * end()). You may clear() it. It has methods \ref extend(), extend(
   * InputIterator, InputIterator) and \ref isExtendable(),
   * isExtendable(InputIterator, InputIterator).  The object stores
   * all the distinct points \c p such that 'extend( \c p )' was
   * successful. It is thus a model of boost::ForwardContainer (non
   * mutable).
   *
   * It is also a model of concepts::CPointPredicate (returns 'true' iff a point
   * is within the current bounds).
   *
   * Note on complexity: See COBANaivePlaneComputer. Although it uses three
   * instances of COBANaivePlaneComputer, the recognition is \b not three
   * times slower. Indeed, recognition stops quickly on bad axes.
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
   * polylogarithmic with the diameter.
   *
   * Essentially a backport from [ImaGene](https://gforge.liris.cnrs.fr/projects/imagene).
   *
   @code
   typedef SpaceND<3,int> Z3;
   typedef COBAGenericNaivePlaneComputer< Z3, int64_t > NaivePlaneComputer;
   NaivePlaneComputer plane;
   plane.init( 100, 1, 1 ); // diameter is 100, width is 1/1 => naive 
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
  class COBAGenericNaivePlaneComputer
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
    typedef COBANaivePlaneComputer< Space, InternalInteger > COBAComputer;
    typedef typename COBAComputer::Primitive Primitive;

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
    typedef std::vector<Dimension>::iterator AxisIterator;
    typedef std::vector<Dimension>::const_iterator AxisConstIterator;
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~COBAGenericNaivePlaneComputer();

    /**
     * Constructor. The object is not valid and should be initialized.
     * @see init
     */
    COBAGenericNaivePlaneComputer();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    COBAGenericNaivePlaneComputer ( const COBAGenericNaivePlaneComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    COBAGenericNaivePlaneComputer & operator= ( const COBAGenericNaivePlaneComputer & other );

    /**
       @return the object that performs integer calculation.
    */
    MyIntegerComputer & ic() const;

    /**
       @return an active axis (or the active axis when there is only one).
    */
    Dimension active() const;

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
    void init( InternalInteger diameter, 
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
     * plane. Therefore, a COBAGenericNaivePlaneComputer is a model of
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
     * @param [in,out] normal (updates) the current normal vector 
     */
    template <typename Vector3D>
    void getNormal( Vector3D & normal ) const;

    /**
     * @tparam Vector3D any type T such that T.operator[](int i)
     * returns a reference to a double. i ranges in 0,1,2.
     *
     * @param normal (updates) the current unit normal vector 
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
    std::vector<Dimension> myAxes; /**< The list of active plane axes. Starts with {0,1,2}. At least one. */
    COBAComputer myComputers[ 3 ]; /**< The three COBA plane computers. */
    mutable std::vector<Dimension> _axesToErase; /**< Useful when erasing axes. */
    // ------------------------- Hidden services ------------------------------
  protected:


    // ------------------------- Internals ------------------------------------
  private:
  }; // end of class COBAGenericNaivePlaneComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'COBAGenericNaivePlaneComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'COBAGenericNaivePlaneComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, typename TInternalInteger>
  std::ostream&
  operator<< ( std::ostream & out, const COBAGenericNaivePlaneComputer<TSpace, TInternalInteger> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/COBAGenericNaivePlaneComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined COBAGenericNaivePlaneComputer_h

#undef COBAGenericNaivePlaneComputer_RECURSES
#endif // else defined(COBAGenericNaivePlaneComputer_RECURSES)
