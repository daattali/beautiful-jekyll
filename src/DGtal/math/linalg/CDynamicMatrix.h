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
 * @file CDynamicMatrix.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CDynamicMatrix.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDynamicMatrix_RECURSES)
#error Recursive header files inclusion detected in CDynamicMatrix.h
#else // defined(CDynamicMatrix_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDynamicMatrix_RECURSES

#if !defined CDynamicMatrix_h
/** Prevents repeated inclusion of headers. */
#define CDynamicMatrix_h

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
// class CDynamicMatrix
/**
Description of \b concept '\b CDynamicMatrix' <p>
@ingroup Concepts
@brief Aim:
Represent any dynamic sized matrix having sparse or dense representation.

### Refinement of
 - CMatrix

### Associated types

### Notation
 - \c DynamicMatrix : A type that is a model of CDynamicMatrix
 - \e x : object of type \c DynamicMatrix
 - \e i, \e j : object of type \c DynamicMatrix::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Constructor |  \a x(i, j)          |                   | \c DynamicVector              |              |           |                |            |

### Invariants

### Models
 - Eigen::MatrixXd, Eigen::SparseMatrix, Eigen::DenseMatrix

### Notes

@tparam T the type that should be a model of CDynamicMatrix.
 */
template <typename T>
struct CDynamicMatrix : CMatrix<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;

    BOOST_CONCEPT_USAGE( CDynamicMatrix )
    {
        T xx(i, j);
    }
    // ------------------------- Private Datas --------------------------------
private:
    Index i, j;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CDynamicMatrix
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDynamicMatrix_h

#undef CDynamicMatrix_RECURSES
#endif // else defined(CDynamicMatrix_RECURSES)
