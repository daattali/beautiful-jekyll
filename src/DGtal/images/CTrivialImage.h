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
 * @file CTrivialImage.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/08
 *
 * This file is part of the DGtal library.
 */

#if defined(CConstImageRECURSES)
#error Recursive header files inclusion detected in CTrivialImage.h
#else // defined(CConstImageRECURSES)
/** Prevents recursive inclusion of headers. */
#define CConstImageRECURSES

#if !defined CTrivialImage_h
/** Prevents repeated inclusion of headers. */
#define CTrivialImage_h

#include <boost/concept_check.hpp>
#include <boost/concept/assert.hpp>
#include <boost/concept/requires.hpp>

#include "DGtal/images/CTrivialConstImage.h"

namespace DGtal
{
  namespace concepts
  {
  /////////////////////////////////////////////////////////////////////////////
  // struct CTrivialImage
/**
 * Description of \b concept '\b CTrivialImage' <p>
 *
 * @ingroup Concepts
 * @brief Aim: Defines the concept describing an image without extra ranges, 
 * which is a refinement of CTrivialConstImage. 
 *
###  Refinement of
  - CTrivialConstImage
###  Associated types 
  
###  Notation
 - \e X : A type that is a model of CTrivialImage
 - \e x, \e y  : Object of type X
 - \e p, \e v : Objects of type Point and Value
   
###  Definitions
   
###  Valid expressions and semantics
   

| Name          | Expression | Type requirements   | Return type | Precondition     | Semantics | Post condition | Complexity |
|---------------|------------|---------------------|-------------|------------------|-----------|----------------|------------|
| Set value | x.setValue(p,v) | | | | set a given value v to a given point p | | |   

   
###  Invariants
   
###  Models
ImageContainerBySTLVector, ImageContainerBySTLMap, ImageContainerByITKImage, ImageContainerByHashTree
   
   */

  template <typename I>
  struct CTrivialImage: CTrivialConstImage<I>
  {

   public:

    BOOST_CONCEPT_USAGE(CTrivialImage)
    {
      myI.setValue( myPoint, myValue ); 
    }

   private:
    I myI;
    typename I::Point myPoint; 
    typename I::Value myValue; 
    
  };
  }
} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined CTrivialImage_h

#undef CConstImageRECURSES
#endif // else defined(CConstImageRECURSES)
