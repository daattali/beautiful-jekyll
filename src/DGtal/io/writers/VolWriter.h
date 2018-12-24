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
 * @file VolWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/22
 *
 * Header file for module VolWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(VolWriter_RECURSES)
#error Recursive header files inclusion detected in VolWriter.h
#else // defined(VolWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VolWriter_RECURSES

#if !defined VolWriter_h
/** Prevents repeated inclusion of headers. */
#define VolWriter_h

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
  // template class VolWriter
  /**
   * Description of template struct 'VolWriter' <p>
   * \brief Aim: Export a 3D Image using the Vol formats.
   *
   * A functor can be specified to convert image values to Vol values
   * (unsigned char).
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
   */
  template <typename TImage, typename TFunctor = functors::Identity>
  struct VolWriter
  {
    // ----------------------- Standard services ------------------------------
    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, Value, unsigned char> )) ;    
    BOOST_STATIC_ASSERT(TImage::Domain::dimension == 3);

    /** 
     * Export an Image with the Vol format.
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param compressed boolean to decide wether the vol must be compressed or not
     * @param aFunctor functor used to cast image values
     * @return true if no errors occur.
     */
    static bool exportVol(const std::string & filename, const Image &aImage, 
                          const bool compressed=true,
                          const Functor & aFunctor = Functor());
  };
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/VolWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VolWriter_h

#undef VolWriter_RECURSES
#endif // else defined(VolWriter_RECURSES)
