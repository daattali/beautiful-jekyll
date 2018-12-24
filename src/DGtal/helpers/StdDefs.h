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
 * @file StdDefs.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/11/01
 *
 * Header file for module StdDefs.cpp.
 * Gathers standard definitions of digital spaces, adjacencies, topologies.
 *
 * This file is part of the DGtal library.
 */

#if defined(StdDefs_RECURSES)
#error Recursive header files inclusion detected in StdDefs.h
#else // defined(StdDefs_RECURSES)
/** Prevents recursive inclusion of headers. */
#define StdDefs_RECURSES

#if !defined StdDefs_h
/** Prevents repeated inclusion of headers. */
#define StdDefs_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/SpaceND.h"
#include "DGtal/kernel/domains/HyperRectDomain.h"
#include "DGtal/kernel/sets/DigitalSetSelector.h"
#include "DGtal/topology/DigitalTopology.h"
#include "DGtal/topology/MetricAdjacency.h"
#include "DGtal/topology/Object.h"
#include "DGtal/topology/KhalimskySpaceND.h"
#include "DGtal/topology/KhalimskyPreSpaceND.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpSeparableMetric.h"
#include "DGtal/geometry/volumes/distance/ExactPredicateLpPowerSeparableMetric.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /**
   * This namespace gathers all standard type definitions as well as
   * some static instances for using a 2D digital space with integers
   * represented by 'int'. It is useful for a developer who wants to
   * develop an application in the 2D plane and who does not wish to
   * tune specifically the possible types.
   *
   * This is the standard set of types for 2D imagery.
   *
   * @todo Once stabilized, provide a Z2l (for int64) and a Z2I (for
   * arbitrary integers).
   */
  namespace Z2i {
    typedef DGtal::int32_t Integer;
    typedef SpaceND< 2, Integer > Space;
    typedef Space Z2;
    typedef KhalimskySpaceND< 2, Integer > KSpace;
    typedef KSpace K2;
    typedef KSpace::Cell Cell;
    typedef KSpace::SCell SCell;
    typedef KSpace::Cells Cells;
    typedef KSpace::SCells SCells;
    typedef KhalimskyPreSpaceND< 2, Integer > KPreSpace;
    typedef KPreSpace KP2;
    typedef KPreSpace::Cell PreCell;
    typedef KPreSpace::SCell SPreCell;
    typedef KPreSpace::Cells PreCells;
    typedef KPreSpace::SCells SPreCells;
    /** Standard 4-neighborhood for a 2D digital space. */
    typedef MetricAdjacency< Space, 1> Adj4;
    /** Standard 8-neighborhood for a 2D digital space. */
    typedef MetricAdjacency< Space, 2> Adj8;
    typedef DigitalTopology< Adj4, Adj8 > DT4_8;
    typedef DigitalTopology< Adj8, Adj4 > DT8_4;
    typedef Space::Point Point;
    typedef Space::Vector Vector;
    typedef Space::RealPoint RealPoint;
    typedef Space::RealVector RealVector;
    typedef HyperRectDomain< Space > Domain; 
    typedef DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;
    typedef Object<DT4_8, DigitalSet> Object4_8;
    typedef Object<DT4_8, DigitalSet>::ComplementObject ComplementObject4_8;
    typedef Object<DT4_8, DigitalSet>::SmallObject SmallObject4_8;
    typedef Object<DT4_8, DigitalSet>::SmallComplementObject SmallComplementObject4_8;
    typedef Object<DT8_4, DigitalSet> Object8_4;
    typedef Object<DT8_4, DigitalSet>::ComplementObject ComplementObject8_4;
    typedef Object<DT8_4, DigitalSet>::SmallObject SmallObject8_4;
    typedef Object<DT8_4, DigitalSet>::SmallComplementObject SmallComplementObject8_4;


    static const Adj4 adj4;
    static const Adj8 adj8;
    static const DT4_8 dt4_8 = DT4_8( adj4, adj8, JORDAN_DT );
    static const DT8_4 dt8_4 = DT8_4( adj8, adj4, JORDAN_DT );

    typedef GridCurve<K2> Curve;

    typedef ExactPredicateLpSeparableMetric<Space,2> L2Metric;
    typedef ExactPredicateLpSeparableMetric<Space,1> L1Metric;
    typedef ExactPredicateLpPowerSeparableMetric<Space,2> L2PowerMetric;
    typedef ExactPredicateLpPowerSeparableMetric<Space,1> L1PowerMetric;
 
    static const L2Metric l2Metric;
    static const L1Metric l1Metric;
    static const L2PowerMetric l2PowerMetric;
    static const L1PowerMetric l1PowerMetric;

  } // namespace Z2i

  /**
   * This namespacef gathers all standard type definitions as well as
   * some static instances for using a 3D digital space with integers
   * represented by 'int'. It is useful for a developer who wants to
   * develop an application in the 3D plane and who does not wish to
   * tune specifically the possible types.
   *
   * This is the standard set of types for 3D imagery.
   *
   * @todo Once stabilized, provide a Z3l (for int64) and a Z3I (for
   * arbitrary integers).
   */
  namespace Z3i {
    typedef DGtal::int32_t Integer;
    typedef SpaceND< 3, Integer > Space;
    typedef Space Z3;
    typedef KhalimskySpaceND< 3, Integer > KSpace;
    typedef KSpace K3;
    typedef KSpace::Cell Cell;
    typedef KSpace::SCell SCell;
    typedef KSpace::Cells Cells;
    typedef KSpace::SCells SCells;
    typedef KhalimskyPreSpaceND< 3, Integer > KPreSpace;
    typedef KPreSpace KP3;
    typedef KPreSpace::Cell   PreCell;
    typedef KPreSpace::SCell  SPreCell;
    typedef KPreSpace::Cells  PreCells;
    typedef KPreSpace::SCells SPreCells;
    /** Standard 6-neighborhood for a 3D digital space. */
    typedef MetricAdjacency< Space, 1> Adj6;
    /** Standard 18-neighborhood for a 3D digital space. */
    typedef MetricAdjacency< Space, 2> Adj18;
    /** Standard 26-neighborhood for a 3D digital space. */
    typedef MetricAdjacency< Space, 3> Adj26;
    typedef DigitalTopology< Adj6, Adj18 > DT6_18;
    typedef DigitalTopology< Adj18, Adj6 > DT18_6;
    typedef DigitalTopology< Adj6, Adj26 > DT6_26;
    typedef DigitalTopology< Adj26, Adj6 > DT26_6;
    typedef Space::Point Point;
    typedef Space::Vector Vector;
    typedef Space::RealPoint RealPoint;
    typedef Space::RealVector RealVector;
    typedef HyperRectDomain< Space > Domain; 
    typedef DigitalSetSelector< Domain, BIG_DS+HIGH_BEL_DS >::Type DigitalSet;
    typedef Object<DT6_18, DigitalSet> Object6_18;
    typedef Object<DT6_18, DigitalSet>::ComplementObject ComplementObject6_18;
    typedef Object<DT6_18, DigitalSet>::SmallObject SmallObject6_18;
    typedef Object<DT6_18, DigitalSet>::SmallComplementObject SmallComplementObject6_18;
    typedef Object<DT18_6, DigitalSet> Object18_6;
    typedef Object<DT18_6, DigitalSet>::ComplementObject ComplementObject18_6;
    typedef Object<DT18_6, DigitalSet>::SmallObject SmallObject18_6;
    typedef Object<DT18_6, DigitalSet>::SmallComplementObject SmallComplementObject18_6;
    typedef Object<DT6_26, DigitalSet> Object6_26;
    typedef Object<DT6_26, DigitalSet>::ComplementObject ComplementObject6_26;
    typedef Object<DT6_26, DigitalSet>::SmallObject SmallObject6_26;
    typedef Object<DT6_26, DigitalSet>::SmallComplementObject SmallComplementObject6_26;
    typedef Object<DT26_6, DigitalSet> Object26_6;
    typedef Object<DT26_6, DigitalSet>::ComplementObject ComplementObject26_6;
    typedef Object<DT26_6, DigitalSet>::SmallObject SmallObject26_6;
    typedef Object<DT26_6, DigitalSet>::SmallComplementObject SmallComplementObject26_6;

    static const Adj6 adj6;
    static const Adj18 adj18;
    static const Adj26 adj26;
    static const DT6_18 dt6_18 = DT6_18( adj6, adj18, JORDAN_DT );
    static const DT18_6 dt18_6 = DT18_6( adj18, adj6, JORDAN_DT );
    static const DT6_26 dt6_26 = DT6_26( adj6, adj26, JORDAN_DT );
    static const DT26_6 dt26_6 = DT26_6( adj26, adj6, JORDAN_DT );

    typedef ExactPredicateLpSeparableMetric<Space,2> L2Metric;
    typedef ExactPredicateLpSeparableMetric<Space,1> L1Metric;
    typedef ExactPredicateLpPowerSeparableMetric<Space,2> L2PowerMetric;
    typedef ExactPredicateLpPowerSeparableMetric<Space,1> L1PowerMetric;

    static const L2Metric l2Metric;
    static const L1Metric l1Metric;
    static const L2PowerMetric l2PowerMetric;
    static const L1PowerMetric l1PowerMetric;

  } // namespace Z3i

  

  
} // namespace DGtal


//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined StdDefs_h

#undef StdDefs_RECURSES
#endif // else defined(StdDefs_RECURSES)
