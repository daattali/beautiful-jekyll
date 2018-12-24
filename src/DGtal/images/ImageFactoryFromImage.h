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
 * @file ImageFactoryFromImage.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/23
 *
 * Header file for module ImageFactoryFromImage.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageFactoryFromImage_RECURSES)
#error Recursive header files inclusion detected in ImageFactoryFromImage.h
#else // defined(ImageFactoryFromImage_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageFactoryFromImage_RECURSES

#if !defined ImageFactoryFromImage_h
/** Prevents repeated inclusion of headers. */
#define ImageFactoryFromImage_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/base/Alias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // Template class ImageFactoryFromImage
  /**
   * Description of template class 'ImageFactoryFromImage' <p>
   * \brief Aim: implements a factory to produce images from a "bigger/original" one according to a given domain.
   * 
   * @tparam TImageContainer an image container type (model of CImage).
   * 
   * The factory images production (images are copied, so it's a creation process) is done with the function 'requestImage'
   * so the deletion must be done with the function 'detachImage'.
   * 
   * The update of the original image is done with the function 'flushImage'.
   */
  template <typename TImageContainer>
  class ImageFactoryFromImage
  {

    // ----------------------- Types ------------------------------

  public:
    typedef ImageFactoryFromImage<TImageContainer> Self; 
    
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;
    typedef typename ImageContainer::Domain Domain;
    
    ///New types
    typedef ImageContainer OutputImage;

    // ----------------------- Standard services ------------------------------

  public:

    /**
     * Constructor.
     * @param anImage alias on the underlying image container.
     */
    ImageFactoryFromImage(Alias<ImageContainer> anImage):
      myImagePtr(&anImage)
    {
    }

    /**
     * Destructor.
     * Does nothing
     */
    ~ImageFactoryFromImage() {}
    
  private:
    
    ImageFactoryFromImage( const ImageFactoryFromImage & other );
    
    ImageFactoryFromImage & operator=( const ImageFactoryFromImage & other );

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
        return myImagePtr->domain();
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
      return (myImagePtr->isValid());
    }

    /**
     * Returns a pointer of an OutputImage created with the Domain aDomain.
     * 
     * @param aDomain the domain.
     * 
     * @return an ImagePtr.
     */
    OutputImage * requestImage(const Domain &aDomain)
    {
      OutputImage* outputImage = new OutputImage(aDomain);
      
      typename Domain::Iterator it = outputImage->domain().begin();
      typename Domain::Iterator it_end = outputImage->domain().end();
      for (; it != it_end; ++it)
      {
        outputImage->setValue(*it, (*myImagePtr)(*it));
      }
        
      return outputImage;
    }
    
    /**
     * Flush (i.e. write/synchronize) an OutputImage.
     * 
     * @param outputImage the OutputImage.
     */
    void flushImage(OutputImage* outputImage)
    {
      typename Domain::Iterator it = outputImage->domain().begin();
      typename Domain::Iterator it_end = outputImage->domain().end();
      for (; it != it_end; ++it)
      {
        myImagePtr->setValue(*it, (*outputImage)(*it));
      }
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
    //ImageFactoryFromImage() {}
    
    // ------------------------- Private Datas --------------------------------
  protected:

    /// Alias on the image container
    ImageContainer * myImagePtr;

    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class ImageFactoryFromImage


  /**
   * Overloads 'operator<<' for displaying objects of class 'ImageFactoryFromImage'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ImageFactoryFromImage' to write.
   * @return the output stream after the writing.
   */
  template <typename TImageContainer>
  std::ostream&
  operator<< ( std::ostream & out, const ImageFactoryFromImage<TImageContainer> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageFactoryFromImage.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageFactoryFromImage_h

#undef ImageFactoryFromImage_RECURSES
#endif // else defined(ImageFactoryFromImage_RECURSES)
