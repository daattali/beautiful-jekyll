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
 * @file COBAGenericStandardPlaneComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/09/20
 *
 * Header file for module COBAGenericStandardPlaneComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(COBAGenericStandardPlaneComputer_RECURSES)
#error Recursive header files inclusion detected in COBAGenericStandardPlaneComputer.h
#else // defined(COBAGenericStandardPlaneComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define COBAGenericStandardPlaneComputer_RECURSES

#if !defined COBAGenericStandardPlaneComputer_h
/** Prevents repeated inclusion of headers. */
#define COBAGenericStandardPlaneComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <set>
#include "DGtal/base/Common.h"
#include "DGtal/base/IteratorAdapter.h"
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
  // template class COBAGenericStandardPlaneComputer
  /**
   * Description of template class 'COBAGenericStandardPlaneComputer'
   * <p> \brief Aim: A class that recognizes pieces of digital planes
   * of given axis width. When the diagonal width is \f$ 1 \times
   * \sqrt{3} \f$, it corresponds to standard planes. Contrary to
   * COBANaivePlaneComputer, the axis is \b not specified at
   * initialization of the object. This class uses four instances of
   * COBANaivePlaneComputer of axis z, by transforming points
   * \f$(x,y,z)\f$ to \f$(x \pm z, y \pm z, z)\f$.

   * As a (3D) geometric primitive computer, it obeys the concept
   * CAdditivePrimitiveComputer. It is copy constructible, assignable.
   * It has methods \ref extend(), extend( InputIterator,
   * InputIterator) and \ref isExtendable(),
   * isExtendable(InputIterator, InputIterator).  The object stores
   * all the distinct points \c p such that 'extend(\c p )' was
   * successful. It is thus a model of boost::ForwardContainer (non
   * mutable). It is iterable (inner type ConstIterator, begin(),
   * end()). You may clear() it.

   * It is also a model of concepts::CPointPredicate (returns 'true' iff a point
   * is within the current bounds).

   * Note on complexity: See COBAStandardPlaneComputer. Although it uses four
   * instances of COBAStandardPlaneComputer, the recognition is \b not four
   * times slower. Indeed, recognition stops quickly on bad orthants.

   * Note on execution times: The user should favor int64_t instead of
   * BigInteger whenever possible (diameter smaller than 500). The
   * speed-up is between 10 and 20 for these diameters. For greater
   * diameters, it is necessary to use BigInteger (see below).

   * @tparam TSpace specifies the type of digital space in which lies
   * input digital points. A model of CSpace.

   * @tparam TInternalInteger specifies the type of integer used in
   * internal computations. The type should be able to hold integers
   * of order (2*D^3)^2 if D is the diameter of the set of digital
   * points. In practice, diameter is limited to 20 for int32_t,
   * diameter is approximately 500 for int64_t, and whatever with
   * BigInteger/GMP integers. For huge diameters, the slow-down is
   * polylogarithmic with the diameter.

   *   @code
   *   typedef SpaceND<3,int> Z3;
   *   typedef COBAGenericStandardPlaneComputer< Z3, int64_t > StandardPlaneComputer;
   *   StandardPlaneComputer plane;
   *   plane.init( 100, 1, 1 ); * diameter is 100, width is 1/1 x sqrt(3) => standard
   *   plane.extend( Point( 10, 0, 0 ) ); // return 'true'
   *   plane.extend( Point( 0, 8, 0 ) );  // return 'true'
   *   plane.extend( Point( 0, 0, 6 ) );  // return 'true'
   *   plane.extend( Point( 5, 5, 5 ) );  // return 'false'
   *   // There is no standard plane going through the 3 first points and the last one.
   *   @endcode

   * Model of boost::DefaultConstructible, boost::CopyConstructible,
   * boost::Assignable, boost::ForwardContainer,
   * concepts::CAdditivePrimitiveComputer, concepts::CPointPredicate.

   * @advanced All accepted inserted points are stored in the
   * different naive plane computers, but they are stored
   * "transformed". This is why we adapt the iterator on the naive
   * plane computer with a boost::transform_iterator, such that the
   * points are transformed back when accessing to the value of the
   * iterator (notably in \ref begin and \ref end method).
   */
  template < typename TSpace,
             typename TInternalInteger >
  class COBAGenericStandardPlaneComputer
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
    typedef typename PointSet::const_iterator PointSetConstIterator;
    typedef typename PointSet::iterator PointSetIterator;
    typedef TInternalInteger InternalInteger;
    typedef IntegerComputer< InternalInteger > MyIntegerComputer;
    typedef COBANaivePlaneComputer< Space, InternalInteger > COBAComputer;
    typedef typename COBAComputer::Primitive Primitive;
    typedef typename COBAComputer::IntegerVector3 IntegerVector3;

    // ----------------------- internal types ------------------------------
  private:
    typedef std::vector<Dimension>::iterator OrthantIterator;
    typedef std::vector<Dimension>::const_iterator OrthantConstIterator;

    // --------- adapter types for standard to naive transformation --------
  public:
    /**
       This type is used to cast points from \f$(x,y,z)\f$ to \f$(x
       \pm z,y \pm z,z)\f$ and inversely. This is used when recognize
       a standard plane. Indeed, we only know how to recognize naive
       planes. So we dilate points of standard planes with this
       transform so that the standard plane becomes naive. Otherwise
       said, if \f$T_{\pm,\pm}: (x,y,z) \mapsto (x \pm z,y \pm
       z,z)\f$, then P is a standard plane iff one of \f$T_{+,+}(P),
       T_{+,-}(P), T_{-,+}(P), T_{-,-}(P)\f$ is a naive plane of main
       axis z.
    */
    struct Transform {
      typedef Point Value;
      typedef Point value_type;
      bool _posX; /**< true for +z on x, false for -z on x */
      bool _posY; /**< true for +z on y, false for -z on y */
      inline Transform() {}
      inline Transform( bool posX, bool posY ) : _posX( posX ), _posY( posY ) {}
      inline Point operator()( const Point & p ) const
      {
	if ( _posX ) {
	  if ( _posY ) return Point( p[ 0 ] + p[ 2 ], p[ 1 ] + p[ 2 ], p[ 2 ] );
	  else         return Point( p[ 0 ] + p[ 2 ], p[ 1 ] - p[ 2 ], p[ 2 ] );
	} else {
	  if ( _posY ) return Point( p[ 0 ] - p[ 2 ], p[ 1 ] + p[ 2 ], p[ 2 ] );
	  else         return Point( p[ 0 ] - p[ 2 ], p[ 1 ] - p[ 2 ], p[ 2 ] );
	}
      }
      inline bool isPlusZOnX() const { return _posX; }
      inline bool isPlusZOnY() const { return _posY; }
      inline Point inverse( const Point & p ) const
      {
	if ( _posX ) {
	  if ( _posY ) return Point( p[ 0 ] - p[ 2 ], p[ 1 ] - p[ 2 ], p[ 2 ] );
	  else         return Point( p[ 0 ] - p[ 2 ], p[ 1 ] + p[ 2 ], p[ 2 ] );
	} else {
	  if ( _posY ) return Point( p[ 0 ] + p[ 2 ], p[ 1 ] - p[ 2 ], p[ 2 ] );
	  else         return Point( p[ 0 ] + p[ 2 ], p[ 1 ] + p[ 2 ], p[ 2 ] );
	}
      }
      template <typename Vector3D>
      void transformBack( Vector3D & v )
      {
        if ( _posX ) v[ 2 ] += v[ 0 ];
	else         v[ 2 ] -= v[ 0 ];
        if ( _posY ) v[ 2 ] += v[ 1 ];
	else         v[ 2 ] -= v[ 1 ];
      }
      template <typename Vector3D>
      void transform( Vector3D & v )
      {
        if ( _posX ) v[ 2 ] -= v[ 0 ];
	else         v[ 2 ] += v[ 0 ];
        if ( _posY ) v[ 2 ] -= v[ 1 ];
	else         v[ 2 ] += v[ 1 ];
      }
    };

    /**
       We wrap a transform over the iterator on point that uses one of
       the functor Transform to cast back the point from the naive
       space to the standard space.
    */
    typedef boost::transform_iterator<Transform,PointSetConstIterator,Point,Point>
    ConstIterator;

    // ----------------------- std public types ------------------------------
  public:
    typedef ConstIterator const_iterator;
    typedef const Point* const_pointer;
    typedef const Point& const_reference;
    typedef Point value_type;
    typedef typename PointSet::difference_type difference_type;
    typedef typename PointSet::size_type size_type;

    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~COBAGenericStandardPlaneComputer();

    /**
     * Constructor. The object is not valid and should be initialized.
     * @see init
     */
    COBAGenericStandardPlaneComputer();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    COBAGenericStandardPlaneComputer ( const COBAGenericStandardPlaneComputer & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    COBAGenericStandardPlaneComputer & operator= ( const COBAGenericStandardPlaneComputer & other );

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
     * @param widthNumerator the maximal diagonal width for the plane
     * is defined as the rational number \a widthNumerator / \a
     * widthDenominator x sqrt(3). (default is 1/1 x sqrt(3),
     * i.e. standard plane).
     *
     * @param widthDenominator the maximal diagonal width for the
     * plane is defined as the rational number \a widthNumerator / \a
     * widthDenominator x sqrt(3). (default is 1/1 x sqrt(3),
     * i.e. standard plane).
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
     * @return the number of distinct points in the current standard plane.
     */
    Size size() const;

    /**
     * @return 'true' if and only if this object contains no point.
     */
    bool empty() const;

    /**
     * @return a const iterator pointing on the first point stored in the current standard plane.
     */
    ConstIterator begin() const;

    /**
     * @return a const iterator pointing after the last point stored in the current standard plane.
     */
    ConstIterator end() const;

    /**
     * NB: std version.
     * @return the maximal allowed number of points in the current standard plane.
     * @see maxSize
     */
    Size max_size() const;

    /**
     * same as max_size
     * @return the maximal allowed number of points in the current standard plane.
     */
    Size maxSize() const;


    //-------------------- model of concepts::CPointPredicate -----------------------------
  public:

    /**
     * Checks if the point \a p is in the current digital
     * plane. Therefore, a COBAGenericStandardPlaneComputer is a model of
     * concepts::CPointPredicate.
     *
     * @param p any 3D point.
     *
     * @return 'true' if it is in the current plane, false otherwise.
     */
    bool operator()( const Point & p ) const;

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

    //-------------------- model of CIncrementalPrimitiveComputer -----------------------------
  public:

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
       which is a ParallelStrip of diagonal width smaller than the one
       specified at instanciation.

       @note The returned primitive has the form \f$\mu \le \vec{N}
       \cdot \vec{X} \le \mu + \epsilon\f$. It is guaranteed that its diagonal
       width is strictly less than the value \a widthNumerator / \a
       widthDenominator x sqrt(3) specified with method \ref init.
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
    Point minimalPoint() const;

    /**
     * @pre ! empty()
     * @return the current maximal point of the plane, i.e. the one
     * with the highest scalar product with the current normal
     * vector. Note that other points may also have a maximum value.
     */
    Point maximalPoint() const;

    /**
       The basic method for computing all characteristics of the
       recognized plane. Used by \ref primitive, \ref minimalPoint,
       \ref maximalPoint, \ref getBounds.

       @param[out] n the integral normal vector (with last component positive).
       @param[out] imin the minimum dot product of an inserted point with \a n.
       @param[out] imax the maximum dot product of an inserted point with \a n.
       @param[out] p_min an inserted point satisfying the minimum dot product \a imin.
       @param[out] p_max an inserted point satisfying the maximum dot product \a imax.
    */
    void getCharacteristics( IntegerVector3 & n,
                             InternalInteger & imin, InternalInteger & imax,
                             Point & p_min, Point & p_max ) const;

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
    std::vector<Dimension> myOrthants; /**< The list of active plane orthants. Starts with {0:++,1:+-,2:-+,3:--}. */
    COBAComputer myComputers[ 4 ];     /**< The four COBA plane computers. */
    static Transform myTransforms[ 4 ];/**< The four space transformation associated with each COBA plane computer, shared by all computers. */
    mutable std::vector<Dimension> _orthantsToErase; /**< Useful when erasing orthants. */
    // ------------------------- Hidden services ------------------------------
  protected:
    /**
       @param orthant any orthant specified as an integer between 0 and 3.
       @return the space transformation "standard to naive" associated
       with orthant \a orthant.
    */
    static Transform t( Dimension orthant );
    /**
       @param orthant any orthant specified as an integer between 0 and 3.
       @return the space transformation "naive to standard" associated
       with orthant \a orthant.
    */
    static Transform invT( Dimension orthant );

    // ------------------------- Internals ------------------------------------
  private:
  }; // end of class COBAGenericStandardPlaneComputer


  /**
   * Overloads 'operator<<' for displaying objects of class 'COBAGenericStandardPlaneComputer'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'COBAGenericStandardPlaneComputer' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, typename TInternalInteger>
  std::ostream&
  operator<< ( std::ostream & out, const COBAGenericStandardPlaneComputer<TSpace, TInternalInteger> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/COBAGenericStandardPlaneComputer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined COBAGenericStandardPlaneComputer_h

#undef COBAGenericStandardPlaneComputer_RECURSES
#endif // else defined(COBAGenericStandardPlaneComputer_RECURSES)
