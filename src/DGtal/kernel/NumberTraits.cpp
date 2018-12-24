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

/** 
 * @file NumberTraits.cpp
 * @author David Coeurjolly (\c david.coeurjolly@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2011/09/10
 * 
 * Implementation of methods defined in NumberTraits.h 
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include "DGtal/kernel/NumberTraits.h"
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// class Common
///////////////////////////////////////////////////////////////////////////////

/** DGtal Global variables
*
**/
namespace DGtal
{
  //Constant definitions in NumberTraits specializations.
  const int8_t NumberTraits<int8_t>::ONE = 1;
  const int8_t NumberTraits<int8_t>::ZERO = 0;
  const uint8_t NumberTraits<uint8_t>::ONE = 1;
  const uint8_t NumberTraits<uint8_t>::ZERO = 0;

  const int16_t NumberTraits<int16_t>::ONE = 1;
  const int16_t NumberTraits<int16_t>::ZERO = 0;
  const uint16_t NumberTraits<uint16_t>::ONE = 1;
  const uint16_t NumberTraits<uint16_t>::ZERO = 0;

  const int32_t NumberTraits<int32_t>::ONE = 1;
  const int32_t NumberTraits<int32_t>::ZERO = 0;
  const uint32_t NumberTraits<uint32_t>::ONE = 1;
  const uint32_t NumberTraits<uint32_t>::ZERO = 0;

  const int64_t NumberTraits<int64_t>::ONE = 1;
  const int64_t NumberTraits<int64_t>::ZERO = 0;
  const uint64_t NumberTraits<uint64_t>::ONE = 1;
  const uint64_t NumberTraits<uint64_t>::ZERO = 0;

  const float NumberTraits<float>::ONE = 1.0f;
  const float NumberTraits<float>::ZERO = 0.0f;

  const double NumberTraits<double>::ONE = 1.0;
  const double NumberTraits<double>::ZERO = 0.0;
 
  const long double NumberTraits<long double>::ONE = 1.0;
  const long double NumberTraits<long double>::ZERO = 0.0;

#ifdef WITH_BIGINTEGER
  const DGtal::BigInteger NumberTraits<DGtal::BigInteger>::ONE = 1;
  const DGtal::BigInteger NumberTraits<DGtal::BigInteger>::ZERO = 0;
#endif 

}
