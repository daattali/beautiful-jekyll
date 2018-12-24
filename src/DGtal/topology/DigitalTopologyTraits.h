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
 * @file DigitalTopologyTraits.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2013/10/30
 *
 * Header file for module DigitalTopologyTraits.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalTopologyTraits_RECURSES)
#error Recursive header files inclusion detected in DigitalTopologyTraits.h
#else // defined(DigitalTopologyTraits_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalTopologyTraits_RECURSES

#if !defined DigitalTopologyTraits_h
/** Prevents repeated inclusion of headers. */
#define DigitalTopologyTraits_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/topology/MetricAdjacency.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalTopologyTraits
  /**
     Description of template class 'DigitalTopologyTraits' <p>
     \brief Aim: the traits classes for DigitalTopology types.
     
     @tparam TForegroundAdjacency any model of CAdjacency.
     @tparam TBackgroundAdjacency any model of CAdjacency.
     @tparam dim the dimension of the embedding digital space.
     
     The traits are specialized for the classical (4,8) and (8,4)
     adjacencies in 2D and (6,18), (6,26), (26,6) and (18,6)
     adjacencies in 3D, following the works of Bertrand and
     Couprie (@cite Bertrand2007a). They specify for GEODESIC_NEIGHBORHOOD_SIZE:
     
     - 2 for (4,8) and (8,4) -> ok
     - 1 for (6,26) (previously set to 2 by @cite Bertrand2007a)
     - 2 for (6,18) (previously set to 3 by @cite Bertrand2007a)
     - 3 for (18,6) (previously set to 2 by @cite Bertrand2007a)
     - 2 for (26,6) (previously set to 1 by @cite Bertrand2007a)
   */
  template <typename TForegroundAdjacency, typename TBackgroundAdjacency, Dimension dim>
  struct DigitalTopologyTraits
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = dim;
  }; // end of class DigitalTopologyTraits

  /**
     \brief Aim: Specialization of the traits classes for DigitalTopology types for any 2D Space, for topology (4,8).
  */
  template <typename TSpace>
  struct DigitalTopologyTraits< MetricAdjacency< TSpace, 1>,
				MetricAdjacency< TSpace, 2>,
				2 >
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = 2;
  };

  /**
     \brief Aim: Specialization of the traits classes for DigitalTopology types for any 2D Space, for topology (8,4).
  */
  template <typename TSpace>
  struct DigitalTopologyTraits< MetricAdjacency< TSpace, 2>,
				MetricAdjacency< TSpace, 1>,
				2 >
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = 2;
  };

  /**
     \brief Aim: Specialization of the traits classes for DigitalTopology types for any 2D Space, for topology (6,26).
  */
  template <typename TSpace>
  struct DigitalTopologyTraits< MetricAdjacency< TSpace, 1>,
				MetricAdjacency< TSpace, 3>,
				3 >
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = 1; // JOL: 2 does not work ;
  };

  /**
     \brief Aim: Specialization of the traits classes for DigitalTopology types for any 2D Space, for topology (6,18).
  */
  template <typename TSpace>
  struct DigitalTopologyTraits< MetricAdjacency< TSpace, 1>,
				MetricAdjacency< TSpace, 2>,
				3 >
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = 2; // JOL: 3 does not work ;
  };

  /**
     \brief Aim: Specialization of the traits classes for DigitalTopology types for any 2D Space, for topology (18,6).
  */
  template <typename TSpace>
  struct DigitalTopologyTraits< MetricAdjacency< TSpace, 2>,
				MetricAdjacency< TSpace, 1>,
				3 >
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = 3; // JOL: 2 does not work 
  };

  /**
     \brief Aim: Specialization of the traits classes for DigitalTopology types for any 2D Space, for topology (26,6).
  */
  template <typename TSpace>
  struct DigitalTopologyTraits< MetricAdjacency< TSpace, 3>,
				MetricAdjacency< TSpace, 1>,
				3 >
  {
    // ----------------------- Specific traits ------------------------------
  public:
    static const Dimension GEODESIC_NEIGHBORHOOD_SIZE = 2; // JOL: 1 does not work 
  };


} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalTopologyTraits_h

#undef DigitalTopologyTraits_RECURSES
#endif // else defined(DigitalTopologyTraits_RECURSES)
