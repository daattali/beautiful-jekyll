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
 * @file   Style2DFactory.h
 * @author Martial Tola <http://liris.cnrs.fr/martial.tola/>
 * @date   lundi 24 octobre 2011
 *
 * @brief
 *
 * Header file for module Style2DFactory
 *
 * This file is part of the DGtal library.
 */

#if defined(Style2DFactory_RECURSES)
#error Recursive header files inclusion detected in Style2DFactory.h
#else // defined(Style2DFactory_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Style2DFactory_RECURSES

#if !defined Style2DFactory_h
/** Prevents repeated inclusion of headers. */
#define Style2DFactory_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions

#include "DGtal/math/AngleLinearMinimizer.h"
#include "DGtal/geometry/curves/ArithmeticalDSS.h"
#include "DGtal/geometry/curves/ArithmeticalDSSComputer.h"
#include "DGtal/geometry/curves/AlphaThickSegmentComputer.h"
#include "DGtal/shapes/fromPoints/CircleFrom2Points.h"
#include "DGtal/shapes/fromPoints/CircleFrom3Points.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/geometry/curves/FP.h"
#include "DGtal/geometry/curves/FreemanChain.h"
#include "DGtal/geometry/curves/StabbingLineComputer.h"
#include "DGtal/geometry/curves/FrechetShortcut.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/images/ImageContainerByHashTree.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/KhalimskyPreSpaceND.h"
#include "DGtal/topology/Object.h"
#include "DGtal/topology/CanonicSCellEmbedder.h"
#include "DGtal/topology/CubicalComplex.h"
#include "DGtal/kernel/PointVector.h"
#include "DGtal/geometry/tools/Preimage2D.h"
#include "DGtal/shapes/fromPoints/StraightLineFrom2Points.h"
#include "DGtal/arithmetic/LatticePolytope2D.h"
#include "DGtal/dec/VectorField.h"
#include "DGtal/dec/KForm.h"
#include "DGtal/dec/DiscreteExteriorCalculus.h"
#include "DGtal/io/colormaps/GradientColorMap.h"
#include "DGtal/io/colormaps/HueShadeColorMap.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal {

  struct Style2DFactory{

  static void draw( DGtal::Board2D & aBoard, DGtal::DrawableWithBoard2D *style )
  {
      style->setStyle(aBoard);
   }
 };

}

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions/methods
#include "DGtal/io/Style2DFactory.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Style2DFactory_h

#undef Style2DFactory_RECURSES
#endif // else defined(Style2DFactory_RECURSES)
