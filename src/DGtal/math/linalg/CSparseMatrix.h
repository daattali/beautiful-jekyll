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
 * @file CSparseMatrix.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CSparseMatrix.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSparseMatrix_RECURSES)
#error Recursive header files inclusion detected in CSparseMatrix.h
#else // defined(CSparseMatrix_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSparseMatrix_RECURSES

#if !defined CSparseMatrix_h
/** Prevents repeated inclusion of headers. */
#define CSparseMatrix_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/linalg/CMatrix.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace concepts
{
/////////////////////////////////////////////////////////////////////////////
// class CSparseMatrix
/**
Description of \b concept '\b CSparseMatrix' <p>
@ingroup Concepts
@brief Aim:
Represent any dynamic or static sized matrix having sparse representation.

### Refinement of
 - CMatrix

### Associated types
 - Triplet triplet type

### Notation
 - \c SparseMatrix : A type that is a model of CSparseMatrix
 - \e ti, \e te : Instances of type that is a model of boost::InputIterator<Triplet>

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Fill from triplets      | \a x.setFromTriplets(ti,te)           |                   |           |              |           |                |            |

### Invariants

### Models
 - SimpleMatrix

### Notes

@tparam T the type that should be a model of CSparseMatrix.
@tparam TripletInterator the type that should be a model of boost::InputIterator<Triplet>
 */
template <typename T, typename TripletInterator>
struct CSparseMatrix : CMatrix<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;

    BOOST_CONCEPT_ASSERT(( boost::InputIterator<TripletInterator> ));

    BOOST_CONCEPT_USAGE( CSparseMatrix )
    {
        z.setFromTriplets(ti, te);
    }

    // ------------------------- Private Datas --------------------------------
private:
    T z;
    TripletInterator ti, te;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CSparseMatrix
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSparseMatrix_h

#undef CSparseMatrix_RECURSES
#endif // else defined(CSparseMatrix_RECURSES)
