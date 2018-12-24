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
 * @file CMatrix.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/20
 *
 * Header file for concept CMatrix.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CMatrix_RECURSES)
#error Recursive header files inclusion detected in CMatrix.h
#else // defined(CMatrix_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CMatrix_RECURSES

#if !defined CMatrix_h
/** Prevents repeated inclusion of headers. */
#define CMatrix_h

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
// class CMatrix
/**
Description of \b concept '\b CMatrix' <p>
@ingroup Concepts
@brief Aim:
Represent any static or dynamic sized matrix having sparse or dense representation.

### Refinement of
 - CVectorSpace

### Associated types

### Notation
 - \c Matrix : A type that is a model of CMatrix
 - \e x : const object of type \c Matrix
 - \e z : object of type \c Matrix
 - \e i, \e j : object of type \c Matrix::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Identity setter |  | \a x.setIdentity() |              |              |           |                |            |
| Number of rows      | \a x.rows()           |                   |  \c Index            |              |           |                |            |
| Number of columns      |  \a x.cols()           |                   | \c Index              |              |           |                |            |

### Invariants

### Models

### Notes

@tparam T the type that should be a model of CMatrix.
 */
template <typename T>
struct CMatrix : CVectorSpace<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Scalar Scalar;
    typedef typename T::Index Index;

    BOOST_CONCEPT_USAGE( CMatrix )
    {
        z.setIdentity();
        checkConstConstraints();
    }

    void checkConstConstraints() const
    {
        ConceptUtils::sameType(i, z.rows());
        ConceptUtils::sameType(j, z.cols());
    }
    // ------------------------- Private Datas --------------------------------
private:
    T z;
    Index i, j;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CMatrix
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CMatrix_h

#undef CMatrix_RECURSES
#endif // else defined(CMatrix_RECURSES)
