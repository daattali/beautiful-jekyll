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
 * @file RawReader.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/25
 *
 * Header file for module RawReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(RawReader_RECURSES)
#error Recursive header files inclusion detected in RawReader.h
#else // defined(RawReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RawReader_RECURSES

#if !defined RawReader_h
/** Prevents repeated inclusion of headers. */
#define RawReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include <cstdio>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include <boost/static_assert.hpp>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class RawReader
  /**
   * Description of template class 'RawReader' <p>
   * \brief Aim: Raw binary import of an Image.
   *
   * The import methods \c importRaw8, \c importRaw16 and \c importRaw32 read raw files (little-endian format)
   * containing unsigned integer values of, respectively, 8 bits, 16 bits and 32 bits width.
   * The method \c importRaw can read any type of values, signed integers, floating point types or
   * even structures.
   *
   * All these methods return an instance of the template parameter \c TImageContainer. A functor can be specified to convert raw values to image values.
   *
   * Example usage:
   * @code
   * ...
   * typedef DGtal::SpaceND<int,3> Space3;
   * typedef DGtal::HyperRectDomain<Space3> TDomain;
   * typedef TDomain::Point Point;
   *
   * //Default image container = STLVector
   * typedef DGtal::ImageSelector<TDomain, int>::Type Image;
   *
   * DGtal::RawReader<Image> reader;
   * Image image = reader.importRaw8("data.raw");
   *
   * trace.info() << image <<endl;
   * ...
   * @endcode
   *
   * @tparam TImageContainer the image container to use.
   *
   * @tparam TFunctor the type of functor used in the import (by default set to functors::Cast< TImageContainer::Value>) .
   *
   * @see RawWriter
   * @see testRawReader.cpp
   */
  template <typename TImageContainer,
      typename TFunctor = functors::Cast< typename TImageContainer::Value > >
  struct RawReader
  {
    // ----------------------- Standard services ------------------------------
  public:

    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Value Value;
    typedef typename TImageContainer::Domain::Vector Vector;
    typedef TFunctor Functor;

    /**
     * Method to import a Raw (any type stored in little-endian format)
     * into an instance of the template parameter ImageContainer.
     *
     * @tparam Word read pixel type.
     * @param filename the file name to import.
     * @param extent the size of the raw data set.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > ).
     * aFunctor must accept Word as input.
     * @return an instance of the ImageContainer.
     */
    template <typename Word>
    static ImageContainer importRaw(const std::string & filename,
             const Vector & extent,
             const Functor & aFunctor =  Functor());

    /**
     * Method to import a Raw (unsigned 8bits little endian, uint8_t, unsigned char) into an instance of the
     * template parameter ImageContainer.
     *
     * @param filename the file name to import.
     * @param extent the size of the raw data set.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > ).
     * aFunctor must accept uint8_t as input.
     * @return an instance of the ImageContainer.
     */
    static ImageContainer importRaw8(const std::string & filename,
             const Vector & extent,
             const Functor & aFunctor =  Functor());

    /**
     * Method to import a Raw (unsigned 16bits little endian, uint16_t, unsigned short) into an instance of the
     * template parameter ImageContainer.
     *
     * @param filename the file name to import.
     * @param extent the size of the raw data set.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > ).
     * aFunctor must accept uint16_t as input.
     * @return an instance of the ImageContainer.
     */
    static ImageContainer importRaw16(const std::string & filename,
             const Vector & extent,
             const Functor & aFunctor =  Functor());

    /**
     * Method to import a Raw (unsigned 32bits little endian, uint32_t, unsigned int) into an instance of the
     * template parameter ImageContainer.
     *
     * @param filename the file name to import.
     * @param extent the size of the raw data set.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > ).
     * aFunctor must accept uint32_t as input.
     * @return an instance of the ImageContainer.
     */
    static ImageContainer importRaw32(const std::string & filename,
             const Vector & extent,
             const Functor & aFunctor =  Functor());


  private:

  }; // end of class RawReader

  /**
   * Generic read word (binary mode) in little-endian mode.
   *
   * @param fin input FILE.
   * @param aValue value to write.
   *
   * @return modified stream.
   */
  template <typename Word>
  FILE* raw_reader_read_word( FILE* fin, Word& aValue );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/RawReader.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined RawReader_h

#undef RawReader_RECURSES
#endif // else defined(RawReader_RECURSES)
