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
 * @file testInHalfPlane-benchmark.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/11/22
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "DGtal/base/Common.h"

#include "DGtal/kernel/PointVector.h"

#include "DGtal/geometry/tools/determinant/C2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/Simple2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/SimpleIncremental2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/AvnaimEtAl2x2DetSignComputer.h"
#include "DGtal/geometry/tools/determinant/Filtered2x2DetComputer.h"

#include "DGtal/geometry/tools/determinant/COrientationFunctor2.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBy2x2DetComputer.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;


///////////////////////////////////////////////////////////////////////////////
// Random Functions 
///////////////////////////////////////////////////////////////////////////////
/**
 * @return a random integer of type DGtal::int32_t
 * lying in the range [0 ; 2^15[
 */
DGtal::int32_t randomInt15 ()
{
  return static_cast<DGtal::int32_t>(rand() % 32768); 
}

/**
 * @return a random integer of type DGtal::int32_t
 * lying in the range [0 ; 2^26[
 */
DGtal::int32_t randomInt26 ()
{
  return static_cast<DGtal::int32_t>(rand() % 2048) + 
    ( randomInt15() * 2048 ); 
}

/**
 * @return a random integer of type DGtal::int32_t
 * lying in the range [0 ; 2^30[
 */
DGtal::int32_t randomInt30 ()
{
  return randomInt15() + 
    ( randomInt15() * 32768 ); 
}

/**
 * @return a random integer of type DGtal::int64_t
 * lying in the range [0 ; 2^52[
 */
DGtal::int64_t randomInt52 ()
{
  return
    static_cast<DGtal::int64_t>(rand() % 128) + 
    ( static_cast<DGtal::int64_t>(randomInt15()) +  
      ( static_cast<DGtal::int64_t>(randomInt30()) ) 
      * 32768 ) 
    * 128; 
}

/**
 * @return a random integer of type double
 * lying in the range [0 ; 2^52[
 */
double randomDouble52 ()
{
  return
    static_cast<double>(rand() % 128) + 
    ( static_cast<double>(randomInt15()) +  
      ( static_cast<double>(randomInt30()) ) 
      * 32768 ) 
    * 128; 
}

/**
 * @return a random integer of type DGtal::int64_t
 * lying in the range [0 ; 2^62[
 */
DGtal::int64_t randomInt62 ()
{
  return
    static_cast<DGtal::int64_t>(rand() % 4) + 
    ( static_cast<DGtal::int64_t>(randomInt30()) +  
      ( static_cast<DGtal::int64_t>(randomInt30()) ) 
      * 1073741824 ) 
    * 4; 
}


#ifdef WITH_BIGINTEGER
/**
 * @return a random integer of type DGtal::BigInteger
 * lying in the range [0 ; 2^62[
 */
DGtal::BigInteger randomBigInt62 ()
{
  return
    static_cast<DGtal::BigInteger>(rand() % 4) + 
    ( static_cast<DGtal::BigInteger>(randomInt30()) +  
      ( static_cast<DGtal::BigInteger>(randomInt30()) ) 
      * 1073741824 ) 
    * 4; 
}
#endif

/**
 * @return a random (signed) integer of type DGtal::int32_t
 * lying in the range [-2^15 ; 2^15[
 */
DGtal::int32_t signedRandomInt15 ()
{
  DGtal::int32_t x = randomInt15(); 
  return ((rand() % 2) ? x : -x);
}

/**
 * @return a random (signed) integer of type DGtal::int32_t
 * lying in the range [-2^26 ; 2^26[
 */
DGtal::int32_t signedRandomInt26 ()
{
  DGtal::int32_t x = randomInt26(); 
  return ((rand() % 2) ? x : -x);
}

/**
 * @return a random (signed) integer of type DGtal::int32_t
 * lying in the range [-2^30 ; 2^30[
 */
DGtal::int32_t signedRandomInt30 ()
{
  DGtal::int32_t x = randomInt30(); 
  return ((rand() % 2) ? x : -x);
}

/**
 * @return a random (signed) integer of type DGtal::int64_t
 * lying in the range [-2^52 ; 2^52[
 */
DGtal::int64_t signedRandomInt52 ()
{
  DGtal::int64_t x = randomInt52(); 
    return ((rand() % 2) ? x : -x);
}

/**
 * @return a random (signed) integer of type double
 * lying in the range [-2^52 ; 2^52[
 */
double signedRandomDouble52 ()
{
  double x = randomDouble52(); 
  return ((rand() % 2) ? x : -x);
}

/**
 * @return a random (signed) integer of type DGtal::int64_t
 * lying in the range [-2^62 ; 2^62[
 */
DGtal::int64_t signedRandomInt62 ()
{
  DGtal::int64_t x = randomInt62(); 
    return ((rand() % 2) ? x : -x);
}

#ifdef WITH_BIGINTEGER
/**
 * @return a random (signed) integer of type DGtal::BigInteger
 * lying in the range [-2^62 ; 2^62[
 */
DGtal::BigInteger signedRandomBigInt62 ()
{
  DGtal::BigInteger x = randomBigInt62(); 
  if (rand() % 2)
    return x; 
  else 
    return -x;
}
#endif

///////////////////////////////////////////////////////////////////////////////
// Tests Functions 
///////////////////////////////////////////////////////////////////////////////
/**
 * Function that traces to the standard output the running
 * time of a given functor @a f for @a n computations over 
 * points whose coordinates are randomly chosen by @a gen.
 * @param f a functor to run
 * @param gen a generator providing random numbers
 * @param n number of tries 
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor, typename RandomFunctor>
bool randomTest(OrientationFunctor f, RandomFunctor gen, const DGtal::int32_t n = 1000000)
{
  BOOST_CONCEPT_ASSERT((  DGtal::concepts::COrientationFunctor2<OrientationFunctor> )); 

  typedef typename OrientationFunctor::Point Point; 
  Point P, Q, R; 

  clock_t timeBegin, timeEnd;
  timeBegin = clock();

  for (DGtal::int32_t i = 0; (i < n); ++i)
    {
      P[0] = gen(); 
      P[1] = gen(); 
      Q[0] = gen(); 
      Q[1] = gen(); 
      f.init(P, Q);
      R[0] = gen(); 
      R[1] = gen(); 
      f( R );
    }

  timeEnd = clock();
  long double time, CPUTime;
  time = ((double)timeEnd-(double)timeBegin); 
  CPUTime = time/((double)CLOCKS_PER_SEC);  
  std::cout << CPUTime << " "; 

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of a given orientation functor @a f for @a n computations
 * for three points P, Q, R such that Q = R. 
 * The coordinates of P and Q are randomly chosen by @a gen.
 * @param f a functor to run
 * @param gen a generator providing random numbers
 * @param n number of tries 
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor, typename RandomFunctor>
bool nullSameVectorsTest(OrientationFunctor f, RandomFunctor gen, const DGtal::int32_t n = 1000000)
{
  BOOST_CONCEPT_ASSERT((  DGtal::concepts::COrientationFunctor2<OrientationFunctor> )); 

  typedef typename OrientationFunctor::Point Point; 
  Point P, Q; 

  clock_t timeBegin, timeEnd;
  timeBegin = clock();

  for (DGtal::int32_t i = 0; (i < n); ++i)
    {
      P[0] = gen(); 
      P[1] = gen(); 
      Q[0] = gen(); 
      Q[1] = gen(); 
      f.init(P, Q);
      f( Q );
    }

  timeEnd = clock();
  long double time, CPUTime;
  time = ((double)timeEnd-(double)timeBegin); 
  CPUTime = time/((double)CLOCKS_PER_SEC);  
  std::cout << CPUTime << " "; 

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of a given orientation functor @a f for @a n computations
 * for three points P, Q, R such that R = P. 
 * The coordinates of P and R are randomly chosen by @a gen.
 * @param f a functor to run
 * @param gen a generator providing random numbers
 * @param n number of tries 
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor, typename RandomFunctor>
bool nullZeroVectorTest(OrientationFunctor f, RandomFunctor gen, const DGtal::int32_t n = 1000000)
{
  BOOST_CONCEPT_ASSERT((  DGtal::concepts::COrientationFunctor2<OrientationFunctor> )); 

  typedef typename OrientationFunctor::Point Point; 
  Point P, Q; 

  clock_t timeBegin, timeEnd;
  timeBegin = clock();

  for (DGtal::int32_t i = 0; (i < n); ++i)
    {
      P[0] = gen(); 
      P[1] = gen(); 
      Q[0] = gen(); 
      Q[1] = gen(); 
      f.init(P, Q);
      f( P );
    }

  timeEnd = clock();
  long double time, CPUTime;
  time = ((double)timeEnd-(double)timeBegin); 
  CPUTime = time/((double)CLOCKS_PER_SEC);  
  std::cout << CPUTime << " "; 

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of a given orientation functor @a f for @a n computations
 * for three collinear points P, Q, R such that Q-P = ku and 
 * R-P = lu. 
 * P is set to (0,0), the components of u, k and l are randomly chosen by @a gen.
 * @param f a functor to run
 * @param gen a generator providing random numbers
 * @param n number of tries 
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor, typename RandomFunctor>
bool nullTest(OrientationFunctor f, RandomFunctor gen, const DGtal::int32_t n = 1000000)
{
  BOOST_CONCEPT_ASSERT(( DGtal::concepts::COrientationFunctor2<OrientationFunctor> )); 

  typedef typename OrientationFunctor::Point Point; 
  Point P, Q, R; 
  P = Point(0,0); 

  typedef typename Point::Coordinate Coordinate; 
  Coordinate k, l, u0, u1; 

  clock_t timeBegin, timeEnd;
  timeBegin = clock();

  for (DGtal::int32_t i = 0; (i < n); ++i)
    {
      k = gen(); 
      l = gen(); 
      u0 = gen(); 
      u1 = gen();
      Q[0] = k*u0; 
      Q[1] = k*u1; 
      R[0] = l*u0; 
      R[1] = l*u1;   
      f.init(P, Q);
      f( R );
    }

  timeEnd = clock();
  long double time, CPUTime;
  time = ((double)timeEnd-(double)timeBegin); 
  CPUTime = time/((double)CLOCKS_PER_SEC);  
  std::cout << CPUTime << " "; 

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of a given orientation functor @a f for @a n computations
 * for three quasi-collinear points P, Q, R defined such that 
 * Q-P = ku + epsilon and R-P = lu + epsilon where espilon is 
 * a random integer between -2 and 2.  
 * P is set to (0,0), the components of u, k and l are randomly chosen by @a gen.
 * @param f a functor to run
 * @param gen a generator providing random numbers
 * @param n number of tries 
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor, typename RandomFunctor>
bool quasiNullTest(OrientationFunctor f, RandomFunctor gen, const DGtal::int32_t n = 1000000)
{
  BOOST_CONCEPT_ASSERT(( DGtal::concepts::COrientationFunctor2<OrientationFunctor> )); 

  typedef typename OrientationFunctor::Point Point; 
  Point P, Q, R; 
  P = Point(0,0); 

  typedef typename Point::Coordinate Coordinate; 
  Coordinate k, l, u0, u1; 

  clock_t timeBegin, timeEnd;
  timeBegin = clock();

  for (DGtal::int32_t i = 0; (i < n); ++i)
    {
      k = gen(); 
      l = gen(); 
      u0 = gen(); 
      u1 = gen();
      Q[0] = k*u0;
      Q[0] += (rand()%5)-2; 
      Q[1] = k*u1; 
      Q[1] += (rand()%5)-2; 
      R[0] = l*u0; 
      R[0] += (rand()%5)-2; 
      R[1] = l*u1;   
      R[1] += (rand()%5)-2; 
      f.init(P, Q);
      f( R );
    }

  timeEnd = clock();
  long double time, CPUTime;
  time = ((double)timeEnd-(double)timeBegin); 
  CPUTime = time/((double)CLOCKS_PER_SEC);  
  std::cout << CPUTime << " "; 

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of a given orientation functor @a f for @a n computations.
 * The orientation functor is initialized with 2 points given 
 * once for all. 
 * We then compute the orientation of a random sequence of adjacent points
 * with respect to these two points. 
 *
 * @param f a functor to run
 * @param n number of tries 
 * @tparam OrientationFunctor a model of COrientationFunctor2
 */
template<typename OrientationFunctor>
bool incTest(OrientationFunctor f, const DGtal::int32_t n = 1000000)
{
  BOOST_CONCEPT_ASSERT((  DGtal::concepts::COrientationFunctor2<OrientationFunctor> )); 

  typedef typename OrientationFunctor::Point Point; 
  Point P, Q, R; 

  typedef typename Point::Coordinate Coordinate; 
  Coordinate dx, dy; 

  Coordinate max = 1073741824;  
  P = Point(0,0); 
  Q = Point(max, max);  
  R = Point(max/2, max/2); 
  f.init(P, Q);

  clock_t timeBegin, timeEnd;
  timeBegin = clock();

  for (DGtal::int32_t i = 0; (i < n); ++i)
    {
      dx = (rand() % 3) - 1; 
      dy = (rand() % 3) - 1; 
      R[0] += dx; 
      ASSERT( R[0] >= -max ); 
      ASSERT( R[0] < max ); 
      R[1] += dy; 
      ASSERT( R[0] >= -max ); 
      ASSERT( R[0] < max ); 
      f( R );
    }

  timeEnd = clock();
  long double time, CPUTime;
  time = ((double)timeEnd-(double)timeBegin); 
  CPUTime = time/((double)CLOCKS_PER_SEC);  
  std::cout << CPUTime << " "; 

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of all available functors for random points whose 
 * coordinates are within [-2^30 ; 2^30[.
 */
bool incTestComparison()
{
  typedef PointVector<2, DGtal::int32_t> Point; 

  long seed = time(NULL); 

  std::cout << "# incremental input " << std::endl; 
  std::cout << "# running times in s. for 1 million tries" << std::endl; 

  { 
    srand(seed); 
    std::cout << "2x2-int32-int64 "; 
    typedef Simple2x2DetComputer<DGtal::int32_t, DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    incTest( F() );
    std::cout << std::endl; 
  }
  { 
    srand(seed); 
    std::cout << "2x2-inc-int32-int64 "; 
    typedef SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    incTest( F() );
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim++-int32-double "; 
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> F; 
    incTest( F() );
    std::cout << std::endl;   
  }
#ifdef WITH_BIGINTEGER
  { 
    srand(seed); 
    std::cout << "2x2-int32-BigInt "; 
    typedef Simple2x2DetComputer<DGtal::int32_t, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    incTest( F() );
    std::cout << std::endl; 
  }
  { 
    srand(seed); 
    std::cout << "2x2-inc-int32-BigInt "; 
    typedef SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    incTest( F() );
    std::cout << std::endl;   
  }
#endif
  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of all available functors for random points whose 
 * coordinates are within [-2^30 ; 2^30[.
 */
bool randomTest30All()
{
  typedef PointVector<2, DGtal::int32_t> Point; 

  std::cout << "# random integers within [-2^30 ; 2^30[" << std::endl; 
  std::cout << "# running times in s. for 1 million tries" << std::endl; 
  std::cout << "# columns: random, null1, null2, null3, quasi-null " << std::endl; 
  std::cout << "# NB. double has " << std::numeric_limits<double>::digits << " bits in the mantissa " << std::endl; 

  long seed = time(NULL); 

  {
    srand(seed); 
    std::cout << "3x3-int32-int64 "; 
    typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int64_t> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl; 
  }
#ifdef WITH_BIGINTEGER
  { 
    srand(seed); 
    std::cout << "3x3-int32-BigInt "; 
    typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::BigInteger> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
}
#endif
  { 
    srand(seed); 
    std::cout << "2x2-int32-int64 "; 
    typedef Simple2x2DetComputer<DGtal::int32_t, DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl; 
  }
#ifdef WITH_BIGINTEGER
  {
    srand(seed); 
    std::cout << "2x2-int32-BigInt "; 
    typedef Simple2x2DetComputer<DGtal::int32_t, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
  }
#endif 
  { 
    srand(seed); 
    std::cout << "2x2-inc-int32-int64 "; 
    typedef SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
  }
#ifdef WITH_BIGINTEGER
  { 
    srand(seed); 
    std::cout << "2x2-inc-int32-BigInt "; 
    typedef SimpleIncremental2x2DetComputer<DGtal::int32_t, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
  }
#endif
  {
    srand(seed); 
    std::cout << "2x2-avnaim-int32-int32 "; 
    typedef AvnaimEtAl2x2DetSignComputer<DGtal::int32_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
  }
  { 
    srand(seed); 
    std::cout << "2x2-avnaim-int32-double "; 
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim++-int32-double "; 
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> F; 
    randomTest( F(), signedRandomInt30 );
    nullSameVectorsTest( F(), signedRandomInt30 );
    nullZeroVectorTest( F(), signedRandomInt30 ); 
    nullTest( F(), signedRandomInt15 ); 
    quasiNullTest( F(), signedRandomInt15 ); 
    std::cout << std::endl;   
  }

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of all available functors for random points whose 
 * coordinates are within [-2^52 ; 2^52[.
 */
bool randomTest52All()
{
  std::cout << "# random integers within [-2^52 ; 2^52[" << std::endl; 
  std::cout << "# running times in s. for 1 million tries" << std::endl; 
  std::cout << "# columns: random, null1, null2, null3, quasi-null " << std::endl; 
  std::cout << "# NB. double has " << std::numeric_limits<double>::digits << " bits in the mantissa " << std::endl; 

  long seed = time(NULL); 

#ifdef WITH_BIGINTEGER
  { //! BigInt cannot be constructed from a DGtal::int64_t
    srand(seed); 
    std::cout << "3x3-double-BigInt ";  
    typedef PointVector<2, double> Point; 
    typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::BigInteger> F; 
    randomTest( F(), signedRandomDouble52 );
    nullSameVectorsTest( F(), signedRandomDouble52 );
    nullZeroVectorTest( F(), signedRandomDouble52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-double-BigInt "; 
    typedef PointVector<2, double> Point; 
    typedef Simple2x2DetComputer<double, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomDouble52 );
    nullSameVectorsTest( F(), signedRandomDouble52 );
    nullZeroVectorTest( F(), signedRandomDouble52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  { 
    srand(seed); 
    std::cout << "2x2-inc-double-BigInt "; 
    typedef PointVector<2, double> Point; 
    typedef SimpleIncremental2x2DetComputer<double, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomDouble52 );
    nullSameVectorsTest( F(), signedRandomDouble52 );
    nullZeroVectorTest( F(), signedRandomDouble52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
#endif
  {
    srand(seed); 
    std::cout << "2x2-avnaim-int64-int64 "; 
    typedef PointVector<2, DGtal::int64_t> Point; 
    typedef AvnaimEtAl2x2DetSignComputer<DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt52 );
    nullSameVectorsTest( F(), signedRandomInt52 );
    nullZeroVectorTest( F(), signedRandomInt52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim-double-int64 "; 
    typedef PointVector<2, double> Point; 
    typedef AvnaimEtAl2x2DetSignComputer<DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomDouble52 );
    nullSameVectorsTest( F(), signedRandomDouble52 );
    nullZeroVectorTest( F(), signedRandomDouble52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim-int64-double "; 
    typedef PointVector<2, DGtal::int64_t> Point; 
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt52 );
    nullSameVectorsTest( F(), signedRandomInt52 );
    nullZeroVectorTest( F(), signedRandomInt52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  { 
    srand(seed); 
    std::cout << "2x2-avnaim-double-double "; 
    typedef PointVector<2, double> Point; 
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomDouble52 );
    nullSameVectorsTest( F(), signedRandomDouble52 );
    nullZeroVectorTest( F(), signedRandomDouble52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim++-int64-double ";
    typedef PointVector<2, DGtal::int64_t> Point;  
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> F; 
    randomTest( F(), signedRandomInt52 );
    nullSameVectorsTest( F(), signedRandomInt52 );
    nullZeroVectorTest( F(), signedRandomInt52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim++-double-double ";
    typedef PointVector<2, double> Point;  
    typedef AvnaimEtAl2x2DetSignComputer<double> DetComputer; 
    typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> F; 
    randomTest( F(), signedRandomDouble52 );
    nullSameVectorsTest( F(), signedRandomDouble52 );
    nullZeroVectorTest( F(), signedRandomDouble52 ); 
    nullTest( F(), signedRandomInt26 ); 
    quasiNullTest( F(), signedRandomInt26 ); 
    std::cout << std::endl;   
  }

  return true; 
}

/**
 * Function that traces to the standard output the running
 * time of all available functors for random points whose 
 * coordinates are within [-2^62 ; 2^62[.
 */
bool randomTest62All()
{
  std::cout << "# random integers within [-2^62 ; 2^62[" << std::endl; 
  std::cout << "# running times in s. for 1 million tries" << std::endl; 
  std::cout << "# columns: random, null1, null2, null3, quasi-null " << std::endl; 
  std::cout << "# NB. long double has " << std::numeric_limits<long double>::digits << " bits in the mantissa " << std::endl; 

  long seed = time(NULL); 

#ifdef WITH_BIGINTEGER
  { //! BigInt cannot be constructed from a DGtal::int64_t
    srand(seed); 
    std::cout << "3x3-BigInt-BigInt ";  
    typedef PointVector<2, DGtal::BigInteger> Point; 
    typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::BigInteger> F; 
    randomTest( F(), signedRandomBigInt62 );
    nullSameVectorsTest( F(), signedRandomBigInt62 );
    nullZeroVectorTest( F(), signedRandomBigInt62 ); 
    nullTest( F(), signedRandomInt30 ); 
    quasiNullTest( F(), signedRandomInt30 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-BigInt-BigInt "; 
    typedef PointVector<2, DGtal::BigInteger> Point; 
    typedef Simple2x2DetComputer<DGtal::BigInteger, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomBigInt62 );
    nullSameVectorsTest( F(), signedRandomBigInt62 );
    nullZeroVectorTest( F(), signedRandomBigInt62 ); 
    nullTest( F(), signedRandomInt30 ); 
    quasiNullTest( F(), signedRandomInt30 ); 
    std::cout << std::endl;   
  }
  { 
    srand(seed); 
    std::cout << "2x2-inc-BigInt-BigInt "; 
    typedef PointVector<2, DGtal::BigInteger> Point; 
    typedef SimpleIncremental2x2DetComputer<DGtal::BigInteger, DGtal::BigInteger> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomBigInt62 );
    nullSameVectorsTest( F(), signedRandomBigInt62 );
    nullZeroVectorTest( F(), signedRandomBigInt62 ); 
    nullTest( F(), signedRandomInt30 ); 
    quasiNullTest( F(), signedRandomInt30 ); 
    std::cout << std::endl;   
  }
#endif
  { 
    srand(seed); 
    std::cout << "2x2-avnaim-int64-int64 "; 
    typedef PointVector<2, DGtal::int64_t> Point; 
    typedef AvnaimEtAl2x2DetSignComputer<DGtal::int64_t> DetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, DetComputer> F; 
    randomTest( F(), signedRandomInt62 );
    nullSameVectorsTest( F(), signedRandomInt62 );
    nullZeroVectorTest( F(), signedRandomInt62 ); 
    nullTest( F(), signedRandomInt30 ); 
    quasiNullTest( F(), signedRandomInt30 ); 
    std::cout << std::endl;   
  }
  {
    srand(seed); 
    std::cout << "2x2-avnaim++-int64-longdouble ";
    typedef PointVector<2, DGtal::int64_t> Point;  
    typedef AvnaimEtAl2x2DetSignComputer<long double> DetComputer; 
    typedef Filtered2x2DetComputer<DetComputer> FDetComputer; 
    typedef InHalfPlaneBy2x2DetComputer<Point, FDetComputer> F; 
    randomTest( F(), signedRandomInt62 );
    nullSameVectorsTest( F(), signedRandomInt62 );
    nullZeroVectorTest( F(), signedRandomInt62 ); 
    nullTest( F(), signedRandomInt30 ); 
    quasiNullTest( F(), signedRandomInt30 ); 
    std::cout << std::endl;   
  }

  return true; 
}

///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class InHalfPlane-benchmark" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  incTestComparison(); 
  randomTest30All(); 
  randomTest52All(); 
  randomTest62All(); 

  bool res = true; 
  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
