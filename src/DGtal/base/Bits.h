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
 * @file Bits.h
 * @brief A collection of functions to help with bitwise manipulations.
 * @author Nicolas Silva (\c nicolas.silva@insa-lyon.fr )
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/09/02
 * 
 */
#ifndef BITS_HPP
#define BITS_HPP

#include <string>
#include "DGtal/base/Common.h"
#include "DGtal/base/BasicFunctors.h"
#include "DGtal/base/ExpressionTemplates.h"

namespace DGtal
{

  struct Bits
  {
    /**
     * @brief Bits Structs grouping all the functions of this tiny
     * library for bitwise calculation.
     *
     * @todo Check that T is CInteger.
     */

     
    /**
     * Returns a string containing value's bits. Mainly designed for debugging purposes.
     * 
     * @param value The value that you need to dipslay as a bit string.
     * @param nbBits number of bits to be displayed. If equal to 0, the number of bits will
     * correspond to the size of the type T.
     */
    template <typename T>
    static std::string bitString(T value, unsigned nbBits = 0)
    {
      std::string bitStr;
      /*functors::Min<unsigned int> min;*/

      // if the requested number of bit is 0, use the size of the data type instead
      if(nbBits == 0) nbBits = sizeof(T)*8;
      int i = (int)(std::min((DGtal::int64_t)sizeof(T)*8-1, (DGtal::int64_t)nbBits-1));

      for(; i>=0; i--)
	{
	  T mask = ((T)1) << i; // if you take these parenthesis out,
	  // a mountain of incredible runtime
	  // errors will jump on you.(I warned
	  // ya !)
	  if(value & mask)
	    bitStr += "1" ;
	  else
	    bitStr += "0" ;
	}
      return bitStr;
    }


    // ---------------------------------------------------------------------
    //  Other functions
    // ---------------------------------------------------------------------

    /**
     * Returns an value which bits are of the form 0..010..0 with the nthBit equal to 1.
     */ 
    template<typename T> 
    static inline T mask(unsigned nthBit)
    {
      return static_cast<T>(static_cast<T>(1) << nthBit); 
    }

    /**
     *  Returns the state of key's nthBit bit.
     */ 
    template <typename T>
    static inline bool getBit(T key, unsigned nthBit)
    {
      return ( key & mask<T>(nthBit) );
    }

  
    /** 
     * Returns a value such that only its bit corresponding to the
     * first (least important) set bit of val, is set.
     */ 
    template <typename T>
    static inline  T firstSetBit(T val)
    {
      return ( (val & -val) | (val & (~val + 1)) );
    }


    /**
     * Returns a value such that only its bit corresponding to the
     * first (least important) unset bit of val, is set.
     */ 
    template <typename T>
    static inline T firstUnsetBit(T val)
    {
      return ~val & (val + 1);
    }


    /**
     * Returns the amount of set bits in val.
     */ 
    template <typename T>
    static inline unsigned int nbSetBits(T val)
    {
#ifdef TRACE_BITS
      std::cerr << "unsigned int nbSetBits(T val)" << std::endl;
#endif
      unsigned int i = 0;
      for ( ; val; ++i) {val ^= val & -val; }
      return i;
    }

    /**
       Overloading for type uint8_t
       Returns the amount of set bits in val.
    */ 
    static inline 
    unsigned int nbSetBits( DGtal::uint8_t val )
    {
#ifdef TRACE_BITS
      std::cerr << "unsigned int nbSetBits( DGtal::uint8_t val )" << std::endl;
#endif
      return myBitCount[ val ];
    }

    /**
       Overloading for type uint16_t
       Returns the amount of set bits in val.
    */ 
    static inline 
    unsigned int nbSetBits( DGtal::uint16_t val )
    {
#ifdef TRACE_BITS
      std::cerr << "unsigned int nbSetBits( DGtal::uint16_t val )" << std::endl;
#endif
      return nbSetBits( static_cast<DGtal::uint8_t>( val & 0xff ) ) 
	+ nbSetBits( static_cast<DGtal::uint8_t>( val >> 8 ) );
    }

    /**
       Overloading for type uint32_t
       Returns the amount of set bits in val.
    */ 
    static inline 
    unsigned int nbSetBits( DGtal::uint32_t val )
    {
#ifdef TRACE_BITS
      std::cerr << "unsigned int nbSetBits( DGtal::uint32_t val )" << std::endl;
#endif
      return nbSetBits( static_cast<DGtal::uint16_t>( val & 0xffff ) ) 
	+ nbSetBits( static_cast<DGtal::uint16_t>( val >> 16 ) );
    }

    /**
       Overloading for type uint64_t
       Returns the amount of set bits in val.
    */ 
    static inline 
    unsigned int nbSetBits( DGtal::uint64_t val )
    {
#ifdef TRACE_BITS
      std::cerr << "unsigned int nbSetBits( DGtal::uint64_t val )" << std::endl;
#endif
      return nbSetBits( static_cast<DGtal::uint32_t>( val & 0xffffffffLL ) ) 
	+ nbSetBits( static_cast<DGtal::uint32_t>( val >> 32 ) );
    }

    /**
       Specialization for uint8_t.

       Set bits are numbered from 1 to x when reading the word from the
       least significant to the most significant bit. This number is the
       index of bit \a b in the number \a n.

       @param b a bit index in 0..7
       @param n a number in 0..255
       @return this index or 0 if the bit is not set.
    */
    static inline 
    unsigned int indexInSetBits( DGtal::uint8_t n, unsigned int b )
    {
      ASSERT( b < 8 );
      return myIndexInSetBits[ b ][ n ];
    }

    /**
       Specialization for uint16_t.

       Set bits are numbered from 1 to x when reading the word from the
       least significant to the most significant bit. This number is the
       index of bit \a b in the number \a n.

       @param b a bit index in 0..15
       @param n a number in 0..65535
       @return this index or 0 if the bit is not set.
    */
    static inline 
    unsigned int indexInSetBits( DGtal::uint16_t n, unsigned int b )
    {
      ASSERT( b < 16 );
      if ( b < 8 ) 
	return indexInSetBits( static_cast<DGtal::uint8_t>( n & 0xff ), b );
      else 
	{
	  unsigned int idx = indexInSetBits( static_cast<DGtal::uint8_t>( n >> 8 ), b - 8 );
	  return ( idx == 0 )
	    ? 0 // bit b is not set
	    : idx + nbSetBits( static_cast<DGtal::uint8_t>( n & 0xff ) );
	}
    }

    /**
       Specialization for uint32_t.

       Set bits are numbered from 1 to x when reading the word from the
       least significant to the most significant bit. This number is the
       index of bit \a b in the number \a n.

       @param b a bit index in 0..31
       @param n a number in 0..2^32-1
       @return this index or 0 if the bit is not set.
    */
    static inline 
    unsigned int indexInSetBits( DGtal::uint32_t n, unsigned int b )
    {
      ASSERT( b < 32 );
      if ( b < 16 ) 
	return indexInSetBits( static_cast<DGtal::uint16_t>( n & 0xffff ), b );
      else 
	{
	  unsigned int idx = indexInSetBits( static_cast<DGtal::uint16_t>( n >> 16 ), b - 16 );
	  return ( idx == 0 )
	    ? 0 // bit b is not set
	    : idx + nbSetBits( static_cast<DGtal::uint16_t>( n & 0xffff ) );
	}
    }

   /**
       Specialization for uint64_t.

       Set bits are numbered from 1 to x when reading the word from the
       least significant to the most significant bit. This number is the
       index of bit \a b in the number \a n.

       @param b a bit index in 0..63
       @param n a number in 0..2^64-1
       @return this index or 0 if the bit is not set.
    */
    static inline 
    unsigned int indexInSetBits( DGtal::uint64_t n, unsigned int b )
    {
      ASSERT( b < 64 );
      if ( b < 32 ) 
	return indexInSetBits( static_cast<DGtal::uint32_t>( n & 0xffffffffLL ), b );
      else 
	{
	  unsigned int idx = indexInSetBits( static_cast<DGtal::uint32_t>( n >> 32 ), b - 32 );
	  return ( idx == 0 )
	    ? 0 // bit b is not set
	    : idx + nbSetBits( static_cast<DGtal::uint32_t>( n & 0xffffffffLL ) );
	}
    }

    
    /**
       @param n any number
       @return the index (0..) of the least significant bit.
    */
    static inline 
    unsigned int leastSignificantBit( DGtal::uint8_t n )
    {
      return myLSB[ n ];
    }

    /**
       @param n any number
       @return the index (0..) of the least significant bit.
    */
    static inline 
    unsigned int leastSignificantBit( DGtal::uint16_t n )
    {
      return ( n & 0xff ) 
        ? leastSignificantBit( (DGtal::uint8_t) n )
        : 8 + leastSignificantBit( (DGtal::uint8_t) (n>>8) );
    }

    /**
       @param n any number
       @return the index (0..) of the least significant bit.
    */
    static inline 
    unsigned int leastSignificantBit( DGtal::uint32_t n )
    {
      return ( n & 0xffff ) 
        ? leastSignificantBit( (DGtal::uint16_t) n )
        : 16 + leastSignificantBit( (DGtal::uint16_t) (n>>16) );
    }

    /**
       @param n any number
       @return the index (0..) of the least significant bit.
    */
    static inline 
    unsigned int leastSignificantBit( DGtal::uint64_t n )
    {
      return ( n & 0xffffffffLL ) 
        ? leastSignificantBit( (DGtal::uint32_t) n )
        : 32 + leastSignificantBit( (DGtal::uint32_t) (n>>32) );
    }
 
    /**
       @param n any number
       @return the index (..0) of the most significant bit.
    */
    static inline 
    unsigned int mostSignificantBit( DGtal::uint8_t n )
    {
      return myMSB[ n ];
    }

    /**
       @param n any number
       @return the index (..0) of the mot significant bit.
    */
    static inline 
    unsigned int mostSignificantBit( DGtal::uint16_t n )
    {
      return ( n & 0xff00 ) 
        ? 8 + mostSignificantBit( (DGtal::uint8_t) (n>>8) )
        :  mostSignificantBit((DGtal::uint8_t) (n) );
    }
 
    /**
       @param n any number
       @return the index (..0) of the most significant bit.
    */
    static inline 
    unsigned int mostSignificantBit( DGtal::uint32_t n )
    {
      return ( n & 0xffff0000 ) 
        ? 16 + mostSignificantBit( (DGtal::uint16_t) (n>>16) )
        :  mostSignificantBit((DGtal::uint16_t) (n) );
    }

    /**
       @param n any number
       @return the index (..0) of the most significant bit.
    */
    static inline 
    unsigned int mostSignificantBit( DGtal::uint64_t n )
    {
      return ( n & 0xffffffff00000000LL ) 
        ? 32 + mostSignificantBit( (DGtal::uint32_t) (n>>32) )
        :  mostSignificantBit((DGtal::uint32_t) (n) );      
    }
    

    	  
    /**
       Lookup table for counting the number of bits set to 1 in a byte.
       ( Taken from STL \<bitset\> )
    */
    static const DGtal::uint8_t myBitCount[ 256 ];

    /**
       Lookup table for finding the least significant bit.
    */
    static const DGtal::uint8_t myLSB[ 256 ];

    /**
    Lookup table for finding the least significant bit.
    */
    static const DGtal::uint8_t myMSB[ 256 ];

    /**
       Usage: myIndexInSetBits[ b ][ n ]
       - \a b in 0..7
       - \a n in 0..255
       Set bits are numbered from 1 to x when reading the word from the
       least significant to the most significant bit. This number is the
       index of bit \a b in the number \a n.
       return this index or 0 if the bit is not set.
    */
    static const DGtal::uint8_t myIndexInSetBits[ 8 ][ 256 ];

    
  };//struct
}
#endif
