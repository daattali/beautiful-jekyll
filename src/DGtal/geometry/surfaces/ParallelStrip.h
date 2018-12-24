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
 * @file ParallelStrip.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/09/26
 *
 * Header file for module ParallelStrip.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ParallelStrip_RECURSES)
#error Recursive header files inclusion detected in ParallelStrip.h
#else // defined(ParallelStrip_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ParallelStrip_RECURSES

#if !defined ParallelStrip_h
/** Prevents repeated inclusion of headers. */
#define ParallelStrip_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ParallelStrip
  /**
     Description of template class 'ParallelStrip' <p> \brief Aim: A
     parallel strip in the space is the intersection of two parallel
     half-planes such that each half-plane includes the other.

     If N is the unit normal to one of the half-plane, the set of
     point \a X that is included in the strip satisfies some: \f$ \mu
     \le N \dot X \le \mu + \nu \f$, where inequalities can be large
     or strict.

     The \b normal to the strip is the vector \a N. The \b width of
     the strip is the scalar \f$\nu\f$. The \b axis \b width of the
     strip is the quantity \f$|\nu / N_i|\f$ where \f$|N_i|\f$ is the
     greatest component.

     \b Models: A ParallelStrip is a model of concepts::CPointPredicate.

     \note Parallel strips of axis width smaller than 1 are not naive
     digital planes since their parameters are floating-point
     values. However, they approach naive digital planes.

     \note Parallel strips of diagonal width smaller than
     \f$\sqrt{3}\f$ are not standard digital planes since their
     parameters are floating-point values. However, they approach
     standard digital planes.

     @tparam TSpace any digital space, i.e., a model of CSpace.

     @tparam muIncluded when 'true', the first inequality is large,
     i.e. \f$ \mu \le N \dot X \f$, otherwise it is strict, i.e. \f$
     \mu < N \dot X \f$

     @tparam muPlusNuIncluded when 'true', the second inequality is
     large, i.e. \f$ N \dot X \le \mu + \nu\f$, otherwise it is
     strict, i.e. \f$ N \dot X < \mu + \nu\f$
   */
  template <typename TSpace, bool muIncluded = true, bool muPlusNuIncluded = true>
  class ParallelStrip
  {
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));

    // ----------------------- public types ------------------------------
  public:
    typedef TSpace Space;
    typedef ParallelStrip<Space,muIncluded,muPlusNuIncluded> Self;
    typedef typename Space::Point Point;
    typedef typename Space::RealPoint RealPoint;
    typedef typename Space::Vector Vector;
    typedef typename Space::RealVector RealVector;
    typedef typename RealPoint::Coordinate Coordinate;
    typedef typename RealVector::Component Component;
    typedef Component Scalar;

    
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~ParallelStrip();

    /**
     * Constructor. The object is invalid.
     */
    ParallelStrip();

    /**
       Constructor from parameters.
       @param mu the minimal value of N.X
       @param N the normal to the plane
       @param nu the width of the strip.
     
       Note that the equation is normalized so that the normal is a
       unit vector.
     */
    ParallelStrip ( Scalar mu, const RealVector & N, Scalar nu );

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    ParallelStrip ( const ParallelStrip & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    ParallelStrip & operator= ( const ParallelStrip & other );

    //-------------------- strip / plane services -----------------------------
  public:

    /**
     * @return the unit normal vector to the strip.
     */
    const RealVector & normal() const;

    /**
       @return the parameter \f$\mu\f$ such that \f$ \mu \le N \cdot X\f$.
    */
    Scalar mu() const;

    /**
       Same as \ref width().
       @return the width of the strip, i.e. the parameter \f$\nu\f$
       such that \f$N \cdot X \le \mu + \nu\f$. 
    */
    Scalar nu() const;

    /**
       Same as \ref nu().
       @return the width of the strip, i.e. the parameter \f$\nu\f$
       such that \f$N \cdot X \le \mu + \nu\f$. 
    */
    Scalar width() const;

    /**
       @return the axis width of the strip, i.e. its width along its
       main axis.
    */
    Scalar axisWidth() const;

    /**
       @return the main axis of the strip (i.e. the absolute maximal
       component of the normal vector).
    */
    Dimension mainAxis() const;

    /**
       @return the diagonal width of the strip (its width along its
       main diagonal).
    */
    Scalar diagonalWidth() const;

    /**
       @return the integer that specifies the main diagonal among the
       2^dimension diagonals. The 1-bits of its bit representation
       specifies the axes that are negated.
    */
    Dimension mainDiagonal() const;

    /**
       If N is the unit normal to the current plane, then \f$ \mu \le
       N \cdot X\f$ and \f$N \cdot X \le \mu + \nu\f$ are the two
       half-planes defining it.
       
       @param mu the lower bound (corresponding to the unit vector).
       @param mu_plus_nu the upper bound (corresponding to the unit vector).
     */
    void getBounds( Scalar & mu, Scalar & mu_plus_nu ) const;

    //-------------------- model of concepts::CPointPredicate -----------------------------
  public:

    /**
     * Checks if the digital point \a p is in this strip. Therefore, a
     * ParallelStrip is a model of concepts::CPointPredicate.
     *
     * @param p any 3D digital point.
     *
     * @return 'true' if it is in the strip, false otherwise.
     */
    bool operator()( const Point & p ) const;

    /**
     * Checks if the (real-valued) point \a p is in this strip.
     *
     * @param p any 3D real-valued point.
     *
     * @return 'true' if it is in the strip, false otherwise.
     */
    bool operator()( const RealPoint & p ) const;

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
    /// The minimal scalar value \f$\mu\f$ of the strip.
    Scalar myMu;
    /// The unit normal vector \a N to the strip.
    RealVector myN;
    /// The width \f$\nu\f$ of the strip.
    Scalar myNu;

    // ------------------------- Private Datas --------------------------------
  private:

    // ------------------------- Hidden services ------------------------------
  protected:

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ParallelStrip


  /**
   * Overloads 'operator<<' for displaying objects of class 'ParallelStrip'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ParallelStrip' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace, bool muIncluded, bool muPlusNuIncluded>
  std::ostream&
  operator<< ( std::ostream & out, 
               const ParallelStrip<TSpace,muIncluded,muPlusNuIncluded> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/geometry/surfaces/ParallelStrip.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ParallelStrip_h

#undef ParallelStrip_RECURSES
#endif // else defined(ParallelStrip_RECURSES)
