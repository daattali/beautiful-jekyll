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
 * @file CVector.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/20
 *
 * Header file for concept CVector.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CVector_RECURSES)
#error Recursive header files inclusion detected in CVector.h
#else // defined(CVector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CVector_RECURSES

#if !defined CVector_h
/** Prevents repeated inclusion of headers. */
#define CVector_h

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
// class CVector
/**
Description of \b concept '\b CVector' <p>
@ingroup Concepts
@brief Aim:
Represent any static or dynamic sized column vector having sparse or dense representation.

### Refinement of
 - CVectorSpace

### Associated types

### Notation
 - \c Vector : A type that is a model of CVector
 - \e x : const object of type \c Vector
 - \e z : object of type \c Vector
 - \e i : object of type \c Vector::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Number of rows      | \a x.rows()           |                   |  \c Index            |              |  Returns the size of the vector       |                |            |

### Invariants

### Models

 EigenLinearAlgebraBackend::DenseVector, SimpleMatrix::Vector

### Notes

@tparam T the type that should be a model of CVector.
 */
template <typename T>
struct CVector : CVectorSpace<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Scalar Scalar;
    typedef typename T::Index Index;

    BOOST_CONCEPT_USAGE( CVector )
    {
        checkConstConstraints();
    }

    void checkConstConstraints() const
    {
        ConceptUtils::sameType(i, z.rows());
    }

    // ------------------------- Private Datas --------------------------------
private:
  T z;
  Index i;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CVector
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CVector_h

#undef CVector_RECURSES
#endif // else defined(CVector_RECURSES)
