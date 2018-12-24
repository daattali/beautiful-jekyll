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
 * @file TiledImageBidirectionalConstRangeFromPoint.h
 * @author Martial Tola (\c martial.tola@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2013/11/06
 *
 *
 * Header file for module TiledImageBidirectionalConstRangeFromPoint.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(TiledImageBidirectionalConstRangeFromPoint_RECURSES)
#error Recursive header files inclusion detected in TiledImageBidirectionalConstRangeFromPoint.h
#else // defined(TiledImageBidirectionalConstRangeFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define TiledImageBidirectionalConstRangeFromPoint_RECURSES

#if !defined TiledImageBidirectionalConstRangeFromPoint_h
/** Prevents repeated inclusion of headers. */
#define TiledImageBidirectionalConstRangeFromPoint_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/ConstIteratorAdapter.h"
#include "DGtal/base/CConstBidirectionalRangeFromPoint.h"
#include "boost/concept_check.hpp"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{


  ///////////////////////////////////////////////////////////////////////////////
  // class TiledImageBidirectionalConstRangeFromPoint
  ///////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Aim: model of CConstBidirectionalRangeFromPoint that adapts a TiledImage range of elements
   * bounded by two iterators [itb, ite) and provides services to
   * (circularly)iterate over it (in a read-only manner).
   *
   * @tparam TTiledImage the type of the TiledImage with his const iterator to adapt (at least bidirectional)
   *
   * @see ConstRangeAdapter
   */
  template <typename TTiledImage>

  class TiledImageBidirectionalConstRangeFromPoint
  {

      BOOST_CONCEPT_ASSERT ( ( boost::BidirectionalIterator<typename TTiledImage::ConstIterator> ) );

      // ------------------------- inner types --------------------------------

    public:
      
      typedef TTiledImage TiledImage;

      typedef typename TiledImage::Point Point;

      typedef typename TiledImage::ConstIterator ConstIterator;
      typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

      typedef Circulator<ConstIterator> ConstCirculator;
      typedef std::reverse_iterator<ConstCirculator> ConstReverseCirculator;

      // ------------------------- standard services --------------------------------
      
      /**
       * Standard constructor from a TiledImage.
       * @param ti pointer on a TiledImage.
       */
      TiledImageBidirectionalConstRangeFromPoint ( const TiledImage *ti )
        : myti ( ti ) {}

      /**
       * Copy constructor.
       * @param other the iterator to clone.
       */
      TiledImageBidirectionalConstRangeFromPoint ( const TiledImageBidirectionalConstRangeFromPoint & other )
          : myti ( other.myti ) {}

      /**
       * Assignment.
       * @param other the iterator to copy.
       * @return a reference on 'this'.
       */
      TiledImageBidirectionalConstRangeFromPoint& operator= ( const TiledImageBidirectionalConstRangeFromPoint & other )
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
      ~TiledImageBidirectionalConstRangeFromPoint() {}

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
        typedef typename IteratorCirculatorTraits<ConstIterator>::Value Value;
        out << "[TiledImageBidirectionalConstRangeFromPoint]" << std::endl;
        out << "\t";
        std::copy ( myti->begin(), myti->end(), std::ostream_iterator<Value> ( out, ", " ) );
        out << std::endl;
      }

      /**
       * @return the style name used for drawing this object.
       */
      std::string className() const
      {
        return "TiledImageBidirectionalConstRangeFromPoint";
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
      ConstIterator begin() const
      {
        return ConstIterator ( myti->begin() );
      }

      /**
       * Iterator service.
       * @return begin iterator
       */
      ConstIterator begin ( const Point &aPoint ) const
      {
        return ConstIterator ( myti->begin(aPoint) );
      }

      /**
       * Iterator service.
       * @return end iterator
       */
      ConstIterator end() const
      {
        return ConstIterator ( myti->end() );
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
       * @return rbegin iterator
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

      /**
       * Circulator service.
       * @return a circulator
       */
      ConstCirculator c() const
      {
        return ConstCirculator ( this->begin(), this->begin(), this->end() );
      }

      /**
       * Circulator service.
       * @return a reverse circulator
       */
      ConstReverseCirculator rc() const
      {
        return ConstReverseCirculator ( this->c() );
      }

  }; //end class TiledImageBidirectionalConstRangeFromPoint

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////


#endif // !defined TiledImageBidirectionalConstRangeFromPoint_h

#undef TiledImageBidirectionalConstRangeFromPoint_RECURSES
#endif // else defined(TiledImageBidirectionalConstRangeFromPoint_RECURSES)
