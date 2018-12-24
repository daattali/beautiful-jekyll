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
 * @file
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/01
 *
 * Header file for concept CBoundedInteger.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CBoundedInteger_RECURSES)
#error Recursive header files inclusion detected in CBoundedInteger.h
#else // defined(CBoundedInteger_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CBoundedInteger_RECURSES

#if !defined CBoundedInteger_h
/** Prevents repeated inclusion of headers. */
#define CBoundedInteger_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/base/CQuantity.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CBoundedNumber
  /**
Description of \b concept '\b CBoundedNumber' <p>
     @ingroup Concepts

@brief Aim: The concept CBoundedNumber specifies what are the bounded
     numbers. Models of this
     concept should be listed in NumberTraits class and should have
     the isBounded property.

 ### Refinement of
  - CQuantity<T>

 ### Associated types:

 ### Notation
     - \a X : A type that is a model of CBoundedNumber

 ### Definitions

 ### Valid expressions and semantics


Name | Expression |  Type requirements | Return type| Precondition | Semantics | Postcondition | Complexity 
-----|------------|--------------------|------------|--------------|-----------|---------------|-----------
\a X should be tagged \b true in \a NumberTraits for \a IsBounded | typename NumberTraits<X>::IsBounded | TagTrue | | | | | |
  
 ### Invariants

 ### Models

short, int, unsigned int, long long, unsigned long long,
uint16_t, uint32_t, uint64_t, int16_t, int32_t, int64_t.

 ### Notes

@tparam T the type that is checked. T should be a model of
     CBoundedNumber.
   */
  template <typename T>
  struct CBoundedNumber: CQuantity<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    BOOST_CONCEPT_USAGE(CBoundedNumber)
    {

      // Bounded Number should have a TagTrue tag to IsBounded type.
      ConceptUtils::checkTrue( myIsBounded );

    }

    // ------------------------- Private Datas --------------------------------
  private:
    T myX;
    typename NumberTraits<T>::IsBounded myIsBounded;

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of concept CBoundedNumber
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CBoundedNumber_h

#undef CBoundedNumber_RECURSES
#endif // else defined(CBoundedNumber_RECURSES)
