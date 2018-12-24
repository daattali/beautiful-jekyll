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
 * @file CIntegralNumber.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/02
 *
 * Header file for concept CIntegralNumber.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CIntegralNumber_RECURSES)
#error Recursive header files inclusion detected in CIntegralNumber.h
#else // defined(CIntegralNumber_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CIntegralNumber_RECURSES

#if !defined CIntegralNumber_h
/** Prevents repeated inclusion of headers. */
#define CIntegralNumber_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
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
  // class CIntegralNumber
  /**
Description of \b concept '\b CIntegralNumber' <p>
     @ingroup Concepts

@brief Aim: Concept checking for Integral Numbers. Models of this
     concept should be listed in NumberTraits class and should have
     the isIntegral property.
     
 ### Refinement of 
   
    - CQuantity<T>
 
 ### Associated types 
    
 ### Notation
     - \a X : A type that is a model of CIntegralNumber
     - \a x, \a  y  : Object of type X
    
 ### Definitions
    
 ### Valid expressions and semantics
 

Name | Expression |  Type requirements | Return type| Precondition | Semantics | Postcondition | Complexity 
-----|------------|--------------------|------------|--------------|-----------|---------------|-----------
\a X should be tagged \b true in \a NumberTraits for \a IsIntegral. | typename NumberTraits<X>::IsIntegral | TagTrue | | | | | |
    
    
 ### Invariants

    
 ### Models

BigInteger,  short, int, long long, uint32_t, int16_t, int32_t, int64_t, ...

 ### Notes

@tparam T the type that is checked. T should be a model of
     CBoundedInteger.
    
   */
  template <typename T>
  struct CIntegralNumber: CQuantity<T>
  {
    // ----------------------- Concept checks ------------------------------
  public:
    BOOST_CONCEPT_USAGE(CIntegralNumber)
    {
      // Will compile iff Integral.
      ConceptUtils::checkTrue( myIsIntegral );
    }
    
    // ------------------------- Internals ------------------------------------
  private:
    typename NumberTraits<T>::IsIntegral myIsIntegral;

  }; // end of concept CIntegralNumber
  }  
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CIntegralNumber_h

#undef CIntegralNumber_RECURSES
#endif // else defined(CIntegralNumber_RECURSES)
