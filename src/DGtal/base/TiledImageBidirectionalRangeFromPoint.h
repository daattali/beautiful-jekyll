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
 * @file TiledImageBidirectionalRangeFromPoint.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2013/11/07
 *
 *
 * Header file for module TiledImageBidirectionalRangeFromPoint.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(TiledImageBidirectionalRangeFromPoint_RECURSES)
#error Recursive header files inclusion detected in TiledImageBidirectionalRangeFromPoint.h
#else // defined(TiledImageBidirectionalRangeFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TiledImageBidirectionalRangeFromPoint_RECURSES

#if !defined TiledImageBidirectionalRangeFromPoint_h
/** Prevents repeated inclusion of headers. */
#define TiledImageBidirectionalRangeFromPoint_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/IteratorAdapter.h"
#include "DGtal/base/CBidirectionalRangeFromPoint.h"
#include "boost/concept_check.hpp"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  ///////////////////////////////////////////////////////////////////////////////
  // class TiledImageBidirectionalRangeFromPoint
  ///////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Aim: model of CBidirectionalRangeFromPoint that adapts a TiledImage range of elements
   * bounded by two iterators [itb, ite) and provides services to
   * (circularly)iterate over it.
   *
   * @tparam TTiledImage the type of the TiledImage with his const iterator to adapt (at least bidirectional)
   *
   * @see RangeAdapter
   */
  template <typename TTiledImage>

  class TiledImageBidirectionalRangeFromPoint
  {

      BOOST_CONCEPT_ASSERT ( ( boost::BidirectionalIterator<typename TTiledImage::OutputIterator> ) );
      BOOST_CONCEPT_ASSERT ( ( boost::BidirectionalIterator<typename TTiledImage::ConstIterator> ) );

      // ------------------------- inner types --------------------------------

    public:

      typedef TTiledImage TiledImage;

      typedef typename TiledImage::Point Point;

      typedef typename TiledImage::OutputIterator Iterator;
      typedef typename TiledImage::ConstIterator ConstIterator;

      typedef std::reverse_iterator<Iterator> ReverseIterator;
      typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

      typedef typename TiledImage::OutputIterator OutputIterator;
      typedef std::reverse_iterator<Iterator> ReverseOutputIterator;

      // typedef Circulator<Iterator> Circulator;
      // typedef std::reverse_iterator<Circulator> ReverseCirculator;

      // ------------------------- standard services --------------------------------

      /**
       * Standard constructor from a TiledImage.
       * @param ti pointer on a TiledImage.
       */
      TiledImageBidirectionalRangeFromPoint ( const TiledImage *ti )
        : myti ( ti ) {}

      /**
       * Copy constructor.
       * @param other the iterator to clone.
       */
      TiledImageBidirectionalRangeFromPoint ( const TiledImageBidirectionalRangeFromPoint & other )
          : myti ( other.myti ) {}

      /**
       * Assignment.
       * @param other the iterator to copy.
       * @return a reference on 'this'.
       */
      TiledImageBidirectionalRangeFromPoint& operator= ( const TiledImageBidirectionalRangeFromPoint & other )
      {
        if ( this != &other )
        {
          myti = other.myti;
        }

        return *this;
      }

      /**
       * Destructor. Does nothing.
       */
      ~TiledImageBidirectionalRangeFromPoint() {}

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const
      {
        return true;
      }

      // ------------------------- display --------------------------------
      /**
       * Writes/Displays the object on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const
      {
        typedef typename IteratorCirculatorTraits<Iterator>::Value Value;
        out << "[TiledImageBidirectionalRangeFromPoint]" << std::endl;
        out << "\t";
        std::copy ( myti->begin(), myti->end(), std::ostream_iterator<Value> ( out, ", " ) );
        out << std::endl;
      }

      /**
       * @return the style name used for drawing this object.
       */
      std::string className() const
      {
        return "TiledImageBidirectionalRangeFromPoint";
      }


      // ------------------------- private data --------------------------------

    private:
      
      const TTiledImage *myti;

      // ------------------------- iterator services --------------------------------

    public:

      /**
       * Iterator service.
       * @return begin iterator
       */
      Iterator begin()
      {
        return Iterator ( myti->begin() );
      }

      /**
       * Iterator service.
       * @param aPoint a Point
       * @return begin iterator at aPoint
       */
      Iterator begin ( const Point &aPoint )
      {
        return Iterator ( myti->begin(aPoint) );
      }

       /**
       * Iterator service.
       * @return begin iterator
       */
      ConstIterator begin() const
      {
        return ConstIterator ( myti->begin() );
      }

      /**
       * Iterator service.
       * @param aPoint a Point
       * @return begin iterator at aPoint
       */
      ConstIterator begin ( const Point &aPoint ) const
      {
        return ConstIterator ( myti->begin(aPoint) );
      }

      /**
       * Iterator service.
       * @return end iterator
       */
      Iterator end()
      {
        return Iterator ( myti->end() );
      }

      /**
        * Iterator service.
       * @return end iterator
       */
      ConstIterator end()  const
      {
        return ConstIterator ( myti->end() );
      }

      /**
       * OutputIterator service.
       * @return an output itertor on the first elements
       */
      OutputIterator outputIterator()
      {
        return OutputIterator ( myti->begin() );
      }

      /**
       * OutputIterator service.
       * @param aPoint a point
       * @return an output itertor on the point
       */
      OutputIterator outputIterator ( const Point &aPoint )
      {
        return OutputIterator ( myti->begin(aPoint) );
      }

      /**
      * ReverseOutputIterator service.
      * @return an output itertor on the first elements
      */
      ReverseOutputIterator routputIterator()
      {
        return ReverseOutputIterator ( myti->begin() );
      }

      /**
       * ReverseOutputIterator service.
       * @param aPoint a point
       * @return an output itertor on the point
       */
      ReverseOutputIterator routputIterator ( const Point &aPoint )
      {
        return ReverseOutputIterator ( myti->begin(aPoint) );
      }

      /**
       * Iterator service.
       * @return rbegin iterator
       */
      ReverseIterator rbegin()
      {
        return ReverseIterator ( this->end() );
      }

      /**
       * Iterator service.
      * @param aPoint a Point
       * @return rbegin iterator at aPoint
       */
      ReverseIterator rbegin ( const Point &aPoint )
      {
        return ReverseIterator ( myti->rbegin(aPoint) );
      }

      /**
       * Iterator service.
       * @return rend iterator
       */
      ReverseIterator rend()
      {
        return ReverseIterator ( this->begin() );
      }

      /**
       * Iterator service.
       * @return rbegin iterator
       */
      ConstReverseIterator rbegin() const
      {
        return ConstReverseIterator ( this->end() );
      }

      /**
       * Iterator service.
      * @param aPoint a Point
       * @return rbegin iterator at aPoint
       */
      ConstReverseIterator rbegin ( const Point &aPoint ) const
      {
        return ConstReverseIterator ( myti->rbegin(aPoint) );
      }

      /**
       * Iterator service.
       * @return rend iterator
       */
      ConstReverseIterator rend() const
      {
        return ConstReverseIterator ( this->begin() );
      }

      // /**
      //  * Circulator service.
      //  * @return a circulator
      //  */
      // Circulator c() const
      // {
      //   return Circulator ( this->begin(), this->begin(), this->end() );
      // }

      // /**
      //  * Circulator service.
      //  * @return a reverse circulator
      //  */
      // ReverseCirculator rc() const
      // {
      //   return ReverseCirculator ( this->c() );
      // }

  }; //end class TiledImageBidirectionalRangeFromPoint

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////


#endif // !defined TiledImageBidirectionalRangeFromPoint_h

#undef TiledImageBidirectionalRangeFromPoint_RECURSES
#endif // else defined(TiledImageBidirectionalRangeFromPoint_RECURSES)
