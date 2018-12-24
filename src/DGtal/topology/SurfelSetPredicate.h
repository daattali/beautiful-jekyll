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
 * @file SurfelSetPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2012/02/10
 *
 * Header file for module SurfelSetPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SurfelSetPredicate_RECURSES)
#error Recursive header files inclusion detected in SurfelSetPredicate.h
#else // defined(SurfelSetPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SurfelSetPredicate_RECURSES

#if !defined SurfelSetPredicate_h
/** Prevents repeated inclusion of headers. */
#define SurfelSetPredicate_h

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
  // template class SurfelSetPredicate
  /**
   * Description of template class 'SurfelSetPredicate' <p> \brief Aim:
   * The predicate returning true iff the point is in the domain given
   * at construction.
   *
   * Model of CSurfelPredicate
   */
  template < typename TSurfelSet, 
             typename TSurfel = typename TSurfelSet::Surfel >
  struct SurfelSetPredicate
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TSurfelSet SurfelSet;
    typedef TSurfel Surfel;

    /**
     * Constructor.
     * @param aSet any set.
     */
    SurfelSetPredicate ( ConstAlias<SurfelSet> aSet );

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SurfelSetPredicate ( const SurfelSetPredicate & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SurfelSetPredicate & operator= ( const SurfelSetPredicate & other );

   /**
     * @param s any surfel.
     * @return true iff s is in the set of surfels.
     */
    bool operator()( const Surfel & s ) const;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    SurfelSetPredicate();

    // ------------------------- Internals ------------------------------------
  private:
    const SurfelSet* mySet;

  }; // end of struct SurfelSetPredicate


} // namespace functors
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/topology/SurfelSetPredicate.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SurfelSetPredicate_h

#undef SurfelSetPredicate_RECURSES
#endif // else defined(SurfelSetPredicate_RECURSES)
