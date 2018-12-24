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
 * @file CWithGradientMap.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/16
 *
 * Header file for concept CWithGradientMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CWithGradientMap_RECURSES)
#error Recursive header files inclusion detected in CWithGradientMap.h
#else // defined(CWithGradientMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CWithGradientMap_RECURSES

#if !defined CWithGradientMap_h
/** Prevents repeated inclusion of headers. */
#define CWithGradientMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
/////////////////////////////////////////////////////////////////////////////
// class CWithGradientMap
/**
Description of \b concept '\b CWithGradientMap' <p>
@ingroup Concepts

@brief Aim:
Such object provides a gradient map that associates to each argument some real vector.

### Refinement of

### Associated types :
   - \e Argument : the type of each element of the domain
   - \e RealVector : the type for representing the gradient values.
   - \e GradientMap : functor \e Argument -> \e RealVector, a model of CUnaryFunctor<T, Argument, RealVector > and boost::CopyConstructible.
   - \e gradientMap() const: returns a \e GradientMap.

### Notation
 - \e X : A type that is a model of CWithGradientMap
 - \e x : object of type X

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Gets the gradient map |\e x.gradientMap()| |\e GradientMap |          | returns the gradient functor | | |      |

### Invariants

### Models
    ImplicitFunctionDiff1LinearCellEmbedder, DigitalSurfaceEmbedderWithNormalVectorEstimator

### Notes

@tparam T the type that should be a model of CWithGradientMap.
 */
template <typename T>
struct CWithGradientMap
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Argument Argument;
  typedef typename T::RealVector RealVector;
  typedef typename T::GradientMap GradientMap;
  BOOST_CONCEPT_ASSERT(( boost::CopyConstructible< GradientMap > ));
  BOOST_CONCEPT_ASSERT(( CUnaryFunctor< GradientMap, Argument, RealVector > ));
  BOOST_CONCEPT_USAGE( CWithGradientMap )
  {
    checkConstConstraints();
  }
  void checkConstConstraints() const
    {
      ConceptUtils::sameType( myGMap, myX.gradientMap() );
    }
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  GradientMap myGMap;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CWithGradientMap
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CWithGradientMap_h

#undef CWithGradientMap_RECURSES
#endif // else defined(CWithGradientMap_RECURSES)
