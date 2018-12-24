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
 * @file CPointPredicate.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/10
 *
 * Header file for concept CPointPredicate.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPointPredicate_RECURSES)
#error Recursive header files inclusion detected in CPointPredicate.h
#else // defined(CPointPredicate_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPointPredicate_RECURSES

#if !defined CPointPredicate_h
/** Prevents repeated inclusion of headers. */
#define CPointPredicate_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/base/CPredicate.h"

//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CPointPredicate
  /**
  Description of \b concept '\b CPointPredicate' <p>
  @ingroup Concepts
  \brief Aim: Defines a predicate on a point.
  
  Associates booleans to points.
  
  ### Refinement of
  CPredicate
  
  
  ### Associated types :
  - Point : specifies the type for an element of the domain (inner
  type).
  
  ### Models
  - basic models: ConstantPointPredicate, TruePointPredicate, FalsePointPredicate, IsUpperPointPredicate, IsLowerPointPredicate, IsWithinPointPredicate
  - complex predicate constructor: BinaryPointPredicate
  - others: DomainPredicate, SetPredicate, IntervalForegroundPredicate, SimpleThresholdForegroundPredicate
  - all models of CDigitalSet are models of CPointPredicate: DigitalSetBySTLVector, DigitalSetBySTLMap, DigitalSetFromMap
  
  ### Notes
  */
  template <typename T>
  struct CPointPredicate: CPredicate<T, typename T::Point>
  {
  // ----------------------- Concept checks ------------------------------
  public:
    typedef typename T::Point Point;

    BOOST_CONCEPT_ASSERT(( CUnaryFunctor<T,Point,bool> ));

    // ------------------------- Private Datas --------------------------------
  private:
    // ------------------------- Internals ------------------------------------
  private:


  }; // end of concept CPointPredicate
} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPointPredicate_h

#undef CPointPredicate_RECURSES
#endif // else defined(CPointPredicate_RECURSES)
