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
 * @file ArithmeticalDSSFactory.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/28
 *
 * Header file for module ArithmeticalDSSFactory.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ArithmeticalDSSFactory_RECURSES)
#error Recursive header files inclusion detected in ArithmeticalDSSFactory.h
#else // defined(ArithmeticalDSSFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArithmeticalDSSFactory_RECURSES

#if !defined ArithmeticalDSSFactory_h
/** Prevents repeated inclusion of headers. */
#define ArithmeticalDSSFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/geometry/curves/ArithmeticalDSL.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  //forward declaration of ArithmeticalDSS
  template <typename TCoordinate,
	    typename TInteger,
	    unsigned short adjacency>
  class ArithmeticalDSS;

  /////////////////////////////////////////////////////////////////////////////
  // template class ArithmeticalDSSFactory
  /**
   * Description of template class 'ArithmeticalDSSFactory' <p>
   * \brief Aim: Set of static methods that create digital straight segments (DSS)
   * from some input parameters, eg. patterns (or reversed patterns) from two
   * upper leaning points (or lower leaning points).
   *
   * @tparam TCoordinate a model of integer for the DGtal point coordinate
   * @tparam TInteger a model of integer for the DSS parameters (a, b, mu, omega)
   * @tparam adjacency a integer equal to 8 (default) for naive and 8-connected DSS,
   * and 4 for standard and 4-connected DSS.
   */
  template <typename TCoordinate,
	    typename TInteger = TCoordinate,
	    unsigned short adjacency = 8>
  class ArithmeticalDSSFactory
  {

    // ----------------------- Inner types -----------------------------------
  public:

    typedef TCoordinate Coordinate;
    typedef Coordinate Position;
    typedef TInteger Integer;
    typedef DGtal::PointVector<2, Coordinate> Point;
    typedef Point Vector;
    typedef std::pair<Vector,Vector> Steps;

    typedef ArithmeticalDSS<TCoordinate,TInteger,adjacency> DSS;
    typedef ArithmeticalDSL<TCoordinate,TInteger,adjacency> DSL;

    // ----------------------- Creation methods ------------------------------

  public:

    /**
     * Construction of the subsegment of minimal parameters of a given DSL. 
     *
     * @param aDSL bounding DSL
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses smartCH algorithm [Roussillon 2014 : \cite RoussillonDGCI2014]. 
     */
    static DSS createSubsegment(const DSL& aDSL, const Point& aF, const Point& aL);

    /**
     * Construction of the subsegment of minimal parameters of a greater DSS. 
     *
     * @param aDSS bounding DSS
     * @param aF first point of the subsegment
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses reversedSmartCH algorithm [Roussillon 2014 : \cite RoussillonDGCI2014].
     *
     * @see createLeftSubsegment
     */
    static DSS createSubsegment(const DSS& aDSS, const Point& aF, const Point& aL);

    /**
     * @brief Method that creates a DSS that is a pattern
     * or a repetition of a pattern from two input digital points,
     * viewed as upper leaning points.
     * @param aF first input digital point
     * @param aL second input digital point
     *
     * NB: logarithmic-time in the greatest component of the vector
     * starting from @a aF and pointing to @a aL
     */
    static DSS createPattern(const Point& aF, const Point& aL);

  /**
     * @brief Method that creates a DSS that is a reversed pattern
     * or a repetition of a reversed pattern from two input digital points,
     * viewed as lower leaning points. Creates the pattern from
     * @a aL to @a aF and negates the result.
     *
     * @see createPattern
     *
     * @param aF first input digital point
     * @param aL second input digital point
     *
     * NB: logarithmic-time in the greatest component of the vector
     * starting from @a aF and pointing to @a aL
     */
  static DSS createReversedPattern(const Point& aF, const Point& aL);
  
  /**
   * @brief Method that creates a DSS from a direction vector, a first and last point and one upper leaning point 
   *
   * @param aA y-component of the direction vector
   * @param aB x-component of the direction vector
   * @param aF first input digital point
   * @param aL second input digital point
   * @param aU upper leaning point
   * @return a DSS
   *
   * NB: logarithmic-time in the max of the greatest component of the vector
   * starting from @a aU and pointing to @a aL and the greatest
   * component of the vector starting from @a aF and pointing to @a
   * aU. 
   */
  
  static DSS createDSS(const Coordinate& aA, const Coordinate& aB, const Point& aF, const Point& aL, const Point& aU);
  


    // ----------------------- Internals -------------------------------------
  private:

    /**
     * Construction of the left subsegment of minimal parameters of a greater DSS. 
     * It is bound by the first point of @a aDSS on the left and by @a aL on the right. 
     *
     * @param aDSS bounding DSS
     * @param aL last point of the subsegment
     *
     * NB: logarithmic-time in the greatest component of the direction vector
     * of the subsegment. Uses reversedSmartCH algorithm [Roussillon 2014 : \cite RoussillonDGCI2014]. 
     */
    static DSS createLeftSubsegment(const DSS& aDSS, const Point& aL);

    /**
     * Returns the bezout vector (u,v) of a given
     * direction vector of slope @a aA / @a aB
     * such that u and @a aB (resp. v and @a aA)
     * have the same sign.
     * @return bezout vector
     * @param aA y-component of the direction vector
     * @param aB x-component of the dirention vector
     * @param aR a remainder equal to either 1 or -1
     *
     * @see createPattern
     *
     * NB: this method uses the extended Euclid's algorithm
     * and runs in logarithmic time.
     */
    static Vector bezoutVector(const Coordinate& aA,
			       const Coordinate& aB,
			       const Coordinate& aR);


  }; // end of class ArithmeticalDSSFactory



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/curves/ArithmeticalDSSFactory.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArithmeticalDSSFactory_h

#undef ArithmeticalDSSFactory_RECURSES
#endif // else defined(ArithmeticalDSSFactory_RECURSES)
