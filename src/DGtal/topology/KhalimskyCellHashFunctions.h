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
 * @file KhalimskyCellHashFunctions.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2015/12/31
 *
 * This file is part of the DGtal library.
 */

#if defined(KhalimskyCellHashFunctions_RECURSES)
#error Recursive header files inclusion detected in KhalimskyCellHashFunctions.h
#else // defined(KhalimskyCellHashFunctions_RECURSES)
/** Prevents recursive inclusion of headers. */
#define KhalimskyCellHashFunctions_RECURSES

#if !defined KhalimskyCellHashFunctions_h
/** Prevents repeated inclusion of headers. */
#define KhalimskyCellHashFunctions_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include <boost/functional/hash.hpp>
//////////////////////////////////////////////////////////////////////////////


namespace std {
  /**
   * Extend std namespace to define a std::hash function on
   * DGtal::KhalimskyCell.
   *
   */
  template < DGtal::Dimension dim,
             typename TInteger >
  struct hash< DGtal::KhalimskyCell< dim, TInteger > >
  {
    size_t operator()(const DGtal::KhalimskyCell< dim, TInteger > & pp) const
    {
      auto const& p = pp.preCell();
      return boost::hash_range(p.coordinates.begin(), p.coordinates.end());
    }
  };

  /**
   * Extend std namespace to define a std::hash function on
   * DGtal::SignedKhalimskyCell.
   *
   */
  template < DGtal::Dimension dim,
             typename TInteger >
  struct hash< DGtal::SignedKhalimskyCell< dim, TInteger > >
  {
    size_t operator()(const DGtal::SignedKhalimskyCell< dim, TInteger > & pp) const
    {
      auto const& p = pp.preCell();
      return p.positive
        ? boost::hash_range(p.coordinates.begin(), p.coordinates.end())
        : boost::hash_range(p.coordinates.begin(), p.coordinates.end()) ^ ( (size_t) 0x7a0d3fe9 );
    }
  };

}

namespace boost{
  /**
   * Extend boost namespace to define a boost::hash function on
   * DGtal::KhalimskyCell.
   *
   */
  template < DGtal::Dimension dim,
             typename TInteger >
  struct hash< DGtal::KhalimskyCell< dim, TInteger > >
  {
    size_t operator()(const DGtal::KhalimskyCell< dim, TInteger > & pp) const
    {
      auto const& p = pp.preCell();
      return boost::hash_range(p.coordinates.begin(), p.coordinates.end());
    }
  };

  /**
   * Extend boost namespace to define a boost::hash function on
   * DGtal::SignedKhalimskyCell.
   *
   */
  template < DGtal::Dimension dim,
             typename TInteger >
  struct hash< DGtal::SignedKhalimskyCell< dim, TInteger > >
  {
    size_t operator()(const DGtal::SignedKhalimskyCell< dim, TInteger > & pp) const
    {
      auto const& p = pp.preCell();
      return p.positive
        ? boost::hash_range(p.coordinates.begin(), p.coordinates.end())
        : boost::hash_range(p.coordinates.begin(), p.coordinates.end()) ^ ( (size_t) 0x7a0d3fe9 );
    }
  };

}



#endif // !defined KhalimskyCellHashFunctions_h

#undef KhalimskyCellHashFunctions_RECURSES
#endif // else defined(KhalimskyCellHashFunctions_RECURSES)
