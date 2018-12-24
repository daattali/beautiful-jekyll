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
 * @file CDenseMatrix.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CDenseMatrix.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDenseMatrix_RECURSES)
#error Recursive header files inclusion detected in CDenseMatrix.h
#else // defined(CDenseMatrix_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDenseMatrix_RECURSES

#if !defined CDenseMatrix_h
/** Prevents repeated inclusion of headers. */
#define CDenseMatrix_h

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
// class CDenseMatrix
/**
Description of \b concept '\b CDenseMatrix' <p>
@ingroup Concepts
@brief Aim:
Represent any dynamic or static sized matrix having dense representation.

### Refinement of
 - CMatrix

### Associated types

### Notation
 - \c DenseMatrix : A type that is a model of CDenseMatrix
 - \e i, \e j : object of type \c DenseMatrix::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Constant ref random accessor      | \a x(i, j)           |                   | \c const Scalar&              |              |           |                |            |
| Ref random accessor      | \a z(i, j)           |                   | \c Scalar&              |              |           |                |            |

### Invariants

### Models
 - SimpleMatrix

### Notes

@tparam T the type that should be a model of CDenseMatrix.
 */
template <typename T>
struct CDenseMatrix : CMatrix<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;
    typedef typename T::Scalar Scalar;

    BOOST_CONCEPT_USAGE( CDenseMatrix )
    {
				Scalar& aa = z(i, j);
				aa = aa; // to avoid compiler warning

        checkConstConstraints();
    }

    void checkConstConstraints() const
    {
				Scalar bb = z(i, j);
				bb = bb; // to avoid compiler warning
    }

    // ------------------------- Private Datas --------------------------------
private:
    T z;
    Index i, j;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CDenseMatrix
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDenseMatrix_h

#undef CDenseMatrix_RECURSES
#endif // else defined(CDenseMatrix_RECURSES)
