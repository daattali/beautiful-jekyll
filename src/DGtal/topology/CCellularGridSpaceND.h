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
 * @file CCellularGridSpaceND.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2012/04/06
 *
 * Header file for concept CCellularGridSpaceND.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CCellularGridSpaceND_RECURSES)
#error Recursive header files inclusion detected in CCellularGridSpaceND.h
#else // defined(CCellularGridSpaceND_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CCellularGridSpaceND_RECURSES

#if !defined CCellularGridSpaceND_h
/** Prevents repeated inclusion of headers. */
#define CCellularGridSpaceND_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CConstSinglePassRange.h"
#include "DGtal/kernel/CInteger.h"
#include "DGtal/kernel/CUnsignedNumber.h"
#include "DGtal/kernel/CIntegralNumber.h"
#include "DGtal/topology/CPreCellularGridSpaceND.h"

//////////////////////////////////////////////////////////////////////////////

// @since 0.8 In DGtal::concepts
namespace DGtal {
  namespace concepts {

/////////////////////////////////////////////////////////////////////////////
// class CCellularGridSpaceND
/**
Description of \b concept '\b CCellularGridSpaceND' <p>
@ingroup Concepts

@brief Aim: This concept describes a cellular grid space in nD. In
these spaces obtained by cartesian product, cells have a cubic shape
that depends on the dimension: 0-cells are points, 1-cells are unit
segments, 2-cells are squares, 3-cells are cubes, and so on.

### Refinement of CPreCellularGridSpaceND

In addition of CPreCellularGridSpaceND, CCellularGridSpaceND add
bounds and related methods.

Models of CCellularGridSpaceND are used whenever you need to define a
topology on your subsets of the digital space, especially boundaries
of objects, curves and digital surfaces.

The space is generally finite (except for arbitrary size
integers). The user should choose between a closed (default) cell
space or an open cell space.

We refer the reader to \ref moduleCellularTopology for further
details.

### Associated types :

- \e Size: the integral unsigned type for representing sizes in the space (model of CUnsignedNumber and CIntegralNumber).

### Notation
- \e X : A type that is a model of \e CCellularGridSpaceND
- \e x : object of type \e X
- \e k : object of type Dimension
- \e i : object of type \e Integer
- \e c : object of type \e Cell
- \e sc : object of type \e SCell
- \e s : object of type \e Surfel
- \e p, \e p1, \e p2 : object of type \e Point
- \e v : object of type \e Vector
- \e sign: object of type \e Sign

### Definitions

- a model of CCellularGridSpaceND is said \b closed if it includes the
  cells of lower dimension along its bounds. It is indeed closed in
  the sense of the star-topology.
- a model of CCellularGridSpaceND is said \b open if it does not include the
  cells of lower dimension along its bounds. It is indeed open in
  the sense of the star-topology.
- when it is initialized with points \e p1 and \e p2, the cellular
  space has a parallelepipedic shape bounded by the given
  coordinates. Any valid cell has then \e digital coordinates
  in-between \e p1 and \e p2 (included).
- when it is default constructed, it is bounded by points \e -p and \e p
 (\e p is model dependant)
- \b adjacent cells to some cell \e c are cells, lying within the space
  bounds, with the same topology as \e c but whose one of their
  digital coordinates differs by one. They are often called 1-adjacent.
- \b incident cells to some cell \e c are cells, lying within the space
  bounds, that are either a face of \e c or such that \e c is one of
  their faces.


### Valid expressions and semantics

| Name          | Expression       | Type requirements | Return type   | Precondition | Semantics                             | Post condition | Complexity |
|---------------|------------------|-------------------|---------------|--------------|---------------------------------------|----------------|------------|
| initialization|\e x.\e init(p1, p2, b)| b is \c bool | \c bool       |              | initializes the space so that cells are within the bounds p1 and p2, returns true iff the initialization was valid (ie, such bounds are representable with these integers).      |                |            |
| Size or width | \e x.size( \e k )    |               | \e Integer    |              | returns the size/width of the space along the axis \e k | |         |
| Minimal coordinate | \e x.min( \e k )|               | \e Integer    |              | returns the minimal possible digital coordinate along the axis \e k | | |
| Maximal coordinate | \e x.max( \e k )|               | \e Integer    |              | returns the maximal possible digital coordinate along the axis \e k | | |
| Lower bound   | \e x.lowerBound()|                   | \e Point      |              | returns the lowest point in the space, i.e. \e p1 |    |            |
| Upper bound   | \e x.upperBound()|                   | \e Point      |              | returns the uppermost point in the space, i.e. \e p1 | |            |
| Lower cell    | \e x.lowerCell() |                   | \e Cell       |              | returns the lowest cell in the space  |                |            |
| Upper cell    | \e x.upperCell() |                   | \e Cell       |              | returns the uppermost cell in the space|               |            |
| Closedness    | \e x.isSpaceClosed()|                | \c bool       |              | returns 'true' iff the cellular space is \e closed|    |            |
|               |                  |                   |               |              |                                       |                |            |
| Get first cell|\e x.uFirst(\e c) |                   | \e Cell       |              | returns the first cell of the space with same topology as \e c | |  |
| Get last cell |\e x.uLast(\e c)  |                   | \e Cell       |              | returns the last cell of the space with same topology as \e c | |  |
| Get maximal cell along some axis|\e x.uGetMax(\e c,\e k)| | \e Cell  |              | returns the same cell as \e c except the \e k-th coordinate that is the maximal possible | | |
| Get minimal cell along some axis|\e x.uGetMin(\e c,\e k)| | \e Cell  |              | returns the same cell as \e c except the \e k-th coordinate that is the minimal possible | | |
| Distance to upper bound |\e x.uDistanceToMax(\e c,\e k)| | \e Integer  |            | returns the number of increments to do along the \e k-th axis to reach the upper bound | | |
| Distance to lower bound |\e x.uDistanceToMin(\e c,\e k)| | \e Integer  |            | returns the number of decrements to do along the \e k-th axis to reach the lower bound | | |
|               |                  |                   |               |              |                                       |                |            |
| Get first cell|\e x.sFirst(\e sc) |                   | \e SCell     |              | returns the first cell of the space with same topology as \e sc | |  |
| Get last cell |\e x.sLast(\e sc)  |                   | \e SCell     |              | returns the last cell of the space with same topology as \e sc | |  |
| Get maximal cell along some axis|\e x.sGetMax(\e sc,\e k)| | \e SCell|              | returns the same cell as \e sc except the \e k-th coordinate that is the maximal possible | | |
| Get minimal cell along some axis|\e x.sGetMin(\e sc,\e k)| | \e SCell|              | returns the same cell as \e sc except the \e k-th coordinate that is the minimal possible | | |
| Distance to upper bound |\e x.sDistanceToMax(\e sc,\e k)| | \e Integer  |           | returns the number of increments to do along the \e k-th axis to reach the upper bound | | |
| Distance to lower bound |\e x.sDistanceToMin(\e sc,\e k)| | \e Integer  |           | returns the number of decrements to do along the \e k-th axis to reach the lower bound | | |


### Invariants

### Models

- KhalimskySpaceND

### Notes

@tparam T the type that should be a model of CCellularGridSpaceND.
 */
template <typename T>
struct CCellularGridSpaceND
  : CPreCellularGridSpaceND<T>
{
  // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Size Size;

  BOOST_CONCEPT_ASSERT(( CUnsignedNumber< Size > ));
  BOOST_CONCEPT_ASSERT(( CIntegralNumber< Size > ));

  BOOST_CONCEPT_USAGE( CCellularGridSpaceND )
  {
    ConceptUtils::sameType( myBool, myX.init( myP1, myP2, myBool ) );
    checkConstConstraints();
  }
  void checkConstConstraints() const
  {
    ConceptUtils::sameType( mySize, myX.size( myDim ) );
    ConceptUtils::sameType( myInteger, myX.min( myDim ) );
    ConceptUtils::sameType( myInteger, myX.max( myDim ) );
    ConceptUtils::sameType( myP1, myX.lowerBound() );
    ConceptUtils::sameType( myP2, myX.upperBound() );
    ConceptUtils::sameType( myCell, myX.lowerCell() );
    ConceptUtils::sameType( myCell, myX.upperCell() );
    ConceptUtils::sameType( myBool, myX.isSpaceClosed() );
    // -------------------- Unsigned cell geometry services --------------------
    ConceptUtils::sameType( myCell, myX.uFirst( myCell ) );
    ConceptUtils::sameType( myCell, myX.uLast( myCell ) );
    ConceptUtils::sameType( myCell, myX.uGetMax( myCell, myDim ) );
    ConceptUtils::sameType( myCell, myX.uGetMin( myCell, myDim ) );
    ConceptUtils::sameType( myInteger, myX.uDistanceToMax( myCell, myDim ) );
    ConceptUtils::sameType( myInteger, myX.uDistanceToMin( myCell, myDim ) );
    // -------------------- Signed cell geometry services --------------------
    ConceptUtils::sameType( mySCell, myX.sFirst( mySCell ) );
    ConceptUtils::sameType( mySCell, myX.sLast( mySCell ) );
    ConceptUtils::sameType( mySCell, myX.sGetMax( mySCell, myDim ) );
    ConceptUtils::sameType( mySCell, myX.sGetMin( mySCell, myDim ) );
    ConceptUtils::sameType( myInteger, myX.sDistanceToMax( mySCell, myDim ) );
    ConceptUtils::sameType( myInteger, myX.sDistanceToMin( mySCell, myDim ) );

}
  // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  typename CPreCellularGridSpaceND<T>::Integer myInteger;
  Size mySize;
  Dimension myDim;
  typename CPreCellularGridSpaceND<T>::Point myP1, myP2;
  typename CPreCellularGridSpaceND<T>::Cell myCell;
  typename CPreCellularGridSpaceND<T>::SCell mySCell;
  bool myBool;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CCellularGridSpaceND

} // namespace concepts
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CCellularGridSpaceND_h

#undef CCellularGridSpaceND_RECURSES
#endif // else defined(CCellularGridSpaceND_RECURSES)
