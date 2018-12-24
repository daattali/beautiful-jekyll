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
 * @file HDF5Writer.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/09/11
 *
 * Header file for module HDF5Writer.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(HDF5Writer_RECURSES)
#error Recursive header files inclusion detected in HDF5Writer.h
#else // defined(HDF5Writer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define HDF5Writer_RECURSES

#if !defined HDF5Writer_h
/** Prevents repeated inclusion of headers. */
#define HDF5Writer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/BasicFunctors.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class HDF5Writer
  /**
   * Description of template struct 'HDF5Writer' <p>
   * \brief Aim: Export an Image with the HDF5 format.
   *
   * A functor can be specified to convert image values to
   * unsigned char values.
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
   */
  template <typename TImage, typename TFunctor = functors::Identity>
  struct HDF5Writer
  {
    // ----------------------- Standard services ------------------------------
    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, Value, unsigned char> )) ;    
    BOOST_STATIC_ASSERT(TImage::Domain::dimension == 3);

    /** 
     * Export a 3D UInt8 HDF5 output file with ZLIB compression activated.
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param aDataset the dataset name to export.
     * @param aFunctor functor used to cast image values
     * @return true if no errors occur.
     */
    static bool exportHDF5_3D(const std::string & filename, const Image &aImage, const std::string & aDataset,
			  const Functor & aFunctor = Functor());
  };
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/HDF5Writer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined HDF5Writer_h

#undef HDF5Writer_RECURSES
#endif // else defined(HDF5Writer_RECURSES)
