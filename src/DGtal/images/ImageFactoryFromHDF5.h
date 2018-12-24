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
 * @file ImageFactoryFromHDF5.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/05/16
 *
 * Header file for module ImageFactoryFromHDF5.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageFactoryFromHDF5_RECURSES)
#error Recursive header files inclusion detected in ImageFactoryFromHDF5.h
#else // defined(ImageFactoryFromHDF5_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageFactoryFromHDF5_RECURSES

#if !defined ImageFactoryFromHDF5_h
/** Prevents repeated inclusion of headers. */
#define ImageFactoryFromHDF5_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/base/Alias.h"
#include "DGtal/kernel/CBoundedNumber.h"

#include "hdf5.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class H5DSpecializations
  /**
   * Description of template class 'H5DSpecializations' <p>
   * \brief Aim: implements HDF5 reading and writing for specialized type T.
   *
   * @tparam TImageFactory an image factory type (model of CImageFactory).
   * @tparam T a type.
   */
  template <typename TImageFactory, typename T>
  struct H5DSpecializations
  {
    // ----------------------- Standard services ------------------------------

    typedef TImageFactory ImageFactory;
    typedef typename ImageFactory::OutputImage::Value Value;

    static int H5DreadS(ImageFactory &anImageFactory, hid_t memspace, Value *data_out);
    static int H5DwriteS(ImageFactory &anImageFactory, hid_t memspace, Value *data_in);

  }; // end of class H5DSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // template class H5DSpecializations
  /**
   * Description of template class 'H5DSpecializations' <p>
   * \brief Aim: implements HDF5 reading and writing for specialized type DGtal::uint8_t.
   */
  template <typename TImageFactory>
  struct H5DSpecializations<TImageFactory, DGtal::uint8_t>
  {
    // ----------------------- Standard services ------------------------------

    typedef TImageFactory ImageFactory;
    typedef typename ImageFactory::OutputImage::Value Value;

    static int H5DreadS(ImageFactory &anImageFactory, hid_t memspace, Value *data_out)
    {
      return H5Dread(anImageFactory.dataset, H5T_NATIVE_UINT8, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_out);
    }

    static int H5DwriteS(ImageFactory &anImageFactory, hid_t memspace, Value *data_in)
    {
      return H5Dwrite(anImageFactory.dataset, H5T_NATIVE_UINT8, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_in);
    }

  }; // end of class H5DSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // template class H5DSpecializations
  /**
   * Description of template class 'H5DSpecializations' <p>
   * \brief Aim: implements HDF5 reading and writing for specialized type DGtal::int32_t.
   */
  template <typename TImageFactory>
  struct H5DSpecializations<TImageFactory, DGtal::int32_t>
  {
    // ----------------------- Standard services ------------------------------

    typedef TImageFactory ImageFactory;
    typedef typename ImageFactory::OutputImage::Value Value;

    static int H5DreadS(ImageFactory &anImageFactory, hid_t memspace, Value *data_out)
    {
      return H5Dread(anImageFactory.dataset, H5T_NATIVE_INT32, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_out);
    }

    static int H5DwriteS(ImageFactory &anImageFactory, hid_t memspace, Value *data_in)
    {
      return H5Dwrite(anImageFactory.dataset, H5T_NATIVE_INT32, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_in);
    }

  }; // end of class H5DSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // template class H5DSpecializations
  /**
   * Description of template class 'H5DSpecializations' <p>
   * \brief Aim: implements HDF5 reading and writing for specialized type DGtal::int64_t.
   */
  template <typename TImageFactory>
  struct H5DSpecializations<TImageFactory, DGtal::int64_t>
  {
    // ----------------------- Standard services ------------------------------

    typedef TImageFactory ImageFactory;
    typedef typename ImageFactory::OutputImage::Value Value;

    static int H5DreadS(ImageFactory &anImageFactory, hid_t memspace, Value *data_out)
    {
      return H5Dread(anImageFactory.dataset, H5T_NATIVE_INT64, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_out);
    }

    static int H5DwriteS(ImageFactory &anImageFactory, hid_t memspace, Value *data_in)
    {
      return H5Dwrite(anImageFactory.dataset, H5T_NATIVE_INT64, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_in);
    }

  }; // end of class H5DSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // template class H5DSpecializations
  /**
   * Description of template class 'H5DSpecializations' <p>
   * \brief Aim: implements HDF5 reading and writing for specialized type double.
   */
  template <typename TImageFactory>
  struct H5DSpecializations<TImageFactory, double>
  {
    // ----------------------- Standard services ------------------------------

    typedef TImageFactory ImageFactory;
    typedef typename ImageFactory::OutputImage::Value Value;

    static int H5DreadS(ImageFactory &anImageFactory, hid_t memspace, Value *data_out)
    {
      return H5Dread(anImageFactory.dataset, H5T_NATIVE_DOUBLE, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_out);
    }

    static int H5DwriteS(ImageFactory &anImageFactory, hid_t memspace, Value *data_in)
    {
      return H5Dwrite(anImageFactory.dataset, H5T_NATIVE_DOUBLE, memspace, anImageFactory.dataspace, H5P_DEFAULT, data_in);
    }

  }; // end of class H5DSpecializations

  /////////////////////////////////////////////////////////////////////////////
  // Template class ImageFactoryFromHDF5
  /**
   * Description of template class 'ImageFactoryFromHDF5' <p>
   * \brief Aim: implements a factory from an HDF5 file.
   *
   * @tparam TImageContainer an image container type (model of CImage).
   *
   * The factory images production (images are copied, so it's a creation process) is done with the function 'requestImage'
   * so the deletion must be done with the function 'detachImage'.
   *
   * The update of the original image is done with the function 'flushImage'.
   */
  template <typename TImageContainer>
  class ImageFactoryFromHDF5
  {

    // ----------------------- Types ------------------------------

  public:
    typedef ImageFactoryFromHDF5<TImageContainer> Self;

    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;
    typedef typename ImageContainer::Domain Domain;

    ///New types
    typedef ImageContainer OutputImage;
    typedef typename OutputImage::Value Value;

    BOOST_CONCEPT_ASSERT(( concepts::CBoundedNumber< Value > ));

    // ----------------------- Standard services ------------------------------

  public:

    /**
     * Constructor.
     * @param aFilename HDF5 filename.
     * @param aDataset datasetname.
     */
    ImageFactoryFromHDF5(const std::string & aFilename, const std::string & aDataset):
      myFilename(aFilename), myDataset(aDataset)
    {
      const int ddim = Domain::dimension;

      hsize_t dims_out[ddim];              // dataset dimensions

      // Open the file and the dataset.
      file = H5Fopen(myFilename.c_str(), H5F_ACC_RDWR, H5P_DEFAULT);
      dataset = H5Dopen2(file, myDataset.c_str(), H5P_DEFAULT);

      // Get datatype and dataspace handles and then query dataset class, order, size, rank and dimensions.
      datatype = H5Dget_type(dataset); // datatype handle

      dataspace = H5Dget_space(dataset); // dataspace handle

      H5Sget_simple_extent_dims(dataspace, dims_out, NULL);

      // --

      typedef SpaceND<ddim> TSpace;
      typename TSpace::Point low, up;

      typename Domain::Integer d;
      for(d=0; d<ddim; d++)
      {
        low[d]=0;
        up[d]=dims_out[ddim-d-1]-1;
      }

      myDomain = new Domain(low, up);
    }

    /**
     * Destructor.
     */
    ~ImageFactoryFromHDF5()
    {
      delete myDomain;

      // --

      // Close/release resources.
      H5Tclose(datatype);
      H5Dclose(dataset);
      H5Sclose(dataspace);
      H5Fclose(file);
    }
    
  private:
    
    ImageFactoryFromHDF5( const ImageFactoryFromHDF5 & other );
    
    ImageFactoryFromHDF5 & operator=( const ImageFactoryFromHDF5 & other );

    // ----------------------- Interface --------------------------------------
  public:

    /////////////////// Domains //////////////////

    /**
     * Returns a reference to the underlying image domain.
     *
     * @return a reference to the domain.
     */
    const Domain & domain() const
    {
        return *myDomain;
    }

    /////////////////// Accessors //////////////////


    /////////////////// API //////////////////

    /**
     * Writes/Displays the object on an output stream.
     * @param out the output stream where the object is written.
     */
    void selfDisplay ( std::ostream & out ) const;

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const
    {
      return (myDomain->isValid());
    }

    /**
     * Returns a pointer of an OutputImage created with the Domain aDomain.
     *
     * @param aDomain the domain.
     *
     * @return an ImagePtr.
     */
    OutputImage * requestImage(const Domain &aDomain) // time consuming
    {
      DGtal::IOException dgtalio;
      
      const int ddim = Domain::dimension;

      // --

      hsize_t offset[ddim];        // hyperslab offset in the file
      hsize_t count[ddim];         // size of the hyperslab in the file

      herr_t status;
      hsize_t dimsm[ddim];         // memory space dimensions
      hid_t memspace;

      hsize_t offset_out[ddim];    // hyperslab offset in memory
      hsize_t count_out[ddim];     // size of the hyperslab in memory

      int N_SUB[ddim];
      typename Domain::Integer d;

      int malloc_size=1;
      for(d=0; d<ddim; d++)
      {
        N_SUB[d] = (aDomain.upperBound()[ddim-d-1]-aDomain.lowerBound()[ddim-d-1])+1;
        malloc_size = malloc_size*N_SUB[d];
      }

      Value *data_out = (Value*) malloc (malloc_size * sizeof(Value)); // output buffer
      if (data_out == NULL)
      {
        trace.error() << "data_out malloc error in requestImage: " << (malloc_size * sizeof(Value)) << std::endl;
        throw dgtalio;
      }

      // Define hyperslab in the dataset.
      for(d=0; d<ddim; d++)
        offset[d] = aDomain.lowerBound()[ddim-d-1]-myDomain->lowerBound()[ddim-d-1];
      for(d=0; d<ddim; d++)
        count[d] = N_SUB[d];
      status = H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);
      if (status)
      {
        trace.error() << " H5Sselect_hyperslab from dataspace error" << std::endl;
        throw dgtalio;
      }

      // Define the memory dataspace.
      for(d=0; d<ddim; d++)
        dimsm[d] = N_SUB[d];
      memspace = H5Screate_simple(ddim,dimsm,NULL);

      // Define memory hyperslab.
      for(d=0; d<ddim; d++)
        offset_out[d] = 0;
      for(d=0; d<ddim; d++)
        count_out[d] = N_SUB[d];
      status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_out, NULL, count_out, NULL);
      if (status)
      {
        trace.error() << " H5Sselect_hyperslab from memspace error" << std::endl;
        throw dgtalio;
      }

      // Read data from hyperslab in the file into the hyperslab in memory.
      //status = H5Dread(dataset, H5T_NATIVE_INT, memspace, dataspace, H5P_DEFAULT, data_out);
      status = H5DSpecializations<Self, Value>::H5DreadS(*this, memspace, data_out);
      if (status)
      {
        trace.error() << " H5DSpecializations/H5DreadS error" << std::endl;
        throw dgtalio;
      }

      OutputImage* outputImage = new OutputImage(aDomain);
      if (outputImage == NULL)
      {
        trace.error() << "outputImage new error in requestImage: " << std::endl;
        throw dgtalio;
      }

      typedef SpaceND<ddim> TSpace;
      typename TSpace::Point a, b;
      for(d=0; d<ddim; d++)
      {
        a[d]=offset[ddim-d-1]+myDomain->lowerBound()[d];
        b[d]=a[d]+N_SUB[ddim-d-1]-1;
      }
      HyperRectDomain<TSpace> hrdomain(a,b);

      int p=0;
      for( typename HyperRectDomain<TSpace>::ConstIterator
            it = hrdomain.begin(), itend = hrdomain.end();
          it != itend;
          ++it)
      {
        outputImage->setValue((*it), data_out[ p++ ]);
      }

      H5Sclose(memspace);

      // --

      free(data_out);

      return outputImage;
    }

    /**
     * Flush (i.e. write/synchronize) an OutputImage.
     *
     * @param outputImage the OutputImage.
     */
    void flushImage(OutputImage* outputImage)
    {
      DGtal::IOException dgtalio;
      
      const int ddim = Domain::dimension;

      // --

      hsize_t offset[ddim];        // hyperslab offset in the file
      hsize_t count[ddim];         // size of the hyperslab in the file

      herr_t status;
      hsize_t dimsm[ddim];         // memory space dimensions
      hid_t memspace;

      hsize_t offset_in[ddim];    // hyperslab offset in memory
      hsize_t count_in[ddim];     // size of the hyperslab in memory

      //int i[ddim];
      int N_SUB[ddim];
      typename Domain::Integer d;

      int malloc_size=1;
      for(d=0; d<ddim; d++)
      {
        N_SUB[d] = (outputImage->domain().upperBound()[ddim-d-1]-outputImage->domain().lowerBound()[ddim-d-1])+1;
        malloc_size = malloc_size*N_SUB[d];
      }

      Value *data_in = (Value*) malloc (malloc_size * sizeof(Value)); // input buffer
      if (data_in == NULL)
      {
        trace.error() << "data_in malloc error in flushImage: " << (malloc_size * sizeof(Value)) << std::endl;
        throw dgtalio;
      }

      // Define hyperslab in the dataset.
      for(d=0; d<ddim; d++)
        offset[d] = outputImage->domain().lowerBound()[ddim-d-1]-myDomain->lowerBound()[ddim-d-1];
      for(d=0; d<ddim; d++)
        count[d] = N_SUB[d];
      status = H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);
      if (status)
      {
        trace.error() << " H5Sselect_hyperslab from dataspace error" << std::endl;
        throw dgtalio;
      }

      // Define the memory dataspace.
      for(d=0; d<ddim; d++)
        dimsm[d] = N_SUB[d];
      memspace = H5Screate_simple(ddim,dimsm,NULL);

      // Define memory hyperslab.
      for(d=0; d<ddim; d++)
        offset_in[d] = 0;
      for(d=0; d<ddim; d++)
        count_in[d] = N_SUB[d];
      status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_in, NULL, count_in, NULL);
      if (status)
      {
        trace.error() << " H5Sselect_hyperslab from memspace error" << std::endl;
        throw dgtalio;
      }

      typedef SpaceND<ddim> TSpace;
      typename TSpace::Point a, b;
      for(d=0; d<ddim; d++)
      {
        a[d]=offset[ddim-d-1]+myDomain->lowerBound()[d];
        b[d]=a[d]+N_SUB[ddim-d-1]-1;
      }
      HyperRectDomain<TSpace> hrdomain(a,b);

      std::vector<typename TSpace::Dimension> v(ddim);
      for(d=0; d<ddim; d++)
        v[d]=d;

      int p=0;
      for( typename HyperRectDomain<TSpace>::ConstSubRange::ConstIterator
            it = hrdomain.subRange(v, a).begin(), itend = hrdomain.subRange(v, a).end();
          it != itend;
          ++it)
      {
        data_in[ p++ ] = outputImage->operator()((*it));
      }

      // Write data from hyperslab in memory into the hyperslab in the file.
      //status = H5Dwrite(dataset, H5T_NATIVE_INT, memspace, dataspace, H5P_DEFAULT, data_in);
      status = H5DSpecializations<Self, Value>::H5DwriteS(*this, memspace, data_in);
      if (status)
      {
        trace.error() << " H5DSpecializations/H5DwriteS error" << std::endl;
        throw dgtalio;
      }

      H5Sclose(memspace);

      // --

      free(data_in);
    }

    /**
     * Free (i.e. delete) an OutputImage.
     *
     * @param outputImage the OutputImage.
     */
    void detachImage(OutputImage* outputImage)
    {
      delete outputImage;
    }

    // ------------------------- Protected Datas ------------------------------
  private:
    /**
     * Default constructor.
     */
    //ImageFactoryFromHDF5() {}

    // ------------------------- Private Datas --------------------------------
  protected:

    /// Alias on the image domain
    Domain *myDomain;

    /// HDF5 filename and datasetname
    const std::string myFilename;
    const std::string myDataset;

  public:

    // HDF5 handles
    hid_t file, dataset;
    hid_t datatype, dataspace;

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ImageFactoryFromHDF5


  /**
   * Overloads 'operator<<' for displaying objects of class 'ImageFactoryFromHDF5'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImageFactoryFromHDF5' to write.
   * @return the output stream after the writing.
   */
  template <typename TImageContainer>
  std::ostream&
  operator<< ( std::ostream & out, const ImageFactoryFromHDF5<TImageContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageFactoryFromHDF5.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageFactoryFromHDF5_h

#undef ImageFactoryFromHDF5_RECURSES
#endif // else defined(ImageFactoryFromHDF5_RECURSES)
