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
 * @file CStaticMatrix.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CStaticMatrix.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CStaticMatrix_RECURSES)
#error Recursive header files inclusion detected in CStaticMatrix.h
#else // defined(CStaticMatrix_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CStaticMatrix_RECURSES

#if !defined CStaticMatrix_h
/** Prevents repeated inclusion of headers. */
#define CStaticMatrix_h

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
// class CStaticMatrix
/**
Description of \b concept '\b CStaticMatrix' <p>
@ingroup Concepts
@brief Aim:
Represent any static sized matrix having sparse or dense representation.

### Refinement of
 - CMatrix
 - boost::DefaultConstructible

### Associated types

### Notation
 - \c StaticMatrix : A type that is a model of CStaticMatrix
 - \e i, \e j : object of type \c StaticMatrix::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Static rows number      |  \a StaticVector::M          |                   | \c StaticVector::Index              |              |           |                |            |
| Static cols number      |  \a StaticVector::N          |                   | \c StaticVector::Index              |              |           |                |            |

### Invariants

### Models
 - SimpleMatrix

### Notes

@tparam T the type that should be a model of CStaticMatrix.
 */
template <typename T>
struct CStaticMatrix : CMatrix<T>, boost::DefaultConstructible<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;

    BOOST_CONCEPT_USAGE( CStaticMatrix )
    {
        ConceptUtils::sameType( i, T::M );
        ConceptUtils::sameType( j, T::N );
    }
    // ------------------------- Private Datas --------------------------------
private:
    Index i, j;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CStaticMatrix
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CStaticMatrix_h

#undef CStaticMatrix_RECURSES
#endif // else defined(CStaticMatrix_RECURSES)
