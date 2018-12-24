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
 * @file CPointEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/16
 *
 * Header file for concept CPointEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CPointEmbedder_RECURSES)
#error Recursive header files inclusion detected in CPointEmbedder.h
#else // defined(CPointEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CPointEmbedder_RECURSES

#if !defined CPointEmbedder_h
/** Prevents repeated inclusion of headers. */
#define CPointEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/kernel/CSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
/////////////////////////////////////////////////////////////////////////////
// class CPointEmbedder
/**
Description of \b concept '\b CPointEmbedder' <p>
@ingroup Concepts
@brief Aim:
A point embedder is a mapping from digital points to Euclidean points.
It adds inner types to functor.

### Refinement of
- CUnaryFunctor<T, T::Point, T::RealPoint>

### Associated types :
- \e Space: the digital space
- \e Point: same as Space::Point
- \e Argument: type of the argument, same as Space::Point
- \e Value: type of value, same as Space::RealPoint

### Notation
 - \e X : A type that is a model of CPointEmbedder
 - \e x : object of type X
 - \e p : object of type Point

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
|Apply function|\e x(\e p)|              | \e Value      |              | return the value of the function \a x on argument \a p | | |

### Invariants

### Models

- CanonicEmbedder, RegularPointEmbedder

### Notes

@tparam T the type that should be a model of CPointEmbedder.
*/
template <typename T>
struct CPointEmbedder : CUnaryFunctor<T, typename T::Point, typename T::RealPoint>
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Space Space;
  typedef typename T::Point Point;
  typedef typename T::RealPoint RealPoint;
  typedef typename T::Argument Argument;
  typedef typename T::Value Value;

  BOOST_CONCEPT_ASSERT(( CSpace< Space > ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Point, typename Space::Point >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< Point, Argument >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< RealPoint, typename Space::RealPoint >::value ));
  BOOST_STATIC_ASSERT(( ConceptUtils::SameType< RealPoint, Value >::value ));
  BOOST_CONCEPT_USAGE( CPointEmbedder )
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
  Point myP;
  RealPoint myRP;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CPointEmbedder
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CPointEmbedder_h

#undef CPointEmbedder_RECURSES
#endif // else defined(CPointEmbedder_RECURSES)
