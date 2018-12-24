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
 * @file CBinner.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/10/27
 *
 * Header file for concept CBinner.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CBinner_RECURSES)
#error Recursive header files inclusion detected in CBinner.h
#else // defined(CBinner_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBinner_RECURSES

#if !defined CBinner_h
/** Prevents repeated inclusion of headers. */
#define CBinner_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/CEuclideanRing.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
/////////////////////////////////////////////////////////////////////////////
// class CBinner
/**
Description of \b concept '\b CBinner' <p>
@ingroup Concepts

@brief Aim: Represents an object that places a quantity into a bin,
i.e. a functor that associates a natural integer to a continuous
value.

It is used for instance when computing an histogram over samples of a
continuous random variable.

### Refinement of boost::CopyConstructible

### Associated types :
- \c Quantity: the type of domain values (i.e. continuous values), a model of CEuclideanRing.
- \c Bin: should be some unsigned integral type and satisfy boost::is_integral and boost::is_unsigned.

### Notation
 - \c X : A type that is a model of CBinner
 - \e x, \e y : object of type X

### Definitions

### Valid expressions and semantics

| Name  | Expression | Type requirements | Return type   | Precondition | Semantics | Post condition | Complexity |
|-------|------------|-------------------|---------------|--------------|-----------|----------------|------------|
| construction | \c X( \e m, \e M, \e n ) | \e m and \e M are \c Quantity, \e n is a \c Bin | | | | Constructs a binner with \e n bins and range from \e m to \e M | | | 
| apply | \e x( \e q ) | \e q is a \c Quantity | \c Bin  |              | returns the bin in which fall \e q | | |

### Invariants

### Models

- RegularBinner

### Notes

@tparam T the type that should be a model of CBinner.
 */
template <typename T>
struct CBinner : boost::CopyConstructible<T>
{
    // ----------------------- Concept checks ------------------------------
public:
  typedef typename T::Quantity Quantity;
  typedef typename T::Bin Bin;
  BOOST_CONCEPT_ASSERT(( CEuclideanRing< Quantity > ));
  BOOST_STATIC_ASSERT(( boost::is_integral<Bin>::value ));
  BOOST_STATIC_ASSERT(( boost::is_unsigned<Bin>::value ));

  // 2. then check the presence of data members, operators and methods with
  BOOST_CONCEPT_USAGE( CBinner )
  {
    myClone = new T( myQ, myQ, myBin );
    checkConstConstraints();
  }
  void checkConstConstraints() const
  {
    ConceptUtils::sameType( myBin, myX( myQ ) );
  }
    // ------------------------- Private Datas --------------------------------
private:
  T myX; // do not require T to be default constructible.
  Quantity myQ;
  Bin myBin;
  T* myClone;
  
    // ------------------------- Internals ------------------------------------
private:

}; // end of concept CBinner
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBinner_h

#undef CBinner_RECURSES
#endif // else defined(CBinner_RECURSES)
