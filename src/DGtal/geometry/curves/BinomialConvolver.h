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
 * @file BinomialConvolver.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2011/07/06
 *
 * Header file for module BinomialConvolver.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(BinomialConvolver_RECURSES)
#error Recursive header files inclusion detected in BinomialConvolver.h
#else // defined(BinomialConvolver_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BinomialConvolver_RECURSES

#if !defined BinomialConvolver_h
/** Prevents repeated inclusion of headers. */
#define BinomialConvolver_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <map>
#include "DGtal/base/Common.h"
#include "DGtal/math/Signal.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class BinomialConvolver
  /**
     Description of template class 'BinomialConvolver'. <p>

     @brief Aim: This class represents a 2D contour convolved by some
     binomial. It computes first and second order derivatives so as to
     be able to estimate tangent and curvature. In particular, it
     smoothes digital contours but could be used for other kind of
     contours.

     @tparam TConstIteratorOnPoints the type that represents an
     iterator in a sequence of points. Each component of Point must be
     convertible into a double.

     @tparam TValue the type for storing the convolved versions of the
     contour (double as default).

     @see testBinomialConvolver.cpp
  */
  template <typename TConstIteratorOnPoints, typename TValue = double>
  class BinomialConvolver
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TValue Value;
    typedef TConstIteratorOnPoints ConstIteratorOnPoints;
    typedef typename ConstIteratorOnPoints::value_type Point;

   /**
      Constructor. The object is not valid.

      @param n the parameter for the size of the binomial kernel
      (which is then 2^n).

      @see init
     */
    BinomialConvolver( unsigned int n = 1 );


    /**
     * Destructor.
     */
    ~BinomialConvolver();

    /**
       @param n the parameter for the size of the binomial kernel
       (which is then 2^n).
    */
    void setSize( unsigned int n );

    /**
       @return the parameter for the size of the binomial kernel
       (which is then 2^n).
    */
    unsigned int size() const;

    /**
       @return the suggested size for the binomial convolver as
       ceil( d / pow( h, 1.0/3.0 ) ), with d the diameter of the
       contour.
    */
    static
    unsigned int suggestedSize( const double h,
        const ConstIteratorOnPoints& itb,
        const ConstIteratorOnPoints& ite );

    /**
       Initializes the convolver with some sequence of points.
       @param h grid size (must be >0).
       @param itb begin iterator
       @param ite end iterator
       @param isClosed true if the input range is viewed as closed.

       The object is then valid.
    */
    void init( const double h,
         const ConstIteratorOnPoints& itb,
         const ConstIteratorOnPoints& ite,
         const bool isClosed );

    /**
       Given a valid iterator [it], return the corresponding index
       position in the binomial convolver in logarithmic time. The
       method init should have been called before.

       @see init

       @param it any valid iterator
       @return its index for accessing geometric data.
    */
    int index( const ConstIteratorOnPoints& it ) const;

    /**
     * @param i any index.
     *
     * @return the position vector (x[ i ],y[ i ]) (0 is the first point).
     */
    std::pair<Value,Value> x( int i ) const;

    /**
     * @param i any index.
     *
     * @return the derivative of the position (x'[ i ],y'[ i ]) (0 is
     * the first point).
     */
    std::pair<Value,Value> dx( int i ) const;

    /**
     * @param i any index.
     *
     * @return the second derivative of the position (x''[ i ],y''[ i
     * ]) (0 is the first point).
     */
    std::pair<Value,Value> d2x( int i ) const;

    /**
     * @param i any index.
     *
     * @return the normalized tangent vector (x'[ i ],y'[ i ]) (0 is
     * the first point).
     */
    std::pair<Value,Value> tangent( int i ) const;

    /**
     * @param i any index.
     *
     * @return the curvature of the signal (0 is the first point).

     * NB: depends on the gridstep.
     */
    Value curvature( int i ) const;


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

    // ------------------------- Protected Datas ------------------------------
  protected:
    unsigned int myN;
    double myH;
    Signal<Value> myX;
    Signal<Value> myY;
    Signal<Value> myDX;
    Signal<Value> myDY;
    Signal<Value> myDDX;
    Signal<Value> myDDY;

    ///Copy of the begin iterator
    ConstIteratorOnPoints myBegin;

    ///Copy of the end iterator
    ConstIteratorOnPoints myEnd;

    // Stores the mapping Iterator => Index.
    std::map<ConstIteratorOnPoints,int> myMapIt2Idx;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    BinomialConvolver ( const BinomialConvolver & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    BinomialConvolver & operator= ( const BinomialConvolver & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class BinomialConvolver

  /**
     Description of template class
     'TangentFromBinomialConvolverFunctor' <p> \brief Aim: This class
     is a functor for getting the tangent vector of a binomial convolver.

     @tparam TBinomialConvolver any BinomialConvolver.

     @tparam TRealPoint the type for representing the tangent vector.
  */
  template <typename TBinomialConvolver, typename TRealPoint>
  struct TangentFromBinomialConvolverFunctor
  {
  public:
    // ----------------------- inner type ------------------------------
    typedef TRealPoint Value;
    typedef TRealPoint RealPoint;
    typedef TBinomialConvolver BinomialConvolver;
    typedef typename TBinomialConvolver::Value SignalValue;
    typedef typename TBinomialConvolver::ConstIteratorOnPoints ConstIteratorOnPoints;

    /**
       Operator()

       @param bc a binomial convolver.
       @param it any valid iterator in the current BinomialConvolver.
       @return the tangent vector at position [it].
     */
    Value operator()( const BinomialConvolver & bc,
          const ConstIteratorOnPoints & it ) const;

  };

  /**
     Description of template class
     'CurvatureFromBinomialConvolverFunctor' <p> \brief Aim: This class
     is a functor for getting the curvature of a binomial convolver.

     @tparam TBinomialConvolver any BinomialConvolver.

     @tparam TReal the type for representing the curvature scalar.
  */
  template <typename TBinomialConvolver, typename TReal>
  struct CurvatureFromBinomialConvolverFunctor
  {
  public:
    // ----------------------- inner type ------------------------------
    typedef TReal Value;
    typedef TReal Real;
    typedef TBinomialConvolver BinomialConvolver;
    typedef typename TBinomialConvolver::Value SignalValue;
    typedef typename TBinomialConvolver::ConstIteratorOnPoints ConstIteratorOnPoints;

    /**
       Operator()

       @param bc a binomial convolver.
       @param it any valid iterator in the current BinomialConvolver.
       @return the tangent vector at position [it].
     */
    Value operator()( const BinomialConvolver & bc,
          const ConstIteratorOnPoints & it ) const;

  };

  /**
     Description of template class 'BinomialConvolverEstimator' <p>
     \brief Aim: This class encapsulates a BinomialConvolver and a
     functor on BinomialConvolver so as to be a model of
     CCurveLocalGeometricEstimator.

     @tparam TBinomialConvolver any BinomialConvolver.

     @tparam TBinomialConvolverFunctor .
  */
  template <typename TBinomialConvolver, typename TBinomialConvolverFunctor>
  class BinomialConvolverEstimator
  {
  public:
    typedef TBinomialConvolver BinomialConvolver;
    typedef TBinomialConvolverFunctor BinomialConvolverFunctor;
    typedef typename BinomialConvolver::ConstIteratorOnPoints ConstIteratorOnPoints;
    typedef ConstIteratorOnPoints ConstIterator;
    typedef typename BinomialConvolverFunctor::Value Value;
    typedef Value Quantity;

    BinomialConvolverEstimator( unsigned int n = 0,
        const BinomialConvolverFunctor & f
        = BinomialConvolverFunctor() );

    /**
     * Initialisation.
     * @param h grid size (must be >0).
     * @param itb begin iterator
     * @param ite end iterator
     * @param isClosed true if the input range is viewed as closed.
     */
    void init( const double h,
         const ConstIterator & itb,
         const ConstIterator & ite,
         const bool isClosed = true );

    /**
     * @return the estimated quantity at *it
     */
    Quantity eval( const ConstIterator& it );

    /**
     * @return the estimated quantity
     * from itb till ite (exculded)
     */
    template <typename OutputIterator>
    OutputIterator eval( const ConstIterator& itb,
       const ConstIterator& ite,
       OutputIterator result );



  private:
    BinomialConvolver myBC;
    BinomialConvolverFunctor myFunctor;

  };

  /**
   * Overloads 'operator<<' for displaying objects of class 'BinomialConvolver'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'BinomialConvolver' to write.
   * @return the output stream after the writing.
   */
  template <typename TConstIteratorOnPoints, typename TValue >
  std::ostream&
  operator<< ( std::ostream & out,
         const BinomialConvolver<TConstIteratorOnPoints,TValue> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/BinomialConvolver.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BinomialConvolver_h

#undef BinomialConvolver_RECURSES
#endif // else defined(BinomialConvolver_RECURSES)
