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
 * @file CAdditivePrimitiveComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/09/31
 *
 * Header file for concept CAdditivePrimitiveComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CAdditivePrimitiveComputer_RECURSES)
#error Recursive header files inclusion detected in CAdditivePrimitiveComputer.h
#else // defined(CAdditivePrimitiveComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CAdditivePrimitiveComputer_RECURSES

#if !defined CAdditivePrimitiveComputer_h
/** Prevents repeated inclusion of headers. */
#define CAdditivePrimitiveComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/BasicArchetypes.h"
#include "DGtal/geometry/surfaces/CIncrementalPrimitiveComputer.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CAdditivePrimitiveComputer
  /**
  Description of \b concept '\b CAdditivePrimitiveComputer' <p>
  @ingroup Concepts 
  @brief Aim: Defines the concept describing an object that
  computes some primitive from input points given group by group,
  while keeping some internal state. At any moment, the object is
  supposed to store at least one valid primitive for the formerly
  given input points. A primitive is an informal word that
  describes some family of objects that share common
  characteristics. Often, the primitives are geometric,
  e.g. digital planes.
  
  ### Refinement of CIncrementalPrimitiveComputer
  
  ### Associated types :
  - \a Primitive, the type that defines the primitive.
  - \a Point: the type of the input points.
  
  ### Notation
  - \a X : A type that is a model of CAdditivePrimitiveComputer
  - \a x : object of type \a X
  
  ### Valid expressions and semantics
  
  
  | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
  |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
  |insert new points| x.extend(\a it, \a itE)| \a ForwardIterator \a it, \a itE: the type of iterator on points, a model of boost::ForwardIterator on Point | \a bool | | tries to find a primitive that matches the new points in range [\a it, \a itE) and all formerly given input points, return \a true on success (state may change), \a false otherwise (state is unchanged)| | |
  |check new points| x.isExtendable(\a it, \a itE)| \a ForwardIterator \a it, \a itE: the type of iterator on points, a model of boost::ForwardIterator | \a bool | | tries to find a primitive that matches the new points in range [\a it, \a itE) and all formerly given input points, return \a true only if it possible, the state is always unchanged| | |
  
  
  ### Invariants###
  
  ### Models###
  
  - COBANaivePlaneComputer, COBAGenericNaivePlaneComputer, ChordNaivePlaneComputer, ChordGenericNaivePlaneComputer, COBAGenericStandardPlaneComputer
  
  ### Notes###
  
  @tparam T the type that should be a model of CAdditivePrimitiveComputer.
  */
  template <typename T>
  struct CAdditivePrimitiveComputer : CIncrementalPrimitiveComputer<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // Inner types
    typedef typename T::Point Point; // already required in CIncrementalPrimitiveComputer
    // Methods
    BOOST_CONCEPT_USAGE( CAdditivePrimitiveComputer )
    {
      ConceptUtils::sameType( myBool, myX.extend( myIt, myIt ) );
      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
      ConceptUtils::sameType( myBool, myX.isExtendable( myIt, myIt ) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // only if T is default constructible.
    bool myBool;
    CForwardIteratorArchetype<Point> myIt;

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CAdditivePrimitiveComputer

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CAdditivePrimitiveComputer_h

#undef CAdditivePrimitiveComputer_RECURSES
#endif // else defined(CAdditivePrimitiveComputer_RECURSES)
