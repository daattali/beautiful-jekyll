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
 * @file CDigitalSurfaceEmbedder.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/16
 *
 * Header file for concept CDigitalSurfaceEmbedder.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDigitalSurfaceEmbedder_RECURSES)
#error Recursive header files inclusion detected in CDigitalSurfaceEmbedder.h
#else // defined(CDigitalSurfaceEmbedder_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDigitalSurfaceEmbedder_RECURSES

#if !defined CDigitalSurfaceEmbedder_h
/** Prevents repeated inclusion of headers. */
#define CDigitalSurfaceEmbedder_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/topology/CSCellEmbedder.h"
//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

/////////////////////////////////////////////////////////////////////////////
// class CDigitalSurfaceEmbedder
/**
Description of \b concept '\b CDigitalSurfaceEmbedder' <p>
@ingroup Concepts
@brief Aim:
A digital surface embedder is a specialized mapping from signed cells to Euclidean points.
It adds inner types to functor as well as a method to access the digital surface.

### Refinement of
- CSCellEmbedder<T>

### Associated types :
- \e KSpace: the cellular grid space
- \e SCell: same as KSpace::SCell
- \e RealPoint: the type of Euclidean point
- \e Surface: a digital surface, some concrete DigitalSurface<X>.
- \e Argument: type of the argument, same as SCell
- \e Value: type of value, same as RealPoint

### Notation
 - \e X : A type that is a model of CDigitalSurfaceEmbedder
 - \e x : object of type X
 - \e p : object of type SCell

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
|Apply function|\e x(\e p)|              | \e Value      |              | return the value of the function \a x on argument \a p | | |
|Accessor to surface|\e x.surface()|     | \e Surface    |              | return the associated digital surface | | |

### Invariants

### Models

### Notes

@tparam T the type that should be a model of CDigitalSurfaceEmbedder.
*/
template <typename T>
struct CDigitalSurfaceEmbedder : CSCellEmbedder<T>
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::KSpace KSpace;
  typedef typename T::Surface Surface;
  typedef typename T::SCell SCell;
  typedef typename T::RealPoint RealPoint;
  typedef typename T::Argument Argument;
  typedef typename T::Value Value;

  // Already checked in CSCellEmbedder
  // BOOST_CONCEPT_ASSERT(( CCellularGridSpaceND< KSpace > ));
  // BOOST_STATIC_ASSERT(( ConceptUtils::SameType< SCell, typename KSpace::SCell >::value ));
  // BOOST_STATIC_ASSERT(( ConceptUtils::SameType< SCell, Argument >::value ));
  // BOOST_STATIC_ASSERT(( ConceptUtils::SameType< RealPoint, typename KSpace::RealPoint >::value ));
  // BOOST_STATIC_ASSERT(( ConceptUtils::SameType< RealPoint, Value >::value ));
  BOOST_CONCEPT_USAGE( CDigitalSurfaceEmbedder )
  {
    checkConstConstraints();
  }
  
  void checkConstConstraints() const
  { // operator()
    // ConceptUtils::sameType( myRP, myX( myP ) );
    ConceptUtils::sameType( mySurface, myX.surface() );
  }
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  // SCell myP;
  // RealPoint myRP;
  Surface mySurface;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CDigitalSurfaceEmbedder

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDigitalSurfaceEmbedder_h

#undef CDigitalSurfaceEmbedder_RECURSES
#endif // else defined(CDigitalSurfaceEmbedder_RECURSES)
