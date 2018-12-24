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
 * @file VolReader.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2010/07/25
 *
 * Header file for module VolReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(VolReader_RECURSES)
#error Recursive header files inclusion detected in VolReader.h
#else // defined(VolReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define VolReader_RECURSES

#if !defined VolReader_h
/** Prevents repeated inclusion of headers. */
#define VolReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <sstream>
#include <string>
#include <cstdio>
#include "DGtal/base/Common.h"
#include "DGtal/base/CUnaryFunctor.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class VolReader
  /**
   * Description of template class 'VolReader' <p>
   * \brief Aim: implements methods to read a "Vol" file format.
   *
   * The main import method "importVol" returns an instance of the template 
   * parameter TImageContainer.
   *
   * The private methods have been backported from the SimpleVol project 
   * (see http://liris.cnrs.fr/david.coeurjolly).
   *
   * Example usage:
   * @code
   * ...
   * typedef SpaceND<int,3> Space3;
   * typedef HyperRectDomain<Space3> TDomain;
   * typedef TDomain::Point Point;
   *
   * //Default image container = STLVector
   * typedef ImageSelector<TDomain, int>::Type Image;
   *
   * Image image = VolReader<Image>::importVol("data.vol");
   *
   * trace.info() << image <<endl;
   * ...
   * @endcode
   *
   * @tparam TImageContainer the image container to use. 
   *
   * @tparam TFunctor the type of functor used in the import (by default set to functors::Cast< TImageContainer::Value>) .
   * @see testVolReader.cpp
   */
  template <typename TImageContainer,  
	    typename TFunctor = functors::Cast< typename TImageContainer::Value > >
  struct VolReader
  {
    // ----------------------- Standard services ------------------------------

    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Value Value;
    typedef TFunctor Functor;
    
    BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, unsigned char, Value > )) ;    

    BOOST_STATIC_ASSERT(ImageContainer::Domain::dimension == 3);


    /** 
     * Main method to import a Vol into an instance of the 
     * template parameter ImageContainer.
     * 
     * @param filename the file name to import.
     * @param aFunctor the functor used to import and cast the source
     * image values into the type of the image container value (by
     * default set to functors::Cast < TImageContainer::Value > .
     *
 
     * @return an instance of the ImageContainer.
     */
    static ImageContainer importVol(const std::string & filename, 
                                    const Functor & aFunctor =  Functor());
    
  private:

    typedef unsigned char voxel;
    /**
     * This class help us to associate a field type and his value.
     * An object is a pair (type, value). You can copy and assign
     * such objects.
     */
    /* In recent C++, we should use a std::map, but we prefer (badly) code it
       by hand for compatibility with old compilers.
       At this time, there is a limit of 30 fields in header :-} */
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
    
    //! Global list of required fields in a .vol file
    static const char *requiredHeaders[];
   
  }; // end of class VolReader


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/VolReader.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined VolReader_h

#undef VolReader_RECURSES
#endif // else defined(VolReader_RECURSES)
