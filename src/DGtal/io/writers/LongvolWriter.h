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
 * @file LongvolWriter.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/11
 *
 * Header file for module LongvolWriter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LongvolWriter_RECURSES)
#error Recursive header files inclusion detected in LongvolWriter.h
#else // defined(LongvolWriter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LongvolWriter_RECURSES

#if !defined LongvolWriter_h
/** Prevents repeated inclusion of headers. */
#define LongvolWriter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
#include "DGtal/base/BasicFunctors.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class LongvolWriter
  /**
   * Description of template struct 'LongvolWriter' <p>
   * \brief Aim: Export a 3D Image using the Longvol formats
   * (volumetric image with DGtal::uint64_t value type).
   *
   * A functor can be specified to convert image values to LongVol values
   * (DGtal::uint64_t).
   *
   * @tparam TImage the Image type.
   * @tparam TFunctor the type of functor used in the export.
   *
   * @see testLongvol.cpp
   */
  template <typename TImage, typename TFunctor = functors::Identity>
  struct LongvolWriter
  {
    // ----------------------- Standard services ------------------------------

    typedef TImage Image;
    typedef typename TImage::Value Value;
    typedef TFunctor Functor;
    typedef DGtal::uint64_t ValueLongvol;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, Value, ValueLongvol> )) ;    
    
    
    /** 
     * Export an Image with the Longvol format. A DGtal::IOException
     * is thrown in case of io problems.
     * 
     * @param filename name of the output file
     * @param aImage the image to export
     * @param compressed boolean to decide wether the vol must be compressed or not
     * @param aFunctor functor used to cast image values
     * @return true if no errors occur.
     */
    static bool exportLongvol(const std::string & filename, const Image &aImage,
                              const bool compressed = true,
                              const Functor & aFunctor = Functor());
    
    
  private: 
    
    /** 
     * Generic write word (binary mode) in little-endian.
     * 
     * @param outs output stream.
     * @param value value to write.
     * 
     * @return modified stream.
     */
    template <typename Word>
    static
    std::ostream& write_word( std::ostream& outs, Word value )
    {
      for (unsigned size = sizeof( Word ); size; --size, value >>= 8)
        outs.put( static_cast <char> (value & 0xFF) );
      return outs;
    }
    
  };
}//namespace

///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/writers/LongvolWriter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LongvolWriter_h

#undef LongvolWriter_RECURSES
#endif // else defined(LongvolWriter_RECURSES)
