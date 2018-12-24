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
 * @file DomainPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Header file for module DomainPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DomainPredicate_RECURSES)
#error Recursive header files inclusion detected in DomainPredicate.h
#else // defined(DomainPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DomainPredicate_RECURSES

#if !defined DomainPredicate_h
/** Prevents repeated inclusion of headers. */
#define DomainPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/BasicPointPredicates.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::functors
namespace DGtal {
  namespace functors {

  /////////////////////////////////////////////////////////////////////////////
  // template class DomainPredicate
  /**
   * Description of template class 'DomainPredicate' <p> \brief Aim:
   * The predicate returning true iff the point is in the domain given
   * at construction. It is just a wrapper class around the methods
   * Domain::isInside( const Point & ), where \c Domain stands for any
   * model of CDomain.
   *
   * It is used by domains to define the type by their method \c
   * predicate().
   *
   * Model of concepts::CPointPredicate
   *
   * @see DomainAdjacency::predicate.
   */
  template <typename TDomain>
  struct DomainPredicate
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TDomain Domain;
    typedef typename Domain::Point Point;

    /**
     * Constructor from domain.
     * @param aDomain any domain.
     */
    DomainPredicate ( ConstAlias<Domain> aDomain );

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    DomainPredicate ( const DomainPredicate & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    DomainPredicate & operator= ( const DomainPredicate & other );

   /**
     * @param p any point.
     * @return true iff p is in the domain.
     */
    bool operator()( const Point & p ) const;

    /**
     * @return a const reference to the associated domain.
     */
    const Domain & domain() const;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    DomainPredicate();


    // ------------------------- Internals ------------------------------------
  private:

    /// Aliasing pointer on the domain corresponding to this predicate.
    const Domain* myDomain;

  }; // end of struct DomainPredicate

} // namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/domains/DomainPredicate.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DomainPredicate_h

#undef DomainPredicate_RECURSES
#endif // else defined(DomainPredicate_RECURSES)
