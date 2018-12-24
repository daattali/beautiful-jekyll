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
 * @file Topology.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5127), University of Savoie, France
 *
 * @date 2011/11/18
 *
 * This file contain generic definitions for topology module.
 *
 * This file is part of the DGtal library.
 */

#if defined(Topology_RECURSES)
#error Recursive header files inclusion detected in Topology.h
#else // defined(Topology_RECURSES)
/** Prevents recursive inclusion of headers. */
#define Topology_RECURSES

#if !defined Topology_h
/** Prevents repeated inclusion of headers. */
#define Topology_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  /**
     Kinds of connectedness for an object or a graph.
   */
  enum Connectedness
    {
      DISCONNECTED = 0, CONNECTED = 1, UNKNOWN = 2
    };
  
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined Topology_h

#undef Topology_RECURSES
#endif // else defined(Topology_RECURSES)
