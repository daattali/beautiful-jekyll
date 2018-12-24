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
 * @file ClosedIntegerHalfPlane.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/27
 *
 * Header file for module ClosedIntegerHalfPlane.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ClosedIntegerHalfPlane_RECURSES)
#error Recursive header files inclusion detected in ClosedIntegerHalfPlane.h
#else // defined(ClosedIntegerHalfPlane_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ClosedIntegerHalfPlane_RECURSES

#if !defined ClosedIntegerHalfPlane_h
/** Prevents repeated inclusion of headers. */
#define ClosedIntegerHalfPlane_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class ClosedIntegerHalfPlane
  /**
     Description of template class 'ClosedIntegerHalfPlane' <p>
     \brief Aim:
     A half-space specified by a vector N and a constant c. The
     half-space is the set \f$ \{ P \in Z^2, N.P \le c \} \f$.

     A model of boost::DefaultConstructible, boost::CopyConstructible,
     boost::Assignable, concepts::CPointPredicate.
  */
  template <typename TSpace>
  struct ClosedIntegerHalfPlane
  {
    typedef ClosedIntegerHalfPlane<TSpace> Self;
    BOOST_CONCEPT_ASSERT(( concepts::CSpace< TSpace > ));
    
    typedef TSpace Space;
    typedef typename Space::Integer Integer;
    typedef typename Space::Point Point;
    typedef typename Space::Vector Vector;
    
    // ----------------------- public data ------------------------------
  public:

    Vector N;  ///< The normal to the half-space.
    Integer c; ///< The uppermost value N.(x,y) that is in the half-space.

  protected:
    // ----------------------- Standard services ------------------------------
  public:
    /**
     * Destructor.
     */
    ~ClosedIntegerHalfPlane();

    /**
       Constructor from normal and constant.

       @param aN a vector that defines the normal direction to the half-plane.
       @param aC the constant that defines the bound.
    */
    ClosedIntegerHalfPlane( const Vector & aN, const Integer & aC );
    
    /**
       Constructor. Computes the half-space of the form N.P<=c whose
       supporting line passes through A and B such that the point \a
       inP satisfies the constraint.
       
       @param A any point.
       @param B any point different from A.
       @param inP any point not on the straight line (AB).
       @param ic any compatible integer computer.
     */
    ClosedIntegerHalfPlane( const Point & A, const Point & B, 
                            const Point & inP, IntegerComputer<Integer> & ic );

    /**
       @param p any point in the plane.
       @return 'true' if p is inside the half-space (i.e. N.p <= c ).
    */
    bool operator()( const Point & p ) const;

    /**
       @param p any point in the plane.
       @return 'true' if p is on the boundary of the half-space (i.e. N.p == c ).
    */
    bool isOnBoundary( const Point & p ) const;

    /**
       @return the tangent vector to the half-plane boundary (ie. ( -N.y, N.x ) ).
    */
    Vector tangent() const;

    /**
       Negates the half-space. Only the boundary is common.
    */
    void negate();

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


  }; // end of class ClosedIntegerHalfPlane


  /**
   * Overloads 'operator<<' for displaying objects of class 'ClosedIntegerHalfPlane'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ClosedIntegerHalfPlane' to write.
   * @return the output stream after the writing.
   */
  template <typename TSpace>
  std::ostream&
  operator<< ( std::ostream & out, const ClosedIntegerHalfPlane<TSpace> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/arithmetic/ClosedIntegerHalfPlane.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ClosedIntegerHalfPlane_h

#undef ClosedIntegerHalfPlane_RECURSES
#endif // else defined(ClosedIntegerHalfPlane_RECURSES)
