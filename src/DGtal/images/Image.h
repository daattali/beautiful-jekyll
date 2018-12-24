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
 * @file Image.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2012/02/07
 *
 * Header file for module Image.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(Image_RECURSES)
#error Recursive header files inclusion detected in Image.h
#else // defined(Image_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Image_RECURSES

#if !defined Image_h
/** Prevents repeated inclusion of headers. */
#define Image_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/base/CowPtr.h"
#include "DGtal/graph/CVertexMap.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // Template class Image
  /**
   * Description of template class 'Image' <p>
   * \brief Aim: implements association bewteen points lying in a
   * digital domain and values.
   *
   * This class is a lightweight proxy on ImageContainers (models of
   * CImage). Image class is also a model of CImage.
   *
   * @tparam TImageContainer an image container type (model of CImage).
   *
   *
   */
  template < typename TImageContainer >
  class Image
  {

    // ----------------------- Types ------------------------------

  public:

    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CVertexMap<TImageContainer> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain Domain;
    typedef typename TImageContainer::Point Point;
    typedef typename TImageContainer::Value Value;
    typedef typename TImageContainer::ConstRange ConstRange;
    typedef typename TImageContainer::Range Range;
    typedef typename TImageContainer::OutputIterator OutputIterator;

    ///Pointer to the image container data.
    typedef CowPtr<TImageContainer> ImagePointer;

    // ----------------------- Standard services ------------------------------

  public:

    /**
     * Default constructor.
     */
    Image() {
#ifdef DEBUG_VERBOSE
trace.warning() << "Image Ctor default "<<std::endl;
#endif

    };

    /**
     * Constructor from a pointer on the underlying image container.
     * (data pointer is acquired, ownership transfer)
     */
    Image(ImageContainer *anImageContainer):
      myImagePointer(anImageContainer)
    {
#ifdef DEBUG_VERBOSE
    trace.warning() << "Image Ctor fromPointer "<<std::endl;
#endif
    }

    /**
     * Constructor from Copy on write pointer.
     * (data is not copied if read-only)
     * @param anImageContainerCowPointer a COW-pointer on the underlying container.
     */
    Image(const CowPtr<ImageContainer> &anImageContainerCowPointer):
      myImagePointer(anImageContainerCowPointer)
    {
      #ifdef DEBUG_VERBOSE
trace.warning() << "Image Ctor fromCow  "<<std::endl;
#endif
    }

    /**
     * Constructor from ImageContainer const reference
     * (data is duplicated).
     * @param other an object of same type to copy.
     */
   Image(const ImageContainer &other):
      myImagePointer(new ImageContainer(other) )
      {
#ifdef DEBUG_VERBOSE
trace.warning() << "Image Ctor fromConstRef "<<std::endl;
#endif
      }


   /**
     * Copy Constructor
     * (data is not copied here).
     * @param other an object of same type to copy.
     */
   Image(const Image &other):
      myImagePointer(other.myImagePointer )
      {
          #ifdef DEBUG_VERBOSE
trace.warning() << "Image copy Ctor  "<<std::endl;
#endif
      }

      /**
     * Assignment.
     * @param other the object to copy.
     * @return a reference on 'this'.
     */
    Image & operator= ( const Image & other )
    {
      #ifdef DEBUG_VERBOSE
 trace.warning() << "Image assignment "<<std::endl;
#endif
      if (&other != this)
	{
	  myImagePointer = other.myImagePointer;
	}
      return *this;
    }


    /**
     * Destructor.
     * Does nothing, the cow pointer takes care of everything
     */
    ~Image() {}

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
      return myImagePointer->domain();
    }

    /**
     * Returns the range of the underlying image
     * to iterate over its values
     *
     * @return a range.
     */
    ConstRange constRange() const
    {
      return myImagePointer->constRange();
    }

    /**
     * Returns the range of the underlying image
     * to iterate over its values
     *
     * @return a range.
     */
    Range range()
    {
      return myImagePointer->range();
    }

    /////////////////// Accessors //////////////////


    /**
     * Get the value of an image at a given position given
     * by a Point.
     *
     * @pre the point must be in the domain
     *
     * @param aPoint the point.
     * @return the value at aPoint.
     */
    Value operator()(const Point & aPoint) const
    {
      return myImagePointer->operator()(aPoint);
    }


    /////////////////// Set values //////////////////

    /**
     * Set a value on an Image at a position specified by a Point.
     *
     * @pre @c it must be a point in the image domain.
     *
     * @param aPoint the point.
     * @param aValue the value.
     */
    void setValue(const Point &aPoint, const Value &aValue)
    {
      myImagePointer->setValue(aPoint,aValue);
    }



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
      return (myImagePointer->isValid() );
    }


    /**
     * Returns the smart pointer on the Image container data.
     * @return a const ImagePointer.
     */
    const ImagePointer getPointer() const
    {
      return myImagePointer;
    }

    // ------------------------- Protected Datas ------------------------------
  private:
    // ------------------------- Private Datas --------------------------------
  protected:

    /// Owning smart pointer on the image container
    ImagePointer myImagePointer;


  private:


    // ------------------------- Internals ------------------------------------
  private:

  }; // end of class Image


  /**
   * Overloads 'operator<<' for displaying objects of class 'Image'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'Image' to write.
   * @return the output stream after the writing.
   */
  template <typename T>
  std::ostream&
  operator<< ( std::ostream & out, const Image<T> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/Image.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Image_h

#undef Image_RECURSES
#endif // else defined(Image_RECURSES)
