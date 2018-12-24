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
 * @file ITKWriter.h
 * @author Pierre Gueth (\c pierre.gueth@gmail.com )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/28
 *
 * Header file for module ITKWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ITKWriter_RECURSES)
#error Recursive header files inclusion detected in ITKWriter.h
#else // defined(ITKWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ITKWriter_RECURSES

#if !defined ITKWriter_h
/** Prevents repeated inclusion of headers. */
#define ITKWriter_h

#include "DGtal/images/CConstImage.h"
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/io/ITKIOTrait.h"

namespace DGtal
{

  /**
   * Description of template class 'ITKWriter'
   * \brief Export a 2D/3D Image using the ITK formats.
   *
   * A functor can be specified to convert image values to ITK file values.
   * ITKIOTrait is used to determine the actual value type used when saving the image.
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
	 * @see ITKReader
   * @see ITKIOTrait
   */
  template <typename TImage, typename TFunctor = typename ITKIOTrait<typename TImage::Value>::DefaultWriteFunctor >
  struct ITKWriter
  {
    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef typename ITKIOTrait<Value>::ValueOut ValueOut;
    typedef TFunctor Functor;

    BOOST_CONCEPT_ASSERT(( concepts::CConstImage<TImage> ));
    BOOST_CONCEPT_ASSERT(( concepts::CUnaryFunctor<TFunctor, Value, ValueOut> )) ;
    BOOST_STATIC_ASSERT(( (TImage::Domain::dimension == 3) || (TImage::Domain::dimension == 2) ));

    /**
     * Export an Image with a format supported by ITK.
     *
     * @param filename name of the output file
     * @param aImage the image to export
     * @param aFunctor functor used to cast image values
     * @return true if no errors occur.
     */
    static bool exportITK(const std::string & filename, const Image &aImage,
        const Functor & aFunctor = Functor());
  };
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/ITKWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ITKWriter_h

#undef ITKWriter_RECURSES
#endif // else defined(ITKWriter_RECURSES)
