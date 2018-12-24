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
 * @file NumberTraits.h
 * @author Jacques-Olivier Lachaud (\c jacques-olivier.lachaud@univ-savoie.fr )
 * Laboratory of Mathematics (CNRS, UMR 5807), University of Savoie, France
 *
 * @date 2010/07/03
 *
 * Header file for module NumberTraits.cpp
 *
 * This file is part of the DGtal library.
 */

#if defined(NumberTraits_RECURSES)
#error Recursive header files inclusion detected in NumberTraits.h
#else // defined(NumberTraits_RECURSES)
/** Prevents recursive inclusion of headers. */
#define NumberTraits_RECURSES

#if !defined NumberTraits_h
/** Prevents repeated inclusion of headers. */
#define NumberTraits_h

//////////////////////////////////////////////////////////////////////////////
// Inclusions
#include <iostream>
#include <limits>
#include <cfloat>
#include <boost/integer_traits.hpp>
#include <boost/call_traits.hpp>
#include "DGtal/base/Common.h"
//////////////////////////////////////////////////////////////////////////////

namespace DGtal
{
  enum BoundEnum {BOUNDED = 0, UNBOUNDED = 1, BOUND_UNKNOWN = 2};
  enum SignEnum {SIGNED = 0, UNSIGNED = 1, SIGN_UNKNOWN = 2};


/////////////////////////////////////////////////////////////////////////////
// template class NumberTraits
  /**
   * Description of template class 'NumberTraits' <p>
   * \brief Aim: The traits class for all models of Cinteger.
   *
   * Since CInteger describes the concept Integer, this class is used
   * by models of CIinteger to specialize some definitions related to
   * Integer. For instance it defines whether a given Integer is
   * signed or not and what is signed/unsigned version.
   */
  template <typename T>
  struct NumberTraits
  {
    // ----------------------- Associated types ------------------------------
    typedef TagUnknown IsBounded;
    typedef TagUnknown IsUnsigned;
    typedef TagUnknown IsSigned;
    typedef TagUnknown IsIntegral;
    typedef TagFalse IsSpecialized;
    typedef T SignedVersion;
    typedef T UnsignedVersion;
    typedef T ReturnType;

    //Defines a type that represents the "best" way to pass
    // a parameter of type T to a function.
    typedef typename boost::call_traits<T>::param_type ParamType;


    /**
     * Constant Zero.
     */

#if ( defined(WIN32))
    static const T ZERO;
#else
    static const T ZERO = T(0);
#endif

    /**
      * Constant One.
    */
#if (defined (WIN32))
    static const T ONE;
#else
    static const T ONE = T(1);
#endif

    /**
     * @return the zero of this integer.
     */
    static ReturnType zero();

    /**
     * @return the one of this integer.
     */
    static ReturnType one();

    /**
     * @return the minimum possible value for this type of integer or
     * ONE if not bounded or unknown.
     */
    static ReturnType min();

    /**
     * @return the maximum possible value for this type of integer or
     * ZERO if not bounded or unknown.
     */
    static ReturnType max();

    /**
     * @return the number of significant digits for this integer type,
     * or 0 if unbounded or unknown.
     */
    static unsigned int digits();

    /**
     * @return BOUNDED, UNBOUNDED, or BOUND_UNKNOWN.
     */
    static BoundEnum isBounded();
    /**
     * @return SIGNED, UNSIGNED or SIGN_UNKNOWN.
     */
    static SignEnum isSigned();
   
    /**
     * Cast method to DGtal::int64_t (for I/O or board export uses
     * only).
     */
    static DGtal::int64_t castToInt64_t(const T & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const T & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & ONE ) == ZERO;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & ONE ) != ZERO;
    }
  }; // end of class NumberTraits

  
  /**
   * Specialization for DGtal::uint16_t.
   */
  template <>
  struct NumberTraits<uint16_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int16_t SignedVersion;
    typedef uint16_t UnsignedVersion;
    typedef uint16_t ReturnType;
    typedef boost::call_traits<uint16_t>::param_type ParamType;
    static const uint16_t ZERO; // = 0;
    static const uint16_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint16_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint16_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint16_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
    static DGtal::int64_t castToInt64_t(const uint16_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const uint16_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }

  }; // end of class NumberTraits<uint16_t>.

  /**
   * Specialization for DGtal::int16_t.
   */
  template <>
  struct NumberTraits<int16_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int16_t SignedVersion;
    typedef uint16_t UnsignedVersion;
    typedef int16_t ReturnType;
    typedef boost::call_traits<int16_t>::param_type ParamType;
    static const int16_t ZERO; // = 0;
    static const int16_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int16_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int16_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int16_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int16_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const int16_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }
  }; // end of class NumberTraits<int16_t>.
 

  /**
   * Specialization for DGtal::uint8_t.
   */
  template <>
  struct NumberTraits<uint8_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int8_t SignedVersion;
    typedef uint8_t UnsignedVersion;
    typedef uint8_t ReturnType;
    typedef boost::call_traits<uint8_t>::param_type ParamType;
    static const uint8_t ZERO; // = 0;
    static const uint8_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint8_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint8_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint8_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
    static DGtal::int64_t castToInt64_t(const uint8_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const uint8_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }

  }; // end of class NumberTraits<uint8_t>.

  /**
   * Specialization for DGtal::int8_t.
   */
  template <>
  struct NumberTraits<int8_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int8_t SignedVersion;
    typedef uint8_t UnsignedVersion;
    typedef int8_t ReturnType;
    typedef boost::call_traits<int8_t>::param_type ParamType;
    static const int8_t ZERO; // = 0;
    static const int8_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int8_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int8_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int8_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int8_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const int8_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }
  }; // end of class NumberTraits<int16_t>.

  /**
   * Specialization for DGtal::uint32_t.
   */
  template <>
  struct NumberTraits<uint32_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int32_t SignedVersion;
    typedef uint32_t UnsignedVersion;
    typedef uint32_t ReturnType;
    typedef boost::call_traits<uint32_t>::param_type ParamType;
    static const uint32_t ZERO; // = 0;
    static const uint32_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint32_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint32_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint32_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
   static DGtal::int64_t castToInt64_t(const uint32_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    static double castToDouble(const uint32_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }
  }; // end of class NumberTraits<uint32_t>.

  /**
   * Specialization for DGtal::int32_t.
   */
  template <>
  struct NumberTraits<int32_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int32_t SignedVersion;
    typedef uint32_t UnsignedVersion;
    typedef int32_t ReturnType;
    typedef boost::call_traits<int32_t>::param_type ParamType;
    static const int32_t ZERO;// = 0;
    static const int32_t ONE;// = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int32_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int32_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int32_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int32_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const int32_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }
  }; // end of class NumberTraits<int32_t>.

  /**
   * Specialization for DGtal::uint64_t.
   */
  template <>
  struct NumberTraits<uint64_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int64_t SignedVersion;
    typedef uint64_t UnsignedVersion;
    typedef uint64_t ReturnType;
    typedef boost::call_traits<uint64_t>::param_type ParamType;
    static const uint64_t ZERO; // = 0;
    static const uint64_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<uint64_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<uint64_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<uint64_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return UNSIGNED;
    }
   static DGtal::int64_t castToInt64_t(const uint64_t & aT)
    {
      return static_cast<DGtal::int64_t>(aT);
    }
    /**
     * Cast method to double (for I/O or board export uses
     * only).
     */
    static double castToDouble(const uint64_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }
  }; // end of class NumberTraits<uint64_t>.

  /**
   * Specialization for DGtal::int64_t.
   */
  template <>
  struct NumberTraits<int64_t>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef int64_t SignedVersion;
    typedef uint64_t UnsignedVersion;
    typedef int64_t ReturnType;
    typedef boost::call_traits<int64_t>::param_type ParamType;
    static const int64_t ZERO; // = 0;
    static const int64_t ONE; // = 1;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<int64_t>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<int64_t>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<int64_t>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const int64_t & aT)
    {
      return aT;
    }
    static double castToDouble(const int64_t & aT)
    {
      return static_cast<double>(aT);
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return ( aT & 1 ) == 0;
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return ( aT & 1 ) != 0;
    }
  }; // end of class NumberTraits<int64_t>.

  /**
   * Specialization for float.
   */
  template <>
  struct NumberTraits<float>
  {
    typedef TagFalse IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef float SignedVersion;
    typedef float UnsignedVersion;
    typedef float ReturnType;
    typedef boost::call_traits<float>::param_type ParamType;
    static const float ZERO;
    static const float ONE;
    static ReturnType zero()
    {
      return 0.0f;
    }
    static ReturnType one()
    {
      return 1.0f;
    }
    static ReturnType min()
    {
      return FLT_MIN;
    }
    static ReturnType max()
    {
      return FLT_MAX;
    }
    static unsigned int digits()
    {
      return FLT_DIG;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const float & aT)
    {
      return static_cast<int64_t>( aT );
    }
    static double castToDouble(const float & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class NumberTraits<float>.


  /**
   * Specialization for double.
   */
  template <>
  struct NumberTraits<double>
  {
    typedef TagFalse IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef double SignedVersion;
    typedef double UnsignedVersion;
    typedef double ReturnType;
    typedef boost::call_traits<double>::param_type ParamType;
    static const double ZERO;
    static const double ONE;
    static ReturnType zero()
    {
      return 0.0;
    }
    static ReturnType one()
    {
      return 1.0;
    }
    static ReturnType min()
    {
      return DBL_MIN;
    }
    static ReturnType max()
    {
      return DBL_MAX;
    }
    static unsigned int digits()
    {
      return DBL_DIG;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
    static DGtal::int64_t castToInt64_t(const double & aT)
    {
      return static_cast<int64_t>( aT );
    }
    static double castToDouble(const double & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class NumberTraits<double>.


  /**
   * Specialization for long double.
   */
  template <>
  struct NumberTraits<long double>
  {
    typedef TagFalse IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagFalse IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef long double SignedVersion;
    typedef long double UnsignedVersion;
    typedef long double ReturnType;
    typedef boost::call_traits<long double>::param_type ParamType;
    static const long double ZERO;
    static const long double ONE;
    static ReturnType zero()
    {
      return 0.0;
    }
    static ReturnType one()
    {
      return 1.0;
    }
    static ReturnType min()
    {
      return LDBL_MIN;
    }
    static ReturnType max()
    {
      return LDBL_MAX;
    }
    static unsigned int digits()
    {
      return LDBL_DIG;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const long double & aT)
    {
      return static_cast<int64_t>( aT );
    }
    static double castToDouble(const long double & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class NumberTraits<long double>.

  

#ifdef APPLE
  /**
   * Specialization for unsigned long.
   */
  template <>
  struct NumberTraits<unsigned long>
  {
    typedef TagTrue IsIntegral;
    typedef TagTrue IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagFalse IsSigned;
    typedef TagTrue IsSpecialized;
    typedef long SignedVersion;
    typedef unsigned long UnsignedVersion;
    typedef unsigned long ReturnType;
    typedef boost::call_traits<unsigned long>::param_type ParamType;
    static const unsigned long ZERO;
    static const unsigned long ONE;
    static ReturnType zero()
    {
      return 0;
    }
    static ReturnType one()
    {
      return 1;
    }
    static ReturnType min()
    {
      return boost::integer_traits<unsigned long>::const_min;
    }
    static ReturnType max()
    {
      return boost::integer_traits<unsigned long>::const_max;
    }
    static unsigned int digits()
    {
      return boost::integer_traits<unsigned long>::digits;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
   static DGtal::int64_t castToInt64_t(const unsigned long & aT)
    {
      return static_cast<int64_t>( aT );
    }
    static double castToDouble(const unsigned long & aT)
    {
      return static_cast<double>(aT);
    }
  }; // end of class NumberTraits<unsigned long>.
#endif
  

#ifdef WITH_BIGINTEGER
  /**
   * Specialization for DGtal::BigInteger. 
   * Note that DGtal::BigInteger represents
   * signed and unsigned arbitrary-size integers. Therefore both
   * IsUnsigned and IsSigned are TagTrue.
   */
  template <>
  struct NumberTraits<DGtal::BigInteger>
  {
    typedef TagTrue IsIntegral;
    typedef TagFalse IsBounded;
    typedef TagTrue IsUnsigned;
    typedef TagTrue IsSigned;
    typedef TagTrue IsSpecialized;
    typedef DGtal::BigInteger SignedVersion;
    typedef DGtal::BigInteger UnsignedVersion;
    typedef DGtal::BigInteger ReturnType;
    typedef DGtal::BigInteger ParamType;
    static const DGtal::BigInteger ZERO;
    static const DGtal::BigInteger ONE;
    static ReturnType zero()
    {
      return ZERO;
    }
    static ReturnType one()
    {
      return ONE;
    }
    static ReturnType min()
    {
      FATAL_ERROR_MSG(false, "UnBounded interger type does not support min() function");
      return ZERO;
    }
    static ReturnType max()
    {
      FATAL_ERROR_MSG(false, "UnBounded interger type does not support max() function");
      return ZERO;
    }

    static unsigned int digits()
    {
      FATAL_ERROR_MSG(false, "UnBounded interger type does not support digits() function");
      return 0;
    }
    static BoundEnum isBounded()
    {
      return BOUNDED;
    }
    static SignEnum isSigned()
    {
      return SIGNED;
    }
    static DGtal::int64_t castToInt64_t(const DGtal::BigInteger & aT)
    {
      return aT.get_si();
    }
    static double castToDouble(const DGtal::BigInteger & aT)
    {
      return aT.get_d();
    }
    /**
       @param aT any number.
       @return 'true' iff the number is even.
    */
    static bool even( ParamType aT )
    {
      return mpz_even_p( aT.get_mpz_t() );
    }
    /**
       @param aT any number.
       @return 'true' iff the number is odd.
    */
    static bool odd( ParamType aT )
    {
      return mpz_odd_p( aT.get_mpz_t() );
    }
  }; // end of class NumberTraits<DGtal::BigInteger>.
#endif


  class Warning_promote_trait_not_specialized_for_this_case { };

  template<class A, class B>
  struct promote_trait
  {
    typedef Warning_promote_trait_not_specialized_for_this_case promote_t;
  };

  template<>
  struct promote_trait<int32_t, int64_t>
  {
    typedef int64_t promote_t;
  };

} // namespace DGtal


///////////////////////////////////////////////////////////////////////////////
// Includes inline functions.
#include "DGtal/kernel/NumberTraits.ih"

//                                                                           //
///////////////////////////////////////////////////////////////////////////////

#endif // !defined NumberTraits_h

#undef NumberTraits_RECURSES
#endif // else defined(NumberTraits_RECURSES)
