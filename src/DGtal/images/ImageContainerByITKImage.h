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
 * @file ImageContainerByITKImage.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * @author Pierre Gueth (\c pierre.gueth@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/10/23
 *
 * Header file for module ImageContainerByITKImage.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageContainerByITKImage_RECURSES)
#error Recursive header files inclusion detected in ImageContainerByITKImage.h
#else // defined(ImageContainerByITKImage_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageContainerByITKImage_RECURSES

#if !defined ImageContainerByITKImage_h
/** Prevents repeated inclusion of headers. */
#define ImageContainerByITKImage_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/Common.h"
#include "DGtal/base/CLabel.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/images/DefaultConstImageRange.h"
#include "DGtal/images/DefaultImageRange.h"

#if defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#endif
#include <itkImage.h>
#include <itkImageRegionConstIterator.h>
#include <itkImageRegionIterator.h>
#include <iostream>
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#if defined(__GNUG__)
#endif
#pragma GCC diagnostic pop
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

    /////////////////////////////////////////////////////////////////////////////
    // template class ImageContainerByITKImage
    /**
     * Description of template class 'ImageContainerByITKImage' <p>
     * \brief Aim: implements a model of CImageContainer using a ITK Image.
     *
     * Using this container, you can switch from DGtal alogrithms to
     * ITK processing pipeline.
     * The Ownership of the underlying ITK image is shared between the wrapper
     * and the ITK pipeline.
     * If the ITK image region is modified, one should manually update the domain of the wrapper.
     * This is done by calling the updateDomain() method.
     *
     * \see testITKImage.cpp
     */
    template <typename TDomain, typename TValue>
    class ImageContainerByITKImage
    {
      // ----------------------- Standard services ------------------------------
    public:

      BOOST_CONCEPT_ASSERT(( concepts::CLabel<TValue> ));
      BOOST_CONCEPT_ASSERT(( concepts::CDomain<TDomain> ));

      typedef TValue Value;
      typedef TDomain Domain;
      typedef ImageContainerByITKImage<TDomain, TValue> Self;

      // static constants
      static const typename Domain::Dimension dimension = Domain::dimension;

      typedef typename Domain::Point Point;
      typedef typename Domain::Vector Vector;
      typedef typename Domain::Dimension Dimension;
      typedef typename Domain::Integer Integer;
      typedef typename Domain::Size Size;
      typedef Point Vertex;

      typedef typename itk::Image< TValue, dimension> ITKImage;
      typedef typename ITKImage::Pointer ITKImagePointer;
      typedef typename itk::ImageRegionConstIterator< ITKImage > ConstIterator;
      typedef typename itk::ImageRegionIterator< ITKImage > Iterator;

      typedef DefaultConstImageRange<Self> ConstRange;
      typedef DefaultImageRange<Self> Range;

      /**
       * Constructor.
       *
       * @param aDomain the image domain.
       */
      ImageContainerByITKImage(const Domain& aDomain);

      /**
       * Constructor.
       *
       * @param aRef a reference to an ITKImage
       */
      ImageContainerByITKImage(const ITKImagePointer &aRef);

      /**
       * Copy constructor
       *
       * @param other the object to copy.
       *
       */
      ImageContainerByITKImage(const ImageContainerByITKImage& other);

      /**
       * Assignment.
       *
       * @param other the object to copy.
       * @return a reference on 'this'.
       */
      ImageContainerByITKImage & operator=(const ImageContainerByITKImage & other);

      /**
       * Destructor.
       */
      ~ImageContainerByITKImage();

      // ----------------------- Interface --------------------------------------
    public:

      /**
       *
       * update internal domain cache.
       * should be called after modifying underlying ITK image.
       *
       */
      void updateDomain();

      /**
       * @return the range providing begin and end
       * iterators to scan the values of image.
       */
      ConstRange constRange() const
      {
          return ConstRange(*this);
      }

      /**
       * @return the range providing begin and end
       * iterators to scan the values of image.
       */
      Range range()
      {
          return Range(*this);
      }

      /**
       * Get the value of an image at a given position.
       *
       * @param aPoint  position in the image.
       * @return the value at aPoint.
       */
      Value operator()(const Point &aPoint) const;

      /**
       * Get the value of an image at a given position.
       *
       * @param it  position in the image.
       * @return the value at aPoint.
       */
      Value operator()(const ConstIterator &it) const;

      /**
       * Get the value of an image at a given position.
       *
       * @param it  position in the image.
       * @return the value at aPoint.
       */
      Value operator()(const Iterator &it) const;

      /**
       * Set a value on an Image at aPoint.
       *
       * @param aPoint location of the point to associate with aValue.
       * @param aValue the value.
       */
      void setValue(const Point &aPoint, const Value &aValue);

      /**
       * Set a value on an Image at aPoint.
       *
       * @param it location of the point (Iterator) to associate with aValue.
       * @param V the value.
       */
      void setValue(Iterator &it, const Value &V);

      // ------------------------- methods ------------------------------


      /**
       * @return the domain associated to the image.
       */
      const Domain& domain() const
      {
          return myDomain;
      }

      /**
       * Returns a copy of the itkImage smartPointer
       */
      inline
      ITKImagePointer getITKImagePointer() const
      {
          return myITKImagePointer;
      }

      // ------------------------- stream ------------------------------

      /**
       * Writes/Displays the object on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const;

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const;

      // ------------------------- Iterators ------------------------------
      /**
       * begin() const iterator.
       *
       **/
      inline
      ConstIterator begin() const
      {
          ConstIterator iter = ConstIterator(myITKImagePointer, myITKImagePointer->GetLargestPossibleRegion());
          iter.GoToBegin();
          return iter;
      }

      /**
       * begin() const iterator.
       *
       **/
      inline
      Iterator begin()
      {
          Iterator iter = Iterator(myITKImagePointer, myITKImagePointer->GetLargestPossibleRegion());
          iter.GoToBegin();
          return iter;
      }

      /**
       * end() const iterator.
       *
       **/
      inline
      const ConstIterator end() const
      {
          ConstIterator iter = ConstIterator(myITKImagePointer, myITKImagePointer->GetLargestPossibleRegion());
          iter.GoToEnd();
          return iter;
      }

      /**
       * end()  iterator.
       *
       **/
      inline
      Iterator end()
      {
          Iterator iter = Iterator(myITKImagePointer, myITKImagePointer->GetLargestPossibleRegion());
          iter.GoToEnd();
          return iter;
      }

      // ------------------------- Private Datas --------------------------------
    private:

      // ------------------------- Hidden services ------------------------------
    protected:

      /**
       * Constructor.
       * Forbidden by default (protected to avoid g++ warnings).
       */
      ImageContainerByITKImage();

      // ------------------------- Internals ------------------------------------
    private:

      ITKImagePointer myITKImagePointer;
      Domain myDomain; // cached from myITKImagePointer region. updated when calling update().
    }; // end of class ImageContainerByITKImage

  /**
   * Overloads 'operator<<' for displaying objects of class 'ImageContainerByITKImage'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImageContainerByITKImage' to write.
   * @return the output stream after the writing.
   */
  template <typename T, typename TV>
  std::ostream&
  operator<< ( std::ostream & out, const ImageContainerByITKImage<T, TV> & object );

}
///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageContainerByITKImage.ih"

//
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageContainerByITKImage_h

#undef ImageContainerByITKImage_RECURSES
#endif // else defined(ImageContainerByITKImage_RECURSES)
