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
 * @file ArrayImageAdapter.h
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/06/19
 *
 * This file is part of the DGtal library.
 */

#if defined(ArrayImageAdapter_RECURSES)
#error Recursive header files inclusion detected in ArrayImageAdapter.h
#else // defined(ArrayImageAdapter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define ArrayImageAdapter_RECURSES

#if !defined ArrayImageAdapter_h
/** Prevents repeated inclusion of headers. */
#define ArrayImageAdapter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <boost/concept/assert.hpp>
#include <boost/iterator/iterator_concepts.hpp>
#include <iterator>
#include <type_traits>

#include <DGtal/base/Common.h>
#include <DGtal/images/CConstImage.h>
#include <DGtal/images/ArrayImageIterator.h>
#include <DGtal/base/IteratorCompletion.h>
#include <DGtal/kernel/domains/Linearizer.h>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  /// @cond
  /**
   * @brief Aim: Image adapter for generic arrays with sub-domain view capability.
   *
   * Description of template class 'ArrayImageAdapter' <p>
   * It is an empty class that is specialized for HyperRectDomain (see @ref DGtal::ArrayImageAdapter< TArrayIterator, HyperRectDomain< TSpace > >).
   *
   * @tparam TArrayIterator Type of a random-access iterator over the datas (can be a T* pointer).
   * @tparam TDomain  Type of the domain (must be an HyperRectDomain).
   */
  template <
    typename TArrayIterator,
    typename TDomain
  >
  class ArrayImageAdapter;
  /// @endcond

  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Aim: Image adapter for generic arrays with sub-domain view capability.
   *
   * Description of template class 'ArrayImageAdapter' <p>
   * This creates an image (concepts::CImage compatible) given a random-access iterator (that can be a T* pointer)
   * that fully spans an array of data, and two domains:
   * - the definition (full) domain whose size is equal to the data size.
   * - the viewable domain, a subset of the full-domain, on which the image is accessible.
   * This adapted image is writable iff the given iterator is mutable.
   *
   * The available iterators for this image can return the corresponding point and are
   * faster than using an iterator over the domain (see ArrayImageIterator).
   * Reverse iterators and ranges are defined in the inherited class IteratorCompletion.
   *
   * Some helpers are available (see makeArrayImageAdapterFromIterator and makeArrayImageAdapterFromImage)
   * for easy construction (with template deduction) from an iterator or an CConstImage model.
   *
   * It is important to note that, since this class only adapts an already existing storage to an image, all
   * copy operations (constructor and operator) lead to shallow copies.
   *
   * The following code snippet demonstrates how to use ArrayImageAdapter from converting a native C-array to an image:
   * @snippet images/exampleArrayImageAdapter.cpp ArrayImageAdapter_example
   *
   * Another usage example is illustrated in the image module documentation, \ref arrayimageadat.
   *
   * @remark The given random-access iterator can be either mutable or constant.
   *
   * @warning The array must be column-major ordered (but row-major order could be later accepted via template parameter, if needed ?)
   * @warning The domain must be an HyperRectDomain.
   *
   * @tparam TArrayIterator Type of a random-access iterator over the datas (can be a T* pointer).
   * @tparam TSpace Type of the space associated to the HyperRectDomain (auto-deduced from TDomain template, see ArrayImageAdapter).
   *
   * @see makeArrayImageAdapterFromIterator
   * @see makeArrayImageAdapterFromImage
   * @see exampleArrayImageAdapter.cpp
   */
  template <
    typename TArrayIterator,
    typename TSpace
  >
  class ArrayImageAdapter< TArrayIterator, HyperRectDomain<TSpace> >
      : public IteratorCompletion< ArrayImageAdapter< TArrayIterator, HyperRectDomain<TSpace> > >
    {

    // Checks Random-access iterator concept on TArrayIterator
    BOOST_CONCEPT_ASSERT( (boost_concepts::RandomAccessTraversalConcept<TArrayIterator>) );

    public:
      // Aliases
      using Self = ArrayImageAdapter<TArrayIterator, HyperRectDomain<TSpace> >;           ///< Self type.
      using ArrayIterator   = TArrayIterator;                                             ///< The given random-access iterator's type.
      using Value           = typename std::iterator_traits<ArrayIterator>::value_type;   ///< The value type stored in the image.
      using Reference       = typename std::iterator_traits<ArrayIterator>::reference;    ///< Mutable reference type.
      using ConstReference  = const Reference;                                            ///< Constant reference type.

      // DGtal aliases and constant
      using Domain    = HyperRectDomain<TSpace>;      ///< Domain type.
      using Point     = typename Domain::Point;       ///< Point type.
      using Dimension = typename Domain::Dimension;   ///< Dimension type.
      using Size      = typename Domain::Size;        ///< Size type.
      using Vector    = typename Domain::Vector;      ///< Vector type.
      using Vertex    = Point;                        ///< Vertex type.
      using Integer   = typename Domain::Integer;     ///< Integer type.
      BOOST_STATIC_CONSTANT( Dimension, dimension = Domain::dimension );  ///< Rank of the space.

      using Linearizer = DGtal::Linearizer<Domain, ColMajorStorage>; ///< Linearization of the points.

      // Iterators & Ranges
      template <class> friend class ArrayImageIterator;
      using Iterator      = typename IteratorCompletionTraits<Self>::Iterator;      ///< Mutable iterator based on ArrayImageIterator.
      using ConstIterator = typename IteratorCompletionTraits<Self>::ConstIterator; ///< Constant iterator base on ArrayImageIterator.

      /** Default constructor.
       *
       * Empty allocated memory on empty domains.
       */
      ArrayImageAdapter()
        : myArrayIterator{nullptr}
        , myFullDomain{}
        , myViewDomain{}
        {}

      /** Constructor from iterator, full domain and viewable domain.
       *
       * @param anArrayIterator   A random-access iterator on the datas.
       * @param aFullDomain       The domain span by the given iterator.
       * @param aViewDomain       The viewable domain of this image.
       */
      ArrayImageAdapter( ArrayIterator anArrayIterator, Domain const& aFullDomain, Domain const& aViewDomain )
          : myArrayIterator(anArrayIterator)
          , myFullDomain{ aFullDomain }
          , myViewDomain{ aViewDomain }
        {
          ASSERT_MSG(
                 aFullDomain.lowerBound().isLower( aViewDomain.lowerBound() )
              && aFullDomain.upperBound().isUpper( aViewDomain.upperBound() ),
              "The viewable domain must be included into the full domain."
          );
        }

      /** Constructor from iterator and full domain.
       *
       * The viewable domain is then the full domain.
       *
       * @param anArrayIterator   A random-access iterator on the datas.
       * @param aFullDomain       The domain span by the given iterator.
       */
      ArrayImageAdapter( ArrayIterator anArrayIterator, Domain const& aFullDomain )
          : ArrayImageAdapter( anArrayIterator, aFullDomain, aFullDomain )
        {
        }

      /** Copy constructor with other viewable domain.
       *
       * The full domain will be the same as the copied ArrayImageAdapter. Only the viewable domain will be modified.
       *
       * @warning Since this class in only a view on a independant storage, it does a shallow copy.
       *
       * @param other         An another ArrayImageAdapter instance.
       * @param aViewDomain   A new viewable domain for this image.
       */
      ArrayImageAdapter( Self const& other, Domain const& aViewDomain )
          : ArrayImageAdapter( other.myArrayIterator, other.myFullDomain, aViewDomain )
        {}

      /**
       * @return the image viewable domain.
       */
      inline
      Domain domain() const
        {
          return myViewDomain;
        }

      /**
       * @return the full domain where the allocated memory is defined.
       */
      inline
      Domain fullDomain() const
        {
          return myFullDomain;
        }

      /** Reads a value given a point lying inside the full domain.
       *
       * @param[in] aPoint  The point.
       * @return a constant value.
       */
      inline
      Value getValue( Point const& aPoint ) const
        {
          ASSERT_MSG(
              myFullDomain.isInside(aPoint),
              "The point is outside the full domain."
          );

          return myArrayIterator[ Linearizer::getIndex(aPoint, myFullDomain) ];
        }

      /** Sets a value given a point lying inside the full domain.
       *
       * @param[in] aPoint  The point.
       * @param[in] aValue  The value.
       */
      inline
      void setValue( Point const& aPoint, Value aValue )
        {
          ASSERT_MSG(
              myFullDomain.isInside(aPoint),
              "The point is outside the full domain."
          );

          myArrayIterator[ Linearizer::getIndex(aPoint, myFullDomain) ] = aValue;
        }

      /** Reads a value given a point lying inside the full domain.
       *
       * @param[in] aPoint  The point.
       * @return a constant value.
       */
      inline
      Value operator() ( Point const& aPoint ) const
        {
          return getValue(aPoint);
        }

      /**
       * @return a mutable iterator pointing to the lower bound of the viewable domain.
       */
      inline
      Iterator begin()
        {
          return Iterator{ this, myFullDomain, myViewDomain };
        }

      /**
       * @return a constant iterator pointing to the lower bound of the viewable domain.
       */
      inline
      ConstIterator begin() const
        {
          return ConstIterator{ this, myFullDomain, myViewDomain };
        }

      /**
       * @return a constant iterator pointing to the lower bound of the viewable domain.
       */
      inline
      ConstIterator cbegin() const
        {
          return ConstIterator{ this, myFullDomain, myViewDomain };
        }

      /**
       * @return an mutable iterator pointing after the upper bound of the viewable domain.
       */
      inline
      Iterator end()
        {
          return Iterator{ this, myFullDomain, myViewDomain, true };
        }

      /**
       * @return a constant iterator pointing after the upper bound of the viewable domain.
       */
      inline
      ConstIterator end() const
        {
          return ConstIterator{ this, myFullDomain, myViewDomain, true };
        }

      /**
       * @return a constant iterator pointing after the upper bound of the viewable domain.
       */
      inline
      ConstIterator cend() const
        {
          return ConstIterator{ this, myFullDomain, myViewDomain, true };
        }


    public: // Should be private since ArrayImageIterator is a friend but g++ 4.9.1 don't care ... (no prob with clang++ 3.5.0)

      /** Dereference of a mutable iterator.
       *
       * @param[in] aFullIndex  Linearized index of the point.
       * @return a mutable reference to the value associated to the point.
       */
      inline
      Reference dereference( Point const& /* aPoint */, typename Point::Coordinate aFullIndex )
        {
          ASSERT_MSG(
              aFullIndex >= 0 && static_cast<typename Domain::Size>(aFullIndex) < myFullDomain.size(),
              "linearized index out of bounds !"
          );
          return myArrayIterator[aFullIndex];
        }

      /** Dereference of a constant iterator.
       *
       * @param[in] aFullIndex  Linearized index of the point.
       * @return a constant reference to the value associated to the point.
       */
      inline
      ConstReference dereference( Point const& /* aPoint */, typename Point::Coordinate aFullIndex ) const
        {
          ASSERT_MSG(
              aFullIndex >= 0 && static_cast<typename Domain::Size>(aFullIndex) < myFullDomain.size(),
              "linearized index out of bounds !"
          );
          return myArrayIterator[aFullIndex];
        }

    // ----------------------- Interface --------------------------------------
    public:
      /**
       * Writes/Displays the object on an output stream.
       * @param out the output stream where the object is written.
       */
      void selfDisplay ( std::ostream & out ) const
        {
          out << "[ArrayImageAdapter] with full domain " << myFullDomain << " and viewable domain " << myViewDomain;
        }

      /**
       * Checks the validity/consistency of the object.
       * @return 'true' if the object is valid, 'false' otherwise.
       */
      bool isValid() const
        {
          return true;
        }

    // ------------------------- Private Datas --------------------------------
    private:
      ArrayIterator myArrayIterator; ///< Pointer to the allocated memory.
      Domain myFullDomain;  ///< Definition (full) domain.
      Domain myViewDomain;  ///< Viewable domain.

    }; // end of class ArrayImageAdapter

  //! [IteratorCompletionTraits]

  /** Iterator traits specialized for ArrayImageAdapter.
   *
   * \see IteratorCompletion
   */
  template <
    typename TArrayIterator,
    typename TDomain
  >
  class IteratorCompletionTraits< ArrayImageAdapter<TArrayIterator, TDomain> >
    {
    public:
      using Self = ArrayImageAdapter<TArrayIterator, TDomain>;  ///< Self type.
      using Iterator = ArrayImageIterator<Self>; ///< Mutable iterator.
      using ConstIterator = ArrayImageIterator<const Self>; ///< Constant iterator.

      /** Functor that returns the distance between the domain's lower bound and a given point.
       *
       * \see SimpleRandomAccessRangeFromPoint and SimpleRandomAccessConstRangeFromPoint.
       */
      class DistanceFunctor
        {
        public:
          using Domain = typename Self::Domain;         ///< Domain type.
          using Point = typename Self::Point;           ///< Point type.
          using Difference = typename Self::Difference; ///< Type of the difference between two iterators.

          /** Constructor from an image.
           * @param anImage Constant pointer to an image.
           */
          DistanceFunctor( Self const* anImage )
            : myDomain( anImage->domain() )
            {}

          /** Return the distance between the domain's lower bound and the given point.
           * @param aPoint  The point.
           * @return the distance.
           */
          Difference operator() ( Point const& aPoint ) const
            {
              ASSERT_MSG(
                  myDomain.isInside(aPoint),
                  "The point is outside the domain !"
              );
              return Linearizer<Domain, ColMajorStorage>::getIndex( aPoint, myDomain );
            }

        private:
          Domain myDomain; ///< Stored domain to avoid iterator corruption if domain changed.
        };

    }; // end of specialized class IteratorCompletionTraits

  //! [IteratorCompletionTraits]

  /**
   * Overloads 'operator<<' for displaying objects of class 'ArrayImageIterator'.
   * @param out the output stream where the object is written.
   * @param object the object of class 'ArrayImageIterator' to write.
   * @return the output stream after the writing.
   */
  template <
    typename TArrayIterator,
    typename TDomain
  >
  std::ostream&
  operator<< ( std::ostream & out, const ArrayImageAdapter<TArrayIterator, TDomain> & object )
    {
      object.selfDisplay( out );
      return out;
    }


  // ------------------ ArrayImageAdapter construction helpers ----------------

  /** Returns an ArrayImageAdapter from an iterator, a full domain and a viewable domain.
   *
   * @param anArrayIterator   A random-access iterator on the datas.
   * @param aFullDomain       The domain span by the given iterator.
   * @param aViewDomain       The viewable domain of this image.
   * @return an ArrayImageAdapter instance.
   */
  template <
    typename TArrayIterator,
    typename TDomain
  >
  ArrayImageAdapter< TArrayIterator, TDomain >
  makeArrayImageAdapterFromIterator( TArrayIterator anArrayIterator, TDomain const& aFullDomain, TDomain const& aViewDomain )
    {
      return { anArrayIterator, aFullDomain, aViewDomain };
    }

  /** Returns an ArrayImageAdapter from an iterator and a full domain.
   *
   * The viewable domain will be the same as the full domain.
   *
   * @param anArrayIterator   A random-access iterator on the datas.
   * @param aFullDomain       The domain span by the given iterator.
   * @return an ArrayImageAdapter instance.
   */
  template <
    typename TArrayIterator,
    typename TDomain
  >
  ArrayImageAdapter< TArrayIterator, TDomain >
  makeArrayImageAdapterFromIterator( TArrayIterator anArrayIterator, TDomain const& aFullDomain )
    {
      return { anArrayIterator, aFullDomain, aFullDomain };
    }

  /** Returns an ArrayImageAdapter from an image and a viewable domain.
   *
   * @param anImage       The image that models the CConstImage concept.
   * @param aViewDomain   The viewable domain of this image.
   */
  template <
    typename TImage,
    typename TDomain = typename TImage::Domain
  >
  // We use decltype on begin() iterator because it returns the constant iterator
  //  if the image is constant while ::Iterator typedef returns the mutable iterator.
  ArrayImageAdapter< decltype( ((TImage*)nullptr)->begin() ), TDomain >
  makeArrayImageAdapterFromImage( TImage & anImage, TDomain const& aViewDomain )
    {
      // Remove constness because CConstImage requires assignability.
      BOOST_CONCEPT_ASSERT( (DGtal::concepts::CConstImage< typename std::remove_const<TImage>::type >) );

      return { anImage.begin(), anImage.domain(), aViewDomain };
    }

  /** Returns an ArrayImageAdapter from an image.
   *
   * The viewable domain will be the same as the given image domain.
   *
   * @param anImage       The image that models the CConstImage concept.
   */
  template <
    typename TImage,
    typename TDomain = typename TImage::Domain
  >
  // We use decltype on begin() iterator because it returns the constant iterator
  //  if the image is constant while ::Iterator typedef returns the mutable iterator.
  ArrayImageAdapter< decltype( ((TImage*)nullptr)->begin() ), TDomain >
  makeArrayImageAdapterFromImage( TImage & anImage )
    {
      // Remove constness because CConstImage requires assignability.
      BOOST_CONCEPT_ASSERT( (DGtal::concepts::CConstImage< typename std::remove_const<TImage>::type >) );

      return { anImage.begin(), anImage.domain(), anImage.domain() };
    }

} // namespace DGtal

///////////////////////////////////////////////////////////////////////////////
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined ArrayImageAdapter_h

#undef ArrayImageAdapter_RECURSES
#endif // else defined(ArrayImageAdapter_RECURSES)

