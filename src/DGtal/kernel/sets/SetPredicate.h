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
 * @file SetPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Header file for module SetPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(SetPredicate_RECURSES)
#error Recursive header files inclusion detected in SetPredicate.h
#else // defined(SetPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SetPredicate_RECURSES

#if !defined SetPredicate_h
/** Prevents repeated inclusion of headers. */
#define SetPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/kernel/BasicPointPredicates.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  // 2013/02/02: JOL: Since 0.6, models of CDigitalSet are also models
  // of concepts::CPointPredicate. Therefore, this facade to models of
  // CDigitalSet is no longer useful.
  namespace deprecated {

  /////////////////////////////////////////////////////////////////////////////
  // template class SetPredicate
  /**
     Description of template class 'SetPredicate' <p> \brief Aim: The
     predicate returning true iff the point is in the set given at
     construction. The set given at construction is aliased in the
     predicate and not cloned, which means that the lifetime of the
     set should exceed the lifetime of the predicate.

     Model of concepts::CPointPredicate.
     
     @deprecated Since 0.6, digital sets are also models of concepts::CPointPredicate,
     hence using a SetPredicate is therefore no more
     useful. 

   */
  template <typename TDigitalSet>
  struct SetPredicate
  {
    // ----------------------- Standard services ------------------------------
  public:
    typedef TDigitalSet DigitalSet;
    typedef typename DigitalSet::Domain Domain;
    typedef typename Domain::Point Point;

    /**
     * Constructor.
     * @param aSet any set (only aliased).
     */
    SetPredicate ( ConstAlias<DigitalSet> aSet );

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    SetPredicate ( const SetPredicate & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    SetPredicate & operator= ( const SetPredicate & other );

   /**
     * @param p any point.
     * @return true iff p is in the domain.
     */
    bool operator()( const Point & p ) const;

    // ------------------------- Hidden services ------------------------------
  protected:

    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    SetPredicate();

    // ------------------------- Internals ------------------------------------
  private:
    /**
     * Aliasing pointer on the underlying set
     */
    const DigitalSet* mySet;

  }; // end of struct SetPredicate

  } // namespace deprecated

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/sets/SetPredicate.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SetPredicate_h

#undef SetPredicate_RECURSES
#endif // else defined(SetPredicate_RECURSES)
