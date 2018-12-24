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
 * @file DigitalSetSelector.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @author Sebastien Fourey (\c Sebastien.Fourey@greyc.ensicaen.fr )
 * Groupe de Recherche en Informatique, Image, Automatique et
 * Instrumentation de Caen - GREYC (CNRS, UMR 6072), ENSICAEN, France
 *
 * @date 2010/07/01
 *
 * Header file for module DigitalSetSelector.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSetSelector_RECURSES)
#error Recursive header files inclusion detected in DigitalSetSelector.h
#else // defined(DigitalSetSelector_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSetSelector_RECURSES

#if !defined DigitalSetSelector_h
/** Prevents repeated inclusion of headers. */
#define DigitalSetSelector_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/sets/DigitalSetByAssociativeContainer.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"

#include "DGtal/kernel/PointHashFunctions.h"
#include <unordered_set>
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  // ----------------------- Related enumerations -----------------------------
  enum DigitalSetSize { SMALL_DS = 0, MEDIUM_DS = 1, BIG_DS = 2, WHOLE_DS = 3 };
  enum DigitalSetVariability { LOW_VAR_DS = 0, HIGH_VAR_DS = 4 };
  enum DigitalSetIterability { LOW_ITER_DS = 0, HIGH_ITER_DS = 8 };
  enum DigitalSetBelongTestability { LOW_BEL_DS = 0, HIGH_BEL_DS = 16 };

  /////////////////////////////////////////////////////////////////////////////
  // template class DigitalSetSelector
  /**
   * Description of template class 'DigitalSetSelector' <p> \brief
   * Aim: Automatically defines an adequate digital set type according
   * to the hints given by the user.
   *
   * @code
   typedef SpaceND<int,4> Space4;
   typedef HyperRectDomain<Space4> Domain;
   typedef Space4::Point Point;
   Point a ( { 1, 2, 3 ,4} );
   Point b ( { 5, 5, 3 ,5} );
   // Domain characterized by points a and b
   Domain domain ( a,b );
   // Specifies a small point set but with a high variability.
   typedef typename DigitalSetSelector
     < Domain, SMALL_DS + HIGH_VAR_DS >::Type SpecificSet; 
   SpecificSet set1( domain );
   *
   * @endcode
   */
  template <typename Domain, int Preferences >
  struct DigitalSetSelector
  {
    // ----------------------- Local types ------------------------------
    /**
     * Adequate digital set representation for the given preferences.
     */
    typedef DigitalSetByAssociativeContainer<Domain, std::unordered_set< typename Domain::Point> > Type;
  }; // end of class DigitalSetSelector


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/sets/DigitalSetSelector.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSetSelector_h

#undef DigitalSetSelector_RECURSES
#endif // else defined(DigitalSetSelector_RECURSES)
