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
 * @file PointVector.h
 * @author David Coeurjolly (@c david.coeurjolly@liris.cnrs.fr )
 * @author Guillaume Damiand
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/05/14
 *
 *
 * This file is part of the DGtal library.
 */

#if defined(PointVector_RECURSES)
#error Recursive header files inclusion detected in PointVector.h
#else // defined(PointVector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PointVector_RECURSES

#if !defined PointVector_h
/** Prevents repeated inclusion of headers. */
#define PointVector_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include <bitset>
#include <algorithm>
#include <array>
#include <vector>

#include "DGtal/base/Common.h"
#include "DGtal/base/CBidirectionalRange.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/CEuclideanRing.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /// @return a bitset having true for each dimension presents in dimensions.
  template<Dimension dim, typename Container>
  std::bitset<dim> setDimensionsIn( const Container &dimensions );

  /// @return a bitset having true for each dimension not presents in dimensions.
  template<Dimension dim, typename Container>
  std::bitset<dim> setDimensionsNotIn( const Container &dimensions );

  /////////////////////////////////////////////////////////////////////////////
  // class PointVector
  /**
   * Description of class 'PointVector' <p>
   *
   * @brief Aim: Implements basic operations that will be used in 
   * Point and  Vector classes.
   *
   * A PointVector may represent either a symbolic point or a symbolic
   * vector depending on the context. The coordinates of the point or
   * the components of the vector should be part of a ring. For
   * performance reasons, these two types are just aliases. The user
   * should take care how to use it depending on the context. For
   * instance, adding two points has no meaning, but will be
   * authorized by the compiler.
   *
   * @tparam dim static constant of type DGtal::Dimension that
   * specifies the static  dimension of the space and thus the number
   * of elements  of the Point or Vector.
   * @tparam TEuclideanRing speficies the number type assoicated to an
   * Euclidean domain (or Euclidean ring) algebraic structure
   * (commutative unitary ring with no zero divisors and with a division
   * operator but not necessarily an inverse for the multiplication
   * operator). This type is used to represent PointVector elements
   * (Coordinate for Point and Component for Vector) and define
   * operations on Point or Vectors.
   * @tparam TContainer specifies the container to be used to store
   * the point coordinates. At this point, such container must be a
   * random access bidirectionnal a-la STL containers (e.g. vector,
   * boost/array). If TContainer implements comparison operators == !=
   * < <= > <=, then PointVector will also implements it and with the
   * exact same behaviour.
   *
   *
   * If TEuclideanRing is a Integer type (built-in integers,
   * BigIntegers, ...), the "/" operator on Points corresponds to
   * component by component Euclidean division. 
   *
   * If TEuclideanRing is a double, the "/" operator on Points
   * correspond to the classical division on real numbers (x*1/x = 1).
   * 
   *
   * The default less than operator is the one of the lexicographic
   * ordering, starting from dimension 0 to N-1.
   *
   * PointVector also realizes the concept CLattice with an infimum
   * (meet, greatest lower bound) and a supremum (join, least upper
   * bound) operation.
   *
   * Usage example:
   * @code
   *
   * ...
   * typedef PointVector<5, int> VectorD5;
   * VectorD5 p, q, r;
   *
   * p[1] = 2;  // p = {0, 2, 0, 0, 0}
   * q[3] = -5   // q = {0, 0, 0, -5, 0}
   * r =  p + q ;   //  r = {0, 2, 0, -5, 0}
   *
   * ...
   * @endcode
   *
   * PointVector is a model of CBidirectionalRange.
   * 
   * @see testPointVector.cpp
   *
   */
  template < DGtal::Dimension dim, 
	     typename TEuclideanRing,
	     typename TContainer=std::array<TEuclideanRing,dim> >
  class PointVector
  {
    // ----------------------- Standard services ------------------------------
  public:
    
    BOOST_CONCEPT_ASSERT(( concepts::CEuclideanRing<TEuclideanRing> ) );
    
    ///We cannot check the TContainer since boost::array is not a
    ///model of boost::RandomAccessContainer
  
    ///Self type
    typedef PointVector<dim, TEuclideanRing, TContainer> Self;

    ///Type for Vector elements
    typedef TEuclideanRing Component;
  
    ///Type for Point elements
    typedef Component Coordinate;

    ///Unsigned version of the components.
    typedef typename NumberTraits<Component>::UnsignedVersion UnsignedComponent;
    
    ///Copy of the dimension type
    typedef DGtal::Dimension Dimension;

    ///Copy of the static dimension of the Point/Vector.
    static const Dimension dimension = dim;

    ///Types needed by CLinearAlgebraContainer
    typedef Component Scalar;
    typedef Dimension Index;

    ///Copy of the container type
    typedef TContainer Container;


    /**
     *  Copy of the Container iterator types
     *
     **/
    typedef typename Container::iterator Iterator;
    typedef typename Container::const_iterator ConstIterator;
    typedef typename Container::reverse_iterator ReverseIterator;
    typedef typename Container::const_reverse_iterator ConstReverseIterator;

    /**
     * Constructor.
     */
    PointVector();

    /**
     * Constructor from array of values.
     *
     * @param ptrValues the array of values.
     */
    explicit PointVector( const Component* ptrValues );

    /**
     * Constructor from two values (the Dimension of the vector should
     * be at least 2). Other components are set to 0.
     *
     * @param x the first value.
     * @param y the second value.
     */
    PointVector( const Component & x, const Component & y );

    /**
     * Constructor from three values (the Dimension of the vector should
     * be at least 3). Other components are set to 0.
     *
     * @param x the first value.
     * @param y the second value.
     * @param z the third value.
     */
    PointVector( const Component & x, const Component & y, const Component & z );

    /**
     * Constructor from four values (the Dimension of the vector should
     * be at least 4). Other components are set to 0.
     *
     * @param x the first value.
     * @param y the second value.
     * @param z the third value.
     * @param t the fourth value.
     */
    PointVector( const Component & x, const Component & y, 
		 const Component & z, const Component & t );

    /**
     * Constructor from initializer list.
     * @param init the initializer list.
     */
    PointVector( std::initializer_list<Component> init );

    /** Constructor taking two points and a functor as parameters.
     *  The new point is initialized by the result of functor f
     *  applied for each pair of coordinates of apoint1 and apoint2
     */
    template<typename BinaryFunctor>
    PointVector( const Self& apoint1, const Self& apoint2,
		 const BinaryFunctor& f );

    /** Constructor taking a point and a unary functor as parameters.
     *  The new point is initialized by the result of functor f for
     *  each coordinate of apoint1
     */
    template<typename UnaryFunctor>
    PointVector( const Self& apoint1, 
		 const UnaryFunctor& f );

    /**
     * Destructor.
     */
    ~PointVector();

    // ----------------------- Iterator services ------------------------------
  public:
    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    PointVector( const Self & other );

    /**
     * Copy constructor from another component PointVector.
     * A static cast is used to cast the values during the copy.
     * @param other the object to clone.
     */
    template <typename OtherComponent, typename OtherCont>
    PointVector( const PointVector<dim,OtherComponent,OtherCont> & other );

    /**
     * Assignement Operator
     *
     * @param pv the object to copy.
     * @return a reference on 'this'.
     */
    Self & operator= ( const Self & pv );

    /**
     * Partial copy of a given PointVector. Only coordinates in dimensions
     * are copied.
     *
     * @param pv the object to copy.
     * @param dimensions the dimensions of v to copy
     *        (Size between 0 and N, all differents).
     * @return a reference on 'this'.
     */
    Self& partialCopy (const Self & pv,
		       std::initializer_list<Dimension> dimensions);

    /**
     * Inverse partial copy of a given PointVector. Only coordinates not 
     * in dimensions are copied.
     *
     * @param pv the object to copy.
     * @param dimensions the dimensions of v to copy
     *        (Size between 0 and N, all differents).
     * @return a reference on 'this'.
     */
    Self& partialCopyInv (const Self & pv,
			  std::initializer_list<Dimension> dimensions);

    /**
     * Partial copy of a given PointVector. Only coordinates in dimensions
     * are copied.
     *
     * @param pv the object to copy.
     * @param dimensions the dimensions of v to copy
     *        (Size between 0 and N, all differents).
     * @return a reference on 'this'.
     */
    Self& partialCopy (const Self & pv,
		       const std::vector<Dimension> &dimensions);

    /**
     * Partial copy of a given PointVector. Only coordinates not 
     * in dimensions are copied.
     *
     * @param pv the object to copy.
     * @param dimensions the dimensions of v to copy
     *        (Size between 0 and N, all differents).
     * @return a reference on 'this'.
     */
    Self& partialCopyInv (const Self & pv,
			  const std::vector<Dimension> &dimensions);

    /**
     * Partial equality.
     *
     * @param pv Point/Vector to compare to this.
     * @param dimensions  Dimensions along which to compare the points.
     *
     * @return true iff points are equal for given dimensions .
     */
    bool partialEqual ( const Self & pv,
			const std::vector<Dimension> &dimensions )  const;

    /**
     * Partial inverse equality.
     *
     * @param pv Point/Vector to compare to this.
     * @param dimensions  Dimensions along which to compare the points.
     *
     * @return true iff points are equal for dimensions not in dimensions.
     */
    bool partialEqualInv ( const Self & pv,
			   const std::vector<Dimension> &dimensions )  const;
    
    // ----------------------- Iterator services ------------------------------
  public:
    /**
     * PointVector begin() iterator.
     *
     * @return an Iterator on the first element of a Point/Vector.
     **/
    Iterator begin();

    /**
     * PointVector end() iterator.
     *
     * @return an Iterator on the last element of a Point/Vector.
     **/
    Iterator end();

    /**
     * PointVector begin() const iterator.
     *
     * @return an ConstIterator on the first element of a Point/Vector.
     **/
    ConstIterator begin() const;

    /**
     * PointVector end() const iterator.
     *
     * @return a ConstIterator on the last element of a Point/Vector.
     **/
    ConstIterator end() const;

    /**
     * PointVector rbegin() reverse iterator.
     *
     * @return a ReverseIterator on the first element of a Point/Vector.
     **/
    ReverseIterator rbegin();

    /**
     * PointVector rend() reverse iterator.
     *
     * @return a ReverseIterator on the last element of a Point/Vector.
     **/
    ReverseIterator rend();

    /**
     * PointVector rbegin() const reverse iterator.
     *
     * @return an ConstReverseIterator on the first element of a Point/Vector.
     **/
    ConstReverseIterator rbegin() const;
    
    /**
     * PointVector rend() const reverse iterator.
     *
     * @return a ConstReverseIterator on the last element of a Point/Vector.
     **/
    ConstReverseIterator rend() const;

    // ----------------------- Array services ------------------------------
  public:
    /**
     * Returns the size of the vector (i.e. the number of its
     * coefficients).
     */
    static Dimension size();
		inline Dimension rows() const { return dim; }

    /**
     * Returns the  @a i-th coefficient of the vector.
     *
     * @pre The @a i index must lie between @a 0 and @a size() .
     *
     * @param i is the index of the retrieved coefficient.
     */
    const Component& operator[]( Dimension i ) const;
    inline const Component& operator()( Dimension i ) const { return (*this)[i]; }

    /**
     * Returns a non-const reference to the @a i-th element of the
     * vector.
     *
     * @pre The @a i index must lie between @a 0 and @a size() .
     *
     * @param i is the index of the retrieved coefficient.
     */
    Component& operator[](Dimension i );
    Component& operator()(Dimension i ) { return (*this)[i]; }

    // ----------------------- Comparison operations --------------------------
  public:
    /**
     * Equality operator.
     *
     * @param pv Point/Vector to compare to this.
     *
     * @return true iff points are equal.
     *
     * @warning It inherits from operator== of TContainer.
     */
    bool operator== ( const Self & pv ) const;

    /**
     * Difference operator on Points/Vectors.
     *
     * @param pv the Point/Vector to compare to this.
     *
     * @return true iff this differs from pv, false otherwise.
     *
     * @warning It inherits from operator!= of TContainer.
     */
    bool operator!= ( const Self & pv ) const;

    /**
     * Comparison operator on Points/Vectors (LesserThan).
     *
     * @param pv the Point/Vector to compare to this.
     *
     * @return true iff this < pv, false otherwise.
     *
     * @warning It inherits from operator< of TContainer. Consequently, it uses the lexicographical order when using default container.
     */
    bool operator< ( const Self & pv ) const;

    /**
     * Comparison operator on Points/Vectors (LesserOrEqualThan).
     *
     * @param pv the Point/Vector to compare to this.
     *
     * @return true iff this <= pv, false otherwise.
     *
     * @warning It inherits from operator<= of TContainer. Consequently, it uses the lexicographical order when using default container.
     */
    bool operator<= ( const Self & pv ) const;

    /**
     * Comparison operator on Points/Vectors (GreaterThan).
     *
     * @param pv the Point/Vector to compare to this.
     *
     * @return true iff this > pv, false otherwise.
     *
     * @warning It inherits from operator> of TContainer. Consequently, it uses the lexicographical order when using default container.
     */
    bool operator> ( const Self & pv ) const;
    
    /**
     * Comparison operator on Points/Vectors (GreaterOrEqualThan).
     *
     * @param pv the Point/Vector to compare to this.
     *
     * @return true iff this >= pv, false otherwise.
     *
     * @warning It inherits from operator>= of TContainer. Consequently, it uses the lexicographical order when using default container.
     */
    bool operator>= ( const Self & pv ) const;

    // ----------------------- Operations ------------------------------
  public:
    /**
     * Multiplies @a *this by the @a coeff scalar number.
     *
     * @param coeff is the factor @a *this get multiplied by.
     * @return a reference on 'this'.
     */
    PointVector & operator*= ( Component coeff );

    /**
     * Multiplication operator with a scalar number
     *
     * @param coeff is the factor 'this' is multiplied by.
     * @return a new Point that is the multiplication of 'this' by coeff.
     */
    PointVector operator*( Component coeff ) const;
    
    /**
     * dot product with a PointVector
     *
     * @param v a vector that is dot-producted to *this.
     * @return the dot product of this and v.
     */
    Component dot( const Self &v) const;

    /**
     * cross product with a PointVector
     *
     * @param v a vector that is cross-producted to *this.
     * @return the cross product product 
     */
    Self crossProduct( const Self &v) const;

    /**
     * Positive angle between two vectors, deduced from their scalar product.
     * @param v any vector
     * @return the angle between *this and v in [0,pi].
     */
    double cosineSimilarity ( const Self & v ) const;

    /**
     * Addition operator with assignement.
     *
     * @param v is the Point that gets added to @a *this.
     * @return a reference on 'this'.
     */
    Self & operator+= ( const Self & v );

    /**
     * Addition operator.
     *
     * @param v is the Point that gets added to @a *this.
     * @return a new Point that is the addition of 'this' to [v].
     */
    Self operator+ ( const Self & v ) const;

    /**
     * Substraction operator with assignement.
     *
     * @param v is the Point that gets substracted to  *this.
     * @return a reference on 'this'.
     */
    Self & operator-= ( const Self & v );

    /**
     * Substraction operator.
     * Point - Vector => Point
     *
     * @param v is the Point that gets substracted to @a *this.
     * @return a new Point that is the subtraction 'this'-[v].
     */
    Self operator- ( const Self & v ) const;

    /**
     * Unary minus operator.
     * -Vector => Vector
     *
     * @return a new Vector that is the opposite of 'this', i.e. -'this'.
     */
    Self operator-() const;

    
    /**
     * Division operator with assignement.
     *
     * @param v is the Point that gets divided to @a *this.
     * @return a reference on 'this'.
     */
    Self & operator/= ( const Self & v );

    /**
     * Division operator.
     *
     * @param v is the Point that gets divided to @a *this.
     * @return the component division of *this by v.
     */
    Self  operator/ ( const Self & v ) const ;
  
    /**
     * Divides @a *this by the @a coeff scalar number.
     *
     * @param coeff is the factor @a *this get divided by.
     * @return the component division of *this by coeff.
     */
    Self operator/ ( const Component coeff ) const;
    
    /**
     * Divides @a *this by the @a coeff scalar number.
     *
     * @param coeff is the factor @a *this get divided by.
     * @return a reference on 'this'.
     */
    Self & operator/= ( const Component coeff );
   
    /**
     * Assignment operator from PointVector with different component
     * type.
     * A static cast is used to cast the values during the copy.
     *
     * @param v is the Point that gets divided to @a *this.
     * @return a reference on 'this'.
     */
    template<typename AnotherComponent>
    Self & operator= ( const PointVector<dim,AnotherComponent, Container> & v );
  
    
    /**
     * Resets all the values to zero.
     */
    void reset();

    /**
     * Resets all the values to zero. Needed by CLinearAlgebraContainer.
     */
		inline void clear() { reset(); }

    /**
     * Implements the infimum (or greatest lower bound). It means the
     * point whose coordinates are exactly the minimum of the two
     * points coordinate by coordinate.
     *
     * @param apoint any point.
     * @return a new point being the inf between *this and apoint.
     * @see isLower
     */
    Self inf( const Self& apoint ) const;

    /**
     * Implements the supremum (or least upper bound). It means the
     * point whose coordinates are exactly the maximum of the two
     * points coordinate by coordinate.
     *
     * @param apoint any point.
     * @return a new point being the sup between *this and apoint.
     * @see isUpper
     */
    Self sup( const Self& apoint ) const;

    /**
     * @param p any point.
     * @return true if this is below p (ie. this==inf(this,p))
     * NB: faster than computing the infimum and compare it afterwards.
     */
    bool isLower( const Self& p ) const;

    /**
     * @param p any point.
     * @return true if this is upper p (ie. this==sup(this,p))
     * NB: faster than computing the supremum and compare it afterwards.
     */
    bool isUpper( const Self& p ) const;

    /** 
     * Return the maximum component value of a point/vector.
     * 
     * @return the maximum value.
     */
    Component max() const;
   
    /** 
     * Return the minimum component value of a point/vector.
     * 
     * @return the minimum value.
     */ 
    Component min() const;

    /** 
     * Return the iterator on the component with maximim value of a
     * point/vector.
     * 
     * @return an iterator.
     */
    Iterator maxElement() ;
   
    /** 
     * Return the iterator on the component with minimum value of a
     * point/vector.
     * 
     * @return an iterator.
     */ 
    Iterator minElement() ;

    /**
       Negates this vector.
    */
    void negate();

    /**
     * Specify the set of norm types
     *
     */
    enum NormType { L_2, L_1, L_infty };

    /**
     * Computes the norm of a point/vector.
     * \warning This method performs a conversion
     * from the type T to double for each components to compute the
     * norms. For exact norms (restricted to L_1 and L_infinity
     * norms), please refer to PointVector::norm1 and PointVector::normInfinity. 
     *

     * @param type specifies the type of norm to consider (see @ref NormType).
     * @return the norm of the point/vector as a double.
     */
    double norm( const NormType type = L_2 ) const;

    /**
     * Computes the square L2 norm of a point/vector.
     * \warning This method performs a conversion
     * from the type T to double for each components to compute the
     * norms.
     *
     * @return the squared norm of the point/vector as a double.
     */
    double squaredNorm( ) const;

    
    /**
     * Computes the 1-norm of a vector.
     *
     * @return the absolute sum of the components of this vector.
     */
    UnsignedComponent norm1() const;

    /**
     * Computes the infinity-norm of a vector.
     *
     * @return the maximum absolute value of the components of this vector.
     */
    UnsignedComponent normInfinity() const;


    /** 
     * Compute the normalization of a given vector (*this) and return
     * a unitary vector on double.
     * 
     * @return a unitary vector with double as coordiante type. 
     * @advanced the point container is forced to boost::array<double,dim> 
     */
    PointVector<dim, double, std::array<double,dim> > getNormalized() const;
    

    // ------------------------- Standard vectors ------------------------------
  public:

    /**
     * @param val any value.
     * @return the diagonal vector (val,val, .. val).
     */
    static Self diagonal( Component val = 1 );

    /**
     * @param k any number between 0 and Dimension-1.
     * @param val any value.
     * @return the [k]-th base vector (0,0, ..., 0, val, 0, ..., 0).
     */
    static Self base( Dimension k, Component val = 1 );

    // --------------- CDrawableWithBoard2D realization -------------------
  public:
 
    /**
     * @return the style name used for drawing this object.
     */
    std::string className() const;

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /// Static const for zero PointVector.
    static Self zero;
    
    // ------------------------- Hidden services ------------------------------
  protected:
    
    ///Internal data-structure: std::array with constant size.
    Container myArray;

  }; // end of class PointVector

  /// Operator <<
  template<Dimension dim, typename Component, typename TC>
  std::ostream&
  operator<<( std::ostream & out, const PointVector<dim, Component, TC> & object );

  /**
     External multiplication operator with a scalar number

     @param coeff is the factor \a aVector is multiplied by.
     @param aVector is the vector that is multiplied by the factor \a coef.

     @return a new Vector that is the multiplication of \a aVector by
     \a coeff.
  */
  template<Dimension dim, typename Component, typename Container>
  PointVector<dim, Component,Container> 
  operator*( Component coeff,
	     const PointVector<dim, Component,Container> & aVector );


  ///Static const for zero definition
  template< Dimension dim, typename Component, typename TC>
  PointVector<dim, Component,TC>  PointVector<dim, Component,TC>::zero;

  
} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions
#include "DGtal/kernel/PointVector.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PointVector_h

#undef PointVector_RECURSES
#endif // else defined(PointVector_RECURSES)
