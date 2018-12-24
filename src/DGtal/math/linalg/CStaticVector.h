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
 * @file CStaticVector.h
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systemes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2014/03/21
 *
 * Header file for concept CStaticVector.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CStaticVector_RECURSES)
#error Recursive header files inclusion detected in CStaticVector.h
#else // defined(CStaticVector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CStaticVector_RECURSES

#if !defined CStaticVector_h
/** Prevents repeated inclusion of headers. */
#define CStaticVector_h

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
// class CStaticVector
/**
Description of \b concept '\b CStaticVector' <p>
@ingroup Concepts
@brief Aim:
Represent any static sized column vector having sparse or dense representation.

### Refinement of
 - CVector
 - boost::DefaultConstructible

### Associated types :

### Notation
 - \c StaticVector : A type that is a model of CStaticVector
 - \e i : object of type \c StaticVector::Index

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| Static size member      |  \a StaticVector::dimension          |                   | \c StaticVector::Index              |              |           |                |            |

### Invariants

### Models

 - PointVector
 - SimpleMatrix::Vector

### Notes

@tparam T the type that should be a model of CStaticVector.
 */
template <typename T>
struct CStaticVector : CVector<T>, boost::DefaultConstructible<T>
{
    // ----------------------- Concept checks ------------------------------
public:
    typedef typename T::Index Index;

    BOOST_CONCEPT_USAGE( CStaticVector )
    {
        ConceptUtils::sameType( i, T::dimension );
    }
    // ------------------------- Private Datas --------------------------------
private:
    Index i;

    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CStaticVector
}
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CStaticVector_h

#undef CStaticVector_RECURSES
#endif // else defined(CStaticVector_RECURSES)
