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
 * @file PGMWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/22
 *
 * Header file for module PGMWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(PGMWriter_RECURSES)
#error Recursive header files inclusion detected in PGMWriter.h
#else // defined(PGMWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PGMWriter_RECURSES

#if !defined PGMWriter_h
/** Prevents repeated inclusion of headers. */
#define PGMWriter_h

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
  // template class PGMWriter
  /**
   * Description of template struct 'PGMWriter' <p>
   * \brief Aim: Export a 2D and a 3D Image using the Netpbm PGM formats (ASCII mode).
   *  - PGM: grayscale
   *  - PGM3D: 3D variant of PGM
   *
   * A functor can be specified to convert image values to PGM values
   * (unsigned char).
   *
   * Usage example:
   * @code
   * ...
   * typedef SpaceND<int,2> TSpace;
   * typedef TSpace::Point Point;
   * typedef HyperRectDomain<TSpace> Domain;
   * typedef ImageSelector<Domain, unsigned char>::Type Image;
   * ...
   * Point a ( 1, 1);
   * Point b ( 16, 16);
   * Image image(a,b);
   * ... //Do something in image
   * PGMWriter<Image>::exportPPM("export.pgm",image);
   * 
   * @endcode
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
   *
   * @see testPNMRawWriter.cpp
   */
  template <typename TImage, typename TFunctor =  functors::Identity>
  struct PGMWriter
  {
    // ----------------------- Standard services ------------------------------
    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, Value, unsigned char> )) ;    
    
    BOOST_STATIC_ASSERT( (TImage::Domain::dimension == 2) || 
       (TImage::Domain::dimension == 3));

    /** 
     * Export an Image with PGM format. 
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param aFunctor  functor used to cast image values
     * @param saveASCII used to save image with ASCII pixel value and with white space. 
     *        (default= false since ASCII mode is not efficient).     
     * @param topbotomOrder 'true' if the image scan should start from the top.
     * 
     * @return true if no errors occur.
     */
    static bool exportPGM(const std::string & filename, const Image &aImage, 
			  const Functor & aFunctor = Functor(),  
			  bool saveASCII=false, bool topbotomOrder=true);
  

    /** 
     * Export an Image with PGM3D format.
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param aFunctor  functor used to cast image values
     * @param saveASCII used to save image with ASCII pixel value and with white space. 
     *        (default= false since ASCII mode is not efficient).     
     * 
     * @return true if no errors occur.
     */
    static bool exportPGM3D(const std::string & filename, const Image &aImage, 
			    const Functor & aFunctor = Functor(), bool saveASCII=false);
    
  };
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/PGMWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PGMWriter_h

#undef PGMWriter_RECURSES
#endif // else defined(PGMWriter_RECURSES)
