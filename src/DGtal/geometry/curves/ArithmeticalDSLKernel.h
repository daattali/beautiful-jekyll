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
 * @file ArithmeticalDSLKernel.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/07/02
 *
 * Header file for module ArithmeticalDSLKernel.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSLKernel_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSLKernel.h
#else // defined(ArithmeticalDSLKernel_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSLKernel_RECURSES

#if !defined ArithmeticalDSLKernel_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSLKernel_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/NumberTraits.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template struct ArithmeticalDSLKernel
  /**
   * \brief Aim: Small class that contains the code that depends
   * on the arithmetical thickness (either naive or standard)
   * of a digital straight line (DSL). It provides mainly two
   * static methods:
   * - ArithmeticalDSLKernel::shift that returns the shift vector of a DSL
   * from its slope parameters \f$ a \f$ and \f$ b \f$.
   * ie. the vector \f$ s \f$ translating a point of remainder \f$ r \f$ to a point
   * of remainder \f$ r + \omega \f$
   * - ArithmeticalDSLKernel::steps that returns the step vectors of a DSL
   * ie. the couple of vectors \f$ v \f$ and \f$ w \f$ used to iterate over
   * the points of a DSL in an orientation given by the DSL parameters
   * \f$ a \f$ and \f$ b \f$.
   * Obviously, these two vectors are equal to 0 if \f$ \omega = 0 \f$ (not valid DSL).
   * Moreover, the first vector (\f$ v \f$) is equal to the direction vector,
   * while the second one (\f$ w \f$) is equal to 0, if \f$ \omega = 1 \f$,
   * ie. if the lower leaning line and the upper leaning line are counfounded.
   * Though, in the general case, the first vector (\f$ v \f$) translates any point \f$ p \f$
   * of remainder \f$ r \f$ to its unique neighbor point \f$ q \f$ of remainder
   * \b greater than or equal to \f$ r \f$, while the second one (\f$ w \f$) is
   * such that \f$ v - w = s \f$.
   *
   * These methods are specialized with respect to the chosen adjacency
   * 8 (default) or 4.
   *
   * @ref moduleArithDSSReco
   *
   * @tparam TCoordinate a model of integer for the DGtal point coordinates
   * @tparam adjacency integer equal to 8 (default) for naive (simply 8-connected) DSL,
   * and 4 for standard (simply 4-connected) DSL.
   *
   * @see ArithmeticalDSL
   * @see exampleArithmeticalDSL.cpp
   */
  template <typename TCoordinate,
	    unsigned short adjacency = 8>
  struct ArithmeticalDSLKernel
  {

    // ----------------------- Inner types ------------------------------------
  public:
    /**
     * Type of the digital plane.
     */
    typedef SpaceND<2, TCoordinate> Space;
    /**
     * Type of the shift vector.
     */
    typedef typename Space::Vector Vector;
    /**
     * Type of the step vectors, defined as a STL pair of Vector
     */
    typedef std::pair<Vector, Vector> Steps;

    
    // ----------------------- static members ---------------------------------
  public:
    /**
     * Adjacency used for the DSL
     */
    BOOST_STATIC_CONSTANT(unsigned short, ForegroundAdjacency = 8); // adjacency
    
    /**
     * Adjacency used for the complement
     */
    BOOST_STATIC_CONSTANT(unsigned short, BackgroundAdjacency = 4); // complementary adjacency
    
    // ----------------------- static methods ---------------------------------
  public:
    /**
     * Given parameters @a a and @a b, this method computes the shift vector
     * translating a point of remainder \f$ r \f$ to a point of remainder \f$ r + \omega \f$
     *
     * NB: The shift vector is set to (0,0) if \f$ \omega = 0 \f$,
     * ie. @a a and @a b are both null.
     *
     * NB: If ( @a a , @a b ) lies between two octants (resp. quadrants)
     * (eg. @a b > 0 and @a a = 0), the shift vector of the next octant
     * (resp. quadrant) is chosen with respect to the counter-clockwise orientation.
     *
     * @param a a-parameter
     * @param b b-parameter
     * @tparam TInteger a model of integer for the parameters @a a and @a b
     * @return the shift vector
     *
     * @see exampleArithmeticalDSL.cpp
     */
    template <typename TInteger>
    static Vector shift(const TInteger& a, const TInteger& b);

    /**
     * Given parameters @a a and @a b, this method returns
     * the two step vectors, ie. the vectors that are used
     * to iterate over the points of a DSL of slope @a a / @a b.
     *
     * In the general case, the first vector \f$ v \f$ translates any point \f$ p \f$
     * of remainder \f$ r \f$ to its unique neighbor point \f$ q \f$ of remainder
     * greater than or equal to \f$ r \f$, while the second one \f$ w \f$ is
     * such that \f$ v - w = s \f$.
     *
     * NB: The two vectors are set to (0,0) if \f$ \omega = 0 \f$,
     * ie. @a a and @a b are both null.
     *
     * NB: The second vector is set to (0,0) if \f$ \omega = 1 \f$,
     * ie. if either @a a or @a b is null, if either @a a == @a b
     * or either @a a == - @a b in the naive case.
     *
     * @param a a-parameter
     * @param b b-parameter
     * @tparam TInteger a model of integer for the parameters @a a and @a b
     * @return the the pair of steps
     *
     * @see exampleArithmeticalDSL.cpp
     */
    template <typename TInteger>
    static Steps steps(const TInteger& a, const TInteger& b);

    /**
     * Returns the \f$ L_{\infty} \f$ (for the 8-adjacency)
     * or the \f$ L_1 \f$ norm (for the 4-adjacency)
     * of two integers  @a a and @a b,
     *
     * @param a a-parameter
     * @param b b-parameter
     * @tparam TInteger a model of integer for the parameters @a a and @a b
     * @return the norm
     */
    template<typename TInteger>
    static TInteger norm(const TInteger& a, const TInteger& b);

  };

  /////////////////////////////////////////////////////////////////////////////
  // specialization of the template struct ArithmeticalDSLKernel for 4-adjacency
  template <typename TCoordinate>
  struct ArithmeticalDSLKernel<TCoordinate, 4>
  {
    // ----------------------- Inner types ------------------------------------
  public:
    typedef SpaceND<2, TCoordinate> Space;
    typedef typename Space::Vector Vector;
    typedef std::pair<Vector, Vector> Steps;
    
    
    // ----------------------- static members ---------------------------------
  public:
        /**
     * Adjacency used for the DSL
     */
    BOOST_STATIC_CONSTANT(unsigned short, ForegroundAdjacency = 4); // adjacency
    
    /**
     * Adjacency used for the complement
     */
    BOOST_STATIC_CONSTANT(unsigned short, BackgroundAdjacency = 8); // complementary adjacency

    // ----------------------- static methods ---------------------------------
  public:
    template <typename TInteger>
    static Vector shift(const TInteger& a, const TInteger& b);
    template <typename TInteger>
    static Steps steps(const TInteger& a, const TInteger& b);
    template<typename TInteger>
    static TInteger norm(const TInteger& a, const TInteger& b);
    
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/ArithmeticalDSLKernel.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArithmeticalDSLKernel_h

#undef ArithmeticalDSLKernel_RECURSES
#endif // else defined(ArithmeticalDSLKernel_RECURSES)
