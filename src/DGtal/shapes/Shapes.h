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
 * @file
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/10/28
 *
 * Header file for module Shapes.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Shapes_RECURSES)
#error Recursive header files inclusion detected in Shapes.h
#else // defined(Shapes_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Shapes_RECURSES

#if !defined Shapes_h
/** Prevents repeated inclusion of headers. */
#define Shapes_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/SurfelAdjacency.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/shapes/CDigitalOrientedShape.h"
#include "DGtal/shapes/CDigitalBoundedShape.h"
#include "DGtal/shapes/CEuclideanOrientedShape.h"
#include "DGtal/shapes/CEuclideanBoundedShape.h"
#include "DGtal/shapes/GaussDigitizer.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class Shapes
  /**
   * Description of template class 'Shapes' <p> \brief Aim: A utility
   * class for constructing different shapes (balls, diamonds, and
   * others).
   *
   * @tparam TDomain the type of the domain in which shapes are created.
   */
  template <typename TDomain>
  class Shapes
  {
    // Concept checks
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<TDomain> ) );

    // ----------------------- public types ------------------------------
  public:
    typedef TDomain Domain;
    typedef typename Domain::Space Space;
    typedef typename Domain::Space::RealPoint RealPoint;
    typedef typename Domain::Point Point;
    typedef typename Domain::Vector Vector;
    typedef typename Domain::Predicate Predicate;
    typedef typename Domain::ConstIterator ConstIterator;
    //Arithmetic
    typedef typename Space::Integer Integer;
    typedef typename Space::UnsignedInteger UnsignedInteger;

    // ----------------------- Static services ------------------------------
  public:

    /** 
     * Adds to the (perhaps non empty) set [aSet] an shape defined by
     * an instance of ShapeFunctor. Add Points where orientation is inside.
     * The shape functor must be a model of CDigitalOrientedShape and
     * CDigitalBoundedShape.
     * 
     * @param aSet the set (modified) which will contain the shape.
     * @param aFunctor a functor defining the shape.
     * @tparam TDigitalSet a model of CDigitalSet.
     * @tparam TShapeFunctor a model of CDigitalBoundedShape and
     * CDigitalOrientedShape.
     */
    template <typename TDigitalSet, typename TShapeFunctor>
    static void digitalShaper( TDigitalSet & aSet,
                               const TShapeFunctor & aFunctor);

    /** 
     * Adds to the (perhaps non empty) set [aSet] an shape defined by
     * an instance of ShapeFunctor. Add Points where orientation is inside.
     * The shape functor must be a model of CEuclideanOrientedShape
     * and CEuclideanBoundedShape. The underlying digitization process is
     * a Gauss Digitizer with grid step h.
     * 
     * @param aSet the set (modified) which will contain the shape.
     * @param aFunctor a functor defining the shape.
     * @param h grid step for the Gauss digitization.
     *
     * @tparam TDigitalSet a model of CDigitalSet.
     * @tparam TShapeFunctor a model of CEuclideanBoundedShape and
     * CEuclideanOrientedShape.
     */
    template <typename TDigitalSet, typename TShapeFunctor>
    static void euclideanShaper( TDigitalSet & aSet,
                                 const TShapeFunctor & aFunctor,
                                 const double h = 1.0);

    /**
       Add to the set \a aSet the points of the domain that satisfies
       the predicate \a aPP.

       @param aSet (modified) the digital set that will contain the points.
       @param aPP a predicate on point.
       
       @tparam DigitalSet a model of CDigitalSet such that
       DigitalSet::Domain is Domain.

       @tparam PointPredicate a model of concepts::CPointPredicate such that
       PointPredicate::Point is Point.
     */
    template < typename DigitalSet, typename PointPredicate >
    static
    void makeSetFromPointPredicate( DigitalSet & aSet,
                                    const PointPredicate & aPP );
    
    
    /**
     * Adds the discrete ball (norm-1) of center [aCenter] and radius
     * [aRadius] to the (perhaps non empty) set [aSet].
     *
     * @warning deprecated Use implicitShaper instead.
     * @tparam TDigitalSet the type chosen for the digital set.
     * @param aSet the set (modified) which will contain the discrete ball.
     * @param aCenter the center of the ball.
     * @param aRadius the radius of the ball.
     */
    template<typename TDigitalSet>
    static void addNorm1Ball( TDigitalSet & aSet,
                              const Point & aCenter, 
                              UnsignedInteger aRadius );
    
    /**
     * Adds the discrete ball (norm-2) of center [aCenter] and radius
     * [aRadius] to the (perhaps non empty) set [aSet].
     *
     * @warning deprecated Use implicitShaper instead.
     * @tparam TDigitalSet the type chosen for the digital set.
     * @param aSet the set (modified) which will contain the discrete ball.
     * @param aCenter the center of the ball.
     * @param aRadius the radius of the ball.
     */
    template <typename TDigitalSet>
    static void addNorm2Ball( TDigitalSet & aSet,
                              const Point & aCenter, 
                              UnsignedInteger aRadius );

    /**
     * Removes the discrete ball (norm-1) of center [aCenter] and radius
     * [aRadius] to the (perhaps non empty) set [aSet].
     *
     * @tparam TDigitalSet the type chosen for the digital set.
     * @param aSet the set (modified) which will contain the discrete ball.
     * @param aCenter the center of the ball.
     * @param aRadius the radius of the ball.
     */
    template <typename TDigitalSet>
    static void removeNorm1Ball( TDigitalSet & aSet,
                                 const Point & aCenter, 
                                 UnsignedInteger aRadius );
 
    /**
     * Removes the discrete ball (norm-2) of center [aCenter] and radius
     * [aRadius] to the (perhaps non empty) set [aSet].
     *
     * @tparam TDigitalSet the type chosen for the digital set.
     * @param aSet the set (modified) which will contain the discrete ball.
     * @param aCenter the center of the ball.
     * @param aRadius the radius of the ball.
     */
    template <typename TDigitalSet>
    static void removeNorm2Ball( TDigitalSet & aSet,
                                 const Point & aCenter, 
                                 UnsignedInteger aRadius );


    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~Shapes();

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
  private:
    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    Shapes();

  private:

    /**
     * Copy constructor.
     * @param other the object to clone.
     * Forbidden by default.
     */
    Shapes ( const Shapes & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    Shapes & operator= ( const Shapes & other );

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Shapes


  /**
   * Overloads 'operator<<' for displaying objects of class 'Shapes'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Shapes' to write.
   * @return the output stream after the writing.
   */
  template <typename TDomain>
  std::ostream&
  operator<< ( std::ostream & out, const Shapes<TDomain> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/shapes/Shapes.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Shapes_h

#undef Shapes_RECURSES
#endif // else defined(Shapes_RECURSES)
