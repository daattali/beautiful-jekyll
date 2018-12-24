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
 * @file CCellEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/16
 *
 * Header file for concept CCellEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CCellEmbedder_RECURSES)
#error Recursive header files inclusion detected in CCellEmbedder.h
#else // defined(CCellEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CCellEmbedder_RECURSES

#if !defined CCellEmbedder_h
/** Prevents repeated inclusion of headers. */
#define CCellEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/topology/CCellularGridSpaceND.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

/////////////////////////////////////////////////////////////////////////////
// class CCellEmbedder
/**
Description of \b concept '\b CCellEmbedder' <p>
@ingroup Concepts
@brief Aim:
A cell embedder is a mapping from unsigned cells to Euclidean points.
It adds inner types to functor.

### Refinement of
- CUnaryFunctor<T, T::Cell, T::RealPoint>

### Associated types :
- \e KSpace: the cellular grid space
- \e Cell: same as KSpace::Cell
- \e RealPoint: the type of Euclidean point
- \e Argument: type of the argument, same as KSpace::Cell
- \e Value: type of value, same as RealPoint

### Notation
- \e X : A type that is a model of CCellEmbedder
- \e x : object of type X
- \e p : object of type Cell

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
|Apply function|\e x(\e p)|              | \e Value      |              | return the value of the function \a x on argument \a p | | |

### Invariants

### Models

- CanonicCellEmbedder, ImageLinearCellEmbedder, ImplicitFunctionLinearCellEmbedder, ImplicitFunctionDiff1LinearCellEmbedder

### Notes

@tparam T the type that should be a model of CCellEmbedder.
*/
template <typename T>
struct CCellEmbedder : CUnaryFunctor<T, typename T::Cell, typename T::RealPoint>
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::KSpace KSpace;
  typedef typename T::Cell Cell;
  typedef typename T::RealPoint RealPoint;
  typedef typename T::Argument Argument;
  typedef typename T::Value Value;

  BOOST_CONCEPT_ASSERT(( CCellularGridSpaceND< KSpace > ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Cell, typename KSpace::Cell >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Cell, Argument >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< RealPoint, Value >::value ));
  BOOST_CONCEPT_USAGE( CCellEmbedder )
  {
    checkConstConstraints();
  }
  
  void checkConstConstraints() const
  { // operator()
    ConceptUtils::sameType( myRP, myX( myP ) );
  }
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Cell myP;
  RealPoint myRP;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CCellEmbedder

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CCellEmbedder_h

#undef CCellEmbedder_RECURSES
#endif // else defined(CCellEmbedder_RECURSES)
