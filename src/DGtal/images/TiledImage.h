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
 * @file TiledImage.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/01/24
 *
 * Header file for module TiledImage.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(TiledImage_RECURSES)
#error Recursive header files inclusion detected in TiledImage.h
#else // defined(TiledImage_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TiledImage_RECURSES

#if !defined TiledImage_h
/** Prevents repeated inclusion of headers. */
#define TiledImage_h

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

#include "DGtal/images/ImageCache.h"

#include "DGtal/base/TiledImageBidirectionalConstRangeFromPoint.h"
#include "DGtal/base/TiledImageBidirectionalRangeFromPoint.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /////////////////////////////////////////////////////////////////////////////
  // Template class TiledImage
  /**
   * Description of template class 'TiledImage' <p>
   * \brief Aim: implements a tiled image from a "bigger/original" one from an ImageFactory.
   *
   * @tparam TImageContainer an image container type (model of ).
   * @tparam TImageFactory an image factory type (model of CImageFactory).
   * @tparam TImageCacheReadPolicy an image cache read policy class (model of CImageCacheReadPolicy).
   * @tparam TImageCacheWritePolicy an image cache write policy class (model of CImageCacheWritePolicy).
   *
   * @note It is important to take into account that read and write policies are passed as aliases in the TiledImage constructor,
   * so for example, if two TiledImage instances are successively created with the same read policy instance,
   * the state of the cache for a given time is therefore the same for the two TiledImage instances !
   */
  template <typename TImageContainer, typename TImageFactory, typename TImageCacheReadPolicy, typename TImageCacheWritePolicy>
  class TiledImage
  {

    // ----------------------- Types ------------------------------

  public:
    typedef TiledImage<TImageContainer, TImageFactory, TImageCacheReadPolicy, TImageCacheWritePolicy> Self;

    ///Checking concepts
    BOOST_CONCEPT_ASSERT(( concepts::CImage<TImageContainer> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageFactory<TImageFactory> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageCacheReadPolicy<TImageCacheReadPolicy> ));
    BOOST_CONCEPT_ASSERT(( concepts::CImageCacheWritePolicy<TImageCacheWritePolicy> ));

    ///Types copied from the container
    typedef TImageContainer ImageContainer;
    typedef typename ImageContainer::Domain Domain;
    typedef typename ImageContainer::Point Point;
    typedef typename ImageContainer::Value Value;

    typedef typename ImageContainer::Difference Difference;

    ///Types
    typedef TImageFactory ImageFactory;
    typedef typename ImageFactory::OutputImage OutputImage;

    typedef TImageCacheReadPolicy ImageCacheReadPolicy;
    typedef TImageCacheWritePolicy ImageCacheWritePolicy;
    typedef ImageCache<OutputImage, ImageFactory, ImageCacheReadPolicy, ImageCacheWritePolicy > MyImageCache;

    // ----------------------- Standard services ------------------------------

  public:

    /**
     * Constructor.
     * @param anImageFactory alias on the image factory (see ImageFactoryFromImage or ImageFactoryFromHDF5).
     * @param aReadPolicy alias on a read policy.
     * @param aWritePolicy alias on a write policy.
     * @param N how many tiles we want for each dimension.
     */
    TiledImage(Alias<ImageFactory> anImageFactory,
               Alias<ImageCacheReadPolicy> aReadPolicy,
               Alias<ImageCacheWritePolicy> aWritePolicy,
               typename Domain::Integer N):
      myN(N), myImageFactory(&anImageFactory), myReadPolicy(&aReadPolicy), myWritePolicy(&aWritePolicy)
    {
      myImageCache = new MyImageCache(myImageFactory, myReadPolicy, myWritePolicy);

      m_lowerBound = myImageFactory->domain().lowerBound();
      m_upperBound = myImageFactory->domain().upperBound();

      for(typename DGtal::Dimension i=0; i<Domain::dimension; i++)
        mySize[i] = (m_upperBound[i]-m_lowerBound[i]+1)/myN;
    }

    /**
     * Destructor.
     */
    ~TiledImage()
    {
      delete myImageCache;
    }

  private:

  public:

    /**
      * Copy constructor.
      * @param other the TiledImage to clone.
      */
    TiledImage( const TiledImage &other )
    {
      myN =  other.myN;
      myImageFactory = other.myImageFactory;
      myReadPolicy = other.myReadPolicy;
      myWritePolicy = other.myWritePolicy;

      myImageCache = new MyImageCache(myImageFactory, myReadPolicy, myWritePolicy);

      m_lowerBound = myImageFactory->domain().lowerBound();
      m_upperBound = myImageFactory->domain().upperBound();

      for(typename DGtal::Dimension i=0; i<Domain::dimension; i++)
        mySize[i] = (m_upperBound[i]-m_lowerBound[i]+1)/myN;
    }

    /**
      * Assignment.
      * @param other the TiledImage to copy.
      * @return a reference on 'this'.
      */
    TiledImage & operator=( const TiledImage & other )
    {
        if ( this != &other )
        {
          myN =  other.myN;
          myImageFactory = other.myImageFactory;
          myReadPolicy = other.myReadPolicy;
          myWritePolicy = other.myWritePolicy;

          myImageCache = new MyImageCache(myImageFactory, myReadPolicy, myWritePolicy);

          m_lowerBound = myImageFactory->domain().lowerBound();
          m_upperBound = myImageFactory->domain().upperBound();

          for(typename DGtal::Dimension i=0; i<Domain::dimension; i++)
            mySize[i] = (m_upperBound[i]-m_lowerBound[i]+1)/myN;
        }

        return *this;
    }

    // ----------------------- Interface --------------------------------------
  public:

    /////////////////// Domains ///////////////////

    /**
     * Returns a reference to the underlying image domain.
     *
     * @return a reference to the domain.
     */
    const Domain & domain() const
    {
      return myImageFactory->domain();
    }

    /**
     * Returns the block coords domain.
     *
     * @return the block coords domain.
     */
    const Domain domainBlockCoords() const
    {
      Point lowerBoundCords, upperBoundCoords;

      for(typename DGtal::Dimension i=0; i<Domain::dimension; i++)
        {
          lowerBoundCords[i] = 0;
          upperBoundCoords[i] = myN;

          if (((m_upperBound[i]-m_lowerBound[i]+1) % myN) == 0)
            upperBoundCoords[i]--;
        }

      return Domain(lowerBoundCords, upperBoundCoords);
    }

    /////////////////////////// Custom Iterator /////////////

    /**
     * Specific TiledIterator on TiledImage.
     */

    class TiledIterator : public
    std::iterator<std::bidirectional_iterator_tag, Value, ptrdiff_t, Value*, Value&>
    {

      friend class TiledImage<ImageContainer, ImageFactory, ImageCacheReadPolicy, ImageCacheWritePolicy>;

    public:

      /*typedef std::bidirectional_iterator_tag iterator_category; // ???
        typedef Value value_type;
        typedef ptrdiff_t difference_type; // ???
        typedef Value* pointer;
        typedef Value& reference;*/

      typedef typename ImageContainer::Range::/*Output*/Iterator TiledRangeIterator;
      typedef typename Domain::Iterator BlockCoordsIterator;

      //TiledIterator();

      /**
       * Constructor.
       *
       * @param aBlockCoordsIterator a block coords iterator
       * @param aTiledImage pointer to the TiledImage
       */
      TiledIterator ( BlockCoordsIterator aBlockCoordsIterator,
                      const TiledImage<ImageContainer, ImageFactory,
                      ImageCacheReadPolicy, ImageCacheWritePolicy> *aTiledImage ) :  myTiledImage ( aTiledImage ),
                                                                                     myBlockCoordsIterator ( aBlockCoordsIterator )
      {
        if ( myBlockCoordsIterator != myTiledImage->domainBlockCoords().end() )
          {
            myTile = myTiledImage->findTileFromBlockCoords( (*myBlockCoordsIterator) );
            myTiledRangeIterator = myTile->range().begin();
          }
      }

      /**
       * Constructor.
       *
       * @param aBlockCoordsIterator a block coords iterator
       * @param aPoint a point
       * @param aTiledImage pointer to the TiledImage
       */
      TiledIterator ( BlockCoordsIterator aBlockCoordsIterator,
                      const Point& aPoint,
                      const TiledImage<ImageContainer, ImageFactory,
                      ImageCacheReadPolicy, ImageCacheWritePolicy> *aTiledImage ) :  myTiledImage ( aTiledImage ),
                                                                                     myBlockCoordsIterator ( aBlockCoordsIterator )
      {
        if ( myBlockCoordsIterator != myTiledImage->domainBlockCoords().end() )
          {
            myTile = myTiledImage->findTileFromBlockCoords( (*myBlockCoordsIterator) );
            myTiledRangeIterator = myTile->range().begin(aPoint);
          }
      }

      /**
       * operator *
       *
       * @return the value associated to the current TiledRangeIterator position.
       */
      inline
      Value & operator*()
      {
        return (*myTiledRangeIterator);
      }

      /**
       * Operator ==
       *
       * @return true if this and it are equals.
       */
      inline
      bool operator== ( const TiledIterator &it ) const
      {
        return ( ( this->myBlockCoordsIterator == it.myBlockCoordsIterator ) && ( this->myTiledRangeIterator == it.myTiledRangeIterator ) );
      }

      /**
       * Operator !=
       *
       * @return true if this and it are different.
       */
      inline
      bool operator!= ( const TiledIterator &it ) const
      {
        if ( myBlockCoordsIterator == myTiledImage->domainBlockCoords().end() )
          return false;

        return ( ( this->myBlockCoordsIterator != it.myBlockCoordsIterator ) || ( this->myTiledRangeIterator != it.myTiledRangeIterator ) );
      }

      /**
       * Implements the next() method to scan the domain points dimension by dimension
       * (lexicographic order).
       **/
      inline
      void nextLexicographicOrder()
      {
        myTiledRangeIterator++;

        if ( myTiledRangeIterator != myTile->range().end() )
          return;
        else
          {
            myBlockCoordsIterator++;

            if ( myBlockCoordsIterator == myTiledImage->domainBlockCoords().end() )
              return;

            myTile = myTiledImage->findTileFromBlockCoords( (*myBlockCoordsIterator) );
            myTiledRangeIterator = myTile->range().begin();
          }
      }

      /**
       * Operator ++ (++it)
       *
       */
      inline
      TiledIterator &operator++()
      {
        nextLexicographicOrder();
        return *this;
      }

      /**
       * Operator ++ (it++)
       *
       */
      inline
      TiledIterator operator++ ( int )
      {
        TiledIterator tmp = *this;
        nextLexicographicOrder();
        return tmp;
      }

      /**
       * Implements the prev() method to scan the domain points dimension by dimension
       * (lexicographic order).
       **/
      inline
      void prevLexicographicOrder()
      {
        // -- IF we are at the end... (reverse, --)
        if ( myBlockCoordsIterator == myTiledImage->domainBlockCoords().end() )
          {
            myBlockCoordsIterator--;

            myTile = myTiledImage->findTileFromBlockCoords( (*myBlockCoordsIterator) );

            myTiledRangeIterator = myTile->range().end();
            myTiledRangeIterator--;

            return;
          }
        // -- IF we are at the end... (reverse, --)

        // ---

        if ( myTiledRangeIterator != myTile->range().begin() )
          {
            myTiledRangeIterator--;
            return;
          }
        else
          {
            if ( myBlockCoordsIterator == myTiledImage->domainBlockCoords().begin() )
              return;

            myBlockCoordsIterator--;

            myTile = myTiledImage->findTileFromBlockCoords( (*myBlockCoordsIterator) );

            myTiledRangeIterator = myTile->range().end();
            myTiledRangeIterator--;
          }
      }

      /**
       * Operator -- (--it)
       *
       */
      inline
      TiledIterator &operator--()
      {
        prevLexicographicOrder();
        return *this;
      }

      /**
       * Operator -- (it--)
       */
      inline
      TiledIterator operator-- ( int )
      {
        TiledIterator tmp = *this;
        prevLexicographicOrder();
        return tmp;
      }

    private:
      /// TiledImage pointer
      const TiledImage *myTiledImage;

      /// Alias on the current tile
      ImageContainer * myTile;

      /// Current tiled range iterator
      TiledRangeIterator myTiledRangeIterator;

      /// Current block coords iterator
      BlockCoordsIterator myBlockCoordsIterator;
    };


    typedef TiledIterator ConstIterator;
    typedef TiledIterator OutputIterator;

    typedef std::reverse_iterator<TiledIterator> ReverseTiledIterator;
    typedef ReverseTiledIterator ConstReverseIterator;
    typedef ReverseTiledIterator ReverseOutputIterator;


    ConstIterator begin() const
    {
      return TiledIterator( this->domainBlockCoords().begin(), this );
    }

    OutputIterator begin()
    {
      return TiledIterator( this->domainBlockCoords().begin(), this );
    }

    ConstIterator begin(const Point& aPoint) const
    {
      Point coords = this->findBlockCoordsFromPoint(aPoint);
      return TiledIterator(  this->domainBlockCoords().begin(coords), aPoint, this );
    }

    OutputIterator begin(const Point& aPoint)
    {
      Point coords = this->findBlockCoordsFromPoint(aPoint);
      return TiledIterator(  this->domainBlockCoords().begin(coords), aPoint, this );
    }

    ConstIterator end() const
    {
      return TiledIterator( this->domainBlockCoords().end(), this );
    }

    OutputIterator end()
    {
      return TiledIterator( this->domainBlockCoords().end(), this );
    }

    ConstReverseIterator rbegin() const
    {
      return ReverseTiledIterator( end() );
    }

    ReverseOutputIterator rbegin()
    {
      return ReverseTiledIterator( end() );
    }

    ConstReverseIterator rbegin(const Point& aPoint) const
    {
      typename DGtal::Dimension i;

      Point point2;
      for(i=0; i<Domain::dimension; i++)
        point2[i]=(m_upperBound[i]-aPoint[i])+m_lowerBound[i];

      TiledIterator it( begin(point2) ); it++;
      return ReverseTiledIterator(it);
    }

    ReverseOutputIterator rbegin(const Point& aPoint)
    {
      typename DGtal::Dimension i;

      Point point2;
      for(i=0; i<Domain::dimension; i++)
        point2[i]=(m_upperBound[i]-aPoint[i])+m_lowerBound[i];

      TiledIterator it( begin(point2) ); it++;
      return ReverseTiledIterator(it);
    }

    ConstReverseIterator rend() const
    {
      return ReverseTiledIterator( begin() );
    }

    ConstReverseIterator rend()
    {
      return ReverseTiledIterator( begin() );
    }

    // ---

    OutputIterator outputIterator()
    {
      return OutputIterator( begin() );
    }

    OutputIterator outputIterator(const Point& aPoint)
    {
      return OutputIterator( begin(aPoint) );
    }

    ReverseOutputIterator routputIterator()
    {
      return ReverseOutputIterator( end() );
    }

    ReverseOutputIterator routputIterator(const Point &aPoint)
    {
      return ReverseOutputIterator( rbegin(aPoint) );
    }

    /////////////////////////// Ranges  /////////////////////

    typedef TiledImageBidirectionalConstRangeFromPoint<TiledImage > ConstRange;
    typedef TiledImageBidirectionalRangeFromPoint<TiledImage > Range;

    /**
     * @return the range providing begin and end
     * iterators (with this) to scan the values of image.
     */
    ConstRange constRange() const
    {
      return ConstRange( this );
    }

    /**
     * @return the range providing begin and end
     * iterators (with this) to scan the values of image.
     */
    Range range()
    {
      return Range( this );
    }

    /////////////////// API ///////////////////////

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
      return (myImageFactory->isValid() && myImageCache->isValid());
    }

    /**
     * Get the domain containing aPoint.
     *
     * @param aPoint the point.
     * @return the domain containing aPoint.
     */
    const Domain findSubDomain(const Point & aPoint) const
    {
      ASSERT(myImageFactory->domain().isInside(aPoint));

      typename DGtal::Dimension i;

      Point low;
      for(i=0; i<Domain::dimension; i++)
        {
          low[i] = (aPoint[i]-m_lowerBound[i])/mySize[i];
        }

      Point dMin, dMax;
      for(i=0; i<Domain::dimension; i++)
        {
          dMin[i] = (low[i]*mySize[i])+m_lowerBound[i];
          dMax[i] = dMin[i] + (mySize[i]-1);

          if (dMax[i] > m_upperBound[i]) // last tile
            dMax[i] = m_upperBound[i];
        }

      Domain di(dMin, dMax);
      return di;
    }

    /**
     * Get the block coords containing aPoint.
     *
     * @param aPoint the point.
     * @return the block coords containing aPoint.
     */
    const Point findBlockCoordsFromPoint(const Point & aPoint) const
    {
      ASSERT(myImageFactory->domain().isInside(aPoint));

      typename DGtal::Dimension i;

      Point low;
      for(i=0; i<Domain::dimension; i++)
        {
          /*if ( (aPoint[i]-m_lowerBound[i]) < mySize[i] )
            low[i] = 0;
            else*/
          low[i] = (aPoint[i]-m_lowerBound[i])/mySize[i];
        }

      return low;
    }

    /**
     * Get the domain with his block coords.
     *
     * @param aCoord the block coords.
     * @return the domain.
     */
    const Domain findSubDomainFromBlockCoords(const Point & aCoord) const
    {
      ASSERT(domainBlockCoords().isInside(aCoord));

      typename DGtal::Dimension i;

      Point dMin, dMax;
      for(i=0; i<Domain::dimension; i++)
        {
          dMin[i] = (aCoord[i]*mySize[i])+m_lowerBound[i];
          dMax[i] = dMin[i] + (mySize[i]-1);

          if (dMax[i] > m_upperBound[i]) // last tile
            dMax[i] = m_upperBound[i];
        }

      Domain di(dMin, dMax);
      return di;
    }

    /**
     * Returns an ImageContainer pointer for the block coords aCoord.
     *
     * @param aCoord the block coords.
     * @return an ImageContainer pointer.
     */
    ImageContainer * findTileFromBlockCoords(const Point & aCoord) const
    {
      ASSERT(domainBlockCoords().isInside(aCoord));

      Domain d = findSubDomainFromBlockCoords( aCoord );
      ImageContainer *tile = myImageCache->getPage(d);
      if (!tile)
        {
          myImageCache->incCacheMissRead();
          myImageCache->update(d);
          tile = myImageCache->getPage(d);
        }

      return tile;
    }

    /**
     * Get the value of an image (from cache) at a given position given by aPoint.
     *
     * @param aPoint the point.
     * @return the value at aPoint.
     */
    Value operator()(const Point & aPoint) const
    {
      ASSERT(myImageFactory->domain().isInside(aPoint));

      typename OutputImage::Value aValue;
      bool res;

      res = myImageCache->read(aPoint, aValue);

      if (res)
        return aValue;
      else
        {
          myImageCache->incCacheMissRead();
          Domain d;
#ifdef DEBUG_VERBOSE
          trace.info()<<"+";
#endif 
          d = findSubDomain(aPoint);

          myImageCache->update(d);

          myImageCache->read(aPoint, aValue);

          return aValue;
        }

      // Unspecified behavior, returning the default constructed value.
      return aValue;
    }

    /**
     * Set a value on an image (in cache) at a position specified by a aPoint.
     *
     * @param aPoint the point.
     * @param aValue the value.
     */
    void setValue(const Point &aPoint, const Value &aValue)
    {
      ASSERT(myImageFactory->domain().isInside(aPoint));

      if (myImageCache->write(aPoint, aValue))
        return;
      else
        {
          myImageCache->incCacheMissWrite();
          myImageCache->update(findSubDomain(aPoint));
          myImageCache->write(aPoint, aValue);
        }
    }

    /**
     * Get the cacheMissRead value.
     */
    unsigned int getCacheMissRead()
    {
      return myImageCache->getCacheMissRead();
    }

    /**
     * Get the cacheMissWrite value.
     */
    unsigned int getCacheMissWrite()
    {
      return myImageCache->getCacheMissWrite();
    }

    /**
     * Clear the cache and reset the cache misses
     */
    void clearCacheAndResetCacheMisses()
    {
      myImageCache->clearCacheAndResetCacheMisses();
    }

    // ------------------------- Private Datas --------------------------------
  protected:

    /// Number of tiles per dimension
    typename Domain::Integer myN;

    /// Width of a tile (for each dimension)
    Point mySize;

    /// ImageFactory pointer
    ImageFactory *myImageFactory;

    /// ImageCache pointer
    MyImageCache *myImageCache;

    /// domain lower and upper bound
    Point m_lowerBound, m_upperBound;

    /// TImageCacheReadPolicy pointer
    TImageCacheReadPolicy *myReadPolicy;

    /// TImageCacheWritePolicy pointer
    TImageCacheWritePolicy *myWritePolicy;

    // ------------------------- Internals ------------------------------------

  }; // end of class TiledImage


  /**
   * Overloads 'operator<<' for displaying objects of class 'TiledImage'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'TiledImage' to write.
   * @return the output stream after the writing.
   */
  template <typename TImageContainer, typename TImageFactory, typename TImageCacheReadPolicy, typename TImageCacheWritePolicy>
  std::ostream&
  operator<< ( std::ostream & out, const TiledImage<TImageContainer, TImageFactory, TImageCacheReadPolicy, TImageCacheWritePolicy> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/TiledImage.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined TiledImage_h

#undef TiledImage_RECURSES
#endif // else defined(TiledImage_RECURSES)
