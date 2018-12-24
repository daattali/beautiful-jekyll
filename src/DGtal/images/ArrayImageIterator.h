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
 * @file ArrayImageIterator.h
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/06/19
 *
 * This file is part of the DGtal library.
 */

#if defined(ArrayImageIterator_RECURSES)
#error Recursive header files inclusion detected in ArrayImageIterator.h
#else // defined(ArrayImageIterator_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArrayImageIterator_RECURSES

#if !defined ArrayImageIterator_h
/** Prevents repeated inclusion of headers. */
#define ArrayImageIterator_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <ostream>
#include <type_traits>
#include <boost/iterator/iterator_facade.hpp>
#include <DGtal/kernel/domains/Linearizer.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Aim: Random access iterator over an image given his definition domain and viewable domain.
   *
   * Description of template class 'ArrayImageIterator' <p>
   * This iterator spans a viewable domain given an iterable image-like class (see below) defined
   * on a specified full domain. This iterator provides access to the iterable class through classical iterator syntax and, in addition, exposes current point to which the iterator point to.
   * Thus, when it is needed to iterate over an image while knowing the current point ( for example, when filling an image with a formulae that depends on the point), it is faster to use this iterator instead of a classical domain iterator and the use of operator() and setValue.
   *
   * In order to work, the iterable class must expose a dereference method that,
   * given a point and his linearized index (column-major ordered), returns:
   * - a mutable reference to the corresponding value for a mutable iterator.
   * - a copy or a constant reference to the corresponding value for a constant iterator.
   *
   * In addition, the iterable class must have Domain typedef.
   *
   * For an usage example, see ArrayImageAdapter.h .
   *
   * @tparam TIterableClass   Type of the iterable class.
   *
   * @see ArrayImageAdapter.h
   */
  template <
    typename TIterableClass
  >
  class ArrayImageIterator
    : public boost::iterator_facade <
        ArrayImageIterator<TIterableClass>,
        typename TIterableClass::Value,
        std::random_access_iterator_tag,
        decltype( ((TIterableClass*)nullptr)->dereference( TIterableClass::Point::diagonal(0), typename TIterableClass::Point::Coordinate(0) ) )
      >
    {
    // ----------------------- Standard services ------------------------------
    public:

      // Typedefs
      using Self = ArrayImageIterator<TIterableClass>;  ///< Self type.
      using IterableClass = TIterableClass;             ///< Iterable class type.
      using Domain = typename IterableClass::Domain;    ///< Domain type. \todo or in template with default value ?
      using Point = typename Domain::Point;             ///< Point type.
      using Linearizer = DGtal::Linearizer<Domain, ColMajorStorage>; ///< Linearizer type. \todo hard-coded, but must be later set as template.
      using Reference = decltype( ((IterableClass*)nullptr)->dereference( Point::diagonal(0), typename Point::Coordinate(0) ) ); ///< Return type when dereferencing this iterator.

      /// Default constructor.
      ArrayImageIterator();

      /** Iterator from a point.
       *
       * @param anIterableClassPtr  Pointer to the iterable class instance.
       * @param aFullDomain         Full domain of the image.
       * @param aViewDomain         Viewable domain that the iterator will span.
       * @param aPoint              Point to which the iterator will point.
       */
      ArrayImageIterator( IterableClass* anIterableClassPtr, Domain const& aFullDomain, Domain const& aViewDomain, Point const& aPoint );

      /** Iterator pointing to the first value.
       *
       * @param anIterableClassPtr  Pointer to the iterable class instance.
       * @param aFullDomain         Full domain of the image.
       * @param aViewDomain         Viewable domain that the iterator will span.
       */
      ArrayImageIterator( IterableClass* anIterableClassPtr, Domain const& aFullDomain, Domain const& aViewDomain );

      /** Iterator pointing to the first value and spanning the whole domain.
       *
       * @param anIterableClassPtr  Pointer to the iterable class instance.
       * @param aFullDomain         Full domain of the image.
       */
      ArrayImageIterator( IterableClass* anIterableClassPtr, Domain const& aFullDomain );

      /** Iterator pointing after the last value of the viewable domain.
       *
       * @param anIterableClassPtr  Pointer to the iterable class instance.
       * @param aFullDomain         Full domain of the image.
       * @param aViewDomain         Viewable domain that the iterator will span.
       */
      ArrayImageIterator( IterableClass* anIterableClassPtr, Domain const& aFullDomain, Domain const& aViewDomain, bool /* last */ );

      /** Iterator pointing after the last value of the whole domain.
       *
       * @param anIterableClassPtr  Pointer to the iterable class instance.
       * @param aFullDomain         Full domain of the image.
       */
      ArrayImageIterator( IterableClass* anIterableClassPtr, Domain const& aFullDomain, bool /* last */ );

      /** Copy constructor with type interoperability.
       *
       * @param other An another iterator whose iterable class pointer is convertible to the current iterable class pointer type.
       */
      template < typename TOtherIterableClass >
      ArrayImageIterator(
          ArrayImageIterator<TOtherIterableClass> const& other,
          typename std::enable_if< std::is_convertible<TOtherIterableClass*, IterableClass*>::value >::type* = 0
      );

      /** Move constructor with type interoperability.
       *
       * @param other An another iterator whose iterable class pointer is convertible to the current iterable class pointer type.
       */
      template < typename TOtherIterableClass >
      ArrayImageIterator(
          ArrayImageIterator<TOtherIterableClass> && other,
          typename std::enable_if< std::is_convertible<TOtherIterableClass*, IterableClass*>::value >::type* = 0
      ) noexcept;

      /// Destructor.
      ~ArrayImageIterator();

      /** Copy assignment with type interoperability.
       *
       * @tparam TOtherIterableClass  The type of the other iterable class (auto-deduced).
       * @param other An another iterator whose iterable class pointer is convertible to the current iterable class pointer type.
       * @return a reference to this class instance.
       */
      template < typename TOtherIterableClass >
      typename std::enable_if<
          std::is_convertible<TOtherIterableClass*, IterableClass*>::value,
          Self& >::type
      operator= (
          ArrayImageIterator<TOtherIterableClass> const& other
      );

      /** Move assignment constructor with type interoperability.
       *
       * @tparam TOtherIterableClass  The type of the other iteratable class (auto-deduced).
       * @param other An another iterator whose iterable class pointer is convertible to the current iterable class pointer type.
       * @return a reference to this class instance.
       */
      template < typename TOtherIterableClass >
      typename std::enable_if<
          std::is_convertible<TOtherIterableClass*, IterableClass*>::value,
          Self& >::type
      operator= (
          ArrayImageIterator<TOtherIterableClass> && other
      );


      // ----------------------- Interface --------------------------------------
    public:

      /**
       * @return the point behind this iterator.
       */
      inline Point const& getPoint() const noexcept;

      /**
       * @return the distance from this iterator to a given point.
       * @param aPoint  The point.
       */
      inline
      std::ptrdiff_t distance_to( Point const& aPoint ) const noexcept;

      /**
       * Writes/Displays the object on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const;

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const;

    // ------------------------- Private Datas --------------------------------
    private:
      IterableClass* myIterableClassPtr; ///< Pointer to the iterable class.
      Domain myFullDomain;  ///< Full domain of the image.
      Domain myViewDomain;  ///< Iterable (viewable) domain of the image.
      Point myFullExtent;   ///< Extent of the full domain.
      Point myViewExtent;   ///< Extent of the viewable domain.
      Point myPoint;        ///< Current point where the iterator point to.
      typename Point::Coordinate myFullIndex; ///< Linearized index of the current point.

      // ------------------------- Hidden services ------------------------------
    private:

      // Friendship
      template <class> friend class ArrayImageIterator; ///< Friendship of interoperability. \see http://www.boost.org/doc/libs/1_58_0/libs/iterator/doc/iterator_facade.html
      friend class boost::iterator_core_access; ///< Friendship of interoperability. \see http://www.boost.org/doc/libs/1_58_0/libs/iterator/doc/iterator_facade.html

      /// Increment of one step.
      void increment();

      /// Decrement of one step.
      void decrement();

      /** Test equality with other iterator.
       * @param other The other iterator.
       */
      inline
      bool equal( Self const& other ) const;

      /// Dereference.
      inline
      Reference dereference() const;

      /** Calculate the distance to other iterator.
       * @param other The other iterator.
       * @return the distance.
       */
      inline
      std::ptrdiff_t distance_to( Self const& other ) const ;

      /** Advance by n steps.
       * @param n The number of steps.
       * \todo Find a more efficient implementation ...
       */
      void advance( std::ptrdiff_t n );

    }; // end of class ArrayImageIterator


  /**
   * Overloads 'operator<<' for displaying objects of class 'ArrayImageIterator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ArrayImageIterator' to write.
   * @return the output stream after the writing.
   */
  template <typename TIterableClass>
  std::ostream&
  operator<< ( std::ostream & out, const ArrayImageIterator<TIterableClass> & object );

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/images/ArrayImageIterator.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArrayImageIterator_h

#undef ArrayImageIterator_RECURSES
#endif // else defined(ArrayImageIterator_RECURSES)

