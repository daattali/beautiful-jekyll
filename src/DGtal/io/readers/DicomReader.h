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
 * @file DicomReader.h
 * @author Adrien Krähenbühl (\c adrien.krahenbuhl@loria.fr )
 * LORIA (CNRS, UMR 7503), Université de Lorraine, France
 *
 * @date 2013/10/10
 *
 * Header file for module DicomReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DicomReader_RECURSES)
#error Recursive header files inclusion detected in DicomReader.h
#else
/** Prevents recursive inclusion of headers. */
#define DicomReader_RECURSES

#if !defined DicomReader_h
/** Prevents repeated inclusion of headers. */
#define DicomReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/images/CImage.h"

//////////////////////////////////////////////////////////////////////////////

#ifdef _MSC_VER
#pragma warning(disable : 4290)
#endif

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// class DicomReader
/**
 * Description of class 'DicomReader' <p>
 * \brief Aim: Import a 3D DICOM image from file series.
 *
 *  This class requires ITK installation (http://www.itk.org/ITK/resources/software.html)
 *  and to compile DGtal with -DWITH_ITK option.
 *
 *  Simple example: (extract from test/io/readers/testDicomReader.cpp)
 *
 *  @code
 *  #include "DGtal/images/ImageContainerBySTLVector.h"
 *  #include "DGtal/helpers/StdDefs.h"
 *  #include "DGtal/io/readers/DicomReader.h"
 *
 *  ...
 *
 *  typedef ImageContainerBySTLVector<DGtal::Z3i::Domain, unsigned char > Image3D;
 *  string filename = "test.dcm";
 *  Image3D image = DicomReader< Image3D, Rescaling<int32_t,Image3D::Value> >::importDicom(
 * 								filename, Rescaling<int32_t,Image3D::Value>(-900,530,0,255) );
 *  @endcode
 *
 * @tparam TImageContainer the type of the image container
 *
 * @tparam TFunctor the type of functor used in the import (you can use the Rescaling as in the example above).
 *
 */


  template <typename TImageContainer,
		typename TFunctor = functors::Cast< typename TImageContainer::Value > >
  struct DicomReader
  {
	// ----------------------- Standard services ------------------------------
  public:

	typedef TImageContainer ImageContainer;
	typedef typename TImageContainer::Value Value;
	typedef TFunctor Functor;
	typedef int32_t PixelType;

	BOOST_CONCEPT_ASSERT((  concepts::CImage<ImageContainer> )) ;
	BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<Functor, PixelType, Value > )) ;
	BOOST_STATIC_ASSERT(( TImageContainer::Domain::dimension == 3 ));

	/**
	 * Main method to import a Dicom serie into an instance of the
	 * template parameter ImageContainer.
	 *
	 * @param aFilename one file of the serie to import.
	 * @param aFunctor the functor used to import and cast the source
	 * image values into the type of the image container value (by
	 * default set to functors::Cast < TImageContainer::Value >.
	 *
	 * @return an instance of the ImageContainer.
	 */
	static ImageContainer importDicom(const std::string & aFilename,
									  const Functor & aFunctor =  Functor());

 }; // end of class  DicomReader



} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/DicomReader.ih"


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DicomReader_h

#undef DicomReader_RECURSES
#endif // else defined(DicomReader_RECURSES)
