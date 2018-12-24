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
 * @file CDiscreteExteriorCalculusVectorSpace.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/20
 *
 * Header file for concept CDiscreteExteriorCalculusVectorSpace.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDiscreteExteriorCalculusVectorSpace_RECURSES)
#error Recursive header files inclusion detected in CDiscreteExteriorCalculusVectorSpace.h
#else // defined(CDiscreteExteriorCalculusVectorSpace_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDiscreteExteriorCalculusVectorSpace_RECURSES

#if !defined CDiscreteExteriorCalculusVectorSpace_h
/** Prevents repeated inclusion of headers. */
#define CDiscreteExteriorCalculusVectorSpace_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/linalg/CVectorSpace.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
/////////////////////////////////////////////////////////////////////////////
// class CDiscreteExteriorCalculusVectorSpace
/**
Description of \b concept '\b CDiscreteExteriorCalculusVectorSpace' <p>
@ingroup Concepts
@brief Aim:
Lift linear algebra container concept into the dec package.

### Refinement of

### Associated types
  - \c Container: Associated container, a model of concept CLinearAlgebraContainer.
  - \c Calculus: Associated discrete exterior calculus.

### Notation

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Constructor from calculus      | t(calculus)           |                   |               |              |           |                |            |
| Constructor from calculus and container      | t(calculus, container)           |                   |               |              |           |                |            |

### Invariants

### Models
 - KForm
 - LinearOperator
 - VectorField

### Notes

@tparam T the type that should be a model of CDiscreteExteriorCalculusVectorSpace.
*/
template <typename T>
struct CDiscreteExteriorCalculusVectorSpace : CVectorSpace<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Container Container;
    typedef typename T::Calculus Calculus;

    BOOST_CONCEPT_USAGE( CDiscreteExteriorCalculusVectorSpace )
    {
        T t0(calculus);
        T t1(calculus, container);
    }
    // ------------------------- Private Datas --------------------------------
private:
    Container container;
    Calculus calculus;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CDiscreteExteriorCalculusVectorSpace
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDiscreteExteriorCalculusVectorSpace_h

#undef CDiscreteExteriorCalculusVectorSpace_RECURSES
#endif // else defined(CDiscreteExteriorCalculusVectorSpace_RECURSES)
