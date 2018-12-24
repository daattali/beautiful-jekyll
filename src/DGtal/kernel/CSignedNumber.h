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
 * @file CSignedNumber.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/02
 *
 * Header file for concept CSignedNumber.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CSignedNumber_RECURSES)
#error Recursive header files inclusion detected in CSignedNumber.h
#else // defined(CSignedNumber_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CSignedNumber_RECURSES

#if !defined CSignedNumber_h
/** Prevents repeated inclusion of headers. */
#define CSignedNumber_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/base/CQuantity.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CSignedNumber
  /**
Description of \b concept '\b CSignedNumber' <p>
     @ingroup Concepts
     @brief Aim: Concept checking for Signed Numbers. Models of this
     concept should be listed in NumberTraits class and should have
     the isSigned property.
     
 ### Refinement of 
    - CQuantity

 ### Associated types 
    
 ### Notation
     - \a X : A type that is a model of CSignedNumber
     - \a x, \a y  : Object of type X
    
 ### Definitions
    
 ### Valid expressions and 



Name | Expression |  Type requirements | Return type| Precondition | Semantics | Postcondition | Complexity 
-----|------------|--------------------|------------|--------------|-----------|---------------|-----------
\a X should be tagged \b true in \a NumberTraits for \a IsSigned | typename NumberTraits<X>::IsSigned | TagTrue | | | | | |
    
 ### Invariants###

    
 ### Models###
     double, BigInteger,  short, int, long long, int16_t, int32_t, int64_t.

 ### Notes###

@tparam T the type that is checked. T should be a model of
     CBoundedInteger.
    
   */
  template <typename T>
  struct CSignedNumber: CQuantity<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    BOOST_CONCEPT_USAGE(CSignedNumber)
    {
      // Will compile iff Signed.
      ConceptUtils::checkTrue(myIsSigned );
    }
    
    // ------------------------- Private Datas --------------------------------
  private:
    
    // ------------------------- Internals ------------------------------------
  private:
    typename NumberTraits<T>::IsSigned myIsSigned;

  }; // end of concept CSignedNumber
  } 
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CSignedNumber_h

#undef CSignedNumber_RECURSES
#endif // else defined(CSignedNumber_RECURSES)
