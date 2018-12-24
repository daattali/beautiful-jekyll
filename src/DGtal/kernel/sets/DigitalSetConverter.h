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
 * @file DigitalSetConverter.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/09
 *
 * Header file for module DigitalSetConverter.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(DigitalSetConverter_RECURSES)
#error Recursive header files inclusion detected in DigitalSetConverter.h
#else // defined(DigitalSetConverter_RECURSES)
/** Prevents recursive inclusion of headers. */
#define DigitalSetConverter_RECURSES

#if !defined DigitalSetConverter_h
/** Prevents repeated inclusion of headers. */
#define DigitalSetConverter_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/kernel/sets/CDigitalSet.h"
#include "DGtal/kernel/sets/DigitalSetBySTLVector.h"
#include "DGtal/kernel/sets/DigitalSetBySTLSet.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{

  /////////////////////////////////////////////////////////////////////////////
  // class DigitalSetConverter
  /**
   * Description of class 'DigitalSetConverter' <p>
   * \brief Aim: Utility class to convert between types of sets.
   *
   * @tparam OutputDigitalSet the type of the input DigitalSet (model
   * of CDigitalSet).
   *
   */
  template <typename OutputDigitalSet>
  struct DigitalSetConverter
  {
    // ----------------------- Standard services ------------------------------
  public:

    /**
     * Assigns input to output.
     *
     * @param output (modified) the output set.
     * @param input the input set.
     *
     * @tparam InputDigitalSet the type of the output DigitalSet  (model
     * of CDigitalSet).
     */
    template<typename InputDigitalSet>
    static
    void assign( OutputDigitalSet & output, const InputDigitalSet & input );

    /**
     * Use function overloading for possible faster assignment. 
     * Assigns input to output.
     *
     * @param output (modified) the output set.
     * @param input the input set.
     */
    static
    void assign( OutputDigitalSet & output, const OutputDigitalSet & input );

  }; // end of class DigitalSetConverter


} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/sets/DigitalSetConverter.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined DigitalSetConverter_h

#undef DigitalSetConverter_RECURSES
#endif // else defined(DigitalSetConverter_RECURSES)
