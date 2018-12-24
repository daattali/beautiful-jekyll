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
 * @file SimpleDistanceColorMap.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * LIRIS (CNRS, UMR 5205), Université de Lyon, France
 *
 * @date 2011/07/18
 *
 * Header file for module SimpleDistanceColorMap
 *
 * This file is part of the DGtal library.
 */

#if defined(SimpleDistanceColorMap_RECURSES)
#error Recursive header files inclusion detected in SimpleDistanceColorMap.h
#else // defined(SimpleDistanceColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SimpleDistanceColorMap_RECURSES

#if !defined SimpleDistanceColorMap_h
/** Prevents repeated inclusion of headers. */
#define SimpleDistanceColorMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/io/Color.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  
  /////////////////////////////////////////////////////////////////////////////
  // class SimpleDistanceColorMap
  /**
   * Description of class 'SimpleDistanceColorMap' <p>
   * \brief Aim: simple blue to red colormap for distance information for instance.
   *
   * Color formula from a fragment shader in https://github.com/dgpdec/course.
   *
   * @tparam TValue the value type
   */
  
  template <typename TValue>
  class SimpleDistanceColorMap
  {
    // ----------------------- Standard services ------------------------------
  public:
    
    ///Value type
    typedef TValue Value;
    
    /**
     * Copy constructor.
     * @param[in] other the object to clone.
     * Forbidden by default.
     */
    SimpleDistanceColorMap ( const SimpleDistanceColorMap & other );
    
    /**
     * Assignment.
     * @param [in] anOther the object to copy.
     * @return a reference on 'this'.
     * Forbidden by default.
     */
    SimpleDistanceColorMap & operator= ( const SimpleDistanceColorMap & anOther );
    
    
    /**
     * Constructor from two min and max values.
     *
     * @param[in] amin the minimum value of the range.
     * @param[in] amax the maximum value of the range.
     * @param[in] withTick if true, white ticks are displayed (default true).
     **/
    SimpleDistanceColorMap(const Value & amin,
                           const Value & amax,
                           const bool withTick=true):
    myMin(amin), myMax(amax), myTick(withTick)
    {}
    
    
    
    /**
     * Computes the color associated with a value.
     *
     * @param[in] aValue A value within the value range.
     * @return A  color.
     */
    Color operator()( const Value & aValue ) const
    {
      const double val = (NumberTraits<Value>::castToDouble(aValue) - NumberTraits<Value>::castToDouble(myMin))/
      (NumberTraits<Value>::castToDouble(myMax) - NumberTraits<Value>::castToDouble(myMin));
      const double d = 1. - val;
      double r = (1. - d*d) * .8;
      double g = (1. - (2. * (d - .5)) * (2. * (d - .5))) * .7;
      double b = (1. - (1. - d) * (1. - d));
      
      // lines
      if (myTick)
      {
        double h = val;
        h = h * 30.;
        h = h - floor( h );
        h = (1. / (1. + exp(-100.*(h - .55)))) + (1. / (1. + exp(-100.*(-h + .45))));
        h = 1. - h;
        r = h + (1. -h)*r;
        g = h + (1. - h)*g;
        b = h + (1. - h)*b;
      }
      
      return Color(static_cast<unsigned char>(r*255),
                   static_cast<unsigned char>(g*255),
                   static_cast<unsigned char>(b*255));
    }
    
    
    
    // ----------------------- Interface --------------------------------------
  public:
    
    /**
     * Writes/Displays the object on an output stream.
     * @param[in,out] out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;
    
    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const { return true;}
    
    /**
     * Returns the lower bound of the value range.
     *
     * @return The lower bound of the value range.
     */
    const Value & min() const
    {
      return myMin;
    }
    
    /**
     * Returns the upper bound of the value range.
     *
     * @return The upper bound of the value range.
     */
    const Value & max() const
    {
      return myMax;
    }

    // ------------------------- Protected Datas ------------------------------
  protected:
    
    ///Min value
    Value myMin;
    
    ///Max value
    Value myMax;
    
    ///Boolean to activate/desactivate ticks
    bool myTick;
    
    // ------------------------- Hidden services ------------------------------
  protected:
    
    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    SimpleDistanceColorMap();
 
  
  }; // end of class SimpleDistanceColorMap
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined SimpleDistanceColorMap

#undef SimpleDistanceColorMap_RECURSES
#endif // else defined(SimpleDistanceColorMap_RECURSES)
