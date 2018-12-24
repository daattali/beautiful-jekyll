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
 * @file LongvolReader.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/06/11
 *
 * Header file for module LongvolReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(LongvolReader_RECURSES)
#error Recursive header files inclusion detected in LongvolReader.h
#else // defined(LongvolReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define LongvolReader_RECURSES

#if !defined LongvolReader_h
/** Prevents repeated inclusion of headers. */
#define LongvolReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include "DGtal/base/Common.h"
#include <boost/static_assert.hpp>
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/base/CUnaryFunctor.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  
  /////////////////////////////////////////////////////////////////////////////
  // template class LongvolReader
  /**
   * Description of template class 'LongvolReader' <p>
   * \brief Aim: implements methods to read a "Longvol" file format
   * (with DGtal::uint64_t value type).
   *
   * The main import method "importLongvol" returns an instance of the template
   * parameter TImageContainer.
   *
   * The private methods have been backported from the Simplelvol project
   * (see http://liris.cnrs.fr/david.coeurjolly).
   *
   * Example usage:
   * @code
   * ...
   * #include <DGtal/helpers/StdDefs.h>
   *
   * //Default image container = STLVector
   * typedef ImageSelector<Z3i::Domain, DGtal::uint64_t>::Type Image;
   *
   * Image image = LongvolReader<Image>::importLongvol("data.longvol");
   *
   * trace.info() << image <<endl;
   * ...
   * @endcode
   *
   * @tparam TImageContainer the image container to use.
   * @tparam TFunctor the type of functor used in the import (by default set to functors::Cast< TImageContainer::Value>).
   *
   * @see testLongvol.cpp
   */
  template <typename TImageContainer,
  typename TFunctor= functors::Cast< typename TImageContainer::Value > >
  struct LongvolReader
  {
    // ----------------------- Standard services ------------------------------
    
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Value Value;
    typedef TFunctor Functor;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, DGtal::uint64_t, Value > )) ;
    BOOST_STATIC_ASSERT(ImageContainer::Domain::dimension == 3);
    
    
    /**
     * Main method to import a Longvol into an instance of the
     * template parameter ImageContainer.
     *
     * @param filename the file name to import.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > .
     *
     *@return an instance of the ImageContainer.
     */
    static ImageContainer importLongvol(const std::string & filename,
                                        const Functor & aFunctor =  Functor());
    
    
    
  private:
    
    /**
     * Generic read word (binary mode) in little-endian mode.
     *
     * @param fin input stream.
     * @param aValue value to write.
     *
     * @return modified stream.
     */
    template <typename Word>
    static
    std::stringstream& read_word( std::stringstream & fin, Word& aValue )
    {
      aValue = 0;
      char c;
      for (unsigned int size = 0; size < sizeof( Word ); ++size)
      {
        fin.get( c ) ;
        unsigned char cc=static_cast<unsigned char>(c);
        aValue |= (cc << (8 * size));
      }
      return fin;
    }
    
    
    typedef unsigned char voxel;
    /** This class help us to associate a field type and his value.
     * An object is a pair (type, value). You can copy and assign
     * such objects.
     */
    /* In recent C++, we should use a std::map, but we prefer (badly) code it
     * by hand for compatibility with old compilers.
     * At this time, there is a limit of 30 fields in header :-}
     */
    struct HeaderField {
      //! Constructor. The string are copied.
      HeaderField( const char *t, const char *v ) :
      type( strdup(t) ), value( strdup(v) ) {}
      ~HeaderField() {
        free( type );
        free( value );
      }
      //! Copy constructor
      HeaderField( const HeaderField &h ) :
      type( strdup(h.type) ), value( strdup(h.value) ) {};
      //! Default constructor
      HeaderField() : type(NULL), value(NULL) {};
      //! Assignement operator
      const HeaderField &operator = (const HeaderField &h) {
        free( type );
        free( value );
        if (h.type != NULL) {
          type = strdup( h.type );
          value = strdup( h.value );
        }
        return *this;
      }
      //! Type of field (e.g. Voxel-Size)
      char *type;
      //! Value of field (e.g. 2)
      char *value;
    };
    
    
    //! Returns NULL if this field is not found
    static const char *getHeaderValue( const char *type, const HeaderField * header );
    
    //! Returns non-zero if failure
    static     int getHeaderValueAsInt( const char *type, int *dest , const HeaderField * header);
    
    //! Internal method which returns the index of a field or -1 if not found.
    static int getHeaderField( const char *type, const HeaderField * header ) ;
    
    //! Global list of required fields in a .longvol file
    static const char *requiredHeaders[];
    
  }; // end of class LongvolReader
  
  
} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/LongvolReader.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined LongvolReader_h

#undef LongvolReader_RECURSES
#endif // else defined(LongvolReader_RECURSES)
