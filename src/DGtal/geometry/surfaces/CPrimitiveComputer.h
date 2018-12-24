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
 * @file CPrimitiveComputer.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/09/31
 *
 * Header file for concept CPrimitiveComputer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPrimitiveComputer_RECURSES)
#error Recursive header files inclusion detected in CPrimitiveComputer.h
#else // defined(CPrimitiveComputer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPrimitiveComputer_RECURSES

#if !defined CPrimitiveComputer_h
/** Prevents repeated inclusion of headers. */
#define CPrimitiveComputer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

  /////////////////////////////////////////////////////////////////////////////
  // class CPrimitiveComputer
  /**
  Description of \b concept '\b CPrimitiveComputer' <p>
  @ingroup Concepts
  @brief Aim: Defines the concept describing an object that
  computes some primitive from input points, while keeping some
  internal state. At any moment, the object is supposed to store at
  least one valid primitive for the formerly given input points. A
  primitive is an informal word that describes some family of
  objects that share common characteristics. Often, the primitives
  are geometric, e.g. digital planes.
  
  ### Refinement of boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>
  
  ### Associated types :
  - \a Space, the type that defines the digital space.
  - \a Primitive, the type that defines the primitive.
  
  ### Notation
  - \a X : A type that is a model of CPrimitiveComputer
  - \a x : object of type X

  ### Valid expressions and semantics


  | Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
  |---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
  |access to primitive | x.primitive() |             | \a Primitive|                  |returns a primitive that represents the current solution| | O(1)|
  
  
  ### Invariants###
  
  ### Models###
  
  - COBANaivePlaneComputer, COBAGenericNaivePlaneComputer, ChordNaivePlaneComputer, ChordGenericNaivePlaneComputer, COBAGenericStandardPlaneComputer
  
  ### Notes###
  
  @tparam T the type that should be a model of CPrimitiveComputer.
  */
  template <typename T>
  struct CPrimitiveComputer : boost::DefaultConstructible<T>, boost::CopyConstructible<T>, boost::Assignable<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // Inner types
    typedef typename T::Primitive Primitive;
    typedef typename T::Space Space;

    // Methods
    BOOST_CONCEPT_USAGE( CPrimitiveComputer )
    {
      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
      ConceptUtils::sameType( myP, myX.primitive() );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // only if T is default constructible.
    Primitive myP;

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CPrimitiveComputer

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPrimitiveComputer_h

#undef CPrimitiveComputer_RECURSES
#endif // else defined(CPrimitiveComputer_RECURSES)
