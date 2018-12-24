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
 * @file test2x2DetComputers.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/18
 *
 * Functions for testing classes that implements a model of C2x2DetComputer.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/kernel/NumberTraits.h"
#include "DGtal/geometry/tools/determinant/C2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/SimpleIncremental2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"
#include "DGtal/geometry/tools/determinant/Filtered2x2DetComputer.h"
//////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing various model of CIncremental2x2DeterminantComputer
///////////////////////////////////////////////////////////////////////////////

/**
 * Function that compares the result returned by @a aComputer
 * with a ground truth in each quadrant. 
 * @param aComputer any determinant computer
 * @tparam DetComputer a model of CIncremental2x2DetComputer
 */
template<typename DetComputer>
bool simpleTest2x2DetComputer(DetComputer aComputer)
{
  BOOST_CONCEPT_ASSERT(( C2x2DetComputer<DetComputer> )); 
  typedef typename DetComputer::Integer Integer; 
  typedef typename DetComputer::Value Value; 

  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "Testing block ..." );
  trace.info() << aComputer << endl; 

  Integer a = 5; 
  Integer b = 2; 


  //first quadrant
  aComputer.init(a,b); 
  if (aComputer(2,1) == NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(3,1) == -NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(5,2) == NumberTraits<Value>::ZERO)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //second quadrant
  aComputer.init(-a,b); 
  if (aComputer(2,-1) == NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(3,-1) == -NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(5,-2) == NumberTraits<Value>::ZERO)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //third quadrant
  aComputer.init(-a,-b); 
  if (aComputer(-2,-1) == NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(-3,-1) == -NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(-5,-2) == NumberTraits<Value>::ZERO)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  //fourth quadrant
  aComputer.init(a,-b); 
  if (aComputer(-2,1) == NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(-3,1) == -NumberTraits<Value>::ONE)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  if (aComputer(-5,2) == NumberTraits<Value>::ZERO)
    nbok++; 
  nb++; 
  trace.info() << "(" << nbok << "/" << nb << ") " << endl;

  trace.endBlock();
  
  return nbok == nb;
}

/**
 * Function that retuns 'true' if @a x1 and @a x2
 * have the same sign: 
 * - both strictly positive
 * - both strictly negative
 * - both null
 * and 'false' otherwise. 
 *
 * @param x1 a first integer
 * @param x2 a second integer
 * @tparam I1 type of the first integer
 * @tparam I2 type of the second integer
 */
template <typename I1, typename I2>
bool hasTheSameSign(I1 x1, I2 x2)
{
  if (x1 == NumberTraits<I1>::ZERO)
    {
      if (x2 == NumberTraits<I2>::ZERO)
	return true; 
      else
	return false; 
    }
  else if (x1 > NumberTraits<I1>::ZERO)
    {
      if (x2 > NumberTraits<I2>::ZERO)
	return true; 
      else
	return false; 
    }
  else //if (x1 < NumberTraits<I1>::ZERO)
    {
      if (x2 < NumberTraits<I2>::ZERO)
	return true; 
      else
	return false; 
    }
}

DGtal::int32_t randomBelow2exp15 ()
{
  return static_cast<DGtal::int32_t>(rand() % 32768); 
}
DGtal::int32_t adHocRandom ()
{
  DGtal::int32_t x = randomBelow2exp15() + 
    32768 * ( randomBelow2exp15() ); 
    return ((rand() % 2) ? x : -x);
}

/**
 * Function that compares the result returned by @a aComputer
 * against the result returned by Simple2x2DetComputer 
 * using integers on 32 and 64 bits for various matrices 
 * whose entries are random integers whose absolute value is 
 * less than 2^32. 
 * @param aComputer a determinant computer to test
 * @tparam DetComputer a model of CIncremental2x2DetComputer
 */
template<typename DetComputer>
bool randomTest2x2DetComputer(DetComputer aComputer)
{
  BOOST_CONCEPT_ASSERT(( C2x2DetComputer<DetComputer> )); 

  typedef Simple2x2DetComputer<DGtal::int32_t, DGtal::int64_t> TrueComputer; 
  TrueComputer trueComputer; 

  trace.beginBlock ( "Testing block ..." );
  trace.info() << trueComputer << " vs " << aComputer << endl; 

  bool isOk = true; 

  DGtal::int32_t a, b, x, y; 

  const int n = 10000; 
  for (int i = 0; ( (i < n)&&(isOk) ); ++i)
    {
      a = adHocRandom(); 
      b = adHocRandom(); 
      x = adHocRandom();
      y = adHocRandom(); 
      trueComputer.init(a, b); 
      aComputer.init(a, b);
      TrueComputer::Value trueRes = trueComputer(x,y);  
      typename DetComputer::Value res = aComputer(x,y);
      // trace.info() << a << "." << y << " - " 
      // 		   << b << " " << x << " => "
      // 		   << trueRes << " / " << res << endl; 
      if ( !hasTheSameSign( trueRes, res ) )
	isOk = false; 
    }

  trace.endBlock();

  return isOk; 
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class 2x2DetComputers" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  bool res = true;
 
  
  res = res 
    && simpleTest2x2DetComputer( Simple2x2DetComputer<DGtal::int16_t, DGtal::int32_t>() )
    && simpleTest2x2DetComputer( Simple2x2DetComputer<DGtal::int32_t, DGtal::int64_t>() )
#ifdef WITH_BIGINTEGER
    && simpleTest2x2DetComputer( Simple2x2DetComputer<DGtal::int32_t, DGtal::BigInteger>() )
#endif
    && simpleTest2x2DetComputer( SimpleIncremental2x2DetComputer<DGtal::int16_t, DGtal::int32_t>() )
    && simpleTest2x2DetComputer( SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::int64_t>() )
#ifdef WITH_BIGINTEGER
    && simpleTest2x2DetComputer( SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::BigInteger>() )
#endif
    && simpleTest2x2DetComputer( AvnaimEtAl2x2DetSignComputer<DGtal::int16_t>() )
    && simpleTest2x2DetComputer( AvnaimEtAl2x2DetSignComputer<DGtal::int32_t>() )
    && simpleTest2x2DetComputer( AvnaimEtAl2x2DetSignComputer<float>() )
    && simpleTest2x2DetComputer( AvnaimEtAl2x2DetSignComputer<double>() )
    && simpleTest2x2DetComputer( Filtered2x2DetComputer<AvnaimEtAl2x2DetSignComputer<double> >() )

#ifdef WITH_BIGINTEGER
    && randomTest2x2DetComputer( Simple2x2DetComputer<DGtal::int32_t, DGtal::BigInteger>() )
    && randomTest2x2DetComputer( SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::BigInteger>() )
#endif
    && randomTest2x2DetComputer( AvnaimEtAl2x2DetSignComputer<DGtal::int32_t>() )
    && randomTest2x2DetComputer( Filtered2x2DetComputer<AvnaimEtAl2x2DetSignComputer<double> >() )
    ;   

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
