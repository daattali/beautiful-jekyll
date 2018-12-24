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
 * @file PPMWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/22
 *
 * Header file for module PPMWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(PPMWriter_RECURSES)
#error Recursive header files inclusion detected in PPMWriter.h
#else // defined(PPMWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PPMWriter_RECURSES

#if !defined PPMWriter_h
/** Prevents repeated inclusion of headers. */
#define PPMWriter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include "DGtal/base/Common.h"
#include "DGtal/io/Color.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/BasicFunctors.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class PPMWriter
  /**
   * Description of template struct 'PPMWriter' <p>
   * \brief Aim: Export a 2D and a 3D Image using the Netpbm PPM formats (ASCII mode).
   *  - PPM: grayscale
   *  - PPM3D: 3D variant of PPM
   *
   * A functor can be specified to convert image values to DGtal::Color values.
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
   *
   * @see testPNMRawWriter.cpp
   */
  template <typename TImage, typename TFunctor>
  struct PPMWriter
  {
    // ----------------------- Standard services ------------------------------
    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, Value, DGtal::Color> )) ;    
    BOOST_STATIC_ASSERT( (TImage::Domain::dimension == 2) || 
       (TImage::Domain::dimension == 3));

    /** 
     * Export an Image with PPM format. 
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param aFunctor  functor used to cast image values
     * @param topbottomOrder true if top to bottom order is prefered (default: true)
     *
     * @return true if no errors occur.
     */
    static bool exportPPM(const std::string & filename, const Image &aImage, 
			  const Functor & aFunctor = Functor(), bool topbottomOrder=true);
  

    /** 
     * Export an Image with PPM3D format.
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param aFunctor  functor used to cast image values
     * 
     * @return true if no errors occur.
     */
    static bool exportPPM3D(const std::string & filename, const Image &aImage, 
			    const Functor & aFunctor = Functor());
    
  };
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/PPMWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PPMWriter_h

#undef PPMWriter_RECURSES
#endif // else defined(PPMWriter_RECURSES)
