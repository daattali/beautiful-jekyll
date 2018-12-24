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
 * @file CUnsignedNumber.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/02
 *
 * Header file for concept CUnsignedNumber.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CUnsignedNumber_RECURSES)
#error Recursive header files inclusion detected in CUnsignedNumber.h
#else // defined(CUnsignedNumber_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CUnsignedNumber_RECURSES

#if !defined CUnsignedNumber_h
/** Prevents repeated inclusion of headers. */
#define CUnsignedNumber_h

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
  // class CUnsignedNumber
  /**
Description of \b concept '\b CUnsignedNumber' <p>
     @ingroup Concepts

     @brief Aim: Concept checking for Unsigned numbers. Models of this
     concept should be listed in NumberTraits class and should have
     the isUnsigned property.
     
 ### Refinement of
    - CQuantity
    
 ### Associated types :
    
 ### Notation
     - \e X : A type that is a model of CUnsignedNumber
     - \e x, \e y  : Object of type X
    
 ### Definitions
    
 ### Valid expressions  


Name | Expression |  Type requirements | Return type| Precondition | Semantics | Postcondition | Complexity 
-----|------------|--------------------|------------|--------------|-----------|---------------|-----------
\a X should be tagged \b true in \a NumberTraits for \a IsUnsigned. | typename NumberTraits<X>::IsUnsigned | TagTrue | | | | | |
    
 ### Invariants###
    
 ### Models###
     unsigned short, unsigned int, unsigned long long, uint16_t, uint32_t, uint64_t.
    
 ### Notes###


   */
  template <typename T>
  struct CUnsignedNumber: CQuantity<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    BOOST_CONCEPT_USAGE(CUnsignedNumber)
    {
      // Will compile iff Unsigned.
      ConceptUtils::checkTrue( myIsUnsigned );
    }
    
    // ------------------------- Private Datas --------------------------------
  private:
    
    // ------------------------- Internals ------------------------------------
  private:
    typename NumberTraits<T>::IsUnsigned myIsUnsigned;

  }; // end of concept CUnsignedNumber
}
} // namespace DGtal

                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CUnsignedNumber_h

#undef CUnsignedNumber_RECURSES
#endif // else defined(CUnsignedNumber_RECURSES)
