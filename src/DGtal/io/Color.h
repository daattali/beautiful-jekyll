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
 * @file Color.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 * 
 * @date 2011/07/17
 *
 * Header file for module Color.cpp
 *
 * This file is part of the DGtal library.
 * Backport from Color of LibBoard library :http://libboard.sourceforge.net
 */

#if defined(Color_RECURSES)
#error Recursive header files inclusion detected in Color.h
#else // defined(Color_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Color_RECURSES

#if !defined Color_h
/** Prevents repeated inclusion of headers. */
#define Color_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include <boost/lexical_cast.hpp>
#include <algorithm>  
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class Color
  /**
   * Description of class 'Color' <p>
   * 
   * @brief Structure representing an RGB triple with alpha component.
   *
   * @note if compilation flag COLOR_WITH_ALPHA_ARITH is set, then the
   * arithmetical operations on colors also consider the
   * alpha-channel. Otherwise, the alpha channel is not changed when
   * summing up to colors for instance.
   *
   */
  class Color
  {
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Destructor.
     */
    ~Color();

    // ----------------------- Interface --------------------------------------
  public:

    /**
     * Constructor.
     *
     * @param aRgb an unsigned int representing the color.
     * @param aAlpha color transparency (default value =255);
     */
    
    Color( const unsigned int aRgb,
           unsigned char aAlpha = 255 );

    /**
     * Copy Constructor.
     *
     * @param aColor the color to copy.
     */
    
    Color( const Color &aColor ):
      myRed(aColor.myRed),myGreen(aColor.myGreen),
      myBlue(aColor.myBlue), myAlpha(aColor.myAlpha)
    {}

    /**
     * Constructor from R, G, B and Alpha parameter.
     *
     * @param aRedValue  red component
     * @param aGreenValue green component
     * @param aBlueValue blue component
     * @param aAlphaValue color transparency.
     */
    
    
    Color( const unsigned char aRedValue,
           const unsigned char  aGreenValue,
           const unsigned char  aBlueValue,
           const unsigned char aAlphaValue = 255 )
      : myRed(aRedValue),myGreen(aGreenValue),myBlue(aBlueValue),myAlpha(aAlphaValue) { }
    

    /**
     * Constructor from gray scale value.
     *
     * @param aGrayValue the color gray value.
     * @param aAlphaValue color transparency (default value =255);.
     */
    
    Color( unsigned char aGrayValue,
           unsigned char aAlphaValue = 255 )
      : myRed(aGrayValue),myGreen(aGrayValue), myBlue(aGrayValue), myAlpha(aAlphaValue) { }


    /**
     * Default Constructor.
     *
     */
    
    Color( )
      : myRed(0),myGreen(0),myBlue(0), myAlpha(255)
    {
    }
    
    Color& setRGBi( const unsigned char aRedValue,
		    const unsigned char aGreenValue,
		    const unsigned char aBlueValue,
		    const unsigned char aAlphaValue );

    /**
     * Set the color parameter from an unsigned integer coding each canal.
     *
     * @param aRGBA an unsigned integer on 32 bits(DGtal::unit32_t)
     * representing the color coded with 4 bits on each components R, G, B
     * and Alpha value.
     * @return a reference on the itself.
     *
     */
    
    Color& setRGBA( DGtal::uint32_t aRGBA );
    
    void red( const unsigned char aRedValue );

    void green( const unsigned char aGreenValue );
    
    void blue( const unsigned char aBlueValue );

    void alpha( const unsigned char aAlphaValue );
    
    unsigned char red() const ;

    unsigned char green() const ;
    
    unsigned char blue() const ;

    unsigned char alpha() const ;


    /**
     * @return the unsigned integer ( DGtal::uint32_t ) coding  each
     * R, G, B canal on 8 bits starting from least significant bit.
     **/
    
    DGtal::uint32_t getRGB() const;

    /**
     * @return the unsigned integer ( DGtal::uint32_t ) coding  each
     * R, G, B, A canal on 8 bits starting from least significant bit.
     **/
        
    DGtal::uint32_t getRGBA() const;


    bool valid() const;


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

    

    Color & setRGBf( float red, 
		     float green,
		     float blue,
		     float alpha = 1.0 );
  
    bool operator==( const Color & aColor ) const;

    bool operator!=( const Color & aColor ) const;

    bool operator<( const Color & aColor ) const;

    
    /**
     * Addition operator with assignement.
     *
     * @note returned components are clamped to [0,255] interval. 
     *
     * @param v is the Color that gets added to @a *this.
     * @return a reference on 'this'.
     */
    Color & operator+= ( const Color & v )
    {
      this->myRed = clamp((int)this->myRed + (int)v.myRed);
      this->myBlue =  clamp((int)this->myBlue + (int)v.myBlue);
      this->myGreen =  clamp((int)this->myGreen + (int)v.myGreen);
#ifdef COLOR_WITH_ALPHA_ARITH
      this->myAlpha =  clamp((int)this->myAlpha + (int)v.myAlpha);
#endif
      return *this;
    }

    /**
     * Addition operator.
     *
     * @note returned components are clamped to [0,255] interval. 
     *
     *
     * @param v is the Color that gets added to @a *this.
     * @return a new Point that is the addition of 'this' to [v].
     */
    Color operator+ ( const Color & v ) const
    {
      Color c;
      c.myRed = clamp((int)this->myRed + (int)v.myRed);
      c.myBlue =clamp((int)this->myBlue + (int)v.myBlue);
      c.myGreen = clamp((int)this->myGreen + (int)v.myGreen);
#ifdef COLOR_WITH_ALPHA_ARITH
      c.myAlpha = clamp((int)this->myAlpha + (int)v.myAlpha);
#else
      c.myAlpha = this->myAlpha ;
#endif
  return c;
    }

    /**
     * Substraction operator with assignement.
     *
     * @note returned components are clamped to [0,255] interval. 
     *
     *
     * @param v is the Point that gets substracted to  *this.
     * @return a reference on 'this'.
     */
    Color & operator-= ( const Color & v )
    {
      this->myRed = clamp((int)this->myRed - (int)v.myRed);
      this->myBlue = clamp((int)this->myBlue - (int)v.myBlue);
      this->myGreen = clamp((int)this->myGreen - (int)v.myGreen);
#ifdef COLOR_WITH_ALPHA_ARITH
      this->myAlpha = clamp((int)this->myAlpha - (int)v.myAlpha);
#endif
      return *this;
    }

    /**
     * Substraction operator.
     *
     * @note returned components are clamped to [0,255] interval. 
     *
     * @param v is the Color that gets substacted to @a *this.
     * @return a new Point that is the subtraction 'this'-[v].
     */
    Color operator- ( const Color & v ) const
    {
      Color c;
      c.myRed = clamp((int)this->myRed - (int)v.myRed);
      c.myBlue = clamp((int)this->myBlue - (int)v.myBlue);
      c.myGreen = clamp((int)this->myGreen - (int)v.myGreen);
#ifdef COLOR_WITH_ALPHA_ARITH
      c.myAlpha = clamp((int)this->myAlpha - (int)v.myAlpha);
#else
      c.myAlpha = this->myAlpha ;
#endif
      return c;
    }

    /** 
     * Multiplication by a scalar (component-wise)
     *
     * @note returned components are clamped to [0,255] interval. 
     *
     * 
     * @param coeff the scalar
     * 
     * @return the scaled color
     */
    Color &operator *= ( const double coeff)
    {
      this->myRed = clamp((double)this->myRed*coeff);
      this->myBlue = clamp((double)this->myBlue*coeff);
      this->myGreen = clamp((double)this->myGreen*coeff);
#ifdef COLOR_WITH_ALPHA_ARITH
      this->myAlpha =  clamp((double)this->myAlpha*coeff);
#endif
      return *this;
    }

    /** 
     * Multiplication by a scalar (component-wise)
     *
     * @note returned components are clamped to [0,255] interval. 
     *
     * @param coeff the scalar.
     * @return a scaled color
     */
    Color operator * ( const double coeff) const
    {
      Color c;
      c.myRed = clamp((double)this->myRed*coeff);
      c.myBlue = clamp((double)this->myBlue*coeff);
      c.myGreen = clamp((double)this->myGreen*coeff);
#ifdef COLOR_WITH_ALPHA_ARITH
      c.myAlpha =  clamp((double)this->myAlpha*coeff);
#else
      c.myAlpha  = this->myAlpha;
#endif
      return c;
    }
   
    /**
     * Assignement Operator
     *
     * @param pv the object to copy.
     * @return a reference on 'this'.
     */
    Color & operator= ( const Color & pv )
    {
      this->myRed = pv.myRed;
      this->myGreen = pv.myGreen;
      this->myBlue = pv.myBlue;
      this->myAlpha = pv.myAlpha;
      return *this;
    }
    

    
    void flushPostscript( std::ostream & ) const;

    std::string svg() const;

    /** 
     * Return a an SVG parameter string for the opacity value.
     * 
     * @param aPrefix A prefix string to be appended to the returned 
     * string if not empty.
     * 
     * @return An empty string if alpha == 255, otherwise the string \<prefix\>-opacity="<alpha-value>".
     */
    std::string svgAlpha( const char * aPrefix ) const;

    std::string postscript() const;

    /** 
     * Return a string representation of the color usable in TikZ commands.
     * Use the corresponding named color (or a mixture of a named color and black)
     * for predefined colors. Use a mixture of red, green and blue for general
     * colors.
     * 
     * @return a string representation of the color usable in TikZ commands.
     */
    std::string tikz() const;
  
    static const Color None;
    static const Color Black;
    static const Color Gray;
    static const Color White;
    static const Color Red;
    static const Color Green;
    static const Color Lime;
    static const Color Blue;
    static const Color Cyan;
    static const Color Magenta;
    static const Color Yellow;
    static const Color Silver;
    static const Color Purple;
    static const Color Navy;
    static const Color Aqua;

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  private:
    unsigned char myRed;      /**< The red component. */
    unsigned char myGreen;    /**< The green component. */
    unsigned char myBlue;      /**< The blue component. */
    unsigned char myAlpha;    /**< The opacity. */
    // ------------------------- Hidden services ------------------------------
  protected:


  private:

    /** 
     * Clamp an int to [0,255]
     * 
     * @param [in] value the value to clamp
     * 
     * @return the clamped value
     */
    unsigned char clamp(const double value)  const
    {
      return static_cast<unsigned char>(std::max( std::min(value, 255.0), 0.0));
    }



    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Color



  /**
     External multiplication operator with a scalar number

     @param coeff is the factor \a Color is multiplied by.
     @param aColor is the vector that is multiplied by the factor \a coef.

     @return a new Vector that is the multiplication of \a aVector by
     \a coeff.
  */
  Color
  operator*( const double coeff,
	     const Color &aColor );
 
 

  /**
   * Overloads 'operator<<' for displaying objects of class 'Color'.
   * @param out the output stream where the object is written.
   * @param aColor the object of class 'Color' to write.
   * @return the output stream after the writing.
   */
  std::ostream&
  operator<< ( std::ostream & out, const Color & aColor );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods 
#include "DGtal/io/Color.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Color_h

#undef Color_RECURSES
#endif // else defined(Color_RECURSES)
