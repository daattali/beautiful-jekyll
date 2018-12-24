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
 * @file DefaultImageRange.h
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/02/06
 *
 *
 * Header file for module DefaultImageRange.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(DefaultImageRange_RECURSES)
#error Recursive header files inclusion detected in DefaultImageRange.h
#else // defined(DefaultImageRange_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DefaultImageRange_RECURSES

#if !defined DefaultImageRange_h
/** Prevents repeated inclusion of headers. */
#define DefaultImageRange_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/ConstIteratorAdapter.h"
#include "DGtal/kernel/domains/CDomain.h"
#include "DGtal/images/CTrivialImage.h"
#include "DGtal/images/SetValueIterator.h"
#include "boost/concept_check.hpp"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal 
{


  ///////////////////////////////////////////////////////////////////////////////
  // class DefaultImageRange
  ///////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Aim: model of CConstBidirectionalRangeFromPoint and 
   * CBidirectionalRangeWithWritableIteratorFromPoint that adapts the domain 
   * of an image in order to iterate over the values associated
   * to its domain points
   * (in a read-only as well as a write-only manner).  
   *
   * @tparam TImage a model of CImage mapping points to values
   *
   * NB: the underlying image is stored as an aliasing pointer
   * in order to avoid copies. As a consequence the pointed object must exist 
   * and must not be deleted during the use of any instance of this class.
   *
   * TODO: inherits from DefaultConstImageRange
   */
  template <typename TImage>
  class DefaultImageRange
  {


    // ------------------------- inner types --------------------------------
  public: 
  
    BOOST_CONCEPT_ASSERT(( concepts::CTrivialImage<TImage> ));
    typedef typename TImage::Domain Domain; 
    typedef typename TImage::Point Point; 
    typedef typename TImage::Value Value; 

    /// constant iterator types 
    BOOST_CONCEPT_ASSERT(( concepts::CDomain<Domain> )); 
    typedef ConstIteratorAdapter<typename Domain::ConstIterator,TImage,Value> ConstIterator; 
    typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

    /// output iterator types
    typedef SetValueIterator<TImage> OutputIterator;
    typedef SetValueIterator<TImage, typename Domain::ConstReverseIterator> ReverseOutputIterator;

    // ------------------------- standard services --------------------------------

    /**
     * Standard constructor from an image.
     * @param aImage any image.
     *
     */
    DefaultImageRange( TImage& aImage )
      : myImagePtr(&aImage) {}

    /**
     * Copy constructor.
     * @param other the iterator to clone.
     */
    DefaultImageRange( const DefaultImageRange & other )
      : myImagePtr(other.myImagePtr) {}
  
    /**
     * Assignment.
     * @param other the iterator to copy.
     * @return a reference on 'this'.
     */
    DefaultImageRange& operator= ( const DefaultImageRange & other )
    {  
      if ( this != &other )
	{
	  myImagePtr = other.myImagePtr;
	}
      return *this;
    }

    /**
     * Destructor. Does nothing.
     */
    ~DefaultImageRange() {}

    /**
     * Checks the validity/consistency of the object.
     * @return 'true' if the object is valid, 'false' otherwise.
     */
    bool isValid() const { return true; }
  
  

    // ------------------------- private data --------------------------------
  private: 
    /**
     * Aliasing pointer on the underlying image
     */
    TImage* myImagePtr; 

    // ------------------------- iterator services (read-only) --------------------------------
  public:

    /**
     * Iterator service.
     * @return begin iterator
     */
    ConstIterator begin() const {
      Domain d = myImagePtr->domain(); 
      return ConstIterator( d.begin(), *myImagePtr );
    }

    /**
     * Iterator service.
     * @param aPoint any point
     * @return begin iterator
     */
    ConstIterator begin(const Point& aPoint) const {
      Domain d = myImagePtr->domain(); 
      return ConstIterator( d.begin(aPoint), *myImagePtr );
    }

    /**
     * Iterator service.
     * @return end iterator
     */
    ConstIterator end() const {
      Domain d = myImagePtr->domain(); 
      return ConstIterator( d.end(), *myImagePtr );
    }

    /**
     * Iterator service.
     * @return rbegin iterator
     */
    ConstReverseIterator rbegin() const {
      return ConstReverseIterator(this->end());
    }

    /**
     * Iterator service.
     * @param aPoint any point
     * @return rbegin iterator
     */
    ConstReverseIterator rbegin(const Point& aPoint) const {
      Domain d = myImagePtr->domain(); 
      typename Domain::ConstIterator itOnPts = d.begin(aPoint); 
      if ( itOnPts != d.end() ) ++itOnPts; 
      ConstIterator itOnVals( itOnPts, *myImagePtr );
      return ConstReverseIterator( itOnVals );
    }

    /**
     * Iterator service.
     * @return rend iterator
     */
    ConstReverseIterator rend() const {
      return ConstReverseIterator(this->begin());
    }

    // ------------------------- iterator services (write-only) --------------------------------
  public: 
    /**
     * Iterator service.
     * @return output iterator
     */
    OutputIterator outputIterator() const {
      Domain d = myImagePtr->domain(); 
      return OutputIterator( d.begin(), *myImagePtr );
    }

    /**
     * Iterator service.
     * @param aPoint any point
     * @return output iterator
     */
    OutputIterator outputIterator(const Point& aPoint) const {
      Domain d = myImagePtr->domain(); 
      return OutputIterator( d.begin(aPoint), *myImagePtr );
    }

    /**
     * Iterator service.
     * @return reverse output iterator
     */
    ReverseOutputIterator routputIterator() const {
      Domain d = myImagePtr->domain();
      return ReverseOutputIterator( d.rbegin(), *myImagePtr );
    }

    /**
     * Iterator service.
     * @param aPoint any point
     * @return reverse output iterator
     */
    ReverseOutputIterator routputIterator(const Point& aPoint) const {
      Domain d = myImagePtr->domain();
      return ReverseOutputIterator( d.rbegin(aPoint), *myImagePtr );
    }

  }; //end class DefaultImageRange

} // namespace DGtal

  ///////////////////////////////////////////////////////////////////////////////


#endif // !defined DefaultImageRange_h

#undef DefaultImageRange_RECURSES
#endif // else defined(DefaultImageRange_RECURSES)
