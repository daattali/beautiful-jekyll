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
 * @file PPMReader.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2011/04/29
 *
 * Header file for module PPMReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(PPMReader_RECURSES)
#error Recursive header files inclusion detected in PPMReader.h
#else // defined(PPMReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define PPMReader_RECURSES

#if !defined PPMReader_h
/** Prevents repeated inclusion of headers. */
#define PPMReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/io/colormaps/BasicColorToScalarFunctors.h"
//////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable : 4290)
#endif

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class PPMReader
/**
 * Description of class 'PPMReader' <p>
 * \brief Aim: Import a 2D or 3D using the Netpbm formats (ASCII mode).
 * - PPM: RGB 
 *  - PGM: grayscale
 *  - PPM3D: 3D variant of PPM
 *  - PGM3D: 3D variant of PGM
 * 
 *
 *  Simple example: (extract from test file testPPMReader.cpp)
 * 
 *  @code
 *  #include "DGtal/helpers/StdDefs.h"
 *  #include "DGtal/io/readers/PPMReader.h"
 *  #include "DGtal/kernel/images/ImageSelector.h"
 *  ...
 *  string filename = "test.pgm";
 *  typedef ImageSelector < Z2i::Domain, uint>::Type Image;
 *  Image image = PPMReader<Image>::importPGMImage( filename ); 
 *   @endcode
 *  You can then for instance display a threshold part of the image:
 *  @code 
 *  #include "DGtal/kernel/imagesSetsUtils/SetFromImage.h"  
 *  ...
 *  Z2i::DigitalSet set2d (image.domain());
 *  // Threshold all pixel in ]0, 255] in a DigitalSet   
 *  SetFromImage<Z2i::DigitalSet>::append<Image>(set2d, image, 0, 255);
 *  Board2D board;
 *  board << image.domain() << set2d; // display domain and set   
 *  @endcode
 *
 * @tparam TImageContainer the type of the image container
 *
 * @tparam TFunctor the type of the functor to transform the source image color into  scalar value. This functor should follows the concept 
 *  CUnaryFunctor<TFunctor,  DGtal::Color, TImageContainer::Value> 
 *
 *  
 */
  template <typename TImageContainer, 
	    typename TFunctor=functors::ColorRGBEncoder<typename TImageContainer::Value> >
  struct PPMReader
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain::Vector Vector;
    typedef typename TImageContainer::Value Value;
    typedef TFunctor Functor;
    
    enum MagicNumber {P1,P2,P3,P4,P5,P6};

    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor,  DGtal::Color, Value> )) ;    

    BOOST_STATIC_ASSERT( (ImageContainer::Domain::dimension == 2) || 
                         (ImageContainer::Domain::dimension == 3));

   
     /** 
     * Main method to import a PPM (24bit, 8bits per channel) into an instance of the 
     * template parameter ImageContainer.
     * 
     * @param aFilename the file name to import.  
     * @param aFunctor the functor that from a given color return it associated code (by default set to BasicColorToScalarFunctors::ColorRGBEncoder). 
     * @param topbotomOrder
     * if true, the point of coordinate (0,0) will be the bottom left
     * corner image point (default) else the center of image
     * coordinate will be the top left of the image (not usual).
     * @return an instance of the ImageContainer.
     */
    static  ImageContainer importPPM(const std::string & aFilename, 
                                     const Functor & aFunctor =  functors::ColorRGBEncoder<Value>(), 
				     bool topbotomOrder = true);


    
 }; // end of class  PPMReader



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/PPMReader.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined PPMReader_h

#undef PPMReader_RECURSES
#endif // else defined(PPMReader_RECURSES)
