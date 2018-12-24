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
 * @file BasicTypes.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/05/15
 *
 * Header file for module BasicTypes.cpp.
 *
 * This file contains the definition of basic types.
 *
 * This file is part of the DGtal library.
 */

#if defined(BasicTypes_RECURSES)
#error Recursive header files inclusion detected in BasicTypes.h
#else // defined(BasicTypes_RECURSES)
/** Prevents recursive inclusion of headers. */
#define BasicTypes_RECURSES

#if !defined BasicTypes_h
/** Prevents repeated inclusion of headers. */
#define BasicTypes_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <cstdlib>
#include <iostream>
#include <boost/cstdint.hpp>

#ifdef WITH_GMP
#include <gmpxx.h>
#endif
//////////////////////////////////////////////////////////////////////////////



namespace DGtal
{
  ///unsigned 8-bit integer.
  typedef boost::uint8_t uint8_t;
  ///unsigned 16-bit integer.
  typedef boost::uint16_t uint16_t;
  ///unsigned 32-bit integer.
  typedef boost::uint32_t uint32_t;
  ///unsigned 64-bit integer.
  typedef boost::uint64_t uint64_t;
  
  ///signed 8-bit integer.  
  typedef boost::int8_t int8_t;
  ///signed 16-bit integer.
  typedef boost::int16_t int16_t;
  ///signed 32-bit integer.
  typedef boost::int32_t int32_t;
  ///signed 94-bit integer.
  typedef boost::int64_t int64_t;
  
#ifdef WITH_GMP
  #define WITH_BIGINTEGER
  ///Multi-precision integer with GMP implementation.
  typedef mpz_class BigInteger;
#endif

} // namespace DGtal



//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined BasicTypes_h

#undef BasicTypes_RECURSES
#endif // else defined(BasicTypes_RECURSES)
