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
 * @file Linearizer.h
 * @author Roland Denis (\c roland.denis@univ-smb.fr )
 * LAboratory of MAthematics - LAMA (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2015/06/18
 *
 * This file is part of the DGtal library.
 */

#if defined(Linearizer_RECURSES)
#error Recursive header files inclusion detected in Linearizer.h
#else // defined(Linearizer_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Linearizer_RECURSES

#if !defined Linearizer_h
/** Prevents repeated inclusion of headers. */
#define Linearizer_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <DGtal/kernel/domains/HyperRectDomain.h> // Only for specialization purpose.
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////

  /**
   * @brief Tag (empty structure) specifying a row-major storage order.
   *
   * @see Linearizer
   */
  struct RowMajorStorage {};

  /**
   * @brief Tag (empty structure) specifying a col-major storage order.
   *
   * @see Linearizer
   */
  struct ColMajorStorage {};

  /////////////////////////////////////////////////////////////////////////////
  /**
   * @brief Aim: Linearization and de-linearization interface for domains.
   *
   * Description of class 'Linearizer' <p>
   * This class is empty but there is a specialization for HyperRectDomain.
   *
   * @tparam  TDomain       Type of the domain.
   * @tparam  TStorageOrder Storage Order (RowMajorStorage of ColMajorStorage).
   *
   */
  template <
      typename TDomain,
      typename TStorageOrder = ColMajorStorage
    >
  struct Linearizer;

  /**
   * @brief Aim: Linearization and de-linearization interface for HyperRectDomain.
   *
   * This is a static class that provides point linearization (point to index) and de-linearization (index to point) for storages working on HyperRectDomain.
   *
   * The storage order can be specified by template (default is colum-major ordered).
   *
   * Example:
   * @code
   * typedef SpaceND<2>             Space;
   * tydedef HyperRectDomain<Space> Domain;
   * typedef typename Space::Point  Point;
   *
   * const Domain domain( Point(0, 1), Point(4, 3) );
   *
   * typename Linearizer<Domain>::Size id = Linearizer<Domain>::getIndex( Point(2, 2), domain ); // returns 7.
   *
   * Point pt = Linearizer<Domain>::getPoint( 7, domain); // returns Point(2,2).
   * @endcode
   *
   * @tparam  TSpace       Type of the space of the HyperRectDomain (auto-deduced from TDomain template, see Linearizer).
   * @tparam  TStorageOrder Storage Order (RowMajorStorage of ColMajorStorage).
   */
  template <
      typename TSpace,
      typename TStorageOrder
    >
  struct Linearizer< HyperRectDomain<TSpace>, TStorageOrder >
    {
      // Usefull typedefs
      typedef HyperRectDomain<TSpace> Domain; ///< The domain type.
      typedef typename TSpace::Point Point;   ///< The point type.
      typedef Point Extent;                   ///< The domain's extent type.
      typedef typename TSpace::Size  Size;    ///< The space's size type.

      /** Linearized index of a point, given the domain lower-bound and extent.
       *
       * @param[in] aPoint      The point to be linearized.
       * @param[in] aLowerBound The lower-bound of the domain.
       * @param[in] anExtent    The extent of the domain.
       * @return the linearized index of the point.
       */
      static inline
      Size getIndex( Point aPoint, Point const& aLowerBound, Extent const& anExtent );

      /** Linearized index of a point, given the domain extent.
       *
       * The lower-bound of the domain is defined to the origin.
       *
       * @param[in] aPoint    The Point to be linearized.
       * @param[in] anExtent  The extent of the domain.
       * @return the linearized index of the point.
       */
      static inline
      Size getIndex( Point aPoint, Extent const& anExtent );

      /** Linearized index of a point, given a domain.
       *
       * @param[in] aPoint    The Point to be linearized.
       * @param[in] aDomain   The domain.
       * @return the linearized index of the point.
       */
      static inline
      Size getIndex( Point aPoint, Domain const& aDomain );

      /** De-linearization of an index, given the domain lower-bound and extent.
       *
       * @param[in] anIndex     The linearized index.
       * @param[in] aLowerBound The lower-bound of the domain.
       * @param[in] anExtent    The domain extent.
       * @return  the point whose linearized index is anIndex.
       */
      static inline
      Point getPoint( Size anIndex, Point const& aLowerBound, Extent const& anExtent );

      /** De-linearization of an index, given the domain extent.
       *
       * The lower-bound of the domain is set to the origin.
       *
       * @param[in] anIndex   The linearized index.
       * @param[in] anExtent  The domain extent.
       * @return  the point whose linearized index is anIndex.
       */
      static inline
      Point getPoint( Size anIndex, Extent const& anExtent );

      /** De-linearization of an index, given a domain.
       *
       * @param[in] anIndex   The linearized index.
       * @param[in] aDomain   The domain.
       * @return  the point whose linearized index is anIndex.
       */
      static inline
      Point getPoint( Size anIndex, Domain const& aDomain );

  }; // end of class Linearizer

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/domains/Linearizer.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Linearizer_h

#undef Linearizer_RECURSES
#endif // else defined(Linearizer_RECURSES)

