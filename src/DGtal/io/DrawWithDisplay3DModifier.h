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
 * @file DrawWithDisplay3DModifier.h
 * @author Aline Martin
 *
 * @date 2013/07/02
 *
 * Header file for module DrawWithDisplay3DModifier.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DrawWithDisplay3DModifier_RECURSES)
#error Recursive header files inclusion detected in DrawWithDisplay3DModifier.h
#else // defined(DrawWithDisplay3DModifier_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DrawWithDisplay3DModifier_RECURSES

#if !defined DrawWithDisplay3DModifier_h
/** Prevents repeated inclusion of headers. */
#define DrawWithDisplay3DModifier_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/topology/KhalimskySpaceND.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/**
   *@brief Base class specifying the methods for classes which intend to
   * modify a Viewer3D stream.
   *
   */
struct DrawWithDisplay3DModifier
{
  std::string className() const;
};



/**
   * @brief Modifier class in a Display3D stream. Useful to choose your
   * own mode for a given class. Realizes the concept
   * CDrawableWithDisplay3D.
   */

struct SetMode3D : public DrawWithDisplay3DModifier
{
  /**
     * @param classname the name of the class to which the style is associated.
     *
     * @param mode the name of the new mode.
     */
  SetMode3D( std::string classname, std::string mode )
    : myClassname( classname ), myMode( mode )
  {}

  std::string myClassname;
  std::string myMode;
};




/**
   * @brief Modifier class in a Display3D stream. Useful to choose your own
   * style for a given class. Realizes the concept
   * CDrawableWithDisplay3D.
   */
struct CustomStyle3D : public DrawWithDisplay3DModifier
{
  /**
     * @param aClassname the name of the class to which the style is associated.
     *
     * @param style a pointer on a dynamically allocated style, which
     * is acquired by the class.
     */
  CustomStyle3D( std::string aClassname, DrawableWithDisplay3D* style ): myClassname( aClassname ), myStyle( style )
  {}

  std::string className() const;

  std::string myClassname;
  CountedPtr<DrawableWithDisplay3D> myStyle;
};




/**
   * Custom style class redefining the fill color and the
   * gl_LINE/gl_POINT color. You can use DGtal::Color with alpha
   * transparency value but you nedd to take into account the z-buffer
   * during the Open-GL based rendering.
   *
   \code
   Display3D display;
   display << CustomColors3D(Color(250, 0,0),Color(250, 0,0));
   ...
   \endcode
   * @see Display3D
   */
struct CustomColors3D : public DrawWithDisplay3DModifier
{
  Color myPenColor;
  Color myFillColor;

  /**
     * Constructor.
     *
     * @param penColor specifies the pen color.
     * @param fillColor specifies the fill color.
     */
  CustomColors3D( const Color & penColor,
                  const Color & fillColor )
    : myPenColor( penColor ), myFillColor( fillColor )
  {}


};




/**
   * @brief Class for adding a Clipping plane through the Viewer3D
   * stream. Realizes the concept CDrawableWithViewer3D.
   */

struct ClippingPlane : public DrawWithDisplay3DModifier
{
  /**
     *
     */
  ClippingPlane( double a, double b, double c, double d, bool drawPlane=true )
    : myA( a ), myB( b ), myC( c ), myD ( d ), myDrawPlane(drawPlane)
  {}

  double * getEquation();
  double myA;
  double myB;
  double myC;
  double myD;
  bool myDrawPlane;
};



/**
   * @brief class to modify the position and scale to construct better illustration mode.
   * @todo add a constructor to automatically define the shift and the scale according a given associated SCell.
   */
struct TransformedPrism : public DrawWithDisplay3DModifier
{
  /**
     * Constructor.
     *
     * @param aSurfel a DGtal::Z3i::SCell ( KhalimskySpaceND< 3, Integer > SCell ) .
     * @param aShift the shift distance (positive or negative).
     * @param aSizeFactor use to change the Prism size (1.0 initial size).
     */
  TransformedPrism( const DGtal::Z3i::SCell  & aSurfel,
                          double aShift, double aSizeFactor=1.0 ):mySurfel(aSurfel), myShift(aShift), mySizeFactor(aSizeFactor)
  {
  }


  /**
     * Constructor.
     *
     * @param aSurfel a DGtal::Z3i::SCell ( KhalimskySpaceND< 3, Integer > SCell ) .
     * @param aVoxel a  DGtal::Z3i::SCell represent the voxel for which the surfel is associated. It permits to determine automatically the shift parameter (the surfel is automatically shifted towards this voxel).
     * @param aShift the shift distance (positive or negative (default 0.05)).
     * @param aSizeFactor use to change the Prism size (default 0.75).
     */
  TransformedPrism( const DGtal::Z3i::SCell  & aSurfel,
                          const DGtal::Z3i::SCell  & aVoxel,
                          double aShift=0.05, double aSizeFactor=0.75  )
    : mySurfel(aSurfel), myShift(aShift), mySizeFactor(aSizeFactor)
  {
    auto const& preSurfel = aSurfel.preCell();
    auto const& preVoxel  = aVoxel.preCell();

    bool xodd = (preSurfel.coordinates[ 0 ] & 1 );
    bool yodd = (preSurfel.coordinates[ 1 ] & 1 );
    bool zodd = (preSurfel.coordinates[ 2 ] & 1 );
    if(!xodd )
    {
      myShift*= ((preVoxel.coordinates[ 0 ]-preSurfel.coordinates[ 0 ] <0)? -1.0: 1.0);
    }else if(!yodd )
    {
      myShift*=((preVoxel.coordinates[ 1 ]-preSurfel.coordinates[ 1 ] <0)? -1.0: 1.0);
    }else if(!zodd )
    {
      myShift*=((preVoxel.coordinates[ 2 ]-preSurfel.coordinates[ 2 ] <0)? -1.0: 1.0);
    }
  }

  ///@todo FIX this member
  DGtal::Z3i::SCell mySurfel;
  double myShift;
  double mySizeFactor;
};


  /**
   * This structure is used to set the "OpenGL name" (an integer
   * identifier) of the following display command(s).
   * You may use it like
   * \code
   * SCell surfel = ... ;
   * viewer << SetName3D( 100 );
   * viewer << surfel; // surfel is identified with name 100 when clicked.
   * \endcode
   */
  struct SetName3D : public DrawWithDisplay3DModifier {
    /// Sets the "OpenGL name" of future display command(s).
    /// @param aName any integer: an identifier for later selection or -1 for none.
    SetName3D( DGtal::int32_t aName = -1 ) : name( aName ) {}
    /// @return the class name as a string.
    std::string className() const { return "SetName3D"; }
    /// the "OpenGL name" for selection, or -1 for none.
    DGtal::int32_t name;
  };

  /**
   * This structure is used to pass callback functions to the
   * viewer. These callback functions are called when specific
   * graphical objects are selected by the user (@see SetName3D).
   */
  struct SetSelectCallback3D : public DrawWithDisplay3DModifier {
    /// The prototype for a callback function. It is called with a
    /// pointer to the viewer, the "OpenGL name" of the selected
    /// graphical element and a pointer toward the data that was given
    /// at construction of SetSelectCallback3D.
    typedef int (*CallbackFct)( void* viewer, DGtal::int32_t name, void* data );
    SetSelectCallback3D( CallbackFct f,
                         void* data,
                         DGtal::int32_t min = 0, DGtal::int32_t max = 0x7fffffff )
      : myFct( f ), myData( data ), myMin( min ), myMax( max ) {}
    /// @return the class name as a string.
    std::string className() const { return "SetSelectCallback3D"; }
    /// The callback function associated to the selection of an element.
    CallbackFct myFct;
    void* myData;
    DGtal::int32_t myMin;
    DGtal::int32_t myMax;
  };
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/DrawWithDisplay3DModifier.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DrawWithDisplay3DModifier_h

#undef DrawWithDisplay3DModifier_RECURSES
#endif // else defined(DrawWithDisplay3DModifier_RECURSES)
