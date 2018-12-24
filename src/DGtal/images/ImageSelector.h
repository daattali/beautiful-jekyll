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
 * @file ImageSelector.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/14
 *
 * Header file for module ImageSelector.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageSelector_RECURSES)
#error Recursive header files inclusion detected in ImageSelector.h
#else // defined(ImageSelector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageSelector_RECURSES

#if !defined ImageSelector_h
/** Prevents repeated inclusion of headers. */
#define ImageSelector_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CLabel.h"
#include "DGtal/images/ImageContainerBySTLMap.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerByHashTree.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  enum ImageIterability {  HIGH_ITER_IMAGE = 0 , LOW_ITER_I = 1};
  enum ImageBelongTestability {  HIGH_BEL_I = 0, LOW_BEL_I = 2 };
  enum ImageSpecificContainer { NORMAL_CONTAINER_I = 0, VTKIMAGEDATA_CONTAINER_I = 4 };

  /////////////////////////////////////////////////////////////////////////////
  // template class ImageSelector
  /**
   * Description of template class 'ImageSelector' <p>
   * \brief Aim:  Automatically defines an adequate image type according
   * to the hints given by the user.  
   */
  template <typename Domain,  typename Value, int Preferences = 0 >
  struct ImageSelector
  {

    BOOST_CONCEPT_ASSERT((concepts::CLabel<Value>));

    // ----------------------- Local types ------------------------------
    /**
     * Adequate digital set representation for the given preferences.
     */
    typedef ImageContainerBySTLVector<Domain,Value> Type;
    
  };
} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images//ImageSelector.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageSelector_h

#undef ImageSelector_RECURSES
#endif // else defined(ImageSelector_RECURSES)
