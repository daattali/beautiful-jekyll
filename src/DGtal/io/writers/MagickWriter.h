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
 * @file MagickWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2017/12/30
 *
 * Header file for module MagickWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(MagickWriter_RECURSES)
#error Recursive header files inclusion detected in MagickWriter.h
#else // defined(MagickWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define MagickWriter_RECURSES

#if !defined MagickWriter_h
/** Prevents repeated inclusion of headers. */
#define MagickWriter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/io/writers/MagickWriter.h"
#include "DGtal/io/Color.h"

#ifndef WITH_MAGICK
#pragma error "You must activate imagemagick (-DWITH_MAGICK=true) to include this file"
#endif

// Specific inclusion method to fix warning with GraphicsMagic 1.3.31 and Clang.
// The warning comes from two "diagnostic pop" with missing corresponding push.
// "MagickLibAddendum" is defined in ImageMagick since 9 years but not in GraphicsMagic.
#if !defined(MagickLibAddendum) && defined(__clang__)
#  pragma clang diagnostic push
#  pragma clang diagnostic push
#  include <Magick++.h>
#  if MagickLibVersion != 0x221900
#    pragma clang diagnostic pop
#    pragma clang diagnostic pop
#  endif
#else
#  include <Magick++.h>
#endif

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class MagickWriter
  /**
   * Description of template struct 'MagickWriter' <p>
   * \brief Aim: Export image using Imagemagick backend.
   *
   * If imagemagick is enabled (with WITH_MAGICK set to true), this writer
   * export any image to a generic color Magick++ image (png, jpg, gif, bmp...) using
   * a given colormap functor.
   *
   * The file format is given by the filename extension during the export.
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export. The return type
   * of the functor must be a DGtal::Color (e.g. any colormap)
   *
   * @see testMagickWriter.cpp
   */
  template <typename TImage, typename TFunctor =  functors::Identity>
  struct MagickWriter
  {
    // ----------------------- Standard services ------------------------------
    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, Value, Color> )) ;
    BOOST_STATIC_ASSERT( (TImage::Domain::dimension == 2) );

    /** 
     * Export an Image with ImageMagick.
     * 
     * @param filename name of the output file the suffix is used to select
     * the file format (png, bmp, jpg,...).
     * @param anImage the image to export
     * @param aFunctor  functor used to cast image values to DGtal::Color
     *
     * @return true if no errors occur.
     */
    static bool exportMagick(const std::string & filename, const Image &anImage,
                             const Functor & aFunctor = Functor())
    {
      Magick::InitializeMagick(NULL);
      int w = (anImage.domain().upperBound()[0] - anImage.domain().lowerBound()[0])+1;
      int h = (anImage.domain().upperBound()[1] - anImage.domain().lowerBound()[1])+1;
      Magick::Geometry geom(w,h);
      Magick::Image image(geom,"white");
      for(auto point: anImage.domain())
      {
        Color c = aFunctor( anImage(point) );
        Magick::ColorRGB  magickc( c.red()/255., c.green()/255., c.blue()/255.) ;
        image.pixelColor( point[0] + anImage.domain().lowerBound()[0],
                         (h-1) - (point[1] + anImage.domain().lowerBound()[1]),
                         magickc );
      }
      image.write(filename);
      return true;
    }
  

  
  };
}//namespace

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined MagickWriter_h

#undef MagickWriter_RECURSES
#endif // else defined(MagickWriter_RECURSES)
