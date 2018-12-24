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
 * @file DrawWithBoard3DTo2DModifier.h
 * @author Aline Martin
 *
 * @date 2013/07/02
 *
 * Header file for module DrawWithBoard3DTo2DModifier.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DrawWithBoard3DTo2DModifier_RECURSES)
#error Recursive header files inclusion detected in DrawWithBoard3DTo2DModifier.h
#else // defined(DrawWithBoard3DTo2DModifier_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DrawWithBoard3DTo2DModifier_RECURSES

#if !defined DrawWithBoard3DTo2DModifier_h
/** Prevents repeated inclusion of headers. */
#define DrawWithBoard3DTo2DModifier_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Alias.h"
#include "DGtal/base/ConstAlias.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/base/CountedPtr.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/io/DrawWithDisplay3DModifier.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/**
 *@brief Base class specifying the methods for classes which intend to
 * modify a Viewer3D stream.
 *
 */
struct DrawWithBoard3DTo2DModifier : public DrawableWithDisplay3D{
  std::string className() const;
};


#ifndef DrawWithViewer3DModifier_h

/**
   * @brief  CameraPosition class to set camera position.
   */
struct CameraPosition : public DrawWithBoard3DTo2DModifier
{
  /**
     * Constructor.
     *
     * @param x x position.
     * @param y y position.
     * @param z z position.
     */
  CameraPosition( const double x, const double y, const double z ):eyex(x), eyey(y), eyez(z)
  {
  }

  double eyex, eyey, eyez;
};


/**
   * @brief CameraDirection class to set camera direction.
   */
struct CameraDirection : public DrawWithBoard3DTo2DModifier
{
  /**
     * Constructor.
     *
     * @param x x direction.
     * @param y y direction.
     * @param z z direction.
     */
  CameraDirection( const double x, const double y, const double z ): dirx(x), diry(y), dirz(z)
  {
  }

  double dirx, diry, dirz;
};


/**
   * @brief CameraUpVector class to set camera up-vector.
   */
struct CameraUpVector : public DrawWithBoard3DTo2DModifier
{
  /**
     * Constructor.
     *
     * @param x x coordinate of up-vector.
     * @param y y coordinate of up-vector.
     * @param z z coordinate of up-vector.
     */
  CameraUpVector( const double x, const double y, const double z ): upx(x), upy(y), upz(z)
  {
    upx=x; upy=y; upz=z;
  }

  double upx, upy, upz;
};



/**
   * @brief CameraZNearFar class to set near and far distance.
   */
struct CameraZNearFar : public DrawWithBoard3DTo2DModifier
{
  /**
     * Constructor.
     *
     * @param near near distance.
     * @param far far distance.
     */
  CameraZNearFar( const double near, const double far ): ZNear(near), ZFar(far)
  {
  }

  double ZNear, ZFar;
};
#endif


} // namespace DGtal




///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/boards/DrawWithBoard3DTo2DModifier.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DrawWithBoard3DTo2DModifier_h

#undef DrawWithBoard3DTo2DModifier_RECURSES
#endif // else defined(DrawWithBoard3DTo2DModifier_RECURSES)
