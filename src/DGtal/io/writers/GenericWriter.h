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
 * @file GenericWriter.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/05/01
 *
 * Header file for module GenericWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(GenericWriter_RECURSES)
#error Recursive header files inclusion detected in GenericWriter.h
#else // defined(GenericWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GenericWriter_RECURSES

#if !defined GenericWriter_h
/** Prevents repeated inclusion of headers. */
#define GenericWriter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/images/CConstImage.h"
#include "DGtal/images/Image.h"
#include "DGtal/images/ImageContainerBySTLVector.h"
#include "DGtal/images/ImageContainerBySTLMap.h"

#include "DGtal/io/colormaps/HueShadeColorMap.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class GenericWriter
  /**
   * Description of template class 'GenericWriter' <p>
   * \brief Aim: Provide a mechanism to save image (2D or 3D) into file  with the best saver loader according to an filename (by parsing the extension).
   *
   * The typical use is very simple:
   * - First include the header of the generic reader (and StdDefs) and define image type:
   @code
   #include "DGTal/io/readers/GenericWriter.h"
   #include "DGtal/helpers/StdDefs.h"
   typedef DGtal::ImageContainerBySTLMap<DGtal::Z3i::Domain, unsigned char> Image3D;
   typedef DGtal::ImageContainerBySTLMap<DGtal::Z2i::Domain, unsigned char> Image2D;
   @endcode
   * - After contructing and filling an image (anImage2D or anImage3D), just save it with:
   @code
   anImage3D >> "aFilename.pgm3d";
   anImage3D >> "aFilename.vol";
   anImage2D >> "aFilename.pgm";
   @endcode
   * @note the stream operator hide a default functor (c++ cast to a
   *  given type) and if the user want to control the cast he can used the
   *  exportFile function (see below).
   * @tparam TContainer the container (mainly an ImageContainer like ImageContainerBySTLVector or ImageContainerBySTLMap).
   * @tparam Tdim the dimension of the container (by default given by the container).
   * @tparam TValue the value type of data contained in the image (by default given by the container)
   * @tparam TFunctor a functor type to apply image transformation before saving the image (by default set to functors::Identity).
   *
   *
   */

  template <typename TContainer,
            int Tdim=TContainer::Point::dimension,
            typename TValue = typename TContainer::Value,
            typename TFunctor = functors::Identity >
  struct GenericWriter
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;
    /**
     * Export an  image.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param aFunctor to apply image transformation before saving.
     *
     **/
    static bool exportFile(const std::string &filename,
                           const TContainer &anImage,
                           const TFunctor & aFunctor = TFunctor() );
  };

  /**
   * GenericWriter
   * Template partial specialisation for volume images of dimension 3 and unsigned char value type (which allows to export vol, pgm3D, h5 and raw file format).
   **/
  template <typename TContainer, typename TFunctor>
  struct GenericWriter<TContainer, 3 , unsigned char,  TFunctor>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, typename TContainer::Value, unsigned char> )) ;
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;

    /**
     * Export a volume image.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param datasetName the dataset name to export.
     * @param aFunctor to apply image transformation before saving.
     *
     **/
    static bool exportFile(const std::string &filename,  const TContainer &anImage, const std::string &datasetName="UInt8Array3D",
                           const TFunctor & aFunctor = TFunctor() );

  };

  /**
   * GenericWriter
   * Template partial specialisation for volume images of dimension 3 and DGtal::uint64_t value type (which allows to export longvol file format).
   **/
  template <typename TContainer, typename TFunctor>
  struct GenericWriter<TContainer, 3 , DGtal::uint64_t,  TFunctor>
  {

    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, typename TContainer::Value, DGtal::uint64_t > )) ;
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;


    /**
     * Export a volume image.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param aFunctor to apply image transformation before saving.
     *
     **/
    static bool exportFile(const std::string &filename,  const TContainer &anImage,
                           const TFunctor & aFunctor = TFunctor() );

  };


  /**
   * GenericWriter
   * Template partial specialisation for volume images of dimension 3
   **/
  template <typename TContainer, typename TValue, typename TFunctor>
  struct GenericWriter<TContainer, 3 , TValue, TFunctor>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;
    /**
     * Export a volume image.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param datasetName the dataset name to export.
     * @param aFunctor to apply image transformation before saving.
     *
     **/
    static bool exportFile(const std::string &filename,
                           const TContainer &anImage,
                           const std::string &datasetName="UInt8Array3D",
                           const TFunctor & aFunctor = TFunctor() );

  };

  /**
   * GenericWriter
   * Template partial specialisation for images of dimension 2
   **/
  template <typename TContainer, typename TValue,  typename TFunctor>
  struct GenericWriter<TContainer, 2, TValue, TFunctor>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;

    /**
     * Export the 2D image file.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param aFunctor to apply image transformation before saving.
     *
     **/

    static bool exportFile(const std::string &filename,
                           const TContainer &anImage,
                           const TFunctor & aFunctor = TFunctor() );

  };


  /**
   * GenericWriter
   * Template partial specialisation for images of dimension 2 with image value DGtal::Color 
   **/
  template <typename TContainer,  typename TFunctor>
  struct GenericWriter<TContainer, 2, DGtal::Color, TFunctor>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;

    /**
     * Export the 2D image file.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param aFunctor to apply image transformation before saving.
     *
     **/

    static bool exportFile(const std::string &filename,
                           const TContainer &anImage,
                           const TFunctor & aFunctor = TFunctor() );

  };



  
  /**
   * GenericWriter
   * Template partial specialisation for images of dimension 2 and Functor returning a Color object
   **/
  template <typename TContainer, typename TValue >
  struct GenericWriter<TContainer, 2, TValue, HueShadeColorMap<TValue>  >
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;

    /**
     * Export the 2D image file.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param aFunctor to apply image transformation before saving: transform scalar value to Color by using HueShadeColorMap.
     *
     **/
    /**
     * Export image with specific scalar->Color functor: .
     *
     **/

    static bool exportFile(const std::string &filename, const TContainer &anImage,
                           const HueShadeColorMap<TValue> & aFunctor );

  };

  /**
   * GenericWriter
   * Template partial specialisation for images of dimension 2 and unsigned char value type (which allows to export pgm, ppm file format ).
   **/
  template <typename TContainer,  typename TFunctor>
  struct GenericWriter<TContainer, 2, unsigned char, TFunctor>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CConstImage<TContainer> )) ;
    /**
     * Export the 2D image file.
     * @param filename the filename of the saved image (with a extension name).
     * @param anImage the image to be saved.
     * @param aFunctor to apply image transformation before saving.
     *
     **/
    static bool exportFile(const std::string &filename, const TContainer &anImage,
                           const TFunctor & aFunctor = TFunctor() );

  };

  /**
   *  'operator>>' for exporting an ImageContainer.
   *  This operator automatically selects the best method according to
   *  the filename extension (pgm, pgm3D, raw, vol).
   *
   * @param aContainer the container to be exported.
   * @param aFilename the filename of the file to be exported.
   * @return true, if the export was successful.
   */
  template <typename TImageContainer >
  bool
  operator >> ( const TImageContainer & aContainer,  const std::string & aFilename  );


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/GenericWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GenericWriter_h

#undef GenericWriter_RECURSES
#endif // else defined(GenericWriter_RECURSES)
