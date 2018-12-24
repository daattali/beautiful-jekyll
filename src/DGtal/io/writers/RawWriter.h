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
 * @file RawWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/22
 *
 * Header file for module RawWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(RawWriter_RECURSES)
#error Recursive header files inclusion detected in RawWriter.h
#else // defined(RawWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define RawWriter_RECURSES

#if !defined RawWriter_h
/** Prevents repeated inclusion of headers. */
#define RawWriter_h

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
  // template class RawWriter
  /**
   * Description of template struct 'RawWriter' <p>
   * \brief Aim: Raw binary export of an Image.
   *
   * The export methods \c exportRaw8, \c exportRaw16 and \c exportRaw32 write raw files (little-endian format)
   * with unsigned integer values of, respectively, 8 bits, 16 bits and 32 bits width.
   * The method \c exportRaw can write any type of values, signed integers, floating point types or
   * even structures.
   *
   * A functor can be specified to convert image values to raw values
   * (e.g. unsigned char for \c exportRaw8).
   * 
   * Example usage:
   * @code
   * ...
   * typedef DGtal::SpaceND<int,3> Space;
   * typedef DGtal::HyperRectDomain<Space> Domain;
   * typedef Domain::Point Point;
   *
   * //Default image container = STLVector
   * typedef DGtal::ImageSelector<TDomain, unsigned char>::Type Image;
   *
   * Domain domain( Point::diagonal(0), Point::diagonal(10) );
   * Image image( domain );
   *
   * ... // Filling the image.
   *
   * DGtal::RawWriter<Image> writer;
   * if ( writer.exportRaw8( "data.raw", image ) )
   *   trace.info() << "Image successfully exported." << endl;
   * else
   *   trace.info() << "Error while exporting image." << endl;
   * @endcode
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
   *
   * @see RawReader
   * @see testRawReader.cpp
   */
  template <typename TImage, typename TFunctor = functors::Identity>
  struct RawWriter
  {
    // ----------------------- Standard services ------------------------------

    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;

    /**
     * Export an Image to Raw format (any value type, in little-endian format).
     *
     * @tparam Word exported pixel type.
     * @param filename name of the output file.
     * @param aImage the image to export.
     * @param aFunctor functor used to cast image values.
     * @return true if no errors occur.
     */
    template <typename Word>
    static bool exportRaw(const std::string& filename,
         const Image& aImage,
         const Functor& aFunctor = Functor());

    /**
     * Export an Image to Raw format (unsigned 8bits little-endian, uint8_t, unsigned char).
     *
     * @param filename name of the output file.
     * @param aImage the image to export.
     * @param aFunctor functor used to cast image values.
     * @return true if no errors occur.
     */
    static bool exportRaw8(const std::string& filename,
         const Image& aImage,
         const Functor& aFunctor = Functor());

    /**
     * Export an Image to Raw format (unsigned 16bits little-endian, uint16_t, unsigned short).
     *
     * @param filename name of the output file.
     * @param aImage the image to export.
     * @param aFunctor functor used to cast image values.
     * @return true if no errors occur.
     */
    static bool exportRaw16(const std::string& filename,
         const Image& aImage,
         const Functor& aFunctor = Functor());

    /**
     * Export an Image to Raw format (unsigned 32bits little-endian, uint32_t, unsigned int).
     *
     * @param filename name of the output file.
     * @param aImage the image to export.
     * @param aFunctor functor used to cast image values.
     * @return true if no errors occur.
     */
    static bool exportRaw32(const std::string& filename,
         const Image& aImage,
         const Functor& aFunctor = Functor());

  private:

  };

  /**
   * Generic write word (binary mode) in little-endian.
   *
   * @param outs output stream.
   * @param value value to write.
   *
   * @return modified stream.
   */
  template <typename Word>
  std::ostream& raw_writer_write_word(std::ostream& outs, Word value);

}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/RawWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined RawWriter_h

#undef RawWriter_RECURSES
#endif // else defined(RawWriter_RECURSES)
