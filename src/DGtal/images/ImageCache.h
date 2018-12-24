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
 * @file ImageCache.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/24
 *
 * Header file for module ImageCache.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageCache_RECURSES)
#error Recursive header files inclusion detected in ImageCache.h
#else // defined(ImageCache_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageCache_RECURSES

#if !defined ImageCache_h
/** Prevents repeated inclusion of headers. */
#define ImageCache_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/CImageFactory.h"
#include "DGtal/images/CImageCacheReadPolicy.h"
#include "DGtal/images/CImageCacheWritePolicy.h"
#include "DGtal/base/Alias.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{   

// CACHE_READ_POLICY_LAST, CACHE_READ_POLICY_FIFO, CACHE_READ_POLICY_LRU, CACHE_READ_POLICY_NEIGHBORS   // read policies
// CACHE_WRITE_POLICY_WT, CACHE_WRITE_POLICY_WB                                                         // write policies
    
/////////////////////////////////////////////////////////////////////////////
// Template class ImageCache
/**
 * Description of template class 'ImageCache' <p>
 * \brief Aim: implements an images cache with 'read and write' policies.
 * 
 * @tparam TImageContainer an image container type (model of CImage).
 * @tparam TImageFactory an image factory type (model of CImageFactory).
 * @tparam TReadPolicy an image cache read policy class (model of CImageCacheReadPolicy).
 * @tparam TWritePolicy an image cache write policy class (model of CImageCacheWritePolicy).
 * 
 * The cache provides 3 functions:
 * 
 *  - read :    for getting the value of an image from cache at a given position given by a point only if that point belongs to an image from cache
 *  - write :   for setting a   value on an image from cache at a given position given by a point only if that point belongs to an image from cache
 *  - update :  for updating the cache according to the read cache policy
 */
template <typename TImageContainer, typename TImageFactory, typename TReadPolicy, typename TWritePolicy>
class ImageCache
{

    // ----------------------- Types ------------------------------

public:
    typedef ImageCache<TImageContainer, TImageFactory, TReadPolicy, TWritePolicy> Self; 
    
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageFactory<TImageFactory> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageCacheReadPolicy<TReadPolicy> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageCacheWritePolicy<TWritePolicy> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;
    typedef typename ImageContainer::Domain Domain;
    typedef typename ImageContainer::Point Point;
    typedef typename ImageContainer::Value Value;
    
    typedef TImageFactory ImageFactory;
    
    typedef TReadPolicy ReadPolicy;
    typedef TWritePolicy WritePolicy;

    // ----------------------- Standard services ------------------------------

public:
  
    /**
     * Constructor.
     * @param anImageFactory alias on the image factory (see ImageFactoryFromImage or ImageFactoryFromHDF5).
     * @param aReadPolicy a read policy.
     * @param aWritePolicy a write policy.
     */
    ImageCache(Alias<ImageFactory> anImageFactory, Alias<ReadPolicy> aReadPolicy, Alias<WritePolicy> aWritePolicy):
      myImageFactoryPtr(&anImageFactory), myReadPolicy(&aReadPolicy), myWritePolicy(&aWritePolicy)
    {
      myReadPolicy->clearCache();
      
      cacheMissRead = 0;
      cacheMissWrite = 0;
    }
    
    /**
     * Destructor.
     * Does nothing
     */
    ~ImageCache()
    {
    }
    
private:
    
    ImageCache( const ImageCache & other );
        
    ImageCache & operator=( const ImageCache & other );

    // ----------------------- Interface --------------------------------------
public:

    /////////////////// Domains //////////////////


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
        return (myImageFactoryPtr->isValid());
    }
    
    /**
    * Get the value of an image from cache at a given position given
    * by aPoint only if aPoint belongs to an image from cache.
    *
    * @param aPoint the point.
    * @param aValue the value returned.
    * 
    * @return 'true' if aPoint belongs to an image from cache, 'false' otherwise.
    */
    bool read(const Point & aPoint, Value &aValue) const;
    
    /**
     * Get the alias on the image that matchs the domain aDomain
     * or NULL if no image in the cache matchs the domain aDomain.
     * 
     * @param aDomain the domain.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPage(const Domain & aDomain) const;

    /**
     * Set a value on an image from cache at a given position given
     * by aPoint only if aPoint belongs to an image from cache.
     *
     * @param aPoint the point.
     * @param aValue the value returned.
     * 
     * @return 'true' if aPoint belongs to an image from cache, 'false' otherwise.
     */
    bool write(const Point & aPoint, const Value &aValue);
    
    /**
     * Update the cache according to the read cache policy.
     * 
     * @param aDomain the domain.
     */
    void update(const Domain &aDomain);
    
    /**
     * Get the cacheMissRead value.
     */
    unsigned int getCacheMissRead()
    {
        return cacheMissRead;
    }
    
    /**
     * Get the cacheMissWrite value.
     */
    unsigned int getCacheMissWrite()
    {
        return cacheMissWrite;
    }
    
    /**
     * Inc the cacheMissRead value.
     */
    void incCacheMissRead()
    {
        cacheMissRead++;
    }
    
    /**
     * Inc the cacheMissWrite value.
     */
    void incCacheMissWrite()
    {
        cacheMissWrite++;
    }
    
    /**
     * Clear the cache and reset the cache misses
     */
    void clearCacheAndResetCacheMisses()
    {
      myReadPolicy->clearCache();
      
      cacheMissRead = 0;
      cacheMissWrite = 0;
    }

    // ------------------------- Protected Datas ------------------------------
private:
    /**
     * Default constructor.
     */
    //ImageCache() {}
    
    // ------------------------- Private Datas --------------------------------
protected:

    /// Alias on the image factory
    ImageFactory * myImageFactoryPtr;
    
    /// Specialized caches
    ReadPolicy * myReadPolicy;
    WritePolicy * myWritePolicy;
    
private:
    
    /// cache miss values
    unsigned int cacheMissRead;
    unsigned int cacheMissWrite;

    // ------------------------- Internals ------------------------------------
private:

}; // end of class ImageCache


/**
 * Overloads 'operator<<' for displaying objects of class 'ImageCache'.
 * @param out the output stream where the object is written.
 * @param object the object of class 'ImageCache' to write.
 * @return the output stream after the writing.
 */
template <typename TImageContainer, typename TImageFactory, typename TReadPolicy, typename TWritePolicy>
std::ostream&
operator<< ( std::ostream & out, const ImageCache<TImageContainer, TImageFactory, TReadPolicy, TWritePolicy> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageCachePolicies.h"
#include "DGtal/images/ImageCache.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageCache_h

#undef ImageCache_RECURSES
#endif // else defined(ImageCache_RECURSES)
