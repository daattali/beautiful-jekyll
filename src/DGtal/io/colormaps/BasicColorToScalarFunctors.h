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
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/10/15
 *
 * Header file for module ColorToScalarFunctors.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ColorToScalarFunctors_RECURSES)
#error Recursive header files inclusion detected in ColorToScalarFunctors.h
#else // defined(ColorToScalarFunctors_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ColorToScalarFunctors_RECURSES

#if !defined ColorToScalarFunctors_h
/** Prevents repeated inclusion of headers. */
#define ColorToScalarFunctors_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
    /** 
     * Basic color to scalar functor which returns the red channel.
     * 
     * 
     */
    struct RedChannel 
    {
      inline
      unsigned char operator() (const Color &aCol) const
      {
        return aCol.red(); 
      }
    };

    /** 
     * Basic color to scalar functor which returns the blue channel.
     * 
     * 
     */
    struct BlueChannel 
    {
      inline
      unsigned char operator() (const Color &aCol) const
      {
        return aCol.blue(); 
      }
    };

    /** 
     * Basic color to scalar functor which returns the Green channel.
     * 
     * 
     */
    struct GreenChannel 
    {
      inline
      unsigned char operator() (const Color &aCol) const
      {
        return aCol.green(); 
      }
    };

    /** 
     * Basic color to scalar functor which returns the mean of the three
     * channel values.
     * 
     */
    struct MeanChannels 
    {
      inline
      unsigned char operator() (const Color &aCol) const
      {
        return static_cast<unsigned char>(  ((int)aCol.green() + (int)aCol.blue() + (int)aCol.red()) / 3); 
      }
    };

    /** 
     * Basic color to scalar functor which returns the code of the RGB color (DGtal_uint32 casted into TValue) .
     * 
     */
    template<typename TValue>
    struct ColorRGBEncoder
    {
      typedef TValue Value;
      
      inline
      Value operator() (const Color &aCol) const
      {
        return static_cast<Value> (aCol.getRGB()); 
      }
    };
    
  } //namespace functors
} // namespace DGtal

  //                                                                           //
  ///////////////////////////////////////////////////////////////////////////////

#endif // !defined ColorToScalarFunctors_h

#undef ColorToScalarFunctors_RECURSES
#endif // else defined(ColorToScalarFunctors_RECURSES)
