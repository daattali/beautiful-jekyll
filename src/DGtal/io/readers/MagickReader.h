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
 * @file MagickReader.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/25
 *
 * Header file for module MagickReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MagickReader_RECURSES)
#error Recursive header files inclusion detected in MagickReader.h
#else // defined(MagickReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MagickReader_RECURSES

#if !defined MagickReader_h
/** Prevents repeated inclusion of headers. */
#define MagickReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include <cstdio>

#if defined(WITH_MAGICK)
// Specific inclusion method to fix warning with GraphicsMagic 1.3.31 and Clang.
// The warning comes from two "diagnostic pop" with missing corresponding push.
// "MagickLibAddendum" is defined in ImageMagick since 9 years but not in GraphicsMagic.
#  if !defined(MagickLibAddendum) && defined(__clang__)
#    pragma clang diagnostic push
#    pragma clang diagnostic push
#    include <Magick++.h>
#    if MagickLibVersion != 0x221900
#      pragma clang diagnostic pop
#      pragma clang diagnostic pop
#    endif
#  else
#    include <Magick++.h>
#  endif
#else // defined WITH_MAGICK
#  error "DGtal has not been built with imagemagick support. Consider adding -DWITH_MAGICK=true when building the project with cmake."
#endif // defined WITH_MAGICK


#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  namespace functors
  {
    template<typename TValue>
    struct MagickCast
    {
      Cast<TValue> myCast;
      TValue operator()(const Color &col) const
      {
        return myCast( col.red() + col.green() + col.blue() );
      }
    };
    
    template<>  
    struct MagickCast<Color>
    {
      Color operator()(const Color &col) const
      {
        return col;
      }
    };
  } 
  
  /////////////////////////////////////////////////////////////////////////////
  // template class MagickReader
  /**
   * Description of template class 'MagickReader' <p>
   * \brief Aim: implements methods to read a 2D image using the ImageMagick library.
   *
   * The functor cast colors (DGtal::Color) to the image value type (@a TimageContainer::Value).
   *
   * Typical examples of functor are:
   *   - Color to scalar values (e.g. unsigned char) for "grayscale" images
   *   - Identity functor but the image needs to have DGtal::Color as value type.
   *
   * @tparam TImageContainer the image container to use. 
   * @tparam TFunctor the type of functor used in the import to cast color to image values (by default set to functors::MagickCast< TImageContainer::Value>) .
   */
  template <typename TImageContainer, typename TFunctor=  functors::MagickCast< typename TImageContainer::Value > >
  struct MagickReader
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain::Vector Vector;
    typedef typename TImageContainer::Value Value;    
    typedef TFunctor Functor ;

    BOOST_STATIC_ASSERT( (ImageContainer::Domain::dimension == 2));

    /** 
     * Main method to import an Image into an instance of the 
     * template parameter ImageContainer.
     * 
     * @param filename the file name to import.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > .
     * @param topbotomOrder if true, the point of coordinate (0,0) will be the bottom left corner image point (default) else the center of image coordinate will be the top left of the image (not usual).  
     * @return an instance of the ImageContainer.
     */
    static ImageContainer importImage(const std::string & filename, 
				      const Functor & aFunctor =  Functor(), 
				      bool topbotomOrder = true);
    
  }; // end of class MagickReader


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/MagickReader.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MagickReader_h

#undef MagickReader_RECURSES
#endif // else defined(MagickReader_RECURSES)
