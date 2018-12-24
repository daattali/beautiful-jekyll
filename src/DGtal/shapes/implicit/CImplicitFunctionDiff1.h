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
 * @file CImplicitFunctionDiff1.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/02/28
 *
 * Header file for concept CImplicitFunctionDiff1.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CImplicitFunctionDiff1_RECURSES)
#error Recursive header files inclusion detected in CImplicitFunctionDiff1.h
#else // defined(CImplicitFunctionDiff1_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CImplicitFunctionDiff1_RECURSES

#if !defined CImplicitFunctionDiff1_h
/** Prevents repeated inclusion of headers. */
#define CImplicitFunctionDiff1_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/shapes/implicit/CImplicitFunction.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CImplicitFunctionDiff1
  /**
Description of \b concept '\b CImplicitFunctionDiff1' <p>
     @ingroup Concepts

@brief Aim: Describes a 1-differentiable function of the form
     f(x), where x is some real point in the given space, and f(x) is
     some value. 

 ### Refinement of CImplicitFunction
      
 ### Associated types :    
     - RealPoint: the type for the domain
     - RealVector: the type for a vector in the domain
     - Value: the type for the range

 ### Notation
     - \c X : A type that is a model of CImplicitFunctionDiff1
     - \c f : objet of type X
     - \c a : objet of type RealPoint
    
 ### Definitions
    
 ### Valid expressions and

| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
| gradient operator | \c gradient( \c a ) |        | RealVector  |                  |Evaluates the gradient of the function \c f at point \c a | | |  
      
 ### Invariants
    
 ### Models
      ImplicitPolynomial3Shape

 ### Notes

@tparam T the type that should be a model of CImplicitFunctionDiff1.
   */
  template <typename T> 
  struct CImplicitFunctionDiff1 : CImplicitFunction<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    // 1. define first provided types (i.e. inner types), like
    typedef typename T::RealPoint RealPoint;
    typedef typename T::RealVector RealVector;

    BOOST_CONCEPT_USAGE( CImplicitFunctionDiff1 )
    {
      // check const methods.
      checkConstConstraints();
    }
    void checkConstConstraints() const
    {
      // const method dummyConst should take parameter myA of type A and return
      // something of type B
      ConceptUtils::sameType( myB, myX.gradient( myA ) );
    }
    // ------------------------- Private Datas --------------------------------
  private:
    T myX; // do not require T to be default constructible.
    RealPoint myA;
    RealVector myB;
    
  }; // end of concept CImplicitFunctionDiff1
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CImplicitFunctionDiff1_h

#undef CImplicitFunctionDiff1_RECURSES
#endif // else defined(CImplicitFunctionDiff1_RECURSES)
