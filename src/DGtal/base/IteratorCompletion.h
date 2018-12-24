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
 * @file IteratorCompletion.h
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/06/23
 *
 * This file is part of the DGtal library.
 */

#if defined(IteratorCompletion_RECURSES)
#error Recursive header files inclusion detected in IteratorCompletion.h
#else // defined(IteratorCompletion_RECURSES)
/** Prevents recursive inclusion of headers. */
#define IteratorCompletion_RECURSES

#if !defined IteratorCompletion_h
/** Prevents repeated inclusion of headers. */
#define IteratorCompletion_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <boost/iterator/reverse_iterator.hpp>
#include <DGtal/base/SimpleRandomAccessRangeFromPoint.h>
#include <DGtal/base/SimpleRandomAccessConstRangeFromPoint.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Aim: Traits that must be specialized for each IteratorCompletion derived class.
   *
   * This traits must shown:
   * - a typedef Iterator corresponding to the derived class mutable random-access iterator.
   * - a typedef ConstIterator corresponding to the derived class constant random-access iterator.
   * - a class DistanceFunctor, constructible from a pointer to the derived class and
   *   that behaves like a distance functor from the begin() iterator to a given point.
   *   (see SimpleRandomAccessRangeFromPoint and SimpleRandomAccessConstRangeFromPoint)
   *
   * @see IteratorCompletion
   * @see the specialization of IteratorCompletionTraits for ArrayImageView.
   *
   * @tparam TDerived Type of the derived class (CRTP).
   */
  template < typename TDerived >
  class IteratorCompletionTraits;

  /**
   * @brief Aim: Class that uses CRTP to add reverse iterators and ranges to a derived class.
   *
   * Description of template class 'IteratorCompletionTraits' <p>
   * This class adds new iterators to a given class if it provides a minimal interface for random-access iterators related to points.
   *
   * More precisely, it provides:
   * - reverse mutable and constant iterators,
   * - mutable and constant ranges,
   * - constant normal and reverse iterators from C++11 if the class provides cbegin and cend methods.
   *
   * Each derived class of IteratorCompletion must specialize IteratorCompletionTraits in order to provide
   * enough informations on his iterators, especially a distance functor between a given point and the begin iterator.
   *
   * @tparam TDerived Type of the derived class (CRTP).
   *
   * The following snippets illustrate how to use it to easily build a concepts::CImage model from a C-style array
   * (better use ArrayImageAdapter for that purpose).
   *
   * After common includes:
   * @snippet exampleIteratorCompletion.cpp includes
   * we start with the head of our class, including typedefs, constructor and destructor:
   * @snippet exampleIteratorCompletion.cpp MyImageHeader
   * As you can see, the MyImage class inherits from IteratorCompletion templated with his own type (CRTP).
   * The public inheritance is necessary is order to make visible the methods and typedefs provided by IteratorCompletion.
   * 
   * Then, we add the basic interface needed for images:
   * @snippet exampleIteratorCompletion.cpp CImageBasicInterface
   * and the minimal iterator accessors:
   * @snippet exampleIteratorCompletion.cpp BasicIteratorInterface
   *
   * The class is finally closed with the private members:
   * @snippet exampleIteratorCompletion.cpp PrivateMembers
   * 
   * A specialization of IteratorCompletionTraits is needed in order to provide IteratorCompletion with
   * the Iterator and ConstIterator type, and a DistanceFunctor that returns the distance from the begin 
   * iterator to a given point (see SimpleRandomAccessRangeFromPoint and SimpleRandomAccessConstRangeFromPoint):
   * @snippet exampleIteratorCompletion.cpp IteratorCompletionTraits
   *
   * We have now a concepts::CImage model that can be used like any image:
   * @snippet exampleIteratorCompletion.cpp UsageExample
   *
   * @see ArrayImageAdapter.h
   * @see exampleIteratorCompletion.cpp
   */
  template <
    typename TDerived
  >
  class IteratorCompletion
    {
    public:

      typedef typename IteratorCompletionTraits<TDerived>::Iterator           Iterator;         ///< Mutable iterator type.
      typedef typename IteratorCompletionTraits<TDerived>::ConstIterator      ConstIterator;    ///< Constant iterator type.
      typedef typename IteratorCompletionTraits<TDerived>::DistanceFunctor    DistanceFunctor;  ///< Type of the functor calculating the distance between iterators.

      typedef boost::reverse_iterator<Iterator>       ReverseIterator;      ///< Mutable reverse iterator type.
      typedef boost::reverse_iterator<ConstIterator>  ConstReverseIterator; ///< Constant reverse iterator type.
      typedef SimpleRandomAccessRangeFromPoint< ConstIterator, Iterator, DistanceFunctor >  Range;      ///< Mutable range type.
      typedef SimpleRandomAccessConstRangeFromPoint< ConstIterator, DistanceFunctor >       ConstRange; ///< Constant range type.
      typedef std::ptrdiff_t    Difference;   ///< Type of the distance between two iterators.

      /**
       * @return  a mutable reverse-iterator pointing to the last value.
       * @warning the derived class must have a end() method that returns a mutable bidirectional iterator.
       */
      ReverseIterator rbegin()
        {
          return ReverseIterator( static_cast<TDerived*>(this)->end() );
        }

      /**
       * @return  a constant reverse-iterator pointing to the last value.
       * @warning the derived class must have a end() method that returns a constant bidirectional iterator.
       */
      inline
      ConstReverseIterator rbegin() const
        {
          return ConstReverseIterator( static_cast<TDerived*>(this)->end() );
        }

      /**
       * @return  a constant reverse-iterator pointing to the last value (C++11).
       * @warning the derived class must have a cend() method that returns a constant bidirectional iterator.
       */
      inline
      ConstReverseIterator crbegin() const
        {
          return ConstReverseIterator( static_cast<TDerived*>(this)->cend() );
        }

      /**
       * @return  a mutable reverse-iterator pointing before the first value.
       * @warning the derived class must have a begin() method that returns a mutable bidirectional iterator.
       */
      inline
      ReverseIterator rend()
        {
          return ReverseIterator( static_cast<TDerived*>(this)->begin() );
        }

      /**
       * @return  a constant reverse-iterator pointing before the first value.
       * @warning the derived class must have a begin() method that returns a constant bidirectional iterator.
       */
      inline
      ConstReverseIterator rend() const
        {
          return ConstReverseIterator( static_cast<TDerived*>(this)->begin() );
        }

      /**
       * @return  a constant reverse-iterator pointing before the first value (C++11).
       * @warning the derived class must have a cbegin() method that returns a constant bidirectional iterator.
       */
      inline
      ConstReverseIterator crend() const
        {
          return ConstReverseIterator( static_cast<TDerived*>(this)->cbegin() );
        }

      /**
       * @return  a mutable range over the derived class values.
       * @warning the derived class must have begin() and end() methods that return mutable random-access iterators.
       * @warning In addition, the class must provide a distance functor to a point.
       */
      inline
      Range range()
        {
          TDerived* const derived = static_cast<TDerived*>(this);
          return Range(
              derived->begin(),
              derived->end(),
              typename IteratorCompletionTraits<TDerived>::DistanceFunctor( derived )
          );
        }

      /**
       * @return  a constant range over the derived class values.
       * @warning the derived class must have begin() and end() methods that return constant random-access iterators.
       * @warning In addition, the class must provide a distance functor to a point.
       */
      inline
      ConstRange constRange() const
        {
          TDerived const* const derived = static_cast<TDerived const*>(this);
          return ConstRange(
              derived->begin(),
              derived->end(),
              typename IteratorCompletionTraits<TDerived>::DistanceFunctor( derived )
          );
        }

    protected:

      /// Protected destructor to avoid memory leak.
      ~IteratorCompletion()
        {}
    };

} // namespace DGtal

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined IteratorCompletion_h

#undef IteratorCompletion_RECURSES
#endif // else defined(IteratorCompletion_RECURSES)

