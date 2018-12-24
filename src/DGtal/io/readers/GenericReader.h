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
 * @file GenericReader.h
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2013/05/01
 *
 * Header file for module GenericReader.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(GenericReader_RECURSES)
#error Recursive header files inclusion detected in GenericReader.h
#else // defined(GenericReader_RECURSES)
/** Prevents recursive inclusion of headers. */
#define GenericReader_RECURSES

#if !defined GenericReader_h
/** Prevents repeated inclusion of headers. */
#define GenericReader_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <vector>
#include "DGtal/images/CImage.h"
#include "DGtal/base/Common.h"
#include "DGtal/io/readers/VolReader.h"
#include "DGtal/io/readers/LongvolReader.h"
#include "DGtal/io/readers/PPMReader.h"
#include "DGtal/io/readers/PGMReader.h"
#include "DGtal/io/readers/RawReader.h"
#ifdef WITH_HDF5
#include "DGtal/io/readers/HDF5Reader.h"
#endif
#ifdef WITH_MAGICK
#include "DGtal/io/readers/MagickReader.h"
#endif
#ifdef WITH_ITK
#include "DGtal/io/readers/DicomReader.h"
#include "DGtal/io/readers/ITKReader.h"
#endif
#include "DGtal/io/colormaps/BasicColorToScalarFunctors.h"

//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class GenericReader
  /**
   * Description of template class 'GenericReader' <p>
   * \brief Aim: Provide a mechanism to load with the bestloader according to an image (2D or 3D) filename (by parsing the extension).
   *
   * The typical use is very simple:
   * - First include the header of the generic reader (and StdDefs) and define image type:
   @code
   #include "DGTal/io/readers/GenericReader.h"
   #include "DGtal/helpers/StdDefs.h"
   typedef DGtal::ImageContainerBySTLMap<DGtal::Z3i::Domain, unsigned int> Image3D;
   typedef DGtal::ImageContainerBySTLMap<DGtal::Z2i::Domain, unsigned int> Image2D;
   @endcode

   * - Use the same import function for both 2D or 3D images:
   @code
   Image3D an3Dimage= DGtal::GenericReader<Image3D>::import("example.vol");
   Image2D an2Dimage= DGtal::GenericReader<Image2D>::import("example.pgm");
   @endcode
   *
   * @advanced the file format value type will be cast to
   * TContainer::Value.  For instance, VOL file format deals with
   * "unsigned char" and if the TContainer::Value type is different, you
   * could have type conversion issues.
   *
   *
   * @tparam TContainer the container (mainly an ImageContainer like ImageContainerBySTLVector or ImageContainerBySTLMap).
   * @tparam Tdim the dimension of the container (by default given by the container).
   *
   */
  template <typename TContainer, int Tdim=TContainer::Point::dimension,  typename TValue = typename TContainer::Value>
  struct GenericReader
  {
    BOOST_CONCEPT_ASSERT((  concepts::CImage<TContainer> )) ;

    /**
     * Import a volume nd image file.  For the special format of raw
     * image, the default parameter of the image size must be given in
     * the optional function vector parameter (dimSpace).
     *
     * @param filename the image filename to imported.
     * @param dimSpace a vector containing the n dimensional image size.
     *
     **/

    static TContainer import(const std::string &filename,
                             std::vector<unsigned int> dimSpace= std::vector<unsigned int > () );

    /**
     * Import  a volume nd image file by specifying a value functor.
     *
     * @tparam TFunctor The type of the functor (should verify the
     * concept CUnaryFunctor<TFunctor, TValue , TContainer::Value > )
     *
     * @param dimSpace a vector containing the n dimensional image size..
     * @param filename the image filename to be imported.
     * @param aFunctor to transform the input type of image value (TValue)
     * into the given image type (TContainer::Value).
     *
     **/
    template <typename TFunctor>
    static TContainer importWithValueFunctor(
    const std::string & filename, const TFunctor & aFunctor,
    std::vector<unsigned int> dimSpace =
    std::vector<unsigned int>() )
    {
      BOOST_CONCEPT_ASSERT(
      (concepts::CUnaryFunctor<TFunctor, TValue, typename TContainer::Value>));
      DGtal::IOException dgtalio;
      const std::string extension =
      filename.substr( filename.find_last_of( "." ) + 1 );

      if ( extension == "raw" )
      {
        for ( unsigned int i = 0; i < dimSpace.size(); i++ )
          ASSERT( dimSpace[ i ] != 0 );
        typename TContainer::Point const pt;
        for ( unsigned int i = 0; i < dimSpace.size(); i++ )
          pt[ i ]            = dimSpace[ i ];

        return RawReader<TContainer, TFunctor>::template importRaw<TValue>(
        filename, pt, aFunctor );
      }

      trace.error() << "Extension " << extension
                    << " not yet implemented in DGtal GenericReader."
                    << std::endl;
      throw dgtalio;
    }

    /**
     * Import  a volume nd image file by specifying a value functor.
     *
     * @tparam TFunctor The type of the functor (should verify the
     * concept CUnaryFunctor<TFunctor, TValue , TContainer::Value > )

     * @param dimSpace a vector containing the n dimensional image
     * size.
     * @param filename the image filename to be imported.
     * @param aFunctor an ColorRGBEncoder. The type of the functor
     * (should verify the concept CUnaryFunctor<TFunctor,
     * TContainer::Value, DGtal::Color >).
     *
     **/

    template <typename TFunctor>
    static TContainer importWithColorFunctor(
    const std::string & filename, const TFunctor & aFunctor,
    std::vector<unsigned int> dimSpace =
    std::vector<unsigned int>() )

    {
      BOOST_CONCEPT_ASSERT(
      (concepts::CUnaryFunctor<TFunctor, DGtal::Color,
                               typename TContainer::Value>));

      DGtal::IOException dgtalio;
      const std::string extension =
      filename.substr( filename.find_last_of( "." ) + 1 );

      if ( extension == "raw" )
      {
        for ( unsigned int i = 0; i < dimSpace.size(); i++ )
          ASSERT( dimSpace[ i ] != 0 );
        typename TContainer::Point const pt;
        for ( unsigned int i = 0; i < dimSpace.size(); i++ )
          pt[ i ]            = dimSpace[ i ];
        return RawReader<TContainer, TFunctor>::template importRaw<
        DGtal::Color>( filename, pt, aFunctor );
      }

      trace.error() << "Extension " << extension
                    << " not yet implemented in DGtal GenericReader."
                    << std::endl;
      throw dgtalio;
    }
  };


  /**
   * GenericReader
   * Template partial specialisation for volume images of dimension 3
   **/
  template <typename TContainer, typename TValue>
  struct GenericReader<TContainer, 3, TValue>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CImage<TContainer> )) ;
    /**
     * Import a volume image file.  For the special format of raw
     * image, the default parameter x,y, z need to be updated
     * according to the dimension if the image.
     *
     * @param filename the image filename to be imported.
     * @param x the size in the x direction.
     * @param y the size in the y direction.
     * @param z the size in the z direction.
     *
     **/

    static TContainer import(const std::string &filename,  unsigned int x=0,
                             unsigned int y=0, unsigned int z=0);



    /**
     * Import an image file by specifying a value functor
     *  (used for gray scale image format: vol, longvol, pgm3D, raw).
     *
     * @tparam TFunctor The type of the functor (should verify the concept CUnaryFunctor<TFunctor, unsigned char , TContainer::Value > ).
     * @param filename the image filename to be imported.
     * @param aFunctor an ColorRGBEncoder. The type of the functor (should verify the concept CUnaryFunctor<TFunctor, TContainer::Value, DGtal::Color > ).
     * @param x x
     * @param y y
     * @param z z
     *
     **/
    template<typename TFunctor>
    static TContainer importWithValueFunctor(const std::string &filename,
                                             const TFunctor &aFunctor,
                                             unsigned int x=0,
                                             unsigned int y=0, unsigned int z=0)
      {
        BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, unsigned char, typename TContainer::Value > )) ;
        DGtal::IOException dgtalio;
        const std::string extension = filename.substr(filename.find_last_of(".") + 1);

        if ( extension == "vol" )
          {
            return VolReader<TContainer, TFunctor>::importVol( filename, aFunctor );
          }
        else if ( extension == "longvol" )
          {
            return LongvolReader<TContainer, TFunctor>::importLongvol( filename, aFunctor  );
          }
        else if ( extension == "pgm3d" || extension == "pgm3D" || extension == "p3d" || extension == "pgm" )
          {
            return PGMReader<TContainer, TFunctor>::importPGM3D(filename, aFunctor);
          }
        else if ( extension == "raw" )
          {
            ASSERT( x != 0 && y != 0 && z != 0 );
            typename TContainer::Point const pt (x, y, z);
            return RawReader< TContainer, TFunctor >::template importRaw<TValue>( filename, pt, aFunctor  );
          }

#ifdef WITH_HDF5
        if ( extension == "h5" )
          return HDF5Reader<TContainer, TFunctor>::importHDF5_3D(filename, "UInt8Array3D", aFunctor);
#endif

#ifdef WITH_ITK
        if ( extension == "dcm" )
          {
            return DicomReader<TContainer, TFunctor>::importDicom(filename, aFunctor);
          }
          else if ( extension == "nii" || extension == "mha" ||
                    extension == "mhd" || extension == "tiff" ||
                    extension == "tif" )
          {
            return ITKReader<TContainer>::importITK( filename, aFunctor );
          }
#endif

        trace.error() << "Extension " << extension<< " in 3D, not yet implemented in DGtal GenericReader." << std::endl;
        throw dgtalio;
      }
  };



  /**
   * GenericReader
   * Template partial specialisation for volume images with 32 bits values
   **/
  template <typename TContainer>
  struct GenericReader<TContainer, 3 , DGtal::uint32_t>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CImage<TContainer> )) ;
    /**
     * Import a volume image file.  For the special format of raw
     * image, the default parameter x,y, z need to be updated
     * according to the dimension if the image.
     *
     * @param filename the image filename to be imported.
     * @param x the size in the x direction.
     * @param y the size in the y direction.
     * @param z the size in the z direction.
     *
     **/

    static TContainer import(const std::string &filename,  unsigned int x=0,
                             unsigned int y=0, unsigned int z=0);



    /**
     * Import an image file by specifying a value functor
     *  (used for gray scale image format: vol, longvol, pgm3D, raw).
     *
     * @tparam TFunctor The type of the functor (should verify the concept CUnaryFunctor<TFunctor, unsigned char , TContainer::Value > ).
     * @param filename the image filename to be imported.
     * @param aFunctor an ColorRGBEncoder. The type of the functor (should verify the concept CUnaryFunctor<TFunctor, TContainer::Value, DGtal::Color > ).
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     * @param z specify the  " image size to be used with raw format.
     *
     **/
    template<typename TFunctor>
    static TContainer importWithValueFunctor(const std::string &filename,
                                             const TFunctor &aFunctor,
                                             unsigned int x=0,
                                             unsigned int y=0, unsigned int z=0)
      {
        BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, DGtal::uint32_t, typename TContainer::Value > )) ;
        DGtal::IOException dgtalio;
        const std::string extension = filename.substr( filename.find_last_of(".") + 1 );

        if ( extension == "longvol" )
          {
            return LongvolReader<TContainer, TFunctor>::importLongvol( filename, aFunctor  );
          }
        else if ( extension == "raw" )
          {
            ASSERT( x != 0 && y != 0 && z != 0 );
            typename TContainer::Point const pt (x, y, z);
            return RawReader< TContainer, TFunctor >::importRaw32 ( filename, pt, aFunctor  );
          }

#ifdef WITH_ITK
        if ( extension == "dcm" )
          {
            return DicomReader<TContainer, TFunctor>::importDicom(filename, aFunctor);
          }
        else if ( extension == "mha" || extension == "mhd" )
          {
            return ITKReader<TContainer>::importITK( filename, aFunctor );
          }
#endif

        trace.error() << "Extension " << extension<< " not yet implemented in DGtal GenericReader." << std::endl;
        throw dgtalio;
      }
  };




  /**
   * GenericReader
   * Template partial specialisation for volume images with 32 bits values
   **/
  template <typename TContainer>
  struct GenericReader<TContainer, 3 , DGtal::uint64_t>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CImage<TContainer> )) ;
    /**
     * Import a volume image file.  
     *
     * @param filename the image filename to be imported.
     *
     **/

    static TContainer import(const std::string &filename);

  };


  /**
   * GenericReader
   * Template partial specialisation for volume images of dimension 2
   **/
  template <typename TContainer, typename TValue>
  struct GenericReader<TContainer, 2, TValue>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CImage<TContainer> )) ;

    /**
     * Import a volume image file.  For the special format h5 (you need to set WITH_HDF5 of cmake build),
     *  the default parameter datasetName needs to be updated
     * according to the dimension if the image.
     *
     * @param filename the image filename to be imported.
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     *
     **/

    static TContainer import(const std::string &filename, unsigned int x=0,
                             unsigned int y=0);


    /**
     * Import an image file by specifying a color encoder functor
     *  (used only for color image format ppm, ( gif, jpeg, ... if the
     *  magick image lib is installed) .
     *
     * @tparam TFunctor The type of the functor (should verify the concept CUnaryFunctor<TFunctor, TContainer::Value, DGtal::Color > ).
     * @param filename the image filename to be imported.
     * @param aFunctor an ColorRGBEncoder. The type of the functor (should verify the concept CUnaryFunctor<TFunctor, TContainer::Value, DGtal::Color > ).
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     *
     **/
    template<typename TFunctor>
    static TContainer importWithColorFunctor(const std::string &filename,
                                             const  TFunctor &aFunctor,
                                             unsigned int x=0,
                                             unsigned int y=0)
      {
        BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, DGtal::Color, typename TContainer::Value> )) ;
        DGtal::IOException dgtalio;
        //Getting image extension
        const std::string extension = filename.substr( filename.find_last_of(".") + 1 );

        if ( extension == "ppm" )
          {
            return PPMReader<TContainer, TFunctor>::importPPM(filename, aFunctor);
          }
        else if ( extension == "raw" )
          {
            ASSERT( x != 0 && y != 0 );
            typename TContainer::Point const pt (x,y);
            return RawReader< TContainer, TFunctor >::template importRaw<DGtal::Color>( filename, pt, aFunctor);
          }
        else if ( extension == "gif" || extension == "jpg" || extension == "png" || extension == "jpeg" || extension == "bmp" )
          {
#ifdef WITH_MAGICK
            MagickReader<TContainer, TFunctor> reader;
            return reader.importImage( filename, aFunctor );
#else
            trace.error() << "Extension " << extension<< " not yet implemented in DGtal but you can add Magick option to deal with this image type." << std::endl;
            throw dgtalio;
#endif
          }

        trace.error() << "Extension " << extension<< " in 2D, not yet implemented in DGtal GenericReader." << std::endl;
        throw dgtalio;
      }


    /**
     * Import an image file by specifying a value functor used for
     *  grayscale image.
     *
     * @tparam TFunctor The type of the functor (should verify the concept CUnaryFunctor<TFunctor, unsigned char, TContainer::Value > ).
     * @param filename the image filename to be imported.
     * @param aFunctor to transform input unsigned char of image value into the given image type.
     *  image.
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     **/
    template<typename TFunctor>
    static TContainer importWithValueFunctor(const std::string &filename,
                                             const  TFunctor &aFunctor, unsigned int x=0,
                                             unsigned int y=0)
      {
        BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, unsigned char, typename TContainer::Value > )) ;

        DGtal::IOException dgtalio;
        //Getting image extension
        const std::string extension = filename.substr( filename.find_last_of(".") + 1 );

        if ( extension == "raw" )
          {
            ASSERT( x!= 0 && y != 0);
            typename TContainer::Point const pt (x,y);
            return RawReader< TContainer, TFunctor >::importRaw8( filename, pt, aFunctor  );
          }
        else if ( extension == "pgm" )
          {
            return PGMReader<TContainer, TFunctor>::importPGM(filename, aFunctor);
          }

#ifdef WITH_HDF5
        if (extension=="h5")
          return HDF5Reader<TContainer, TFunctor>::importHDF5(filename, "image8bit", aFunctor);
#endif

        trace.error() << "Extension " << extension<< " not yet implemented in DGtal GenericReader." << std::endl;
        throw dgtalio;

      }

  };

  /**
   * GenericReader
   * Template partial specialisation for volume images of dimension 2 with DGtal::uint32_t values
   **/
  template <typename TContainer>
  struct GenericReader<TContainer, 2, DGtal::uint32_t>
  {
    BOOST_CONCEPT_ASSERT((  concepts::CImage<TContainer> )) ;

    /**
     * Import a volume image file.  For the special format h5 (you need to set WITH_HDF5 of cmake build),
     *  the default parameter datasetName needs to be updated
     * according to the dimension if the image.
     *
     * @param filename the image filename to be imported.
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     *
     **/

    static TContainer import(const std::string &filename,unsigned int x=0,
                             unsigned int y=0 );


    /**
     * Import an image file by specifying a color encoder functor
     *  (used only for color image format ppm, ( gif, jpeg, ... if the
     *  magick image lib is installed) .
     *
     * @tparam TFunctor The type of the functor (should verify the concept CUnaryFunctor<TFunctor, TContainer::Value, DGtal::Color > ).
     * @param filename the image filename to be imported.
     * @param aFunctor an ColorRGBEncoder. The type of the functor (should verify the concept CUnaryFunctor<TFunctor, TContainer::Value, DGtal::Color > ).
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     *
     **/
    template<typename TFunctor>
    static TContainer importWithColorFunctor(const std::string &filename,
                                             const  TFunctor &aFunctor, unsigned int x=0,
                                             unsigned int y=0)
      {

        BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, DGtal::Color, typename TContainer::Value> )) ;
        DGtal::IOException dgtalio;
        //Getting image extension
        const std::string extension = filename.substr(filename.find_last_of(".") + 1);

        if ( extension == "ppm" )
          {
            return PPMReader<TContainer, TFunctor>::importPPM(filename, aFunctor);
          }
        else if ( extension == "raw" )
          {
            ASSERT( x != 0 && y != 0 );
            typename TContainer::Point const pt (x,y);
            return RawReader< TContainer, TFunctor >::template importRaw<DGtal::Color>( filename, pt, aFunctor);
          }
        else if ( extension == "gif" || extension == "jpg" || extension == "png" || extension == "jpeg" || extension == "bmp" )
          {
#ifdef WITH_MAGICK
            MagickReader<TContainer, TFunctor> reader;
            return reader.importImage( filename, aFunctor );
#else
            trace.error() << "Extension " << extension<< " not yet implemented in DGtal but you can add Magick option to deal with this image type." << std::endl;
            throw dgtalio;
#endif
          }

        trace.error() << "Extension " << extension<< " not yet implemented in DGtal GenericReader." << std::endl;
        throw dgtalio;
      }


    /**
     * Import an image file by specifying a value functor used for
     *  grayscale image.
     *
     * @tparam TFunctor The type of the functor (should verify the concept CUnaryFunctor<TFunctor, unsigned char, TContainer::Value > ).
     * @param filename the image filename to be imported.
     * @param aFunctor to transform input unsigned char of image value into the given image type.
     * @param x specify the  x image size to be used with raw format.
     * @param y specify the  y image size to be used with raw format.
     **/
    template<typename TFunctor>
    static TContainer importWithValueFunctor(const std::string &filename,
                                             const  TFunctor &aFunctor, unsigned int x=0,
                                             unsigned int y=0)
      {
        BOOST_CONCEPT_ASSERT((  concepts::CUnaryFunctor<TFunctor, unsigned char, typename TContainer::Value > )) ;

        DGtal::IOException dgtalio;
        //Getting image extension
        const std::string extension = filename.substr(filename.find_last_of(".") + 1);

        if ( extension == "raw" )
          {
            ASSERT( x != 0 && y != 0);
            typename TContainer::Point const pt (x,y);
            return RawReader< TContainer, TFunctor >::importRaw8 ( filename, pt, aFunctor  );
          }
        else if ( extension == "pgm ")
          {
            return PGMReader<TContainer, TFunctor>::importPGM(filename, aFunctor);
          }

#ifdef WITH_HDF5
        if (extension=="h5")
          return HDF5Reader<TContainer, TFunctor>::importHDF5(filename, "image8bit", aFunctor);
#endif

        trace.error() << "Extension " << extension<< " not yet implemented in DGtal GenericReader." << std::endl;
        throw dgtalio;

      }

  };


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/io/readers/GenericReader.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined GenericReader_h

#undef GenericReader_RECURSES
#endif // else defined(GenericReader_RECURSES)
