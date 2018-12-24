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
 * @file CDenseVector.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CDenseVector.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CDenseVector_RECURSES)
#error Recursive header files inclusion detected in CDenseVector.h
#else // defined(CDenseVector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CDenseVector_RECURSES

#if !defined CDenseVector_h
/** Prevents repeated inclusion of headers. */
#define CDenseVector_h

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
// class CDenseVector
/**
Description of \b concept '\b CDenseVector' <p>
@ingroup Concepts
@brief Aim:
Represent any dynamic or static sized matrix having dense representation.

### Refinement of
 - CVector

### Associated types

### Notation
 - \c DenseVector : A type that is a model of CDenseVector
 - \e i : object of type \c DenseVector::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Constant ref random accessor      | \a x(i)           |                   | \c const Scalar&              |              |           |                |            |
| Ref random accessor      | \a z(i)           |                   | \c Scalar&              |              |           |                |            |

### Invariants

### Models
 - SimpleVector

### Notes

@tparam T the type that should be a model of CDenseVector.
 */
template <typename T>
struct CDenseVector : CVector<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;
    typedef typename T::Scalar Scalar;

    BOOST_CONCEPT_USAGE( CDenseVector )
    {
				Scalar& aa = z(i);
				aa = aa; // to avoid compiler warning

        checkConstConstraints();
    }

    void checkConstConstraints() const
    {
				Scalar bb = z(i);
				bb = bb; // to avoid compiler warning
    }

    // ------------------------- Private Datas --------------------------------
private:
    T z;
    Index i;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CDenseVector
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CDenseVector_h

#undef CDenseVector_RECURSES
#endif // else defined(CDenseVector_RECURSES)
