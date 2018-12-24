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
 * @file CColorMap.h
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/30
 *
 * Header file for concept CColorMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(CColorMap_RECURSES)
#error Recursive header files inclusion detected in CColorMap.h
#else // defined(CColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define CColorMap_RECURSES

#if !defined CColorMap_h
/** Prevents repeated inclusion of headers. */
#define CColorMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "boost/concept_check.hpp"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/base/CLabel.h"
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // class CColorMap
  /**
Description of \b concept \b 'CColorMap' <p>
@ingroup Concepts
    
@brief Aim: Defines the concept describing a color map. A color map converts
    a value within a given range into an RGB triple.
    
### Refinement of
   
### Associated types :
   
### Notation
    - \a X : A type that is a model of CColorMap
    - \a x, \a y  : Object of type X
   
### Definitions
   
### Valid expressions and semantics


| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
|Construction | CMap<Value> cmap(min, max); | min and max are of the same Value | | | | | |
|Obtain a color | color = cmap(value) | value is a Value | DGtal::Color | min  &le; value &le; max | Returns a color computed after the position of \em value \em within the range [min,max] | | |

### Invariants
   
#### Models
           GradientColorMap
           HueShadeColorMap
           ColorBrightnessColorMap 
           GrayScaleColorMap
           RandomColorMap
### Notes
   */
  template <typename CMap>
  struct CColorMap
  {
    // ----------------------- Concept checks ------------------------------
  public:
    
    typedef typename CMap::Value Value;
    
    BOOST_CONCEPT_ASSERT(( CLabel<Value> ));
    
    BOOST_CONCEPT_USAGE( CColorMap )
    {
      CMap myCMap( myMin, myMax );
      // operator() exists, takes a Value, and returns a LibBoard::Color.
      ConceptUtils::sameType( myColor, myCMap.operator()( myValue ) );
    }
    
    // ------------------------- Private Datas --------------------------------
  private:
    
    // ------------------------- Internals ------------------------------------
  private:
    Color myColor;
    Value myMin, myMax, myValue;    
  }; // end of concept CColorMap
  }//namespace concepts
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CColorMap_h

#undef CColorMap_RECURSES
#endif // else defined(CColorMap_RECURSES)
