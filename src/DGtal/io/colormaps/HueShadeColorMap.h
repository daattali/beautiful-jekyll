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
 * @file HueShadeColorMap.h
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/19
 *
 * Header file for module HueShadeColorMap.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(HueShadeColorMap_RECURSES)
#error Recursive header files inclusion detected in HueShadeColorMap.h
#else // defined(HueShadeColorMap_RECURSES)
/** Prevents recursive inclusion of headers. */
#define HueShadeColorMap_RECURSES

#if !defined HueShadeColorMap_h
/** Prevents repeated inclusion of headers. */
#define HueShadeColorMap_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "Board/Board.h"
#include "DGtal/io/Color.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class HueShadeColorMap
  /**
   * Description of template class 'HueShadeColorMap' <p>
   *
   * @brief Aim: This class template may be used to (linearly) convert scalar
   * values in a given range into a color in a \em cyclic hue shade
   * colormap, maybe aka rainbow color map. This color map is suitable, for
   * example, to colorize distance functions. By default, only one hue cycle is
   * used.
   * 
   * The HueShadeColorMap can be used either as a functor object (the value
   * range is given at the object's construction) which converts a value  into a
   * Color structure, or it can be used through a static method taking
   * both the range and the value as parameters.
   *
   * The code below shows a possible use of this class.
   * @code
   * #include "DGtal/io/Color.h"
   * #include "HueShadeColorMap.h"
   * // ...
   * {
   *   HueShadeColorMap<float>    hueShade(0.0f,1.0f);
   *   HueShadeColorMap<float,10> hueShadeBis(0.0f,1.0f);     // Ten cycles.
   *   HueShadeColorMap<float>    hueShadeTer(0.0f,1.0f,10);  // Idem.
   *   Color red = hueShade(1.0f);
   *   Color lightBlue1 = hueShade(0.5f);
   *   // Or, equivalently:
   *   Color lightBlue2 = HueShadeColorMap<float>::getColor(0.0f,1.0f,0.5f);
   * }
   * @endcode
   * 
   * @tparam PValue The type of the range values.
   * @tparam DefaultCycles The default number of cycles (used as a default
   *         parameter by the constructor).
   */
  template <typename PValue, int DefaultCycles = 1 >
    class HueShadeColorMap
    {

    public:
    
    typedef PValue Value;

    // ----------------------- Standard services ------------------------------
    public:

    /** 
     * Constructor.
     * 
     * @param min The lower bound of the value range.
     * @param max The upper bound of the value range.
     * @param cycles The number of cycles in the colormap.
     */
    HueShadeColorMap( const PValue & min,
          const PValue & max,
          const unsigned int cycles = DefaultCycles );
    
    /** 
     * Computes the color associated with a value in a given range.
     * 
     * @param value A value within the value range.
     * @return A color whose hue linearly depends on the 
     * position of [value] within the current range.
     */
    Color operator()( const PValue & value ) const;
      
    /**
     * Destructor.
     */
    ~HueShadeColorMap();

    /**
     * Copy constructor.
     * @param other the object to clone.
     */
    HueShadeColorMap ( const HueShadeColorMap & other );

    /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    HueShadeColorMap & operator= ( const HueShadeColorMap & other );

    // ----------------------- Interface --------------------------------------
    public:

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const;

    /** 
     * Returns the lower bound of the value range.
     *
     * @return The lower bound of the value range.
     */
    const PValue & min() const;

    /** 
     * Returns the upper bound of the value range.
     *
     * @return The upper bound of the value range.
     */
    const PValue & max() const;


    /** 
     * Sets the number of cycles of hue shade.
     * 
     * @param cycles Number of cycles.
     */
    void setCycles( int cycles );

    // ----------------------- Static methods ---------------------------------


    /** 
     * Computes the color associated with a value in a given range.
     * 
     * @param cycles The number of (rainbow) cycles.
     * @param min The lower bound of the value range.  
     * @param max The upper bound of the value range.
     * @param value A value within the value range.
     * @return A color whose hue linearly depends on the 
     * position of [value] within the range [min]..[max]. 
     */
    static Color getColor( const unsigned int cycles,
             const PValue & min,
             const PValue & max,
             const PValue & value );
    
    // ------------------------- Protected Datas ------------------------------
    private:

    // ------------------------- Private Datas --------------------------------
    private:

    // ------------------------- Hidden services ------------------------------
    protected:

    PValue myMin;    /**< The lower bound of the value range.  */
    PValue myMax;           /**< The lower bound of the value range.  */
    unsigned int myCycles;  /**< The number of cycles in the color map. */
    
    /**
     * Constructor.
     * Forbidden by default (protected to avoid g++ warnings).
     */
    HueShadeColorMap();

    // ------------------------- Internals ------------------------------------
    private:

    /** 
     * Converts a color from the HSV (Hue,Saturation,Value) space to the RGB
     * space.
     * 
     * @param r The red component (out).
     * @param g The green component (out).
     * @param b The blue component (out).
     * @param h The hue of the color in [0..360)
     * @param s The saturation of the color in [0..1].
     * @param v The value of the color in [0..1].
     */
    static void HSVtoRGB(double &r, double &g, double &b,
       double h, const double s, const double v);


    }; // end of class HueShadeColorMap


  /**
   * Overloads 'operator<<' for displaying objects of class 'HueShadeColorMap'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'HueShadeColorMap' to write.
   * @return the output stream after the writing.
   */
  template <typename PValue, int DefaultCycles >
    std::ostream&
    operator<< ( std::ostream & out, const HueShadeColorMap<PValue,DefaultCycles> & object );
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/colormaps/HueShadeColorMap.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined HueShadeColorMap_h

#undef HueShadeColorMap_RECURSES
#endif // else defined(HueShadeColorMap_RECURSES)
