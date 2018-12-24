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
 * @file SimpleRandomAccessRangeFromPoint.h
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 * @date 2012/03/27
 *
 *
 * Header file for module SimpleRandomAccessRangeFromPoint.h
 *
 * This file contains the definition of basic functors.
 *
 * This file is part of the DGtal library.
 */

#if defined(SimpleRandomAccessRangeFromPoint_RECURSES)
#error Recursive header files inclusion detected in SimpleRandomAccessRangeFromPoint.h
#else // defined(SimpleRandomAccessRangeFromPoint_RECURSES)
/** Prevents recursive inclusion of headers. */
#define SimpleRandomAccessRangeFromPoint_RECURSES

#if !defined SimpleRandomAccessRangeFromPoint_h
/** Prevents repeated inclusion of headers. */
#define SimpleRandomAccessRangeFromPoint_h

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
  // class SimpleRandomAccessRangeFromPoint
  ///////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Aim: model of CBidirectionalRangeFromPoint that adapts any range of elements
   * bounded by two iterators [itb, ite) and provides services to
   * (circularly)iterate over it (in a read-only manner).
   *
   * @tparam TIterator the type of the iterator to adapt
   * (at least bidirectional)
   * @tparam DistanceFunctor type of distance from point functor for random access container models. Models must have a Point and a Difference inner types. operator() returns a number of type Difference on instances of Point)
   *
   * @see RangeAdapter
   */
  template <typename TConstIterator, typename TIterator, typename DistanceFunctor>

  class SimpleRandomAccessRangeFromPoint
  {

      BOOST_CONCEPT_ASSERT ( ( boost::RandomAccessIterator<TIterator> ) );
      BOOST_CONCEPT_ASSERT ( ( boost::RandomAccessIterator<TConstIterator> ) );
      BOOST_CONCEPT_ASSERT ( ( boost::UnaryFunction<DistanceFunctor,typename DistanceFunctor::Difference,typename DistanceFunctor::Point > ) );

      // ------------------------- inner types --------------------------------

    public:

      typedef typename DistanceFunctor::Point Point;

      typedef TIterator Iterator;
      typedef TConstIterator ConstIterator;

      typedef std::reverse_iterator<Iterator> ReverseIterator;
      typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

      typedef TIterator OutputIterator;
      typedef std::reverse_iterator<Iterator> ReverseOutputIterator;

      typedef DGtal::Circulator<Iterator> Circulator;
      typedef std::reverse_iterator<Circulator> ReverseCirculator;

      typedef DGtal::Circulator<ConstIterator> ConstCirculator;
      typedef std::reverse_iterator<ConstCirculator> ConstReverseCirculator;

      // ------------------------- standard services --------------------------------

      /**
       * Standard constructor from two iterators
       * and one functor.
       * @param itb begin iterator.
       * @param ite end iterator.
       * @param aDistance functor used to adapt on-the-fly the elements of the range
       *
       */
      SimpleRandomAccessRangeFromPoint ( const TIterator& itb,
                                         const TIterator& ite,
                                         const DistanceFunctor & aDistance )
          : myBegin ( itb ), myEnd ( ite ), myDistance ( aDistance ) {}

      /**
       * Copy constructor.
       * @param other the iterator to clone.
       */
      SimpleRandomAccessRangeFromPoint ( const SimpleRandomAccessRangeFromPoint & other )
          : myBegin ( other.myBegin ), myEnd ( other.myEnd ),
          myDistance ( other.myDistance ) {}

      /**
       * Assignment.
       * @param other the iterator to copy.
       * @return a reference on 'this'.
       */
      SimpleRandomAccessRangeFromPoint& operator= ( const SimpleRandomAccessRangeFromPoint & other )
      {
        if ( this != &other )
        {
          myBegin = other.myBegin;
          myEnd = other.myEnd;
          myDistance = other.myDistance;
        }

        return *this;
      }

      /**
       * Destructor. Does nothing.
       */
      ~SimpleRandomAccessRangeFromPoint() {}

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
        out << "[SimpleRandomAccessRangeFromPoint]" << std::endl;
        out << "\t";
        std::copy ( myBegin, myEnd, std::ostream_iterator<Value> ( out, ", " ) );
        out << std::endl;
      }

      /**
       * @return the style name used for drawing this object.
       */
      std::string className() const
      {
        return "SimpleRandomAccessRangeFromPoint";
      }


      // ------------------------- private data --------------------------------

    private:
      /**
       * Begin underlying iterator
       */
      TIterator myBegin;
      /**
       * End underlying iterator
       */
      TIterator myEnd;

      /**
       * Underlying distance function
       */
      DistanceFunctor myDistance;

      // ------------------------- iterator services --------------------------------

    public:

      /**
       * Iterator service.
       * @return begin iterator
       */
      Iterator begin()
      {
        return Iterator ( myBegin );
      }


      /**
       * Iterator service.
       * @param aPoint a Point
       * @return begin iterator at aPoint
       */
      Iterator begin ( const Point &aPoint )
      {
        return Iterator ( myBegin ) + myDistance ( aPoint );
      }

      /**
       * Iterator service.
       * @return begin iterator
       */
      ConstIterator begin() const
      {
        return ConstIterator ( myBegin );
      }


      /**
       * Iterator service.
       * @param aPoint a Point
       * @return begin iterator at aPoint
       */
      ConstIterator begin ( const Point &aPoint ) const
      {
        return ConstIterator ( myBegin ) + myDistance ( aPoint );
      }

      /**
       * Iterator service.
       * @return end iterator
       */
      Iterator end()
      {
        return Iterator ( myEnd );
      }

     /**
        * Iterator service.
       * @return end iterator
       */
      ConstIterator end()  const
      {
        return ConstIterator ( myEnd );
      }

      /**
       * OutputIterator service.
       * @return an output iterator on the first elements
       */
      OutputIterator outputIterator()
      {
        return OutputIterator ( myBegin );
      }

      /**
       * OutputIterator service.
       * @param aPoint a point
       * @return an output iterator on the point
       */
      OutputIterator outputIterator ( const Point &aPoint )
      {
        return OutputIterator ( myBegin ) + myDistance ( aPoint ) ;
      }

      /**
      * ReverseOutputIterator service.
      * @return an output itertor on the first elements
      */
      ReverseOutputIterator routputIterator()
      {
        return ReverseOutputIterator ( this->end() );
      }

      /**
       * ReverseOutputIterator service.
       * @param aPoint a point
       * @return an output iterator on the point
       */
      ReverseOutputIterator routputIterator ( const Point &aPoint )
      {
        return ReverseOutputIterator ( myBegin + myDistance ( aPoint ) + 1 ) ;
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
        return ReverseIterator ( myBegin + myDistance ( aPoint ) + 1 );
      }


      /**
       * Iterator service.
       * @return rend iterator
       */
      ReverseIterator rend()
      {
        return ReverseIterator ( myBegin );
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
        return ConstReverseIterator ( myBegin + myDistance ( aPoint ) + 1 );
      }


      /**
       * Iterator service.
       * @return rend iterator
       */
      ConstReverseIterator rend() const
      {
        return ConstReverseIterator ( myBegin );
      }

      /**
       * Mutable circulator service.
       * @return a circulator
       */
      Circulator c()
      {
        return Circulator ( this->begin(), this->begin(), this->end() );
      }

      /**
       * Reverse mutable circulator service.
       * @return a reverse circulator
       */
      ReverseCirculator rc()
      {
        return ReverseCirculator ( this->c() );
      }

      /**
       * Constant circulator service.
       * @return a constant circulator
       */
      ConstCirculator c() const
      {
        return ConstCirculator ( this->begin(), this->begin(), this->end() );
      }

      /**
       * Reverse constant circulator service.
       * @return a reverse constant circulator
       */
      ConstReverseCirculator rc() const
      {
        return ConstReverseCirculator ( this->c() );
      }

  }; //end class SimpleRandomAccessRangeFromPoint

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////


#endif // !defined SimpleRandomAccessRangeFromPoint_h

#undef SimpleRandomAccessRangeFromPoint_RECURSES
#endif // else defined(SimpleRandomAccessRangeFromPoint_RECURSES)
