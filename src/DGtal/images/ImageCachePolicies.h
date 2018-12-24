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
 * @file ImageCachePolicies.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/02/06
 *
 * Header file for module ImageCachePolicies.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(ImageCachePolicies_RECURSES)
#error Recursive header files inclusion detected in ImageCachePolicies.h
#else // defined(ImageCachePolicies_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ImageCachePolicies_RECURSES

#if !defined ImageCachePolicies_h
/** Prevents repeated inclusion of headers. */
#define ImageCachePolicies_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/ConceptUtils.h"
#include "DGtal/images/CImage.h"
#include "DGtal/images/CImageFactory.h"
#include "DGtal/base/Alias.h"

#include "DGtal/images/ImageCache.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

/////////////////////////////////////////////////////////////////////////////
// Template class ImageCacheReadPolicyLAST
/**
 * Description of template class 'ImageCacheReadPolicyLAST' <p>
 * \brief Aim: implements a 'LAST' read policy cache.
 * 
 * The cache keeps only one page in memory, the last one. 
 * When the page needs to be replaced, the new page replaces the old one.
 * 
 * @tparam TImageContainer an image container type (model of CImage).
 * @tparam TImageFactory an image factory.
 * 
 * The policy is done with 5 functions:
 * 
 *  - getPage :                 for getting the alias on the image that contains a point or NULL if no image in the cache contains that point
 *  - getPage :                 for getting the alias on the image that contains a domain or NULL if no image in the cache contains that domain
 *  - getPageToDetach :         for getting the alias on the image that we have to detach or NULL if no image have to be detached
 *  - updateCache :             for updating the cache according to the cache policy
 *  - clearCache :              for clearing the cache
 */
template <typename TImageContainer, typename TImageFactory>
class ImageCacheReadPolicyLAST
{
public:
  
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageFactory<TImageFactory> ));    
    
    typedef TImageFactory ImageFactory;
    
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain Domain;
    typedef typename TImageContainer::Point Point;
    typedef typename TImageContainer::Value Value;
    
    ImageCacheReadPolicyLAST(Alias<ImageFactory> anImageFactory):
      myCacheImagesPtr(NULL),  myImageFactory(&anImageFactory)
    {
    }

    /**
     * Destructor.
     * Does nothing
     */
    ~ImageCacheReadPolicyLAST() {}
    
private:
    
    ImageCacheReadPolicyLAST( const ImageCacheReadPolicyLAST & other );
    
    ImageCacheReadPolicyLAST & operator=( const ImageCacheReadPolicyLAST & other );
    
public:
    
    /**
     * Get the alias on the image that contains the point aPoint
     * or NULL if no image in the cache contains the point aPoint.
     * 
     * @param aPoint the point.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPage(const Point & aPoint);
    
    /**
     * Get the alias on the image that matchs the domain aDomain
     * or NULL if no image in the cache matchs the domain aDomain.
     * 
     * @param aDomain the domain.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPage(const Domain & aDomain);
    
    /**
     * Get the alias on the image that we have to detach
     * or NULL if no image have to be detached.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPageToDetach();
    
    /**
     * Update the cache according to the cache policy.
     *
     * @param aDomain the domain.
     */
    void updateCache(const Domain &aDomain);
    
    /**
     * Clear the cache.
     */
    void clearCache();
    
protected:
    
    /// Alias on the images cache
    ImageContainer * myCacheImagesPtr;
    
    /// Alias on the image factory
    ImageFactory * myImageFactory;
    
}; // end of class ImageCacheReadPolicyLAST

/////////////////////////////////////////////////////////////////////////////
// Template class ImageCacheReadPolicyFIFO
/**
 * Description of template class 'ImageCacheReadPolicyFIFO' <p>
 * \brief Aim: implements a 'FIFO' read policy cache.
 * 
 * The cache keeps track of all the pages in memory in a queue, with the most recent arrival at the back, and the earliest arrival in front. 
 * When a page needs to be replaced, the page at the front of the queue (the oldest page) is selected.
 * 
 * @tparam TImageContainer an image container type (model of CImage).
 * @tparam TImageFactory an image factory.
 * 
 * The policy is done with 5 functions:
 * 
 *  - getPage :                 for getting the alias on the image that contains a point or NULL if no image in the cache contains that point
 *  - getPage :                 for getting the alias on the image that contains a domain or NULL if no image in the cache contains that domain
 *  - getPageToDetach :         for getting the alias on the image that we have to detach or NULL if no image have to be detached
 *  - updateCache :             for updating the cache according to the cache policy
 *  - clearCache :              for clearing the cache
 */
template <typename TImageContainer, typename TImageFactory>
class ImageCacheReadPolicyFIFO
{
public:
  
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageFactory<TImageFactory> ));    
    
    typedef TImageFactory ImageFactory;
    
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain Domain;
    typedef typename TImageContainer::Point Point;
    typedef typename TImageContainer::Value Value;
    
    ImageCacheReadPolicyFIFO(Alias<ImageFactory> anImageFactory, int aFIFOSizeMax=10):
       myFIFOSizeMax(aFIFOSizeMax), myImageFactory(&anImageFactory)
    {
    }

    /**
     * Destructor.
     * Does nothing
     */
    ~ImageCacheReadPolicyFIFO() {}
    
private:
    
    ImageCacheReadPolicyFIFO( const ImageCacheReadPolicyFIFO & other );
    
    ImageCacheReadPolicyFIFO & operator=( const ImageCacheReadPolicyFIFO & other );
    
public:
    
    /**
     * Get the alias on the image that contains the point aPoint
     * or NULL if no image in the cache contains the point aPoint.
     * 
     * @param aPoint the point.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPage(const Point & aPoint);
    
    /**
     * Get the alias on the image that matchs the domain aDomain
     * or NULL if no image in the cache matchs the domain aDomain.
     * 
     * @param aDomain the domain.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPage(const Domain & aDomain);
    
    /**
     * Get the alias on the image that we have to detach
     * or NULL if no image have to be detached.
     *
     * @return the alias on the image container or NULL pointer.
     */
    ImageContainer * getPageToDetach();
    
    /**
     * Update the cache according to the cache policy.
     *
     * @param aDomain the domain.
     */
    void updateCache(const Domain &aDomain);
    
    /**
     * Clear the cache.
     */
    void clearCache();
    
protected:
    
    /// Alias on the images cache
    std::deque <ImageContainer *> myFIFOCacheImages;
    
    /// Size max of the FIFO
    unsigned int myFIFOSizeMax;
    
    /// Alias on the image factory
    ImageFactory * myImageFactory;
    
}; // end of class ImageCacheReadPolicyFIFO

/////////////////////////////////////////////////////////////////////////////
// Template class ImageCacheWritePolicyWT
/**
 * Description of template class 'ImageCacheWritePolicyWT' <p>
 * \brief Aim: implements a 'WT (Write-through)' write policy cache.
 * 
 * Write is done synchronously both to the cache and to the disk.
 * 
 * @tparam TImageContainer an image container type (model of CImage).
 * @tparam TImageFactory an image factory.
 * 
 * The policy is done with 2 functions:
 * 
 *  - writeInPage :     for setting a value on an image at a given position given by a point
 *  - flushPage :       for flushing the image on disk according to the cache policy
 */
template <typename TImageContainer, typename TImageFactory>
class ImageCacheWritePolicyWT
{
public:
  
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageFactory<TImageFactory> ));
  
    typedef TImageFactory ImageFactory;
    
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain Domain;
    typedef typename TImageContainer::Point Point;
    typedef typename TImageContainer::Value Value;
    
    ImageCacheWritePolicyWT(Alias<ImageFactory> anImageFactory):
      myImageFactory(&anImageFactory)
    {
    }

    /**
     * Destructor.
     * Does nothing
     */
    ~ImageCacheWritePolicyWT() {}
    
private:
    
    ImageCacheWritePolicyWT( const ImageCacheWritePolicyWT & other );
    
    ImageCacheWritePolicyWT & operator=( const ImageCacheWritePolicyWT & other );
    
public:
    
    /**
    * Set a value on an image at a given position given
    * by aPoint.
    *
    * @param anImageContainer the image.
    * @param aPoint the point.
    * @param aValue the value.
    */
    void writeInPage(ImageContainer * anImageContainer, const Point & aPoint, const Value &aValue);
    
    /**
    * Flush the image on disk according to the cache policy.
    *
    * @param anImageContainer the image.
    */
    void flushPage(ImageContainer * anImageContainer);
    
protected:
    
    /// Alias on the image factory
    ImageFactory * myImageFactory;
    
}; // end of class ImageCacheWritePolicyWT

/////////////////////////////////////////////////////////////////////////////
// Template class ImageCacheWritePolicyWB
/**
 * Description of template class 'ImageCacheWritePolicyWB' <p>
 * \brief Aim: implements a 'WB (Write-back or Write-behind)' write policy cache.
 * 
 * Initially, writing is done only to the cache. The write to the disk is postponed 
 * until the cache blocks containing the data are about to be modified/replaced by new content.
 * 
 * @tparam TImageContainer an image container type (model of CImage).
 * @tparam TImageFactory an image factory.
 * 
 * The policy is done with 2 functions:
 * 
 *  - writeInPage :     for setting a value on an image at a given position given by a point
 *  - flushPage :       for flushing the image on disk according to the cache policy
 */
template <typename TImageContainer, typename TImageFactory>
class ImageCacheWritePolicyWB
{
public:
  
    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageFactory<TImageFactory> ));
  
    typedef TImageFactory ImageFactory;
    
    typedef TImageContainer ImageContainer;
    typedef typename TImageContainer::Domain Domain;
    typedef typename TImageContainer::Point Point;
    typedef typename TImageContainer::Value Value;
    
    ImageCacheWritePolicyWB(Alias<ImageFactory> anImageFactory):
      myImageFactory(&anImageFactory)
    {
    }

    /**
     * Destructor.
     * Does nothing
     */
    ~ImageCacheWritePolicyWB() {}
    
private:
    
    ImageCacheWritePolicyWB( const ImageCacheWritePolicyWB & other );
    
    ImageCacheWritePolicyWB & operator=( const ImageCacheWritePolicyWB & other );
    
public:
    
    /**
    * Set a value on an image at a given position given
    * by aPoint.
    *
    * @param anImageContainer the image.
    * @param aPoint the point.
    * @param aValue the value.
    */
    void writeInPage(ImageContainer * anImageContainer, const Point & aPoint, const Value &aValue);
    
    /**
    * Flush the image on disk according to the cache policy.
    *
    * @param anImageContainer the image.
    */
    void flushPage(ImageContainer * anImageContainer);
    
protected:
    
    /// Alias on the image factory
    ImageFactory * myImageFactory;
    
}; // end of class ImageCacheWritePolicyWB

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ImageCachePolicies.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ImageCachePolicies_h

#undef ImageCachePolicies_RECURSES
#endif // else defined(ImageCachePolicies_RECURSES)
