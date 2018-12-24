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
 * @file testBits.cpp
 * @ingroup Tests
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 *
 * @date 2012/07/02
 *
 * This file is part of the DGtal library
 */

//#define TRACE_BITS

#include <cstdio>
#include <cmath>
#include <iostream>
#include "DGtal/base/Common.h"
#include "DGtal/base/Bits.h"

using namespace DGtal;


// Set bits are numbered from 1 to x when reading the word from the
// least significant to the most significant bit. This number is the
// index of bit \a b in the number \a n.
// return 0 if the bit is not set.
unsigned int index( DGtal::uint32_t n, unsigned int b )
{
  int i = 0;
  for ( ; b != 0; --b )
    {
      if ( n & 1 ) ++i;
      n >>= 1;
    }
  return ( n & 1 ) ? i + 1 : 0; 
}


int main()
{
  unsigned int nb = 0;
  unsigned int nbok = 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint8_t)-1) == 8 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint16_t)-1) == 16 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint32_t)-1) == 32 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint64_t)-1) == 64 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint8_t)1) == 1 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint16_t)1) == 1 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint32_t)1) == 1 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint64_t)1) == 1 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint8_t)-2) == 7 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint16_t)-2) == 15 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint32_t)-2) == 31 ? 1 : 0;
  ++nb, nbok += Bits::nbSetBits( (DGtal::uint64_t)-2) == 63 ? 1 : 0;

  for ( unsigned int i = 0; i < 100; ++i )
    {
      DGtal::uint16_t n = (DGtal::uint16_t) ( rand() % 65536 ); 
      for ( unsigned int b = 0; b < 16; ++b )
	++nb, nbok += Bits::indexInSetBits( n, b ) == index( n, b ) ? 1 : 0;
    }

  std::cerr << "(" << nbok << "/" << nb << ")" << " tests." << std::endl;

  trace.beginBlock ( "Testing speed of loop version of indexInSetBits" );
  srand( 0 );
  unsigned int val = 0;
  for ( unsigned int i = 0; i < 100000; ++i )
    {
      DGtal::uint32_t n = (DGtal::uint32_t) rand();
      for ( unsigned int b = 0; b < 32; ++b )
	val += index( n, b );
    }
  trace.info() << "- checksum = " << val << std::endl;
  trace.endBlock();

  trace.beginBlock ( "Testing speed of look-up table version of indexInSetBits" );
  srand( 0 );
  unsigned int val2 = 0;
  for ( unsigned int i = 0; i < 100000; ++i )
    {
      DGtal::uint32_t n = (DGtal::uint32_t) rand();
      for ( unsigned int b = 0; b < 32; ++b )
	val2 += Bits::indexInSetBits( n, b );
    }
  trace.info() << "- checksum = " << val2 << std::endl;
  trace.endBlock();
  ++nb, nbok += val == val2 ? 1 : 0;
  return ( nb == nbok ) ? 0 : 1;
}
/** @ingroup Tests **/
