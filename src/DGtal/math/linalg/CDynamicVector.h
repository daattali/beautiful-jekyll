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
 * @file CDynamicVector.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CDynamicVector.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDynamicVector_RECURSES)
#error Recursive header files inclusion detected in CDynamicVector.h
#else // defined(CDynamicVector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDynamicVector_RECURSES

#if !defined CDynamicVector_h
/** Prevents repeated inclusion of headers. */
#define CDynamicVector_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/math/linalg/CVector.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace concepts
{
/////////////////////////////////////////////////////////////////////////////
// class CDynamicVector
/**
Description of \b concept '\b CDynamicVector' <p>
@ingroup Concepts
@brief Aim:
Represent any dynamic sized column vector having sparse or dense representation.

### Refinement of
 - CVector

### Associated types :

### Notation
 - \c DynamicVector : A type that is a model of CDynamicVector
 - \e x : object of type \c DynamicMatrix
 - \e i : object of type \c DynamicVector::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Constructor |  \a x(i)          |                   | \c DynamicVector              |              |           |                |            |

### Invariants

### Models
 - Eigen::VectorXd, Eigen::SparseVector, Eigen::DenseVector

### Notes

@tparam T the type that should be a model of CDynamicVector.
 */
template <typename T>
struct CDynamicVector : CVector<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;

    BOOST_CONCEPT_USAGE( CDynamicVector )
    {
      T zz(i);
    }
    // ------------------------- Private Datas --------------------------------
private:
    Index i;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CDynamicVector
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDynamicVector_h

#undef CDynamicVector_RECURSES
#endif // else defined(CDynamicVector_RECURSES)
