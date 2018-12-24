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
 * @file testArithmeticalDSLKernel.cpp
 * @ingroup Tests
 * @author Tristan Roussillon (\c tristan.roussillon@liris.cnrs.fr )
 * Laboratoire d'InfoRmatique en Image et Systèmes d'information - LIRIS (CNRS, UMR 5205), CNRS, France
 *
 * @date 2013/07/03
 *
 * Functions for testing class ArithmeticalDSLKernel.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"

#include "DGtal/geometry/curves/ArithmeticalDSLKernel.h"
///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ArithmeticalDSLKernel.
///////////////////////////////////////////////////////////////////////////////
/**
 * General test. 
 * 
 * @param a a-parameter
 * @param b b-parameter
 *
 * @tparam Coordinate model of integer for the vector components
 * @tparam Integer model of integer for the a- and b-parameter
 * @tparam adj integer equal to 4 or 8 for the adjacency type
 */
template <typename Coordinate, typename Integer, unsigned short adj>
bool test(const Integer& a, const Integer& b)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "testing general cases..." );

  typename ArithmeticalDSLKernel<Coordinate, adj>::Steps steps = 
    ArithmeticalDSLKernel<Coordinate, adj>::steps(a, b); 

  trace.info() << " step1: " << steps.first << std::endl;
  trace.info() << " step2: " << steps.second << std::endl;

  typename ArithmeticalDSLKernel<Coordinate, adj>::Vector shift = 
    ArithmeticalDSLKernel<Coordinate, adj>::shift(a, b);   

  trace.info() << " shift: " << shift << std::endl;

  if ( (steps.first - steps.second) == shift )
    nbok++; 
  nb++; 

  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;
  trace.endBlock();
  
  return nbok == nb;
}

/**
 * Test for the special cases  
 * 
 * @param a a-parameter
 * @param b b-parameter
 *
 * @tparam Coordinate model of integer for the vector components
 * @tparam Integer model of integer for the a- and b-parameter
 * @tparam adj integer equal to 4 or 8 for the adjacency type
 */
template <typename Coordinate, typename Integer, unsigned short adj>
bool specialCases(const Integer& a, const Integer& b)
{
  unsigned int nbok = 0;
  unsigned int nb = 0;
  
  trace.beginBlock ( "testing special cases..." );

  trace.info() << " a " << a << " b " << b << std::endl;

  typename ArithmeticalDSLKernel<Coordinate, adj>::Steps steps = 
    ArithmeticalDSLKernel<Coordinate, adj>::steps(a, b); 

  trace.info() << " step1: " << steps.first << std::endl;
  trace.info() << " step2: " << steps.second << std::endl;

  typedef typename ArithmeticalDSLKernel<Coordinate, adj>::Vector Vector; 
  Vector shift = 
    ArithmeticalDSLKernel<Coordinate, adj>::shift(a, b);   

  trace.info() << " shift: " << shift << std::endl;

  if ( (a == 0) && (b == 0) )
    {
      if ( (steps.first == Vector(0,0)) 
	   && (steps.second == Vector(0,0)) 
	   && (shift == Vector(0,0)))
	nbok++; 
      nb++; 
    }
  else
    {
      if ( (a == 0)||(b == 0) )
	{
	  if ( (steps.first != Vector(0,0)) 
	       && (steps.second == Vector(0,0)) 
	       && (shift != Vector(0,0)))
	    nbok++; 
	  nb++; 
	}
      else 
	{
	  if ( (adj == 8)
	       &&( (a == b)||(a == -b) ) )
	    {
	      if ( (steps.first != Vector(0,0)) 
		   && (steps.second == Vector(0,0)) 
		   && (shift != Vector(0,0)) )
		nbok++; 
	      nb++; 
	    }
	  else 
	    {
	      if ( (steps.first != Vector(0,0)) 
		   && (steps.second != Vector(0,0)) 
		   && (shift != Vector(0,0)) )
		nbok++; 
	      nb++; 
	    }
	}
    }
  trace.info() << "(" << nbok << "/" << nb << ") "
	       << std::endl;
  trace.endBlock();
  
  return nbok == nb;

}


///////////////////////////////////////////////////////////////////////////////
// Standard services - public :

int main( int argc, char** argv )
{
  trace.beginBlock ( "Testing class ArithmeticalDSLKernel" );
  trace.info() << "Args:";
  for ( int i = 0; i < argc; ++i )
    trace.info() << " " << argv[ i ];
  trace.info() << endl;

  //-------------- general tests -------------------------
  //8-adjacency
  bool res = test<DGtal::int32_t, DGtal::int32_t, 8>(8,5)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(5,8)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(-5,8)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(-8,5)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(-8,-5)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(-5,-8)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(5,-8)
    && test<DGtal::int32_t, DGtal::int32_t, 8>(8,-5)
    ; 

  //4-adjacency
  res = res 
    && test<DGtal::int32_t, DGtal::int32_t, 4>(8,5)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(5,8)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(-5,8)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(-8,5)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(-8,-5)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(-5,-8)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(5,-8)
    && test<DGtal::int32_t, DGtal::int32_t, 4>(8,-5)
    ; 

  //-------------- special tests --------------------------
  //8-adjacency
  res = res 
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(0,0)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(0,5)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(0,-5)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(5,0)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(-5,0)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(1,1)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(1,-1)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(-1,1)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 8>(-1,-1)
    ; 

  //4-adjacency
  res = res 
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(0,0)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(0,5)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(0,-5)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(5,0)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(-5,0)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(1,1)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(1,-1)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(-1,1)
    && specialCases<DGtal::int32_t, DGtal::int32_t, 4>(-1,-1)
    ; 





#ifdef WITH_BIGINTEGER
  res = res 
    && test<DGtal::BigInteger, DGtal::BigInteger, 8>(8,5) 
    && test<DGtal::BigInteger, DGtal::BigInteger, 4>(8,5)
    ; 
#endif

  trace.emphase() << ( res ? "Passed." : "Error." ) << endl;
  trace.endBlock();
  return res ? 0 : 1;
}
//                                                                           //
///////////////////////////////////////////////////////////////////////////////
